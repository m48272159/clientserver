#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <thread>
#include <string>


// Function to handle client connections
void HandleClient(boost::asio::ip::tcp::socket& socket) {
    try {
        // Read data from the client
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket, buffer, '\n');
        std::string data;
        std::istream is(&buffer);
        std::getline(is, data);

        // Echo the data to the console
        std::cout << "Received from client: " << data << std::endl;
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error handling client: " << e.what() << std::endl;
    }
}

// Function to start the server
void StartServer(unsigned short port) {
	// Create an IO service
    boost::asio::io_service ioService;
    // Create a TCP endpoint
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

    // Create a TCP acceptor
    boost::asio::ip::tcp::acceptor acceptor(ioService, endpoint);

    // Start accepting clients
    while (true) {
        try {
            // Create a new socket for the client
            boost::asio::ip::tcp::socket socket(ioService);

            // Accept the client connection
            acceptor.accept(socket);

            // Spawn a new thread to handle the client
            std::thread clientThread(HandleClient, std::ref(socket));
            clientThread.detach();
        } catch (const boost::system::system_error& e) {
            std::cerr << "Error accepting client: " << e.what() << std::endl;
        }
    }
}


// Function to handle user input
void HandleUserInput(boost::asio::ip::tcp::socket& socket) {
    try {
        // Read user input
        std::string userInput;
        std::getline(std::cin, userInput);

        // Send the user input to the server
        boost::asio::write(socket, boost::asio::buffer(userInput + "\n"));
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error sending data to server: " << e.what() << std::endl;
    }
}

void StartClient(unsigned short port)
{
    try {
        // Create an IO service
        boost::asio::io_service ioService;

        // Create a TCP endpoint
		// TODO: remove hardcoding of loopback address
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::loopback(), port);

        // Create a TCP socket
        boost::asio::ip::tcp::socket socket(ioService);

        // Connect to the server
        socket.connect(endpoint);

        // Start a loop to handle user input
        while (true) {
            // Handle user input
            HandleUserInput(socket);

            // Check if the user wants to exit
            if (std::cin.eof()) {
                break;
            }
        }
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error connecting to server: " << e.what() << std::endl;
		exit(1);
    }
}

