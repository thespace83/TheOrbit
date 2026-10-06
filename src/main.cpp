#include <SFML/Graphics.hpp>
#include "Rails.h"

using namespace std;

static constexpr int WINDOW_HEIGHT{800};
static constexpr int WINDOW_WIGHT{800};


class Field {
    sf::Texture *grid_texture;
    sf::Sprite *grid_sprite;

public:
    sf::Vector2f position{};
    float scale{1};

    Field() {
        grid_texture = new sf::Texture("assets/grid.png");
        grid_sprite = new sf::Sprite(*grid_texture);
    }

    void draw_grid(sf::RenderWindow &window) const {
        for (int y{}; y < WINDOW_HEIGHT / 64 + 1; y++) {
            for (int x{}; x < WINDOW_WIGHT / 64 + 1; x++) {
                grid_sprite->setPosition(sf::Vector2f(x * 64, y * 64));
                window.draw(*grid_sprite);
            }
        }
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIGHT, WINDOW_HEIGHT}), "My Trains"); //, sf::State::Fullscreen);

    const Field field{};

    Rails rails{sf::Vector2f(100, 100), sf::Vector2f(700, 300)};

    sf::Clock clock;
    while (window.isOpen()) {
        const float delta = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));
        field.draw_grid(window);

        rails.draw(window);

        window.display();
    }
}
