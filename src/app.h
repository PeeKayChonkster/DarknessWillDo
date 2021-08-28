#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Drawable;
class Runnable;

class App
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
	float deltaTime;
	static std::vector<Runnable*> runnables;
	static std::vector<Drawable*> drawables;
	static unsigned int screenWidth, screenHeight;

	void callUpdateCallbacks();
	void drawDrawables();
public:
	App();
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();

	int run();
	float getDeltaTime() const;
	static void registerRunnable(Runnable* runnable);
	static void registerDrawable(Drawable* drawable);
	static void unregisterRunnable(Runnable* runnable);
	static void unregisterDrawable(Drawable* drawable);
	static sf::Vector2i getScreenSize();

	// Paths //
	static const std::string RESOURCES_PATH;
	static const std::string TEXTURES_PATH;
	static const std::string FONTS_PATH;
	///////////
	
};