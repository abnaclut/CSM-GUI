#include "csm_gui/gui_application.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <iostream>

using ImVec2 = ImVec2;

namespace csm_gui
{

  GuiApplication::GuiApplication() = default;
  GuiApplication::~GuiApplication() { shutdown(); }

  bool GuiApplication::initialize(int width, int height)
  {
    window_width_ = width;
    window_height_ = height;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      return false;
    }

    if (!createWindow(width, height, "CSM GUI"))
    {
      std::cerr << "Failed to create window" << std::endl;
      glfwTerminate();
      return false;
    }

    if (!setupImGui())
    {
      std::cerr << "Failed to setup ImGui" << std::endl;
      destroyWindow();
      glfwTerminate();
      return false;
    }

    initialized_ = true;
    running_ = true;

    return true;
  }

  void GuiApplication::run()
  {
    if (!initialized_)
    {
      std::cerr << "Application not initialized" << std::endl;
      return;
    }

    while (running_ && !glfwWindowShouldClose(window_))
    {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      render();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window_);
    }
  }

  void GuiApplication::shutdown()
  {
    running_ = false;
    initialized_ = false;

    shutdownImGui();
    destroyWindow();
    glfwTerminate();
  }

  void GuiApplication::setCustomRenderCallback(std::function<void()> callback)
  {
    custom_render_callback_ = std::move(callback);
  }

  void GuiApplication::render()
  {
    // ImGui::GetIO() for window size
    ImGuiIO& io = ImGui::GetIO();

    ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    ImGui::Begin("CSM GUI", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoSavedSettings);

    renderTestUI();

    if (custom_render_callback_)
    {
      custom_render_callback_();
    }

    ImGui::End();
  }

  void GuiApplication::renderTestUI()
  {
    ImGui::Text("CSM GUI Application");
    ImGui::Separator();

    if (ImGui::Button("Button 1", ImVec2(120, 30)))
    {
      std::cout << "Button 1 clicked!" << std::endl;
    }

    ImGui::SameLine();

    if (ImGui::Button("Button 2", ImVec2(120, 30)))
    {
      std::cout << "Button 2 clicked!" << std::endl;
    }

    ImGui::SameLine();

    if (ImGui::Button("Button 3", ImVec2(120, 30)))
    {
      std::cout << "Button 3 clicked!" << std::endl;
    }

    ImGui::Separator();

    static bool checkbox_value = false;
    ImGui::Checkbox("Test Checkbox", &checkbox_value);

    static float slider_value = 0.5f;
    ImGui::SliderFloat("Test Slider", &slider_value, 0.0f, 1.0f);

    static char input_text[256] = "";
    ImGui::InputText("Test Input", input_text, sizeof(input_text));

    ImGui::Separator();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.8f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.7f, 0.9f, 1.0f));
    if (ImGui::Button("Styled Button", ImVec2(150, 40)))
    {
      std::cout << "Styled button clicked!" << std::endl;
    }
    ImGui::PopStyleColor(2);

    ImGui::Text(" ");
    ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.6f, 1.0f), "Status: Ready");
  }

  void GuiApplication::glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
  }

  bool GuiApplication::createWindow(int width, int height, const std::string& title)
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) { return false; }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1);
    return true;
  }

  void GuiApplication::destroyWindow()
  {
    if (window_)
    {
      glfwDestroyWindow(window_);
      window_ = nullptr;
    }
  }

  bool GuiApplication::setupImGui()
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window_, true)) { return false; }
    if (!ImGui_ImplOpenGL3_Init("#version 330 core")) { return false; }

    return true;
  }

  void GuiApplication::shutdownImGui()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

} // namespace csm_gui