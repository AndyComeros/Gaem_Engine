#include <GUIRenderer.h>

GUIRenderer::GUIRenderer() : window(nullptr), currentGUI(0) {
	//set flags
	flags = ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoTitleBar;
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
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		GUI_Manual();
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIRenderer::SwitchMenu(int nGUI) {
	currentGUI = nGUI;
}

void GUIRenderer::GUI_Main() {
	ImGui::Begin("window", nullptr, flags);
	ImGui::End();
}

void GUIRenderer::GUI_Settings() {
	ImGui::Begin("window", nullptr, flags);

	ImGui::End();
}

void GUIRenderer::GUI_Exit() {
	
	ImGui::Begin("window", nullptr, flags | ImGuiWindowFlags_NoBackground);
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

	ImGui::End();
}

void GUIRenderer::GUI_Manual()
{
	ImGui::Begin("window", nullptr, flags);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);
	TextCenteredOnLine("Controls:",0.5);
	TextCenteredOnLine("Forward: W",0.5);
	TextCenteredOnLine("Reverse: S",0.5);
	TextCenteredOnLine("Turn Left: A",0.5);
	TextCenteredOnLine("Turn Right: D",0.5);
	TextCenteredOnLine("Toggle wireframe: K",0.5);
	TextCenteredOnLine("Exit Game: X",0.5);

	if (ButtonCenteredOnLine("Return", 0.5)) {
		SwitchMenu(0);
	}

	ImGui::End();
}

void GUIRenderer::GUI_Debug() {
	ImGui::Begin("window", nullptr, flags);

	ImGui::End();
}

void GUIRenderer::GUI_InGame()
{
	ImGui::Begin("window", nullptr, flags | ImGuiWindowFlags_NoBackground);
	char str[20];
	sprintf(str, "%.2f", Renderer::Get().GetFPS());
	ImGui::Text(str);
	ImGui::End();
}

void GUIRenderer::TextCenteredOnLine(const char* label, float alignment) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	ImGui::PushItemWidth(400);
	ImGui::Text(label);

}

bool GUIRenderer::ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
{
	ImGuiStyle& style = ImGui::GetStyle();
	float width = 0.0f;
	width += style.ItemSpacing.x;

	width += 200.0f;
	AlignForWidth(width, 0.5);

	return ImGui::Button(label, ImVec2(width, 50));
}

void GUIRenderer::AlignForWidth(float width, float alignment)
{
	ImGuiStyle& style = ImGui::GetStyle();
	float avail = ImGui::GetContentRegionAvail().x;
	float off = (avail - width) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}
