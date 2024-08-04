#include <iostream>
// #include <boost/asio.hpp>
// #include <boost/beast/http.hpp>

#include "curlmanager.h"
#include <httpclientasio.h>

int main()
{

    // try {

    // } catch()
    // {

    // }

    CurlManager().sendHttpRequest("https://nces.by/wp-content/uploads/certificates/pki/ruc1.cer");

    std::cout << "Запрос выполнен успешно!" << std::endl;
    //std::cout << "Тело ответа: " << response_body << std::endl;

    return 0;
}
