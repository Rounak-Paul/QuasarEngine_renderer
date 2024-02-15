#!/bin/bash

echo "Building shaders..."

input_dir="src/Shader/Code"
output_dir="$2"
vulkanSDKPath="$1"

mkdir -p "$output_dir"

if [ -z "$vulkanSDKPath" ]; then
    echo "VULKAN_SDK path not provided. Please provide it as an argument."
    exit 1
fi

echo "Vulkan SDK path: $vulkanSDKPath"

for file in "$input_dir"/*.vert "$input_dir"/*.frag; do
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    ext="${file##*.}"
    output_file="$output_dir/$filename.$ext.spv"

    echo "$vulkanSDKPath/macOS/bin/glslc" "$file" -o "$output_file"
    "$vulkanSDKPath/macOS/bin/glslc" "$file" -o "$output_file"
done