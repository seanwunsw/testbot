# More than a packetlogger (In progress)
This repo is a fork from [BladeTiger12/nostale-packetlogger](https://gitlab.com/BladeTiger12/nostale-packetlogger)

As somehow I cant compile the version that he got on that repo but somehow his release is working just fine

# How to use
You will need the following dlls in the folder of the game before you inject the dll into the game

- qt5core.dll
- qt5gui.dll
- qt5widgets.dll
- qt5network.dll



# How to compile
This tutorial might not be the best practice but it did works for me, allow me to work on this project very quickly.

1. Open the project with visual studio 2022
2. Install qt vs tools through extensions
3. Install qt 5.15.2_msvc2019 32
4. Run vcpkg install --triplet x86-windows-static in /PacketLogger
5. Compile the project in Release x86

- optimise performance as right now it hung up easily(maybe now it works?)
- github action to compile this in to a release
- [x] make it so if it doesnt need all the other dll for polyhook2

