# AiFramework
C++ OpenGL 2D Framework. A third attempt at writing an game framework/engine. 

# Requirements - Windows(vcpkg)
You are an Windows user? We gotchu! Install these requirements and then the code will magically work!

```
vcpkg install glad[wgl]:x86-windows-static-md opengl:x86-windows-static-md glm:x86-windows-static-md glad[wgl]:x64-windows-static-md opengl:x64-windows-static-md glm:x64-windows-static-md
```

Don't forget to use Visual Studio for this to work!

# Requirements - Linux
You are using the cool Linux? No problem! To compile AiFramework, just...

```
cd AiFramework
./build.sh
```

and it will take care of installing the required packages and building everything automatically!
After running the build script, you can just `make` and it will build `libaifw.so` under the `build` directory.

To build the test application, run:

```
cd AiFrameworkTestApp
make run
```

Make sure you compiled the AiFramework library before-hand.

# Requirements - MacOS
Well, we didn't get that far. If you want to take your shot at making this a reality, make a fork, do your magic, then make a pull request.

# Documentation
You may be wondering... where is the documentation?
I will write some documentation once everything is stable enough. Until then, you can perhaps try to refer to the provided test application.
