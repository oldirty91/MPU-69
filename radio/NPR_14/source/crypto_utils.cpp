#include "crypto_utils.h"
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>

// Default 256-bit key and 128-bit IV
static uint8_t crypto_key[32];
static uint8_t crypto_iv[16];

// Function to handle errors
void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

// Function to calculate CRC-16
uint16_t calculate_crc16(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// Function to generate a random crypto key
void generate_crypto_key(uint8_t *key, size_t key_len) {
    // Seed the random number generator
    srand(time(NULL));

    // Fill the key buffer with random bytes
    for (size_t i = 0; i < key_len; i++) {
        key[i] = rand() % 256;
    }
}

// Function to encrypt data
void encrypt(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t *ciphertext_len)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len_temp;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) handleErrors();
    ciphertext_len_temp = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len_temp += len;

    EVP_CIPHER_CTX_free(ctx);

    *ciphertext_len = ciphertext_len_temp;
}

// Function to decrypt data
void decrypt(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext, size_t *plaintext_len)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len_temp;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) handleErrors();
    plaintext_len_temp = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
    plaintext_len_temp += len;

    EVP_CIPHER_CTX_free(ctx);

    *plaintext_len = plaintext_len_temp;
}

// Function to set the crypto key
void set_crypto_key(const uint8_t *new_key, size_t key_len) {
    if (key_len == 32) {
        memcpy(crypto_key, new_key, key_len);
    } else {
        fprintf(stderr, "Invalid key length: must be 256 bits.\n");
    }
}

// Function to set the crypto IV
void set_crypto_iv(const uint8_t *new_iv, size_t iv_len) {
    if (iv_len == 16) {
        memcpy(crypto_iv, new_iv, iv_len);
    } else {
        fprintf(stderr, "Invalid IV length: must be 128 bits.\n");
    }
}

// Initialize default key and IV
void initialize_default_crypto_params() {
    const char default_key[33] = "01234567890123456789012345678901";
    const char default_iv[17] = "0123456789012345";

    memcpy(crypto_key, default_key, 32);
    memcpy(crypto_iv, default_iv, 16);
}

// Call initialize function at startup
__attribute__((constructor))
void initialize_crypto() {
    initialize_default_crypto_params();
}