#include "SortingAlgorithms.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>


void BubbleSort::render(sf::RenderTarget& target) const {
  // Get the size of the window
  sf::Vector2u WindowSize = target.getSize();
  unsigned int WindowWidth = WindowSize.x;
  unsigned int WindowHeight = WindowSize.y;

  float BarSpacing = 6.0f; // 6 pixels for gap
  float BarWidth = (WindowWidth - ((data.size() - 1) * BarSpacing)) / static_cast<float>(data.size()); // bar width will depend on width of the window and gap between bars
  float MaxHeight = WindowHeight * 0.8f; // will correct it later maybe?

  // max for scaling
  float MaxVal = *std::max_element(data.begin(), data.end());


  // Loop for render each bar
  for (auto i = 0; i < data.size(); ++i) {
    sf::RectangleShape bar;

    // Setting size for each bar
    float BarHeight = (static_cast<float>(data[i]) / MaxVal) * MaxHeight;
    bar.setSize(sf::Vector2f(BarWidth, BarHeight));

    // Setting position for each bar
    float xPos = (i * BarWidth) + (i * BarSpacing);
    float yPos = WindowHeight - BarHeight;

    // Add jumping effect for comparing bars
    if ((isComparing || isSwapping) && (i == innerIndex || i == innerIndex + 1)) {
      yPos -= 20;
    }

    bar.setPosition(xPos, yPos);

    // Highlight
    if (isComparing && i == innerIndex) {
      bar.setFillColor(sf::Color(128, 0, 128));     // Right comparing bar Purple
    }
    else if (isComparing && i == innerIndex + 1) {
      bar.setFillColor(sf::Color(255, 165, 0));      // Left comparing bar Orange
    }
    else if (isSwapping && i == innerIndex) {
      bar.setFillColor(sf::Color(128, 0, 128));     // Right swapping bar Purple
    }
    else if (isSwapping && i == innerIndex + 1) {
      bar.setFillColor(sf::Color(255, 165, 0));  // Left swapping bar Orange
    }
    else if (isComparing && i == innerIndex -1) {
      bar.setFillColor(sf::Color(255, 165, 0));   // Orange for last smaller bar
    }
    else if (i >= data.size() - outerIndex || isFinished) {
      bar.setFillColor(sf::Color::Green);    // Sorted elements
    }
    else {
      bar.setFillColor(sf::Color::White);    // Unsorted elements
    }

    target.draw(bar);
  }
}



void BubbleSort::performStep(bool forward) {
  if (forward) {
    // Save current state for potential backward step
    SortState currentState;
    currentState.innerIndex = innerIndex;
    currentState.outerIndex = outerIndex;
    currentState.dataSnapshot = data;
    currentState.isComparing = isComparing;
    currentState.isSwapping = isSwapping;
    stateHistory.push_back(currentState);

    // Limit history size to prevent memory issues
    if (stateHistory.size() > 100) {
      stateHistory.erase(stateHistory.begin());
    }

    // Perform one step of bubble sort
    if (isFinished) {
      return; // Nothing more to do
    }

    if (isComparing) {
      if (data[innerIndex] > data[innerIndex + 1]) {
        isSwapping = true;
        isComparing = false;
      } else {
        innerIndex++;
        if (innerIndex >= data.size() - 1 - outerIndex) {
          isComparing = false;
        }
      }
    }
    else if (isSwapping) {
      std::swap(data[innerIndex], data[innerIndex + 1]);
      isSwapping = false;
      innerIndex++;

      // Check if inner loop is complete
      if (innerIndex >= data.size() - 1 - outerIndex) {
        isComparing = false;  // Will be handled in the "else" block
      } else {
        isComparing = true;   // Continue with next comparison
      }
    }
    else {
      // Inner loop done - move to next outer iteration
      if (innerIndex == data.size() - 1 - outerIndex) {
        outerIndex ++;
        innerIndex = 0;
        // Check if algorithm is complete
        if (outerIndex >= data.size() - 1) {
          isFinished = true;
          return;
        }
      }

      // Start comparing current adjacent pair
      if (innerIndex < data.size() - 1 - outerIndex) {
        isComparing = true;
      }
    }
  }
  else {
    // Backward step - restore previous state
    if (!stateHistory.empty()) {
      SortState prevState = stateHistory.back();
      stateHistory.pop_back();

      // Restore all state variables
      outerIndex = prevState.outerIndex;
      innerIndex = prevState.innerIndex;
      data = prevState.dataSnapshot;
      isComparing = prevState.isComparing;
      isSwapping = prevState.isSwapping;
      isFinished = false;
    }
  }
}



void BubbleSort::reset(){
  outerIndex = 0;
  innerIndex = 0;
  isComparing = false;
  isSwapping = false;
  isFinished = false;
  stateHistory.clear();
  delayTimer = 0.0f;
}



void BubbleSort::update(float dt) {
  if (isPaused || isFinished) return;

  delayTimer += (dt * speed);

  const float STEP_DELAY = 0.5f;
  if (delayTimer >= STEP_DELAY) {
    delayTimer = 0.0f;
    performStep(true);
  }
}
