#C:\src\CIVM_GalleryControl\CIVM_GalleryControl\CMakeLists.txt
#-----------------------------------------------------------------------------
set(MODULE_NAME CIVM_GalleryControl)
set(MODULE_TITLE ${MODULE_NAME})

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)
add_subdirectory(Widgets)

#-----------------------------------------------------------------------------
set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

# Current_{source,binary} and Slicer_{Libs,Base} already included
set(MODULE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
  ${CMAKE_CURRENT_BINARY_DIR}/Widgets
#  ${CMAKE_CURRENT_SOURCE_DIR}/MRML
#  ${CMAKE_CURRENT_BINARY_DIR}/MRML

### next two lines to depend on custom mrml
   ${vtkMRMLNDLibrary_SOURCE_DIR}
   ${vtkMRMLNDLibrary_BINARY_DIR}
# dont need following? because all our mrml is in same lib?
#   ${vtkMRMLNDLibraryNode_SOURCE_DIR}
#   ${vtkMRMLNDLibraryNode_BINARY_DIR}
### next two lines to depend on custom mrml
#   ${vtkMRMLNDLibraryBuilder_SOURCE_DIR}
#   ${vtkMRMLNDLibraryBuilder_BINARY_DIR}
### 
   #${CIVM_NDDisplayModuleWidget_SOURCE_DIR}
   ##X${CIVM_NDDisplay_INCLUDE_DIR}
   #${CIVM_NDDisplayModuleWidget_BINARY_DIR}
   #${CIVM_NDDisplay_SOURCE_DIR}
   ##X${CIVM_NDDisplay_INCLUDE_DIR}
   #${CIVM_NDDisplay_BINARY_DIR}
  )

set(MODULE_SRCS
  qSlicer${MODULE_NAME}Module.cxx
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.cxx
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_MOC_SRCS
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_UI_SRCS
  Resources/UI/qSlicer${MODULE_NAME}ModuleWidget.ui
  )

set(MODULE_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  qSlicer${MODULE_NAME}ModuleWidgets
### next line to depend on custom mrml
#  vtkMRMLNDLibraryNode
#  vtkMRMLNDLibraryBuilder
# flopped decision to use two build libs instead of one. so no library, but yes libnode,and libbuild
  vtkMRMLNDLibrary
###
  #qSlicerCIVM_NDDisplayModule
  #qSlicerCIVM_NDDisplayModuleWidgets
  )

set(MODULE_RESOURCES
  Resources/qSlicer${MODULE_NAME}Module.qrc
  )

#with node and builder in same lib.
#add_library( libvtkMRMLNDLibrary SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibrary PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )
#when node and builder were separate
#add_library( libvtkMRMLNDLibraryNode SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibraryNode PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )
#add_library( libvtkMRMLNDLibraryBuilder SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibraryBuilder PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )

#add_library( libCIVM_NDDisplay SHARED IMPORTED )
#set_target_properties( libCIVM_NDDisplay PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )

#add_library( libqSlicerCIVM_NDDisplayModule SHARED IMPORTED )
#set_target_properties( libqSlicerCIVM_NDDisplayModule PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) ) 

#add_library( libqSlicerCIVM_NDDisplayModuleWidgets SHARED IMPORTED )
#set_target_properties( libqSlicerCIVM_NDDisplayModuleWidgets PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) ) 

#add_library( libvtkMRMLGalleryControlLibraryNode SHARED IMPORTED )
#add_library( libvtkSlicerCIVM_GalleryControlModuleMRML SHARED IMPORTED )
#set_target_properties( libvtkSlicerCIVM_GalleryControlModuleMRML PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )

#-----------------------------------------------------------------------------
slicerMacroBuildQtModule(
  NAME ${MODULE_NAME}
  TITLE ${MODULE_TITLE}
  EXPORT_DIRECTIVE ${MODULE_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  SRCS ${MODULE_SRCS}
  MOC_SRCS ${MODULE_MOC_SRCS}
  UI_SRCS ${MODULE_UI_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  RESOURCES ${MODULE_RESOURCES}
  WITH_GENERIC_TESTS
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

