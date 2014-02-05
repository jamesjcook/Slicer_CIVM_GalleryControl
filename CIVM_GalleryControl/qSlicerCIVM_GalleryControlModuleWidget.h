/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerCIVM_GalleryControlModuleWidget_h
#define __qSlicerCIVM_GalleryControlModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerCIVM_GalleryControlModuleExport.h"

class qSlicerCIVM_GalleryControlModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_CIVM_GALLERYCONTROL_EXPORT qSlicerCIVM_GalleryControlModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerCIVM_GalleryControlModuleWidget(QWidget *parent=0);
  virtual ~qSlicerCIVM_GalleryControlModuleWidget();




  QStringList GetLibraries(QString );
  QStringList GetLibraries(QString, int);
  QString GetLibrary();
  QStringList GetLibDims(QString  );
  QStringList GetDimEntries(QString, QString );
  QStringList GetDisplayProtocols(QString );
  QStringList GetDisplayProtocols(QStringList );
  void LoadData();
  void SetDisplayLayout(QString );
  void BuildDisplayControls(QString, QWidget);
  void nothing();



public slots:
  
protected slots:

  void BuildGallery(void);
  void BuildGallery(QString );
  void SetControls();
protected:
  QScopedPointer<qSlicerCIVM_GalleryControlModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

 private:
  Q_DECLARE_PRIVATE(qSlicerCIVM_GalleryControlModuleWidget);
  Q_DISABLE_COPY(qSlicerCIVM_GalleryControlModuleWidget);
  QString DataRoot;
  QString LibRoot; // root of library we've selected
  QString ps;



  void PrintText(const QString);
  void PrintMethod(const QString);
  void clearLayout(QLayout* , bool );

};

#endif
