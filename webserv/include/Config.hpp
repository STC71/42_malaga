#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>   // for std::string
#include <vector>   // for std::vector
#include <map>     // for std::map

// LocationConfig struct defines specific route configurations
// Evaluation point: different routes must support different methods (GET, POST, DELETE)
// Evaluation point: CGI must work properly with correct interpreters
// Evaluation point: upload functionality must work in designated locations
struct LocationConfig {
    std::string path;                                    // route path (e.g., "/", "/cgi-bin/")
    std::string root;                                    // document root override for this location
    bool directory_listing;                              // evaluation point: directory listing must be configurable
    std::map<std::string, std::string> cgi_paths;        // extension -> interpreter mapping for CGI scripts
    std::vector<std::string> methods;                    // evaluation point: method restrictions per location
    std::string upload_path;                             // evaluation point: file upload destination directory
    std::string index;                                   // default file for directory requests
    std::string redirect;                                // redirection URL if configured
    size_t client_max_body_size;                         // evaluation point: body size limits per location

    // Constructor: sets safe defaults for location configuration
    LocationConfig() : directory_listing(false), index(""), redirect(""), client_max_body_size(1048576) {}
};

// ServerConfig struct defines virtual host configurations  
// Evaluation point: multiple servers with different ports must work
// Evaluation point: multiple servers with different hostnames must work
// Evaluation point: custom error pages must be served correctly
struct ServerConfig {
    std::vector<int> ports;                              // evaluation point: multiple ports per server support
    std::string server_name;                             // evaluation point: hostname-based virtual hosting
    std::string root;                                    // document root directory
    std::string index;                                   // default index file (e.g., "index.html")
    std::map<int, std::string> error_pages;              // evaluation point: custom error pages by status code
    std::vector<LocationConfig> locations;               // location-specific configurations
    size_t client_max_body_size;                         // evaluation point: request body size limit

    // Constructor: sets default body size limit (1MB)
    ServerConfig() : client_max_body_size(1048576) {}
};

// Config class handles configuration file parsing
// Evaluation point: configuration must support multiple servers
// Evaluation point: configuration syntax must be robust and error-free
class Config {
private:
    std::vector<ServerConfig> servers;                   // list of all configured virtual hosts

public:
    // Constructor: initializes empty configuration
    Config();
    
    // Load configuration from file
    // Evaluation point: must parse Nginx-like syntax correctly
    // Evaluation point: must handle configuration errors gracefully
    void load(const std::string& filename);
    
    // Get all configured servers
    // Used by Server class to set up listening sockets
    const std::vector<ServerConfig>& getServers() const { return servers; }
    
    // Utility function for string processing
    // Removes whitespace from configuration lines
    std::string trim(const std::string& str);
};

#endif