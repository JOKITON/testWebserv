#include "tcpServer.hpp"

int main( void ) {
	std::cout << "Attempting to create a server..." << std::endl;
    using namespace http;
	std::string	domain = "0.0.0.0";
    TcpServer server = TcpServer(domain, 8080);

    return 0;
}