#ifndef EPOCH_H
#define EPOCH_H

#include <vector>
#include "evol.h"

const int T_TABLES = N_BITS * 10;

std::vector<bool> generate_random_logic_table(int input_size);
int evaluate_logic_table(const std::vector<bool>& logic_table, const std::vector<int>& input);
std::pair<std::vector<int>, std::vector<int>> generate_random_sqrt_binary();

#endif // EPOCH_H