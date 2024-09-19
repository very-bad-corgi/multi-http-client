// CurlManager_H
#pragma once

#include <string>
#include <optional>

class CurlManager
{
public:
    static CurlManager& getInstance()
    {
        static CurlManager instance;
        return instance;
    }

    ~CurlManager();
    CurlManager(const CurlManager& other) = delete;
    void operator=(const CurlManager& other) = delete;

private:
    CurlManager();

public:

    //size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::optional<std::string> sendHttpRequest(const std::string &url);
};
