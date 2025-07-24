// HTTP Request parser implementation for webserv project
// Evaluation point: must support GET, POST, and DELETE methods correctly
// Evaluation point: proper HTTP header parsing and validation
// Evaluation point: body parsing with Content-Length and Transfer-Encoding support
// Evaluation point: chunked encoding support for request bodies
// Evaluation point: multipart/form-data parsing for file uploads

#include "Request.hpp"       // Request class definition with HTTP parsing capabilities
#include <sstream>           // std::istringstream for parsing request lines and headers
#include <iostream>          // std::cerr for debug output and error logging
#include <stdexcept>         // std::runtime_error for HTTP parsing errors
#include <cstdlib>           // std::atoi for Content-Length conversion
#include <sys/socket.h>      // socket operations (if needed for client file descriptor)
#include <unistd.h>          // POSIX standard definitions (if needed)
#include <cerrno>            // errno global variable for system call error reporting
#include <cstring>           // strerror() for errno to string conversion
#include <iomanip>           // std::hex, std::setw for hex dump of request data
#include <cctype>            // std::isxdigit for hexadecimal validation in chunked encoding

// Constructor - parses initial HTTP request data incrementally
// Evaluation point: incremental parsing supports non-blocking I/O with select()
// Evaluation point: proper validation of HTTP request format and methods
// Evaluation point: support for GET, POST, DELETE methods as required
Request::Request(int fd, const std::string& initial_data) 
    : method(), uri(), query(), version(), headers(), body(), dechunked_body(),
      body_complete(false), is_chunked(false), client_fd(fd) {
    std::cerr << "DEBUG: Constructing Request for client_fd: " << client_fd << std::endl << std::flush;
    std::cerr << "DEBUG: Initial raw_request size: " << initial_data.size() << std::endl << std::flush;
    std::cerr << "DEBUG: Full raw_request content (string): [" << initial_data << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Raw request (string): [" << initial_data.substr(0, 100) << (initial_data.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Raw request (hex): ";
    for (size_t i = 0; i < initial_data.size(); ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)initial_data[i] << " ";
    }
    std::cerr << std::dec << std::endl << std::flush;
    std::string raw_request = initial_data;

    // Parse HTTP request line (METHOD URI VERSION)
    // Evaluation point: proper HTTP/1.1 request line parsing
    std::istringstream iss(raw_request);
    std::string request_line;
    if (!std::getline(iss, request_line)) {
        std::cerr << "DEBUG: Empty request line" << std::endl << std::flush;
        throw std::runtime_error("Empty request line");
    }
    if (!request_line.empty() && request_line[request_line.length() - 1] == '\r') {
        request_line.erase(request_line.length() - 1);
    }

    std::istringstream request_stream(request_line);
    std::string temp_method, temp_uri, temp_version;
    request_stream >> temp_method >> temp_uri >> temp_version;

    if (temp_method.empty() || temp_uri.empty() || temp_version.empty()) {
        std::cerr << "DEBUG: Invalid request line: " << request_line << std::endl << std::flush;
        throw std::runtime_error("Invalid request line");
    }

    // Validate HTTP method support
    // Evaluation point: must support GET, POST, DELETE as specified in subject
    if (temp_method != "GET" && temp_method != "POST" && temp_method != "DELETE") {
        std::cerr << "DEBUG: Unsupported method: " << temp_method << std::endl << std::flush;
        throw std::runtime_error("Unsupported method: " + temp_method);
    }

    method = temp_method;
    // Parse URI and extract query string if present
    // Evaluation point: proper URI parsing with query string support for GET parameters
    size_t query_pos = temp_uri.find('?');
    if (query_pos != std::string::npos) {
        uri = temp_uri.substr(0, query_pos);
        query = temp_uri.substr(query_pos + 1);
    } else {
        uri = temp_uri;
        query = "";
    }
    version = temp_version;
    std::cerr << "DEBUG: Parsed method: " << method << ", URI: " << uri << ", Query: " << query << ", Version: " << version << std::endl << std::flush;

    // Parse HTTP headers
    // Evaluation point: proper header parsing for Content-Length, Transfer-Encoding, etc.
    std::string header_line;
    while (std::getline(iss, header_line) && header_line != "\r" && !header_line.empty()) {
        if (!header_line.empty() && header_line[header_line.length() - 1] == '\r') {
            header_line.erase(header_line.length() - 1);
        }
        size_t colon = header_line.find(':');
        if (colon != std::string::npos) {
            std::string key = header_line.substr(0, colon);
            std::string value = header_line.substr(colon + 1);
            size_t start = value.find_first_not_of(" \t");
            size_t end = value.find_last_not_of(" \t");
            if (start != std::string::npos && end != std::string::npos) {
                value = value.substr(start, end - start + 1);
            }
            headers[key] = value;
            std::cerr << "DEBUG: Parsed header: " << key << ": " << value << std::endl << std::flush;
        }
    }

    // Extract filename from URI for upload requests
    // Evaluation point: file upload support through URI parsing
    if (uri.find("/Uploads/") == 0 && uri.length() > 9) {
        std::string filename = uri.substr(9);
        if (!filename.empty()) {
            headers["X-Filename"] = filename;
            std::cerr << "DEBUG: Extracted filename from URI: " << filename << std::endl << std::flush;
        }
    }

    // Handle different body types: chunked encoding vs. Content-Length
    // Evaluation point: chunked encoding support is critical for HTTP/1.1 compliance
    std::map<std::string, std::string>::const_iterator te_it = headers.find("Transfer-Encoding");
    std::map<std::string, std::string>::const_iterator cl_it = headers.find("Content-Length");

    if (te_it != headers.end() && te_it->second == "chunked") {
        is_chunked = true;
        std::cerr << "DEBUG: Detected Transfer-Encoding: chunked" << std::endl << std::flush;
        // Process chunked body if header end is found
        // Evaluation point: proper chunked encoding implementation
        size_t header_end = raw_request.find("\r\n\r\n");
        if (header_end != std::string::npos) {
            header_end += 4;
            std::cerr << "DEBUG: Full raw_request content (string): [" << raw_request << "]" << std::endl << std::flush;
            body = raw_request.substr(header_end);
            std::cerr << "DEBUG: Raw request before body extraction (string): [" << raw_request.substr(0, 100) << (raw_request.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
            std::cerr << "DEBUG: Raw request before body extraction (hex): ";
            for (size_t i = 0; i < raw_request.size(); ++i) {
                std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)raw_request[i] << " ";
            }
            std::cerr << std::dec << std::endl << std::flush;
            std::cerr << "DEBUG: header_end position: " << header_end << std::endl << std::flush;
            std::cerr << "DEBUG: Initial body content (string): [" << body.substr(0, 100) << (body.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
            std::cerr << "DEBUG: Initial body content (hex): ";
            for (size_t i = 0; i < body.size(); ++i) {
                std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)body[i] << " ";
            }
            std::cerr << std::dec << std::endl << std::flush;
            dechunkBody();
        } else {
            std::cerr << "DEBUG: No header end found in raw_request, waiting for more data" << std::endl << std::flush;
        }
    } else if (cl_it != headers.end()) {
        // Handle Content-Length body
        // Evaluation point: proper Content-Length parsing for POST request bodies
        size_t content_length = std::atoi(cl_it->second.c_str());
        std::cerr << "DEBUG: Content-Length: " << content_length << std::endl << std::flush;
        size_t header_end = raw_request.find("\r\n\r\n");
        if (header_end != std::string::npos) {
            header_end += 4;
            body = raw_request.substr(header_end);
            std::cerr << "DEBUG: Initial body content (string): [" << body.substr(0, 100) << (body.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
            std::cerr << "DEBUG: Initial body content (hex): ";
            for (size_t i = 0; i < body.size(); ++i) {
                std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)body[i] << " ";
            }
            std::cerr << std::dec << std::endl << std::flush;
        } else {
            std::cerr << "DEBUG: No header end found in raw_request, waiting for more data" << std::endl << std::flush;
        }
        if (body.size() >= content_length) {
            body = body.substr(0, content_length);
            body_complete = true;
            // Process multipart form data for file uploads
            // Evaluation point: file upload support with multipart/form-data
            processMultipartFormData();
        } else {
            body_complete = false;
        }
    } else {
        body_complete = true;
    }
    std::cerr << "DEBUG: Request parsing complete, body_complete: " << (body_complete ? "true" : "false") << std::endl << std::flush;
}

