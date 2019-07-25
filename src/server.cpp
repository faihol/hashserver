#include <thread>

#include <server.h>

server::server(short port): m_acceptor(m_io_service)
{
	boost::asio::ip::tcp::endpoint endpoint = tcp::endpoint(tcp::v4(), port);
	m_acceptor.open(endpoint.protocol());
	m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acceptor.bind(endpoint);
	m_acceptor.listen();
	do_accept();
}

void server::run(size_t thread_count) {
	std::vector<std::shared_ptr<std::thread>> threads;
	for (std::size_t i = 0; i < thread_count; ++i) {
		auto ptr = std::shared_ptr<std::thread>(new std::thread([this](){m_io_service.run();}));
		threads.push_back(ptr);
	}
	for (std::size_t i = 0; i < thread_count; ++i)
		threads[i]->join();
}

void server::do_accept() {
	std::shared_ptr<session> new_session(new session(m_io_service));
	m_acceptor.async_accept(new_session->socket(),
		[this, new_session](const boost::system::error_code & e) {
			if (!e) {
				new_session->start();
			}
			do_accept();
	});
}
