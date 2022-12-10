#!/bin/bash

rm -rf engine/deps
rm -rf editor/deps
rm -rf model_loader/deps

path=$(pwd)

echo "Cloning & setting up engine dependencies..."
mkdir -p $path/engine/deps

git clone https://github.com/skypjack/entt.git $path/engine/deps/entt
git clone https://github.com/ocornut/imgui.git $path/engine/deps/imgui

echo "Setting up ImGui..."
cd $path/engine/deps/imgui
git checkout docking

echo "Cloning & setting up editor dependencies..."
mkdir -p $path/editor/deps

cd $path/editor/deps
ln -s $path/engine engine

git clone https://github.com/CedricGuillemet/ImGuizmo.git $path/editor/deps/imguizmo

echo "Setting up model loader dependencies..."
mkdir -p $path/model_loader/deps
cd $path/model_loader/deps
ln -s $path/engine engine

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