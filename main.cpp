#include <cstdio>
#include "isa.h"
#include "control.h"

using namespace std;

int main() {

    load_file(TEXT_START / 4, "../bin/text.bin");
    load_file(DATA_START / 4, "../bin/data.bin");

    dump_mem(TEXT_START, DATA_START, 'h');

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
    dump_mem(TEXT_START, DATA_START, 'h');

    mem[0] = 0x12345678;
    printf("0: %.8X\n", lb(0, 0));
    printf("1: %.8X\n", lb(1, 0));
    printf("2: %.8X\n", lb(2, 0));
    printf("3: %.8X\n", lb(3, 0));
    printf("lw 0 0: %.8X\n", lw(0, 0));

    printf("Pressione qualquer tecla para continuar\n");
    getchar();
    dump_mem(TEXT_START, DATA_START, 'h');


    /*
    dump_reg('d');
    dump_reg('h');
    dump_reg('a');
     */

    /*
    load_file(TEXT_START / 4, "../bin/text.bin");
    load_file(DATA_START / 4, "../bin/data.bin");
    printf("Área de código:\n");
    dump_mem(TEXT_START, DATA_START, 'h');
    printf("Área de dados:\n");
    dump_mem(DATA_START, MEM_SIZE * 4, 'd');
    dump_mem(TEXT_START, DATA_START, 'a');
    */
    return 0;
}


