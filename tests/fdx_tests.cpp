#include "catch.h"
#include "../isa.h"
#include "../control.h"

TEST_CASE("Decode") {
    ri = 0x20082000;
    decode();
    CHECK(op == ADDI);
    CHECK(rt == 8);
    CHECK(rs == 0);
    CHECK(funct == 0);
    CHECK(get_immediate() == 0x2000);

    ri = 0x8D040000;
    decode();
    CHECK(op == LW);
    CHECK(rt == 4);
    CHECK(rs == 8);
    CHECK(rd == 0);
    CHECK(shamt == 0);
    CHECK(funct == 0);
    CHECK(get_immediate() == 0);
}

