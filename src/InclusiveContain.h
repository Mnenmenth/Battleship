/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 */
#ifndef BATTLESHIP_INCLUSIVECONTAIN_H
#define BATTLESHIP_INCLUSIVECONTAIN_H

#include <SFML/Graphics/Rect.hpp>
bool InclusiveContain(sf::FloatRect a, sf::Vector2f b) {
    return (a.left-1 <= b.x && a.top-1 <= b.y && a.left + a.width + 1>= b.x && a.top + a.height + 1>= b.y);
}

#endif //BATTLESHIP_INCLUSIVECONTAIN_H
