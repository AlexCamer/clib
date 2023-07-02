#include "test/suite.h"
#include "test/unit.h"
#include "utility/macros.h"

UNIT(MUL2_unit) {
    for (usize i = 0; i < 64; i++)
        ASSERT(MUL2(i) == i * 2);
}

UNIT(DIV2_unit) {
    for (usize i = 0; i < 64; i++)
        ASSERT(DIV2(i) == i / 2);
}

UNIT(EXP2_unit) {
    for (usize i = 0; i < 64; i++)
        ASSERT(EXP2(i) == 1 << i);
}

UNIT(MUL_EXP2_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(MUL_EXP2(i, j) == i * EXP2(j));
    }
}

UNIT(DIV_EXP2_unit) {
    for (usize i = 0; i < 256; i += 16) {
        for (usize j = 0; j < 16; j++)
            ASSERT(DIV_EXP2(i, j) == i / EXP2(j));
    }
}

UNIT(MOD_EXP2_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(MOD_EXP2(i, j) == i % EXP2(j));
    }
}

UNIT(PAD_EXP2_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(PAD_EXP2(i, j) == (i + EXP2(j) - 1) / EXP2(j) * EXP2(j));
    }
}

UNIT(MIN_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(MIN(i, j) == (i < j ? i : j));
    }
}

UNIT(MAX_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(MAX(i, j) == (i > j ? i : j));
    }
}

UNIT(AVG_unit) {
    for (usize i = 0; i < 16; i++) {
        for (usize j = 0; j < 16; j++)
            ASSERT(AVG(i, j) == (i + j) / 2);
    }
}

SUITE(MUL2_unit,
      DIV2_unit,
      EXP2_unit,
      MUL_EXP2_unit,
      DIV_EXP2_unit,
      MOD_EXP2_unit,
      PAD_EXP2_unit,
      MIN_unit,
      MAX_unit,
      AVG_unit)
