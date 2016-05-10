#-----------------------------------------------------------------------------
set(KIT "vtkMRMLNDLibrary")
project(${KIT})
string(TOUPPER ${KIT} KIT_NAME_UPPER)

#from widget compiles.
#set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

set(${KIT}_EXPORT_DIRECTIVE "VTK_${KIT_NAME_UPPER}_MRML_EXPORT")

# this is empty, why bother.
#set(${KIT}_INCLUDE_DIRECTORIES
#  )
set(${KIT}_SRCS
  vtkMRMLNDLibraryNode.cxx
  vtkMRMLNDLibraryNode.h
  vtkMRMLNDLibraryBuilder.cxx
  vtkMRMLNDLibraryBuilder.h
  )

set(${KIT}_TARGET_LIBRARIES
  #${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  # ITK/SLICER not necessary
  #${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
  )
#add_library(${KIT} ${KIT}.cxx)
#install(TARGETS ${KIT}.lib DESTINATION bin)
#install(FILES ${KIT}.h DESTINATION include)



find_package(Qt4)
 # COMPONENTS QtOpenGL QtXml)
INCLUDE(${QT_USE_FILE})
#if ( Qt_FOUND OR QtXml_FOUND )
#OR NOT QtXml_FOUND )

if ( Qt4_FOUND_BROKEBOO ) 
  set(${KIT}_TARGET_LIBRARIES
#    ${${KIT}_TARGET_LIBRARIES}
    ${QT_LIBRARIES}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    )
  set(${KIT}_INCLUDE_DIRECTORIES
    ${${KIT}_INCLUDE_DIRECTORIES}
    ${QT_INCLUDE_DIRECTORIES}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )
#    target_link_libraries(${${KIT}_EXPORT_DIRECTIVE} Qt4::QtCore )
# says target is not built by this library!
#  add_library(${KIT}_TARGET_LIBRARIES ${QT_QTCORE_LIBRARY})
# generates error here.
else()
  set(${KIT}_INCLUDE_DIRECTORIES
    )
endif()
#endif( Qt_FOUND ) 
#OR QtXml_FOUND )
#endif( NOT Qt_FOUND OR NOT QtXml_FOUND )



#VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
# the if qt lines mess up the macros alot, cant make use of that.
#if ( NOT Qt4_FOUND ) 
SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
#else()
#slicerMacroBuildQtModule(
#  NAME ${KIT}
#  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
#  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
#  SRCS ${${KIT}_SRCS}
#  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
#  )
#endif()
#-----------------------------------------------------------------------------
# this tagcategory should be integrated into the ndlibrray kit, just left on its lonesome for now.
if(INDEV)
set(KIT "vtkMRMLTagCategoryStorage")
project(${KIT})
string(TOUPPER ${KIT} KIT_NAME_UPPER)
set(${KIT}_EXPORT_DIRECTIVE "VTK_${KIT_NAME_UPPER}_MRML_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )

set(${KIT}_SRCS
  vtkMRMLTagCategoryStorageNode.cxx
  vtkMRMLTagCategoryStorageNode.h
#   vtkMRMLNDLibraryNode.cxx
#   vtkMRMLNDLibraryNode.h
#   vtkMRMLNDLibraryBuilder.cxx
#   vtkMRMLNDLibraryBuilder.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  ${SLICER_LIBRARIES}
  ${VTK_LIBRARIES}
#  vtkRendering
#  vtkSlicerAnnotationsModuleMRML
  )
#add_library(${KIT} ${KIT}.cxx)
#install(TARGETS ${KIT}.lib DESTINATION bin)
#install(FILES ${KIT}.h DESTINATION include)
#VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
endif()
#-----------------------------------------------------------------------------
