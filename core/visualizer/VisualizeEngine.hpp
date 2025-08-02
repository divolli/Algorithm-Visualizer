#pragma once

#include "AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class VisualizeEngine
{
  public:
    void handleInput(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderTarget& target) const;
    std::unique_ptr<AlgorithmVisualizer> currentVisualizer = nullptr;
};
