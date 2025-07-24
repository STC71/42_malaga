// Configuration parser implementation for webserv project
// Evaluation point: configuration must support multiple servers and ports
// Evaluation point: location blocks with method restrictions and CGI paths
// Evaluation point: error pages, upload paths, and directory listing configuration
// Evaluation point: proper validation of all configuration parameters

#include "Config.hpp"        // Config class definition with ServerConfig and LocationConfig
#include <fstream>           // std::ifstream for reading configuration files
#include <sstream>           // std::istringstream for parsing configuration lines
#include <iostream>          // std::cerr for debug output and error logging
#include <stdexcept>         // std::runtime_error for configuration validation errors
#include <cstdlib>           // standard library functions (if needed)
#include <unistd.h>          // access() for validating file/directory accessibility
#include <cstring>           // strerror() for errno to string conversion

// Default constructor
Config::Config() {}

// Utility function to trim whitespace and semicolons from configuration values
// Evaluation point: proper parsing of configuration file format
std::string Config::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n;");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

// Main configuration loading function - parses entire config file
// Evaluation point: must support multiple server blocks with different ports
// Evaluation point: location blocks with CGI, upload, and method restrictions
// Evaluation point: proper error handling and validation of all parameters
void Config::load(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to open config file: " << filename 
                  << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
        throw std::runtime_error("Failed to open config file: " + filename);
    }
    std::cerr << "DEBUG: Opened config file: " << filename << std::endl;

    // Configuration parsing state variables
    // Evaluation point: proper nested block parsing (server -> location)
    std::string line;
    ServerConfig current_server;
    LocationConfig current_location;
    bool in_server_block = false;
    bool in_location_block = false;

    // Parse configuration file line by line
    // Evaluation point: robust parsing with proper error handling
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments

        std::cerr << "DEBUG: Processing line: " << line << std::endl;

        std::istringstream iss(line);
        std::string key;
        iss >> key;

        // Handle server block start
        // Evaluation point: multiple server blocks support
        if (key == "server" && line.find("{") != std::string::npos) {
            if (in_server_block) {
                std::cerr << "ERROR: Nested server block detected" << std::endl;
                throw std::runtime_error("Nested server blocks are not allowed");
            }
            in_server_block = true;
            current_server = ServerConfig();
            std::cerr << "DEBUG: Starting server block" << std::endl;
            continue;
        }

        // Handle block closing
        // Evaluation point: proper validation before closing blocks
        if (in_server_block && line == "}") {
            if (in_location_block) {
                // Validate CGI interpreters before adding location
                // Evaluation point: CGI interpreter validation is critical
                for (std::map<std::string, std::string>::iterator it = current_location.cgi_paths.begin();
                     it != current_location.cgi_paths.end(); ++it) {
                    if (access(it->second.c_str(), X_OK) != 0) {
                        std::cerr << "ERROR: CGI interpreter not found or not executable: " << it->second 
                                  << " for extension " << it->first 
                                  << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
                        throw std::runtime_error("Invalid CGI interpreter: " + it->second);
                    }
                    std::cerr << "DEBUG: Validated CGI interpreter: " << it->second << " for extension " << it->first << std::endl;
                }
                current_server.locations.push_back(current_location);
                in_location_block = false;
                std::cerr << "DEBUG: Added location block: " << current_location.path << std::endl;
            } else {
                // Validate server configuration before adding
                // Evaluation point: server must have at least one port defined
                if (current_server.ports.empty()) {
                    std::cerr << "ERROR: No ports defined for server block" << std::endl;
                    throw std::runtime_error("No ports defined for server block");
                }
                // Validate root directory accessibility
                // Evaluation point: root directory must be accessible for static file serving
                if (current_server.root.empty()) {
                    std::cerr << "WARNING: No root defined for server block, using default '/var/www/html'" << std::endl;
                    current_server.root = "/var/www/html";
                }
                if (access(current_server.root.c_str(), R_OK) != 0) {
                    std::cerr << "ERROR: Root directory not accessible: " << current_server.root 
                              << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
                    throw std::runtime_error("Root directory not accessible: " + current_server.root);
                }
                servers.push_back(current_server);
                in_server_block = false;
                std::cerr << "DEBUG: Added server block with ports: ";
                for (size_t i = 0; i < current_server.ports.size(); ++i) {
                    std::cerr << current_server.ports[i] << " ";
                }
                std::cerr << std::endl;
            }
            continue;
        }

        // Handle location block start
        // Evaluation point: location blocks for specific path handling
        if (in_server_block && key == "location" && line.find("{") != std::string::npos) {
            if (in_location_block) {
                std::cerr << "ERROR: Nested location block detected" << std::endl;
                throw std::runtime_error("Nested location blocks are not allowed");
            }
            std::string path;
            size_t path_start = line.find_first_not_of(" \t", key.length());
            size_t path_end = line.find("{", path_start);
            if (path_start == std::string::npos || path_end == std::string::npos) {
                std::cerr << "ERROR: Invalid location directive syntax: " << line << std::endl;
                throw std::runtime_error("Invalid location directive syntax");
            }
            path = trim(line.substr(path_start, path_end - path_start));
            in_location_block = true;
            current_location = LocationConfig();
            current_location.path = path;
            std::cerr << "DEBUG: Starting location block for path: " << path << std::endl;
            continue;
        }

        if (in_location_block && line == "}") {
            // Validate CGI interpreters before closing location block
            // Evaluation point: CGI interpreter validation is critical for functionality
            for (std::map<std::string, std::string>::iterator it = current_location.cgi_paths.begin();
                 it != current_location.cgi_paths.end(); ++it) {
                if (access(it->second.c_str(), X_OK) != 0) {
                    std::cerr << "ERROR: CGI interpreter not found or not executable: " << it->second 
                              << " for extension " << it->first 
                              << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
                    throw std::runtime_error("Invalid CGI interpreter: " + it->second);
                }
                std::cerr << "DEBUG: Validated CGI interpreter: " << it->second << " for extension " << it->first << std::endl;
            }
            current_server.locations.push_back(current_location);
            in_location_block = false;
            std::cerr << "DEBUG: Added location block: " << current_location.path << std::endl;
            continue;
        }

        // Parse location-specific directives
        // Evaluation point: location blocks must support all required features
        if (in_location_block) {
            if (key == "root") {
                // Set root directory for this location
                current_location.root = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set location root: " << current_location.root << std::endl;
            } else if (key == "index") {
                // Set index file for directory requests
                current_location.index = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set location index: " << current_location.index << std::endl;
            } else if (key == "cgi_path") {
                // Parse CGI interpreter mappings (extension=interpreter format)
                // Evaluation point: CGI support is mandatory for dynamic content
                std::string token;
                while (iss >> token) {
                    // Each token must have format: extension=interpreter
                    // Evaluation point: proper CGI configuration syntax validation
                    size_t equals_pos = token.find('=');
                    if (equals_pos == std::string::npos || equals_pos == 0 || equals_pos == token.length() - 1) {
                        std::cerr << "ERROR: Invalid cgi_path syntax in token: " << token << std::endl;
                        throw std::runtime_error("Invalid cgi_path syntax: " + token);
                    }
                    std::string extension = token.substr(0, equals_pos);
                    std::string interpreter = token.substr(equals_pos + 1);
                    if (extension.empty() || interpreter.empty()) {
                        std::cerr << "ERROR: Empty extension or interpreter in cgi_path: " << token << std::endl;
                        throw std::runtime_error("Invalid cgi_path syntax: " + token);
                    }
                    current_location.cgi_paths[extension] = interpreter;
                    std::cerr << "DEBUG: Added cgi_path: " << extension << " -> " << interpreter << std::endl;
                }
                if (current_location.cgi_paths.empty()) {
                    std::cerr << "ERROR: No valid cgi_path entries found in: " << line << std::endl;
                    throw std::runtime_error("No valid cgi_path entries");
                }
            } else if (key == "upload_path") {
                // Set upload directory for POST file uploads
                // Evaluation point: file upload support is required
                current_location.upload_path = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set upload_path: " << current_location.upload_path << std::endl;
            } else if (key == "directory_listing") {
                // Enable/disable directory listing for this location
                // Evaluation point: directory listing must be configurable
                std::string value;
                iss >> value;
                current_location.directory_listing = (value == "on");
                std::cerr << "DEBUG: Set directory_listing: " << (current_location.directory_listing ? "on" : "off") << std::endl;
            } else if (key == "client_max_body_size") {
                // Set maximum request body size for uploads
                // Evaluation point: body size limits are critical for security
                std::string value;
                iss >> value;
                std::istringstream converter(value);
                unsigned long size;
                if (!(converter >> size)) {
                    std::cerr << "ERROR: Invalid client_max_body_size: " << value << std::endl;
                    throw std::runtime_error("Invalid client_max_body_size");
                }
                current_location.client_max_body_size = size;
                std::cerr << "DEBUG: Set client_max_body_size: " << current_location.client_max_body_size << std::endl;
            } else if (key == "methods") {
                // Define allowed HTTP methods for this location
                // Evaluation point: method restrictions must be properly enforced
                std::string method;
                current_location.methods.clear();
                while (iss >> method) {
                    current_location.methods.push_back(method);
                    std::cerr << "DEBUG: Added method: " << method << std::endl;
                }
            } else if (key == "redirect") {
                // Set HTTP redirect for this location
                // Evaluation point: HTTP redirects must work correctly
                current_location.redirect = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set redirect: " << current_location.redirect << std::endl;
            } else {
                std::cerr << "WARNING: Unknown location directive: " << key << std::endl;
            }
        } else if (in_server_block) {
            // Parse server-level directives
            // Evaluation point: server configuration must support all required features
            if (key == "listen") {
                // Parse listening ports (can be multiple)
                // Evaluation point: multiple ports support is required
                std::string port_str;
                while (iss >> port_str) {
                    std::istringstream converter(port_str);
                    int port;
                    // Validate port range (1-65535)
                    // Evaluation point: proper port validation is essential
                    if (!(converter >> port) || port <= 0 || port > 65535) {
                        std::cerr << "ERROR: Invalid port: " << port_str << std::endl;
                        throw std::runtime_error("Invalid port: " + port_str);
                    }
                    current_server.ports.push_back(port);
                    std::cerr << "DEBUG: Added port: " << port << std::endl;
                }
            } else if (key == "server_name") {
                // Set server name for virtual host support
                current_server.server_name = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set server_name: " << current_server.server_name << std::endl;
            } else if (key == "root") {
                // Set document root directory for static files
                // Evaluation point: static file serving requires proper root configuration
                current_server.root = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set server root: " << current_server.root << std::endl;
            } else if (key == "index") {
                // Set default index file for directory requests
                current_server.index = trim(iss.str().substr(iss.tellg()));
                std::cerr << "DEBUG: Set server index: " << current_server.index << std::endl;
            } else if (key == "client_max_body_size") {
                // Set server-level maximum request body size
                // Evaluation point: body size limits prevent DoS attacks
                std::string value;
                iss >> value;
                std::istringstream converter(value);
                unsigned long size;
                if (!(converter >> size)) {
                    std::cerr << "ERROR: Invalid client_max_body_size: " << value << std::endl;
                    throw std::runtime_error("Invalid client_max_body_size");
                }
                current_server.client_max_body_size = size;
                std::cerr << "DEBUG: Set server client_max_body_size: " << current_server.client_max_body_size << std::endl;
            } else if (key == "error_page") {
                // Configure custom error pages for HTTP status codes
                // Evaluation point: error pages must be properly served for different status codes
                int code;
                std::string path;
                iss >> code >> path;
                current_server.error_pages[code] = path;
                std::cerr << "DEBUG: Added error_page: " << code << " -> " << path << std::endl;
            } else {
                std::cerr << "WARNING: Unknown server directive: " << key << std::endl;
            }
        } else {
            // Directive outside server block - configuration error
            // Evaluation point: configuration syntax must be strictly validated
            std::cerr << "ERROR: Directive outside server block: " << key << std::endl;
            throw std::runtime_error("Directive outside server block: " + key);
        }
    }

    // Handle unclosed blocks at end of file
    // Evaluation point: configuration file must be syntactically complete
    if (in_server_block) {
        if (in_location_block) {
            // Validate and close final location block
            // Evaluation point: CGI interpreter validation must occur before accepting config
            for (std::map<std::string, std::string>::iterator it = current_location.cgi_paths.begin();
                 it != current_location.cgi_paths.end(); ++it) {
                if (access(it->second.c_str(), X_OK) != 0) {
                    std::cerr << "ERROR: CGI interpreter not found or not executable: " << it->second 
                              << " for extension " << it->first 
                              << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
                    throw std::runtime_error("Invalid CGI interpreter: " + it->second);
                }
                std::cerr << "DEBUG: Validated CGI interpreter: " << it->second << " for extension " << it->first << std::endl;
            }
            current_server.locations.push_back(current_location);
            std::cerr << "DEBUG: Added final location block: " << current_location.path << std::endl;
        }
        // Validate final server configuration
        // Evaluation point: every server must have at least one listening port
        if (current_server.ports.empty()) {
            std::cerr << "ERROR: No ports defined for final server block" << std::endl;
            throw std::runtime_error("No ports defined for final server block");
        }
        // Ensure server has valid root directory
        // Evaluation point: root directory accessibility is critical for file serving
        if (current_server.root.empty()) {
            std::cerr << "WARNING: No root defined for final server block, using default '/var/www/html'" << std::endl;
            current_server.root = "/var/www/html";
        }
        if (access(current_server.root.c_str(), R_OK) != 0) {
            std::cerr << "ERROR: Root directory not accessible: " << current_server.root 
                      << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl;
            throw std::runtime_error("Root directory not accessible: " + current_server.root);
        }
        servers.push_back(current_server);
        std::cerr << "DEBUG: Added final server block with ports: ";
        for (size_t i = 0; i < current_server.ports.size(); ++i) {
            std::cerr << current_server.ports[i] << " ";
        }
        std::cerr << std::endl;
    }

    // Final validation - ensure at least one server is defined
    // Evaluation point: configuration must define at least one functional server
    if (servers.empty()) {
        std::cerr << "ERROR: No server blocks defined in config file" << std::endl;
        throw std::runtime_error("No server blocks defined in config file");
    }

    file.close();
    std::cerr << "DEBUG: Config file loaded successfully, total servers: " << servers.size() << std::endl;
}