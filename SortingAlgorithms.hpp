#pragma once
#include "Visualizations.hpp"


class BubbleSort : public SortingAlgorithm {
private:
    size_t outerIndex = 0;
    size_t innerIndex = 0;

    bool isComparing = false;
    bool isSwapping = false;

    // Helper methods
    void performBubbleSortStep();
    bool isFinished() const;

public:
    // Override all pure virtual functions from SortingAlgorithm
    void render(sf::RenderTarget& target) const override;
    void handleInput(const sf::Event& event) override;
    void update(float dt) override;
    void SetRandomData(size_t length, int min, int max) override;

    // Additional methods
    void reset();
};;


