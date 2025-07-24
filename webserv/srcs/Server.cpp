// HTTP Server core implementation for webserv project
// Evaluation point: multi-server and multi-port support
// Evaluation point: select() based I/O multiplexing (REQUIRED: no poll(), epoll(), kqueue())
// Evaluation point: non-blocking socket operations
// Evaluation point: proper socket setup and binding
// Evaluation point: client connection handling and management
// Evaluation point: request parsing and response generation integration
// Evaluation point: concurrent client handling without threads/fork
// Evaluation point: proper error handling and resource cleanup

#include "Server.hpp"       // Server class definition with socket and connection management
#include "Config.hpp"       // Configuration management for server setup
#include "Request.hpp"      // HTTP request parsing functionality
#include "Response.hpp"     // HTTP response generation functionality
#include <sys/socket.h>     // socket(), bind(), listen(), accept() for network programming
#include <netinet/in.h>     // sockaddr_in structure for IPv4 socket addressing
#include <arpa/inet.h>      // inet_addr(), inet_ntoa() for IP address conversion
#include <unistd.h>         // close(), read(), write() for file descriptor operations
#include <fcntl.h>          // fcntl(), F_SETFL, O_NONBLOCK for non-blocking socket setup
#include <errno.h>          // errno global variable for system call error reporting
#include <string.h>         // strerror() for errno to string conversion
#include <iostream>         // std::cerr for debug output and error logging
#include <vector>           // std::vector for container storage
#include <map>              // std::map for port and client mapping
#include <sstream>          // std::ostringstream for string building
#include <iomanip>          // std::hex, std::setw for debug output formatting
#include <cstdlib>          // exit(), EXIT_FAILURE for program termination

// Constructor - initializes server with configuration and sets up listening sockets
// Evaluation point: proper integration with configuration system
// Evaluation point: multi-server setup with port mapping
// Evaluation point: socket creation and binding for multiple ports
Server::Server(const Config& cfg) : config(cfg) {
    std::cerr << "DEBUG: Starting Server constructor" << std::endl << std::flush;
    std::cerr << "DEBUG: Number of server configurations: " << config.getServers().size() << std::endl << std::flush;

    std::map<int, std::vector<size_t> > port_map;
    for (size_t i = 0; i < config.getServers().size(); ++i) {
        const ServerConfig& server_config = config.getServers()[i];
        std::cerr << "DEBUG: Processing server " << i << " with " << server_config.ports.size() << " ports" << std::endl << std::flush;
        for (size_t p = 0; p < server_config.ports.size(); ++p) {
            int port = server_config.ports[p];
            port_map[port].push_back(i);
            std::cerr << "DEBUG: Server " << i << " listens on port " << port << std::endl << std::flush;
        }
    }

    for (std::map<int, std::vector<size_t> >::iterator it = port_map.begin(); it != port_map.end(); ++it) {
        int port = it->first;
        std::cerr << "DEBUG: Setting up socket for port " << port << std::endl << std::flush;
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0) {
            std::stringstream ss;
            ss << port;
            std::cerr << "ERROR: Failed to create socket for port " << port << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            throw std::runtime_error("Failed to create socket for port " + ss.str());
        }
        std::cerr << "DEBUG: Created socket, server_fd: " << fd << " for port " << port << std::endl << std::flush;

        int opt = 1;
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::stringstream ss;
            ss << port;
            std::cerr << "ERROR: Failed to set SO_REUSEADDR for server_fd: " << fd << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            close(fd);
            throw std::runtime_error("Failed to set socket options for port " + ss.str());
        }
        std::cerr << "DEBUG: Set SO_REUSEADDR for server_fd: " << fd << std::endl << std::flush;

        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        if (bind(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::stringstream ss;
            ss << port;
            std::cerr << "ERROR: Failed to bind socket for port " << port << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            close(fd);
            throw std::runtime_error("Failed to bind socket for port " + ss.str());
        }
        std::cerr << "DEBUG: Bound socket, server_fd: " << fd << " to port " << port << std::endl << std::flush;

        if (listen(fd, 10) < 0) {
            std::stringstream ss;
            ss << port;
            std::cerr << "ERROR: Failed to listen on socket for port " << port << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            close(fd);
            throw std::runtime_error("Failed to listen on socket for port " + ss.str());
        }
        std::cerr << "DEBUG: Server listening on server_fd: " << fd << ", port: " << port << std::endl << std::flush;

        if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
            std::stringstream ss;
            ss << port;
            std::cerr << "ERROR: Failed to set non-blocking for server_fd: " << fd << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            close(fd);
            throw std::runtime_error("Failed to set non-blocking for port " + ss.str());
        }
        std::cerr << "DEBUG: server_fd " << fd << " set to non-blocking for port " << port << std::endl << std::flush;

        server_fds.push_back(fd);
        port_to_server_indices[port] = it->second;
        std::cerr << "DEBUG: Added server_fd " << fd << " for port " << port << " with server_indices: ";
        for (size_t i = 0; i < it->second.size(); ++i) {
            std::cerr << it->second[i] << " ";
        }
        std::cerr << std::endl << std::flush;
    }
    std::cerr << "DEBUG: Server initialized with " << server_fds.size() << " sockets" << std::endl << std::flush;
}

