#include <cstdio>
#include "isa.h"
#include "control.h"

using namespace std;

int main() {

    dump_reg('d');
    dump_reg('h');
    dump_reg('a');

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


