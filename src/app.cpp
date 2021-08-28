#include "app.h"
#include "player.h"
#include "debug.h"
#include <ranges>
#include "drawable.h"
#include "runnable.h"

#define START_SCREEN_WIDTH 800u
#define START_SCREEN_HEIGHT 800u
#define START_RESOURCE_PATH "Resources/"
#define START_TEXTURES_PATH "Textures/"
#define START_FONTS_PATH "Fonts/"

// static members initialization //
const std::string App::RESOURCES_PATH = START_RESOURCE_PATH;
const std::string App::TEXTURES_PATH = RESOURCES_PATH + START_TEXTURES_PATH;
const std::string App::FONTS_PATH = RESOURCES_PATH + START_FONTS_PATH;
std::vector<Runnable*> App::runnables;
std::vector<Drawable*> App::drawables;
unsigned int App::screenWidth = START_SCREEN_WIDTH;
unsigned int App::screenHeight = START_SCREEN_HEIGHT;
///////////////////////////////////


App::App() : deltaTime(0.0f), window(nullptr)
{
}

App::~App()
{

}

int App::run()
{
    ////// Initialization //////
    sf::RenderWindow newWindow(sf::VideoMode(START_SCREEN_WIDTH, START_SCREEN_HEIGHT), "SFML Tutorial!", sf::Style::Close);
    window = &newWindow;
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);
    sf::Event event;
    Player player(TEXTURES_PATH + "PlayerIdleDown.png");
    player.setPosition(glm::vec2(screenWidth / 2.0f, screenHeight / 2.0f));
    ////////////////////////////


    while (window->isOpen())
    {
        // update deltaTime
        deltaTime = clock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::Resized)
            {
                // adjust view matrix to window size
                sf::View newView(sf::FloatRect(0.0f, 0.0f, (float)event.size.width, (float)event.size.height));
                screenWidth = event.size.width;
                screenHeight = event.size.height;
                window->setView(newView);
            }
        }

        // clear the window with black color
        window->clear(sf::Color::Black);


        //// Game Loop ////
        callUpdateCallbacks();
        ///////////////////



        // draw everything here...
        Debug::draw(window); // draw debug messages
        drawDrawables();
        // end the current frame
        window->display();
    }
	return 0;
}

void App::callUpdateCallbacks()
{
    for (auto& r : runnables)
    {
        r->update(deltaTime);
    }
}

void App::drawDrawables()
{
    for (auto& d : drawables)
    {
        d->draw(window);
    }
}

float App::getDeltaTime() const
{
	return deltaTime;
}

void App::registerRunnable(Runnable* runnable)
{
    if (std::ranges::find(runnables, runnable) != runnables.end())
    {
        return;
    }
    else
    {
        runnables.push_back(runnable);
    }
}

void App::registerDrawable(Drawable* drawable)
{
    if (std::ranges::find(drawables, drawable) != drawables.end())
    {
        return;
    }
    else
    {
        drawables.push_back(drawable);
    }
}

void App::unregisterRunnable(Runnable* runnable)
{
    auto iter = std::ranges::find(runnables, runnable);
    if (iter != runnables.end())
    {
        runnables.erase(iter);
    }
    else
    {
        return;
    }
}

void App::unregisterDrawable(Drawable* drawable)
{
    auto iter = std::ranges::find(drawables, drawable);
    if (iter != drawables.end())
    {
        drawables.erase(iter);
    }
    else
    {
        return;
    }
}

sf::Vector2i App::getScreenSize()
{
    return sf::Vector2i(screenWidth, screenHeight);
}
