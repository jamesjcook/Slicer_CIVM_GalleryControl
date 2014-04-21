/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and


==============================================================================*/

#ifndef __qSlicerCIVM_GalleryControlModuleWidget_h
#define __qSlicerCIVM_GalleryControlModuleWidget_h


#include <QFileInfo>
#include <QHash>

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include "qSlicerCIVM_GalleryControlModuleExport.h"


// civm includes
#include <vtkMRMLNDLibraryNode.h>
//both nddiplay includes fail to be found!.

//#include <qSlicerCIVM_NDDisplayModuleWidget.h>
//#include <qSlicerCIVM_NDDisplayModule.h>

class qSlicerCIVM_GalleryControlModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_CIVM_GALLERYCONTROL_EXPORT qSlicerCIVM_GalleryControlModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT
    friend class qSlicerCIVM_GalleryControlPanelDataSelector;
public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerCIVM_GalleryControlModuleWidget(QWidget *parent=0);
  virtual ~qSlicerCIVM_GalleryControlModuleWidget();




/*   QStringList GetLibraries(QString ); */
/*   QStringList GetLibraries(QString, int); */
/*   void SetLibraries(QString); */
/*   QString ReadLibraryPath(void); // reads the library path for our selected lib first calling readlibraryname */
  QString ReadLibraryPath(QString); // reads the gui data selector and gets the path for that library
  QString ReadLibraryName(); // reads the gui data selector and gets the name selected
/*   QStringList GetLibDims(QString  ); */
/*   QStringList GetDimEntries(QString, QString ); */
  QStringList GetDisplayProtocols();                   // function to list any/all display protocols supported 
  QStringList GetDisplayProtocols(vtkMRMLNDLibraryNode *); // function to list any/all display protocols supported by this library
  void LoadData(); 
  void SetDisplayLayout(QString ); 
  void BuildDisplayControls(QString, QWidget);
  void nothing();

 signals:
  void NoSupportedProtocols(std::string);
  void NoSupportedProtocols(vtkMRMLNDLibraryNode * );

public slots:
  
protected slots:

  void BuildGallery(void); 
  void BuildGallery(vtkMRMLNDLibraryNode *); 
  void BuildGallery(QString );
  void DataSelected(void);                   //get the selected lib from the data container(as set by sub panel).
  void DataSelected(vtkMRMLNDLibraryNode *); //set our 
/*   void FillDataLibraries(void);   //get sublibs out of datastore */
/*   bool FillDataLibraries(QString);   //get sublibs out of datastore */
/*   void FillLibrarySelector(void); //fill out our select data gui from datalibraries */
/*   void ClearLibrarySelector(void); // clear out our library list.s */
  void SetControls(void); 

 protected:
  QScopedPointer<qSlicerCIVM_GalleryControlModuleWidgetPrivate> d_ptr;
  void SetDataRoot();
  virtual void setup(void);
  
  private slots: 
/*   void HomeButton(void ); // slot to listen to the HomeDataPushButtonObject; */
/*   void BackButton(void ); // slot to listen to the BackDataPushButtonObject; */
  
 private:
  Q_DECLARE_PRIVATE(qSlicerCIVM_GalleryControlModuleWidget);
  Q_DISABLE_COPY(qSlicerCIVM_GalleryControlModuleWidget);
  QString DataRoot;
  //QString LibRoot;     // root of library we've selected
  //QString SelectedLibName(void); // name of library we've selected,!bad use readlibraryname
  //QString SelectedLibPath(void); // path to the selected library, used by older modules, BAD use readlibrarypath
  QString ps;
  int SelectorIndent;
  //DataObject *DataLibrary. // this should have somekind of method like librarylist returinging a list/vector/something of data libraries
  // we'll simulate that now using a qhash
  //QHash<QString, QFileInfo> DataLibraries;
  //std::map<std::string,vtkMRMLNDLibraryNode *>  DataLibraries;
  //std::map<std::string,displayprotcolclass *> DisplayProtocols; // to be filled in later.

  void PrintText(const QString);
  void PrintMethod(const QString);
  void clearLayout(QLayout* , bool );
  
  vtkMRMLNDLibraryNode * DataStore;
  vtkMRMLNDLibraryNode * FullDataLibrary;
  vtkMRMLNDLibraryNode * CurrentNode;    // the current node selected, to be passed to sub panels. (not in current use, but is set by our dataselected slot.
  //qSlicerCIVM_NDDisplayModuleWidget * temp;
};

#endif
