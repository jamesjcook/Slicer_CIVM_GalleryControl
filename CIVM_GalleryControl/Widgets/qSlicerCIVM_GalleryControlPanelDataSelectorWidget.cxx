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
  d->LibrarySelectorDropList->setDefaultText("<No Data Selected>");
  d->LibrarySelectorDropList->setCurrentIndex(-1);

  // example to connect to parent.
  //connect( this, SIGNAL(mySignal()), parentWidget(), SLOT(parentSlot()) );
  //parentWidget()->a_slot(); 
  
  LibPointer=ndLibrary;
  LibBuilder = new vtkMRMLNDLibraryBuilder();
  LibBuilder->SetLibPointer(ndLibrary);
  
  //DataHash.insert(QString::fromStdString(ndLibrary->GetLibName()),ndLibrary);
  
  if ( LibBuilder->Build(ndLibrary))
    {
    this->UpdateSelector(ndLibrary);
    }
  
  connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(SelectionChange()));
  connect(d->HomeDataPushButton,SIGNAL(clicked()),SLOT(HomeButton()));
  connect(d->BackDataPushButton,SIGNAL(clicked()),SLOT(BackButton()));
  connect(d->ResetDataPushButton,SIGNAL(clicked()),SLOT(ResetButton()));
 
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
  this->PrintMethod("BackButton");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  
  int comboIndex=d->LibrarySelectorDropList->currentIndex();
  int comboIndent=GetTextIndent(d->LibrarySelectorDropList->itemText(comboIndex));
  int startingIndent=GetNameIndent();

  while (  comboIndent >= startingIndent && comboIndex >= 0)
    {
    this->PrintText("Last Step:"+d->LibrarySelectorDropList->itemText(comboIndex));
    comboIndex--;
    comboIndent=GetTextIndent(d->LibrarySelectorDropList->itemText(comboIndex));
    this->PrintText("Stepping back:"+d->LibrarySelectorDropList->itemText(comboIndex));
    }

  if ( comboIndex>=0) 
    {
    d->LibrarySelectorDropList->setCurrentIndex(comboIndex); // this triggers a combobox signal, currentindexchanged, which should trigger SelectionChange
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
// finds number of spaces in text string( assumes frontloaded spaces only)
int qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::GetTextIndent(QString text)
{
  int indentSize=text.size()-text.trimmed().size();  //get starting indent.
  return indentSize;
}

vtkMRMLNDLibraryNode * qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::GetOldestNDAncestor(vtkMRMLNDLibraryNode * selectedNDLib )
{

  vtkMRMLNDLibraryNode * current   = selectedNDLib;
  vtkMRMLNDLibraryNode * ancestor  = selectedNDLib ->GetParentNode();
  while (! ( !ancestor) ) //run while ancestor defined.
    { 
    // this test is confusing, the ancestor will be a 0 pointer(null) when we've reached the top of our tree
    // however only a !ancestor flag will work because ancestor is a pointer.
    // so this should loop while there is an ancestor.
      current = ancestor;
      ancestor = ancestor->GetParentNode();
    }
  
  if ( !ancestor ) 
    {
    ancestor=current;
    } 
  else
    {
    this->PrintText("GetOldestNDAncestor Odd condition with current defined");
    }
  
  return ancestor;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
//::SelectNext(vtkMRMLNDLibraryNode * )
::SelectNext(std::string libName)
{
  this->PrintMethod("SelectNext");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);

  if ( d->LibrarySelectorDropList->currentIndex()+1 < d->LibrarySelectorDropList->count() )
    d->LibrarySelectorDropList->setCurrentIndex(d->LibrarySelectorDropList->currentIndex()+1);
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::SelectionChange(void)
{
  this->PrintMethod("SelectionChange");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  bool setAncestor=false;
  if ( DataHash.size() > 0 )  // dont try to look things up in data hash if its empty
    {
      vtkMRMLNDLibraryNode * selection = DataHash.value(this->ReadLibraryName());
      bool optim=false;
      // the pathextendor optimization is neat but it falls down on no support.
      if ( !optim) 
	{
	  if ( LibBuilder->Build(selection)  )
	    {
	      this->UpdateSelector(selection);
	    }
	}
      else
	{
	  //build while we have one option!.
	  bool buildstatus=true;
	  while (buildstatus)
	    {
	      buildstatus = LibBuilder->Build(selection);
	      if ( buildstatus) 
		{
		  this->UpdateSelector(selection);
		}
	      
	      if ( selection->GetSubLibraries().size()==1 )
		{
		  d->LibrarySelectorDropList->setCurrentIndex(d->LibrarySelectorDropList->currentIndex()+1);
		  this->PrintText("engage depth build optimazation");
		  std::string name=selection->GetSubLibraries().begin()->second->GetLibName();
		  vtkMRMLNDLibraryNode * nextsel=selection->GetSubLibraries()[name];
		  selection=nextsel;
		}
	    }
	}
//       while ( LibBuilder->Build(selection)  )
// 	{
// 	  this->UpdateSelector(selection);
// 	  if(selection->GetSubLibraries().size()==1 ){
// 	    selection=selection->GetSubLibraries().at(0);
// 	  }
// 	}      

      //Let world know we've selected data.
      if( setAncestor) 
	{
	  // move get oldest to a get ancestry function in librarynode?
	  vtkMRMLNDLibraryNode * ancestor  = GetOldestNDAncestor(selection);
	  ancestor->SetCurrentSelection(selection);
	  emit DataSelected();
	} 
      else 
	{
	  emit DataSelected(selection);
	}

    }
   
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::HomeButton(void)
{
  this->PrintMethod("HomeButton");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  d->LibrarySelectorDropList->setCurrentIndex(0); // this triggers a combobox signal, currentindexchanged, which should trigger SelectionChange
//  LibPointer->GetSubLibraries().clear();
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

// //-----------------------------------------------------------------------------
// bool qSlicerCIVM_GalleryControlPanelDataSelectorWidget
// ::ReadLib(vtkMRMLNDLibraryNode * lib)
// {
//   //vtkMRMLNDLibraryBuilder * libBuilder= new vtkMRMLNDLibraryBuilder();
  
//   //delete libBuilder;
//   return LibBuilder->Build(lib);
// }

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::ResetButton(void)
{
  this->PrintMethod("ResetButton");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);

  ///
  if ( 1 ) 
    {
      //order of operations is important here.
      DataHash.clear();
      //LibPointer->clear(); // this doesnt work because we dont have accesss to the real datasubs structrure, need to give that to us.
      //LibPointer->ResetLibrary(); // this doesnt work because we dont have accesss to the real datasubs structrure, need to give that to us.
      d->LibrarySelectorDropList->setCurrentIndex(-1);
      d->LibrarySelectorDropList->clear();

      if ( LibBuilder->ReBuild())
	{
	  this->PrintText("updating selector after clear");
	  this->UpdateSelector(LibPointer);
	}
      
    }
  ///

  //  d->LibrarySelectorDropList->setCurrentIndex(0); // this triggers a combobox signal, currentindexchanged, which should trigger SelectionChange
//  LibPointer->GetSubLibraries().clear();
  return;
}

//-----------------------------------------------------------------------------
// Run each time we make a selection and we udpated our lib.
// Adds to our DataHash mapping, and our ComboBox listing.
// DataHash names match combobox listings exactly. 
//
void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::UpdateSelector(vtkMRMLNDLibraryNode * lib)
{
  this->PrintMethod("UpdateSelector");
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  QString printIndent="";
  int indentSize=GetNameIndent();
  QStringList libList;
  while (printIndent.size()<indentSize)
    { 
    printIndent=printIndent+" ";
    }
  
  //first update we have to add our base lib name
  if (this->ReadLibraryName()=="<No Data Selected>" || d->LibrarySelectorDropList->currentIndex()==-1) 
    {
//     this->PrintText("Inserting base lib"+QString::fromStdString(lib->GetLibName()));
//     DataHash.insert(printIndent + QString::fromStdString(lib->GetLibName()),lib);
//     libList << QString::fromStdString(lib->GetLibName());
    QString dhLibName=printIndent + QString::fromStdString(lib->GetLibName());
    DataHash.insert(dhLibName,lib);
    libList << dhLibName;
    //this->PrintText(QString::fromStdString(lib->GetLibName())+" added!");
    this->PrintText(dhLibName+" added!");
    } 

  printIndent=printIndent+"  ";  // update indent
  
  std::map<std::string,vtkMRMLNDLibraryNode* > subs=lib->GetSubLibraries();
  if ( subs.size()> 0 ) 
    {
    for(std::map<std::string, vtkMRMLNDLibraryNode* >::iterator subIter= subs.begin(); subIter!=subs.end(); ++subIter )  
      {

      if ( ! subIter->second ) 
        {
        this->PrintText("BAD SUBLIB ERROR, UNCONSTRUCTED SUBLIB IN "+this->ReadLibraryName());
        break; 
        }
      QString dhLibName=printIndent + QString::fromStdString(subIter->second->GetLibName());
      DataHash.insert(dhLibName,subIter->second);
      if ( !subIter->second->GetisLeaf() )
	{
	  libList << dhLibName;
	  this->PrintText(QString::fromStdString(subIter->second->GetLibName())+" added!");
	}
      else 
	{
	  this->PrintText("Leaf node detected"+dhLibName+", no print.");
	}
      }
    }
  else 
    {
    this->PrintText("Update called for lib with no sub libs:"+QString::fromStdString(lib->GetLibName()) );
    }
  
  int libInsertPoint=d->LibrarySelectorDropList->currentIndex()+1;// should be good even for first insert as we start with index =-1

  if( libList.size() > 0 ) 
    {
      this->PrintText("  fill lib selector: Insert Items");
      d->LibrarySelectorDropList->insertItems(libInsertPoint,libList); // if we dont clear
    }
  else
    {
      this->PrintText("  fill lib selector: No new items");
    }
  return;
}

//-----------------------------------------------------------------------------
// gets current name in the combobox(including spaces)
QString qSlicerCIVM_GalleryControlPanelDataSelectorWidget::ReadLibraryName(void) {
  Q_D(qSlicerCIVM_GalleryControlPanelDataSelectorWidget);
  QString libraryName="<No Data Selected>";
  libraryName=d->LibrarySelectorDropList->currentText();
  this->PrintText("ReadLibraryName "+libraryName);
  if (libraryName=="<No Data Selected>")
    {
    this->PrintText("Lib name blank");
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
