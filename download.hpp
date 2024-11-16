#pragma once

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <curl/curl.h>

using namespace std;


class fileDownload {
    private:
        vector<string>  fileUrl;
    public:
        fileDownload();

        vector<thread> threads;

        void    addFileUrl(string);
        void    clearFile();
        size_t  getNumOfFiles();
        string  getFileUrl(int);
        ~fileDownload();
};