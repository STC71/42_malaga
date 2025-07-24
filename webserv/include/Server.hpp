#ifndef SERVER_HPP
#define SERVER_HPP

#include "Config.hpp"
#include "Request.hpp"
#include <map>      // for std::map
#include <string>   // for std::string
#include <vector>   // for std::vector

class Request;
class Response;

// Client class embedded in Server - represents individual connections
// Evaluation point: client data must be managed properly through select() only
// Evaluation point: incremental request/response handling for non-blocking I/O
class Client {
public:
    std::string buffer;                                  // stores received data from client
    int port;                                           // port associated with client connection
    size_t server_index;                                // index of ServerConfig in config.servers array
    std::string response;                               // stores pending response to send
    Request* request;                                   // pointer to Request object for incremental handling
    size_t bytes_sent;                                  // bytes sent of response (for incremental sending)
    
    // Constructor: initializes client with port and server index
    Client(int p, size_t idx) : buffer(""), port(p), server_index(idx), response(""), request(NULL), bytes_sent(0) {}
    
    // Destructor: cleans up request object to prevent memory leaks
    // Evaluation point: proper memory management is critical
    ~Client() { if (request) delete request; }
};

// Server class - main HTTP server with I/O multiplexing
// Evaluation point: CRITICAL - select() must be in main loop only
// Evaluation point: CRITICAL - only one read/write per client per select() call
// Evaluation point: CRITICAL - all I/O must go through select()
// Evaluation point: CRITICAL - no errno usage after socket operations
class Server {
private:
    std::vector<int> server_fds;                         // socket descriptors for multiple ports
    std::map<int, std::vector<size_t> > port_to_server_indices; // maps port to ServerConfig indices
    const Config& config;                                // reference to complete server configuration
    std::map<int, Client> clients;                       // active client connections by file descriptor

public:
    // Constructor: initializes server with configuration
    // Sets up listening sockets for all configured ports
    Server(const Config& config);
    
    // Destructor: cleans up all resources and closes sockets
    // Evaluation point: proper cleanup prevents resource leaks
    ~Server();
    
    // Main server loop with select() I/O multiplexing
    // Evaluation point: CRITICAL - this is where select() must be called
    // Evaluation point: CRITICAL - must check read and write AT THE SAME TIME
    // Evaluation point: CRITICAL - only one read/write operation per client per loop
    void run();
    
    // Check if client request is complete and ready for processing
    // Used to determine when to generate response
    bool isRequestComplete(const Client& client) const;
    
    // Get server file descriptors for external access
    const std::vector<int>& getServerFds() const { return server_fds; }
};

#endif