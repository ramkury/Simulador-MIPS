#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "isa.h"

using namespace std;

void print_memory();
bool read_to_memory(int start_addr, const char * filename);

int main() {
    // printf("lw 0 0: %x\n", lw(0, 0));
    // printf("lh 4 0: %x\n", lh(4, 0));
    // printf("lb 6 0: %x\n", lb(6, 0));
    // printf("Escrevendo em memoria...\n");
    // sw(0, 0, -5);
    // sh(4, 0, -10);
    // sb(6, 0, -20);
    // printf("lw 0 0: %x\n", lw(0, 0));
    // printf("lh 4 0: %x\n", lh(4, 0));
    // printf("lb 6 0: %x\n", lb(6, 0));

    read_to_memory(TEXT_START / 4, "bin/text.bin");
    read_to_memory(DATA_START / 4, "bin/data.bin");

    //mem[0] = 0x12345678;
    //printf("0: %x\n", lb(0, 0));
    //printf("1: %x\n", lb(1, 0));
    //printf("2: %x\n", lb(2, 0));
    //printf("3: %x\n", lb(3, 0));
    // printf("lw 0 0: %x\n", lw(0, 0));

    print_memory();

    system("pause");

    return 0;
}

void print_memory() {
    int i;
    printf("\nMemoria (hex):\n");
    for (i = 0; i < MEM_SIZE; ++i) {
        printf(" %.8X ", mem[i]);
    }
    printf("\n");
}

bool read_to_memory(int start_addr, const char * filename)
{
    ifstream f(filename);
    if (!f.is_open())
        return false;
    char buf[4];
    for (int i = start_addr; !f.eof(); i++)
    {
        f.read(buf, 4);
        mem[i] = *(int *)buf;
    }
    return true;
}
