#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <ostream>
#include "../include/HelperParser/ParserInput.hpp"
#include "../include/Visualizer/Visualizations.hpp"


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
  Visualizer* MainAlgorithm = nullptr;
  selected_category(opt, MainAlgorithm, category);

  std::cout
  << "Perfect!\n"
  << "Write algorithm name to visualize and data sample size:\n"
  << "Sizes: s (small), m (medium), l (large) - default is medium\n"
  << "Examples: 'bubble s' or just 'bubble'\n"
  << "--help to see more information and a list of all algorithms."
  << std::endl;
  // Clear the input buffer after reading char
  std::cin.ignore();

  // Read algorithm to visualize
  std::string chosen_alg{};
  std::getline(std::cin, chosen_alg);
  // Verify input
  int check = verify_algorithm(chosen_alg, MainAlgorithm);
  if (check == -1) return -1;
  std::cout
  << "Starting Visualization...\n"
  << "Use keys for navigating:\n"
  << "F - faster, S - slower, Q - quit, R - reset\n"
  << "SPACE - stop/play, <- step backwards, -> step forward"
  << std::endl;

  // Main window loop
  sf::RenderWindow window(sf::VideoMode({1180,720}), "Visualizer");
  window.setPosition({750,150});
  window.setVerticalSyncEnabled(true);
  // Clock for timing
  sf::Clock clock;

  // Main loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q){
        window.close();
      }

      // Handle input
      MainAlgorithm->handleInput(event);
    }

    // Update
    float deltaTime = clock.restart().asSeconds();
    MainAlgorithm->update(deltaTime);

    // Clear
    window.clear(sf::Color::Black);

    // Draw
    MainAlgorithm->render(window);

    // Display
    window.display();
  }

  std::cout << "See you later!" << std::endl;
  return 0;
}







