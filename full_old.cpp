#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

#include "evol.h"

const int T_TABLES = N_BITS * 20;
const int TRAIN_EPOCHS = 5000;
const int N_SELECTED_TABLES = 8;
const int N_TESTS = 320;

//Creates logic tables at random
std::vector<bool> generate_random_logic_table(int input_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    
    std::vector<bool> logic_table(1 << input_size);
    for (size_t i = 0; i < logic_table.size(); ++i) {
        logic_table[i] = dis(gen);
    }
    
    return logic_table;
}

// returns 0 or 1 according to a binary list input along with a logic table
int evaluate_logic_table(const std::vector<bool>& logic_table, const std::vector<int>& input) {
    int index = 0;
    for (int bit : input) {
        index = (index << 1) | bit;
    }
    
    return logic_table[index];
}

// creates a pair of binary list for a random 8 bit int and its square root
std::pair<std::vector<int>, std::vector<int>> generate_random_sqrt_binary() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, (1 << N_BITS) - 1);
    
    int original_number = dis(gen);
    int sqrt_number = static_cast<int>(std::floor(std::sqrt(original_number)));
    sqrt_number = std::min(sqrt_number, (1 << N_BITS) - 1);
    
    std::vector<int> original_binary(N_BITS, 0);
    std::vector<int> sqrt_binary(N_BITS, 0);
    
    for (int i = 0; i < N_BITS; ++i) {
        original_binary[N_BITS - 1 - i] = (original_number >> i) & 1;
        sqrt_binary[N_BITS - 1 - i] = (sqrt_number >> i) & 1;
    }
    
    return {original_binary, sqrt_binary};
}


void train_epoch(std::vector<std::vector<bool>>& tables, std::vector<std::vector<std::pair<int, int>>>& scores) {
    for (int test = 0; test < N_TESTS; ++test) {
        auto [original_binary, sqrt_binary] = generate_random_sqrt_binary();
        
        for (int table_idx = 0; table_idx < T_TABLES; ++table_idx) {
            int table_result = evaluate_logic_table(tables[table_idx], original_binary);
            
            for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
                scores[table_idx][bit_idx].second++;
                
                if (table_result == sqrt_binary[bit_idx]) {
                    scores[table_idx][bit_idx].first++;
                }
            }
        }
    }
}

std::vector<std::vector<bool>> train_tables(int epochs, int n_selected_tables) {
    std::vector<std::vector<bool>> tables(T_TABLES);
    for (auto& table : tables) {
        table = generate_random_logic_table(N_BITS);
    }

    std::vector<std::vector<std::pair<int, int>>> scores(
        T_TABLES, std::vector<std::pair<int, int>>(N_BITS, {0, 0})
    );

    for (int epoch = 0; epoch < epochs; ++epoch) {
        train_epoch(tables, scores);
    }

    // Select top N tables based on accuracy
    std::vector<std::pair<int, double>> table_accuracies;
    for (int table_idx = 0; table_idx < T_TABLES; ++table_idx) {
        double accuracy = 0.0;
        for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
            accuracy += static_cast<double>(scores[table_idx][bit_idx].first) / scores[table_idx][bit_idx].second;
        }
        accuracy /= N_BITS;
        table_accuracies.emplace_back(table_idx, accuracy);
    }

    std::sort(table_accuracies.begin(), table_accuracies.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second;
    });

    std::vector<std::vector<bool>> selected_tables;
    for (int i = 0; i < n_selected_tables; ++i) {
        selected_tables.push_back(tables[table_accuracies[i].first]);
    }

    return selected_tables;
}

std::vector<int> predict(const std::vector<std::vector<bool>>& selected_tables, const std::vector<int>& input) {
    std::vector<int> output_bits(N_BITS, 0);
    for (int bit_idx = 0; bit_idx < N_BITS; ++bit_idx) {
        output_bits[bit_idx] = evaluate_logic_table(selected_tables[bit_idx], input);
    }
    return output_bits;
}

int main() {
    // Train logic tables
    auto selected_tables = train_tables(TRAIN_EPOCHS, N_SELECTED_TABLES);

    // Test of results very visibly
    for (int test = 0; test < 5; ++test) { // Test on 5 random inputs
        auto [input, expected_output] = generate_random_sqrt_binary();
        auto actual_output = predict(selected_tables, input);

        std::cout << "Input:           ";
        for (int bit : input) std::cout << bit;
        std::cout << "\nExpected Output: ";
        for (int bit : expected_output) std::cout << bit;
        std::cout << "\nActual Output:   ";
        for (int bit : actual_output) std::cout << bit;
        std::cout << "\nDifference:      ";
        for (size_t i = 0; i < expected_output.size(); ++i) {
            std::cout << (expected_output[i] != actual_output[i] ? "1" : "0");
        }
        std::cout << "\n\n";
    }

    // Example prediction using the already trained selected_tables
    std::vector<int> input(N_BITS, 1); // Example input
    auto output = predict(selected_tables, input);

    std::cout << "Example Input:   ";
    for (int bit : input) {
        std::cout << bit;
    }
    std::cout << "\nOutput:          ";
    for (int bit : output) {
        std::cout << bit;
    }
    std::cout << std::endl;

    return 0;
}