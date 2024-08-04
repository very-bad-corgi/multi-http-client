#include "curlmanager.h"

#include <curl/curl.h>
#include <iostream>

CurlManager::CurlManager()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CurlManager::~CurlManager()
{
    curl_global_cleanup();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void CurlManager::sendHttpRequest(const std::string &url)
{
    CURL* curl;
    CURLcode curlCode;
    std::string readBuffer;

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curlCode = curl_easy_perform(curl);

        if(curlCode == CURLE_COULDNT_CONNECT) {
            std::cerr << "service '"+url+"' is unavailable" << std::endl;
        }

        long httpStatusCode;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode);
        std::cout << " CURLcode: " << curlCode << ", httpStatus: " << httpStatusCode << std::endl;

        if (curlCode != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(curlCode) << std::endl;
        }
        else
        {
            std::cout << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }




}
