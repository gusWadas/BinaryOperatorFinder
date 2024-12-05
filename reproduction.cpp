#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::vector<bool> mutate_table_10_percent(std::vector<bool> original_table) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (size_t i = 0; i < original_table.size(); ++i) {
        if (dis(gen) < 0.1) {
            original_table[i] = 1 - original_table[i];  // Flip the bit
        }
    }
    
    return original_table;
}

std::vector<bool> combine_tables_half(const std::vector<bool>& table1, const std::vector<bool>& table2) {
    std::vector<bool> combined_table(table1.size());
    size_t half_size = table1.size() / 2;
    
    std::copy(table1.begin(), table1.begin() + half_size, combined_table.begin());
    std::copy(table2.begin() + half_size, table2.end(), combined_table.begin() + half_size);
    
    return combined_table;
}

std::vector<bool> combine_tables_three_quarters(const std::vector<bool>& table1, const std::vector<bool>& table2) {
    std::vector<bool> combined_table(table1.size());
    size_t three_quarters_size = table1.size() * 3 / 4;
    
    std::copy(table1.begin(), table1.begin() + three_quarters_size, combined_table.begin());
    std::copy(table2.begin() + three_quarters_size, table2.end(), combined_table.begin() + three_quarters_size);
    
    return combined_table;
}

void print_table(const std::vector<bool>& table) {
    for (bool val : table) {
        std::cout << val;
    }
    std::cout << std::endl;
}

int main() {
    std::vector<bool> original = {0, 1, 0, 1, 1, 0, 0, 1};
    
    auto mutated = mutate_table_10_percent(original);
    auto combined_half = combine_tables_half(original, mutated);
    auto combined_three_quarters = combine_tables_three_quarters(original, mutated);
    print_table(original);
    print_table(mutated);

    
    return 0;
}