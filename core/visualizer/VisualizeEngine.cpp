#include "VisualizeEngine.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
void VisualizeEngine::handleInput(const sf::Event& event){
  std::cout << "DEBUD[handleInput]\n"; // debug pring
  // Control if statement todo later
  if (currentVisualizer){
    currentVisualizer->handleInput(event);
  }
}


void VisualizeEngine::update(float dt){
  if (currentVisualizer){
    currentVisualizer->update(dt);
  }
}


void VisualizeEngine::render(sf::RenderTarget& target) const{
  if (currentVisualizer){
      currentVisualizer->render(target);
  }
}
