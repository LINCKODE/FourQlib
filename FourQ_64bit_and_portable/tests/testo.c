//
// Created by linckode on 3/22/24.

#include <stdio.h>
#include <string.h>

#include "../FourQ_api.h"


void readFileToBuffer(const char *filePath, char *buffer, const int count) {
    FILE *file = fopen(filePath, "r");

    fread(buffer, count, 1, file);

    fclose(file);
}

void writeBufferToFile(const char *path, const char *buffer, const int count) {
    FILE *file = fopen(path, "w");

    fwrite(buffer, count, 1, file);
    fclose(file);
}

void generateAndSaveKeys(const char *private, const char *public) {
    writeBufferToFile("KEYS/private.fourq", private, 32);
    writeBufferToFile("KEYS/public.fourq", public, 64);
}

void loadKeys(char *private, char *public) {
    readFileToBuffer("KEYS/private.fourq", private, 32);
    readFileToBuffer("KEYS/public.fourq", public, 64);
}

int array_is_equal(const void *array_one, void *array_two,
                    const size_t elem_size, const size_t elem_count)
{
    return memcmp(array_one, array_two, elem_count * elem_size) == 0;
}


int main() {
    printf("FourQ function testing.\n");

    printf("Generating keypair...\n");

    char SecretKey[32], PublicKey[64];

    loadKeys(SecretKey, PublicKey);

    char SharedSecret[32];

    readFileToBuffer("KEYS/shared.fourq", SharedSecret, 32);

    char GeneratedSecret[32];

    SecretAgreement(SecretKey, PublicKey, GeneratedSecret);
    printf("Checks out: >%d<\n", array_is_equal(SharedSecret, GeneratedSecret, 32, 1));



}
