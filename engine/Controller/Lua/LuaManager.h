#include <sol/sol.hpp>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();
	void LoadScript(const std::string& fileNames);
	
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

	template<typename T>
	T GetData(const char* luaName) {

		sol::optional<T> result = luaState.get<T>(luaName);

		if (result)
			return result;

		std::cerr << "Could not retrieve" << luaName << std::endl;
		return T();
		
	}



private:

	sol::state luaState;;
};