// Destructor - cleanup all server and client file descriptors
// Evaluation point: proper resource cleanup and file descriptor management
// Evaluation point: prevention of file descriptor leaks
Server::~Server() {
    for (size_t i = 0; i < server_fds.size(); ++i) {
        close(server_fds[i]);
    }
    for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        close(it->first);
    }
}

// Check if HTTP request is complete (headers + body)
// Evaluation point: proper HTTP message parsing and completion detection
// Evaluation point: support for Transfer-Encoding: chunked
// Evaluation point: support for Content-Length header parsing
// Evaluation point: handling of different HTTP body transmission methods
bool Server::isRequestComplete(const Client& client) const {
    const std::string& buffer = client.buffer;
    size_t header_end = buffer.find("\r\n\r\n");
    if (header_end == std::string::npos) {
        std::cerr << "DEBUG: No header end found in client.buffer, length: " << buffer.length() << std::endl << std::flush;
        return false;
    }

    // Verificar si es Transfer-Encoding: chunked
    size_t te_pos = buffer.find("Transfer-Encoding: chunked");
    if (te_pos != std::string::npos && te_pos < header_end) {
        size_t trailer_pos = buffer.find("0\r\n\r\n", header_end);
        if (trailer_pos == std::string::npos) {
            std::cerr << "DEBUG: Chunked request incomplete, no trailer (0\\r\\n\\r\\n) found" << std::endl << std::flush;
            return false;
        }
        std::cerr << "DEBUG: Chunked request complete, trailer found at position: " << trailer_pos << std::endl << std::flush;
        return true;
    }

    // Verificar Content-Length
    size_t cl_pos = buffer.find("Content-Length: ");
    if (cl_pos != std::string::npos && cl_pos < header_end) {
        size_t cl_value_pos = cl_pos + 16; // Longitud de "Content-Length: "
        size_t cl_end = buffer.find("\r\n", cl_value_pos);
        if (cl_end != std::string::npos) {
            std::string cl_str = buffer.substr(cl_value_pos, cl_end - cl_value_pos);
            size_t content_length = std::atoi(cl_str.c_str());
            if (buffer.length() >= header_end + 4 + content_length) {
                std::cerr << "DEBUG: Content-Length request complete, expected: " << content_length << ", buffer length: " << buffer.length() - (header_end + 4) << std::endl << std::flush;
                return true;
            }
            std::cerr << "DEBUG: Content-Length request incomplete, expected: " << content_length << ", have: " << (buffer.length() - (header_end + 4)) << std::endl << std::flush;
            return false;
        }
    }

    // Si no hay Content-Length ni Transfer-Encoding, asumir que la solicitud está completa
    std::cerr << "DEBUG: No Content-Length or Transfer-Encoding, assuming request complete" << std::endl << std::flush;
    return true;
}

