#include <memory>

#include "Downloader.h"

#include "Configure.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
		return -1;

	Configure configure(argv[1], argv[2]);
	std::unique_ptr<Reader> reader_unique_pointer(new Reader(configure));
	std::unique_ptr<Writer> writer_unique_pointer(new Writer(configure));
	Downloader downlodaer(std::move(reader_unique_pointer),
			std::move(writer_unique_pointer));
	downlodaer.download();

	return 0;
}