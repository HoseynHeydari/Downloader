#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <string>

#include "Configure.h"
#include "Reader.h"
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

	virtual ~Downloader() = default;

	virtual inline void download();

private:
	inline void get_http();
	inline void accept_all();
	inline void close_connection();

	const std::string target_url;
	const std::string protocol;
	Reader reader;
	Writer writer;
};

Downloader::Downloader(const std::string& url,
		const std::string& protocol_type,
		std::string&& file_name)
: target_url(url)
, protocol(protocol_type)
, reader(new Reader(target_url, protocol))
, writer(new Writer(file_name))
{
}

Downloader::Downloader(const Configure& configure)
: target_url(configure.get_url())
, protocol(configure.get_protocol())
, reader(new Reader(configure))
, writer(new Writer(configure))
{
}

void Downloader::download()
{
	reader.get_http();
	reader.read_from_host(target_url);
	reader.close_connection();
	reader.accept_all();
	writer.write(reader.get_stream_buffer());
}

#endif