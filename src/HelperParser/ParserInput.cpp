#include "../../include/HelperParser/ParserInput.hpp"
#include <iostream>
#include <fstream>


void verify_option(char& option){
  option = std::toupper(option);
  const std::string check = "SGFAQ";
  while (check.find(option) == std::string::npos){
    std::cout << "It seems that you are provided wrong input.\nPlease select a correct category or quit." << std::endl;
    std::cin >> option;
    option = std::toupper(option);
  }
}


void selected_category(const char& option, Visualizer*& current_category, Category& category){
  switch (option) {
    case 'S':
      category.Sort = std::make_unique<SortingVisualizer>();
      current_category = category.Sort.get();
      std::cout << "Sorting Algorithms category selected.\n";
      break;
    case 'G':
      category.Graph = std::make_unique<GraphVisualizer>();
      current_category = category.Graph.get();
      std::cout << "Graph Algorithms category selected.\n";
      break;
    case 'F':
      category.Finance = std::make_unique<FinanceVisualizer>();
      current_category = category.Finance.get();
      std::cout << "Financial Algorithms category selected.\n";
      break;
    case 'A':
      category.ML = std::make_unique<MLVisualizer>();
      current_category = category.ML.get();
      std::cout << "ML/AI Algorithms category selected.\n";
      break;
  }
}


size_t getSampleSize(char size) {
  switch (size) {
    case 's': return 35;   // small
    case 'm': return 60;  // medium
    case 'l': return 120;  // large
    default:  return 60;  // default to medium
  }
}


ParsedInput parseAlgorithmInput(const std::string& input) {
  ParsedInput result;
  size_t spacePos = input.find(' ');

  if (spacePos == std::string::npos) {
    result.algorithm = input;
    result.size = 'm';
  } else {
    // Space found - split algorithm and size
    result.algorithm = input.substr(0, spacePos);
    std::string sizeStr = input.substr(spacePos + 1);

    // Validate size
    if (!sizeStr.empty()) {
        char sizeChar = std::tolower(sizeStr[0]);
        if (sizeChar == 's' || sizeChar == 'm' || sizeChar == 'l') {
            result.size = sizeChar;
        }
    }
  }

  result.valid = !result.algorithm.empty();
  return result;
}


int verify_algorithm(std::string& chosen_alg, Visualizer* current_category){
  while(true) {
    // Check for quit
    if(!chosen_alg.empty() && std::toupper(chosen_alg[0]) == 'Q' && chosen_alg.size() < 3) {
      return -1;
    }

    // Check for help
    if (chosen_alg == "--help") {
      std::ifstream help_file("../help.txt");
      if (help_file) {
        std::cout << help_file.rdbuf() << '\n';
      } else {
        std::cerr << "Help file not found.\n";
        // Fallback help
        std::cout << "Available algorithms:\n";
        for (const auto& pair : Algorithms_Map) {
            std::cout << "- " << pair.first << "\n";
        }
      }
      std::cout << "Please enter algorithm name and size: ";
      std::getline(std::cin, chosen_alg);
      continue;
    }

    // Parse the input
    ParsedInput parsed = parseAlgorithmInput(chosen_alg);

    if (!parsed.valid) {
      std::cout << "Invalid input format. Please try again or press Q to exit: ";
      std::getline(std::cin, chosen_alg);
      continue;
    }

    // Look for algorithm in map
    auto it = Algorithms_Map.find(parsed.algorithm);
    if (it == Algorithms_Map.end()) {
      std::cout << "Unknown algorithm: " << parsed.algorithm
                << "\nPlease select existing one (--help for help) or press Q to exit: ";
      std::getline(std::cin, chosen_alg);
      continue;
    }

    // Try to set the algorithm
    if (it->second(current_category)) {
      std::cout << "Algorithm " << parsed.algorithm << " set successfully!\n";
      std::cout << "Sample size: " << getSampleSize(parsed.size) << " elements\n";

      // initialize data of current cuttegory
      current_category->initializeData(getSampleSize(parsed.size));

      return 0; // Success
    } else {
      std::cout << "Algorithm " << parsed.algorithm
                << " is not compatible with the selected category.\n"
                << "Please choose a different algorithm or press Q to exit: ";
      std::getline(std::cin, chosen_alg);
      continue;
    }
  }
}
