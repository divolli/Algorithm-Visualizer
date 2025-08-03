#pragma once
#include "visualizer/AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class BubbleSortVisualizer : public AlgorithmVisualizer {
  private:

  public:
    void update(float dt);
    void render(sf::RenderTarget& target) const;
    void handleInput(const sf::Event& event);
    void reset();
};
