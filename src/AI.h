/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#ifndef BATTLESHIP_AI_H
#define BATTLESHIP_AI_H

#include "GamePiece.h"

namespace AI {
    std::vector<std::shared_ptr<GamePiece>> GenShips(int TileSize, sf::Texture &spriteSheet, std::map<std::string, sf::IntRect> &ShipConfig, sf::RenderWindow &window);
}


#endif //BATTLESHIP_AI_H
