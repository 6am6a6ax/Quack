#!/bin/bash

echo "Cloning & setting up engine dependencies..."
mkdir -p engine/deps

git --work-tree=engine/deps clone https://github.com/skypjack/entt.git
git --work-tree=engine/deps clone https://github.com/ocornut/imgui.git

echo "Setting up ImGui..."
git --work-tree=engine/deps/imgui checkout docking

echo "Cloning & setting up editor dependencies..."
mkdir -p editor/deps
ln -s engine editor/deps/engine

git --work-tree=editor/deps clone https://github.com/CedricGuillemet/ImGuizmo.git

echo "Setting up model loader dependencies..."
ln -s engine editor/deps/engine

echo "Installing dependencies libraries..."
sudo apt install libglew-dev libglfw3-dev libglm-dev libyaml-dev libassimp-dev libspdlog-dev libstb-dev

echo "Installing CG libraries..."
sudo apt install libgl-dev libgl1-mesa-dev libglu1-mesa-dev libvulkan-dev libxcursor-dev libxi-dev libxinerama-dev libxmu-dev spirv-tools vulkan-tools vulkan-validationlayers-dev

echo "Building project..."
# mkdir build
# cd build
# cmake ..
# make

echo "Done"