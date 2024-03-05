#include "tcpServer.hpp"

int main( void ) {
	std::cout << "Attempting to create a server..." << std::endl;
    using namespace http;
	std::string	domain = "0.0.0.0"; // localhost
    TcpServer server = TcpServer(domain, 80); // port 80

    return 0;
}