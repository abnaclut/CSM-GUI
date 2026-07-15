#ifndef CSM_GUI_GUI_THEME_HPP
#define CSM_GUI_GUI_THEME_HPP

#include <imgui.h>
#include <string>

namespace csm_gui
{

  struct Theme
  {
    // Colors
    ImVec4 background;
    ImVec4 background_darker;
    ImVec4 background_darkest;
    ImVec4 foreground;
    ImVec4 foreground_muted;
    ImVec4 accent;
    ImVec4 accent_hover;
    ImVec4 accent_active;
    ImVec4 success;
    ImVec4 error;
    ImVec4 warning;
    ImVec4 info;

    // Font sizes
    float font_size_small;
    float font_size_normal;
    float font_size_large;
    float font_size_title;

    // Spacing
    float padding_small;
    float padding_normal;
    float padding_large;

    // Rounding
    float rounding_small;
    float rounding_normal;
    float rounding_large;

    // Borders
    float border_width;
    bool show_borders;

    static Theme makeDark();
    static Theme makeLight();
    static Theme makeCyberpunk();
    static Theme makeMinimal();

    void apply() const;
  };

  class ThemeManager
  {
  public:
    static ThemeManager& instance();

    void setTheme(const Theme& theme);
    const Theme& getTheme() const;
    void applyCurrentTheme() const;

    // Load custom theme from JSON or INI
    bool loadThemeFromFile(const std::string& path);

    // Save current theme to file
    bool saveThemeToFile(const std::string& path) const;

  private:
    ThemeManager() = default;
    Theme current_theme_;
  };

} // namespace csm_gui

#endif // CSM_GUI_GUI_THEME_HPP