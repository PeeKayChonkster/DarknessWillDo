#pragma once
#include <vector>
#include <string>
#include "SFML/Audio.hpp"

class AudioPlayer
{
private:
	struct LibrarySound
	{
		sf::SoundBuffer buffer;
		std::string name;
		float volume = 100.0f;

		LibrarySound() = default;
		LibrarySound(const sf::SoundBuffer buffer, std::string name, float volume)
		{
			this->buffer = buffer;
			this->name = name;
			this->volume = volume;
		}
	};

	struct LibraryMusic
	{
		std::string path;
		std::string name;
		float volume = 100.0f;

		LibraryMusic() = default;
		LibraryMusic(std::string path, std::string name, float volume)
		{
			this->path = path;
			this->name = name;
			this->volume = volume;
		}
	};

	std::vector<sf::Sound> sounds;
	sf::Music music;
	std::vector<LibrarySound> soundLibrary;
	std::vector<LibraryMusic> musicLibrary;
	std::string currentAudioName;

	bool randomPitch = false;
	float maxPitchDeviation = 0.1f;
	float volume = 100.0f;

	void trim();
public:
	
	bool loadSound(std::string name, std::string path, float volume = 100.0f);
	bool loadMusic(std::string name, std::string path, float volume = 100.0f);
	void playSound(std::string name, bool randomPitch = false);
	void playMusic(std::string name);
	void stop();
	bool isPlaying(const sf::Sound& sound) const noexcept;
	unsigned int getNumberOfSoundSources() const noexcept;
};

