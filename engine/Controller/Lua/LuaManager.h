#include <sol/sol.hpp>

#include <GameObject.h>
#include <ResourceManager.h>

class LuaManager
{
public:
	LuaManager();

	~LuaManager();
	
	void RunInitMethod();
	void RunUpdateMethod(double dt);
	bool Expose_Engine();

	void LoadScript(const std::string& fileNames);
	
	sol::function GetFunction(const char* luaName);

	template<typename T>
	T GetData(const char* luaName) {
		try {
			return luaState.get<T>(luaName);
		}
		catch (const sol::error& e) {
			std::cout << "ERROR: could not get data: " << e.what() << std::endl;
			return T();
		}
	}

	template<typename T>
	void Expose_CPPVariable(const char* luaName, T cppData) {
		luaState.set(luaName, cppData);
	}

	template<typename Func, typename... Args>
	void Expose_CPPFunction(const char* luaName, Func cppFunc, Args... args) {
		luaState.set_function(luaName, cppFunc, args);
	}

	template<typename Class, typename... Args>
	void Expose_CPPClass(const char* luaName, Args... args) {
		luaState.new_usertype<Class>(luaName, args...);
	}



private:

	sol::state luaState;
	sol::function update;
	sol::function init;
};

