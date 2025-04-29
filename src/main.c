#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bip39.h"
#include "sha256.h"
#include "utils.h"

#define VERSION "0.1.0"

int main(int argc, char *argv[])
{
    clear_console();
    printf("Bitcoin Wallet C - Version %s\n\n", VERSION);

    if (argc < 3)
    {
        printf("Uso: %s <128|160|192|224|256> <-en|-br>\n", argv[0]);
        return 1;
    }

    int entropy_bits = atoi(argv[1]);
    printf("Parsed entropy_bits: %d\n", valid_entropy_bits(entropy_bits));

    if (!valid_entropy_bits(entropy_bits))
    {
        printf("Por favor, insira a quantidade de bits de entropia:\n");
        printf("(Apenas valores válidos: 128, 160, 192, 224 ou 256 — exigido pelo padrão BIP-39)\n");
        return 1;
    }

    const char *filename = NULL;
    if (strcmp(argv[2], "-en") == 0)
    {
        filename = "./wordlist/wordlist_en.txt";
    }
    else if (strcmp(argv[2], "-br") == 0)
    {
        filename = "./wordlist/wordlist_br.txt";
    }
    else
    {
        fprintf(stderr, "Invalid option. Use -en for English or -br for Portuguese.\n");
        return 1;
    }

    printf("%d bits!\n\n", entropy_bits);
    printf("Entropy Bytes: %d\n", entropy_bytes(entropy_bits));
    printf("Checksum bits: %d\n", checksum_bits(entropy_bits));
    printf("Total bits: %d\n", total_bits(entropy_bits));
    printf("Number of words: %d\n\n", total_words(entropy_bits));

    // Carrega a wordlist
    char wordlist[2048][MAX_WORD_LENGTH];
    load_wordlist(filename, wordlist);

    // Gera a entropia
    uint8_t entropy[entropy_bytes(entropy_bits)];
    generate_entropy(entropy, entropy_bytes(entropy_bits));

    // Converte a entropia para mnemônico
    entropy_to_mnemonic(entropy, entropy_bits, wordlist);

    return 0;
}