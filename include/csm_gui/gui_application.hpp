#ifndef CSM_GUI_GUI_APPLICATION_HPP
#define CSM_GUI_GUI_APPLICATION_HPP

#include <string>
#include <functional>

struct GLFWwindow;

namespace csm_gui
{

  class GuiApplication
  {
  public:
    GuiApplication();
    ~GuiApplication();

    bool initialize(int width = 1280, int height = 720);
    void run();
    void shutdown();

    void setCustomRenderCallback(std::function<void()> callback);

  private:
    void render();
    void renderTestUI();

    static void glfwErrorCallback(int error, const char* description);

    bool createWindow(int width, int height, const std::string& title);
    void destroyWindow();
    bool setupImGui();
    void shutdownImGui();

    GLFWwindow* window_ = nullptr;
    bool running_ = false;
    bool initialized_ = false;

    int window_width_ = 1280;
    int window_height_ = 720;

    std::function<void()> custom_render_callback_;
  };

} // namespace csm_gui

#endif // CSM_GUI_GUI_APPLICATION_HPP