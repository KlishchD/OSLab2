#include "Instructions.h"
#include <stdlib.h>

bool Instructions::IsBranching(int32_t instruction)
{
    int32_t chace = instruction - BRANCH_MIN;
    return rand() % 100 <= chace;
}

int32_t Instructions::CalculateBlockWait()
{
    static std::default_random_engine generator;
    static std::normal_distribution<float> distribution(0.0f, 1.0f);
    return (int32_t)(IO_MIN_CYCLES + IO_DEVIATION_CYCLES * std::abs(distribution(generator)));
}
