#pragma once

#include <session.h>

class server {
public:
	server(short port);
	void run(size_t thread_count);
	boost::asio::io_service & io_service() {return m_io_service;}

private:
	void do_accept();

	boost::asio::io_service m_io_service;
	tcp::acceptor m_acceptor;
};
