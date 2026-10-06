//
// Created by Pavel on 06-Oct-26.
//

#ifndef MYTRAINS_RAILS_H
#define MYTRAINS_RAILS_H

#include <SFML/Graphics.hpp>

class Rails {
    sf::Texture *track_texture;
    sf::Texture *crosstie_texture;
    sf::Sprite *track_sprite;
    sf::Sprite *crosstie_sprite;

public:
    sf::Vector2f start;
    sf::Vector2f end;

    Rails(sf::Vector2f start, sf::Vector2f end);

    ~Rails();

    void draw(sf::RenderWindow &window) const;
};


#endif //MYTRAINS_RAILS_H
