#pragma once

#include "SortingAlgorithms.hpp"
#include "Visualizations.hpp"
#include <unordered_map>
#include <functional>


// Generic algorithm setter that works with any visualizer type
using AlgoSetter = std::function<bool(Visualizer*)>;
// Maps algorithm names to their corresponding creation functions
const std::unordered_map<std::string, AlgoSetter> Algorithms_Map = {
    {"bubble", [](Visualizer* v) -> bool {
        SortingVisualizer* sortVis = dynamic_cast<SortingVisualizer*>(v);
        if (sortVis) {
            sortVis->algorithm = std::make_unique<BubbleSort>();
            return true;
        }
        return false;
    }},
    // Add more algorithms here

};


// helper struct
struct ParsedInput {
    std::string algorithm;
    char size = 'm'; // default to medium
    bool valid = false;
};

// Helper main function
void selected_category(const char& option, class Visualizer*& current_category, Category& category);
void verify_option(char& option);
int verify_algorithm(std::string& algorithm, Visualizer* current_category);
size_t getSampleSize(char size);
ParsedInput parseAlgorithmInput(const std::string& input);