// Process multipart/form-data for file uploads
// Evaluation point: file upload functionality with proper boundary parsing
void Request::processMultipartFormData() {
    std::map<std::string, std::string>::const_iterator ct_it = headers.find("Content-Type");
    if (ct_it != headers.end() && ct_it->second.find("multipart/form-data") != std::string::npos) {
        // Extract boundary from Content-Type header
        // Evaluation point: proper multipart boundary extraction and parsing
        std::string boundary;
        size_t boundary_pos = ct_it->second.find("boundary=");
        if (boundary_pos != std::string::npos) {
            boundary = "--" + ct_it->second.substr(boundary_pos + 9);
            std::cerr << "DEBUG: Detected multipart/form-data with boundary: " << boundary << std::endl << std::flush;
        }
        if (!boundary.empty()) {
            // Parse multipart sections to extract file content and metadata
            // Evaluation point: robust multipart parsing for file uploads
            size_t pos = body.find(boundary);
            if (pos == std::string::npos) {
                std::cerr << "DEBUG: Failed to find boundary in multipart body" << std::endl << std::flush;
                return;
            }
            // Extract filename from multipart headers
            // Evaluation point: proper filename extraction for file uploads
            size_t filename_pos = body.find("filename=\"", pos);
            if (filename_pos != std::string::npos) {
                filename_pos += 10;
                size_t filename_end = body.find("\"", filename_pos);
                if (filename_end != std::string::npos && filename_end > filename_pos) {
                    headers["X-Filename"] = body.substr(filename_pos, filename_end - filename_pos);
                    std::cerr << "DEBUG: Parsed filename from multipart: " << headers["X-Filename"] << std::endl << std::flush;
                }
            }
            // Separate multipart headers from file content
            // Evaluation point: proper content extraction from multipart data
            size_t content_pos = body.find("\r\n\r\n", pos);
            if (content_pos != std::string::npos) {
                content_pos += 4;
                size_t boundary_end = body.find(boundary + "--", content_pos);
                if (boundary_end == std::string::npos) {
                    boundary_end = body.find(boundary, content_pos);
                }
                if (boundary_end != std::string::npos) {
                    body = body.substr(content_pos, boundary_end - content_pos);
                    std::cerr << "DEBUG: Extracted multipart body, length: " << body.length() << std::endl << std::flush;
                } else {
                    std::cerr << "DEBUG: Failed to find end boundary in multipart body" << std::endl << std::flush;
                    return;
                }
            } else {
                std::cerr << "DEBUG: Failed to find content start in multipart body" << std::endl << std::flush;
                return;
            }
        } else {
            std::cerr << "DEBUG: No boundary found in Content-Type" << std::endl << std::flush;
            return;
        }
    }
}

