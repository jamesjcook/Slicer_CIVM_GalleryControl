project(qSlicer${MODULE_NAME}ModuleWidgets)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "Q_SLICER_MODULE_${MODULE_NAME_UPPER}_WIDGETS_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
#  get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
#  "/Applications/SegmentationSoftware/src/GalleryControl_multi/CIVM_GalleryControl_nightly/CIVM_GalleryControl" 
  ${vtkMRMLNDLibraryNode_SOURCE_DIR}
  ${vtkMRMLNDLibraryNode_BINARY_DIR}
  ${vtkMRMLNDLibraryBuilder_SOURCE_DIR}
  ${vtkMRMLNDLibraryBuilder_BINARY_DIR}  
  )

set(${KIT}_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.cxx
  qSlicer${MODULE_NAME}FooBarWidget.h
  qSlicer${MODULE_NAME}PanelBlankWidget.cxx
  qSlicer${MODULE_NAME}PanelBlankWidget.h
  qSlicer${MODULE_NAME}PanelPGRWidget.cxx
  qSlicer${MODULE_NAME}PanelPGRWidget.h
  qSlicer${MODULE_NAME}PanelDataSelectorWidget.cxx
  qSlicer${MODULE_NAME}PanelDataSelectorWidget.h
  )

set(${KIT}_MOC_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.h
  qSlicer${MODULE_NAME}PanelBlankWidget.h
  qSlicer${MODULE_NAME}PanelPGRWidget.h
  qSlicer${MODULE_NAME}PanelDataSelectorWidget.h
  )

set(${KIT}_UI_SRCS
  ../Resources/UI/qSlicer${MODULE_NAME}FooBarWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelBlankWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelPGRWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelDataSelectorWidget.ui
  )

set(${KIT}_RESOURCES
  ../Resources/UI/qSlicer${MODULE_NAME}FooBarWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelBlankWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelPGRWidget.ui
  ../Resources/UI/qSlicer${MODULE_NAME}PanelDataSelectorWidget.ui
  )

set(${KIT}_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  vtkMRMLNDLibraryNode
  vtkMRMLNDLibraryBuilder
  vtkSlicerMarkupsModuleMRML
  )

#add_library( libvtkMRMLNDLibraryNode SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibraryNode PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )

#add_library( libvtkMRMLNDLibraryBuilder SHARED IMPORTED )
#set_target_properties( libvtkMRMLNDLibraryBuilder PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )

#link_directories(/Applications/SegmentationSoftware/build/Slicer_multi/release_v4.3.1/Slicer-build/lib/Slicer-4.3/qt-loadable-modules/)
#libvtkSlicerMarkupsModuleMRML.dylib
# add fiducial library in markups
#add_library( release_v4.3.1/Slicer-build/lib/Slicer-4.3/qt-loadable-modul
add_library( libvtkSlicerMarkupsModuleMRML SHARED IMPORTED )

#${CMAKE_BINARY_DIR}
set_target_properties( libvtkSlicerMarkupsModuleMRML PROPERTIES IMPORTED_LOCATION ($CMAKE_BINARY_DIR ) )
#TARGET_LINK_LIBRARIES( qSlicer${MODULE_NAME}ModuleWidgets libvtkMRMLNDLibraryNode)
#TARGET_LINK_LIBRARIES( qSlicer${MODULE_NAME}ModuleWidgets libvtkSlicerMarkupsModuleMRML)
#TARGET_LINK_LIBRARIES( vtkSlicer${MODULE_NAME}ModuleLogic libvtkSlicerMarkupsModuleMRML)

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleWidgets(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  MOC_SRCS ${${KIT}_MOC_SRCS}
  UI_SRCS ${${KIT}_UI_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  RESOURCES ${${KIT}_RESOURCES}
  WRAP_PYTHONQT
  )

