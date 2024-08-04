#include "configmanager.h"
#include "logmanager.h"

#include <nlohmann/json.hpp>

#include <fstream>

void ConfigManager::viewConfig(const nlohmann::json& config)
{
    for (auto& [key, value] : config.items()) {
        LogManager::log("Object: " + key);

        if (value.is_object())
        {
            for (auto& [subkey, subvalue] : value.items()) {
                LogManager::log("  Подключ: " + subkey + ", Значение: " + std::string(subvalue));
            }
        }
        else if (value.is_array())
        {
            for (const auto& element : value) {
                LogManager::log("  Элемент массива: " + std::string(element));
            }
        }
        else
        {
            LogManager::log("  Значение: " + std::string(value));
        }
    }
}

nlohmann::json ConfigManager::parseConfig(const std::string& configFilePath)
{
    nlohmann::json config;

    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        LogManager::log("failed to open config file by path - "+configFilePath, LogType::ERR);
        return config;
    }

    configFile >> config;

    return config;
}
