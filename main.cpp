#include <cstdio>
#include <fstream>

#include "isa.h"

using namespace std;

void print_memory();
void read_to_memory(int start_addr, const char * filename);

int main() {
    read_to_memory(TEXT_START / 4, "bin/text.bin");
    read_to_memory(DATA_START / 4, "bin/data.bin");

    print_memory();

    printf("Pressione qualquer tecla para continuar\n");
    getchar();

    printf("lw 0 0: %.8X\n", lw(0, 0));
    printf("lh 4 0: %.8X\n", lh(4, 0));
    printf("lb 6 0: %.8X\n", lb(6, 0));
    printf("Usando as funções de escrita em memória e verificando efeitos.\n");
    sw(0, 0, -5);
    sh(4, 0, -10);
    sb(6, 0, -20);
    printf("lw 0 0: %.8X\n", lw(0, 0));
    printf("lh 4 0: %.8X\n", lh(4, 0));
    printf("lb 6 0: %.8X\n", lb(6, 0));

    printf("Pressione qualquer tecla para continuar\n");
    getchar();
    print_memory();

    mem[0] = 0x12345678;
    printf("0: %.8X\n", lb(0, 0));
    printf("1: %.8X\n", lb(1, 0));
    printf("2: %.8X\n", lb(2, 0));
    printf("3: %.8X\n", lb(3, 0));
    printf("lw 0 0: %.8X\n", lw(0, 0));

    printf("Pressione qualquer tecla para continuar\n");
    getchar();
    print_memory();

    return 0;
}

void print_memory() {
    int i;
    printf("\nMemoria (hex):\n");
    printf("Início da área de código (0x%.8X)\n", TEXT_START);
    for(i = TEXT_START / 4; i < DATA_START / 4; ++i) {
        printf(" %X ", mem[i]);
    }
    printf("\nInício da área de dados (0x%.8X)\n", DATA_START);
    for(i = DATA_START / 4; i < MEM_SIZE; ++i) {
        printf(" %X ", mem[i]);
    }
    printf("\n");
}

void read_to_memory(int start_addr, const char * filename) {
    ifstream f(filename);
    if (f.is_open()) {
        char buf[4];
        for (int i = start_addr; !f.eof(); i++)
        {
            f.read(buf, 4);
            mem[i] = *(int *)buf;
        }
    }
}