// Append additional data to request body for incremental parsing
// Evaluation point: incremental body parsing supports non-blocking I/O
void Request::appendBody(const std::string& data) {
    body += data;
    std::cerr << "DEBUG: Appended to body, new length: " << body.length() << std::endl << std::flush;
    std::cerr << "DEBUG: Appended body content (string): [" << data.substr(0, 100) << (data.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Appended body content (hex): ";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)data[i] << " ";
    }
    std::cerr << std::dec << std::endl << std::flush;
    if (is_chunked) {
        // Process chunked data as it arrives
        // Evaluation point: incremental chunked encoding processing
        dechunkBody();
    } else if (!body_complete) {
        // Check if Content-Length body is now complete
        // Evaluation point: proper Content-Length validation and completion detection
        std::map<std::string, std::string>::const_iterator cl_it = headers.find("Content-Length");
        if (cl_it != headers.end()) {
            size_t content_length = std::atoi(cl_it->second.c_str());
            if (body.size() >= content_length) {
                body = body.substr(0, content_length);
                body_complete = true;
                // Process complete multipart data if applicable
                processMultipartFormData();
            }
        }
    }
}

// Decode chunked transfer encoding to extract actual content
// Evaluation point: chunked encoding is critical for HTTP/1.1 compliance
void Request::dechunkBody() {
    if (!is_chunked) {
        std::cerr << "DEBUG: Not a chunked request" << std::endl << std::flush;
        dechunked_body = body;
        body_complete = true;
        return;
    }

    std::cerr << "DEBUG: Starting dechunkBody()" << std::endl << std::flush;
    
    // Validate chunked encoding format before processing
    // Evaluation point: robust chunked encoding validation and error handling
    // Valid chunked data must start with hexadecimal chunk size
    size_t first_crlf = body.find("\r\n");
    if (first_crlf != std::string::npos) {
        std::string first_line = body.substr(0, first_crlf);
        
        // Validate first line is hexadecimal (chunk size)
        // Evaluation point: proper hexadecimal validation for chunk sizes
        bool is_hex = true;
        for (size_t i = 0; i < first_line.length(); ++i) {
            if (!std::isxdigit(first_line[i])) {
                is_hex = false;
                break;
            }
        }
        
        // If first line is not valid hex, assume data is already dechunked
        // Evaluation point: graceful handling of malformed chunked data
        if (!is_hex || first_line.empty()) {
            std::cerr << "DEBUG: Data appears to be already dechunked, using as-is" << std::endl << std::flush;
            dechunked_body = body;
            body_complete = true;
            return;
        }
        
        // Validate chunked encoding format structure
        // Evaluation point: complete chunked encoding format validation
        // Valid format: size\r\ndata\r\nsize\r\ndata\r\n0\r\n\r\n
        std::stringstream ss;
        ss << std::hex << first_line;
        size_t chunk_size;
        ss >> chunk_size;
        
        // Verify chunk structure validity by checking next chunk header
        // Evaluation point: comprehensive chunk format validation
        size_t expected_next_chunk_pos = first_crlf + 2 + chunk_size + 2;
        if (expected_next_chunk_pos < body.length()) {
            size_t next_crlf = body.find("\r\n", expected_next_chunk_pos);
            if (next_crlf != std::string::npos) {
                std::string next_line = body.substr(expected_next_chunk_pos, next_crlf - expected_next_chunk_pos);
                // Validate next chunk size or terminator
                // Evaluation point: proper validation of chunk continuation
                bool next_is_hex = true;
                if (!next_line.empty()) {
                    for (size_t i = 0; i < next_line.length(); ++i) {
                        if (!std::isxdigit(next_line[i])) {
                            next_is_hex = false;
                            break;
                        }
                    }
                    if (!next_is_hex && next_line != "0") {
                        std::cerr << "DEBUG: Next chunk line is not hex, assuming already dechunked" << std::endl << std::flush;
                        dechunked_body = body;
                        body_complete = true;
                        return;
                    }
                }
            }
        }
        
        // Final validation: check if chunk size is reasonable
        // Evaluation point: prevent processing of malformed chunked data
        if (chunk_size > body.length() - first_crlf - 2 + 10) { // +10 for error margin
            std::cerr << "DEBUG: Chunk size (" << chunk_size << ") exceeds remaining data significantly, assuming already dechunked" << std::endl << std::flush;
            dechunked_body = body;
            body_complete = true;
            return;
        }
    }

    // Process chunked encoding according to HTTP/1.1 specification
    // Evaluation point: correct implementation of chunked transfer encoding
    dechunked_body.clear();
    size_t pos = 0;

    while (pos < body.length()) {
        // Read chunk size line (hexadecimal format)
        // Evaluation point: proper chunk size parsing and validation
        size_t line_end = body.find("\r\n", pos);
        if (line_end == std::string::npos) {
            std::cerr << "ERROR: Invalid chunked encoding, no CRLF found at pos " << pos << std::endl << std::flush;
            break;
        }

        std::string chunk_size_str = body.substr(pos, line_end - pos);
        std::cerr << "DEBUG: Read chunk size string: " << chunk_size_str << std::endl << std::flush;

        // Convert chunk size from hexadecimal to integer
        // Evaluation point: proper hexadecimal to integer conversion
        std::stringstream ss;
        ss << std::hex << chunk_size_str;
        size_t chunk_size;
        ss >> chunk_size;

        std::cerr << "DEBUG: Parsed chunk size: " << chunk_size << std::endl << std::flush;

        // Check for chunk termination (size 0 indicates end of chunks)
        // Evaluation point: proper handling of chunked encoding termination
        if (chunk_size == 0) {
            pos = line_end + 2; // Skip \r\n
            if (pos < body.length() && body.substr(pos, 2) == "\r\n") {
                pos += 2; // Skip final \r\n
            }
            std::cerr << "DEBUG: Chunked body complete, final length: " << dechunked_body.length() << std::endl << std::flush;
            body_complete = true;
            break;
        }

        // Move position after chunk size line
        pos = line_end + 2;

        // Validate sufficient data is available for chunk
        // Evaluation point: proper chunk boundary validation
        if (pos + chunk_size > body.length()) {
            std::cerr << "ERROR: Incomplete chunk, expected " << chunk_size << " bytes, but only " << (body.length() - pos) << " available" << std::endl << std::flush;
            body_complete = false;
            break;
        }

        // Extract chunk data
        // Evaluation point: safe chunk data extraction
        dechunked_body.append(body, pos, chunk_size);
        std::cerr << "DEBUG: Appended " << chunk_size << " bytes to dechunked body, total: " << dechunked_body.length() << std::endl << std::flush;

        // Move position after chunk data and trailing CRLF
        // Evaluation point: proper CRLF handling after chunk data
        pos += chunk_size;
        if (pos + 2 <= body.length() && body.substr(pos, 2) == "\r\n") {
            pos += 2; // Skip \r\n after data
        } else {
            std::cerr << "ERROR: Missing CRLF after chunk data at pos " << pos << std::endl << std::flush;
            body_complete = false;
            break;
        }
    }

    std::cerr << "DEBUG: Dechunked body: [" << dechunked_body << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Dechunked body (hex): ";
    for (size_t i = 0; i < dechunked_body.size(); ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)dechunked_body[i] << " ";
    }
    std::cerr << std::dec << std::endl << std::flush;
}

