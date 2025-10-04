# 🚀 ISS 25th Anniversary - NASA Space Apps Challenge

<div align="center">

![ISS Anniversary](https://img.shields.io/badge/ISS-25th%20Anniversary-blue?style=for-the-badge)
![NASA Space Apps](https://img.shields.io/badge/NASA-Space%20Apps%20Challenge-orange?style=for-the-badge)
![C++](https://img.shields.io/badge/C++-20-00599C?style=for-the-badge&logo=cplusplus)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)

*Celebrating 25 years of continuous human presence in space*

[About](#about) • [Features](#features) • [Requirements](#requirements) • [Building](#building) • [Usage](#usage)

</div>

---

## 📖 About

This project was created for the **NASA Space Apps Challenge** in honor of the **International Space Station's 25th Anniversary**. The ISS has been continuously inhabited since November 2, 2000, representing one of humanity's greatest achievements in space exploration and international cooperation.

## ✨ Features

- 🌍 Interactive ISS visualization
- 📊 Real-time data processing
- 🎮 Engaging user experience
- 🛰️ Historical mission data

## 🔧 Requirements

Before building the project, ensure you have the following installed:

### Essential Components

| Component | Version | Purpose |
|-----------|---------|---------|
| **Visual Studio 2022** | Latest | Primary IDE with MSVC compiler |
| **CMake** | 3.15+ | Build system generator |
| **Python** | 3.8+ | Build scripts and preprocessing |
| **C++ Compiler** | C++20 | Language standard |
| **MSVC** | Latest | Microsoft Visual C++ Compiler |

### Python Dependencies

```bash
pip install jinja2
```

### Visual Studio Components

- **CMake Tools for Visual Studio** (plugin)
- **Desktop development with C++** workload
- **C++ CMake tools for Windows**

## 🚀 Building the Project

### Method 1: Visual Studio 2022 (Recommended)

#### Step 1: Install CMake Plugin
1. Open Visual Studio 2022
2. Go to `Extensions` → `Manage Extensions`
3. Search for "CMake" and install the CMake tools
4. Restart Visual Studio

#### Step 2: Open the Project
1. Launch Visual Studio 2022
2. Select `File` → `Open` → `CMake...`
3. Navigate to the project directory and select `CMakeLists.txt`
4. VS2022 will automatically configure the project using CMake

#### Step 3: Configure Build Type
1. In the toolbar, locate the configuration dropdown (usually shows "Debug")
2. **⚠️ IMPORTANT:** Select **`x64-Release`** for optimal performance
3. Wait for CMake to finish configuration

#### Step 4: Build
1. Select `Build` → `Build All` or press `Ctrl+Shift+B`
2. CMake will automatically handle all dependencies and build steps
3. Build artifacts will be generated in `out/build/x64-Release/`

#### Step 5: Run
1. Select your startup project in Solution Explorer
2. Press `F5` or click the green "Play" button

### Method 2: Other IDEs (CLion, VS Code, etc.)

If you're using a different IDE:

#### Step 1: Generate Build Files
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

#### Step 2: Copy Runtime Files
After building, you need to copy all files from the output directory to your IDE's execution directory:

**From:** `out/build/x64-Release/` (or your build output directory)  
**To:** Your IDE's project execution directory

This typically includes:
- `.exe` files
- `.dll` files
- Resource files
- Configuration files

#### Step 3: Run from Your IDE
Run the executable from your IDE's run configuration.

### Method 3: Command Line Build

```bash
# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Files will be in build/Release/ or out/build/x64-Release/
```

## 📦 Project Structure

```
ISS-25th-Anniversary/
├── CMakeLists.txt          # Main CMake configuration
├── README.md               # This file
├── src/                    # Source code
│   ├── main.cpp
│   └── ...
├── include/                # Header files
├── resources/              # Assets and resources
├── scripts/                # Build scripts (Python/Jinja2)
└── out/
    └── build/
        └── x64-Release/    # Build output directory
```

## 🎮 Usage

After successfully building the project, launch the executable from:
- Visual Studio: Press `F5`
- Command line: Run the `.exe` from `out/build/x64-Release/`

## 🐛 Troubleshooting

### CMake Configuration Failed
- Ensure CMake tools are properly installed in Visual Studio
- Check that Python and Jinja2 are accessible from command line
- Verify C++20 compiler support

### Build Errors
- Confirm you selected **Release** configuration, not Debug
- Check that all required VS2022 components are installed
- Ensure MSVC toolchain is properly configured

### Missing DLLs at Runtime
- Copy all files from `out/build/x64-Release/` to your execution directory
- Check that Visual C++ Redistributables are installed

### Python Module Not Found
```bash
# Verify Python installation
python --version

# Install Jinja2
pip install jinja2

# Verify installation
python -c "import jinja2; print(jinja2.__version__)"
```

## 🤝 Contributing

This project was created for the NASA Space Apps Challenge. Contributions, issues, and feature requests are welcome!

## 📜 License

This project is part of the NASA Space Apps Challenge initiative.

## 🌟 Acknowledgments

- **NASA** for inspiring space exploration
- **International Space Station partners** for 25 years of continuous human presence in space
- **NASA Space Apps Challenge** organizers and participants

## 📞 Contact

For questions about this project, please open an issue on GitHub.

---

<div align="center">

**Made with 💙 for the ISS 25th Anniversary**

*Celebrating 25 years of humanity living and working in space*

🌍 🛰️ 🚀

</div>
