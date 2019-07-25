#pragma once

#include <boost/asio.hpp>

#include <hasher.h>

using boost::asio::ip::tcp;

class session: public std::enable_shared_from_this<session> {
public:
	enum { buffer_size = 128 };
	static const char delimiter = '\n';
	session(boost::asio::io_service & service): m_socket(service), m_strand(service) {m_reply.reserve(m_hasher.size + 1);}
	void start() {do_read();}
	void process_data(const char * data, size_t length, std::function<void(const std::string &)> callback);
	tcp::socket & socket() {return m_socket;}

private:
	void do_read();
	void do_write(const std::string & data);

	tcp::socket m_socket;
	boost::asio::io_service::strand m_strand;
	std::string m_reply;
	char m_data[buffer_size];
	hasher m_hasher;
};
