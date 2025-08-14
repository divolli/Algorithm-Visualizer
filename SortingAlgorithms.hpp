#pragma once
#include "Visualizations.hpp"


class BubbleSort : public SortingAlgorithm {
  private:
    size_t outerIndex = 0;
    size_t innerIndex = 0;
    bool isComparing = false;
    bool isSwapping = false;

    // Store previous states for backward stepping
    struct SortState {
      size_t outerIndex, innerIndex;
      std::vector<int> dataSnapshot;
      bool isComparing, isSwapping;
    };
    std::vector<SortState> stateHistory;

  public:
    void render(sf::RenderTarget& target) const override;
    void update(float dt) override;
    void performStep(bool forward) override;
    void reset() override;
};



