#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_hex(uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void clear_console()
{
// Para sistemas Linux ou macOS
#if defined(__linux__) || defined(__APPLE__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    // Para sistemas Windows
    system("cls");
#endif
}