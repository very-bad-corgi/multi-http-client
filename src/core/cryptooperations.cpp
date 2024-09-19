#include <cryptooperations.h>

#include <openssl/evp.h>

#include <memory>

using EVP_MD_CTX_PTR = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>;

int CryptoOperations::hash(const std::string& alg_id, const std::string &data, std::string &result)
{
    EVP_MD_PTR md(EVP_get_digestbyname(alg_id.c_str()), EVP_MD_CTX_free);
    const EVP_MD* md = EVP_get_digestbyname(alg_id.c_str());
    if(!md){
        return ERR::CO_FAILED_TO_GET_DIGEST;
    }
    uint siz = static_cast<uint>(EVP_MD_size(md));
    EVP_MD_CTX_PTR ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);
    if(!ctx){
        return ERR::NO_MEMORY;
    }
    EVP_MD_CTX_init(ctx.get());
    if(!EVP_DigestInit(ctx.get(), md)){
        return ERR::CO_DIGEST_INIT_FAILED;
    }
    if(!EVP_DigestUpdate(ctx.get(), data.data(), static_cast<size_t>(data.size()))){
        return ERR::CO_DIGEST_UPDATE_FAILED;
    }
    result.resize(static_cast<int>(siz));
    if(!EVP_DigestFinal(ctx.get(), reinterpret_cast<uchar*>(result.data()), &siz)){
        return ERR::CO_DIGEST_FINAL_FAILED;
    }
    return ERR::SUCCESS;
}
