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

	//expose vec3
	Expose_CPPClass<glm::vec3>("vec3",
		sol::constructors<glm::vec3(), glm::vec3(float,float,float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z
		);

	//expose game object
	Expose_CPPClass<GameObject>("GameObject",
		sol::constructors<GameObject()>(),
		"name", &GameObject::name,
		"position", &GameObject::position,
		"rotation", &GameObject::rotation,
		"scale", &GameObject::scale
		);

	//expose terrain
	Expose_CPPClass<Terrain>("Terrain",
		sol::constructors<Terrain(), Terrain(std::string&, float, float, float)>(),
		sol::base_classes, sol::bases<GameObject>(),
		"GetHeight", &Terrain::GetHeight,
		"SetTextureHeights",&Terrain::SetTextureHeights,
		"GetSize",&Terrain::GetSize,
		"SetTextureScale",&Terrain::SetTextureScale
		);

	//expose resource manager class
	Expose_CPPClass<ResourceManager>("ResourceManager",
		sol::no_constructor,
		"Get", &ResourceManager::Get,

		"CreateGameObject", &ResourceManager::CreateGameObject,
		"CreateTerrain", &ResourceManager::CreateTerrain,
		"LoadTexture", &ResourceManager::LoadTexture,
		"LoadModel", &ResourceManager::LoadModel,
		"LoadShader", &ResourceManager::LoadShader,
		"LoadCubemap", &ResourceManager::LoadCubemap,

		"GetTexture", &ResourceManager::GetTexture,
		"GetModel", &ResourceManager::GetModel,
		"GetShader", &ResourceManager::GetShader,
		"GetCubeMap", &ResourceManager::GetCubeMap
		);
	//expose resource manager singleton
	luaState["resources"] = &ResourceManager::Get();

	//expose skybox
	Expose_CPPClass<CubeMap>("CubeMap",
		sol::constructors<CubeMap, CubeMap(std::vector<std::string>&)>()
		);

	//expose scene object
	Expose_CPPClass<Scene>("Scene",
		sol::constructors<Scene()>(),
		"AddObject", &Scene::AddObject,
		"AddLights", &Scene::AddLights,
		"SetSkybox", &Scene::SetSkybox,
		"GetCamera", &Scene::GetCamera,
		"GetLights", &Scene::GetLights
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
		sol::constructors<PointLight, PointLight(glm::vec3, glm::vec3, glm::vec3,float,float,float)>(),
		"position", &PointLight::position,
		"diffuse", &PointLight::diffuse,
		"quadratic", &PointLight::quadratic
		);
	Expose_CPPClass<SpotLight>("SpotLight",
		sol::constructors<SpotLight, SpotLight(glm::vec3, glm::vec3,float,float, glm::vec3, glm::vec3,float,float,float)>(),
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
		sol::constructors<DirectionLight, DirectionLight(glm::vec3, glm::vec3, glm::vec3)>(),
		"direction", &DirectionLight::direction,
		"diffuse", &DirectionLight::diffuse,
		"specular", &DirectionLight::specular
		);
	Expose_CPPClass<Lights>("Lights",
		sol::constructors<Lights>(),
		"ambient", &Lights::ambient,
		"point", &Lights::point,
		"spot", &Lights::spot,
		"direction", &Lights::direction,
		"SetAmbient", &Lights::SetAmbient,
		"AddDirectionLight", &Lights::AddDirectionLight,
		"AddPointLight", &Lights::AddPointLight,
		"AddSpotLight", &Lights::AddSpotLight
		);
}


void LuaManager::LoadScript(const std::string& fileName) {
	try
	{
		luaState.script_file(fileName);
	}
	catch (const sol::error e)
	{
		std::cout << "ERROR: Could not load Loading Script File!" << e.what() << std::endl;
	}
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
