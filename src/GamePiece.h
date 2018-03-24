/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#ifndef BATTLESHIP_SPRITEUTIL_H
#define BATTLESHIP_SPRITEUTIL_H

#include <SFML/Graphics.hpp>
#include <shared_mutex>

class GamePiece {
public:
    // Game Piece coordinates in tile map
    int x = 0;
    int y = 0;
    // Length of Game Piece in tiles
    int length = 0;
    // Pixel bounding box of Game Piece
    sf::IntRect bounds;
    // Sprite object for Game Piece
    sf::Sprite sprite;
};

bool PieceInWindow(const std::shared_ptr<GamePiece> &piece, const sf::RenderWindow &window);
bool PiecesColliding(const std::shared_ptr<GamePiece> &piece, const std::vector<std::shared_ptr<GamePiece>> &allPieces, bool pieceInVec);

#endif //BATTLESHIP_SPRITEUTIL_H
