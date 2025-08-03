#pragma once
#include "visualizer/AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class BubbleSortVisualizer : public AlgorithmVisualizer {
  private:
    std::vector<int> data{};
  public:
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;
    void handleInput(const sf::Event& event) override;
    void reset() override;

    void SetRandomData(size_t length, int min, int max); // for random vals
    void SetData(const std::vector<int>& UserData); // for user input
};
