#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "glm/vec2.hpp"

class Animation
{
private:
	std::string name;
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned int hframes;
	unsigned int frame;
	unsigned int frameWidth;
	float frameTime;
	sf::IntRect boundingRect;

	void setFrame(unsigned int frame) noexcept;
public:

	Animation() = delete;
	Animation(std::string name, const std::string& texturePath, unsigned int hframes, float frameTime);
	Animation(const Animation& other);
	Animation(Animation&& other);
	Animation& operator=(const Animation& other) = delete;
	~Animation();

	// getters/setters //
	std::string getName() const noexcept;
	unsigned int getHframes() const noexcept;
	unsigned int getFrame() const noexcept;
	float getFrameTime() const noexcept;

	void setPosition(const glm::vec2& vec);
	void setRotation(float angle);
	void setScale(const glm::vec2& vec);
	void move(const glm::vec2& vec);
	/////////////


	void draw(sf::RenderWindow* window, float playTime);
};

