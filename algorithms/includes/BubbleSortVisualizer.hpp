#pragma once
#include "../../core/visualizer/AlgorithmVisualizer.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class BubbleSortVisualizer : public AlgorithmVisualizer {
  private:
    std::vector<int> data{};
    size_t idx = 0, jdx = 0;
    int max_data_value = 0;
    bool sortingComplete = false;
    float delayTimer = 0.f;
    float delayBetweenSteps = 0.05f;
  public:
    void render(sf::RenderTarget& target) const override;
    void handleInput(const sf::Event& event) override;
    void update(float dt) override;
    void reset() override;

    void SetRandomData(size_t length, int min, int max) override; // for random vals
    void SetData(const std::vector<int>& UserData) override; // for user input
};
