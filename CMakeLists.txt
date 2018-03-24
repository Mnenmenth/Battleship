cmake_minimum_required(VERSION 3.9)
project(Battleship)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

find_package(SFML REQUIRED graphics window system)

add_executable(Battleship
        src/Battleship.cpp
        src/InclusiveContain.h
        src/Marker.cpp
        src/Marker.h
        src/Random.h
        src/Ship.h
        src/Ship.cpp
        src/ShipConfig.h
        src/States.h
        src/GamePiece.cpp
        src/GamePiece.h src/AI.cpp src/AI.h src/Player.cpp src/Player.h)
target_link_libraries(Battleship ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})