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

void LuaManager::RunInitMethod() {
	if (init.valid())
		init();
}

void LuaManager::RunUpdateMethod() {
	if (update.valid()) 
		update();
}

bool LuaManager::Expose_Engine() {
	
	//Get main update loop
	LoadScript("resources/scripts/main.lua");
	update = GetFunction("update");
	init = GetFunction("init");

	//expose game object
	Expose_CPPClass<GameObject>("GameObject",
		sol::constructors<GameObject()>(),
		"name",&GameObject::name,
		"position",&GameObject::position,
		"rotation",&GameObject::rotation,
		"scale",&GameObject::scale
		);

	return true;

}


void LuaManager::LoadScript(const std::string& fileName) {

	try
	{
		luaState.script_file(fileName);//loads a file or runs a string of lua code. returns a function result.
	}
	catch (const sol::error e)
	{
		std::cout << "ERROR: Could not load Loading Script File!" << e.what() << std::endl;
	}
	//luaState->load_file(); //returns a lua function that can be executed later.
	//luaState->do_file();  //runs code as a string or from a file. returns a function result./lower lever ver of script(not recomended...)
	
}

sol::function LuaManager::GetFunction(const char* luaName) {

	sol::function func = luaState[luaName];
	if (func.valid()) {
		return func;
	}
	else {
		std::cout << "ERROR: Could not retrieve function: " << luaName << std::endl;
		return sol::nil;
	}

}
