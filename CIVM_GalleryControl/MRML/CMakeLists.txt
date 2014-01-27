project(vtkSlicer${EXTENSION_NAME}ExtensionMRML)

string(TOUPPER ${EXTENSION_NAME} EXTENSION_NAME_UPPER)
set(KIT ${EXTENSION_NAME})
#set(MODULE_NAME CIVM_GALLERYCONTROL)
set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${EXTENSION_NAME_UPPER}_MODULE_MRML_EXPORT")

find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})
set(${KIT}_INCLUDE_DIRECTORIES
  ${Slicer_DIR}
  ${Slicer_INCLUDE_DIRECTORIES}
  )

set(${KIT}_SRCS
  vtkMRMLTagCategoryStorageNode.cxx
  vtkMRMLTagCategoryStorageNode.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
#  ${SLICER_LIBRARIES}
#  vtkRendering
#  vtkSlicerAnnotationsModuleMRML
  )

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
