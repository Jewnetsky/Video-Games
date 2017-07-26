
#ifndef SFMLMUSICPROVIDER_H
#define SFMLMUSICPROVIDER_H


class CGame;

#include "stdafx.h"
#include "IAudioProvider.h"


class CSFMLMusicProvider : public IAudioProvider
{
public:
	CSFMLMusicProvider();
	~CSFMLMusicProvider();

	void AddFileToCache(const std::string filename);

	// Overriding functions
	void InitSounds();


	std::shared_ptr<sf::Music> GetAudioFile(const std::string filename) const;
	std::shared_ptr<sf::Music> PickRandomSong() const;

private:
	AudioCache<std::shared_ptr<sf::Music>> m_musicCache; 
	std::shared_ptr<sf::Music> m_songPlaying;

public:
	class MusicHandler
	{
	public:
		void operator() (CSFMLMusicProvider* provider);
	};
};
#endif




