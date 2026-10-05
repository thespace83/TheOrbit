#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;

int sign(const float n) {
    if (n > 0)
        return 1;
    if (n < 0)
        return -1;
    return 0;
}

class Rocket {
public:
    sf::Vector2f position;
    sf::Vector2f velocity{};
    sf::Texture texture{"rocket.png"};
    sf::Sprite sprite{texture};
    float engine_power{1000};
    float RCS_power{3};
    float rotation{};
    float rotation_velocity{};

    explicit Rocket(const sf::Vector2f position) : position(position) {
        sprite.setOrigin(sf::Vector2f(50, 73));
    }

    void tick(const float delta) {
        position += velocity * delta;
        rotation += rotation_velocity * delta;
        sprite.setPosition(position);
        sprite.setRotation(sf::radians(rotation));

        if ((sf::Vector2f(1280, 800) - position).length() >= 1500) {
            position.x = 1280;
            position.y = 800;
            rotation_velocity = 0;
            velocity.x = 0;
            velocity.y = 0;
        }
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(sprite);
    }
};

class RocketController {
    Rocket *rocket;

public:
    explicit RocketController(Rocket *rocket) {
        this->rocket = rocket;
    }

    void tick(const float delta) const {
        bool controlling_rotation{};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            rocket->rotation_velocity += delta * rocket->RCS_power;
            controlling_rotation = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            rocket->rotation_velocity -= delta * rocket->RCS_power;
            controlling_rotation = true;
        }
        if (!controlling_rotation) {
            rocket->rotation_velocity += delta * rocket->RCS_power * -static_cast<float>(
                sign(rocket->rotation_velocity));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            rocket->velocity += sf::Vector2f(cos(rocket->rotation), sin(rocket->rotation)) * delta * rocket->
                    engine_power;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({2560, 1600}), "Rocket Quest", sf::State::Fullscreen);

    Rocket rocket{sf::Vector2f(400, 400)};
    RocketController rocket_controller{&rocket};

    sf::Clock clock;
    while (window.isOpen()) {
        const float delta = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(0, 0, 0));

        rocket.tick(delta);
        rocket_controller.tick(delta);
        rocket.draw(window);

        window.display();
    }
}
