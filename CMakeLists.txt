cmake_minimum_required(VERSION 3.15)
project(SimpleSynth VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

# Add JUCE as a subdirectory
add_subdirectory("/home/ukhirani/Umang/SDKs and Paths/juce-8.0.8-linux/JUCE" JUCE)


# Use pkg-config to find GTK and Pango (and their dependencies)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(WEBKIT2GTK REQUIRED webkit2gtk-4.0)
find_package(CURL REQUIRED)

include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT2GTK_INCLUDE_DIRS})

## Add include and link flags for GTK and Pango
#include_directories(${GTK3_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS} ${PANGO_LIBRARY_DIRS})
#add_definitions(${GTK3_CFLAGS_OTHER} ${PANGO_CFLAGS_OTHER})

# JUCE plugin target
juce_add_plugin(SimpleSynth
        COMPANY_NAME "SYNTH8"
        PLUGIN_MANUFACTURER_CODE Juce
        PLUGIN_CODE SIMP
        FORMATS VST3 Standalone
        PRODUCT_NAME "SimpleSynth"
        # Add more options as needed
)

# Generate JuceHeader.h for this target
juce_generate_juce_header(SimpleSynth)

#target_sources(SimpleSynth PRIVATE
#        Source/PluginProcessor.cpp
#        Source/PluginEditor.cpp
#)


# Collect all .cpp files from the 'Source' directory
file(GLOB SYNTH_SOURCES "Source/*.cpp")

# Add Maximilian sources
set(MAXIMILIAN_SOURCES
        MaximilianDSP/maximilian.cpp
)

# Add the collected sources to the target
target_sources(SimpleSynth PRIVATE
        ${SYNTH_SOURCES}
        ${MAXIMILIAN_SOURCES}
)

# Add include directory for Maximilian
target_include_directories(SimpleSynth PRIVATE
        MaximilianDSP
)

# Add the collected sources to the target
target_sources(SimpleSynth PRIVATE
    ${SYNTH_SOURCES}
)

target_sources(SimpleSynth PRIVATE
    Source/Oscillator.cpp
)

target_link_libraries(SimpleSynth PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        ${GTK3_LIBRARIES}
        ${PANGO_LIBRARIES}
        ${CURL_LIBRARIES}
        # Add more JUCE modules as needed
)


