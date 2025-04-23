#include "Application.h"

//base variables
const unsigned int WINDOW_WIDTH = 400;
const unsigned int WINDOW_HEIGHT = 600;

App::App()
{
    //window setup
    window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Doodle Jump");
    window.setFramerateLimit(60);

    //mc setup
    doodler = sf::RectangleShape(sf::Vector2f(30, 30));
    doodler.setFillColor(sf::Color::Blue);
    doodler.setPosition(sf::Vector2f(100, 100));

    //font setup
    assert(font.openFromFile("Doodle.ttf"));

    //variables
    doodlerVelocity = sf::Vector2f(0, 0);
    ml = false;
    mr = false;
    inLevel = true;
    score = 0;

    //platforms
    nextPlat = 1;
    for (int i = 0; i < 6; ++i) 
    {
        nextPlat = (rand() % 5) + 1;
        switch (nextPlat) 
        {
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
}

void App::WinUpdate()
{
    while (const std::optional event = window.pollEvent()) 
    {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
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
}

void App::Update()
{
    sf::Text dscore = sf::Text(font, to_string(score));
    dscore.setFillColor(sf::Color::Black);
    dscore.setPosition(sf::Vector2f(0, 0));
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
            doodlerVelocity.y = -1;
        }
        //move platforms if mc at top
        if (doodler.getPosition().y == 0) {
            for (auto& platform : platforms) {
                platform->move(-doodlerVelocity.y);
                score -= (int)doodlerVelocity.y / 10;
            }
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
            int here = true;
            if (platform->colliding(doodler.getPosition(), doodler.getSize()) && doodlerVelocity.y >= 0) {
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

        //window displayw
        window.clear(sf::Color::White);
        window.draw(doodler);
        for (auto platform : platforms) {
            window.draw(platform->getrect());
        }
        dscore.setString(to_string(score));
        window.draw(dscore);
        window.display();
    }

    //if player has lost
    else {
        window.clear(sf::Color::White);
        sf::Text yltext = sf::Text(font, "YOU LOSE");
        yltext.setFillColor(sf::Color::Black);
        yltext.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 50));
        window.draw(yltext);
        dscore.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2 - 20));
        window.draw(dscore);
        window.display();
    }
}

void App::Render()
{

}

bool App::IsOpen()
{
    return window.isOpen();
}
