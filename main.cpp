#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <TerrainManager.h>

int main(void)
{

	class MyClass {
		MyClass() {}

	public:
		int MyFunc() {
			return 69;
		}

	};

	LuaManager luaManager;

/*	luaManager.Expose_CPPClass<GameObject>("GameObject",
		sol::constructors<GameObject()>(),
		"name", &GameObject::name
		);*/

	luaManager.Expose_CPPClass<MyClass>("MyClass",
		sol::constructors<MyClass()>(),
		"MyFunc", &MyClass::MyFunc);


	luaManager.LoadScript("resources/scripts/main.lua");

	std::string name = luaManager.GetData<std::string>("x");

	std::cout << name;


	/*	Scene& scene = GameEngine::Get().scene;
	std::vector<std::string> textures_faces = {
		"resources/textures/skybox/Synthwave2/Right.png",
		"resources/textures/skybox/Synthwave2/Left.png",
		"resources/textures/skybox/Synthwave2/Top.png",
		"resources/textures/skybox/Synthwave2/Bottom.png",
		"resources/textures/skybox/Synthwave2/Front.png",
		"resources/textures/skybox/Synthwave2/Back.png"
	};
	scene.skybox = new CubeMap(textures_faces);


	

	//Run the game
	GameEngine::Get().Run();*/
}
