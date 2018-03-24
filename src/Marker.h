/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#ifndef BATTLESHIP_MARKER_H
#define BATTLESHIP_MARKER_H


#include <SFML/Graphics.hpp>

// Generic Hit/Miss marker class
class Marker {
public:
    Marker() = default;

    // Marker coordinates in tile map
    int x = 0;
    int y = 0;
    // Pixel bounding box of sprite
    sf::IntRect bounds;
    // Sprite object for marker
    sf::Sprite sprite;
};

bool MarkerInWindow;

#endif //BATTLESHIP_MARKER_H
