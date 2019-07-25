#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "session"
#include <boost/test/unit_test.hpp>
#include <session.h>

#define BIG_STRING "weuthn iuqhwty iewybt aoiuhrmbgndskjgbroib amsnbfskjdhbf sadbfkjherbgr gkjhbashjfvkjashvgnd gajshdgjhvgasvjhdvgjrhvgjh sakjdghsdgaskjdg"

BOOST_AUTO_TEST_CASE(test_session) {
	boost::asio::io_service io_service;
	session s(io_service);
	BOOST_REQUIRE_GT(strlen(BIG_STRING), session::buffer_size);
	const std::string data{"123\n\n" BIG_STRING "\n789"};
	const std::array<const std::string, 3> results{
		"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3",
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
		"1878c3cec73b0c43764a086679ded1d7ac1064f631af4a3dcc75b3466afc963c",
	};
	size_t result = 0;
	s.process_data(data.c_str(), data.size(), [&](const std::string & data) {
		BOOST_CHECK_EQUAL(results[result++] + session::delimiter, data);
	});
	BOOST_CHECK_EQUAL(result, results.size());
}
