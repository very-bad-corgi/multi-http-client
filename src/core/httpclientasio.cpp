#include "httpclientasio.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>

HttpClientAsio::HttpClientAsio() {}

std::string HttpClientAsio::sendHttpRequest()
{
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "8080");

    // Создание сокета
    boost::asio::ip::tcp::socket socket(ioc);

    // Установка соединения
    boost::asio::connect(socket, endpoints);

    // Отправка HTTP-запроса
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET / HTTP/1.1\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    // Отправка запроса
    boost::asio::write(socket, request);

    // Получение и вывод ответа
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;

    //std::cout << "http_version:  " << http_version << '\n';

    unsigned int status_code;
    response_stream >> status_code;

    std::string status_message;
    std::getline(response_stream, status_message);

    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
        std::cout << "Произошла ошибка при чтении ответа." << std::endl;
        return "Произошла ошибка при чтении ответа.";
    }

    std::string header;
    while (std::getline(response_stream, header) && header != "\r") {}

    // Вывод тела ответа
    std::string response_body;
    if (response.size() > 0) {
        std::ostringstream oss;
        oss << &response;
        response_body = oss.str();
    }

    return "";
}
