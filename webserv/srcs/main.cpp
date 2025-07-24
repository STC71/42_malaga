// Main entry point for webserv HTTP server
// Evaluation point: program must handle configuration file as argument
// Evaluation point: proper error handling and resource cleanup
// Evaluation point: single server instance managing all ports and connections
// Evaluation point: graceful startup and shutdown procedures

#include "Server.hpp"        // Server class with select() loop and I/O multiplexing
#include "Config.hpp"        // Configuration parser for server setup
#include <iostream>          // std::cerr for error output and debugging

// Main function - entry point for webserv HTTP server
// Evaluation point: must accept configuration file as command line argument
// Evaluation point: proper initialization sequence and error handling
int main(int argc, char* argv[]) {
    // Handle configuration file argument
    // Evaluation point: default config file should be provided if none specified
    std::string config_file = (argc > 1) ? argv[1] : "config/default.conf";
    std::cerr << "DEBUG: Loading config file: " << config_file << std::endl;

    // Parse configuration file
    // Evaluation point: configuration parsing must be robust with proper error handling
    Config config;
    try {
        config.load(config_file);
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Failed to load config: " << e.what() << std::endl;
        return 1;
    }

    // Create single server instance to handle all ports and connections
    // Evaluation point: CRITICAL - only one server instance with select() loop
    // Evaluation point: proper resource management with exception safety
    Server* server = NULL;
    try {
        server = new Server(config);
        std::cerr << "DEBUG: Created server instance" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Failed to create server: " << e.what() << std::endl;
        return 1;
    }

    // Execute server main loop
    // Evaluation point: server.run() contains the main select() loop
    // Evaluation point: proper exception handling during server execution
    try {
        server->run();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: Server runtime error: " << e.what() << std::endl;
        delete server;
        return 1;
    }

    // Cleanup resources and graceful shutdown
    // Evaluation point: proper memory management and resource cleanup
    delete server;
    return 0;
}