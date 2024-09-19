#include "curlmanager.h"
#include "logmanager.h"

#include "networkfilehandler.h"

#include <nlohmann/json.hpp>

#include <string>
#include <fstream>
#include <cstdio>

bool NetworkFileHandler::downloadCertificates(const nlohmann::json& config, const std::string &cokFilePath, const std::string &crlFilePath)
{
    std::remove(crlFilePath.c_str());
    std::remove(cokFilePath.c_str());

    for (auto& [key, value] : config.items()) {
        LogManager::log("Chain: " + key, LogType::DBG);

        for (auto& [subkey, subvalue] : value.items()) {
            if(subvalue.empty() || subvalue == "")
                continue;

            LogManager::log("  Key: " + subkey + ", Value: " + std::string(subvalue), LogType::DBG);

            if(auto certValue = CurlManager::getInstance().sendHttpRequest(std::string(subvalue)); certValue)
            {
                std::string filepath = subkey.ends_with("crl") ? crlFilePath : cokFilePath;

                std::ofstream file(filepath, std::ios::app);
                if (!file.is_open()) {
                    LogManager::log("Не удалось открыть файл для записи: "+filepath, LogType::ERR);
                    continue;
                }
                file << certValue.value();
                LogManager::log(subkey+" успешно записан в "+filepath);
            }
            else
            {
                LogManager::log(std::string(__FUNCTION__)+": Возникла ошибка при скачивании файла "+subkey+" из "+key+" по ссылке "+std::string(subvalue), LogType::ERR);
            }
        }
    }

    return EXIT_SUCCESS;
}
