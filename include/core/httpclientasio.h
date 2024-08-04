// HTTPCLIENTASIO_H
#pragma once

#include <optional>
#include <string>

class HttpClientAsio
{
public:
    HttpClientAsio();

    std::string sendHttpRequest();
};
