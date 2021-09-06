#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <queue>

class Drawable;
class Runnable;
class Node;
class Player;

/// <summary>
/// Pure static class.
/// </summary>
class App
{
private:
	static sf::RenderWindow* window;
	static sf::Clock clock;
	static float deltaTime;
	static std::vector<Drawable*> drawables;
	static std::queue<Node*> newNodes;
	static std::queue<Node*> deletionQueue;
	static unsigned int windowWidth, windowHeight;
	static Node root;
	static Player* player;

	static int init(const std::string windowName, unsigned int width = 800u, unsigned int height = 600u, bool fullscreen = false);
	static void handleEvents();
	static void clean();
	static void update();
	static void render();
	static void callStartCallbacks();
	static void callUpdateCallback(Node* node);
	static void deleteNodes();
	static void drawDrawables();

	virtual void ThisIsPureStaticClass() = 0;		/// virtual method to prohibit instantiation of this class
public:
	App();
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();

	static int run(const std::string windowName, unsigned int width = 800u, unsigned int height = 600u, bool fullscreen = false);
	static float getDeltaTime();
	static void registerNewNode(Node* node);
	static void registerDrawable(Drawable* drawable);
	static void unregisterDrawable(Drawable* drawable);
	static void registerForDeletion(Node* node);
	static sf::Vector2i getWindowSize();
	static const sf::RenderWindow* getWindow();
	static const void addToRoot(Node* node);
	static const void removeFromRoot(Node* node);

	// Paths //
	static const std::string RESOURCES_PATH;
	static const std::string TEXTURES_PATH;
	static const std::string FONTS_PATH;
	static const std::string SOUND_PATH;
	static const std::string MUSIC_PATH;
	///////////
	
};