
#include "download.hpp"

fileDownload::fileDownload() {}

void    fileDownload::addFileUrl(string url)
{
    fileUrl.push_back(url);
}

size_t     fileDownload::getNumOfFiles()
{
    return (fileUrl.size());
}

string    fileDownload::getFileUrl(int i)
{
    return (fileUrl[i]);
}

void    fileDownload::clearFile()
{
    fileUrl.clear();
}



fileDownload::~fileDownload() {}