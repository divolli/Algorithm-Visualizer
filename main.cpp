#include <iostream>
#include <ostream>
#include "ParserInput.hpp"
#include "Visualizations.hpp"


int main(){
  std::cout
      << "Welcome to Algorithm Visualizer!\n"
      << "Please Choose Algorithm Category Below:\n"
      << "1. Sorting Algorithms (press S)\n"
      << "2. Graph Algorithms (press G)\n"
      << "3. Financial Algorithms (press F)\n"
      << "4. ML/AI Algorithms (press A)\n"
      << "For quit press - Q"
      << std::endl;

  // Read option
  char opt{};
  std::cin >> opt;
  // Verify input
  verify_option(opt);
  if (opt == 'Q') return -1; // QUIT

  // Set category
  Category category;
  Visualizer* running_algorithm = nullptr;
  selected_category(opt, running_algorithm, category);

  std::cout
  << "Perfect!\n"
  << "Write algorithm name to visualize and data sample size:\n"
  << "Sizes: s (small), m (medium), l (large) - default is medium\n"
  << "Examples: 'bubble s' or just 'bubble'\n"
  << "--help to see more information and a list of all algorithms.\n"
  << "For quit press - Q"
  << std::endl;
  // Clear the input buffer after reading char
  std::cin.ignore();

  // Read algorithm to visualize
  std::string chosen_alg{};
  std::getline(std::cin, chosen_alg);
  // Verify input
  int check = verify_algorithm(chosen_alg, running_algorithm);
  if (check == -1) return -1;

  // Main window loop if all been chosen okay ?

  return 0;
}







