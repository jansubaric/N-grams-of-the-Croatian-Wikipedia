#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FNAME "combined.txt"

#define BIGRAM_LEN      2
#define TRIGRAM_LEN     3
#define QUADGRAM_LEN    4
#define QUINTGRAM_LEN   5

#define ALPHABET_LEN ('z' - 'a' + 1)

struct bigram {
    /*"2D" polje za bigrame*/
    unsigned long long (*perms)[ALPHABET_LEN];
    /* broj bigrama*/
    unsigned long long n;
};

struct trigram {
    /*"3D" polje za trigrame*/
    unsigned long long (*perms)[ALPHABET_LEN][ALPHABET_LEN];
    unsigned long long n;
};

struct quadgram {
    /* "4D" polje za kvandgrame */
    unsigned long long (*perms)[ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN];
    unsigned long long n;
};

struct quintgram {
    /* "5D" polje za kvintgrame */
    unsigned long long (*perms)[ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN];
    unsigned long long n;
};

/* 
 *
 * funkcija za citanje iz datoteke
 *
 */
char* read_file(char *filename)
{
   char *buffer = NULL;
   unsigned long long string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler) {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       read_size = fread(buffer, sizeof(char), string_size, handler);

       buffer[string_size] = '\0';

       if (string_size != read_size) {
           free(buffer);
           buffer = NULL;
       }

       fclose(handler);
    }

    return buffer;
}

void print_bigram(struct bigram bi)
{
    puts("BIGRAM:");
    for (size_t i = 0; i < ALPHABET_LEN; i++) {
        for (size_t j = 0; j < ALPHABET_LEN; j++) 
            printf("%c%c: %.4f ", i+'a', j+'a', bi.perms[i][j] / (double)bi.n);
        putchar('\n');
    }
}

void print_trigram(struct trigram tri)
{
    puts("TRIGRAM:");
    for (size_t i = 0; i < ALPHABET_LEN; i++) {
        for (size_t j = 0; j < ALPHABET_LEN; j++) {
            for (size_t k = 0; k < ALPHABET_LEN; k++) 
                printf("%c%c%c: %.4f ", i+'a', j+'a', k+'a', tri.perms[i][j][k] / (double)tri.n);
            putchar('\n');
        }
        putchar('\n');
    }
}

void print_quadgram(struct quadgram quad)
{
    puts("QUADGRAM:");
    for (size_t i = 0; i < ALPHABET_LEN; i++) {
        for (size_t j = 0; j < ALPHABET_LEN; j++) {
            for (size_t k = 0; k < ALPHABET_LEN; k++) {
                for (size_t l = 0; l < ALPHABET_LEN; l++) 
                    printf("%c%c%c%c: %.8lf ", i+'a', j+'a', k+'a', l+'a', quad.perms[i][j][k][l] / (double)quad.n);
                putchar('\n');
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

void print_quintgram(struct quintgram quint)
{
    puts("QUINTGRAM:");
    for (size_t i = 0; i < ALPHABET_LEN; i++) {
        for (size_t j = 0; j < ALPHABET_LEN; j++) {
            for (size_t k = 0; k < ALPHABET_LEN; k++) {
                for (size_t l = 0; l < ALPHABET_LEN; l++) {
                    for (size_t m = 0; m < ALPHABET_LEN; m++) 
                    printf("%c%c%c%c%c: %.8f ", i+'a', j+'a', k+'a', l+'a', m+'a', quint.perms[i][j][k][l][m] / (double)quint.n);
                    putchar('\n');
                }
                putchar('\n');
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

/*
 *
 * racunanje broja kombinacija i ispis
 *
 */
void print_bigram_to_quintgram(char *buf)
{
    struct bigram bi = {};
    /* alociranje memorije */
    unsigned long long bi_sz = sizeof(unsigned long long[ALPHABET_LEN][ALPHABET_LEN]);
    bi.perms = malloc(bi_sz);
    memset(bi.perms, 0, bi_sz);

    struct trigram tri = {};
    unsigned long long tri_sz = sizeof(unsigned long long[ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN]);
    tri.perms = malloc(tri_sz);
    memset(tri.perms, 0, tri_sz);

    struct quadgram quad = {};
    unsigned long long quad_sz = sizeof(unsigned long long[ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN]);
    quad.perms = malloc(quad_sz);
    memset(quad.perms, 0, quad_sz);

    struct quintgram quint = {};
    unsigned long long quint_sz = sizeof(unsigned long long[ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN][ALPHABET_LEN]);
    quint.perms = malloc(quint_sz);
    memset(quint.perms, 0, quint_sz);

    unsigned long long buflen = strlen(buf);


    for (unsigned long long i = 0; i < buflen; i++) {

        if (i + BIGRAM_LEN - 1 < buflen
            && islower(buf[i]) && islower(buf[i+1])) {
            bi.perms[buf[i]-'a'][buf[i+1]-'a']++;
            bi.n++;
        }
        else 
            continue;

        if (i + TRIGRAM_LEN - 1 < buflen
            && islower(buf[i+2])) {
            tri.perms[buf[i]-'a'][buf[i+1]-'a'][buf[i+2]-'a']++;
            tri.n++;
        }
        else
            continue;

        if (i + QUADGRAM_LEN - 1 < buflen
            && islower(buf[i+3])) {
            quad.perms[buf[i]-'a'][buf[i+1]-'a'][buf[i+2]-'a'][buf[i+3]-'a']++;
            quad.n++;
        }
        else
            continue;

        if (i + QUINTGRAM_LEN - 1 < buflen
            && islower(buf[i+4])) {
            quint.perms[buf[i]-'a'][buf[i+1]-'a'][buf[i+2]-'a'][buf[i+3]-'a'][buf[i+4]-'a']++;
            quint.n++;
        }
    }

    print_bigram(bi);
    print_trigram(tri);
    print_quadgram(quad);
    print_quintgram(quint);

    /* oslobadjanje memorije */
    free(bi.perms);
    free(tri.perms);
    free(quad.perms);
    free(quint.perms);
}

int main()
{
    char *hr_wiki = read_file(FNAME);

    print_bigram_to_quintgram(hr_wiki);

    free(hr_wiki);

    return EXIT_SUCCESS;
}
