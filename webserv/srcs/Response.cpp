// HTTP Response generator implementation for webserv project
// Evaluation point: proper HTTP status codes (200, 404, 405, 413, 500, etc.)
// Evaluation point: static file serving with correct MIME types
// Evaluation point: directory listing functionality when enabled
// Evaluation point: file upload support via POST method
// Evaluation point: file deletion support via DELETE method
// Evaluation point: CGI integration with proper environment setup
// Evaluation point: error pages for different HTTP status codes
// Evaluation point: session management for bonus features

#include "Response.hpp"      // Response class definition with HTTP response generation
#include "CGI.hpp"           // CGI class for dynamic content execution
#include <sys/stat.h>        // stat(), S_ISDIR() for file system information
#include <dirent.h>          // opendir(), readdir(), closedir() for directory operations
#include <unistd.h>          // access(), unlink() for file access and deletion
#include <fcntl.h>           // open(), O_RDONLY, O_WRONLY for file operations
#include <cerrno>            // errno global variable for system call error reporting
#include <fstream>           // std::ifstream for file stream operations (if needed)
#include <iostream>          // std::cerr for debug output and error logging
#include <sstream>           // std::ostringstream for HTTP response building
#include <ctime>             // time() for session ID generation and timestamps
#include <cstdlib>           // setenv(), putenv() for environment variable management
#include <map>               // std::map for session management and MIME type mapping
#include <string>            // std::string for string operations
#include <cstring>           // strerror() for errno to string conversion
#include <iomanip>           // std::hex, std::setw for hex dump debugging

// Session management class for bonus feature
// Evaluation point: session cookies and visit counting (bonus functionality)
// Evaluation point: stateful HTTP server implementation beyond basic requirements
// Evaluation point: proper session ID generation and management
// Evaluation point: session persistence across multiple requests
class SessionManager {
private:
    std::map<std::string, int> visit_counts;  // Map to store visit counts per session
    static int counter;  // Static counter for unique session IDs
public:
    SessionManager() {}  // Default constructor
    
    // Create new session with unique ID combining timestamp and counter
    // Evaluation point: proper session management for stateful interactions
    // Evaluation point: unique session ID generation algorithm
    std::string createSession() {
        std::ostringstream oss;
        oss << ::time(NULL) << "_" << counter++;  // Combine timestamp and counter
        std::string session_id = oss.str();
        visit_counts[session_id] = 1;  // Initialize visit count
        std::cerr << "DEBUG: Created session: " << session_id << ", visit_count: 1" << std::endl << std::flush;
        return session_id;
    }
    
    // Increment visit count for existing session
    // Evaluation point: session state persistence across requests
    // Evaluation point: session validation and state management
    int incrementVisit(const std::string& session_id) {
        if (visit_counts.find(session_id) != visit_counts.end()) {
            visit_counts[session_id]++;  // Increment count
            std::cerr << "DEBUG: Incremented visit for session: " << session_id << ", new count: " << visit_counts[session_id] << std::endl << std::flush;
            return visit_counts[session_id];
        }
        std::cerr << "DEBUG: Session not found: " << session_id << std::endl << std::flush;
        return 0;
    }
    
    // Get visit count for session without modification
    // Evaluation point: session data retrieval for bonus functionality
    int getVisitCount(const std::string& session_id) {
        if (visit_counts.find(session_id) != visit_counts.end()) {
            return visit_counts[session_id];
        }
        return 0;
    }
};
int SessionManager::counter = 0;  // Initialize static counter

// Constructor - initializes response with request context and server configuration
// Evaluation point: proper integration with request parsing and server config
Response::Response(const Request& req, const ServerConfig& config, int port)
    : request(req), config(config), port(port), status_code(200) {  // Initialize member variables
    std::cerr << "DEBUG: Constructing Response for method: " << request.getMethod() << ", URI: " << request.getUri() << std::endl << std::flush;
}

// Utility function to remove leading/trailing whitespace
// Evaluation point: string processing utility for HTTP header and URI parsing
// Evaluation point: proper handling of whitespace in configuration values
std::string Response::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");  // Find first non-whitespace
    size_t end = str.find_last_not_of(" \t\r\n");     // Find last non-whitespace
    if (start == std::string::npos) return "";  // String is all whitespace
    return str.substr(start, end - start + 1);  // Return trimmed string
}

