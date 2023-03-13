#include <iostream>.
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

void window_Resize_Callback(GLFWwindow* window, int w, int h);

int main(void)
{
	GameEngine::Get().Run();
	
}

void window_Resize_Callback(GLFWwindow* window, int w, int h) {

	glViewport(0, 0, w, h);
}