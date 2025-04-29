#include "sha256.h"
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <stdint.h>

void sha256(const uint8_t *data, size_t len, uint8_t *hash)
{
    // Cria um contexto para o cálculo do hash
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para o contexto do hash.\n");
        return;
    }

    // Inicializa o contexto com SHA-256
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1)
    {
        fprintf(stderr, "Erro ao inicializar o contexto do hash.\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // Atualiza o contexto com os dados de entrada
    if (EVP_DigestUpdate(ctx, data, len) != 1)
    {
        fprintf(stderr, "Erro ao atualizar o hash.\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // Finaliza o hash e armazena o resultado
    if (EVP_DigestFinal_ex(ctx, hash, NULL) != 1)
    {
        fprintf(stderr, "Erro ao finalizar o cálculo do hash.\n");
        EVP_MD_CTX_free(ctx);
        return;
    }

    // Libera o contexto
    EVP_MD_CTX_free(ctx);
}