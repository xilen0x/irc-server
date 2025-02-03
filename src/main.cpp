#include <iostream>
#include "Channel.hpp"
#include "Client.hpp"
#include "Messageprocessing.hpp"
#include "Server.hpp"

// void handleSIGINT(int signal) {
//     std::cout << "SIGINT received. Shutting down the server gracefully..." << std::endl;
//     // Perform cleanup
//     std::exit(0);
// }

// void handleSIGTERM(int signal) {
//     std::cout << "SIGTERM received. Shutting down the server gracefully..." << std::endl;
//     // Perform cleanup
//     std::exit(0);
// }

// void handleSIGSEGV(int signal) {
//     std::cerr << "SIGSEGV received. Segmentation fault occurred!" << std::endl;
//     // Log the error and exit
//     std::exit(1);
// }

// void handleSIGPIPE(int signal) {
//     std::cout << "SIGPIPE received. A client disconnected unexpectedly." << std::endl;
//     // Ignore the signal and continue running
// }

// void handleSIGHUP(int signal) {
//     std::cout << "SIGHUP received. Reloading configuration..." << std::endl;
//     // Reload configuration files
// }

// void handleSIGCHLD(int signal) {
//     std::cout << "SIGCHLD received. Cleaning up child processes..." << std::endl;
//     while (waitpid(-1, nullptr, WNOHANG) > 0); // Clean up zombie processes
// }

// void handleSIGALRM(int signal) {
//     std::cout << "SIGALRM received. Performing periodic tasks..." << std::endl;
//     // Perform periodic tasks (e.g., ping clients)
//     alarm(60); // Reset the alarm for 60 seconds
// }

int main(int argc, char const *argv[])
{
    // std::signal(SIGINT, handleSIGINT);
    // std::signal(SIGTERM, handleSIGTERM);
    // std::signal(SIGSEGV, handleSIGSEGV);
    // std::signal(SIGPIPE, handleSIGPIPE);
    // std::signal(SIGHUP, handleSIGHUP);
    // std::signal(SIGCHLD, handleSIGCHLD);
    // std::signal(SIGALRM, handleSIGALRM);


    if (argc == 3)
    {
        int port = std::atoi(argv[1]);
        // std::string serverName = ;
        std::string password = argv[2];

        try
        {
            if (!parseInput(password, port))
            {
                Server server("ircserv", password, port);
                alarm(60);

    std::cout << "IRC server is running. Press Ctrl+C to stop." << std::endl;
                server.runServer();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            //free resources if needed
        }
    }
    else
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
    return (0);
}
