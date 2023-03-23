#include <sol/sol.hpp>

class LuaManger
{
public:
	LuaManger();
	~LuaManger();
	void LoadScript(const std::string& fileNames);
private:
	
	sol::state* luaState = nullptr;
};

