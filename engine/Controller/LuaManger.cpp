#include "LuaManager.h"


LuaManger::LuaManger()
{
	luaState = new sol::state;
	luaState->open_libraries(sol::lib::base);
}

LuaManger::~LuaManger()
{
	luaState->collect_garbage();
}


void LuaManger::LoadScript(std::string& fileName) {

	luaState->script_file(fileName);//loads a file or runs a string of lua code. returns a function result.
	//luaState->load_file(); //returns a lua function that can be executed later.
	//luaState->do_file();  //runs code as a string or from a file. returns a function result./lower lever ver of script(not recomended...)
	
}