# Survivant
## Game Engine

# Documentation - Survivant

## Introduction

The goal of this project is to create a game engine. In a team of 3, we'll research, structure, project and annotate our plan for tackling this task.  Once completed, we'll use our engine to develop a rather simple game demonstrating its core features.


## Project architecture

### Folder structure

- Dependencies
- Resources
	- Editor
	    - Fonts
	    - Models
	    - Scripts
	  - Engine
	    - Fonts
	    - Materials
	    - Models
	    - Scripts
	    - Shaders
- Source
	- Editor+
	- Runtime+
	- Engine
		- App+
		- Audio+
		- Core+
		- Physics+
		- Rendering+
		- Scripting+
		- UI+
	- Test+

### Notes
- Each dependency has it's own subfolder.
- A "+" at the end of a folder name denotes a C++ project and is not part of its name.
- The root namespace for C++ projects is `Sv{Project}`
	- _Exemple: Core’s root namespace is `SvCore`_
- Each immediate subfolder in a project folder denotes a namespace.
- Subfolders of C++ projects are separated in `{Project}/include/Survivant{Project}/{Subfolder}` and `{Project}/src/{Subfolder}` to make include paths contain the project's name, thus avoiding potential conflicts.
	- _Exemple:_
		- Core+
			- Debug
	- _expands to_
		- Core
			- include
				- SurvivantCore
					- Debug
			- src
				- Debug

___

## Graphics API

For this project, we'll be using OpenGL for its relative ease of use, its long history in the industry and its compatibility with a wide range of hardware. Furthermore, the team's familiarity with this API, as well as the amount of resources available about it will enable us to produce results in a more efficient way and put more effort into other aspects of the engine.

___

## Third-Party Libraries

This sub-section contains a list of the libraries used in this project, along with a brief explanation of their roles and importance (use, source files, type, loading process).

- Explanation of how it works
- Justification for choosing the library
- Library loading process
- Integration of source files (precompiled .lib and/or .dll? generated with _FetchContent_?)
- Static (.lib) / dynamic (.dll) library

___

### 1. GLFW (Windowing)

#### Use

This open-source library is crucial for creating and managing windows compatible with multiple rendering APIs.  GLFW provides high level multi-platform abstraction for graphical applications.

#### Justification

GLFW is the standard windowing API for OpenGL. In addition, the team already has experience with the library.

#### Loading process

