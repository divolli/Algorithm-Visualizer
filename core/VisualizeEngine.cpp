#include "VisualizeEngine.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
void VisualizeEngine::handleInput(const sf::Event& event){
  std::cout << "DEBUD[handleInput]\n"; // debug pring
  // Control if statement todo later
  if (event.key.shift){
    std::cout << "You have pressed a shift!\n";
  }
}


void VisualizeEngine::update(float dt){
  std::cout << dt << "\n"; // debug print
}


void VisualizeEngine::render(sf::RenderTarget& target) const{
  target.draw(sf::CircleShape(30)); // placeholder
}
