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

void LuaManager::RunUpdateMethod(double dt) {
	if (update.valid()) 
		update(dt);
}

void LuaManager::Expose_Engine() {

	//Get main update loop
	LoadScript("resources/scripts/main.lua");
	update = GetFunction("update");
	init = GetFunction("init");

	//expose game object
	Expose_CPPClass<GameObject>("GameObject",
		sol::constructors<GameObject()>(),
		"name", &GameObject::name,
		"position", &GameObject::position,
		"rotation", &GameObject::rotation,
		"scale", &GameObject::scale
		);

	//expose resource manager class
	Expose_CPPClass<ResourceManager>("ResourceManager",
		sol::no_constructor,
		"Get", &ResourceManager::Get,

		"CreateGameObject", &ResourceManager::CreateGameObject,
		"LoadTexture", &ResourceManager::LoadTexture,
		"LoadModel", &ResourceManager::LoadModel,
		"LoadShader", &ResourceManager::LoadShader,

		"GetTexture", &ResourceManager::GetTexture,
		"GetModel", &ResourceManager::GetModel,
		"GetShader", &ResourceManager::GetShader

		);
	//expose resource manager singleton
	luaState["resources"] = &ResourceManager::Get();


	//expose scene object
	Expose_CPPClass<Scene>("Scene",
		sol::constructors<Scene()>(),
		"AddObject", &Scene::AddObject
		);

	//expose camera
	Expose_CPPClass<Camera>("Camera",
		sol::constructors<Camera()>(),
		"LookAt", &Camera::LookAt,
		"position", &Camera::position,
		"rotation", &Camera::rotation,
		"aspectRatio", &Camera::aspectRatio,
		"FOV", &Camera::FOV,
		"nearPlane", &Camera::nearPlane,
		"farPlane", &Camera::farPlane
		);

	//expose lights
	Expose_CPPClass<PointLight>("PointLight",
		sol::constructors<PointLight>(),
		"position", &PointLight::position,
		"diffuse", &PointLight::diffuse,
		"quadratic", &PointLight::quadratic
		);
	Expose_CPPClass<SpotLight>("SpotLight",
		sol::constructors<SpotLight>(),
		"position", &SpotLight::position,
		"direction", &SpotLight::direction,
		"maxAngle", &SpotLight::maxAngle,
		"featherAngle", &SpotLight::featherAngle,
		"diffuse", &SpotLight::diffuse,
		"specular", &SpotLight::specular,
		"constant", &SpotLight::constant,
		"linear", &SpotLight::linear,
		"quadratic", &SpotLight::quadratic
		);
	Expose_CPPClass<DirectionLight>("DirectionLight",
		sol::constructors<DirectionLight>(),
		"direction", &DirectionLight::direction,
		"diffuse", &DirectionLight::diffuse,
		"specular", &DirectionLight::specular
		);
	Expose_CPPClass<Lights>("Lights",
		sol::constructors<Lights>(),
		"ambientLight", &Lights::ambientLight,
		"pointLights", &Lights::pointLights,
		"spotLights", &Lights::spotLights,
		"directionLights", &Lights::directionLights
		);

	//expose terrain
	Expose_CPPClass<Terrain>("Terrain",
		sol::constructors<Terrain, Terrain(std::string&, float, float, float)>(),
		"GetHeight", &Terrain::GetHeight
		);
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
