#include <iostream>
#include <string>

#include "input.h"
#include "shipvariant.h"

int input::intInput() {
    int i;

    while (true) {
        if (std::cin >> i) {
            return i;
        }
        else {
            std::cout << "Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(255, '\n');
        }
    }
}

ShipVariant input::shipVariantInput() {
    int i;

    while (true) {
        if (std::cin >> i) {
            if (i < static_cast<int>(ShipVariant::MAX_SHIP_VARIANT)) {
                return static_cast<ShipVariant>(i);
            }
            else {
                std::cout << "Input out of bounds.\n";
            }
        }
        else {
            std::cout << "Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(255, '\n');
        }
    }
}

std::string input::strInput() {
    std::string i;

    while (true) {
        if (std::getline(std::cin, i)) {
            return i;
        }
        else {
            std::cout << "Please enter a valid string.\n";
            std::cin.clear();
            std::cin.ignore(255, '\n');
        }
    }
}
