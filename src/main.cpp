#include "Downloader.h"

#include "Configure.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
		return -1;

	Configure configure(argv[1], argv[2]);
	Downloader downlodaer(configure);
	downlodaer.write();
	return 0;
}