#include <sol/sol.hpp>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();
	void LoadScript(const std::string& fileNames);
	
	template<typename T>
	void Expose_CPPVariable(const char* luaName, T cppData);

	template<typename Func, typename... Args>
	void Expose_CPPFunction(const char* luaName,Func cppFunc, Args... args);

	template<typename Class, typename... Args>
	void Expose_CPPClass(const char* luaName,Args... args);


private:

	sol::state luaState;;
};

