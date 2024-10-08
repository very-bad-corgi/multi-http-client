#include "constants.h"
#include "logmanager.h"
#include "networkfilehandler.h"
#include "utils.h"
#include "configmanager.h"

#include <nlohmann/json.hpp>

int main(int argc, char *argv[])
{
    Utils::init(argv[0]);

    auto configSettings = ConfigManager().parseConfig(Utils::getPath(Dir::Config, CONFIG::FILE::SETTINGS));
    LogManager::init(configSettings);

    Utils::viewCppStandartUsing();
    Utils::viewCppCompilerUsing();

    LogManager::log("Welcome to simple pet project 'multi-http-client'");

    auto configChainOwn = ConfigManager().parseConfig(Utils::getPath(Dir::Config, CONFIG::FILE::CHAIN_OWN));
    auto configChainNces = ConfigManager().parseConfig(Utils::getPath(Dir::Config, CONFIG::FILE::CHAIN_NCES));

    NetworkFileHandler().downloadCertificates(configChainOwn, Utils::getPath(Dir::Certs, CERTS::FILE::FULLCHAIN_OWN), Utils::getPath(Dir::Certs, CERTS::FILE::CA_REVOKED_OWN));
    NetworkFileHandler().downloadCertificates(configChainNces, Utils::getPath(Dir::Certs, CERTS::FILE::FULLCHAIN_NCES), Utils::getPath(Dir::Certs, CERTS::FILE::CA_REVOKED_NCES));

    return EXIT_SUCCESS;
}
