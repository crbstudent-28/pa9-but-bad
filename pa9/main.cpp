#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Platform.h"

const unsigned int WINDOW_WIDTH = 400;
const unsigned int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Doodle Jump");
    window.setFramerateLimit(60);
    srand(time(0));
    int nextPlat = 1;
    sf::RectangleShape doodler(sf::Vector2f(30, 30));
    doodler.setFillColor(sf::Color::Blue);
    doodler.setPosition(sf::Vector2f(100, 100));
    doodler.setOrigin(sf::Vector2f(15, 1));

    std::deque<Platform*> platforms;
    for (int i = 0; i < 6; ++i) {
        nextPlat = (rand() % 5) + 1;
        switch (nextPlat) {
        case 1:
            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        case 2:
            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        case 3:
            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        case 4:
            platforms.push_back(new SuperPlatform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        case 5:
            platforms.push_back(new BreakPlatform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        default:
            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), WINDOW_HEIGHT - 30 - i * 100));
            break;
        }
        
    }

    sf::Vector2f doodlerVelocity(0, 0);
    int score = 0;
    sf::Font font;
    font.openFromFile("Doodle.ttf");
    sf::Text dscore(font, to_string(score));
    dscore.setFillColor(sf::Color::Black);
    dscore.setPosition(sf::Vector2f(0, 0));
    bool ml = false;
    bool mr = false;
    bool active = true;
    sf::Text yltext(font, "YOU LOSE");
    yltext.setFillColor(sf::Color::Black);
    yltext.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 50));

    while (window.isOpen()) {
        if (active) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                    window.close();
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                        ml = true;
                    }

                    if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                        mr = true;
                    }

                }
                if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                    if (keyReleased->scancode == sf::Keyboard::Scancode::Left) {
                        ml = false;
                    }

                    if (keyReleased->scancode == sf::Keyboard::Scancode::Right) {
                        mr = false;
                    }
                }
            }
            doodlerVelocity.y += 1.25;


            if (ml) {
                doodlerVelocity.x -= 5;
            }
            else if (mr) {
                doodlerVelocity.x += 5;
            }
            else {
                if ((-1 < doodlerVelocity.x) && (doodlerVelocity.x < 1)) {
                    doodlerVelocity.x = 0;
                }
                else if (!mr && !ml) {
                    if (doodlerVelocity.x < 0) {
                        doodlerVelocity.x += 0.35;
                    }
                    if (doodlerVelocity.x > 0) {
                        doodlerVelocity.x -= 0.35;
                    }
                }

            }
            if (doodlerVelocity.x > 6) {
                doodlerVelocity.x = 6;
            }
            if (doodlerVelocity.x < -6) {
                doodlerVelocity.x = -6;
            }
            if (doodlerVelocity.y > 7.5) {
                doodlerVelocity.y = 7.5;
            }
            doodler.move(doodlerVelocity);
            if (doodler.getPosition().y < 0) {
                doodler.setPosition(sf::Vector2f(doodler.getPosition().x, 0));
            }
            if (doodler.getPosition().y > WINDOW_HEIGHT) {
                active = false;
            }
            if (doodler.getPosition().y == 0) {
                for (auto& platform : platforms) {
                    platform->rect->move(sf::Vector2f(0, -doodlerVelocity.y));
                    score -= doodlerVelocity.y / 10;
                }
                std::cout << "Platforms moved\n";
            }
            if (doodler.getPosition().x < 0) {
                doodler.setPosition(sf::Vector2f(WINDOW_WIDTH, doodler.getPosition().y));
            }
            if (doodler.getPosition().x > WINDOW_WIDTH) {
                doodler.setPosition(sf::Vector2f(0, doodler.getPosition().y));
            }
            int i = 0;
            for (auto& platform : platforms) {
                int here = true;
                if (doodler.getGlobalBounds().findIntersection(platform->rect->getGlobalBounds()) && doodlerVelocity.y >= 0) {
                    if (platform->trigger(&doodler, &doodlerVelocity)) {
                        delete platform;
                        platforms.erase(platforms.begin() + i);
                        here = false;
                    }
                }
                if (here) {
                    if (platform->rect->getPosition().y > WINDOW_HEIGHT) {
                        platforms.pop_front();
                        nextPlat = (rand() % 5) + 1;
                        switch (nextPlat) {
                        case 1:
                            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        case 2:
                            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        case 3:
                            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        case 4:
                            platforms.push_back(new SuperPlatform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        case 5:
                            platforms.push_back(new BreakPlatform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        default:
                            platforms.push_back(new Platform(rand() % (WINDOW_WIDTH - 60), 0));
                            break;
                        }
                    }
                }
                i++;
            }

            window.clear(sf::Color::White);
            window.draw(doodler);
            for (auto platform : platforms) {
                window.draw(platform->getrect());
            }
            dscore.setString(to_string(score));
            window.draw(dscore);
            window.display();
        }
        else {
            window.clear(sf::Color::White);
            window.draw(yltext);
            dscore.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2 - 20));
            window.draw(dscore);
            window.display();
        }
    }
    return 0;
}