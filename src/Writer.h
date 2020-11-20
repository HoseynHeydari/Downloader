#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include <fstream>

#include <boost/asio.hpp>

class Writer
{
public:
	explicit Writer(const std::string& file_name);
	~Writer();
	void write(boost::asio::ip::tcp::iostream& content_stream);
private:
	std::fstream writer;
};

Writer::Writer(const std::string& file_name)
{
	writer.open(file_name,
			std::fstream::in | std::fstream::out | std::fstream::app);
}

void Writer::write(boost::asio::ip::tcp::iostream& content_stream)
{
	content_stream.flush();
	writer << content_stream.rdbuf();
}

Writer::~Writer()
{
	writer.close();
}

#endif