#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Request.hpp"
#include "Config.hpp"
#include <string>   // for std::string
#include <map>      // for std::map

// Response class generates HTTP responses for client requests
// Evaluation point: must return correct HTTP status codes for all situations
// Evaluation point: must serve static files properly
// Evaluation point: must handle GET, POST and DELETE methods correctly
// Evaluation point: must serve custom error pages when configured
class Response {
public:
    // Constructor: initializes response generation with request, config and port
    // Evaluation point: must use correct server config based on port/hostname
    Response(const Request& req, const ServerConfig& config, int port);
    
    // Main request handler: generates complete HTTP response
    // Evaluation point: must return appropriate status codes (200, 404, 405, etc.)
    // Evaluation point: must handle unknown methods without crashing
    std::string handleRequest();

private:
    const Request& request;                              // HTTP request being processed
    const ServerConfig& config;                          // server configuration for this virtual host
    int port;                                            // client connection port for virtual host selection
    int status_code;                                     // HTTP response status code to be returned

    // Utility: remove whitespace from strings
    std::string trim(const std::string& str) const;
    
    // Find matching location config for URI path
    // Evaluation point: must apply correct location-specific settings
    const LocationConfig* findLocation(const std::string& uri) const;
    
    // File system checks for static file serving
    // Evaluation point: must handle file existence properly
    bool fileExists(const std::string& path) const;
    
    // Directory detection for directory listing
    // Evaluation point: directory listing must work when enabled
    bool isDirectory(const std::string& path) const;
    
    // MIME type detection for proper Content-Type headers
    // Evaluation point: must serve files with correct Content-Type
    std::string getMimeType(const std::string& path) const;
    
    // Generate HTML directory listing
    // Evaluation point: directory listing feature must work properly
    std::string generateDirectoryListing(const std::string& path, const std::string& uri) const;
    
    // Read file content for static file serving
    // Evaluation point: must serve static files correctly
    std::string readFile(const std::string& path) const;
    
    // Handle file upload via POST method
    // Evaluation point: file upload functionality must work correctly
    // Evaluation point: must save uploaded files to correct directory
    std::string handleUpload(const std::string& upload_path);
    
    // Resolve final file path using location configuration
    // Evaluation point: must respect location-specific root directories
    std::string resolvePath(const LocationConfig* location) const;
};

#endif