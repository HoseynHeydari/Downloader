#ifndef READER_H_
#define READER_H_

#include <string>

#include <boost/asio.hpp>

class Reader
{
public:
	inline Reader(const std::string& url, const std::string& protocol_type);
	inline explicit Reader(const Configure& configure);
	virtual ~Reader() = default;

	virtual inline void get_http();
	virtual inline void read_from_host(const std::string& url);
	virtual inline void accept_all();
	virtual inline void close_connection();

	inline std::streambuf* get_stream_buffer();

private:
	boost::asio::ip::tcp::iostream stream;
};

Reader::Reader(const std::string& url, const std::string& protocol_type)
: stream(url, protocol_type)
{
}

Reader::Reader(const Configure& configure)
: stream(configure.get_url(), configure.get_protocol())
{
}

void Reader::get_http()
{
	stream << "GET / HTTP/1.1\r\n";
}

void Reader::read_from_host(const std::string& url)
{
	stream << "Host: " + url + "\r\n";
}

void Reader::accept_all()
{
	stream << "Accept: */*\r\n";
}

void Reader::close_connection()
{
	stream << "Connection: close\r\n\r\n";
}

std::streambuf* Reader::get_stream_buffer()
{
	stream.flush();
	return stream.rdbuf();
}

#endif