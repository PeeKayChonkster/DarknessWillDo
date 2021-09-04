#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <queue>

class Drawable;
class Runnable;
class Node;

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
	static unsigned int screenWidth, screenHeight;
	static Node root;

	static void callStartCallbacks();
	static void callUpdateCallback(Node* node);
	static void deleteNodes();
	static void drawDrawables();

	virtual void PureStaticClass() = 0;		/// virtual method for prohibition of instancing this class
public:
	App();
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();

	static int run();
	static void callCallbacks();
	static float getDeltaTime();
	static void registerNewNode(Node* node);
	static void registerDrawable(Drawable* drawable);
	static void unregisterDrawable(Drawable* drawable);
	static void registerForDeletion(Node* node);
	static sf::Vector2i getScreenSize();
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