#pragma once

#include "AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class VisualizeEngine
{
  private:
    std::unique_ptr<AlgorithmVisualizer> currentVisualizer = nullptr;
  public:
    void handleInput(const sf::Event& event); // hande user input logic
    void update(float dt); // Main algorithm implementation
    void reset(); // Resets class data
    void render(sf::RenderTarget& target) const; // Render algorithm
    void set_visualizer(std::unique_ptr<AlgorithmVisualizer> NewVisualizer); // Pointer to a new class visualiser
    void SetRandomData(size_t length, int min, int max); // set random data
    void SetData(const std::vector<int>& UserData); // set data from user
};
