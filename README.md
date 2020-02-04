# DreamCatcher
An attempt to reverse engineer the CyberFlix DreamFactory engine

The goal of this project is to learn enough about DreamFactory's
internal workings and data formats that a modern implementation can be written so that DreamFactory based games can be run comfortably on modern operating systems.

Currently I am using [x64dbg](https://github.com/x64dbg/x64dbg) to step the code and [Ghidra](https://github.com/NationalSecurityAgency/ghidra)
to analyze and re-implementing various functions inside the game's binary by injecting my own DLL (DreamCatcher) by adding it to the game's
import table using [CFF Explorer](https://ntcore.com/?page_id=388).
Once the DLL is loaded it will patch various instructions to make the game easier to debug and call our implementation instead where applicable.

This is a similar approach to other reverse engineering projects such as
[OpenTTD](https://github.com/OpenTTD/OpenTTD) and [OpenRCT2](https://github.com/OpenRCT2/OpenRCT2).

This project's main target is DUST: A Tale of the Wired West.
Although you can still buy it on [Amazon](https://www.amazon.com/DUST-Tale-Wired-West-pc/dp/B0007G89H8/) from third party sellers,
I unfortunately I don't know of any digital distributors.
Despite the fact that CyberFlix is out of business I'm not sure if it is safe to upload it anywhere but I'm sure you can find it out there on the internet somewhere.
The SHA-1 hash of the DF.exe I am using is *97462977fc15277ba186a64baffe978d658413a9*

# Documentation

I have not yet had time to write up any formal documentation of what I've found,
however I have added some commentary in the header files.

I highly recommend reading [this incomplete writeup](https://forum.xentax.com/viewtopic.php?t=17905#p140851) on the DreamFactory container format.

# Building

I am using Visual Studio 2019.

The DreamCatcher solution should reside inside a subfolder inside DUST's game directory.

The build output should place DreamCatcher.dll next to DF.exe.

Naturally since DreamFactory is 32-bit, the solution only is configured for x86 builds.

# Contributing

Please do contribute! This is a big project for one person so I can use all the help I can get.

If you are interested in helping with this project or otherwise in reverse engineering then please see this [list](https://github.com/wtsxDev/reverse-engineering).
I also recommend checking out the [XeNTaX](https://forum.xentax.com/) community and reading [this incomplete writeup](https://forum.xentax.com/viewtopic.php?t=17905#p140851) on the DreamFactory container format.