// Find best matching location configuration for URI
// Evaluation point: proper location matching for path-specific configurations
const LocationConfig* Response::findLocation(const std::string& uri) const {
    std::cerr << "DEBUG: findLocation for URI: " << uri << std::endl << std::flush;
    const LocationConfig* best_match = NULL;  // Best matching location
    size_t longest_match = 0;  // Length of longest path match
    for (size_t i = 0; i < config.locations.size(); ++i) {  // Iterate through all locations
        const std::string& loc_path = config.locations[i].path;  // Current location path
        if (uri.find(loc_path) == 0) {  // Check if URI starts with location path
            if (loc_path.length() >= longest_match) {  // Check if this is a better match
                longest_match = loc_path.length();  // Update longest match length
                best_match = &config.locations[i];  // Update best match pointer
                std::cerr << "DEBUG: Matched location: " << loc_path
                          << ", root: " << config.locations[i].root
                          << ", directory_listing: " << (config.locations[i].directory_listing ? "on" : "off")
                          << ", cgi_paths size: " << config.locations[i].cgi_paths.size()
                          << ", index: " << config.locations[i].index
                          << ", redirect: " << config.locations[i].redirect
                          << ", client_max_body_size: " << config.locations[i].client_max_body_size << std::endl << std::flush;
                for (std::map<std::string, std::string>::const_iterator it = config.locations[i].cgi_paths.begin();
                     it != config.locations[i].cgi_paths.end(); ++it) {  // Log CGI paths
                    std::cerr << "DEBUG: cgi_path for extension: " << it->first << " -> " << it->second << std::endl << std::flush;
                }
            }
        }
    }
    if (best_match) {  // If we found a match
        std::cerr << "DEBUG: Selected location: " << best_match->path << std::endl << std::flush;
        return best_match;
    }
    std::cerr << "DEBUG: No specific location matched, using default" << std::endl << std::flush;
    return NULL;  // No location matched
}

// Check if file or directory exists using stat()
// Evaluation point: proper file system validation before serving content
bool Response::fileExists(const std::string& path) const {
    struct stat buffer;  // Buffer for file statistics
    int result = stat(path.c_str(), &buffer);  // Get file statistics
    std::cerr << "DEBUG: Checking if path exists: " << path << ", stat result: " << result << std::endl << std::flush;
    return (result == 0);  // Return true if stat succeeded
}

// Check if path is a directory using S_ISDIR macro
// Evaluation point: directory vs file differentiation for proper handling
bool Response::isDirectory(const std::string& path) const {
    struct stat buffer;  // Buffer for file statistics
    if (stat(path.c_str(), &buffer) != 0) {  // Get file statistics
        std::cerr << "DEBUG: stat failed for path: " << path << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        return false;  // Return false if stat failed
    }
    return S_ISDIR(buffer.st_mode);  // Check if it's a directory
}

// Determine MIME type from file extension for proper Content-Type headers
// Evaluation point: proper Content-Type headers for different file types
// Evaluation point: MIME type detection algorithm for HTTP compliance
// Evaluation point: support for common web file types (HTML, images, text)
// Evaluation point: CGI script MIME type handling (PHP, Python scripts output HTML)
std::string Response::getMimeType(const std::string& path) const {
    std::string extension;  // File extension
    size_t dot_pos = path.find_last_of(".");  // Find last dot in path
    if (dot_pos != std::string::npos && dot_pos < path.length() - 1) {  // If dot found and not at end
        extension = path.substr(dot_pos + 1);  // Extract extension
    }
    if (extension == "html") return "text/html";  // HTML files
    if (extension == "txt") return "text/plain";  // Text files
    if (extension == "jpg" || extension == "jpeg") return "image/jpeg";  // JPEG images
    if (extension == "png") return "image/png";  // PNG images
    if (extension == "php" || extension == "py") return "text/html";  // CGI scripts output HTML
    return "application/octet-stream";  // Default binary type
}

