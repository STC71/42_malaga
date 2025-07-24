#ifndef CGI_HPP
#define CGI_HPP

#include "Request.hpp"
#include "Config.hpp"
#include <string>   // for std::string
#include <utility>  // for std::pair - C++98 compatible

// CGI class handles script execution for dynamic content
// Evaluation point: CGI should work with GET and POST methods
// Evaluation point: CGI should run in correct directory for relative paths
// Evaluation point: Error handling must prevent server crashes
class CGI {
private:
    const Request& request;        // HTTP request data for CGI environment
    const LocationConfig& location; // Location config for CGI settings
    const ServerConfig& config;    // Server config for CGI environment
    int server_port;              // Port number for SERVER_PORT variable

public:
    // Constructor: prepares CGI execution context
    // Takes request, location config, server config and port
    CGI(const Request& req, const LocationConfig& loc, const ServerConfig& cfg, int port);
    
    // Main execution function for CGI scripts
    // Returns pair: <output_content, exit_code>
    // Evaluation point: must handle script errors without crashing server
    // Evaluation point: must work with both GET and POST methods
    // Evaluation point: must set proper CGI environment variables
    std::pair<std::string, int> execute(const std::string& script_path);
};

#endif