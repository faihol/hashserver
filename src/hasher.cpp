#include <cstring>
#include <stdexcept>
#include <openssl/sha.h>

#include <hasher.h>

static const size_t SIZE = SHA256_DIGEST_LENGTH;
static_assert (SIZE*2 == hasher::size, "hasher out buffer size doesn't match");

struct hasher::impl {
	impl() {
		if(!SHA256_Init(&context))
			throw std::runtime_error("SHA256_Init failed");
	}
	void add(const void * data, size_t size) {
		if(!SHA256_Update(&context, data, size))
			throw std::runtime_error("SHA256_Update failed");
	}
	void finish(unsigned char md[SIZE]) {
		if(!SHA256_Final(md, &context))
			throw std::runtime_error("SHA256_Final failed");
	}
	SHA256_CTX context;
};

hasher::hasher() {}
hasher::~hasher() {}

void hasher::add(const void * data, size_t size) {
	if (data != nullptr && size != 0) {
		if (!m_impl)
			m_impl.reset(new impl());
		m_impl->add(data, size);
	}
}

static char halfbyte2hex(unsigned char value) {
	return char(value + (value < 10 ? '0' : 'a' - 10));
}

void hasher::finish(std::string & out) {
	out.resize(size);
	if (!m_impl)
		m_impl.reset(new impl());
	unsigned char md[SIZE];
	m_impl->finish(md);
	m_impl.reset(nullptr);
	for (size_t i = 0; i < SIZE; ++i) {
		out[i*2] = halfbyte2hex(md[i]/16);
		out[i*2+1] = halfbyte2hex(md[i]%16);
	}
}
