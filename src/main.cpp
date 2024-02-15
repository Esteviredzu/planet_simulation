// Created by Romashkin Maksim MK-202

#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <cmath>

const float PI = 3.14159265359;
bool exitFlag = false; // if true, the threads will exit

class Planet {
public:
    std::string name;
    float radiusMovement; // movement radius
    float x; // current coord
    float y;
    float centerX; // center
    float centerY;
    float speed;
    float angle;
    float radiusPlanet; //planet radius

    Planet(std::string name, float speed, float centerX, float centerY, float radiusMovement, float radiusPlanet) : name(name), speed(speed), centerX(centerX), centerY(centerY), radiusMovement(radiusMovement), radiusPlanet(radiusPlanet), angle(0.0f) {
    }

    void move(float deltaTime) {
        angle += speed * deltaTime;
        if (angle >= 360.0f) angle -= 360.0f; 
        float radianAngle = angle * PI / 180.0f;
       
        x = centerX + (radiusMovement * std::cos(radianAngle));
        y = centerY + (radiusMovement * std::sin(radianAngle));
    }
};



void movePlanet(Planet* planet) {
    while (!exitFlag) {
        planet->move(0.04f);
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Planet Simulation");

    Planet Earth("Earth", 50, 500.0f, 500.0f, 40.0f, 50.0f);
    Planet Mars("Mars", 200, 300.0f, 300.0f, 150.0f, 39.0f); 
    Planet Moon("Moon", 400, 500.0f, 500.0f, 150.0f, 20.0f);

    std::thread earthThread(movePlanet, &Earth);
    std::thread marsThread(movePlanet, &Mars);
    std::thread moonThread(movePlanet, &Moon);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                exitFlag = true;
            }
            
        }

        window.clear(sf::Color::Black);

        // Earth
        sf::CircleShape earthShape(Earth.radiusPlanet);
        earthShape.setFillColor(sf::Color::Blue);
        earthShape.setPosition(Earth.x, Earth.y);
        window.draw(earthShape);

        // Mars
        sf::CircleShape marsShape(Mars.radiusPlanet);
        marsShape.setFillColor(sf::Color::Red);
        marsShape.setPosition(Mars.x, Mars.y);
        window.draw(marsShape);

        // Moon
        sf::CircleShape moonShape(Moon.radiusPlanet);
        moonShape.setFillColor(sf::Color::White);
        moonShape.setPosition(Moon.x, Moon.y);
        window.draw(moonShape);

        window.display();
    }

    earthThread.join();
    marsThread.join();
    moonThread.join();


    return 0;
}
