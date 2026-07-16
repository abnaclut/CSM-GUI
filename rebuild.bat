@echo off
echo Building CSM-GUI...

if exist build rmdir /s /q build
mkdir build

cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j

if exist build\csm_gui_app.exe (
  copy build\csm_gui_app.exe .
  echo Build successful! Run: csm_gui_app.exe
) else (
  echo Build failed
)

pause