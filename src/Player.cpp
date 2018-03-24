/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#include "Player.h"

// Place a piece. To be used in event loop while placing piece. Processes movement commands and checks if position is ok. Returns whether piece placement has been finalized or not
bool Player::PlacePiece(int TileSize, const sf::Event &event, const sf::RenderWindow &window, std::shared_ptr<GamePiece> piece, const std::vector<std::shared_ptr<GamePiece>> &pieces) {

    // If there was a keypress
    if(event.type == sf::Event::KeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        // Get the current properties of the piece
        auto currRot    = piece->sprite.getRotation();
        auto currPos    = piece->sprite.getPosition();
        auto currX      = piece->x;
        auto currY      = piece->y;

        // Process movements in each direction
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            piece->y -= 1;
            piece->sprite.setPosition(piece->sprite.getPosition().x, piece->y*TileSize);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            piece->y += 1;
            piece->sprite.setPosition(piece->sprite.getPosition().x, piece->y*TileSize);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            piece->x -= 1;
            piece->sprite.setPosition(piece->x*TileSize, piece->sprite.getPosition().y);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            piece->x += 1;
            piece->sprite.setPosition(piece->x*TileSize, piece->sprite.getPosition().y);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            piece->sprite.rotate(90.0f);
            // If the piece position is finalized, confirm that it is ok before finalizing the placement
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if(PieceInWindow(piece, window) && !PiecesColliding(piece, pieces, true)) return true;
        }

        // If the movements made are not ok, then revert changes
        if(!PieceInWindow(piece, window)) {
            piece->sprite.setRotation(currRot);
            piece->sprite.setPosition(currPos);
            piece->x = currX;
            piece->y = currY;
        }
        return false;
    }
    return false;
}