#include "LuaManager.h"


LuaManager::LuaManager()
{
	luaState;
	luaState.open_libraries(sol::lib::base);
}

LuaManager::~LuaManager()
{
	luaState.collect_garbage();
}

void LuaManager::LoadScript(const std::string& fileName) {

	try
	{
		luaState.script_file(fileName);//loads a file or runs a string of lua code. returns a function result.
	}
	catch (const sol::error e)
	{
		std::cout << "Error Loading Script File!" << e.what() << std::endl;
	}
	//luaState->load_file(); //returns a lua function that can be executed later.
	//luaState->do_file();  //runs code as a string or from a file. returns a function result./lower lever ver of script(not recomended...)
	
}

template<typename T>
void LuaManager::Expose_CPPVariable(const char* luaName, T cppData) {
	luaState.set(luaName,cppData);
}

template<typename Func, typename... Args>
void LuaManager::Expose_CPPFunction(const char* luaName, Func cppFunc, Args... args) {
	luaState.set_function(luaName, cppFunc, args);
}

template<typename Class, typename... Args>
void LuaManager::Expose_CPPClass(const char* luaName, Args... args) {
	luaState.set_usertype<Class>(luaName,args);
}