#include "LuaManager.h"


LuaManager::LuaManager()
{
	luaState = new sol::state;
	luaState->open_libraries(sol::lib::base);
}

LuaManager::~LuaManager()
{
	luaState->collect_garbage();
}

void LuaManager::LoadScript(const std::string& fileName) {

	try
	{
		luaState->script_file(fileName);//loads a file or runs a string of lua code. returns a function result.
	}
	catch (const sol::error e)
	{
		std::cout << "Error Loading Script File!" << e.what() << std::endl;
	}
	//luaState->load_file(); //returns a lua function that can be executed later.
	//luaState->do_file();  //runs code as a string or from a file. returns a function result./lower lever ver of script(not recomended...)
	
}

void LuaManager::RegisterFunction(void*cppFunc , const std::string luaName) {
	luaState->set_function(luaName, *cppFunc);

}