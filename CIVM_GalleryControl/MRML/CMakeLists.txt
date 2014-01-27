project(vtkSlicer${MODULE_NAME}ModuleMRML)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_MRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )

set(${KIT}_SRCS
  vtkMRMLTagCategoryStorageNode.cxx
  vtkMRMLTagCategoryStorageNode.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  ${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
#  vtkRendering
#  vtkSlicerAnnotationsModuleMRML
  )
#add_library( libvtkMRMLNode SHARED IMPORTED )
#add_llibrary( libvtk
# if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
#     execute_process(
#         COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
#     if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
#         message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
#     endif ()
# elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
# else ()
#     message(FATAL_ERROR "Your C++ compiler does not support C++11.")
# endif ()

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
