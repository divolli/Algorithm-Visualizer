#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "VisualizeEngine.hpp"

int main(void){
  // sfml window
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer");

  // Limit framerate
  window.setFramerateLimit(90);

  // measure frame timing
  sf::Clock clock;
  VisualizeEngine engine;
  // main loop
  while (window.isOpen()){
    // Input events
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed) window.close();
      engine.handleInput(event);
    }

    // time since last frame
    float dt = clock.restart().asSeconds();
    engine.update(dt);

    // Render
    window.clear(sf::Color(30,30,30));
    engine.render(window);
    window.display();
  }

  return 0;
}

