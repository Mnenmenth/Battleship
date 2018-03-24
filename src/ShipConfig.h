/*
 * Made by Earl Kennedy
 * https://github.com/Mnenmenth
 * https://mnenmenth.com
 */
#ifndef BATTLESHIP_SHIPCONFIG_H
#define BATTLESHIP_SHIPCONFIG_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#define BOARD_SIZE 10

// Split string based on delimeter
void splitString(std::string &in, char delim, std::vector<std::string> &out) {
    std::stringstream ss(in);
    std::string item;
    while (std::getline(ss, item, delim)) {
        out.push_back(item);
    }
}

// Load the x,y,height,width values of each ship into a map from a config file
bool LoadShipConfig(const char* configFile, std::map<std::string, sf::IntRect> &out) {

    // Open file
    std::ifstream file(configFile);
    // If file can be successfully opened
    if(file.is_open()) {

        // Variable to hold current line
        std::string line;

        // For every line in file
        while(std::getline(file, line)) {
            // Index of ':' in the line
            auto colonPos = line.find(':');
            // Get ship name from line
            std::string ship = line.substr(0, colonPos);
            // Get rest from line
            std::string rest = line.substr(colonPos+1);
            // The coordinates in string form
            std::vector<std::string> strCoords;
            // Split coordinates based on ','
            splitString(rest, ',', strCoords);
            sf::IntRect rect;

            // Assign coordinates to rect
            rect.left = std::stoi(strCoords[0]);
            rect.top = std::stoi(strCoords[1]);
            rect.width = std::stoi(strCoords[2]);
            rect.height = std::stoi(strCoords[3]);

            out.insert(std::pair<std::string, sf::IntRect>(ship, rect));
        }

        return true;;
    }
    return false;
}

#endif //BATTLESHIP_SHIPCONFIG_H
