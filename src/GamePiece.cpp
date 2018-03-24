/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#include "GamePiece.h"
#include "InclusiveContain.h"

//Is the piece in the window
bool PieceInWindow(const std::shared_ptr<GamePiece> &piece, const sf::RenderWindow &window) {
    // The window boundaries
    const sf::FloatRect &windowRect = sf::FloatRect(0, 0, window.getView().getSize().x, window.getView().getSize().y);
    // The piece boundaries
    const sf::FloatRect &spriteRect = piece->sprite.getGlobalBounds();
    return InclusiveContain(windowRect, sf::Vector2f(spriteRect.left, spriteRect.top)) && InclusiveContain(windowRect, sf::Vector2f(spriteRect.left + spriteRect.width, spriteRect.top + spriteRect.height));
}

// Is the piece colliding with any other piece
bool PiecesColliding(const std::shared_ptr<GamePiece> &piece, const std::vector<std::shared_ptr<GamePiece>> &allPieces, bool pieceInVec) {

    // The piece boundaries
    const sf::FloatRect &spriteRect = piece->sprite.getGlobalBounds();
    // If the piece is in the vector its being compared against
    if(pieceInVec) {
        // # of collisions. 1 collision is inevitable as the piece will collide with itself. This is because the piece must already be in allPieces for rendering
        int collisions = 0;
        // Loop through all pieces
        for (auto const &currPiece : allPieces) {
            // If the piece given to the function collides with the current piece, add a collision
            if (spriteRect.intersects(currPiece->sprite.getGlobalBounds()))
                collisions += 1;
            // If there is more than one collision, return false
            if (collisions > 1)
                return true;
        }
        return false;
    // Otherwise, just check for a single collision
    } else {
        for (auto const &currPiece : allPieces)
            if(spriteRect.intersects(currPiece->sprite.getGlobalBounds()))
                return true;
        return false;
    }
}
