// CryptoOperations_h
#pragma once

#include <string>

class CryptoOperations
{
public:
    static CryptoOperations& getInstance()
    {
        static CryptoOperations instance;
        return instance;
    }

    ~CryptoOperations();
    CryptoOperations(const CryptoOperations& other) = delete;
    void operator=(const CryptoOperations& other) = delete;

private:
    CryptoOperations();

public:
    int hash(const std::string& alg_id, const std::string &data, std::string &result);

};


