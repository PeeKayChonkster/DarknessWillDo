#include "audioPlayer.h"
#include <ranges>
#include <random>
#include "debug.h"
#include "glm/common.hpp"

bool AudioPlayer::loadSound(std::string name, std::string path, float volume)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(path))
	{
		Debug::printPersistent("Couldn't load sound file. Path: " + path + "; " + PLACE);
		return false;
	}
	volume = glm::clamp(volume, 0.0f, 100.0f);
	soundLibrary.push_back(LibrarySound(buffer, name, volume));
	return true;
}

bool AudioPlayer::loadMusic(std::string name, std::string path, float volume)
{
	if (!music.openFromFile(path))
	{
		Debug::printPersistent("Couldn't open music file. Path: " + path + "; " + PLACE);
		return false;
	}
	volume = glm::clamp(volume, 0.0f, 100.0f);
	musicLibrary.push_back(LibraryMusic(path, name, volume));
	return true;
}

void AudioPlayer::playSound(std::string name, bool randomPitch)
{
	auto predicat = [&name](const LibrarySound& sound) { return name == sound.name; };
	auto result = std::ranges::find_if(soundLibrary, predicat);
	if (result != soundLibrary.end())
	{
		trim();
		auto &sound = sounds.emplace_back();
		sound.setVolume(result->volume);
		this->randomPitch = randomPitch;
		sound.setBuffer(result->buffer);
		// set random pitch
		if (randomPitch) sound.setPitch(1.0f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * maxPitchDeviation);
		else sound.setPitch(1.0f);
		currentAudioName = name;
		sound.play();
	}
	else
	{
		Debug::printPersistent("Couldn't find sound file in sound library. Name: " + name + "; " + PLACE);
	}
}

void AudioPlayer::playMusic(std::string name)
{
	auto predicat = [&name](const LibraryMusic& music) { return name == music.name; };
	auto result = std::ranges::find_if(musicLibrary, predicat);
	if (result != musicLibrary.end())
	{
		music.openFromFile(result->path);
		music.setVolume(result->volume);
		currentAudioName = name;
		music.play();
	}
	else
	{
		Debug::printPersistent("Couldn't find music file in music library. Name: " + name + "; " + PLACE);
	}
	
}

void AudioPlayer::trim()
{
	auto predicate = [this](const sf::Sound& sound) { return !isPlaying(sound); };
	auto toErase = std::ranges::remove_if(sounds, predicate);
	sounds.erase(toErase.begin(), toErase.end());
}

void AudioPlayer::stop()
{
	for (auto& s : sounds)
		s.stop();
	music.stop();
}

bool AudioPlayer::isPlaying(const sf::Sound& sound) const noexcept
{
	return sound.getStatus() == sf::Sound::Playing;
}

unsigned int AudioPlayer::getNumberOfSoundSources() const noexcept
{
	return sounds.size();
}