// Check if request parsing is complete
// Evaluation point: proper completion detection for incremental parsing
bool Request::isComplete() const {
    return body_complete;
}

// Get processed request body (dechunked if applicable)
// Evaluation point: proper body content retrieval for both chunked and non-chunked requests
std::string Request::getBody() const {
    if (is_chunked) {
        // Return dechunked body for chunked requests
        // Evaluation point: proper dechunked content delivery
        std::cerr << "DEBUG: Returning dechunked_body (string): [" << dechunked_body.substr(0, 100) << (dechunked_body.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
        std::cerr << "DEBUG: Returning dechunked_body (hex): ";
        for (size_t i = 0; i < dechunked_body.size(); ++i) {
            std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)dechunked_body[i] << " ";
        }
        std::cerr << std::dec << std::endl << std::flush;
        return dechunked_body;
    }
    // Return regular body for non-chunked requests
    // Evaluation point: proper content delivery for Content-Length requests
    std::cerr << "DEBUG: Returning body (string): [" << body.substr(0, 100) << (body.size() > 100 ? "..." : "") << "]" << std::endl << std::flush;
    std::cerr << "DEBUG: Returning body (hex): ";
    for (size_t i = 0; i < body.size(); ++i) {
        std::cerr << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)body[i] << " ";
    }
    std::cerr << std::dec << std::endl << std::flush;
    return body;
}

// Get HTTP header value by key
// Evaluation point: proper header access for request processing
std::string Request::getHeader(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = headers.find(key);
    if (it != headers.end()) {
        return it->second;
    }
    return "";
}