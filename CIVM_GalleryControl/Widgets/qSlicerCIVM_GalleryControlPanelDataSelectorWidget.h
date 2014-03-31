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

#ifndef __qSlicerCIVM_GalleryControlPanelDataSelectorWidget_h
#define __qSlicerCIVM_GalleryControlPanelDataSelectorWidget_h

// CIVM VTK includes
#include "vtkMRMLNDLibraryNode.h"
#include "vtkMRMLNDLibraryBuilder.h"

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

// Qt includes
#include <QWidget>
#include <QHash>

// PanelDataSelector Widgets includes
#include "qSlicerCIVM_GalleryControlModuleWidgetsExport.h"

class qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate;

/// \ingroup Slicer_QtModules_CIVM_GalleryControl
class Q_SLICER_MODULE_CIVM_GALLERYCONTROL_WIDGETS_EXPORT qSlicerCIVM_GalleryControlPanelDataSelectorWidget
  : public qSlicerAbstractModuleWidget
{
  Q_OBJECT;
 signals:
  void DataSelected(void);
 public:
  typedef qSlicerAbstractModuleWidget Superclass;
  //qSlicerCIVM_GalleryControlPanelDataSelectorWidget(QWidget *parent=0);
  qSlicerCIVM_GalleryControlPanelDataSelectorWidget(QWidget *parent=0,vtkMRMLNDLibraryNode * ndLibrary=0);
  virtual ~qSlicerCIVM_GalleryControlPanelDataSelectorWidget();
  
  protected slots:
  
  void HomeButton(void);
  void BackButton(void);
  void SelectionChange(void);
  
  
  //  bool ReadLib(void);
  bool ReadLib(vtkMRMLNDLibraryNode *); 
  QString ReadLibraryPath(QString);
  QString ReadLibraryName(void);
 protected:
  QScopedPointer<qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate> d_ptr;
  
  
 private:
  QHash<QString,vtkMRMLNDLibraryNode * >  DataHash;
  void UpdateSelector(vtkMRMLNDLibraryNode * );
  int GetNameIndent(void);
  int GetTextIndent(QString);
  void PrintText(const QString);
  void PrintDataHash(void);
  void PrintMethod(const QString);
  //filldatalisting // function which understands our ndlibrarynode and how to use one to fill in its required parts. 
  //buttonhome | buttonreset
  vtkMRMLNDLibraryNode * LibPointer;    // should rename to datastore later, or vice a versa
  vtkMRMLNDLibraryBuilder * LibBuilder; // a builder ready to go when we need it.
  //buttonback
  Q_DECLARE_PRIVATE(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  Q_DISABLE_COPY(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
};

#endif
