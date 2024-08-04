// CurlManager_H
#pragma once

#include <string>
#include <optional>

class CurlManager
{
public:
    CurlManager();
    ~CurlManager();

    //size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::optional<std::string> sendHttpRequest(const std::string &url);
};
