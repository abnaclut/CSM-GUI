:: ============================================================================
:: setup_dependencies.bat - Download and setup third-party dependencies
:: ============================================================================
@echo off

echo ============================================================
===
CSM-GUI Dependencies Setup
echo ============================================================
echo.

:: Create thirdparty directory
if not exist "thirdparty" (
    echo Creating thirdparty directory...
    mkdir thirdparty
)

:: Check for Git
where git >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] Git is not installed or not in PATH.
    echo Please install Git: https://git-scm.com/download/win
    pause
    exit /b 1
)

:: Download ImGui
echo.
echo Downloading ImGui...
if exist "thirdparty\imgui" (
    echo ImGui already exists, updating...
    cd thirdparty\imgui
    git pull
    git checkout v1.91.0-docking
    cd ../..
) else (
    git clone https://github.com/ocornut/imgui.git thirdparty/imgui
    cd thirdparty/imgui
    git checkout v1.91.0-docking
    cd ../..
)

:: Download GLFW
echo.
echo Downloading GLFW...
if exist "thirdparty\glfw" (
    echo GLFW already exists, updating...
    cd thirdparty\glfw
    git pull
    cd ../..
) else (
    git clone https://github.com/glfw/glfw.git thirdparty/glfw
    cd thirdparty/glfw
    git checkout 3.4
    cd ../..
)

:: Download CSM-CMD
echo.
echo Downloading CSM-CMD...
if exist "thirdparty\csm_cmd" (
    echo CSM-CMD already exists, updating...
    cd thirdparty\csm_cmd
    git pull
    cd ../..
) else (
    git clone https://github.com/abnaclut/CSM-CMD.git thirdparty/csm_cmd
    cd thirdparty/csm_cmd
    git checkout 1.0.0
    cd ../..
)

echo.
echo ============================================================
===
Dependencies setup completed!
echo ============================================================
echo.
echo Installed:
echo   ImGui      - thirdparty/imgui
echo   GLFW       - thirdparty/glfw
echo   CSM-CMD    - thirdparty/csm_cmd
echo.
echo Run rebuild.bat or rebuild_full.bat to build the project.
pause