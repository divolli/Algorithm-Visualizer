#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <memory>
#include "visualizer/VisualizeEngine.hpp"
#include "../algorithms/includes/BubbleSortVisualizer.hpp"
#include "../sfml_ui/UI.hpp"


enum class AppState {
  MainMenu,
  Visualizing
};


int main(void){
  // sfml window
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer");

  // AppState
  AppState currentState = AppState::MainMenu;

  // Limit framerate
  window.setFramerateLimit(90);

  // Font
  sf::Font font;
  if (!font.loadFromFile("../assets/WhiteCapel.ttf")){
    std::cout << "Font file not found\n";
    return -1;
  }

  // measure frame timing
  sf::Clock clock;
  VisualizeEngine engine;
  engine.set_visualizer(std::make_unique<BubbleSortVisualizer>());
  engine.SetRandomData(75, -1000, 1000);

  // Main screen
  MainMenuUI mainMenu(font, window.getSize());

  // MAIN LOOP
  while (window.isOpen()){
    sf::Event event;

    // INPUT LOOP
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
      //inut in menu
      if (currentState == AppState::MainMenu) {
        mainMenu.handleEvent(event, window);

        if (mainMenu.getSelectedCategory() != AlgorithmCategory::None){
          // User picked a category - switch state
          currentState = AppState::Visualizing;
        }
      } else if (currentState == AppState::Visualizing){
        engine.handleInput(event);
      }
    }//END INPUT LOOP

    // time since last frame
    float dt = clock.restart().asSeconds();
    if (currentState == AppState::Visualizing) engine.update(dt);

    // Render
    window.clear(sf::Color(30,30,30));
    if (currentState == AppState::MainMenu)
      engine.render(window);
    else
      engine.render(window);

    window.display();
  }
  return 0;
}

