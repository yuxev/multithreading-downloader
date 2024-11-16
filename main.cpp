#include "download.hpp"

mutex       mtx;


#define PRINT_ONCE()                \
    do {                            \
        static bool done = false;   \
        if (!done)                  \
        {                           \
            printColoredText("NOTE:", "yellow", false); \
            printColoredText("you can enter more than file, when done enter D", "", true); \
            done = true;            \
        }                           \
    } while (0)

void printColoredText(const std::string& text, const std::string& color, bool s)
{
    std::string colorCode;

    if (color == "red")
        colorCode = "\033[31m";
    else if (color == "green")
        colorCode = "\033[32m";
    else if (color == "yellow")
        colorCode = "\033[33m";
    else if (color == "blue")
        colorCode = "\033[34m";
    else if (color == "magenta")
        colorCode = "\033[35m";
    else if (color == "cyan")
        colorCode = "\033[36m";
    else if (color == "white")
        colorCode = "\033[37m";
    else
        colorCode = "\033[0m";

    cout << colorCode << text << "\033[0m";
    if (s)
        cout << endl;
}

std::string extractFileName(const std::string& url)
{
    size_t pos = url.find_last_of("/");

    if (pos != std::string::npos)
        return url.substr(pos + 1);
    else
        return "defaultname.txt"; 
}

size_t writeData(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    return (fwrite(ptr, size, nmemb, stream));
}

void    downloadFile(string fileUrl)
{
    CURL* curl;
    FILE* file;
    CURLcode res;
    string  outputFilename = extractFileName(fileUrl);
    curl = curl_easy_init();
    if (curl)
    {
        file = fopen(outputFilename.c_str(), "wb");
        if (!file)
            { std::cerr << "Failed to open file for writing: " << outputFilename << std::endl; return; }

        curl_easy_setopt(curl, CURLOPT_URL, fileUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << "Download successful: " << outputFilename << std::endl;

        fclose(file);
        curl_easy_cleanup(curl);
    }
}

int main()
{
    fileDownload    fdownld;
    while(true)
    {
        printColoredText("Enter Url file", "green", true);
        PRINT_ONCE();
        string  fileUrl;
        cin >> fileUrl;
        cin.ignore();
        if (fileUrl == "D")
        {
            printColoredText("choose the path where u want to download this file (optional):", "magenta", true);
            string  path;
            getline(cin, path);
            if (filesystem::is_directory(path) || path == "")
            {
                chdir(path.c_str());
                size_t i = 0;
                while(i < fdownld.getNumOfFiles())
                    fdownld.threads.emplace_back(downloadFile, fdownld.getFileUrl(i++));
                
                i = 0;
                int active_threads = fdownld.getNumOfFiles();
                while (active_threads > 0)
                {
                    if (fdownld.threads[i].joinable())
                    {
                        fdownld.threads[i++].join();
                        active_threads--;
                    }
                }
                fdownld.threads.clear();
                fdownld.clearFile();
            }
            else
            {
                printColoredText("wrong path , too lazy to handle this kind of errors i can't create new directory for u or whatever , try again -_-", "red", 1);
                path.clear();
            }
        }
        else
            fdownld.addFileUrl(fileUrl);
    }
    return 0;
}
