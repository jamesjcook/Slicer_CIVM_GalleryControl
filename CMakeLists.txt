cmake_minimum_required(VERSION 2.8.9)

#find_package(Slicer COMPONENTS ConfigurePrerequisites)

project(CIVM_DataLibraryManger)

#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/4.3/Extensions/CIVM_GalleryControl")
set(EXTENSION_CATEGORY "Display")
set(EXTENSION_STATUS "pre-alpha")
set(EXTENSION_CONTRIBUTORS "James Cook (The Center for In Vivo Microscopy, Duke University), Jean-Christophe Fillion-Robin (Kitware)(template)")
set(EXTENSION_DESCRIPTION "Extension to contain logic for reading a library of data and modules to offer helpful displays of those libararies.")
set(EXTENSION_ICONURL "http://viewvc.slicer.org/viewvc.cgi/Slicer4/trunk/Extensions/Testing/CIVM_GalleryControl/CIVM_GalleryControl.png?revision=21746&view=co")
set(EXTENSION_SCREENSHOTURLS "http://wiki.slicer.org/slicerWiki/images/4/42/Slicer-r19441-CIVM_GalleryControl-screenshot.png")

#-----------------------------------------------------------------------------
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
add_subdirectory(CIVM_GalleryControl)
add_subdirectory(CIVM_NDDisplay)
#add_subdirectory(CIVM_RatDevAtlas)
#add_subdirectory(LoadableModuleTemplate)
#add_subdirectory(CIVM_AdultRatPGR)
add_subdirectory(MRML)
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})
