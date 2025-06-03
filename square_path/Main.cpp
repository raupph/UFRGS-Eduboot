#include <iostream>
#include "libs/EdubotLib.hpp"

// Configuration constants
constexpr double INITIAL_SIDE = 0.20;       // Initial square side in meters
constexpr int TIME_PER_METER = 2000;        // Time (ms) to travel 1 meter at given speed
constexpr int NUMBER_OF_SQUARES = 3;        // Number of squares to draw
constexpr double LINEAR_VELOCITY = 0.5;     // Constant linear velocity in m/s
constexpr int ROTATION_DELAY_MS = 1000;     // Delay after rotation in ms
constexpr int STOP_DELAY_MS = 200;          // Delay after stopping in ms

// Function to draw a square with a given side length
void drawSquare(EdubotLib& robot, double sideLength) {
    const int moveTime = static_cast<int>(sideLength * TIME_PER_METER);

    for (int i = 0; i < 4; ++i) {				  // One time for each side of the square
        robot.move(LINEAR_VELOCITY);                // Set linear velocity
        robot.sleepMilliseconds(moveTime);          // Move forward
        robot.stop();
        robot.sleepMilliseconds(STOP_DELAY_MS);     // Pause before rotating

        robot.rotate(90);                           // Rotate 90 degrees clockwise
        robot.sleepMilliseconds(ROTATION_DELAY_MS); // Pause after rotating
    }
}

int main() {
    EdubotLib robot;

    if (robot.connect()) {
        double side = INITIAL_SIDE;

        for (int i = 0; i < NUMBER_OF_SQUARES; ++i) {
            drawSquare(robot, side);
            side *= 2; // Double the side length for the next square
        }

        robot.disconnect();
    } else {
        std::cerr << "Failed to connect to the robot." << std::endl;
    }

    return 0;
}
