#include <iostream>.
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#define windowW 500
#define windowH 500

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void window_Resize_Callback(GLFWwindow* window, int w, int h);

int main(void)
{
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

	//init stuff
	//glfwSetFramebufferSizeCallback(window, window_Resize_Callback);
	glViewport(0,0,windowW, windowH);

	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);


	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		//glDrawArrays(,GL_TRIANGLES);
		
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