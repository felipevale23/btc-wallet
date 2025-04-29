// include/bip39.h
#ifndef bip39_H
#define bip39_H

#define MAX_WORD_LENGTH 16

#include <stdint.h>
#include <stddef.h>

// Protótipo da função
int valid_entropy_bits(uint16_t entropy_bits);
uint8_t entropy_bytes(uint16_t entropy_bits);
uint8_t checksum_bits(uint16_t entropy_bits);
uint16_t total_bits(uint16_t entropy_bits);
uint16_t total_words(uint16_t entropy_bits);
void load_wordlist(const char *filename, char words[2048][MAX_WORD_LENGTH]);
void generate_entropy(uint8_t *entropy, uint8_t len);
int get_bit(uint8_t *data, int bit);
void entropy_to_mnemonic(uint8_t *entropy, uint16_t entropy_bits, char wordlist[2048][MAX_WORD_LENGTH]);

#endif