// NetworkFileHandler_h
#pragma once

#include <nlohmann/json_fwd.hpp>

class NetworkFileHandler
{
public:
    bool downloadCertificates(const nlohmann::json &config, const std::string &cokFilePath, const std::string &crlFilePath);

};
