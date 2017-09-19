#include <cstdio>
#include "../include/isa.h"
#include "../include/control.h"

using namespace std;

int main(int argc, const char * argv[]) {

    load_file(TEXT_START / 4, "bin/text.bin");
    load_file(DATA_START / 4, "bin/data.bin");

    printf("Segmento de código:\n");
    dump_mem(TEXT_START, DATA_START, 'h');
    printf("Segmento de dados:\n");
    dump_mem(DATA_START, MEM_SIZE * 4, 'h');
    printf("Executando o programa:\n");
    run();
    getchar();
    printf("Pressione qualquer tecla para continuar\n");
    getchar();
    dump_mem(TEXT_START, DATA_START, 'h');

    return 0;
}


