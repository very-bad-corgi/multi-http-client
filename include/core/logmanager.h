// LOGMANAGER_H
#pragma once

#include <nlohmann/json_fwd.hpp>

#include <string>
#include <unordered_map>

enum class LogType {
    DBG,
    INF,
    WRN,
    ERR
};

class LogManager
{
public:
    LogManager() = delete;
    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    LogManager(LogManager&&) = delete;
    LogManager& operator=(LogManager&&) = delete;

    static void init(const nlohmann::json& config);
    static void log(const std::string& message, LogType type = LogType::INF);

private:
    static std::string convertToString(LogType level);

    static std::unordered_map<std::string, bool> _need_logged;
};

