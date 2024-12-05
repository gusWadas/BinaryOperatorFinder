#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include <vector>

std::vector<bool> mutate_table_10_percent(std::vector<bool> original_table);
std::vector<bool> combine_tables_half(const std::vector<bool>& table1, const std::vector<bool>& table2);
std::vector<bool> combine_tables_three_quarters(const std::vector<bool>& table1, const std::vector<bool>& table2);
void print_table(const std::vector<bool>& table);

#endif // REPRODUCTION_H