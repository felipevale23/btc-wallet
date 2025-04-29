// SHA 512
#include "sha512.h"
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <string.h>

void sha512(const uint8_t *message, size_t message_len, uint8_t *digest)
{
    SHA512(message, message_len, digest);
}

void hmac_sha512(const uint8_t *key, size_t key_len, const uint8_t *message, size_t message_len, uint8_t *mac)
{
    unsigned int len = 64; // SHA-512 gera 64 bytes
    HMAC(EVP_sha512(), key, key_len, message, message_len, mac, &len);
}

void pbkdf2_hmac_sha512(const uint8_t *password, size_t password_len, const uint8_t *salt, size_t salt_len, uint32_t iterations, uint8_t *out, size_t out_len)
{
    PKCS5_PBKDF2_HMAC((const char *)password, password_len, salt, salt_len, iterations, EVP_sha512(), out_len, out);
}