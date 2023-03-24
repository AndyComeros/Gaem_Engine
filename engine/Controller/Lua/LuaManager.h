#include <sol/sol.hpp>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();
	void LoadScript(const std::string& fileNames);

private:
	
	sol::state* luaState = nullptr;
};

