#include "Camera.h"
#include <iostream>

sf::Vector2f Camera::Delta = sf::Vector2f(0, 0);
sf::Vector2f Camera::Location = sf::Vector2f(0, 0);
float Camera::Zoom = 1;


void Camera::CameraMovement(double DeltaTime)
{
    Camera::Delta = sf::Vector2f(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        Camera::Delta += sf::Vector2f(0, 400 * DeltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        Camera::Delta += sf::Vector2f(0, -400 * DeltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Camera::Delta += sf::Vector2f(400 * DeltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Camera::Delta += sf::Vector2f(-400 * DeltaTime, 0);
    }
    //currently mouse wheel is in the main loop


    Camera::Location += Camera::Delta*(1/Zoom);
}

float Camera::GetDistance(sf::Vector2f a, sf::Vector2f b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    float d = x * x + y * y;



    return pow(d,0.5);
}