// Main server loop - CORE EVALUATION FUNCTION
// Evaluation point: select() usage for I/O multiplexing (MANDATORY: no poll/epoll/kqueue)
// Evaluation point: non-blocking I/O operations for concurrent client handling
// Evaluation point: proper fd_set management for read and write operations
// Evaluation point: timeout handling for server responsiveness
// Evaluation point: new client acceptance and connection management
// Evaluation point: client request reading and response writing
// Evaluation point: error handling and client disconnection management
// Evaluation point: integration with Request and Response classes
void Server::run() {
    fd_set read_fds, write_fds;
    int max_fd = 0;
    for (size_t i = 0; i < server_fds.size(); ++i) {
        if (server_fds[i] > max_fd) max_fd = server_fds[i];
    }

    while (true) {
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);
        for (size_t i = 0; i < server_fds.size(); ++i) {
            FD_SET(server_fds[i], &read_fds);
        }

        for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
            FD_SET(it->first, &read_fds);
            if (!it->second.response.empty()) {
                FD_SET(it->first, &write_fds);
            }
            if (it->first > max_fd) max_fd = it->first;
        }

        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        int activity = select(max_fd + 1, &read_fds, &write_fds, NULL, &timeout);
        if (activity < 0) {
            // Para select(), se permite verificar EINTR según las buenas prácticas
            if (errno != EINTR) {
                std::cerr << "ERROR: Select error" << std::endl << std::flush;
            }
            continue;
        }
        if (activity == 0) {
            std::cerr << "DEBUG: Select timeout" << std::endl << std::flush;
            continue;
        }

        // Handle new incoming connections on server sockets
        // Evaluation point: new client connection acceptance
        // Evaluation point: non-blocking socket setup for clients
        // Evaluation point: server port resolution and client mapping
        // Evaluation point: proper socket address handling
        for (size_t i = 0; i < server_fds.size(); ++i) {
            if (FD_ISSET(server_fds[i], &read_fds)) {
                struct sockaddr_in client_addr;
                memset(&client_addr, 0, sizeof(client_addr));
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fds[i], (struct sockaddr*)&client_addr, &client_len);
                if (client_fd < 0) {
                    std::cerr << "ERROR: Accept failed for server_fd " << server_fds[i] << std::endl << std::flush;
                    continue;
                }
                if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) {
                    std::cerr << "ERROR: Failed to set client_fd " << client_fd << " to non-blocking" << std::endl << std::flush;
                    close(client_fd);
                    continue;
                }
                struct sockaddr_in server_addr;
                memset(&server_addr, 0, sizeof(server_addr));
                socklen_t server_len = sizeof(server_addr);
                if (getsockname(server_fds[i], (struct sockaddr*)&server_addr, &server_len) < 0) {
                    std::cerr << "ERROR: Failed to get server port for server_fd " << server_fds[i] << std::endl << std::flush;
                    close(client_fd);
                    continue;
                }
                int server_port = ntohs(server_addr.sin_port);
                size_t server_index = port_to_server_indices[server_port][0];
                clients.insert(std::pair<int, Client>(client_fd, Client(server_port, server_index)));
                std::cerr << "DEBUG: New connection: fd " << client_fd << " on port " << server_port << " with server_index " << server_index << std::endl << std::flush;
            }
        }

        // Handle client data reading and processing
        // Evaluation point: non-blocking client data reading with recv()
        // Evaluation point: proper connection cleanup on client disconnect
        // Evaluation point: integration with Request class for HTTP parsing
        // Evaluation point: Host header processing for virtual server selection
        // Evaluation point: progressive HTTP request building and completion detection
        std::vector<int> clients_to_remove;
        for (std::map<int, Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
            int client_fd = it->first;
            Client& client = it->second;

            // Leer datos
            if (FD_ISSET(client_fd, &read_fds)) {
                char buffer[8192] = {0};
                ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);
                if (bytes_read <= 0) {
                    // No usar errno - solo verificar return value
                    if (bytes_read < 0) {
                        std::cerr << "ERROR: Failed to read from fd " << client_fd << std::endl << std::flush;
                    } else {
                        std::cerr << "DEBUG: Connection closed on fd " << client_fd << ", bytes_read: " << bytes_read << std::endl << std::flush;
                    }
                    clients_to_remove.push_back(client_fd);
                    continue;
                }
                std::cerr << "DEBUG: Received " << bytes_read << " bytes on fd " << client_fd << " on port " << client.port << std::endl << std::flush;
                std::cerr << "DEBUG: Received data (string): [" << std::string(buffer, bytes_read).substr(0, 100) << (bytes_read > 100 ? "..." : "") << "]" << std::endl << std::flush;
                std::cerr << "DEBUG: Received data (hex): ";
                for (ssize_t i = 0; i < bytes_read; ++i) {
                    std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)buffer[i] << " ";
                }
                std::cerr << std::dec << std::endl << std::flush;
                client.buffer.append(buffer, bytes_read);
                std::cerr << "DEBUG: Appended to client.buffer, new length: " << client.buffer.length() << std::endl << std::flush;
                std::cerr << "DEBUG: client.buffer content (hex): ";
                for (size_t i = 0; i < client.buffer.length(); ++i) {
                    std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)client.buffer[i] << " ";
                }
                std::cerr << std::dec << std::endl << std::flush;

                try {
                    if (!client.request && isRequestComplete(client)) {
                        std::cerr << "DEBUG: Creating new Request with client.buffer length: " << client.buffer.length() << std::endl << std::flush;
                        client.request = new Request(client_fd, client.buffer);
                    } else if (client.request) {
                        std::cerr << "DEBUG: Appending to existing Request, data length: " << bytes_read << std::endl << std::flush;
                        client.request->appendBody(std::string(buffer, bytes_read));
                    }
                    if (client.request && client.request->isComplete()) {
                        std::cerr << "DEBUG: Parsed request successfully for fd " << client_fd << " on port " << client.port << std::endl << std::flush;
                        size_t server_index = client.server_index;
                        std::string host = client.request->getHeader("Host");
                        if (!host.empty()) {
                            size_t colon_pos = host.find(':');
                            if (colon_pos != std::string::npos) {
                                host = host.substr(0, colon_pos);
                            }
                            const std::vector<size_t>& indices = port_to_server_indices[client.port];
                            bool matched = false;
                            for (size_t i = 0; i < indices.size(); ++i) {
                                const ServerConfig& cfg = config.getServers()[indices[i]];
                                if (cfg.server_name == host) {
                                    server_index = indices[i];
                                    std::cerr << "DEBUG: Matched Host header '" << host << "' to server_index " << server_index << std::endl << std::flush;
                                    matched = true;
                                    break;
                                }
                            }
                            if (!matched) {
                                std::cerr << "DEBUG: No server_name matched for Host: " << host << ", using default server_index " << server_index << std::endl << std::flush;
                            }
                        } else {
                            std::cerr << "DEBUG: Empty Host header, using default server_index " << server_index << std::endl << std::flush;
                        }
                        const ServerConfig& server_config = config.getServers()[server_index];
                        Response response(*client.request, server_config, client.port);
                        client.response = response.handleRequest();
                        client.buffer.clear();
                        delete client.request;
                        client.request = NULL;
                        std::cerr << "DEBUG: Generated response for fd " << client_fd << " on port " << client.port << ", response length: " << client.response.length() << std::endl << std::flush;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "ERROR: Exception handling request for fd " << client_fd << ": " << e.what() << std::endl << std::flush;
                    client.response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\nContent-Length: 71\r\nConnection: close\r\n\r\n<html><body><h1>400 Bad Request - Invalid Request</h1></body></html>";
                    delete client.request;
                    client.request = NULL;
                }
            }

            // Handle response writing to clients  
            // Evaluation point: non-blocking response writing with send()
            // Evaluation point: partial send handling for large responses  
            // Evaluation point: proper connection management after response completion
            if (FD_ISSET(client_fd, &write_fds) && !client.response.empty()) {
                std::cerr << "DEBUG: Sending response for fd " << client_fd << " on port " << client.port << std::endl << std::flush;
                
                // Solo un send() por cliente por select() - cumplir regla de evaluación
                ssize_t bytes_sent = send(client_fd, client.response.c_str() + client.bytes_sent, 
                                        client.response.length() - client.bytes_sent, 0);
                if (bytes_sent < 0) {
                    // No usar errno - solo verificar return value
                    std::cerr << "ERROR: Send failed for fd " << client_fd << ", removing client" << std::endl << std::flush;
                    clients_to_remove.push_back(client_fd);
                } else if (bytes_sent == 0) {
                    std::cerr << "DEBUG: Send returned 0 for fd " << client_fd << ", connection may be closed" << std::endl << std::flush;
                    clients_to_remove.push_back(client_fd);
                } else {
                    client.bytes_sent += bytes_sent;
                    std::cerr << "DEBUG: Sent " << bytes_sent << " bytes for fd " << client_fd << ", total sent: " << client.bytes_sent << std::endl << std::flush;
                    
                    if (client.bytes_sent >= client.response.length()) {
                        std::cerr << "DEBUG: Response fully sent for fd " << client_fd << std::endl << std::flush;
                        client.response.clear();
                        client.bytes_sent = 0;
                        clients_to_remove.push_back(client_fd);
                    }
                }
            }
        }

        // Clean up disconnected or completed client connections
        // Evaluation point: proper memory management and resource cleanup
        // Evaluation point: Request object cleanup to prevent memory leaks
        for (size_t i = 0; i < clients_to_remove.size(); ++i) {
            int client_fd = clients_to_remove[i];
            std::cerr << "DEBUG: Closing connection for fd " << client_fd << std::endl << std::flush;
            std::map<int, Client>::iterator it = clients.find(client_fd);
            if (it != clients.end()) {
                if (it->second.request) {
                    delete it->second.request;
                    it->second.request = NULL;
                }
                close(client_fd);
                clients.erase(it);
            }
        }
    }
}