cmake_minimum_required(VERSION 3.16)

# KDE Applications version, managed by release script.
set(RELEASE_SERVICE_VERSION_MAJOR "0")
set(RELEASE_SERVICE_VERSION_MINOR "01")
set(RELEASE_SERVICE_VERSION_MICRO "0")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

set(PLASMA_TOUCH_CONFIGURATOR_VERSION ${RELEASE_SERVICE_VERSION})
project(plasma_touch_configurator
  DESCRIPTION "important configuration in one window for KDE plasma"
  VERSION ${PLASMA_TOUCH_CONFIGURATOR_VERSION}
  LANGUAGES CXX)
# SOVERSION of the kmixcore library
set(PLASMA_TOUCH_CONFIGURATOR_VERSION_MAJOR 0)

set(QT_MIN_VERSION "6.6.1")
set(QT_MAJOR_VERSION "6")
set(KF6_MIN_VERSION "6.0.0")
set(PA_MIN_VERSION "0.9.16")
set(KDE_COMPILERSETTINGS_LEVEL "5.82")
find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMQtDeclareLoggingCategory)
include(GenerateExportHeader)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS
    Core
    DBus
    Gui
    Widgets
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    Config
    ConfigWidgets
    DBusAddons
    Solid
    WidgetsAddons
    WindowSystem
)

# PulseAudio, optional
find_package(PulseAudio "${PA_MIN_VERSION}")
if (PulseAudio_FOUND)
  message(STATUS "Building with PulseAudio support")
  set(HAVE_PULSEAUDIO true)
  add_definitions(-DHAVE_PULSEAUDIO)
  set(SUPPORTED_BACKENDS ${SUPPORTED_BACKENDS} "PulseAudio")
endif ()

# ALSA, optional
find_package(ALSA)
if (ALSA_FOUND)
  message(STATUS "Building with ALSA support")
  set(HAVE_ALSA_MIXER true)
  add_definitions(-DHAVE_ALSA_MIXER)
  set(SUPPORTED_BACKENDS ${SUPPORTED_BACKENDS} "ALSA")
endif ()

message(STATUS "Supported backends: ${SUPPORTED_BACKENDS}")

####################################################################################################
########### compile definitions ####################################################################
####################################################################################################

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})

set(VOLUME_SLIDER_HEADERS
  include/volume_slider.hpp
)
set(VOLUME_SLIDER_SOURCES
  src/volume_slider/volume_slider.cpp
)

qt_add_library(volume_slider
  SHARED
  ${VOLUME_SLIDER_HEADERS}
  ${VOLUME_SLIDER_SOURCES}
)
target_include_directories(volume_slider PRIVATE
  include
)
target_link_libraries(volume_slider PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
