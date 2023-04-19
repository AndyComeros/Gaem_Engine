#include <GUIRenderer.h>

GUIRenderer::GUIRenderer() : window(nullptr), currentGUI(0) {
	//set flags
	flags = ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoBackground;
}

GUIRenderer::~GUIRenderer() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUIRenderer::Init(GLFWwindow* nwindow) {

	window = nwindow;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui::StyleColorsDark();

	ResourceManager::Get().LoadTexture("exitsplash", "resources/textures/exit.png");
}

void GUIRenderer::Draw() {


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool use_work_area = true;
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
	ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
	
	ImGui::Begin("window",nullptr,flags);

	switch (currentGUI)
	{
	case 0:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		GUI_InGame();
		break;
	case 1:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		GUI_Exit();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIRenderer::SwitchMenu(int nGUI) {
	currentGUI = nGUI;
}

void GUIRenderer::GUI_Main() {

}

void GUIRenderer::GUI_Settings() {

}

void GUIRenderer::GUI_Exit() {
	
	
	//probably do some centering func
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float size = ((width < height) ? width : height)/2;
	float availX = ImGui::GetContentRegionAvail().x;
	float availY = ImGui::GetContentRegionAvail().y;
	float offX = (availX - size) * 0.5;
	float offY = (availY - size) * 0.5;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offX);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offY);

	//draw exit button
	Texture* splash = ResourceManager::Get().GetTexture("exitsplash");
	if (ImGui::ImageButton((void*)(intptr_t)splash->ID, ImVec2(size, size))) {
		exit(0);
	}

}

void GUIRenderer::GUI_Debug() {}

void GUIRenderer::GUI_InGame()
{
	

}

