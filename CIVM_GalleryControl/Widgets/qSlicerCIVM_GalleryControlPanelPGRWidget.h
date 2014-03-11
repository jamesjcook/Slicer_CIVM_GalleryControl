/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerCIVM_GalleryControlPanelPGRWidget_h
#define __qSlicerCIVM_GalleryControlPanelPGRWidget_h

// Qt includes
#include <QWidget>

// PanelPGR Widgets includes
#include "qSlicerCIVM_GalleryControlModuleWidgetsExport.h"


////
// SLOPPY PRG CODE BEGIN 
//#include "qSlicerCIVM_GalleryControlModuleWidget.h"
// this has proven prolematic

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

//#include "qSlicerCIVM_GalleryControlPanelPGRExport.h"
#include <qSlicerWidget.h>
#include <qMRMLSliceWidget.h>
#include <ctkSliderWidget.h>
#include <vtkMRMLCrosshairNode.h>
#include <vtkMRMLMarkupsNode.h>

// SLOPPY PGR CODE END
//// 



class qSlicerCIVM_GalleryControlPanelPGRWidgetPrivate;

/// \ingroup Slicer_QtModules_CIVM_GalleryControl
//class Q_SLICER_MODULE_CIVM_GALLERYCONTROL_WIDGETS_EXPORT qSlicerCIVM_GalleryControlPanelPGRWidget
// : public QWidget
class Q_SLICER_MODULE_CIVM_GALLERYCONTROL_WIDGETS_EXPORT qSlicerCIVM_GalleryControlPanelPGRWidget
 : public qSlicerAbstractModuleWidget
{
  Q_OBJECT
public:
  //typedef QWidget Superclass;
  typedef qSlicerAbstractModuleWidget Superclass;
/*   qSlicerCIVM_GalleryControlPanelPGRWidget(QWidget *parent=0); */
   qSlicerCIVM_GalleryControlPanelPGRWidget(QWidget *parent=0, QString="/"); 
  virtual ~qSlicerCIVM_GalleryControlPanelPGRWidget();
  ////
  // SLOPPY PGR CODE BEGIN

  // public functions.
  void PrintMethod(QString);  //print to console with constant text+message
  void PrintText(QString);    //print to console
  QStringList SetLayout();    //defunct?(that needs verification) function to change the layout.
  const char * NodeID(QString); //translates node name to node id
  QString ps;                 //place to hold the path separator so our module can be multi-platform.
  //public data
  QString GalleryName;        // Name of the gallery
  QStringList ImageContrasts; // list of the different contrasts available.
  bool CenterVolumeOnLoad;    // variable to choose when to center on load, might not want that behavior in the future
  bool LoadLabels; 
  QString ViewNodeContrast1;  // First viewers's contrast selection. 
  QString ViewNodeContrast2;  // Second viewers Contrast Selection.
  QStringList SceneNodes;     // list of nodes in the scene, this could probably be a protected variable.
  QString HistologyNodeName;  // name ot the histology node.
  QString Layout;             //String name of the layout to use.
  QString DataRoot;           //path to data set in the setup function. 
  QString DataPath;           //path to data set in the setup function.
  QString LabelPath;          //see datapath.
  QString DataPattern;        //pattern for data file to have parts replacd wit actual contrast and timepoint information.
  QString LabelPattern;       //see datapattern
  QString TimePoint;          // timepoint holder 
  double Pos;           //container for position of the axial image slider
  double PosBackup;
  double Angle;         //container for position of the sagital angle slider
  double AngleBackup;
  int InitialCrosshairThickness; // variable to save the crosshair state before we change it.
  
  //  vtkMRMLSliceNode * SlicePointer ; // smart pointer to connect our slider to to adjust both our datastes at the same time. 
  //  QTextStream Err; // conection to stderr
  //  QTextStream Out; // conection to stdout

  // double GetSliceOffsetValue(vtkMRMLode *);
  //  std::vector<double> GetSliderRange(vtkImageData * );
  std::vector<double> GetSliderRange(vtkMRMLNode * );
  std::vector<double> GetSliceFOV(vtkMRMLNode * );
  std::vector<double> GetSliderRangeSlice(vtkMRMLNode * );
  std::vector<unsigned long> ObserverTags;
  float Priority;
  void SetSliderRange(ctkSliderWidget * , std::vector<double>);
  void ResetTransform();
  void LabelAtPosition(); // tells the label value/name at the current mouse position in the StructureName QLabel
  //void LabelAtPosition(vtkMRMLNode * ); // tells the label value/name at the current mouse position in the StructureName QLabel
  //vtkCommand *  LabelAtPosition();
  /*
  ///
  /// Get/Set the current distance from the origin to the slice plane
  double GetSliceOffset();
  void SetSliceOffset(double offset);*/

  // SLOPPY PGR CODE END
  ////
public slots:
  /////
  // SLOPPY PGR CODE BEGIN

  //  void IncrimentSlider(ctkSliderWidget * );     // incrimentslider
  //  void DecrimentSlider(ctkSliderWidget * );     // decrimentslider
  void BuildScene();          //sets up mrml nodes loads data
  void LoadData();          //sets up mrml nodes loads data
  bool NodeExists(QString);   // checks scene for existing node with given name. Used in the build scene fucntion to avoid reloading data.
  QStringList GetContrasts();    // will look up all the checkboxes in contrasts group and make a qstringlist of values
  void SetViewNodeProperties(QString); //Sets the view properties for a given view node string
  void HistologySelectionDialog(); // runs the histology selection dialog.
  void SetSliceOffsetValue(double offset);
  void SetSliceGeometry(double angle);
  void SetMouseWatcherStatus() ; // turns on mouse watching.
  void SetMouseWatcherStatus_old() ; // turns on mouse watching.

  //  void trackSliceOffsetValue(double offset);  

  // SLOPPY PGR CODE END
  ////

protected slots:

  /////
  // SLOPPY PGR CODE BEGIN

  void ProcessEvent(vtkObject* sender,
                            void* callData,
                            unsigned long eventId,
                            void* clientData);
  void onDeleteAllMarkupsInListPushButtonClicked();  

  // SLOPPY PGR CODE END
  ////

protected:
  QScopedPointer<qSlicerCIVM_GalleryControlPanelPGRWidgetPrivate> d_ptr;

  /////
  // SLOPPY PGR CODE BEGIN

  /*   vtkMRMLCrosshairNode RegionMarker; */
  void setPersistence(bool);
  bool FiducialPlacement;
  bool ReadMousePosition;
  int NumberOfFiducials;
  QString AgeTimeConvert(QString); 
  
  // SLOPPY PGR CODE END
  ////
private:
  Q_DECLARE_PRIVATE(qSlicerCIVM_GalleryControlPanelPGRWidget);
  Q_DISABLE_COPY(qSlicerCIVM_GalleryControlPanelPGRWidget);

  /////
  // SLOPPY PGR CODE BEGIN

  double * cLastRAS; 
  double * cLastXYZ; 
  double * cLastIJK; 
  std::string LastLabelName; 
  vtkMRMLNode * CurrentLabelVolume;
  vtkMRMLNode * CurrentSliceLayerLogic;
  qMRMLSliceWidget * SlicerWidget(vtkInteractorObserver * ) ;
  void OnMRMLSceneNodeAdded(vtkMRMLNode  *);
  QWidget * ParentalUnit;
  void SetLabelStatus();
  // SLOPPY PGR CODE END
  ////

};

#endif
