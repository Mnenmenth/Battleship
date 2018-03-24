/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#include "AI.h"
#include "Random.h"
#include "Ship.h"

// AI for placing ships
std::vector<std::shared_ptr<GamePiece>> AI::GenShips(int TileSize, sf::Texture &spriteSheet, std::map<std::string, sf::IntRect> &ShipConfig, sf::RenderWindow &window) {
    using Random = effolkronium::random_static;

    // Function for random coordinates on screen
    auto RandomCoord = [&TileSize]() -> sf::Vector2f {
        int x = Random::get(0, 9);
        int y = Random::get(0, 9);
        return sf::Vector2f(x*TileSize, y*TileSize);
    };

    // Function to generate random rotation. 0, 90, 180, or 270
    auto RandomRotation = []() -> int {
        return Random::get(0, 3)*90;
    };

    // Vector of placed ships
    std::vector<std::shared_ptr<GamePiece>> ships;

    // Place the ship
    auto PlaceShip = [&RandomCoord, &RandomRotation, &ships, &window](std::shared_ptr<GamePiece> ship) {

        // While the ship needs to get a new position and rotation
        bool placementOk = false;
        while(!placementOk) {

            // Current coordinate and rotation
            auto currCoord = ship->sprite.getPosition();
            auto currRot = ship->sprite.getRotation();

            // Generate new coordinate and rotation
            auto coord = RandomCoord();
            auto rot = RandomRotation();
            ship->sprite.setPosition(coord);
            ship->sprite.setRotation(rot);

            // If the ships collides with any others or is not in the window, reset the coords and rotation
            if(PiecesColliding(ship, ships, false) || !PieceInWindow(ship, window)) {
                ship->sprite.setPosition(currCoord);
                ship->sprite.setRotation(currRot);
                // Otherwise add the ship to the list of placed ships
            } else {
                placementOk = true;
                ships.push_back(ship);
            }

        }
    };

    // Load carrier ship from sprite ship
    auto carrier = std::make_shared<Ship>();
    // Load bounding box from ship config to grab the right sprite from the sprite sheet
    carrier->bounds = ShipConfig["Carrier"];
    carrier->sprite = sf::Sprite(spriteSheet, carrier->bounds);
    // The carrier is 5 tiles long
    carrier->length = 5;
    // Set the position of the sprite
    carrier->sprite.setPosition(0, 0);

    // Let the AI place the ship
    PlaceShip(carrier);

    auto battleship = std::make_shared<Ship>();
    battleship->bounds = ShipConfig["Battleship"];
    battleship->sprite = sf::Sprite(spriteSheet, battleship->bounds);
    battleship->length = 4;
    battleship->sprite.setPosition(0, 0);

    PlaceShip(battleship);

    auto cruiser = std::make_shared<Ship>();
    cruiser->bounds = ShipConfig["Cruiser"];
    cruiser->sprite = sf::Sprite(spriteSheet, cruiser->bounds);
    cruiser->length = 3;
    cruiser->sprite.setPosition(0, 0);

    PlaceShip(cruiser);

    auto submarine = std::make_shared<Ship>();
    submarine->bounds = ShipConfig["Submarine"];
    submarine->sprite = sf::Sprite(spriteSheet, submarine->bounds);
    submarine->length = 3;
    submarine->sprite.setPosition(0, 0);

    PlaceShip(submarine);

    auto destroyer = std::make_shared<Ship>();
    destroyer->bounds = ShipConfig["Destroyer"];
    destroyer->sprite = sf::Sprite(spriteSheet, destroyer->bounds);
    destroyer->length = 2;
    destroyer->sprite.setPosition(0, 0);

    PlaceShip(destroyer);

    // Return the ships placed by the AI
    return ships;
}