#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_SENSORS = 5;
const int SENSOR_RADIUS = 20;
const int SENSOR_SPACING = 100;

struct Sensor {
    int x, y;
    float value;
};

int main() {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 100.0);

    // Create sensors
    vector<Sensor> sensors;
    for (int i = 0; i < NUM_SENSORS; i++) {
        Sensor s;
        s.x = SENSOR_SPACING * (i + 1);
        s.y = WINDOW_HEIGHT / 2;
        s.value = dis(gen);
        sensors.push_back(s);
    }

    // Create SFML window
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sensor Data Visualization");

    // Main loop
    while (window.isOpen()) {
        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Update sensor values
        for (auto& s : sensors) {
            s.value = dis(gen);
        }

        // Clear the window
        window.clear(Color::White);

        // Draw the sensors
        for (const auto& s : sensors) {
            CircleShape circle(SENSOR_RADIUS);
            circle.setFillColor(Color(static_cast<int>(s.value), 0, 0));
            circle.setPosition(s.x - SENSOR_RADIUS, s.y - SENSOR_RADIUS);
            window.draw(circle);
        }

        // Display the updated frame
        window.display();

        // Delay for a short time
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}