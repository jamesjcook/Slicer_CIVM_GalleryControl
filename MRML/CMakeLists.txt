set(KIT "vtkMRMLNDLibraryNode")
project(${KIT})
string(TOUPPER ${KIT} KIT_NAME_UPPER)
set(${KIT}_EXPORT_DIRECTIVE "${KIT_NAME_UPPER}_MRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )

set(${KIT}_SRCS
#  vtkMRMLTagCategoryStorageNode.cxx
#  vtkMRMLTagCategoryStorageNode.h
  vtkMRMLNDLibraryNode.cxx
  vtkMRMLNDLibraryNode.h
#  vtkMRMLNDLibraryBuilder.cxx
#  vtkMRMLNDLibraryBuilder.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  ${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
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

#-----------------------------------------------------------------------------
set(KIT "vtkMRMLNDLibraryBuilder")
project(${KIT})
string(TOUPPER ${KIT} KIT_NAME_UPPER)
set(${KIT}_EXPORT_DIRECTIVE "${KIT_NAME_UPPER}_MRML_EXPORT")
#set(${KIT}_EXPORT_DIRECTIVE "VTK_MRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )

set(${KIT}_SRCS
#  vtkMRMLTagCategoryStorageNode.cxx
#  vtkMRMLTagCategoryStorageNode.h
  vtkMRMLNDLibraryNode.cxx
  vtkMRMLNDLibraryNode.h
  vtkMRMLNDLibraryBuilder.cxx
  vtkMRMLNDLibraryBuilder.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  ${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
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