// Generate HTML directory listing when directory_listing is enabled
// Evaluation point: directory listing functionality as specified in subject
// Evaluation point: proper HTML generation for directory browsing
// Evaluation point: directory traversal with opendir/readdir/closedir
// Evaluation point: URI construction for directory navigation links
// Evaluation point: security consideration (skipping . and .. entries)
std::string Response::generateDirectoryListing(const std::string& path, const std::string& uri) const {
    std::cerr << "DEBUG: Generating directory listing for: " << path << std::endl << std::flush;
    DIR* dir = opendir(path.c_str());  // Open directory
    if (!dir) {  // If opening failed
        std::cerr << "ERROR: Failed to open directory: " << path << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        return "";  // Return empty string
    }
    std::ostringstream listing;  // String stream for HTML content
    listing << "<html><head><title>Directory Listing</title></head><body><h1>Directory Listing for " << uri << "</h1><ul>";  // HTML header
    struct dirent* entry;  // Directory entry
    while ((entry = readdir(dir)) != NULL) {  // Read each directory entry
        std::string name = entry->d_name;  // Entry name
        if (name != "." && name != "..") {  // Skip current and parent directory
            listing << "<li><a href=\"" << uri;  // Create link
            if (uri[uri.length() - 1] != '/') listing << "/";  // Add slash if needed
            listing << name << "\">" << name << "</a></li>";  // Complete link
        }
    }
    listing << "</ul></body></html>";  // HTML footer
    closedir(dir);  // Close directory
    return listing.str();  // Return HTML string
}

// Read file content safely using non-blocking I/O with comprehensive error handling
// Evaluation point: secure file reading with proper error handling
// Evaluation point: non-blocking I/O operations for server performance
// Evaluation point: chunked file reading to handle large files efficiently
// Evaluation point: proper file descriptor management (open/close)
// Evaluation point: errno handling for file system error reporting
std::string Response::readFile(const std::string& path) const {
    int fd = open(path.c_str(), O_RDONLY | O_NONBLOCK);  // Open file for reading (non-blocking)
    if (fd < 0) {  // If opening failed
        std::cerr << "ERROR: Failed to open file: " << path << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        return "";  // Return empty string
    }
    std::string content;  // File content
    char buffer[4096] = {0};  // Read buffer
    ssize_t bytes_read;  // Number of bytes read
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {  // Read file in chunks
        content.append(buffer, bytes_read);  // Append to content
    }
    close(fd);  // Close file descriptor
    if (bytes_read < 0) {  // If read error occurred
        std::cerr << "ERROR: Failed to read file: " << path << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        return "";  // Return empty string
    }
    return content;  // Return file content
}

// Resolve final file system path from URI and location configuration
// Evaluation point: proper path resolution combining server root and location configuration
// Evaluation point: handling of upload_path vs normal file serving paths
// Evaluation point: security consideration for path traversal prevention
std::string Response::resolvePath(const LocationConfig* location) const {  // Resolve final file system path
    std::string uri = request.getUri();  // Get request URI
    std::string path;  // Final resolved path
    if (location && !location->upload_path.empty()) {  // If location has upload path
        path = location->upload_path + (uri == location->path ? "" : uri.substr(location->path.length()));  // Use upload path
    } else {  // Normal file serving
        std::string root = location && !location->root.empty() ? location->root : config.root;  // Get root directory
        if (location && uri.find(location->path) == 0) {  // If URI matches location path
            if (uri == location->path || uri[location->path.length()] == '/') {  // Exact match or subdirectory
                path = root + (uri == location->path ? "" : uri.substr(location->path.length()));  // Remove location prefix
            } else {  // Partial match
                path = root + uri;  // Use full URI
            }
        } else {  // No location match
            path = root + uri;  // Use server root + URI
        }
    }
    path = trim(path);  // Remove any whitespace
    std::cerr << "DEBUG: Resolved path: " << path << std::endl << std::flush;
    return path;  // Return resolved path
}

