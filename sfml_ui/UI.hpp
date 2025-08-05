#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>


enum class AlgorithmCategory {
  Sorting,
  Graphs,
  Finance,
  MachineLearning,
  None // default
};

class MainMenuUI {
  public:
    MainMenuUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderTarget& target)const;
    AlgorithmCategory getSelectedCategory() const;

    private:
      sf::Text title;
      sf::Text subtitle;

      struct UIButton {
        sf::RectangleShape shape;
        sf::Text label;
        AlgorithmCategory category;
      };

      std::vector<UIButton> buttons;
      AlgorithmCategory selectedCategory = AlgorithmCategory::None;
      void setupUI(sf::Font& font, sf::Vector2<unsigned int> windowSize);
};
