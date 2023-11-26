#pragma once

#include <cstdint>
#include <random>

class Instructions {
public:
	static const int32_t COMPUTE = 1;
	static const int32_t IO_BLOCK = 2;
	static const int32_t EXIT = 3;
	static const int32_t BRANCH_MIN = 128;
	static const int32_t BRANCH_MAX = 228;

	static bool IsBranching(int32_t instruction);
	static int32_t CalculateBlockWait();
private:
	static const int32_t IO_MIN_CYCLES = 50;
	static const int32_t IO_DEVIATION_CYCLES = 100;
};