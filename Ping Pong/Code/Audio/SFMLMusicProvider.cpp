
#include "stdafx.h"
#include "SFMLMusicProvider.h"
#include "Game.h"
#include "Gamestates.h"


CSFMLMusicProvider::CSFMLMusicProvider() :
	m_songPlaying(nullptr)
{
}

CSFMLMusicProvider::~CSFMLMusicProvider()
{
}

void CSFMLMusicProvider::AddFileToCache(const std::string filename)
{
	auto itr = m_musicCache.cache.find(filename);
	if (itr == m_musicCache.cache.end())
	{
		std::shared_ptr<sf::Music> song = std::shared_ptr<sf::Music>(new sf::Music()); 
		if (!song->openFromFile(filename))
			throw SoundNotFoundException(filename + " could not be found.");
		else
		{
			song->setVolume(60);
			m_musicCache.cache.insert(std::make_pair(filename, song));
		}
	}
	else
		std::cout << "You already added a file under that address" << std::endl;
}

void CSFMLMusicProvider::InitSounds()
{
	AddFileToCache("Content/Music/Sunshine.ogg");
	AddFileToCache("Content/Music/Amie.ogg");
	AddFileToCache("Content/Music/Real Hip Hop.ogg");
	AddFileToCache("Content/Music/Something for Chicago.ogg");
	AddFileToCache("Content/Music/Third Time.ogg");
}

std::shared_ptr<sf::Music> CSFMLMusicProvider::GetAudioFile(const std::string filename) const
{
	auto itr = m_musicCache.cache.find(filename);
	if (itr == m_musicCache.cache.end())
		throw SoundNotFoundException(filename + " could not be found in music cache");
	else
		return itr->second;
}

std::shared_ptr<sf::Music> CSFMLMusicProvider::PickRandomSong() const
{
	std::mt19937::result_type seed = (unsigned int)time(nullptr);
	auto itr = m_musicCache.cache.begin();
	auto random = std::bind(std::uniform_int_distribution<int>(0, m_musicCache.cache.size()), std::mt19937(seed));

	// Pick random key
	std::advance(itr, random());

	// Check to see if iterator points passed .end()
	if (itr == m_musicCache.cache.end())
		itr--;
	return itr->second;
}

void CSFMLMusicProvider::MusicHandler::operator() (CSFMLMusicProvider* provider)
{
	bool runYet = false;
	while (true)
	{
		if (!runYet)
		{
			provider->m_songPlaying = provider->PickRandomSong();
			provider->m_songPlaying->play();
			runYet = true;
		}

		if (gameState == GameState::Exiting)
		{
			provider->m_songPlaying->stop();
			return;
		}
		
		if (provider->m_songPlaying->getStatus() != sf::Music::Playing)
		{
			// Initialize previous song
			std::shared_ptr<sf::Music> prevSong = provider->m_songPlaying;

			// Get random song but make sure the song that just played isn't repeated
			do
			{
				provider->m_songPlaying = provider->PickRandomSong();
			} while (provider->m_songPlaying == prevSong);

			// Play random song
			provider->m_songPlaying->play(); // Same song plays again but different one plays when code is ran through
		}
	}
}

