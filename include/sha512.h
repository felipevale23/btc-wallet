// include/sha512.h
#ifndef SHA512_H
#define SHA512_H

#include <stdint.h>
#include <stddef.h>

void sha512(const uint8_t *message, size_t message_len, uint8_t *digest);

void hmac_sha512(const uint8_t *key, size_t key_len, const uint8_t *message, size_t message_len, uint8_t *mac);

void pbkdf2_hmac_sha512(const uint8_t *password, size_t password_len, const uint8_t *salt, size_t salt_len, uint32_t iterations, uint8_t *out, size_t out_len);

#endif