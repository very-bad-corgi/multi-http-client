#include "curlmanager.h"
#include "logmanager.h"

#include <curl/curl.h>

#include <boost/algorithm/cxx11/any_of.hpp>
#include <memory>
#include <array>

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

std::optional<std::string> CurlManager::sendHttpRequest(const std::string &url)
{
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> curl(
        curl_easy_init(), &curl_easy_cleanup
    );

    CURLcode curlCode;
    long httpStatusCode;
    auto successStatusCodes = std::to_array({ 200, 201, 202 });

    std::string bodyResponse;

    if (curl.get())
    {
        LogManager::log("Отправка запроса на - "+url, LogType::DBG);

        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &bodyResponse);
        curlCode = curl_easy_perform(curl.get());

        curl_easy_getinfo(curl.get(), CURLINFO_RESPONSE_CODE, &httpStatusCode);
        LogManager::log("CURLcode: " + std::to_string(static_cast<int>(curlCode)) + ", httpStatus: " + std::to_string(static_cast<int>(httpStatusCode)), LogType::DBG);

        if (curlCode == CURLE_OK && boost::algorithm::any_of_equal(successStatusCodes, httpStatusCode))
        {
            LogManager::log("Запрос выполнен успешно! Размер тела ответа: "+std::to_string(bodyResponse.size())+" байт", LogType::DBG);
            return bodyResponse;
        }
        else if(curlCode == CURLE_OK)
        {
            // Вернулся статус 400 / 500
            LogManager::log("Запрос завершился ошибкой, httpStatusCode: " + std::to_string(static_cast<int>(httpStatusCode)), LogType::ERR);
        }
        else
        {
            // Либо url некорректен, нет сети, не резолвится dns, либо ресурс недоступен
            LogManager::log("Запрос завершился ошибкой - "+std::string(curl_easy_strerror(curlCode)), LogType::ERR);
        }
    } else {
        LogManager::log("The operating system has not allocated memory for CURL", LogType::ERR);
    }

    return std::nullopt;
}
