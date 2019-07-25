#include <session.h>

static size_t find_delimiter(const char * data, size_t from, size_t to) {
	for (; from < to; ++from)
		if (data[from] == session::delimiter)
			break;
	return from;
}

void session::process_data(const char * data, size_t length, std::function<void(const std::string &)> callback) {
	size_t prev = 0;
	size_t next = find_delimiter(data, prev, length);
	for (; next < length; prev = ++next, next = find_delimiter(data, next, length)) {
		m_hasher.add(data + prev, next - prev);
		m_hasher.finish(m_reply);
		m_reply += delimiter;
		callback(m_reply);
	}
	m_hasher.add(data + prev, next - prev);
}

void session::do_read() {
	auto self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(m_data, buffer_size),
		m_strand.wrap([this, self](boost::system::error_code ec, std::size_t length) {
			if (!ec) {
				process_data(m_data, length, [this](const std::string & data){do_write(data);});
			}
	}));
}
void session::do_write(const std::string & data) {
	auto self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(data.c_str(), data.size()),
		m_strand.wrap([this, self](boost::system::error_code ec, std::size_t /*length*/) {
		if (!ec) {
			do_read();
		}
	}));
}
