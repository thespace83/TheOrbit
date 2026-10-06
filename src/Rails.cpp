//
// Created by Pavel on 06-Oct-26.
//

#include "Rails.h"

Rails::Rails(const sf::Vector2f start, const sf::Vector2f end) : start(start), end(end) {
    track_texture = new sf::Texture("assets/track.png");
    crosstie_texture = new sf::Texture("assets/crosstie.png");
    track_sprite = new sf::Sprite(*track_texture);
    crosstie_sprite = new sf::Sprite(*crosstie_texture);

    track_sprite->setOrigin(sf::Vector2f(1, 8));
    crosstie_sprite->setOrigin(sf::Vector2f(2, 13));
}

Rails::~Rails() {
    delete track_sprite;
    delete track_texture;
    delete crosstie_sprite;
    delete crosstie_texture;
}

void Rails::draw(sf::RenderWindow &window) const {
    for (int i{}; i < static_cast<int>((end - start).length()); i++) {
        if (i % 15 == 0) {
            crosstie_sprite->setPosition(start + (end - start).normalized() * static_cast<float>(i));
            crosstie_sprite->setRotation((end - start).angle());
            window.draw(*crosstie_sprite);
        }
        track_sprite->setPosition(start + (end - start).normalized() * static_cast<float>(i));
        track_sprite->setRotation((end - start).angle());
        window.draw(*track_sprite);
    }
}
