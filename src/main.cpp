#include "csm_gui/gui_application.hpp"
#include <iostream>
#ifndef IMGUI_INCLUDED
#include <imgui.h>
#endif



int main()
{
  csm_gui::GuiApplication app;

  if (!app.initialize())
  {
    std::cerr << "Failed to initialize GUI" << std::endl;
    return 1;
  }

  // add buttons
  app.setCustomRenderCallback([]()
  {
    ImGui::Text(" ");
    ImGui::Separator();
    ImGui::Text("Custom Section");

    if (ImGui::Button("My Custom Button"))
    {
      std::cout << "Custom button clicked!" << std::endl;
    }
  });

  app.run();

  return 0;
}