#include "animation.h"
#include "debug.h"
#include "tools.h"


Animation::Animation(std::string name, const std::string& texturePath, unsigned int hframes, float frameTime) : name(name), hframes(hframes), frameTime(frameTime), frame(0), frameWidth(0)
{
	if (!texture.loadFromFile(texturePath))
	{
		Debug::printPersistent("Couldn't load texture. Path: " + texturePath + "; " + PLACE);
	}
	else
	{
		auto textureSize = texture.getSize();
		frameWidth = textureSize.x / hframes;
		boundingRect = sf::IntRect(0, 0, frameWidth, textureSize.y);
		sprite.setTexture(texture);
		sprite.setTextureRect(boundingRect);
		sprite.setOrigin(frameWidth * 0.5f, textureSize.y / 2.0f);
	}
}

Animation::Animation(const Animation& other) : name(other.name), texture(other.texture), hframes(other.hframes), frameTime(other.frameTime), frame(other.frame), 
	frameWidth(other.frameWidth), boundingRect(other.boundingRect)
{
	auto textureSize = texture.getSize();
	sprite.setTexture(texture);
	sprite.setTextureRect(boundingRect);
	sprite.setOrigin(frameWidth * (float(frame) + 0.5f), textureSize.y / 2.0f);
}

Animation::Animation(Animation&& other) : name(other.name), texture(other.texture), hframes(other.hframes), frameTime(other.frameTime), frame(other.frame),
	frameWidth(other.frameWidth), boundingRect(other.boundingRect)
{
	auto textureSize = texture.getSize();
	sprite.setTexture(texture);
	sprite.setTextureRect(boundingRect);
	sprite.setOrigin(frameWidth * (float(frame) + 0.5f), textureSize.y / 2.0f);
}

Animation::~Animation()
{
}

std::string Animation::getName() const noexcept
{
	return name;
}

unsigned int Animation::getHframes() const noexcept
{
	return hframes;
}

unsigned int Animation::getFrame() const noexcept
{
	return frame;
}

unsigned int Animation::getFrameWidth() const noexcept
{
	return frameWidth;
}

float Animation::getFrameTime() const noexcept
{
	return frameTime;
}

void Animation::setPosition(const glm::vec2& vec)
{
	sprite.setPosition(chonky::glm_to_sf_vec(vec));
}

void Animation::setRotation(float angle)
{
	sprite.setRotation(angle);
}
 
void Animation::setScale(const glm::vec2& vec)
{
	sprite.setScale(chonky::glm_to_sf_vec(vec));
}

void Animation::move(const glm::vec2& vec)
{
	sprite.move(chonky::glm_to_sf_vec(vec));
}

void Animation::draw(sf::RenderWindow* window, float playTime)
{
	if (hframes > 1)
	{
 		unsigned int nextFrame = int(std::floor(playTime / frameTime));
		if (nextFrame > hframes) nextFrame = 0;
		setFrame(nextFrame);
	}
	window->draw(sprite);
}

void Animation::setFrame(unsigned int frame) noexcept
{
	if (this->frame == frame)
	{
		return;
	}
	else
	{
		this->frame = frame;
		boundingRect.left = frameWidth * frame;
		sprite.setTextureRect(boundingRect);
	}
}
