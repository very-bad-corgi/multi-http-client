// CONSTANTS_H
#pragma once

namespace CONFIG::TYPE
{
    inline constexpr char DEV[] = "dev/";
    inline constexpr char RELEASE[] = "release/";
}

namespace CONFIG::FILE
{
    inline constexpr char SETTINGS[] = "settings.json";
    namespace SETTINGS_BLOCKS
    {
        inline constexpr char LOGGING[] = "logging";
    }

    inline constexpr char CHAIN_OWN[] = "chain-own.json";
    inline constexpr char CHAIN_NCES[] = "chain-nces.json";
}

namespace CERTS::FILE
{
    inline constexpr char FULLCHAIN[] = "fullchain.pem";
    inline constexpr char CA_REVOKED[] = "ca-revoked.crl";

    inline constexpr char FULLCHAIN_NCES[] = "fullchain.nces.pem";
    inline constexpr char CA_REVOKED_NCES[] = "ca-revoked.nces.crl";
    inline constexpr char FULLCHAIN_OWN[] = "fullchain.own.pem";
    inline constexpr char CA_REVOKED_OWN[] = "ca-revoked.own.crl";
}
