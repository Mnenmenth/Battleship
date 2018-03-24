#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <functional>
#include <shared_mutex>
#include <SFML/Graphics.hpp>
#include <libgraph.hpp>

#include "GamePiece.h"
#include "Ship.h"
#include "States.h"
#include "ShipConfig.h"
#include "AI.h"
#include "Player.h"

// Size of one tile that is generated on runtime
int TileSize;

int main() {

    // Load map of ship names and their bounding boxes
    std::map<std::string, sf::IntRect> ShipConfig;
    LoadShipConfig("shipconfig", ShipConfig);

    // Make the tile size the width of the largest ship (doesn't really matter which ship though, they all should be the same width)
    TileSize = ShipConfig["Carrier"].width;

    // Basic context settings for best graphics
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    settings.depthBits = 24;
    settings.stencilBits = 8;

    // Resolution of screen
    sf::VideoMode screenRez = sf::VideoMode::getDesktopMode();

    // Window size is 3/4 the resolution of the screen
    sf::VideoMode windowSize = sf::VideoMode((unsigned int)((double)screenRez.width*(3.0/4.0)), (unsigned int)((double)screenRez.height*(3.0/4.0)));

    // Create the window
    sf::RenderWindow window(windowSize, "Battleship", sf::Style::Default, settings);
    // Set max FPS
    window.setFramerateLimit(60);

    // The view the player's ships will be on. After ships have been placed the view will be placed on the left half of the screen
    auto playerView = sf::View(sf::FloatRect(0, 0, TileSize*BOARD_SIZE, TileSize*BOARD_SIZE));

    // Set the ai view to be the right half of the screen
    auto aiView = sf::View(sf::FloatRect(0.5f, 0, TileSize*BOARD_SIZE, TileSize*BOARD_SIZE));
    aiView.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));

    // Load sprite sheet of ships
    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("TestSpriteSheet.png");

    // Load carrier ship from sprite ship
    auto carrier = std::make_shared<Ship>();
    // Load bounding box from ship config to grab the right sprite from the sprite sheet
    carrier->bounds = ShipConfig["Carrier"];
    carrier->sprite = sf::Sprite(spriteSheet, carrier->bounds);
    // The carrier is 5 tiles long
    carrier->length = 5;
    // Set the position of the sprite
    carrier->sprite.setPosition(0, 0);

    auto battleship = std::make_shared<Ship>();
    battleship->bounds = ShipConfig["Battleship"];
    battleship->sprite = sf::Sprite(spriteSheet, battleship->bounds);
    battleship->length = 4;
    battleship->sprite.setPosition(0, 0);

    auto cruiser = std::make_shared<Ship>();
    cruiser->bounds = ShipConfig["Cruiser"];
    cruiser->sprite = sf::Sprite(spriteSheet, cruiser->bounds);
    cruiser->length = 3;
    cruiser->sprite.setPosition(0, 0);

    auto submarine = std::make_shared<Ship>();
    submarine->bounds = ShipConfig["Submarine"];
    submarine->sprite = sf::Sprite(spriteSheet, submarine->bounds);
    submarine->length = 3;
    submarine->sprite.setPosition(0, 0);

    auto destroyer = std::make_shared<Ship>();
    destroyer->bounds = ShipConfig["Destroyer"];
    destroyer->sprite = sf::Sprite(spriteSheet, destroyer->bounds);
    destroyer->length = 2;
    destroyer->sprite.setPosition(0, 0);

    // List of ships that should currently be rendered
    std::vector<std::shared_ptr<GamePiece>> playerShips = {carrier};
    std::vector<std::shared_ptr<GamePiece>> visibleAIShips = {};
    std::vector<std::shared_ptr<GamePiece>> aiShips = {};

    int State = States::PlayerPlacingShips;
    int PlaceState = States::Placing::Carrier;

    // Game loop
    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {
            // Exit commands
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
                // What to do on resize
            else if(event.type == sf::Event::Resized) {
                window.setSize(sf::Vector2(event.size.width, event.size.height));
            }

            switch(State) {
                case States::PlayerPlacingShips:
                    // Placing operation for each ship
                    switch(PlaceState) {
                        case States::Placing::Carrier:
                            // If the ship is placed in an allowed position
                            if(Player::PlacePiece(TileSize, event, window, carrier, playerShips)) {
                                // Move to next ship for placing
                                PlaceState = States::Placing::Battleship;
                                // Next ship should be rendered for placing
                                playerShips.push_back(battleship);
                            }
                            break;
                        case States::Placing::Battleship:
                            if(Player::PlacePiece(TileSize, event, window, battleship, playerShips)) {
                                PlaceState = States::Placing::Cruiser;
                                playerShips.push_back(cruiser);
                            }
                            break;
                        case States::Placing::Cruiser:
                            if(Player::PlacePiece(TileSize, event, window, cruiser, playerShips)) {
                                PlaceState = States::Placing::Submarine;
                                playerShips.push_back(submarine);
                            }
                            break;
                        case States::Placing::Submarine:
                            if(Player::PlacePiece(TileSize, event, window, submarine, playerShips)) {
                                PlaceState = States::Placing::Destroyer;
                                playerShips.push_back(destroyer);
                            }
                            break;
                        case States::Placing::Destroyer:
                            if(Player::PlacePiece(TileSize, event, window, destroyer, playerShips)) {
                                PlaceState = States::Placing::Done;
                            }
                            break;
                        case States::Placing::Done:
                            // Set the viewport to be only the left half of the screen so on the right half is the AI board
                            playerView.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
                            // Move to the next state
                            State = States::AIPlacingShips;
                        default: break;
                    }
                    break;
                case States::AIPlacingShips:
                    aiShips = AI::GenShips(TileSize, spriteSheet, ShipConfig, window);
                    State = States::PlayerPlacingMarker;
                    break;
                case States::PlayerPlacingMarker:
                    State = States::AIPlacingMarker;
                    break;
                case States::AIPlacingMarker:
                    break;
                case States::Finished:
                    break;
                default: break;
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Set view to player view
        window.setView(playerView);
        // Render player's ships
        for(auto const &ship : playerShips)
            window.draw(ship->sprite);

        window.setView(aiView);
        for(auto const &ship : visibleAIShips)
            window.draw(ship->sprite);

        // Display everything rendered
        window.display();

    }


    return 0;
}