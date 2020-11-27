#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <string>

#include <boost/asio.hpp>

#include "Configure.h"
#include "Writer.h"

class Downloader
{
public:
	inline Downloader(const std::string& target_url,
			const std::string& protocol,
			std::string&& file_name);
	inline Downloader(const Configure& configure);
	Downloader(Downloader&& other) = delete;
	Downloader(const Downloader& other) = delete;

	~Downloader() = default;

	inline void write();
private:
	inline void get_http();
	inline void accept_all();
	inline void close_connection();

	const std::string target_url;
	const std::string protocol;
	boost::asio::ip::tcp::iostream reader;
	Writer my_writer;
};

Downloader::Downloader(const std::string& url,
		const std::string& protocol_type,
		std::string&& file_name)
: target_url(url)
, protocol(protocol_type)
, reader(target_url, protocol)
, my_writer(file_name)
{
}

Downloader::Downloader(const Configure& configure)
: target_url(configure.get_url())
, protocol(configure.get_protocol())
, reader(configure.get_url(), configure.get_protocol())
, my_writer(configure.get_output_name())
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