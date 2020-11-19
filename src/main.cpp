#include "Downloader.h"

int main(int argc, char* argv[])
{
    Downloader downloader("www.martinbroadhurst.com", "http", "result.html");
    downloader.write();
}