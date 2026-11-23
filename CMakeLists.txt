cmake_minimum_required(VERSION 3.22)

# Single source of truth for the release version. CI reads this line to name
# the GitHub release (vX.Y.Z), so bump it here to publish a new version.
project(SimpleSynth VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version")
endif()

if(MSVC)
    # Static runtime so the standalone .exe runs without the VC++ redistributable.
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ---------------------------------------------------------------------------
# JUCE
#   -DJUCE_SOURCE_DIR=/path/to/JUCE  use a local checkout
#   (default)                         fetch JUCE 8.0.8 from GitHub
# ---------------------------------------------------------------------------
set(JUCE_SOURCE_DIR "" CACHE PATH "Path to a local JUCE checkout (optional)")

if(JUCE_SOURCE_DIR)
    add_subdirectory("${JUCE_SOURCE_DIR}" JUCE EXCLUDE_FROM_ALL)
else()
    include(FetchContent)
    FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.8
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(JUCE)
endif()

# Formats: VST3 + Standalone everywhere, AU on macOS.
set(SIMPLESYNTH_FORMATS VST3 Standalone)
if(APPLE)
    list(APPEND SIMPLESYNTH_FORMATS AU)
endif()

juce_add_plugin(SimpleSynth
    VERSION                  ${PROJECT_VERSION}
    COMPANY_NAME             "SYNTH8"
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE              SIMP
    FORMATS                  ${SIMPLESYNTH_FORMATS}
    PRODUCT_NAME             "SimpleSynth"
    IS_SYNTH                 TRUE
    NEEDS_MIDI_INPUT         TRUE
    NEEDS_MIDI_OUTPUT        FALSE
    IS_MIDI_EFFECT           FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD  FALSE
    VST3_CATEGORIES          Instrument Synth
    AU_MAIN_TYPE             kAudioUnitType_MusicDevice)

juce_generate_juce_header(SimpleSynth)

file(GLOB SYNTH_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

target_sources(SimpleSynth PRIVATE
    ${SYNTH_SOURCES}
    MaximilianDSP/maximilian.cpp)

target_include_directories(SimpleSynth PRIVATE
    MaximilianDSP
    Source)

target_compile_definitions(SimpleSynth PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    _USE_MATH_DEFINES)

if(MSVC)
    target_compile_options(SimpleSynth PRIVATE /W0 /bigobj /utf-8)
else()
    target_compile_options(SimpleSynth PRIVATE -w)
endif()

target_link_libraries(SimpleSynth
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags)
