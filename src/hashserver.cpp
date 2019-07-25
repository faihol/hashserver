#include <iostream>
#include <thread>
#include <boost/asio.hpp>

#include <server.h>

int main(int argc, char ** argv) {
	try {
		if (argc != 2) {
			std::cerr << "Usage: hashserver <port>\n";
			return EXIT_FAILURE;
		}
		const int port = std::atoi(argv[1]);
		if (port <= 0) {
			std::cerr << "Please specify usable port number\n";
			return EXIT_FAILURE;
		}
		server s(port);
		boost::asio::signal_set signal_set(s.io_service());
		signal_set.add(SIGINT);
		signal_set.add(SIGTERM);
		signal_set.add(SIGQUIT);
		signal_set.async_wait([&s](const boost::system::error_code&, const int&){s.io_service().stop();});
		s.run(std::thread::hardware_concurrency()*2);
	} catch (const std::exception & e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return EXIT_SUCCESS;
}
