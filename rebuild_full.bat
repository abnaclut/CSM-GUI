:: ============================================================================
:: rebuild_full.bat - Full rebuild with tests and examples
:: ============================================================================
@echo off
setlocal enabledelayedexpansion

echo ============================================================
echo CSM-GUI Full Rebuild (with tests and examples)
echo ============================================================
echo.

:: Remove existing build directory
if exist "build" (
    echo Removing existing build directory...
    rmdir /s /q build
)

:: Create fresh build directory
echo Creating fresh build directory...
mkdir build

:: Download dependencies (if not already present)
echo.
echo Checking dependencies...
if not exist "thirdparty\imgui" (
    echo Downloading ImGui...
    git clone https://github.com/ocornut/imgui.git thirdparty/imgui
    cd thirdparty/imgui
    git checkout v1.91.0-docking
    cd ../..
) else (
    echo ImGui already exists
)

:: Configure CMake with tests and examples
echo.
echo Configuring CMake...
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release ^
    -DCSM_GUI_BUILD_EXAMPLES=ON

:: Build
echo.
echo Building project...
cmake --build build --config Release -j

:: Check for errors
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build failed!
    pause
    exit /b %errorlevel%
)

:: Run tests
echo.
echo Running tests...
ctest --test-dir build --output-on-failure --build-config Release

:: Copy executable to root
echo.
echo Copying executable...
if exist "build\Release\csm_gui_app.exe" (
    copy /Y "build\Release\csm_gui_app.exe" "csm_gui_app.exe"
    echo Executable copied to: csm_gui_app.exe
) else if exist "build\csm_gui_app.exe" (
    copy /Y "build\csm_gui_app.exe" "csm_gui_app.exe"
    echo Executable copied to: csm_gui_app.exe
) else (
    echo [WARNING] Executable not found in build directory
)

:: Copy example executables
echo.
if exist "build\Release\example_custom_theme.exe" (
    copy /Y "build\Release\example_custom_theme.exe" "example_custom_theme.exe"
    echo Example copied to: example_custom_theme.exe
) else if exist "build\example_custom_theme.exe" (
    copy /Y "build\example_custom_theme.exe" "example_custom_theme.exe"
    echo Example copied to: example_custom_theme.exe
)

echo.
echo ============================================================
echo Full rebuild completed successfully!
echo ============================================================
echo.
echo Available executables:
echo   csm_gui_app.exe            - Main GUI application
echo   example_custom_theme.exe   - Custom theme example
echo.
echo Run: csm_gui_app.exe
echo ============================================================
pause