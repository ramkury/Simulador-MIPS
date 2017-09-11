#include "catch.h"
#include "../isa.h"

TEST_CASE("Escrita e leitura em memória") {

    SECTION("Escrita em posições alinhadas de memória:") {
        CHECK_NOTHROW(sw(0, 0, 0x20082000));
        CHECK(mem[0] == 0x20082000);
        CHECK_NOTHROW(sw(3, 1, 0x20092020));
        CHECK(mem[1] == 0x20092020);

        mem[3] = 0x12345678;

        CHECK_NOTHROW(sh(12, 0, 0xABCD));
        CHECK(mem[3] == 0x1234ABCD);
        CHECK_NOTHROW(sh(4, 8, 0x0));
        CHECK(mem[3] == 0x12340000);

        CHECK_NOTHROW(sb(0, 0, 0x12));
        CHECK_NOTHROW(sb(0, 1, 0x34));
        CHECK_NOTHROW(sb(1, 1, 0x56));
        CHECK_NOTHROW(sb(2, 1, 0x78));
        CHECK(mem[0] == 0x78563412);
    }

    SECTION("Leitura em posições alinhadas de memória:") {
        mem[0] = 0x12345678;
        CHECK(lb(0, 0) == 0x78);
        CHECK(lb(0, 1) == 0x56);
        CHECK(lb(0, 2) == 0x34);
        CHECK(lb(0, 3) == 0x12);
        CHECK(lh(0, 0) == 0x5678);
        CHECK(lh(0, 2) == 0x1234);
        CHECK(lw(4, -4) == 0x12345678);
    }

    SECTION("Escrita em posições desalinhadas de memória:") {
        auto x0 = mem[0];
        auto x1 = mem[1];
        CHECK_THROWS(sw(0, 2, 0xFFFF0000));
        CHECK(x0 == mem[0]);
        CHECK(x1 == mem[1]);

        CHECK_THROWS(sh(3, 2, 0x10));
        CHECK_THROWS(sh(3, 0, 0xAA));
    }

    SECTION("Leitura de posiçoes desalinhadas") {
        CHECK_THROWS(lw(2, 0));
        CHECK_THROWS(lw(2, 3));
        CHECK_THROWS(lw(1, 0));
        CHECK_THROWS(lh(1, 0));
        CHECK_THROWS(lh(1, 2));
        CHECK_THROWS(lh(0, 3));
    }
}

