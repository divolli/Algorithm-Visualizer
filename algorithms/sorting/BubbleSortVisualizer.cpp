#include "../includes/BubbleSortVisualizer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>

void BubbleSortVisualizer::handleInput(const sf::Event& event){
  std::cout<<"bubble handleInput check\n"; // placeholder
}


void BubbleSortVisualizer::update(float dt){
  if (sortingComplete) return;

  if ( delayTimer >= delayBetweenSteps) {
    if (data[jdx] > data[jdx + 1]){
      std::swap(data[jdx], data[jdx + 1]);
      // optional sore indicies for color
    }
    ++jdx;
    if (jdx >= data.size() - idx - 1) {
      jdx = 0;
      ++idx;
    }
    if (idx >= data.size()){
      sortingComplete = true;
    }
    delayTimer = 0.f;
  } else {
    delayTimer += dt;
  }
}


void BubbleSortVisualizer::render(sf::RenderTarget& target) const{
  target.clear(sf::Color::Black); // to erase previous frame drawings
  if (data.empty()) return;

  sf::Vector2u size = target.getSize();
  float width = size.x;
  float height = size.y;

  //Width & hight of each bar
  float bar_width = width / static_cast<float>(data.size());
  int maxValue = max_data_value;
  if (maxValue == 0) maxValue = 1; // prevent 0 division
  //loop through data to draw a rectangle
  for (size_t i{}; i < data.size(); ++i){
    float bar_height = (data[i] / static_cast<float>(maxValue)) * height; // scale hight to the screen
    float x = i * bar_width;
    float y = height - bar_height; // Bars grow upwards from the bottom

    sf::RectangleShape bar;
    bar.setSize(sf::Vector2f(std::max(1.f, bar_width - 1.f), bar_height)); // -1 for padding
    bar.setPosition(x,y);
    bar.setFillColor(sf::Color::White); // change later for highlights

    target.draw(bar);
  }
}


//Resets all value in bubblesortvisualizer class
void BubbleSortVisualizer::reset(){
  data.clear();
  idx = 0;
  jdx = 0;
  sortingComplete = false;
  delayTimer = 0.f;
  std::cout << "DEBUG: BubbleSortVisualizer::reset() called.\n";
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

  max_data_value = *std::max_element(data.begin(), data.end());
}

void BubbleSortVisualizer::SetData(const std::vector<int>& UserData) {
  if (!UserData.empty()){
    max_data_value = *std::max_element(UserData.begin(), UserData.end());
  } else {
    max_data_value = 0;
  }
  data = UserData;
}
