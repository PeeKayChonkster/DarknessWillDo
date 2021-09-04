#include "app.h"
#include "player.h"
#include "debug.h"
#include <ranges>
#include "drawable.h"
#include "node.h"
#include <iostream>
#include <exception>
#include <random>
#include <ranges>

#define START_SCREEN_WIDTH 800u
#define START_SCREEN_HEIGHT 800u
#define START_RESOURCE_PATH "Resources/"
#define START_TEXTURES_PATH "Textures/"
#define START_FONTS_PATH "Fonts/"
#define START_SOUND_PATH "Sound/Sound/"
#define START_MUSIC_PATH "Sound/Music/"

// static members initialization //
const std::string App::RESOURCES_PATH = START_RESOURCE_PATH;
const std::string App::TEXTURES_PATH = RESOURCES_PATH + START_TEXTURES_PATH;
const std::string App::FONTS_PATH = RESOURCES_PATH + START_FONTS_PATH;
const std::string App::SOUND_PATH = RESOURCES_PATH + START_SOUND_PATH;
const std::string App::MUSIC_PATH = RESOURCES_PATH + START_MUSIC_PATH;
sf::RenderWindow* App::window = nullptr;
sf::Clock App::clock;
float App::deltaTime = 0.0f;
std::vector<Drawable*> App::drawables;
std::queue<Node*> App::newNodes;
std::queue<Node*> App::deletionQueue;

Node App::root(glm::vec2(0.0f, 0.0f));

unsigned int App::screenWidth = START_SCREEN_WIDTH;
unsigned int App::screenHeight = START_SCREEN_HEIGHT;
///////////////////////////////////


App::App()
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
    srand(time(NULL));
    Player player(glm::vec2(screenWidth / 2.0f, screenHeight / 2.0f));
    addToRoot(&player);
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
            else if (event.type == sf::Event::Resized)
            {
                // adjust view matrix to window size
                sf::View newView(sf::FloatRect(0.0f, 0.0f, (float)event.size.width, (float)event.size.height));
                screenWidth = event.size.width;
                screenHeight = event.size.height;
                window->setView(newView);
            }
            else
            {
                player.pushEvent(event);
            }
        }

        // clear the window with black color
        window->clear(sf::Color::Black);


        //// Game Loop ////
        callCallbacks();
        ///////////////////



        // draw everything here...
        Debug::draw(window); // draw debug messages
        drawDrawables();    // draw all registered drawables
        // end the current frame
        window->display();
    }
	return 0;
}

void App::callCallbacks()
{
    deleteNodes();
    callUpdateCallback(&root);
}

void App::callStartCallbacks()
{
    while (!newNodes.empty())
    {
        newNodes.front()->start();
        newNodes.pop();
    }
}

void App::callUpdateCallback(Node* node)
{
    const auto children = node->getChildren();
    for(int i = 0; i < children->size(); i++)
    {
        App::callUpdateCallback((*children)[i]);
    }
    node->update(App::getDeltaTime());
}

void App::deleteNodes()
{
    while (!deletionQueue.empty())
    {
        Node* n = deletionQueue.front();
        delete n;
        deletionQueue.pop();
    }
}

void App::drawDrawables()
{
    for (auto& d : drawables)
    {
        d->draw(window);
    }
}

float App::getDeltaTime()
{
	return deltaTime;
}

void App::registerNewNode(Node* node)
{
    auto children = node->getChildren();
    for (auto& c : *children)
    {
        registerNewNode(c);
    }
    node->start();
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

void App::registerForDeletion(Node* node)
{
    deletionQueue.push(node);
}

sf::Vector2i App::getScreenSize()
{
    return sf::Vector2i(screenWidth, screenHeight);
}

const sf::RenderWindow* App::getWindow()
{
    return window;
}

const void App::addToRoot(Node* node)
{
    auto children = root.getChildren();
    if (auto result = std::ranges::find(*children, node); result == children->end())
    {
        root.addChild(node);
    }
}

const void App::removeFromRoot(Node* node)
{
    root.removeChild(node);
}
