#include "SoundEngine.h"


SoundEngine& SoundEngine::Get() {

	static SoundEngine e_instance;
	return e_instance;
}

SoundEngine::SoundEngine()
{
	_Engine = irrklang::createIrrKlangDevice();
}

void SoundEngine::addSound(std::string name, std::string filePath)
{
	_Audio.insert({ name, filePath });
}

void SoundEngine::playSound(std::string name, glm::vec3 pos)
{
	_Engine->play3D(_Audio.at(name).c_str(), { pos.x, pos.y, pos.z }, false, false, false);
}

void SoundEngine::addMusic(std::string filePath)
{
	_Music = _Engine->play3D(filePath.c_str(), { 0, 0, 0 }, true, false, true);
	_Music->setVolume(0.5f);
}

void SoundEngine::setListenerPos(glm::vec3 pos)
{
	_Engine->setListenerPosition({ pos.x, pos.y, pos.z }, { 0, 0, 1 });
}

void SoundEngine::setMusicPos(glm::vec3 pos)
{
	_Music->setPosition({ pos.x, pos.y, pos.z });
}

void SoundEngine::toggleMusic(bool state)
{
	_Music->setIsPaused(state);
}

void SoundEngine::drop()
{
	_Music->drop();
	_Engine->drop();
}
