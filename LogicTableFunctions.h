#ifndef LOGIC_TABLE_FUNCTIONS_H
#define LOGIC_TABLE_FUNCTIONS_H

#include <vector>
#include "evol.h"

std::vector<bool> generate_random_logic_table(int input_size);
int evaluate_logic_table(const std::vector<bool>& logic_table, const std::vector<int>& input);

#endif // LOGIC_TABLE_FUNCTIONS_H