#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <queue>

class Drawable;
class Runnable;

class App
{
private:
	static sf::RenderWindow* window;
	sf::Clock clock;
	static float deltaTime;
	static std::vector<Runnable*> runnables;
	static std::vector<Drawable*> drawables;
	static std::queue<Runnable*> newRunnables;
	static unsigned int screenWidth, screenHeight;

	void callUpdateCallbacks();
	void drawDrawables();
public:
	App();
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();

	int run();
	static float getDeltaTime();
	static void registerRunnable(Runnable* runnable);
	static void registerDrawable(Drawable* drawable);
	static void unregisterRunnable(Runnable* runnable);
	static void unregisterDrawable(Drawable* drawable);
	static sf::Vector2i getScreenSize();
	static const sf::RenderWindow* getWindow();

	// Paths //
	static const std::string RESOURCES_PATH;
	static const std::string TEXTURES_PATH;
	static const std::string FONTS_PATH;
	///////////
	
};