# Simple Synth

A minimal, powerful audio synthesizer with a clean interface.

## Features

- **Oscillator** with multiple waveform options
- **ADSR Envelope** for precise sound shaping
- **Filter** with frequency and resonance controls
- **Effects** including Chorus and Reverb
- **Crunch** for adding saturation/distortion
- **Limiter** for controlling dynamics

## Downloads

Pre-built binaries are available in the `/download` folder:
- **Windows**: SimpleSynth.exe
- **Linux**: SimpleSynth.AppImage  
- **macOS**: SimpleSynth.dmg

## Building from Source

### Prerequisites
- CMake 3.15+
- JUCE 8.0+ (automatically downloaded by CI/CD)
- C++20 compatible compiler

### Platform-specific dependencies

#### Linux
```bash
sudo apt-get install build-essential cmake pkg-config \
  libgtk-3-dev libwebkit2gtk-4.0-dev libcurl4-openssl-dev \
  libasound2-dev libjack-jackd2-dev
```

#### Windows
- Visual Studio 2019 or later
- Windows SDK

#### macOS
- Xcode command line tools
- macOS 10.15 or later

### Build Instructions

1. Clone the repository:
```bash
git clone https://github.com/ukhirani/simple-synth.git
cd simple-synth
```

2. Download JUCE (or place it in the project root):
```bash
# The build system will look for JUCE in these locations:
# - ./JUCE (project root)
# - ../JUCE (parent directory) 
# - $JUCE_DIR environment variable
```

3. Build:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target SimpleSynth_Standalone
```

## CI/CD

The project includes GitHub Actions workflows that automatically build releases for all platforms when changes are pushed to the main branch. Built executables are automatically updated in the `/download` folder.

