#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>


class Visualizer {
  public:
    virtual ~Visualizer() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                               SORTING
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SortingAlgorithm {
  protected:
    // Common properties that derived classes can use
    std::vector<int> data;
    float delayTimer = 0.0f;

  public:
    virtual ~SortingAlgorithm() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void SetRandomData(size_t length, int min, int max) = 0;
};


class SortingVisualizer: public Visualizer {
  public:
    std::unique_ptr<SortingAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) {
      if (algorithm) algorithm->update(dt);
    }

    void SetRandomData(size_t length, int min, int max) {
      if (algorithm) algorithm->SetRandomData(length, min, max);
    }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                               GRAPH
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


class GraphAlgorithm {
  public:
    virtual ~GraphAlgorithm() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void SetRandomData(size_t length, int min, int max) = 0;
};


class GraphVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<GraphAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) {
      if (algorithm) algorithm->update(dt);
    }

    void SetRandomData(size_t length, int min, int max) {
      if (algorithm) algorithm->SetRandomData(length, min, max);
    }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                               FINANCE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class FinanceAlgorithm {
  public:
    virtual ~FinanceAlgorithm() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void SetRandomData(size_t length, int min, int max) = 0;
};


class FinanceVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<FinanceAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) {
      if (algorithm) algorithm->update(dt);
    }

    void SetRandomData(size_t length, int min, int max) {
      if (algorithm) algorithm->SetRandomData(length, min, max);
    }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                               ML/AI
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class MLAlgorithm {
  public:
    virtual ~MLAlgorithm() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void SetRandomData(size_t length, int min, int max) = 0;
};


class MLVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<MLAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) {
      if (algorithm) algorithm->update(dt);
    }

    void SetRandomData(size_t length, int min, int max) {
     if (algorithm) algorithm->SetRandomData(length, min, max);
    }
};


struct Category {
  std::unique_ptr<SortingVisualizer> Sort;
  std::unique_ptr<GraphVisualizer> Graph;
  std::unique_ptr<FinanceVisualizer> Finance;
  std::unique_ptr<MLVisualizer> ML;
};



