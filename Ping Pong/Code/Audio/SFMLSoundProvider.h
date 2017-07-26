
#ifndef SFMLSOUNDPROVIDER_H
#define SFMLSOUNDPROVIDER_H

#include "stdafx.h"
#include "IAudioProvider.h"


class CSFMLSoundProvider : public IAudioProvider
{
public:
	CSFMLSoundProvider();
	~CSFMLSoundProvider();

	// Overriding functions
	void AddFileToCache(const std::string filename, sf::SoundBuffer& buffer);

public:
	std::shared_ptr<sf::Sound> GetAudioFile(const std::string filename) const;
	void PlaySound(const std::string filename);
	void InitSounds();

private:
	static const int MAX_SOUNDS = 2;
	sf::SoundBuffer m_buffer[MAX_SOUNDS];
	AudioCache<std::shared_ptr<sf::Sound>> m_soundCache;
};
#endif