1. Initialise with [glfwInit()](https://www.glfw.org/docs/3.3/group__init.html#ga317aac130a235ab08c6db0834907d85e).
2. Set the graphics API version (in our case 4.6) with [glfwWindowHint](https://www.glfw.org/docs/3.3/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033)([GLFW_CONTEXT_VERSION_MAJOR](https://www.glfw.org/docs/3.3/group__window.html#gafe5e4922de1f9932d7e9849bb053b0c0), 4) & [glfwWindowHint](https://www.glfw.org/docs/3.3/group__window.html#ga7d9c8c62384b1e2821c4dc48952d2033)([GLFW_CONTEXT_VERSION_MINOR](https://www.glfw.org/docs/3.3/group__window.html#ga31aca791e4b538c4e4a771eb95cc2d07), 6).
3. Create a default window with [glfwCreateWindow](https://www.glfw.org/docs/3.3/group__window.html#ga3555a418df92ad53f917597fe2f64aeb)(`width`, `height`, `title`).
4. Use the library in the main loop.
5. Select the window with [glfwMakeContextCurrent](https://www.glfw.org/docs/3.3/group__context.html#ga1c04dc242268f827290fe40aa1c91157)(`window`).
6. Finish by destroying the window with [glfwDestroyWindow](https://www.glfw.org/docs/3.3/group__window.html#gacdf43e51376051d2c091662e9fe3d7b2)(`window`) then [glfwTerminate()](https://www.glfw.org/docs/3.3/group__init.html#gaaae48c0a18607ea4a4ba951d939f0901).

#### Source files integration

Added to the project using _FetchContent_

#### Type of library

Static

#### Sources

- [https://www.glfw.org/docs/3.3/quick.html](https://www.glfw.org/docs/3.3/quick.html)

___

### 2. Glad (GL Loader-Generator)

#### Use

Glad is a library for loading graphics API functions. It can be used with OpenGL, Vulkan, WGL, EGL, GLX and OpenGL ES

#### Justification

Glad is an industry standard, easy to use and integrates well with GLFW, which we use for windowing. Furthermore, as the team has used this library on several projects in the past, it was an obvious choice for us.

#### Loading process

1. Initialize the graphics API with `gladLoadGL` by passing in a load function (e.g. `gladLoadGL(glfwGetProcAddress)` )
2. Use the graphics API functions

#### Source files integration

Source code versioned with the project

#### Type of library

Static

#### Sources

- [https://github.com/Dav1dde/glad/wiki/C#quick-start](https://github.com/Dav1dde/glad/wiki/C#quick-start)
- [https://gen.glad.sh/](https://gen.glad.sh/)

___

### 3. ImGui (User Interface)

#### Use

ImGui is a graphical user interface library developed to support game engine development.

#### Justification

ImGui is a lightweight, easy-to-use library with a limited number of dependencies, which prioritizes iteration speed and visualization simplicity.

#### Loading process

1. Initialize the context with `IMGUI_CHECKVERSION()` & `ImGui::CreateContext()`.
2. Select flags for the target input types (ex: `io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard`).
3. Initialize the backend (in our case GLFW and OpenGL) using `ImGui_ImplGlfw_InitForOpenGL(GLFW_WINDOW, true)` & `ImGui_ImplOpenGL3_Init(GLSL_VERSION_STRING)`.
4. At the start of the main loop, start an ImGui frame using `ImGui_ImplOpenGL3_NewFrame()`, `ImGui_ImplGlfw_NewFrame()` & `ImGui::NewFrame()`
5. At the end of the main loop, draw the ImGui frame using `ImGui::Render()` & `ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData())`
6. When the application closes, stop the backend with `ImGui_ImplOpenGL3_Shutdown()` & `ImGui_ImplGlfw_Shutdown()` then destroy the context with `ImGui::DestroyContext()`

#### Source files integration

Added to the project using _FetchContent_

#### Type of library

Static

#### Sources

- [https://github.com/ocornut/imgui#dear-imgui](https://github.com/ocornut/imgui#dear-imgui)
- [https://github.com/ocornut/imgui/wiki/Getting-Started](https://github.com/ocornut/imgui/wiki/Getting-Started)

___

### 4. PhysX (Physique)

#### Use

PhysX lets you define actors and move them according to the laws of classical mechanics in a three-dimensional environment. It also supports collisions, joints and rigid body simulation as well as ray casts, sweeping and overlap tests.

#### Justification

PhysX is a very powerful, albeit complex, low-level library for creating realistic environments. It can also be configured to use the GPU for certain demanding tasks (CUDA).

#### Loading process

1. Initialize using `PxCreateFoundation(PX_PHYSICS_VERSION, callback, error_callback)`
2. Connect the foundation to a socket using `mPvd = PxCreatePvd(*gFoundation)`, `PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10)` & `mPvd->connect(*transport,PxPvdInstrumentationFlag::eALL)`. (Cooking?)
3. Create a physics object with `mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), recordMemoryAllocations, mPvd)`.
4. Use callbacks in the main loop
5. Finish by releasing the physics object and foundation with `mPhysics->release()` & `mFoundation->release()`.

#### Source files integration

***TODO***

#### Type of library

***TODO***

#### Sources

- [https://gameworksdocs.nvidia.com/PhysX/4.0/documentation/PhysXGuide/Manual/Introduction.html#a-brief-overview-of-physx](https://gameworksdocs.nvidia.com/PhysX/4.0/documentation/PhysXGuide/Manual/Introduction.html#a-brief-overview-of-physx)
- [https://docs.nvidia.com/gameworks/content/gameworkslibrary/physx/apireference/files/group__foundation.html](https://docs.nvidia.com/gameworks/content/gameworkslibrary/physx/apireference/files/group__foundation.html)

___

### 5. SoLoud (Audio)

#### Use

SoLoud is an audio engine designed to simplify sound management.

#### Justification

Despite its ease of use, SoLoud offers a multitude of features such as adjustable volume and playback speed, audio filtering, adding sounds to a queue, support for different file formats and seamless audio looping.

#### Loading process

1. Initialize a core using `SoLoud::Soloud gSoloud` & `gSoloud.init()`.
2. Import a sound `SoLoud::Wav gWave` using `gWave.load("pew_pew.wav")`.
3. Modify the sound as desired, then play it with `gSoloud.play(gWave)`.
4. Finish with `gSoloud.deinit()`

#### Source files integration

Added to the project using _FetchContent_

#### Type of library

Static

#### Sources

[https://solhsa.com/soloud/index.html](https://solhsa.com/soloud/index.html)

___

### 6. Assimp (3D Model Importer)

#### Use

The Open Asset Import Library (Assimp) lets you load and manipulate 3D models from a variety of file formats.

#### Justification

Assimp offers a powerful and flexible solution for processing 3D model data within an application. Furthermore, Assimp supports a wide range of formats, making it easy to import models from different sources.

#### Loading process

1. Create an instance of the `Importer` class (i.e.: `Assimp::Importer importer`)
2. Load the model file using `importer.ReadFile`, specifying the file path and the necessary import flags. (ex: `const aiScene* scene = importer.ReadFile("model.obj", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByType)` )
3. Process data from the loaded Assimp scene

#### Source files integration

Added to the project using _FetchContent_

#### Type of library

Static

#### Sources

- [https://www.assimp.org/](https://www.assimp.org/)
- [https://github.com/assimp/assimp](https://github.com/assimp/assimp)
- [https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html](https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html)

___

### 7. STB image (Texture Importer)

#### Use

The STB image library is a simple, lightweight library for loading images in multiple formats.

#### Justification

STB image offers a fast, easy-to-use solution for incorporating images into graphics applications.

#### Loading process

1. Load a file using `stbi_load` (ex: `stbi_load("texture.png", &width, &height, &channels, 0)` )

2. Once the loaded data is no longer required, free the memory with `stbi_image_free`

#### Source files integration

Source code versioned with the project

#### Type of library

Static – Header Only

#### Sources

- [https://github.com/nothings/stb/blob/master/stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)

___

## Conclusion

Briefly summarize the key points of your documentation.

***TODO***
