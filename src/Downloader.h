#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <string>

#include <boost/asio.hpp>

#include "Writer.h"

class Downloader
{
public:
	Downloader(const std::string& target_url,
			const std::string& protocol,
			const std::string& file_name);

	~Downloader() = default;

	void write();
	void write(const std::string& target_url);
private:
	void get_http();
	void accept_all();
	void close_connection();

	const std::string target_url;
	const std::string protocol;
	boost::asio::ip::tcp::iostream reader;
	Writer my_writer;
};

Downloader::Downloader(const std::string& url,
		const std::string& protocol_type,
		const std::string& file_name)
: target_url(url)
, protocol(protocol_type)
, reader(target_url, protocol)
, my_writer(file_name)
{
}

void Downloader::write()
{
	get_http();
	reader << "Host: " + target_url + "\r\n";
	close_connection();
	accept_all();
	my_writer.write(reader);
}

void Downloader::get_http()
{
	reader << "GET / HTTP/1.1\r\n";
}

void Downloader::accept_all()
{
	reader << "Accept: */*\r\n";
}

void Downloader::close_connection()
{
	reader << "Connection: close\r\n\r\n";
}

#endif