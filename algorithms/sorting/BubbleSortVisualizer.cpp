#include "includes/BubbleSortVisualizer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

void BubbleSortVisualizer::handleInput(const sf::Event& event){
  std::cout<<"bubble handleInput check\n"; // placeholder
}


void BubbleSortVisualizer::update(float dt){
  std::cout<<"bubble update check\n"; // placeholder
}


void BubbleSortVisualizer::render(sf::RenderTarget& target) const{
  std::cout<<"bubble render check\n"; // placeholder
}

void BubbleSortVisualizer::reset(){
  std::cout<<"bubble reset check\n"; //placeholder
}
