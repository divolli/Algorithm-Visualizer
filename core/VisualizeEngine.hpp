#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class VisualizeEngine
{
  public:
    void handleInput(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderTarget& target) const;
};
