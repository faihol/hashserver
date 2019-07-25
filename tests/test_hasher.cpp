#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "hasher"
#include <boost/test/unit_test.hpp>
#include <hasher.h>

std::string calculate(const std::string & data, hasher & h) {
	h.add(data.c_str(), data.size());
	std::string out;
	h.finish(out);
	return out;
}

BOOST_AUTO_TEST_CASE(test_hasher) {
	hasher h;
	const std::string data{"0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789"};
	std::string out;
	BOOST_CHECK_EQUAL(calculate(data, h), "c9066ae2de840b3553dbab468755ba2aad0f95125c5b86c8152edfa32be63719");
	BOOST_CHECK_EQUAL(calculate({}, h), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}
