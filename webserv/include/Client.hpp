#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <ctime>    // for std::time_t
#include <string>   // for std::string

// Client struct for basic connection data
// Evaluation point: client connections must be managed properly
struct Client {
    int port;
    std::string buffer; // Request buffer - evaluation point: must handle partial reads
    std::string response; // Response buffer - evaluation point: must handle partial writes
    Client(int p) : port(p) {}
};

// Client class for connection management  
// Evaluation point: each client must be handled through select() only
// Evaluation point: only one read or write per client per select() call
// Evaluation point: client must be removed if socket error occurs
class Client {
public:
    // Constructor: sets initial activity time for timeout management
    Client() : last_activity(std::time(NULL)) {}
    
    // Timeout check: prevents hanging connections
    // Evaluation point: server must handle connection timeouts properly
    // Returns true if client exceeded 30 second timeout limit
    bool isTimedOut() const {
        return (std::time(NULL) - last_activity) > 30; // Timeout de 30 segundos
    }
    
    // Activity update: called after successful read/write operations
    // Evaluation point: must be called to prevent premature timeout
    void updateLastActivity() {
        last_activity = std::time(NULL);
    }
private:
    std::time_t last_activity; // tracks last I/O activity for timeout management
};

#endif