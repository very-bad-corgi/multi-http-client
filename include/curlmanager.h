#ifndef CurlManager_H
#define CurlManager_H

#include <string>

class CurlManager
{
public:
    CurlManager();
    ~CurlManager();

    //size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    void sendHttpRequest(const std::string &url);
};

#endif // CurlManager_H
