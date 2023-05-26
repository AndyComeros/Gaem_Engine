#pragma once
#include <irrKlang/irrKlang.h>
#include <map>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#pragma comment(lib, "irrKlang.lib")
class SoundEngine
{
public:
	SoundEngine();

	static SoundEngine& Get();

	void addSound(std::string name, std::string filePath);

	void playSound(std::string name, glm::vec3 pos);

	void addMusic(std::string filePath);

	void setVolume(float volume);

	void setMusicVolume(float volume);

	void setListenerPos(glm::vec3 pos);

	void setMusicPos(glm::vec3 pos);

	void toggleMusic(bool state);

	void drop();

	void playSoundLoop(std::string name, glm::vec3 pos,float vol);

	void stopSoundLoop(std::string name);

private:

	irrklang::ISoundEngine* _Engine;
	std::map<std::string, std::string> _Audio;
	irrklang::ISound* _Music;

	std::map<std::string, irrklang::ISound*> loopedAudio;
};

