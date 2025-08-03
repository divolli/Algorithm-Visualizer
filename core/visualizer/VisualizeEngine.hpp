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
    void handleInput(const sf::Event& event);
    void update(float dt);
    void reset();
    void render(sf::RenderTarget& target) const;
    void set_visualizer(std::unique_ptr<AlgorithmVisualizer> NewVisualizer);
};
