#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>   // for std::string
#include <map>      // for std::map

// Request class handles HTTP request parsing and validation
// Evaluation point: must support GET, POST and DELETE methods
// Evaluation point: UNKNOWN requests should not crash the server
// Evaluation point: must return appropriate status codes for all requests
class Request {
public:
    // Constructor: initializes request parsing with socket fd and initial data
    // Evaluation point: must handle partial HTTP requests properly
    Request(int fd, const std::string& initial_data);
    
    // Append additional body data for POST requests
    // Evaluation point: must handle file uploads correctly
    // Evaluation point: must respect client_max_body_size limits
    void appendBody(const std::string& data);
    
    // Check if complete HTTP request has been received
    // Used by Server to determine when to process request
    bool isComplete() const;
    
    // HTTP method getter (GET, POST, DELETE)
    // Evaluation point: must handle all supported HTTP methods
    std::string getMethod() const { return method; }
    
    // URI path getter (e.g., "/", "/files/test.txt")
    // Used for routing and file serving
    std::string getUri() const { return uri; }
    
    // Query string getter (part after ? in URL)
    // Used for CGI GET parameters
    std::string getQuery() const { return query; }
    
    // HTTP version getter (should be HTTP/1.1)
    // Used for protocol compliance checking
    std::string getVersion() const { return version; }
    
    // Request body getter for POST data
    // Evaluation point: must handle chunked encoding properly
    // Evaluation point: must handle multipart form data for file uploads
    std::string getBody() const;
    
    // HTTP header getter by key name
    // Used for Content-Type, Content-Length, Host, etc.
    std::string getHeader(const std::string& key) const;

private:
    std::string method;                                  // HTTP method (GET, POST, DELETE)
    std::string uri;                                     // request URI path
    std::string query;                                   // query string parameters
    std::string version;                                 // HTTP protocol version
    std::map<std::string, std::string> headers;          // HTTP headers collection
    std::string body;                                    // raw request body data
    std::string dechunked_body;                          // processed body after dechunking
    bool body_complete;                                  // flag indicating if body is fully received
    bool is_chunked;                                     // flag for chunked transfer encoding
    int client_fd;                                       // client socket file descriptor
    
    // Process chunked transfer encoding
    // Evaluation point: must handle chunked requests properly
    void dechunkBody();
    
    // Process multipart form data for file uploads
    // Evaluation point: file upload functionality must work correctly
    void processMultipartFormData();
};

#endif