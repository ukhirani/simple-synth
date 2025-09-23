cmake_minimum_required(VERSION 3.15)
project(SimpleSynth VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE as a subdirectory
# Check for JUCE in common locations
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/JUCE" JUCE)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../JUCE")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../JUCE" JUCE)
elseif(DEFINED ENV{JUCE_DIR})
    add_subdirectory("$ENV{JUCE_DIR}" JUCE)
else()
    message(FATAL_ERROR "JUCE not found. Please place JUCE in the project root or set JUCE_DIR environment variable.")
endif()


if(MSVC)
    # Disable specific warnings for MSVC
    add_compile_options(/W0)  # Disable all warnings
    # OR for specific warnings: /wd#### (replace #### with warning number)
else()
    # For GCC/Clang
    add_compile_options(-w)  # Disable all warnings
    # OR for specific warnings: -Wno-xxxx (e.g., -Wno-unused-variable)
endif()



# Platform-specific dependencies
if(UNIX AND NOT APPLE)
    # Linux dependencies
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    pkg_check_modules(WEBKIT2GTK REQUIRED webkit2gtk-4.1)
    find_package(CURL REQUIRED)
    include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT2GTK_INCLUDE_DIRS})
endif()

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
        IS_SYNTH TRUE
        
        
        # Add more options as needed
)

# Generate JuceHeader.h for this target
juce_generate_juce_header(SimpleSynth)

#target_sources(SimpleSynth PRIVATE
#        Source/PluginProcessor.cpp
#        Source/PluginEditor.cpp
#)


# Collect all source files
file(GLOB SYNTH_SOURCES "Source/*.cpp")

set(MAXIMILIAN_SOURCES
        MaximilianDSP/maximilian.cpp
)

# All specific sources (remove duplicates from glob)
set(SPECIFIC_SOURCES
        Source/Oscillator.cpp
        Source/Envelope.cpp
        Source/Filter.cpp
        Source/ReverbComponent.cpp
        Source/Crunch.cpp
        Source/Chorus.cpp
        Source/Limiter.cpp
)

# Add all sources to the target
target_sources(SimpleSynth PRIVATE
        ${SYNTH_SOURCES}
        ${MAXIMILIAN_SOURCES}
)

# Add include directory for Maximilian
target_include_directories(SimpleSynth PRIVATE
        MaximilianDSP
)

target_link_libraries(SimpleSynth PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
)

# Platform-specific linking
if(UNIX AND NOT APPLE)
    target_link_libraries(SimpleSynth PRIVATE
        ${GTK3_LIBRARIES}
        ${PANGO_LIBRARIES}
        ${CURL_LIBRARIES}
    )
endif()


