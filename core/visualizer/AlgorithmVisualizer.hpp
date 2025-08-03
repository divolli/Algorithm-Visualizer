#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class AlgorithmVisualizer {
  public:
    virtual ~AlgorithmVisualizer() = default;

    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void reset() = 0;
    virtual void SetRandomData(size_t length, int min, int max) = 0; // for random vals
    virtual void SetData(const std::vector<int>& UserData) = 0; // for user input
};
