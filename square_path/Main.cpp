#include <iostream>
#include "libs/EdubotLib.hpp"

// Configuration constants
#define INITIAL_SIDE 0.20         // Initial square side in meters
#define TIME_PER_METER 2000       // Time (ms) to travel 1 meter at given speed
#define NUMBER_OF_SQUARES 3       // Number of squares to draw

// Function to draw a square with a given side length
void drawSquare(EdubotLib* robot, double sideLength) {
    for (int i = 0; i < 4; i++) {
        robot->move(0.5); // Set linear velocity
        robot->sleepMilliseconds(sideLength * TIME_PER_METER); // Move forward
        robot->stop();
        robot->sleepMilliseconds(200);
        
        robot->rotate(90); // Rotate 90 degrees clockwise
        robot->sleepMilliseconds(1000);
    }
}

int main() {
    EdubotLib* robot = new EdubotLib();

    if (robot->connect()) {
        double side = INITIAL_SIDE;

        for (int i = 0; i < NUMBER_OF_SQUARES; i++) {
            drawSquare(robot, side);
            side *= 2; // Double the side length for next square
        }

        robot->disconnect();
    } else {
        std::cout << "Failed to connect to the robot." << std::endl;
    }

    return 0;
}
