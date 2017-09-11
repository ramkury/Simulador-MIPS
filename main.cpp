#include <cstdio>
#include "isa.h"
#include "control.h"

using namespace std;

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


