#ifndef WRITER_H_
#define WRITER_H_

#include <string>
#include <fstream>

class Writer
{
public:
	inline explicit Writer(const std::string& file_name);
	inline explicit Writer(const Configure& configure);
	Writer(const Writer& other) = delete;
	Writer(Writer&& other) = default;
	virtual inline ~Writer();

	virtual inline void write(std::streambuf* stream_buffer);
private:
	std::fstream writer;
};

Writer::Writer(const std::string& file_name)
{
	writer.open(file_name,
			std::fstream::in | std::fstream::out | std::fstream::app);
}

Writer::Writer(const Configure& configure)
{
	writer.open(configure.get_output_name(),
			std::fstream::in | std::fstream::out | std::fstream::app);
}

void Writer::write(std::streambuf* stream_buffer)
{
	writer << stream_buffer;
}

Writer::~Writer()
{
	writer.close();
}

#endif