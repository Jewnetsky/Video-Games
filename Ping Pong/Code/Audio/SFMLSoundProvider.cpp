#include "stdafx.h"
#include "SFMLSoundProvider.h"


CSFMLSoundProvider::CSFMLSoundProvider()
{
}

CSFMLSoundProvider::~CSFMLSoundProvider()
{
}

void CSFMLSoundProvider::AddFileToCache(const std::string filename, sf::SoundBuffer& buffer)
{
	auto itr = m_soundCache.cache.find(filename);
	if (itr == m_soundCache.cache.end())
	{
		if (buffer.loadFromFile(filename))
		{
			std::shared_ptr<sf::Sound> sound = std::shared_ptr<sf::Sound>(new sf::Sound());
			
			// Set buffer
			sound->setBuffer(buffer);
			m_soundCache.cache.insert(std::make_pair(filename, sound));
		}
		else
			throw SoundNotFoundException(filename + " could not be loaded from file.");
	}
	else
	{
		std::cout << filename << " has already been added to the sound cache." << std::endl;
	}
}

std::shared_ptr<sf::Sound> CSFMLSoundProvider::GetAudioFile(const std::string filename) const
{
	auto itr = m_soundCache.cache.find(filename);
	if (itr == m_soundCache.cache.end())
		throw SoundNotFoundException(filename + " could not be found in the sound cache.");
	else
		return itr->second;
}

void CSFMLSoundProvider::PlaySound(const std::string filename)
{
	auto itr = m_soundCache.cache.at(filename);
	itr->play();
}

void CSFMLSoundProvider::InitSounds()
{
	AddFileToCache("Content/Sounds/Bounce.ogg", m_buffer[0]);
	AddFileToCache("Content/Sounds/Goal.ogg", m_buffer[1]);
}
