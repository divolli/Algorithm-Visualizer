#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class AlgorithmVisualizer {
  public:
    virtual ~AlgorithmVisualizer() = default;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderTarget& target) const = 0;

    virtual void reset() = 0;
    virtual void handleInput(const sf::Event& event) = 0;
};
