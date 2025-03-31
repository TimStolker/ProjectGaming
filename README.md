# Project Gaming
This space shooter arcade game is made using C++ with the SFML library.

## Installation steps
Below are the steps to get this project running on Windows.

### Setting up VS Code [Youtube tutorial](https://www.youtube.com/watch?v=oC69vlWofJQ)
1. Install [Visual Studio Code](https://code.visualstudio.com/download)
2. Install the [C/C++ extensions for VS Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools). You can install the C/C++ extension by searching for 'C++' in the Extension view (ctrl+shift+X)
3. Get the latest version of MinGW-w64 from [MYSYS2](https://www.msys2.org/), which provides up-to-date native builds of GCC, MinGW-w64, and other helpful C++ tools.
4. Run the installer and follow the steps of the installation wizard. Note that MYSYS2 requires 64-bit Windows 8.1 or newer.
5. Run MYSYS2 and run `pacman -S mingw-w64-ucrt-x86_64-gcc` to install the MinGW-w64 toolchain.
6. Enter `Y` when prompted whether to proceed with the installation.
7. Add the path of your MinGW-w64 bin folder to the Windows PATH environment variable by using the following steps:
    - In the Windows search bar, type **Settings** to open your Windows Settings.
    - Search for **Edit environment variables for your account**.
    - In your User variables, select the `Path` variable and then select **Edit**.
    - Select **New** and add the MinGW-w64 destination folder you recorded during the installation process to the list. If you used the default settings above, then this will be the path: `C:\msys64\ucrt64\bin`.
    - Select **OK**, and then select **OK** again in the **Environment Variables** window to update the `PATH` environment variable. You have to reopen any console windows for the updated `PATH` environment variable to be available.

8. Check your MinGW installation by opening a **new** Command Prompt and type `g++ --version`.

### Installing CMake
1. Go to cmake.org and download the Windows installer [link](https://cmake.org/download/)
2. Run the installation wizzard and select the checkbox `Add to PATH`.
3. Add the CMake and CMake Tools extension in VS Code with the 'Extensions' button on the left side.

### Setting up VS environment
1. In the bottom left corner, log in with your github account. There should appear a **Source Control** tab at the bar on the left.
2. Choose a location in your **File Explorer** where you want the project. Open a **Command Prompt** in that location and clone the repo with `git clone https://github.com/TimStolker/ProjectGaming.git`
    - Additionally you can clone it with the build in **Clone in VS Code** button on GitHub.
3. Configure the **IntelliSense Configuration** by pressing `ctrl+shift+P`, or by typing `>` in the search bar, and type `Select IntelliSense Configuration`. From the dropdown of compilers, select `Use g++.exe` or `Use gcc.exe`.
4. Configure **CMake** by pressing `ctrl+shift+P`, or by typing `>` in the search bar, and type `CMake: Configure`.

## Running the program
1. Open a terminal in VS Code and create a build folder with `mkdir build`.
2. Go to that directory with `cd build` and type `cmake ..` to generate the build files.
3. Build the project in the same directory with `cmake --build .`.
4. The executable should be in the install folder together with all the needed .dll files. Note that the OpenAL32.dll is added manually since it isnt build with CMake.
