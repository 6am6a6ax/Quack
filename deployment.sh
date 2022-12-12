#!/bin/bash

path=$(pwd)

#=======================================================================================================================

echo "Cloning & setting up engine dependencies..."
mkdir -p $path/engine/deps

git clone https://github.com/skypjack/entt.git $path/engine/deps/entt
git clone https://github.com/ocornut/imgui.git $path/engine/deps/imgui

echo "Setting up ImGui..."
cd $path/engine/deps/imgui
git checkout docking
cp $path/cmake/imgui/* .

#=======================================================================================================================

echo "Cloning & setting up editor dependencies..."
mkdir -p $path/editor/deps

cd $path/editor/deps
ln -s $path/engine engine

git clone https://github.com/CedricGuillemet/ImGuizmo.git $path/editor/deps/imguizmo

echo "Setting up ImGuizmo..."
cd $path/editor/deps/imguizmo
cp $path/cmake/imguizmo/* .
mkdir -p $path/editor/deps/imguizmo/deps
cd $path/editor/deps/imguizmo/deps
ln -s $path/engine/deps/imgui imgui

#=======================================================================================================================

echo "Setting up model loader dependencies..."
mkdir -p $path/model_loader/deps
cd $path/model_loader/deps
ln -s $path/engine engine

#=======================================================================================================================

echo "Installing dependencies libraries..."
sudo apt install libglew-dev libglfw3-dev libglm-dev libyaml-dev libassimp-dev libspdlog-dev libstb-dev

echo "Installing CG libraries..."
sudo apt install libgl-dev libgl1-mesa-dev libglu1-mesa-dev libvulkan-dev libxcursor-dev libxi-dev libxinerama-dev libxmu-dev spirv-tools vulkan-tools vulkan-validationlayers-dev

echo "Building project..."
mkdir $path/build
cd $path/build
cmake ..
make

echo "Done"