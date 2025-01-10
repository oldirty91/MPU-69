#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <stdint.h>
#include <stddef.h>

// Function prototypes
uint16_t calculate_crc16(const uint8_t *data, size_t length);
void encrypt(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t *ciphertext_len);
void decrypt(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext, size_t *plaintext_len);
void set_crypto_key(const uint8_t *new_key, size_t key_len);
void set_crypto_iv(const uint8_t *new_iv, size_t iv_len);

#endif // CRYPTO_UTILS_H