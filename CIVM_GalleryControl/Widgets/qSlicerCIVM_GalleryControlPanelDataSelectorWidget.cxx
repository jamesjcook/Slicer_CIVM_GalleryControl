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


// PanelDataSelector Widgets includes
#include "qSlicerCIVM_GalleryControlPanelDataSelectorWidget.h"
#include "ui_qSlicerCIVM_GalleryControlPanelDataSelectorWidget.h"


//#include "vtkMRMLNDLibraryBuilder.h"

// PanelDataSelector modification
#include <QDebug>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_CIVM_GalleryControl
class qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate
  : public Ui_qSlicerCIVM_GalleryControlPanelDataSelectorWidget
{
  Q_DECLARE_PUBLIC(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
protected:
  qSlicerCIVM_GalleryControlPanelDataSelectorWidget* const q_ptr;

public:
  qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate(
    qSlicerCIVM_GalleryControlPanelDataSelectorWidget& object);
  virtual void setupUi(qSlicerCIVM_GalleryControlPanelDataSelectorWidget*);
};

// --------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate
::qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate(
  qSlicerCIVM_GalleryControlPanelDataSelectorWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate
::setupUi(qSlicerCIVM_GalleryControlPanelDataSelectorWidget* widget)
{
  this->Ui_qSlicerCIVM_GalleryControlPanelDataSelectorWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlPanelDataSelectorWidget methods

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlPanelDataSelectorWidget
// ::qSlicerCIVM_GalleryControlPanelDataSelectorWidget(QWidget* parentWidget)
//   : Superclass( parentWidget )
//   , d_ptr( new qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate(*this) )
// {
//   Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
//   d->setupUi(this);

//   //  connect(d->PanelDataSelectorButton,SIGNAL(clicked()),SLOT(ButtonTest()));
// }


//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::qSlicerCIVM_GalleryControlPanelDataSelectorWidget(QWidget* parentWidget,vtkMRMLNDLibraryNode * ndLibrary)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerCIVM_GalleryControlPanelDataSelectorWidgetPrivate(*this) )
{
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  d->setupUi(this);

  // example to connect to parent.
  //connect( this, SIGNAL(mySignal()), parentWidget(), SLOT(parentSlot()) );
  //parentWidget()->a_slot(); 
  
  LibPointer=ndLibrary;
  LibBuilder = new vtkMRMLNDLibraryBuilder();
  LibBuilder->SetLibPointer(ndLibrary);
  
  bool status = this->ReadLib(ndLibrary);

  this->UpdateSelector(ndLibrary); //udpates combo box and data hash form our lib
//  this->PrintDataHash();

  d->LibrarySelectorDropList->setDefaultText("<No Data Selected>");
  d->LibrarySelectorDropList->setCurrentIndex(-1);
  

  connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(SelectionChange()));

  connect(d->HomeDataPushButton,SIGNAL(clicked()),SLOT(HomeButton()));
  connect(d->BackDataPushButton,SIGNAL(clicked()),SLOT(BackButton()));
 
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::~qSlicerCIVM_GalleryControlPanelDataSelectorWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::BackButton(void)
{
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  //DataHash.clear();
  //LibPointer=ndLibrary;
  //LibBuilder = new vtkMRMLNDLibraryBuilder();
  //LibBuilder->SetLibPointer(ndLibrary);
  //bool status = this->ReadLib(ndLibrary);
  //this->UpdateDataHash(ndLibrary);
  
  if ( 0 ) { // crashes slicer
  d->LibrarySelectorDropList->setDefaultText("<No Data Selected>");
  d->LibrarySelectorDropList->setCurrentIndex(-1);
  this->UpdateSelector(LibPointer);
  }
  int comboIndex=d->LibrarySelectorDropList->currentIndex();
  int comboIndent=GetTextIndent(d->LibrarySelectorDropList->itemText(comboIndex));
  int startingIndent=GetNameIndent();
  while (  comboIndent >= startingIndent )
    {
    comboIndex--;
    comboIndent=GetTextIndent(d->LibrarySelectorDropList->itemText(comboIndex));
    this->PrintText("Stepping back:"+d->LibrarySelectorDropList->itemText(comboIndex));
    }
//    d->LibrarySelectorDropList->itemText(comboIndex);
  if ( comboIndex>=0) 
    {
    d->LibrarySelectorDropList->setCurrentIndex(comboIndex);
    }
  

  return;
}

//-----------------------------------------------------------------------------
int qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::GetNameIndent(void)
{
  return GetTextIndent(this->ReadLibraryName());
}

//-----------------------------------------------------------------------------
int qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::GetTextIndent(QString text)
{
  QString printIndent="";
  int indentSize=text.size()-text.trimmed().size();  //get starting indent.
  //QStringList libList;
  return indentSize;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::SelectionChange(void)
{
  //Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);  
  //d->LibrarySelectorDropList->currentText().trimmed()
  //((qSlicerCIVM_GalleryControlModuleWidget*)parentWidget())->BuildGallery();
  vtkMRMLNDLibraryNode * selection = DataHash.value(this->ReadLibraryName());
  vtkMRMLNDLibraryNode * ancestor  = selection->GetParentNode();
  vtkMRMLNDLibraryNode * current   = ancestor;
  
  while (1)
    { 
    // this test is confusing, the ancestor will be null when we've reached the top of our tree
      // however only a !ancestor flag will work because ancestor is a pointer.
      // so this should loop while there is an ancestor.
    if (!ancestor)
      {
      current->SetCurrentSelection(selection);
      break;
      } 
    else
      {
      current = ancestor;
      ancestor = ancestor->GetParentNode();
      }
    }
  //LibBuilder->Build(lib)
  //if ( this->ReadLib(selection)  )
  if ( LibBuilder->Build(selection)  )
    {
    //this->UpdateDataHash(selection);
    this->UpdateSelector(selection);//this->ReadLibraryName()
    }
  //call parent ui to tell them we've selected data.
  //connect(d->BackDataPushButton,SIGNAL(clicked()),SLOT(BackButton()));
  //connect( this, SIGNAL(mySignal()), parentWidget(), SLOT(parentSlot()) );
  //signal(this,SIGNAL(DataSelected()),parentWidget(),SLOT(DataSelected()));
// #include "qSlicerCIVM_GalleryControlModuleWidget.h"
//   qSlicerCIVM_GalleryControlModuleWidget * p=this->parentWidget();
//  p->DataSelected(); 
  emit DataSelected();
  // 
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::HomeButton(void)
{
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
     
  LibPointer->GetSubLibraries().clear();
  return;

  
  //bool status = this->ReadLib(LibPointer);
  bool status = LibBuilder->Build(LibPointer);
  
  this->UpdateSelector(LibPointer); //udpates combo box and data hash form our lib

  d->LibrarySelectorDropList->setDefaultText("<No Data Selected>");
  d->LibrarySelectorDropList->setCurrentIndex(-1);

  
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget::PrintDataHash(void)
{
  int i=0;
  int SelectorIndent=0;
  QStringList libList;
  std::string printspc;
  int libInsertPoint=0;
  for(QHash<QString,vtkMRMLNDLibraryNode*>::iterator subIter= DataHash.begin(); subIter!=DataHash.end(); ++subIter )
    {
    while (printspc.size()<SelectorIndent)
      {
      printspc=printspc+" ";
      }
    //std::string subLib=subIter->second->GetLibName();
    this->PrintText(QString::fromStdString(printspc) + subIter.key());
        i++;
    }
  return;
}

//-----------------------------------------------------------------------------
bool qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::ReadLib(vtkMRMLNDLibraryNode * lib)
{
  //vtkMRMLNDLibraryBuilder * libBuilder= new vtkMRMLNDLibraryBuilder();
  
  //delete libBuilder;
  return LibBuilder->Build(lib);
}

//-----------------------------------------------------------------------------
// Run each time we make a selection and the selection needs to be built.
// Adds to our DataHash mapping, and our ComboBox listing.
// DataHash names match combobox listings exactly. 
//
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::UpdateSelector(vtkMRMLNDLibraryNode * lib)
{
  this->PrintMethod("UpdateSelector");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  // if the libname is defined in selector, indent and add children  
  // if the libname is undefined in selector, do not indent
  QString printIndent="";
  //int indentSize=this->ReadLibraryName().size()-this->ReadLibraryName().trimmed().size();  //get starting indent.
  int indentSize=GetNameIndent();
  QStringList libList;
  while (printIndent.size()<indentSize)
    {
    printIndent=printIndent+" ";
    }
  
  //first update we have to add our base lib name
  if (this->ReadLibraryName()=="<No Data Selected>") 
    {
    DataHash.insert(QString::fromStdString(lib->GetLibName()),lib);
    } 
  printIndent=printIndent+"  ";  // update indent
  
  std::map<std::string,vtkMRMLNDLibraryNode* > subs=lib->GetSubLibraries();
  if ( subs.size()> 0 ) 
    {
    for(std::map<std::string, vtkMRMLNDLibraryNode* >::iterator subIter= subs.begin(); subIter!=subs.end(); ++subIter )  
      {
//    DataHash 
      if ( ! subIter->second ) 
        {
        this->PrintText("BAD SUBLIB ERROR, UNCONSTRUCTED SUBLIB IN "+this->ReadLibraryName());
        break; 
        }
      QString dhLibName=printIndent+ QString::fromStdString(subIter->second->GetLibName());
      DataHash.insert(dhLibName,subIter->second);
      libList << dhLibName;
      this->PrintText(QString::fromStdString(subIter->second->GetLibName())+" added!");
      }
    }
  else 
    {
    this->PrintText("Update called for lib with no sub libs:"+QString::fromStdString(lib->GetLibName()) );
    }
  
  int libInsertPoint=d->LibrarySelectorDropList->currentIndex()+1;// should be good even for first insert as we start with index =-1
  //getname of data point in hash at number.
  int startIndex=d->LibrarySelectorDropList->currentIndex();
  // vtkMRMLNDLibraryNode * libname=DataHash->qHash(startIndex+1);
  QString nextName;//=DataHash(startIndex+1)->GetLibName();

  //int indentSize=this->ReadLibraryName().trimmed().size()-this->ReadLibraryName().size();
  //use that to get update position of hash
  // int nextIndent=indentSize;
//   while(nextIndent==indentSize)
//     {
    //starting from that place insert new elements
    //... this will fail because we don thave new elements
    //new organization is needed.
    
//     break;
//     }
  this->PrintText("  fill lib selector: Insert Items");
  d->LibrarySelectorDropList->insertItems(libInsertPoint,libList); // if we dont clear

  return;
}

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlPanelDataSelectorWidget::ReadLibraryPath(QString libraryName) {
  // Read the library path from the ndlib referenced by the libraryName entry in our datastore qhash
  QString library;
  this->PrintText("ReadLibraryName "+libraryName);
  if (libraryName=="<No Data Selected>"|| libraryName=="NoName")
    {
    this->PrintText("Lib path blank");
    library="NoPath";
    }
//   else if ( libraryName == LibPointer->GetLibName() )
//     {
//       library=LibPointer->GetLibRoot();
//     }
  else
    {
    std::string path = DataHash[library]->GetLibRoot();
    library=QString::fromStdString(path);
    this->PrintText("ReadLibraryPath "+libraryName+":"+library);
    }
  return library;
}

//-----------------------------------------------------------------------------
//
QString qSlicerCIVM_GalleryControlPanelDataSelectorWidget::ReadLibraryName(void) {
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  QString libraryName="<No Data Selected>";
  libraryName=d->LibrarySelectorDropList->currentText();//.trimmed() 
  // took out trimmed...
  this->PrintText("ReadLibraryName "+libraryName);
  if (libraryName=="<No Data Selected>")
    {
    this->PrintText("Lib name blank");
    libraryName="NoName";
    }
  return libraryName;
}


void qSlicerCIVM_GalleryControlPanelDataSelectorWidget::PrintMethod(const QString text)
{
  QString pass="qSlicerCIVM_GalleryControlModulePanelDataSelectorWidget method:"+text;
  this->PrintText(pass);
  return;
}


void qSlicerCIVM_GalleryControlPanelDataSelectorWidget::PrintText(const QString text)
{
  QTextStream out(stdout);
  out << text<<"\n";
  return;
}





// void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
// ::ButtonTest()
// {
// //Q_D(
//   QTextStream out(stdout);
//   out << "button test"<<"\n";  
//   return;
// }
