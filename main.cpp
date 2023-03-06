#include <iostream>.
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#define windowW 500
#define windowH 500



void window_Resize_Callback(GLFWwindow* window, int w, int h);



int main(void)
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(windowW, windowH, "Engine", NULL, NULL);

	if (!window)
	{
		std::cout << "GLFW window brokey" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad brokey" << std::endl;
		return -1;
	}




	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	//cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void window_Resize_Callback(GLFWwindow* window, int w, int h) {

	glViewport(0, 0, w, h);
}