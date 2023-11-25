@echo off
setlocal enabledelayedexpansion

echo Building shaders...

set input_dir=Shader\Code
set output_dir=Shader\bin
set vulkanSDKPath=%1

if "%vulkanSDKPath%"=="" (
    echo VULKAN_SDK path not provided. Please provide it as an argument.
    exit /b 1
)

echo Vulkan SDK path: %vulkanSDKPath%

for %%i in (%input_dir%\*.vert %input_dir%\*.frag) do (
    set filename=%%~ni
    set ext=%%~xi
    set output_file=%output_dir%\!filename!!ext!.spv

    echo %vulkanSDKPath%\Bin\glslc.exe "%%i" -o "!output_file!"
    %vulkanSDKPath%\Bin\glslc.exe "%%i" -o "!output_file!"
)