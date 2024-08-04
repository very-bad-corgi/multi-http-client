// ConfigManager_h
#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

struct NcesChainConfig {
    struct Actual {
        std::string kuc;
        std::string kuc_crl;
        std::string ruc;
        std::string rur_crl;
    } actual;

    struct Old {
        std::string kuc;
        std::string kuc_crl;
        std::string ruc;
        std::string ruc_new;
        std::string rur_crl;
    } old;
};
struct OwnChainConfig {
    std::string root;
    std::string root_crl;
    std::string subca;
    std::string subca_crl;
};

class ConfigManager
{
public:
    nlohmann::json parseConfig(const std::string& config);

    void viewConfig(const nlohmann::json& config);

};
