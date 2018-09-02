/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 */
#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

#include "GamePiece.h"

namespace Player {
    bool PlacePiece(int TileSize, const sf::Event &event, const sf::RenderWindow &window, std::shared_ptr<GamePiece> piece, const std::vector<std::shared_ptr<GamePiece>> &pieces);
}

#endif //BATTLESHIP_PLAYER_H
