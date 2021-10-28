#include "ImGuiLayer.h"
#include "Core/Logger/Logger.h"
#include "Core/Application/Application.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Keg
{
	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (m_ShowDemoWindow)
		{
			ImGui::ShowDemoWindow(&m_ShowDemoWindow);
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &m_ShowDemoWindow);      // Edit bools storing our window open/close state

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		KEG_ENGINE_INFO("Created ImGui Context");
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		KEG_ENGINE_INFO("Created ImGui IO");

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Docking


		GLFWwindow* win = static_cast<GLFWwindow *>(Application::GetInstance()->GetWindow()->GetNativeWindow());

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(win, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


	void ImGuiLayer::OnEvent(Event& e)
	{

	}

#ifdef KEG_DEBUG
	std::string ImGuiLayer::GetDebugName()
	{
		return std::string("ImGuiLayer");
	}
#endif
}