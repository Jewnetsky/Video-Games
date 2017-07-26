
#ifndef AUDIOPROVIDER_H
#define AUDIOPROVIDER_H

#include "stdafx.h"


class IAudioProvider
{
public:
	IAudioProvider() {};
	virtual ~IAudioProvider() {};

	// Pure virtual functions
	virtual void InitSounds() = 0;

	template<typename T>
	struct AudioCache
	{
		std::map<std::string, T> cache; 
	};

public:
	class SoundNotFoundException : public std::runtime_error
	{
	public:
		SoundNotFoundException(const std::string &msg) :
			std::runtime_error(msg)
		{}
	};
};
#endif
