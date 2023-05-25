#pragma once
#include <irrKlang/irrKlang.h>
#include <map>
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

	void setListenerPos(glm::vec3 pos);

	void setMusicPos(glm::vec3 pos);

	void toggleMusic(bool state);

	void drop();

private:

	irrklang::ISoundEngine* _Engine;
	std::map<std::string, std::string> _Audio;
	irrklang::ISound* _Music;
};

