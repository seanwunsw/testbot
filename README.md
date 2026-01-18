# More than a packetlogger (In progress)
This repo is a fork from [BladeTiger12/nostale-packetlogger](https://gitlab.com/BladeTiger12/nostale-packetlogger)

As somehow I cant compile the version that he got on that repo but somehow his release is working just fine

# How to use
You will need the following dlls in the folder of the game before you inject the dll into the game

- Zydis.dll
- asmjit.dll
- asmtk.dll
- qt5core.dll
- qt5gui.dll
- qt5widgets.dll
- qt5network.dll



# How to compile
This tutorial might not be the best practice but it did works for me, allow me to work on this project very quickly.

1. Open the project with visual studio 2022
2. Run vcpkg install --triplet x86-windows in /PacketLogger
3. Change PacketLogger.vcxproj line 59 and 60 to ur include path
4. Change PacketLogger.vcxproj and replace line 226 from
```
<AdditionalDependencies>
    PolyHook_2.lib;capstone_dll.lib;%(AdditionalDependencies)
</AdditionalDependencies> 
```

to (formatted just for readability)
```
<AdditionalDependencies>
    PolyHook_2.lib;%(AdditionalDependencies)
</AdditionalDependencies> 
```

# To do list
- Fetch item price from baz
- optimise performance as right now it hung up easily
- attack speed?
- github action to compile this in to a release
- make it so if it doesnt need all the other dll for polyhook2

