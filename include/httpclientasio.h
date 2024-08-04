#ifndef HTTPCLIENTASIO_H
#define HTTPCLIENTASIO_H

#include <optional>
#include <string>

class HttpClientAsio
{
public:
    HttpClientAsio();

    std::optional<std::string> sendHttpRequest();
};

#endif // HTTPCLIENTASIO_H
