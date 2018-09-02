/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 */
#ifndef BATTLESHIP_STATES_H
#define BATTLESHIP_STATES_H

namespace States {

    enum States {
        PlayerPlacingShips,
        AIPlacingShips,
        PlayerPlacingMarker,
        AIPlacingMarker,
        Finished
    };

    enum Placing {
        Carrier,
        Battleship,
        Cruiser,
        Submarine,
        Destroyer,
        Done
    };
}

#endif //BATTLESHIP_STATES_H
