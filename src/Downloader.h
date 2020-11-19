#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <string>
#include <fstream>

#include <boost/asio.hpp>

class Downloader
{
public:
	explicit Downloader(const std::string& target_url,
			const std::string& protocol,
			const std::string& file_name);

	~Downloader();

	void write();
	void write(const std::string& target_url);
private:
	void get_http();
	void accept_all();
	void close_connection();

	const std::string target_url;
	const std::string protocol;
	boost::asio::ip::tcp::iostream reader;
	std::fstream writer;
};


Downloader::Downloader(const std::string& url,
		const std::string& protocol_type,
		const std::string& file_name)
: target_url(url)
, protocol(protocol_type)
, reader(target_url, protocol)
{
	writer.open(file_name,
			std::fstream::in | std::fstream::out | std::fstream::app);
}

void Downloader::write()
{
	get_http();
	reader << "Host: " + target_url + "\r\n";
	close_connection();
	accept_all();
	reader.flush();
	writer << reader.rdbuf();
}

Downloader::~Downloader()
{
	writer.close();
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