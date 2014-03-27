set(KIT CIVM_Tests)
project(${KIT})
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})
#-----------------------------------------------------------------------------
set(KIT_TEST_SRCS
  #qSlicer${MODULE_NAME}ModuleTest.cxx
  CIVM_GalleryControl_NDCreateByPaths.cxx
  )	
  
set(KIT_INCLUDE_DIRECTORIES
   ${vtkMRMLNDLibraryNode_SOURCE_DIR}
   ${vtkMRMLNDLibraryNode_BINARY_DIR}
)

set(KIT_TARGET_LIBRARIES
### next line to depend on custom mrml
  vtkMRMLNDLibraryNode
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  ${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
)

#add_library( libvtkMRMLNDLibraryNode SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibraryNode PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )


#-----------------------------------------------------------------------------
slicerMacroConfigureModuleCxxTestDriver(
  NAME ${KIT}
  SOURCES ${KIT_TEST_SRCS}
  TARGET_LIBRARIES ${KIT_TARGET_LIBRARIES}
  INCLUDE_DIRECTORIES ${KIT_INCLUDE_DIRECTORIES}
  #WITH_VTK_DEBUG_LEAKS_CHECK
  )


#-----------------------------------------------------------------------------
#simple_test(qSlicer${MODULE_NAME}ModuleTest)
