#pragma once

#include <string>
#include <memory>

class hasher {
public:
	static const size_t size = 64;

	hasher();
	~hasher();
	void add(const void * data, size_t size);
	void finish(std::string & out);

private:
	struct impl;
	std::unique_ptr<impl> m_impl;
};