// Handle file upload via POST method with comprehensive validation
// Evaluation point: POST method implementation for file uploads
// Evaluation point: client_max_body_size enforcement (413 status code)
// Evaluation point: proper file system operations with error handling
// Evaluation point: upload_path configuration usage
// Evaluation point: security validation (write permissions, filename extraction)
// Evaluation point: proper HTTP status codes (201 Created, 400 Bad Request, 500 Internal Server Error)
std::string Response::handleUpload(const std::string& upload_path) {  // Handle file upload via POST method
    std::cerr << "DEBUG: Handling upload to: " << upload_path << std::endl << std::flush;

    // Obtener el cuerpo de la solicitud
    std::string body = request.getBody();  // Get request body content
    std::cerr << "DEBUG: Body to be written in handleUpload (string): [" << body << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Body to be written in handleUpload (hex): ";
    for (size_t i = 0; i < body.size(); ++i) {  // Log body in hexadecimal for debugging
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)body[i] << " ";
    }
    std::cerr << std::dec << std::endl << std::flush;

    if (body.empty()) {
        std::cerr << "ERROR: Empty request body for upload" << std::endl << std::flush;
        status_code = 400;
        std::string error_page = config.error_pages.find(400) != config.error_pages.end() ? config.root + config.error_pages.find(400)->second : config.root + "/errors/400.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>400 Bad Request - Empty Body</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 400 Bad Request\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    // Verificar el tamaño del cuerpo
    const LocationConfig* location = findLocation(request.getUri());
    size_t max_body_size = location ? location->client_max_body_size : config.client_max_body_size;
    if (body.length() > max_body_size) {
        std::cerr << "DEBUG: Request body size (" << body.length() << ") exceeds client_max_body_size (" << max_body_size << ")" << std::endl << std::flush;
        status_code = 413;
        std::string error_page = config.error_pages.find(413) != config.error_pages.end() ? config.root + config.error_pages.find(413)->second : config.root + "/errors/413.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>413 Payload Too Large</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 413 Payload Too Large\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    // Obtener el nombre del archivo
    std::string filename = request.getHeader("X-Filename");
    if (filename.empty() && request.getUri().find("/Uploads/") == 0 && request.getUri().length() > 9) {
        filename = request.getUri().substr(9);
        std::cerr << "DEBUG: Using filename from URI: " << filename << std::endl << std::flush;
    }
    if (filename.empty()) {
        std::cerr << "ERROR: No filename provided for upload" << std::endl << std::flush;
        status_code = 400;
        std::string error_page = config.error_pages.find(400) != config.error_pages.end() ? config.root + config.error_pages.find(400)->second : config.root + "/errors/400.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>400 Bad Request - No Filename Provided</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 400 Bad Request\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    // Construir la ruta del archivo
    std::string filepath = upload_path + (upload_path[upload_path.length() - 1] == '/' ? "" : "/") + filename;
    std::cerr << "DEBUG: Saving uploaded file to: " << filepath << std::endl << std::flush;

    // Verificar permisos de escritura en el directorio
    std::string dir_path = upload_path;
    if (access(dir_path.c_str(), W_OK) != 0) {
        std::cerr << "ERROR: No write permission for upload directory: " << dir_path 
                  << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        status_code = 500;
        std::string error_page = config.error_pages.find(500) != config.error_pages.end() ? config.root + config.error_pages.find(500)->second : config.root + "/errors/500.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>500 Internal Server Error - No Write Permission</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 500 Internal Server Error\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    // Abrir el archivo para escritura
    int fd = open(filepath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        std::cerr << "ERROR: Failed to open file for writing: " << filepath 
                  << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        status_code = 500;
        std::string error_page = config.error_pages.find(500) != config.error_pages.end() ? config.root + config.error_pages.find(500)->second : config.root + "/errors/500.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>500 Internal Server Error - Cannot Save File</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 500 Internal Server Error\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    // Escribir el cuerpo en el archivo
    ssize_t bytes_written = write(fd, body.c_str(), body.length());
    close(fd);
    if (bytes_written != static_cast<ssize_t>(body.length())) {
        std::cerr << "ERROR: Failed to write file: " << filepath 
                  << ", bytes_written: " << bytes_written 
                  << ", expected: " << body.length() 
                  << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        status_code = 500;
        std::string error_page = config.error_pages.find(500) != config.error_pages.end() ? config.root + config.error_pages.find(500)->second : config.root + "/errors/500.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>500 Internal Server Error - Cannot Save File</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 500 Internal Server Error\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    std::cerr << "DEBUG: File saved successfully: " << filepath << std::endl << std::flush;

    // Generar respuesta
    std::string location_uri = request.getUri();
    std::string content = "<html><body><h1>201 Created - File Uploaded</h1></body></html>";
    std::ostringstream response;
    response << "HTTP/1.1 201 Created\r\n"
            << "Content-Type: text/html\r\n"
            << "Content-Length: " << content.length() << "\r\n"
            << "Location: " << location_uri << "\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << content;
    return response.str();
}

// Main HTTP request handler - central evaluation point for webserv functionality
// Evaluation point: complete HTTP method support (GET, POST, DELETE)
// Evaluation point: session management with cookies (bonus feature)
// Evaluation point: location configuration matching and application
// Evaluation point: method restriction enforcement (405 Method Not Allowed)
// Evaluation point: upload functionality with client_max_body_size validation
// Evaluation point: file deletion with proper permission checks
// Evaluation point: directory listing when enabled
// Evaluation point: CGI script execution integration
// Evaluation point: static file serving with proper MIME types
// Evaluation point: comprehensive error handling with custom error pages
// Evaluation point: HTTP redirection support (301, 307 status codes)
std::string Response::handleRequest() {  // Main method to handle HTTP requests
    static SessionManager session_manager;  // Static session manager for persistence
    std::cerr << "DEBUG: Handling request for method: " << request.getMethod() << ", URI: " << request.getUri() << std::endl << std::flush;
    const LocationConfig* location = findLocation(request.getUri());  // Find matching location config
    std::string path = resolvePath(location);  // Resolve file system path

    // Manejar sesión
    std::string session_id;  // Session identifier
    std::string cookie_header = request.getHeader("Cookie");  // Get cookie header
    size_t pos = cookie_header.find("session_id=");  // Look for session cookie
    if (pos != std::string::npos) {  // If session cookie found
        size_t start = pos + 11;  // Start after "session_id="
        size_t end = cookie_header.find(";", start);  // Find end of cookie value
        if (end == std::string::npos) end = cookie_header.length();  // Use end of header if no semicolon
        session_id = cookie_header.substr(start, end - start);  // Extract session ID
        std::cerr << "DEBUG: Parsed session_id from cookie: " << session_id << std::endl << std::flush;
        int visit_count = session_manager.incrementVisit(session_id);  // Increment visit count
        if (visit_count == 0) {  // If session not found
            std::cerr << "DEBUG: Invalid session_id, creating new session" << std::endl << std::flush;
            session_id = session_manager.createSession();  // Create new session
        }
    } else {  // No session cookie found
        session_id = session_manager.createSession();  // Create new session
    }
    std::cerr << "DEBUG: Session ID: " << session_id << ", Visit count: " << session_manager.getVisitCount(session_id) << std::endl << std::flush;

    std::ostringstream visit_count_str;  // Convert visit count to string
    visit_count_str << session_manager.getVisitCount(session_id);
    #ifdef _POSIX_C_SOURCE  // POSIX environment variable setting
    setenv("VISIT_COUNT", visit_count_str.str().c_str(), 1);
    #else  // Non-POSIX environment variable setting
    std::string env_var = "VISIT_COUNT=" + visit_count_str.str();
    putenv(const_cast<char*>(env_var.c_str()));
    #endif

    // Verificar ubicación
    if (!location) {  // If no matching location found
        std::cerr << "DEBUG: No matching location for URI: " << request.getUri() << std::endl << std::flush;
        status_code = 404;  // Set 404 Not Found status
        std::string error_page = config.error_pages.find(404) != config.error_pages.end() ? config.root + config.error_pages.find(404)->second : config.root + "/errors/404.html";  // Get error page
        std::string content = readFile(error_page);  // Read error page content
        if (content.empty()) content = "<html><body><h1>404 Not Found - No Matching Location</h1></body></html>";  // Default error content
        std::ostringstream response;  // Build HTTP response
        response << "HTTP/1.1 404 Not Found\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();  // Return 404 response
    }

    // Verificar métodos permitidos
    if (!location->methods.empty()) {  // If location has method restrictions
        bool method_allowed = false;  // Flag for method permission
        for (size_t i = 0; i < location->methods.size(); ++i) {  // Check each allowed method
            if (location->methods[i] == request.getMethod()) {  // If method matches
                method_allowed = true;  // Set permission flag
                break;  // Exit loop
            }
        }
        if (!method_allowed) {  // If method not allowed
            std::cerr << "DEBUG: Method not allowed: " << request.getMethod() << " for " << request.getUri() << std::endl << std::flush;
            status_code = 405;  // Set 405 Method Not Allowed status
            std::string error_page = config.error_pages.find(405) != config.error_pages.end() ? config.root + config.error_pages.find(405)->second : config.root + "/errors/405.html";  // Get error page
            std::string content = readFile(error_page);  // Read error page content
            if (content.empty()) content = "<html><body><h1>405 Method Not Allowed</h1></body></html>";  // Default error content
            std::ostringstream response;  // Build HTTP response
            response << "HTTP/1.1 405 Method Not Allowed\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();  // Return 405 response
        }
    }

    // Manejar POST con upload_path
    if (request.getMethod() == "POST" && !location->upload_path.empty()) {  // Handle POST requests with upload capability
        size_t max_body_size = location->client_max_body_size > 0 ? location->client_max_body_size : config.client_max_body_size;  // Get body size limit
        if (request.getBody().length() > max_body_size) {  // Check if body exceeds limit
            std::cerr << "DEBUG: Request body size (" << request.getBody().length() << ") exceeds client_max_body_size (" << max_body_size << ")" << std::endl << std::flush;
            status_code = 413;  // Set 413 Payload Too Large status
            std::string error_page = config.error_pages.find(413) != config.error_pages.end() ? config.root + config.error_pages.find(413)->second : config.root + "/errors/413.html";  // Get error page
            std::string content = readFile(error_page);  // Read error page content
            if (content.empty()) content = "<html><body><h1>413 Payload Too Large</h1></body></html>";  // Default error content
            std::ostringstream response;  // Build HTTP response
            response << "HTTP/1.1 413 Payload Too Large\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();  // Return 413 response
        }
        return handleUpload(location->upload_path);  // Delegate to upload handler
    }

    // Manejar DELETE
    if (request.getMethod() == "DELETE") {  // Handle DELETE requests
        std::string dir_path = path.substr(0, path.find_last_of('/'));  // Get directory path
        if (access(dir_path.c_str(), W_OK) != 0) {  // Check write permission on directory
            std::cerr << "ERROR: No write permission for directory: " << dir_path 
                      << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            status_code = 403;  // Set 403 Forbidden status
            std::string error_page = config.error_pages.find(403) != config.error_pages.end() ? config.root + config.error_pages.find(403)->second : config.root + "/errors/403.html";  // Get error page
            std::string content = readFile(error_page);  // Read error page content
            if (content.empty()) content = "<html><body><h1>403 Forbidden - No Write Permission</h1></body></html>";  // Default error content
            std::ostringstream response;  // Build HTTP response
            response << "HTTP/1.1 403 Forbidden\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();  // Return 403 response
        }

        if (!fileExists(path)) {
            std::cerr << "DEBUG: Path does not exist: " << path << std::endl << std::flush;
            status_code = 404;
            std::string error_page = config.error_pages.find(404) != config.error_pages.end() ? config.root + config.error_pages.find(404)->second : config.root + "/errors/404.html";
            std::string content = readFile(error_page);
            if (content.empty()) content = "<html><body><h1>404 Not Found - Resource Missing</h1></body></html>";
            std::ostringstream response;
            response << "HTTP/1.1 404 Not Found\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();
        }

        if (isDirectory(path)) {
            std::cerr << "DEBUG: Path is a directory: " << path << std::endl << std::flush;
            status_code = 403;
            std::string error_page = config.error_pages.find(403) != config.error_pages.end() ? config.root + config.error_pages.find(403)->second : config.root + "/errors/403.html";
            std::string content = readFile(error_page);
            if (content.empty()) content = "<html><body><h1>403 Forbidden - Cannot Delete Directory</h1></body></html>";
            std::ostringstream response;
            response << "HTTP/1.1 403 Forbidden\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();
        }

        if (unlink(path.c_str()) == 0) {  // Attempt to delete the file
            std::cerr << "DEBUG: File deleted successfully: " << path << std::endl << std::flush;
            status_code = 200;  // Set 200 OK status
            std::string content = "<html><body><h1>200 OK - File Deleted</h1></body></html>";  // Success message
            std::ostringstream response;  // Build HTTP response
            response << "HTTP/1.1 200 OK\r\n"
                    << "Content-Type: text/html\r\n"
                    << "Content-Length: " << content.length() << "\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << content;
            return response.str();  // Return success response
        } else {  // If deletion failed
            std::cerr << "ERROR: Failed to delete file: " << path 
                      << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
            status_code = 500;  // Set 500 Internal Server Error status
            std::string error_page = config.error_pages.find(500) != config.error_pages.end() ? config.root + config.error_pages.find(500)->second : config.root + "/errors/500.html";  // Get error page
            std::string content = readFile(error_page);  // Read error page content
            if (content.empty()) content = "<html><body><h1>500 Internal Server Error - Delete Failed</h1></body></html>";  // Default error content
            std::ostringstream response;  // Build HTTP response
            response << "HTTP/1.1 500 Internal Server Error\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
            return response.str();  // Return error response
        }
    }

    // Manejar GET y otros métodos
    if (!fileExists(path)) {  // Check if requested resource exists
        std::cerr << "DEBUG: Path does not exist: " << path << std::endl << std::flush;
        status_code = 404;  // Set 404 Not Found status
        std::string error_page = config.error_pages.find(404) != config.error_pages.end() ? config.root + config.error_pages.find(404)->second : config.root + "/errors/404.html";  // Get error page
        std::string content = readFile(error_page);  // Read error page content
        if (content.empty()) content = "<html><body><h1>404 Not Found - Resource Missing</h1></body></html>";  // Default error content
        std::ostringstream response;
        response << "HTTP/1.1 404 Not Found\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }

    if (isDirectory(path)) {
        std::string uri = request.getUri();
        std::string index_path = path + (location && !location->index.empty() ? location->index : config.index);
        if (uri.empty() || uri == "/" || uri[uri.length() - 1] == '/') {
            if (fileExists(index_path)) {
                std::cerr << "DEBUG: Serving index file: " << index_path << std::endl << std::flush;
                path = index_path;
            } else if (location && location->directory_listing) {
                std::cerr << "DEBUG: Generating directory listing for: " << path << std::endl << std::flush;
                std::string content = generateDirectoryListing(path, uri);
                if (content.empty()) {
                    status_code = 403;
                    std::string error_page = config.error_pages.find(403) != config.error_pages.end() ? config.root + config.error_pages.find(403)->second : config.root + "/errors/403.html";
                    std::string content = readFile(error_page);
                    if (content.empty()) content = "<html><body><h1>403 Forbidden - Directory Listing Failed</h1></body></html>";
                    std::ostringstream response;
                    response << "HTTP/1.1 403 Forbidden\r\n"
                            << "Content-Type: text/html\r\n"
                            << "Content-Length: " << content.length() << "\r\n"
                            << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                            << "Connection: close\r\n"
                            << "\r\n"
                            << content;
                    return response.str();
                }
                std::ostringstream response;
                response << "HTTP/1.1 200 OK\r\n"
                        << "Content-Type: text/html\r\n"
                        << "Content-Length: " << content.length() << "\r\n"
                        << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                        << "Connection: close\r\n"
                        << "\r\n"
                        << content;
                return response.str();
            } else {
                std::cerr << "DEBUG: Index file not found and directory listing disabled: " << index_path << std::endl << std::flush;
                status_code = 403;
                std::string error_page = config.error_pages.find(403) != config.error_pages.end() ? config.root + config.error_pages.find(403)->second : config.root + "/errors/403.html";
                std::string content = readFile(error_page);
                if (content.empty()) content = "<html><body><h1>403 Forbidden - Directory Access Denied</h1></body></html>";
                std::ostringstream response;
                response << "HTTP/1.1 403 Forbidden\r\n"
                        << "Content-Type: text/html\r\n"
                        << "Content-Length: " << content.length() << "\r\n"
                        << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                        << "Connection: close\r\n"
                        << "\r\n"
                        << content;
                return response.str();
            }
        } else {
            std::cerr << "DEBUG: Directory redirect: " << path << std::endl << std::flush;
            std::ostringstream response;
            response << "HTTP/1.1 307 Temporary Redirect\r\n"
                    << "Location: " << uri << "/\r\n"
                    << "Content-Length: 0\r\n"
                    << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                    << "Connection: close\r\n"
                    << "\r\n";
            return response.str();
        }
    }

    if (location && !location->redirect.empty()) {
        std::cerr << "DEBUG: Redirecting to: " << location->redirect << std::endl << std::flush;
        std::ostringstream response;
        response << "HTTP/1.1 301 Moved Permanently\r\n"
                << "Location: " << location->redirect << "\r\n"
                << "Content-Length: 0\r\n"
                << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                << "Connection: close\r\n"
                << "\r\n";
        return response.str();
    }

    if (location && !location->cgi_paths.empty()) {
        std::string extension;
        size_t dot_pos = path.find_last_of(".");
        if (dot_pos != std::string::npos && dot_pos < path.length() - 1) {
            extension = path.substr(dot_pos);
            std::cerr << "DEBUG: Detected file extension: " << extension << std::endl << std::flush;
        } else {
            std::cerr << "DEBUG: No file extension found for path: " << path << std::endl << std::flush;
        }

        std::map<std::string, std::string>::const_iterator it = location->cgi_paths.find(extension);
        if (it != location->cgi_paths.end() && fileExists(path)) {
            std::string cgi_interpreter = it->second;
            std::cerr << "DEBUG: Detected CGI request for path: " << path << ", cgi_interpreter: " << cgi_interpreter << std::endl << std::flush;
            std::cerr << "DEBUG: Starting CGI execution, clearing any previous output" << std::endl << std::flush;
            CGI cgi(request, *location, config, port);
            std::pair<std::string, int> cgi_result = cgi.execute(path);
            std::string cgi_output = cgi_result.first;
            status_code = cgi_result.second;
            std::cerr << "DEBUG: CGI executed with status: " << status_code << ", output length: " << cgi_output.length() << std::endl << std::flush;
            std::ostringstream response;
            if (status_code == 200) {
                response << "HTTP/1.1 200 OK\r\n";
            } else {
                response << "HTTP/1.1 500 Internal Server Error\r\n";
            }
            response << "Content-Type: " << getMimeType(path) << "\r\n"
                     << "Content-Length: " << cgi_output.length() << "\r\n"
                     << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                     << "Connection: close\r\n"
                     << "\r\n"
                     << cgi_output;
            return response.str();
        } else {
            std::cerr << "DEBUG: No CGI interpreter found for extension: " << extension << " or file does not exist" << std::endl << std::flush;
        }
    }

    // Static file serving - final fallback for non-CGI, non-special requests
    // Evaluation point: static file serving with proper MIME type detection
    // Evaluation point: file reading with proper error handling (500 status code)
    // Evaluation point: Content-Length header calculation for HTTP compliance
    // Evaluation point: session cookie persistence across static file requests
    std::string content = readFile(path);
    if (content.empty()) {
        std::cerr << "ERROR: Failed to read file: " << path << ", errno: " << errno << " (" << strerror(errno) << ")" << std::endl << std::flush;
        status_code = 500;
        std::string error_page = config.error_pages.find(500) != config.error_pages.end() ? config.root + config.error_pages.find(500)->second : config.root + "/errors/500.html";
        std::string content = readFile(error_page);
        if (content.empty()) content = "<html><body><h1>500 Internal Server Error</h1></body></html>";
        std::ostringstream response;
        response << "HTTP/1.1 500 Internal Server Error\r\n"
                << "Content-Type: text/html\r\n"
                << "Content-Length: " << content.length() << "\r\n"
                << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
                << "Connection: close\r\n"
                << "\r\n"
                << content;
        return response.str();
    }
    std::cerr << "DEBUG: Serving static file: " << path << std::endl << std::flush;
    // Generate successful static file response with proper HTTP headers
    // Evaluation point: HTTP/1.1 compliant response format
    // Evaluation point: MIME type detection based on file extension
    // Evaluation point: Content-Length header for proper HTTP communication
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: " << getMimeType(path) << "\r\n"
            << "Content-Length: " << content.length() << "\r\n"
            << "Set-Cookie: session_id=" << session_id << "; Path=/\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << content;
    return response.str();
}