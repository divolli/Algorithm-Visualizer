#include "includes/BubbleSortVisualizer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <random>

void BubbleSortVisualizer::handleInput(const sf::Event& event){
  std::cout<<"bubble handleInput check\n"; // placeholder
}


void BubbleSortVisualizer::update(float dt){
  std::cout<<"bubble update check\n"; // placeholder
}


void BubbleSortVisualizer::render(sf::RenderTarget& target) const{
  std::cout<<"bubble render check\n"; // placeholder
}

//Resets all value in bubblesortvisualizer class
void BubbleSortVisualizer::reset(){
  std::cout<<"bubble reset check\n"; //placeholder
}

//Set data to sort with optional user vector if not random vector will be created
void BubbleSortVisualizer::SetRandomData(size_t length, int min, int max) {
    data.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>distrib(min, max);

    data.reserve(length);
    for (size_t i{}; i < length; ++i){
        data.push_back(distrib(gen));
    }
}

void BubbleSortVisualizer::SetData(const std::vector<int>& UserData) {
    data = UserData;
}
