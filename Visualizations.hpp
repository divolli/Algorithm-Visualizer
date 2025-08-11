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
    virtual void initializeData(size_t dataSize) = 0;
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

    void render(sf::RenderTarget& target) const override {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) override {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) override {
      if (algorithm) algorithm->update(dt);
    }

    void initializeData(size_t dataSize) override {
      if (algorithm) {
        algorithm->SetRandomData(dataSize, 1, 1000);
      }
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
    virtual void SetRandomData(size_t length, int min, int max) = 0; // place holder from sorting algorithm
};


class GraphVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<GraphAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const override{
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) override {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) override {
      if (algorithm) algorithm->update(dt);
    }

    void initializeData(size_t dataSize) override {
      if (algorithm) {
        algorithm->SetRandomData(dataSize, 1, 1000); // placeholder
      }
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
    virtual void SetRandomData(size_t length, int min, int max) = 0; // place holder from sorting algorithm
};


class FinanceVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<FinanceAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const override {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) override {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) override {
      if (algorithm) algorithm->update(dt);
    }

    void initializeData(size_t dataSize) override {
      if (algorithm) {
        algorithm->SetRandomData(dataSize, 1, 1000); // placeholder
      }
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
    virtual void SetRandomData(size_t length, int min, int max) = 0; // place holder from sorting algorithm
};


class MLVisualizer: public Visualizer {
  // TO DO later
  public:
    std::unique_ptr<MLAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const override {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) override {
      if (algorithm) algorithm->handleInput(event);
    }

    void update(float dt) override {
      if (algorithm) algorithm->update(dt);
    }

    void initializeData(size_t dataSize) override {
      if (algorithm) {
        algorithm->SetRandomData(dataSize, 1, 1000); // placeholder
      }
    }
};


struct Category {
  std::unique_ptr<SortingVisualizer> Sort;
  std::unique_ptr<GraphVisualizer> Graph;
  std::unique_ptr<FinanceVisualizer> Finance;
  std::unique_ptr<MLVisualizer> ML;
};



