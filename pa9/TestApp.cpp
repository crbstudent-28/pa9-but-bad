#include "TestApp.h"

//base variables
const unsigned int WINDOW_WIDTH = 400;
const unsigned int WINDOW_HEIGHT = 600;

TestApp::TestApp()
{
    //window setup
    window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Doodle Jump");
    window.setFramerateLimit(60);

    //mc setup
    doodler = sf::RectangleShape(sf::Vector2f(30, 30));
    doodler.setTexture(new sf::Texture(sf::Image("Character.png")));

    //mc setup
    back = sf::RectangleShape(sf::Vector2f(400, 600));
    back.setTexture(new sf::Texture(sf::Image("BackgroundTest.png")));

    //font setup
    assert(font.openFromFile("Doodle.ttf"));

    platforms.push_back(new Platform(20, 555));
    platforms.push_back(new BreakPlatform(100, 555));
    platforms.push_back(new BreakPlatform(180, 555));
    platforms.push_back(new SuperPlatform(260, 555));
    platforms.push_back(new MovePlatform(320, 555));

    // set variables
    doodler.setPosition(sf::Vector2f(100, 100));
    doodlerVelocity = sf::Vector2f(0, 0);
    ml = false;
    mr = false;
    inLevel = true;
}

bool TestApp::WinUpdate()
{
    while (const std::optional event = window.pollEvent())
    {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {

            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                window.close();
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
            {
                ml = true;
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
            {
                mr = true;
            }

        }
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->scancode == sf::Keyboard::Scancode::Left)
            {
                ml = false;
            }

            if (keyReleased->scancode == sf::Keyboard::Scancode::Right)
            {
                mr = false;
            }
        }
    }
    return false;
}

void TestApp::Update()
{
    //if player hasnt lost
    if (inLevel) {
        //mc movement control
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
                    doodlerVelocity.x += 0.35f;
                }
                if (doodlerVelocity.x > 0) {
                    doodlerVelocity.x -= 0.35f;
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
            inLevel = false;
        }
        if (doodler.getPosition().x < 0) {
            doodler.setPosition(sf::Vector2f(WINDOW_WIDTH, doodler.getPosition().y));
        }
        if (doodler.getPosition().x > WINDOW_WIDTH) {
            doodler.setPosition(sf::Vector2f(0, doodler.getPosition().y));
        }

        //check for platform trigger or deletion
        int i = 0;
        for (auto& platform : platforms) {
            if (!platform)
                continue;
            platform->update();
            if (platform->colliding(doodler.getPosition(), doodler.getSize()) && doodlerVelocity.y >= 0) {
                if (platform->trigger(&doodler, &doodlerVelocity)) {
                    delete platform;
                    platform = nullptr;
                }
            }
        }
        //window displayw
        window.clear(sf::Color::White);
        window.draw(back);
        window.draw(doodler);
        for (auto platform : platforms) {
            if(platform)
                window.draw(platform->getrect());
        }
        window.display();
    }
}