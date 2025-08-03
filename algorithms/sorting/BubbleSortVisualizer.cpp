#include "includes/BubbleSortVisualizer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <iostream>
#include <random>

void BubbleSortVisualizer::handleInput(const sf::Event& event){
  std::cout<<"bubble handleInput check\n"; // placeholder
}


void BubbleSortVisualizer::update(float dt){
  std::cout<<"bubble update check\n"; // placeholder
}


void BubbleSortVisualizer::render(sf::RenderTarget& target) const{
  sf::Vector2u size = target.getSize();
  float width = size.x;
  float height = size.y;

  //Width & hight of each bar
  float bar_width = width / static_cast<float>(data.size());
  int maxValue = *std::max_element(data.begin(), data.end());

  //loop through data to draw a rectangle
  for (size_t i{}; i < data.size(); ++i){
    float bar_height = (data[i] / static_cast<float>(maxValue)) * height; // scale hight to the screen
    float x = i * bar_width;
    float y = height - bar_height;

    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(bar_width - 1, bar_height)); // -1 for padding
    bar.setPosition(x,y);
    bar.setFillColor(sf::Color::White); // change later for highlights

    target.draw(bar);
  }
}

//Resets all value in bubblesortvisualizer class
void BubbleSortVisualizer::reset(){
  std::cout<<"bubble reset check\n"; //placeholder
}

//Set data to sort with optional user vector if not random vector will be created
void BubbleSortVisualizer::SetRandomData(size_t length, int min, int max) {
  if (length < 2)
    throw std::invalid_argument("BubbleSortVisualizer::SetData: Length must be at least 2 for sorting visualization.");
  if (min > max) std::swap(min, max);

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
