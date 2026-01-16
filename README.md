SIMPLE 3D RENDERER IN C USING SDL3

As the title suggests, this 3d renderer runs entirely on C using the SDL3 library.

<img width="1919" height="1079" alt="image" src="https://github.com/user-attachments/assets/ed96235d-9038-47a0-bd61-e9824da9065f" />

The objective was to try and recreate a 3d renderer from almost-scratch, but without already built graphics APIs. Although maybe a bit unefficient and possibly heavier than necessary on the CPU, I aimed to write all the calculations manually. 

There's not too many features, but for now I added: 
- 3D MESH LOADING: a way to load your own Wavefront models (with no materials and I can't guarantee it will work for all .obj, I will make sure it's universal in a later release). 
- DISTORTION, CAMERA SPEED and more: which you can control from the variables before the run loop, but I believe they sit nicely at the current default

TO BUILD:
you will need a C compiler (GCC, Clang, or MSVC) and the SDL3 library

To run with Visual Studio:
1.  Open the project in Visual Studio.
2.  Download the SDL2 Development Libraries from [libsdl.org](https://www.libsdl.org/download-2.0.php).
3.  Go to Project Properties > VC++ Directories and add the SDL2 `include` and `lib` paths.
4.  Copy `SDL3.dll` into the folder where your `.exe` is generated.
5.  Build and Run.

Sorry, but I have no idea for what concerns Linux and Apple, though there should be plenty of videos out there.

CONTROLS:
-WASD, simple xy plane movement
-SHIFT, camera goes down
-SPACE, camera goes up
-ESC, stop the program

ADDITIONAL INFO:
-The renderer will appear in fullscreen, with a 1080x1920 resolution, and I think it will look weird if you have a different resolution so until I add something that checks that automatically, please change the resolution by hand
-'assets/' contains a couple of test meshes I used to debug. If you want to add a mesh I suggest adding it in that folder. 
-Thanks for reading all the way through!
