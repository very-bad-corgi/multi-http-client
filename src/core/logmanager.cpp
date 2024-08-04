#include "logmanager.h"
#include "constants.h"

#include <fmt/core.h>
#include <fmt/chrono.h>

#include <nlohmann/json.hpp>

#include <ctime>

std::unordered_map<std::string, bool> LogManager::_need_logged;

void LogManager::init(const nlohmann::json& config)
{
    for (auto& [key, value] : config.at(CONFIG::FILE::SETTINGS_BLOCKS::LOGGING).items())
    {
        if(_need_logged.contains(key))
            continue;

        _need_logged[key] = value;
    }
}

std::string LogManager::convertToString(LogType level)
{
    switch (level) {
    case LogType::DBG:
        return "DBG";
    case LogType::INF:
        return "INF";
    case LogType::WRN:
        return "WRN";
    case LogType::ERR:
        return "ERR";
    default:
        return "UND";
    }
}

void LogManager::log(const std::string& message, LogType type)
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto local_time = *std::localtime(&time);

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    if(_need_logged.at(convertToString(type)))
    {
        fmt::print("{:%d.%m.%Y %H:%M:%S}.{:03d} [ {} ] {}\n", local_time, static_cast<int>(ms.count()), convertToString(type), message);
    }
}


