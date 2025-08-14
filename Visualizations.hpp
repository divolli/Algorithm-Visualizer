#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <random>
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
    float speed = 1.0f;
    float delayTimer = 0.0f;
    bool isFinished = false;
    bool isPaused = false;

  public:
    virtual ~SortingAlgorithm() = default;
    virtual void render(sf::RenderTarget& target) const = 0;
    virtual void update(float dt) = 0;
    virtual void reset() = 0;
    virtual void performStep(bool forward) = 0; // true - step forward, false - step backward

    // Non virtual functions for all algorithms
    void handleInput(const sf::Event& event){  // S - slow down, F - faster, SPACE - play/stop, -> one step forward, <- step backward, R - reset.
      if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    isPaused = !isPaused;
                    break;
                case sf::Keyboard::F:
                    speed = std::min(speed * 1.5f, 100.0f); // speed limit
                    break;
                case sf::Keyboard::S:
                    speed = std::max(speed / 1.5f, 0.5f); // speed limit
                    break;
                case sf::Keyboard::Left:
                    if (!isPaused) isPaused = true;
                    performStep(false);
                    break;
                case sf::Keyboard::Right:
                    if (!isPaused) isPaused = true;
                    performStep(true);
                    break;
                case sf::Keyboard::R:
                    reset();
                    break;
            }
        }
    }

    void SetRandomData(size_t length, int min, int max) {
      data.clear();
      data.reserve(length);
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<int> dist(min, max);

      for (size_t i = 0; i < length; ++i) {
        data.push_back(dist(gen));
      }
      isFinished = false;
      isPaused = false;
      delayTimer = 0.0f;
      reset();
    }
};


class SortingVisualizer: public Visualizer {
  public:
    std::unique_ptr<SortingAlgorithm> algorithm = nullptr;

    void render(sf::RenderTarget& target) const override {
      if (algorithm) algorithm->render(target);
    }

    void handleInput(const sf::Event& event) override {
      if (algorithm) {
        algorithm->handleInput(event);
      }
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

//->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART->TO DO PART

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



