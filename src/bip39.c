// BIP-39
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sha256.h"
#include "bip39.h"

int valid_entropy_bits(uint16_t entropy_bits)
{
    return (entropy_bits == 128 || entropy_bits == 160 ||
            entropy_bits == 192 || entropy_bits == 224 ||
            entropy_bits == 256);
}

uint8_t entropy_bytes(uint16_t entropy_bits)
{
    return (entropy_bits) / 8; // Arredonda para o byte mais próximo
}

uint8_t checksum_bits(uint16_t entropy_bits)
{
    if (!valid_entropy_bits(entropy_bits))
    {
        return 0;
    }
    uint8_t checksum = (uint8_t)(entropy_bits / 32);
    return checksum;
}

uint16_t total_bits(uint16_t entropy_bits)
{
    if (!valid_entropy_bits(entropy_bits))
    {
        return 0;
    }
    uint16_t total = entropy_bits + checksum_bits(entropy_bits);
    return total;
}

uint16_t total_words(uint16_t entropy_bits)
{
    if (!valid_entropy_bits(entropy_bits))
    {
        return 0;
    }
    return total_bits(entropy_bits) / 11;
}

void load_wordlist(const char *filename, char words[2048][MAX_WORD_LENGTH])
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Failed to open wordlist file");
        exit(1);
    }
    for (int i = 0; i < 2048; i++)
    {
        if (fscanf(fp, "%15s", words[i]) != 1)
        {
            fprintf(stderr, "Error reading word %d from %s\n", i, filename);
            fclose(fp);
            exit(1);
        }
    }
    fclose(fp);
}

const char *wordlist[2048] = {
    "abandon", "ability", "able", "about", "above", "absent", "absorb", "abstract", "absurd", "abuse",
    "access", "accident", "account", "accuse", "achieve", "acid", "acoustic", "acquire", "across", "act",
    "action", "actor", "actress", "actual", "adapt", "add", "addict", "address", "adjust", "admit",
    "adult", "advance", "advice", "aerobic", "affair", "afford", "afraid", "again", "age", "agent",
    "agree", "ahead", "aim", "air", "airport", "aisle", "alarm", "album", "alcohol", "alert",
    // [... completar com as 2048 palavras reais ...]
};

// Função para gerar entropy aleatória
void generate_entropy(uint8_t *entropy, uint8_t len)
{
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL)
    {
        perror("fopen");
        exit(1);
    }

    size_t bytes_read = fread(entropy, 1, len, fp);
    if (bytes_read != len) // Verifica se a quantidade de bytes lidos é igual ao esperado.
    {
        perror("fread");
        fclose(fp);
        exit(1);
    }

    fclose(fp);
}

int get_bit(uint8_t *data, int bit)
{
    int byte_index = bit / 8;
    int bit_index = 7 - (bit % 8);
    return (data[byte_index] >> bit_index) & 1;
}

void entropy_to_mnemonic(uint8_t *entropy, uint16_t entropy_bits, char wordlist[2048][MAX_WORD_LENGTH])
{
    printf("Creating %d Mnemonics words\n", total_words(entropy_bits)); // Adicionado para depurar

    uint8_t hash[32];
    const int len = entropy_bytes(entropy_bits);
    sha256(entropy, len, hash);
    uint8_t data[len + 1];
    memcpy(data, entropy, len);
    data[len] = hash[0]; // append first byte of hash (checksum bits)

    int total = total_bits(entropy_bits); // Verifique aqui também a função `total_bits`
    for (int i = 0; i < total; i += 11)
    {
        int index = 0;
        for (int j = 0; j < 11; j++)
        {
            index <<= 1;
            index |= get_bit(data, i + j);
        }
        printf("%s ", wordlist[index]); // Printa a palavra correspondente
    }
    printf("\n");
}