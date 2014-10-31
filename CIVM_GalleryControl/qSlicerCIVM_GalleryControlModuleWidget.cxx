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

// Qt includes
#include <QDebug>
//// extras for the dynamic

#include <QIcon>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

#include <QFrame>

#include <QVBoxLayout>
#include <QVector>  
#include <QList>
#include <QFileInfo>
#include <QDir>

//ctk includes
#include <ctkUtils.h>

//customMRML includes
//#include "vtkMRMLGalleryControlLibraryNode.h"
//#include <vtkMRMLNDLibraryNode.h>
//#include "vtkMRMLTagCategoryStorageNode.h"
//#include "vtkMRMLNDLibraryBuilder.h"

// Panel includes
#include "qSlicerCIVM_GalleryControlPanelPGRWidget.h"
#include "qSlicerCIVM_GalleryControlPanelDataSelectorWidget.h"

// SlicerQt includes
#include "qSlicerApplication.h"
#include "qSlicerIOManager.h"
#include "qSlicerCIVM_GalleryControlModuleWidget.h"
#include "ui_qSlicerCIVM_GalleryControlModuleWidget.h"

//#include "qSlicerCIVM_NDDisplayModule.h"
//#include "qSlicerCIVM_NDDisplayModuleWidget.h"
//#include "qSlicerCIVM_NDDisplayModuleWidget.h"


//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerCIVM_GalleryControlModuleWidgetPrivate: public Ui_qSlicerCIVM_GalleryControlModuleWidget
{
public:
  qSlicerCIVM_GalleryControlModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModuleWidgetPrivate::qSlicerCIVM_GalleryControlModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModuleWidget::qSlicerCIVM_GalleryControlModuleWidget(QWidget* _parent)
  : Superclass( _parent )
    , d_ptr( new qSlicerCIVM_GalleryControlModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModuleWidget::~qSlicerCIVM_GalleryControlModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::setup()
{
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  d->setupUi(this); // handle the .ui file.
  this->Superclass::setup();



  //// 
  // Init lib at some path, with some name and category.

  this->ps=('/');
#ifdef WIN32 
  //this->ps=('\\');
  this->DataRoot=QString("C:");
#else
  this->ps=('/');
  this->DataRoot=QString("");
#endif
  QString DataStoreName="Brain";
  QString DataStoreCategory="Organ";
  //DataRoot=DataRoot+ps+"DataLibraries"+ps+DataStoreName; //
  DataStoreName="AtlasData";
  DataRoot=DataRoot+ps+"DataLibraries"; //
  DataStore = new vtkMRMLNDLibraryNode(DataRoot.toStdString(),DataStoreName.toStdString(),DataStoreCategory.toStdString());
  // perhaps it would be best to use default constructor here and just let panelDataSelector do the setting/building and other. Investigate later, but here is the code in an if ( 0 ) set
  if ( 0 ) {
  //DataStore = new vtkMRMLNDLibraryNode(DataRoot.toStdString());
  //DataStore->SetLibRoot(DataRoot.toStdString());
  //vtkMRMLNDLibraryBuilder * dataStoreBuilder=new vtkMRMLNDLibraryBuilder(); 

  //dataStoreBuilder->SetLibPointer(DataStore);
  //dataStoreBuilder->Build(DataStore); 
  //std_str_hash tagCloud=dataStoreBuilder->libFileRead("path");
  }


//   this->FullDataLibrary = new vtkMRMLNDLibraryNode(DataRoot.toStdString(),std::string("Brain"),std::string("organ"));
//   vtkMRMLNDLibraryBuilder * libBuilder= new vtkMRMLNDLibraryBuilder();
//   bool status = libBuilder->Build(FullDataLibrary);
//   if ( ! status ) 
//     {
//       QString failMessage=
// 	"build failed on lib";
//       failMessage=failMessage+QString::fromStdString(FullDataLibrary->GetLibName());

//       this->PrintText(failMessage);
//     }
  //this->HomeButton();
// need to setCollapsed true on gallery selection and gallery control during init,
  //d->DocumentationArea->setCollapsed(false);
  d->GalleryArea->setCollapsed(true);
  d->ControlArea->setCollapsed(true);
  
  if (!DataStore ) 
    {
    this->PrintText("ERROR with InputLibrary at "+DataRoot+" ."	);
    }
  else
    {
    qSlicerCIVM_GalleryControlPanelDataSelectorWidget * panelDataSelector =
      new qSlicerCIVM_GalleryControlPanelDataSelectorWidget(this,DataStore);
    d->SelectionLayout->addWidget(panelDataSelector);
  
    //d->SelectionLayout->
//   connect(panelDataSelector,SIGNAL(DataSelected(vtkMRMLNDLibraryNode *)),SLOT(BuildGallery(vtkMRMLNDLibraryNode *)));
//   connect(panelDataSelector,SIGNAL(DataSelected(vtkMRMLNDLibraryNode *)),SLOT(DataSelected(vtkMRMLNDLibraryNode *)));

    connect(panelDataSelector,SIGNAL(DataSelected()),SLOT(BuildGallery()));
    connect(panelDataSelector,SIGNAL(DataSelected(vtkMRMLNDLibraryNode *)),SLOT(BuildGallery(vtkMRMLNDLibraryNode *)));
    connect(this,SIGNAL(NoSupportedProtocols(std::string)),panelDataSelector,SLOT(SelectNext(std::string) ));

    }
//   if ( 0 )
//     {//code superseeded by the paneldataselctor
//     //connect LibrarySelectDropList to filllibselector, and to build gallery
//     connect(d->LibrarySelectorDropList,SIGNAL(activated(int)),SLOT(FillDataLibraries()));
//     connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(BuildGallery()));
//     connect(d->HomeDataPushButton,SIGNAL(clicked()),SLOT(HomeButton()));
//     connect(d->BackDataPushButton,SIGNAL(clicked()),SLOT(BackButton()));
//     }
  
#ifndef WIN32
  //INSERT ADVANCED SECTION TO MAIN PANLE WITH DATA ROOT CHANGER FUNCTION
#endif
  
  // preload data scene.
  if ( 0 ) 
    {
    QString out_path = "StartupRat.mrml";
    out_path.replace(':','_');
    out_path=this->DataRoot+ps+out_path;
    this->PrintText("Startup load of "+out_path);
    //out_path.replace("C_","C:");
    //out_path.replace("DataLibraries"+ps,"");
    qSlicerApplication::application()->ioManager()->loadScene(out_path,false);
    }
    
}

// //-----------------------------------------------------------------------------
// void qSlicerCIVM_GalleryControlModuleWidget::HomeButton(void) 
// {
//   Q_D(qSlicerCIVM_GalleryControlModuleWidget);
//   SelectorIndent=0;
//   this->FillDataLibraries(DataRoot); // replacement for SetLibraries which build us a qhash of name=path, now using a name=ndlib std::map
//   this->PrintText("Datapath="+DataRoot);
//   // populate our dropdown
//   // libselector filled via two function calls now.
//   this->FillLibrarySelector();
//   d->LibrarySelectorDropList->setDefaultText("<No Data Selected>");
//   d->LibrarySelectorDropList->setCurrentIndex(-1);
//   return;
// }
// //-----------------------------------------------------------------------------
// void qSlicerCIVM_GalleryControlModuleWidget::BackButton(void) 
// {
//   QFileInfo * dsInfo=new QFileInfo::QFileInfo(QString::fromStdString(DataStore->GetLibRoot()) );
//   QDir dsBasePath= dsInfo->dir();
//   bool selectorfill=this->FillDataLibraries(dsBasePath.path());
//    if (selectorfill)
//     {
//     this->PrintText("Fill data says we should fill selector");
//     FillLibrarySelector();
//     }
//   return;
// }


// //-----------------------------------------------------------------------------
// void qSlicerCIVM_GalleryControlModuleWidget::FillDataLibraries(void) {
//   this->PrintMethod("FillDataLibraries Slot");
//   bool selectorfill=FillDataLibraries(ReadLibraryPath(this->ReadLibraryName()));
//   if (selectorfill)
//     {
//     this->PrintText("Fill data says we should fill selector");
//     FillLibrarySelector();
//     }
//   return;
// }

// //-----------------------------------------------------------------------------
// // fills the DataLibraries container from the DataStore container. 
// bool qSlicerCIVM_GalleryControlModuleWidget::FillDataLibraries(QString libPath) {
//   this->PrintMethod("FillDataLibraries");
//   // this will be called when we want to change libraries or on initalization of our control panel
//   // this gives a few different cases, 
//   // case 1 is init, 
//   // libPath will be the same as this->DataRoot, but DataStore->GetLibRoot() will be differnet)
//   // case 2 is new lib
//   //   libPath will not be the same a this->DataRoot, or DataStore->GetLibRoot();
//   //   should change our dataroot and continue.
//   // case 3 is same lib
//   //   same lib should ammount to no-op
//   //if our dataroot is the same as the one in our library. or it is the same as our init?
//   if (libPath != QString::fromStdString(DataStore->GetLibRoot()) )// && libPath ==  this->DataRoot )
//     {// desired path is not the same as our current data store, should happen on init, or on change.
//     this->PrintText("DataStore Reset to new lib path");
//     DataStore->ResetLibrary(libPath.toStdString());
//     vtkMRMLNDLibraryBuilder * libBuilder= new vtkMRMLNDLibraryBuilder;
//     SelectorIndent=0;
    
//     libBuilder->Build(DataStore);
//     DataLibraries=DataStore->GetSubLibraries();
//     } 
//   else  if ( libPath == QString::fromStdString(DataStore->GetLibRoot())  ) 
//     {//desiredpath is same as current data store path,
//         this->PrintText("Re-init condition, no reset needed");  
//         return false;
//     }
//   else 
//     {
//     this->PrintText("lib path else condition");
//     }
//   return true;
// }
// //-----------------------------------------------------------------------------
// // fills the lib selector object in the gui from the DataLibraries container.
// void qSlicerCIVM_GalleryControlModuleWidget::ClearLibrarySelector(void) {
//   this->PrintMethod("ClearLibrarySelector");
//   Q_D(qSlicerCIVM_GalleryControlModuleWidget);
//   d->LibrarySelectorDropList->clear();
//   return;  
// }
// //-----------------------------------------------------------------------------
// // fills the lib selector object in the gui from the DataLibraries container.
// void qSlicerCIVM_GalleryControlModuleWidget::FillLibrarySelector(void) {
//   this->PrintMethod("FillLibrarySelector");
//   Q_D(qSlicerCIVM_GalleryControlModuleWidget);
//   int i=0;
//   QStringList libList;
//   std::string printspc;
//   printspc="";
//   while (printspc.size()<SelectorIndent) 
//     {
//     printspc=printspc+" ";
//     }
//   libList <<  QString::fromStdString(printspc) + QString::fromStdString(DataStore->GetLibName());
//   SelectorIndent=SelectorIndent+2;
//   for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= DataLibraries.begin(); subIter!=DataLibraries.end(); ++subIter)
//     {
//     while (printspc.size()<SelectorIndent) 
//       {
//       printspc=printspc+" ";
//       }
//     //std::string subLib=subIter->second->GetLibName();
//     libList<< QString::fromStdString(printspc) + QString::fromStdString(subIter->first);
//     i++;
//     }
//   int libInsertPoint=0;
//   if ( d->LibrarySelectorDropList->count()>0 ) 
//     {
//     this->PrintText("  fill lib selector: clear");
//     this->ClearLibrarySelector();
//     } else 
//     {
//     //if ( d->LibrarySelectorDropList->count()
//     libInsertPoint=d->LibrarySelectorDropList->currentIndex()+1;
//     }
//   this->PrintText("  fill lib selector: Insert Items");
//   d->LibrarySelectorDropList->insertItems(libInsertPoint,libList); // if we dont clear

//   this->PrintText("  fill lib selector: set index 0 ");
//   d->LibrarySelectorDropList->setCurrentIndex(0);
//   d->ControlArea->setCollapsed(true);

//   return;
// }

// //-----------------------------------------------------------------------------
// QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibraries(QString libPath) {
//   // called on module start to populate our list of libraries.
//   int maxDepth=1;
//   QStringList libraries=GetLibraries(libPath,maxDepth);
//   return libraries;
// }

// //-----------------------------------------------------------------------------
// QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibraries(QString libPath,int maxDepth) {
//   // get library locations starting at dataroot, this should return a listing of all relevent libraries we could look.
//   // That list should include the leaf libraries, the maxDepth integer is a limiter for how deep we will traverse
//   // the real work is not done yet in this function, we just return one library for now. 
//   QStringList libraries;
//   bool old_way=false;
//   this->PrintMethod("GetLibraries");
//   // get directory listing at dataRoot including all subdirs, add each (sorted somehow) to libraries list and return
//   // rat times
//   //   00000172800 00000345600 00000691200 00001036800 00001555200 00002073600 00003456000 00006912000
//   QStringList rat_times;
//   rat_times << "00000172800" << "00000345600" << "00000691200" << "00001036800" << "00001555200" << "00002073600" << "00003456000" << "00006912000";
//   QString rat_adult_time=rat_times.last();
//   QString rat_first_time=rat_times.first();
//   //rat_adult_time="00000172800";//rat day 04 for testing.
//   QString max_mamal_time="12623040000";
//   QString human_adult_time = max_mamal_time;//max mamal for unknown adult age
//   QString rat_spec = "average";
//   QString mouse_spec = "DTI";
//   QString human_spec = "130827-2-0";
//   QString dog_spec = "AdultCanisL";
//   QString monkey_spec="AdultMacacaM";
//   QString monkey_spec2="AdultMacacaF";


//   vtkIndent id =  vtkIndent::vtkIndent(2);
//   this->PrintText("Lib2:");
//   id=vtkIndent::vtkIndent(4);
//   DataStore->PrintSelf(std::cout,id); // 

//   std::vector<std::string> * vecLibPaths = new  std::vector<std::string>;
//   vecLibPaths=DataStore->GetAllPaths();
//   QStringList  myNDLibPaths= QStringList::QStringList();

//   ////
//   // this works but it might not be the best way
//   ////
//   if ( 1 ) {
//     for ( int i=0; i< vecLibPaths->size(); i++ ) 
//       {
// 	myNDLibPaths << vecLibPaths->at(i).c_str(); 
// 	myNDLibPaths << vecLibPaths->at(i).c_str();
//       }
//   } else {

//   if ( maxDepth < 0 )  { libraries << "Rattus_norvegicus:Wistar:Adult" ; }
//   libraries << "Rattus_norvegicus:Wistar:"+rat_spec+":"+rat_adult_time ;
// #ifndef WIN32
//   if ( maxDepth < 0 )  { libraries << "Rattus_norvegicus:Wistar:Juvenile"; }
//   libraries << "Rattus_norvegicus:Wistar:"+rat_spec+":"+rat_first_time ;
// #endif
//   if ( maxDepth < 0 )  { libraries << "Mus_Musculus:Adult"; }
//   libraries << "Mus_Musculus:whs_atlas:"+mouse_spec;//+":"+max_mamal_time;
//   if ( maxDepth < 0 )  { libraries << "Macaca_mulatta"; }
//   libraries << "Macaca_mulatta:"+monkey_spec;//+":"+max_mamal_time;
//   if ( maxDepth < 0 )  { libraries << "Human:Adult"; }
//   libraries << "Human:"+human_spec;//+":"+human_adult_time;
//   if ( old_way ) 
//     { 
//       return libraries;
//     } 
//   else 
//     { 
//       return myNDLibPaths;
//     }
// }

// //-----------------------------------------------------------------------------
// QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryPath(void) {
//   this->PrintText("ReadLibraryPath Slot");
//   return this->ReadLibraryPath(this->ReadLibraryName());
// }

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryPath(QString libraryName) 
{
  // Read the library path from the ndlib referenced by the libraryName entry in our datastore qhash 
  this->PrintMethod("ReadLibraryPath");
  QString libraryPath="NoPath";
  
  if ( 0 ) 
    {// this is old and BAD BAD BAD.
    if ( !DataStore->GetCurrentSelection() )//if no selection
      {
      return libraryPath;
      }
    
    this->PrintText("ReadLibraryName "+libraryName);
    if (libraryName=="<No Data Selected>"|| libraryName=="NoName") 
      {
      this->PrintText("Lib path blank");
      } 
    else if ( libraryName == QString::fromStdString(DataStore->GetLibName()) ) 
      {
      libraryPath=QString::fromStdString(DataStore->GetLibRoot() );//GetCurrentSelection()
      }
    else
      {
      libraryPath=QString::fromStdString(DataStore->GetCurrentSelection()->GetLibRoot());
      this->PrintText("ReadLibraryPath "+libraryName+":"+libraryPath);
      }
    }
  return libraryPath;
}

//-----------------------------------------------------------------------------
// 
QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryName(void) {
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  QString libraryName="<No Data Selected>"; 
  if ( 0 ) 
    {// this is old and BAD BAD BAD.
    if ( !DataStore->GetCurrentSelection() )//if no selection
      {
      this->PrintText("No current selection!");
      return libraryName;
      }
    libraryName=QString::fromStdString(DataStore->GetCurrentSelection()->GetLibName());
    this->PrintText("ReadLibraryName "+libraryName);
    if (libraryName=="<No Data Selected>") 
      {
      this->PrintText("Lib name blank");
      libraryName="NoName";
      }
    }
  return libraryName;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery(void) {
  this->PrintMethod("BuildGallery void slot");
  this->BuildGallery(DataStore->GetCurrentSelection());
  return;
}
//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery(vtkMRMLNDLibraryNode * selectedLib)
{
  this->PrintMethod("BuildGallery lib slot");
  if ( !selectedLib)
    {
    this->PrintText("Lib select fail");
    return;
    } 
  else
    {
    CurrentNode = selectedLib;
    this->PrintText("Lib select good, retaining CurrentNode");
    }
  this->BuildGallery(QString::fromStdString(selectedLib->GetLibName()));
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery(QString libraryName) {
  // polls our data storage for the display protocols for a given library
  // this should be fired by any change to the library, eg connected to the drop down list of libraries.
  // insert a button into our gallery zone for each return value from GetDisplayProtocols
  this->PrintMethod("BuildGallery");  
  if (libraryName=="<No Data Selected>" || libraryName=="NoName" || libraryName == "" ) 
    {
    this->PrintText("Lib name blank");
    return;
    }
  else 
    {
    this->PrintText("Lib name present, continuing");
//    return;
    }
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  
  ////
  // clear layout
  // d->GalleryLayout->delete
  this->clearLayout(d->GalleryLayout,true);
  this->clearLayout(d->ControlLayout,true); // not convinced i want to clear this all the time.
  QStringList protocols = this->GetDisplayProtocols(CurrentNode); // decide what protocols are appropriate.
  QList<QPushButton*> galleryButtons;
  // prune protocol list
  // this should occur in our getdisplayprotocols function, 
  for (int i = 0; i < protocols.size(); ++i)
    {
    //qSlicerCIVM_GalleryControlDisplayProtocol * check = new qSlicerCIVM_GalleryControlDisplayProtocol(protocol[i]);
    //if(  !check.IsSupported(DataLibrary->GetLibDims) ) 
    //{
    //protocols.remove(i);// using this should probably switch to iterator access.
    //}
      
    }
  // add buttons for each protcol with their icon (and/or) button.
  for (int i = 0; i < protocols.size(); ++i)
    {
    //cout << fonts.at(i).toLocal8Bit().constData() << endl;

    // foreach protocol add to the protcol location in our gui controls
    // QVBoxLayout * l = new QVBoxLayout;
    // layouts[i]->addWidget(clockViews[i])
    //   d->ControlFrame->setLayout(l);
    this->PrintText(protocols[i]);  

    //// FOR EACH PROTOCOL
    if ( protocols[i] != "NOSUPPORT" )
      {
      QPushButton * widge=  new QPushButton;
      widge->setText(protocols[i]);
      widge->setObjectName(protocols[i]);
        
      QString iconPath=QString::fromStdString(CurrentNode->GetLibRoot())+"/GalleryIcons"+ps+libraryName+'_'+protocols[i]+".png"; 
      this->PrintText(iconPath);
      widge->setIcon(QIcon(iconPath));
      galleryButtons.push_back(widge);
      d->GalleryLayout->addWidget(galleryButtons.at(i));
        
      //set button connections
      connect(widge,SIGNAL(clicked()),SLOT(SetControls()));
      } 
    else 
      {
      QLabel * lab= new QLabel(protocols[i]);
      d->GalleryLayout->addWidget(lab);
      }
    }
  
  // Check if there were no supported protocols, 
  // if we have protocols in our list and they were not unsupported expand the gallery area
  // if we have found the unsupported protocol, emit a no supported protocols signal.
  // (connection to data selector for now in setup function)
  if ( protocols.size()>0 )
    { 
    if ( protocols[0] != "NOSUPPORT" )
      {
      d->GalleryArea->setCollapsed(false);
      }
    else 
      {
      //////emit NoSupportedProtocols(CurrentNode);
      emit NoSupportedProtocols(libraryName.toStdString()); //commented to prevent crashbug
      }

    }

  return;
}
//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::DataSelected (vtkMRMLNDLibraryNode * selectedLib) {
  this->PrintMethod("DataSelected lib arg");
  //this->BuildGallery(QString::fromStdString(selectedLib->GetLibName()));
  if ( !selectedLib) 
    {
    this->PrintText("Lib select fail");
    return;
    }
  CurrentNode=selectedLib;
  return;  
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::DataSelected (void) {
  this->PrintMethod("DataSelected void arg");
  //this->BuildGallery(QString::fromStdString(DataStore->GetCurrentSelection()->GetLibName()));
  CurrentNode=DataStore->GetCurrentSelection();
  return;
}


//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::SetControls(void)
{
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  QObject * panelButton=this->sender();
  QString panelName=panelButton->objectName();
  this->clearLayout(d->ControlLayout,true);
  //protocols[0]
  if ( panelName == "PGR" ) 
    {
    //qSlicerCIVM_GalleryControlPanelPGRWidget * panel = new qSlicerCIVM_GalleryControlPanelPGRWidget(this); //Ui_
    //qSlicerCIVM_GalleryControlPanelPGRWidget * panelPGR = new qSlicerCIVM_GalleryControlPanelPGRWidget(this,this->ReadLibraryPath(this->ReadLibraryName())); 
    qSlicerCIVM_GalleryControlPanelPGRWidget * panelPGR = new qSlicerCIVM_GalleryControlPanelPGRWidget(this,QString::fromStdString(CurrentNode->GetLibRoot()));
    this->PrintText( "adding controls using "+QString::fromStdString(CurrentNode->GetLibName()));
    //QSlicerModuleWidget
    d->ControlLayout->addWidget(panelPGR);
    } 
  else if ( panelName == "FA_Render_Static" ) 
    {
    QString out_path = "Static_Render"+ps+QString::fromStdString(CurrentNode->GetLibName())+"_fa.mrml";
    out_path.replace(':','_');
    out_path=QString::fromStdString(CurrentNode->GetLibRoot())+ps+out_path;
    this->PrintText("FA_Render load of "+out_path);
    //qSlicerApplication::application()->ioManager()->loadScene(out_path,true);
    qSlicerApplication::application()->ioManager()->loadScene(out_path,false);
    }
  else if ( panelName == "Label_Render_Static" ) 
    {
    //this->LoadListPanel(QString::fromStdString(CurrentNode->GetLibName()));
    this->LoadListPanel(panelName);
    }
  else
    {
    this->PrintText("Unreconized Panel selection");
    //////qSlicerCIVM_NDDisplayModule * civmNDDisplay = new qSlicerCIVM_NDDisplayModule(this);
    //qSlicerCIVM_NDDisplayModuleWidget * civmNDDisplay = new qSlicerCIVM_NDDisplayModuleWidget(this);
    //d->ControlLayout->addWidget(civmNDDisplay);
    }
  d->ControlArea->setCollapsed(false); 
  d->GalleryArea->setCollapsed(true);
  return;
}

void qSlicerCIVM_GalleryControlModuleWidget::LoadStaticRender(void)
{
  QObject * panelButton=this->sender();
  QString panelName=panelButton->objectName();
  //QString::fromStdString(CurrentNode->GetLibName())+"_fa.mrml"
  QString out_path = "Static_Render"+ps+panelName;
  
  out_path.replace(':','_');
  out_path=QString::fromStdString(CurrentNode->GetLibRoot())+ps+out_path;
  this->PrintText("Static_Render load of "+out_path);
  //qSlicerApplication::application()->ioManager()->loadScene(out_path,true);
  qSlicerApplication::application()->ioManager()->loadScene(out_path,false);
  return;
}
//
void qSlicerCIVM_GalleryControlModuleWidget::LoadListPanel(QString panelName)
{
   // polls our data storage for the display protocols for a given library
  // this should be fired by any change to the library, eg connected to the drop down list of libraries.
  // insert a button into our gallery zone for each return value from GetDisplayProtocols
  this->PrintMethod("BuildControl");  
//   if (libraryName=="<No Data Selected>" || libraryName=="NoName" || libraryName == "" ) 
//     {
//     this->PrintText("Lib name blank");
//     return;
//     }
//   else 
//     {
//     this->PrintText("Lib name present, continuing");
// //    return;
//     }
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  QStringList panelInfo;
//   QString line = in.readLine();
//   QRegExp sep("\\s*/*/");
  //while (!line.isNull()) {
//  }
  QRegExp sep("_");    
  panelInfo = panelName.split(sep);
  QString pID="";
  //if ( panelInfo[0]== "Label"|| panelInfo[0]== "FA" ) 
  if ( panelInfo[1]== "Render" && panelInfo[2]== "Static" ) 
    {
    //"labels"
    pID=panelInfo[0];
    }

  ////
  // clear layout
  // d->ControlLayout->delete
//  this->clearLayout(d->GalleryLayout,true);
  this->clearLayout(d->ControlLayout,true); // not convinced i want to clear this all the time.
  QRegExp protoCompare("^"+pID+".*[.]mrml$");
  QStringList sceneFiles = this->GetMatchingFilesInDir(QString::fromStdString(CurrentNode->GetLibRoot())+"/Static_Render",protoCompare); // decide what sceneFiles are appropriate.
  QList<QPushButton*> controlButtons;
  // prune sceneFile list
  // this should occur in our getdisplaysceneFiles function, 
  for (int i = 0; i < sceneFiles.size(); ++i)
    {
    //qSlicerCIVM_GalleryControlDisplayProtocol * check = new qSlicerCIVM_GalleryControlDisplayProtocol(protocol[i]);
    //if(  !check.IsSupported(DataLibrary->GetLibDims) ) 
    //{
    //sceneFiles.remove(i);// using this should probably switch to iterator access.
    //}
      
    }
  // add buttons for each protcol with their icon (and/or) button.
  for (int i = 0; i < sceneFiles.size(); ++i)
    {
    //cout << fonts.at(i).toLocal8Bit().constData() << endl;

    // foreach protocol add to the protcol location in our gui controls
    // QVBoxLayout * l = new QVBoxLayout;
    // layouts[i]->addWidget(clockViews[i])
    //   d->ControlFrame->setLayout(l);
    this->PrintText(sceneFiles[i]);  

    //// FOR EACH PROTOCOL
    if ( sceneFiles[i] != "NOSUPPORT" )
      {
      QPushButton * widge=  new QPushButton;
      widge->setText(sceneFiles[i]);
      widge->setObjectName(sceneFiles[i]);
        
      QString iconPath=QString::fromStdString(CurrentNode->GetLibRoot())+"/ControlIcons"+ps+QString::fromStdString(CurrentNode->GetLibName())+'_'+sceneFiles[i]+".png"; 
      this->PrintText(iconPath);
      widge->setIcon(QIcon(iconPath));
      controlButtons.push_back(widge);
      d->ControlLayout->addWidget(controlButtons.at(i));
        
      //set button connections
      connect(widge,SIGNAL(clicked()),SLOT(LoadStaticRender()));
      } 
    else 
      {
      QLabel * lab= new QLabel(sceneFiles[i]);
      d->ControlLayout->addWidget(lab);
      }
    }
  
  // Check if there were no supported sceneFiles, 
  // if we have sceneFiles in our list and they were not unsupported expand the control area
  // if we have found the unsupported protocol, emit a no supported sceneFiles signal.
  // (connection to data selector for now in setup function)
  if ( sceneFiles.size()>0 )
    { 
    if ( sceneFiles[0] != "NOSUPPORT" )
      {
      d->ControlArea->setCollapsed(false);
      }
    else 
      {
      //////emit NoSupportedSceneFiles(CurrentNode);
      //emit NoSupportedSceneFiles(libraryName.toStdString()); //commented to prevent crashbug
      }

    }

  return; 
}
//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::clearLayout(QLayout* layout, bool deleteWidgets = true)
{
// function to clear the control areas(protcol selection and control selection).
  while (QLayoutItem* item = layout->takeAt(0))
    {
    if (deleteWidgets)
      {
      if (QWidget* widget = item->widget())
        delete widget;
      }
    if (QLayout* childLayout = item->layout())
      clearLayout(childLayout, deleteWidgets);
    delete item;
    }
  return;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetDisplayProtocols() 
{
  // This function interface is not certain yet, it might be desireable to take a list of dimensions
  // or a list of lists of values in dimensions.
  // also might need to instantiate all possible protocols and return a pointer to a vector of them.
  //
  // probably want a container of all possible protocols, 
  // and a container of relevent protocols, 
  // this should build the list of relvent from the list of all possible. 
  QStringList protocols;
  //get libdims? 
  //select layouts supporting up to number of libdims?
  //select layouts supporting each combination of libdims?
  protocols << "PGR" << "FA_Render" ;
  return protocols;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetDisplayProtocols(vtkMRMLNDLibraryNode * selectedLib)  
{
  this->PrintMethod("GetDisplayProtocols");

  if ( !selectedLib) 
    {
    this->PrintText("Lib select fail");
    //QStringList e=this->GetDisplayProtocols();
    QStringList e;
    e << "LibrarySelectionFailure!";
    return e;
    }
  QString libName =QString::fromStdString(selectedLib->GetLibName());
  QStringList protocols;
  QStringList panels;
  panels << "PGR";
  panels << "FA_Render_Static";
  panels << "Label_Render_Static";
  //for each panel
  //// SUPPORTLIST HACK.
  QString panelSupportDir = QString::fromStdString(DataStore->GetLibRoot());
  for (int i = 0; i < panels.size(); ++i)
    {
    this->PrintText("support check for "+panels.at(i));
    QFile panelConfFile(panelSupportDir+"/"+panels.at(i)+".conf");
    QStringList panelSupportList;//supported libnames for this panel
    if ( panelConfFile.open(QIODevice::ReadOnly) ) 
      {
      QTextStream in(&panelConfFile);
      while(!in.atEnd() )
        {
        QString line= in.readLine();
        //if(!line.empty())
        panelSupportList << line;
	  
        }
      QRegExp protoCompare("^"+libName+"$");
      if ( panelSupportList.indexOf(protoCompare)>=0 )
        {
        protocols << panels.at(i);
        }  
      panelConfFile.close();
      }
    else
      {
      //QMessageBox::information(0, "error", file.errorString());
      this->PrintText("Panel conf file failed to open! "+panelConfFile.fileName());
      this->PrintText(panelConfFile.errorString());


      }
    }
  
  if ( 0 )
    {
    // temporary listing of possible species for our FARender support.
    QStringList species ;
    species 
      //<< "0_species" 
      //<< "Canis_lupus" 
      << "Human" 
      << "Macaca_mulatta" 
      //<< "Macaca_fascicularis" 
      << "Mus_Musculus" 
      << "Rattus_norvegicus"
      << "20140417__000Y_";
    QStringList pgrlist;
    pgrlist 
      << "130827-2-0"
      << "20140417__000Y_"
#ifndef WIN32
      << "AdultCanisL"
#endif
      << "AdultMacacaM"
#ifndef WIN32
      << "AdultMacacaF"
//    << "average"
      << "day_02"
#endif
      << "day_80"
      << "dti101";
    QStringList organList ; 
    organList
      << "Brain"
      << "Heart";
  
    QRegExp protoCompare("^"+libName+"$");
    if ( species.indexOf(protoCompare)>=0 )
      {
      protocols << "FA_Render_Static";
      }
    if ( pgrlist.indexOf(protoCompare)>=0 )
      {
      protocols << "PGR";
      }  
    if( organList.indexOf(protoCompare)>=0 )
      {
      //protocols << "NoOrganProtocol";
      }
    }
  if ( protocols.size()==0 ) 
    {
    protocols << "NOSUPPORT";
    }
  return protocols; 
}
// //-----------------------------------------------------------------------------
// QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibDims(QString library ) {
//   // make one in each gallery class
//   QStringList dimensions;
//   dimensions << "contrast"; //<< "time" ;
//   return dimensions;
// }


QStringList qSlicerCIVM_GalleryControlModuleWidget::GetMatchingFilesInDir(QString dir,QRegExp protoCompare)
{
//QDir recoredDir("YOUR DIRECTORY");
  QDir recoredDir(dir);
  QStringList allFiles = recoredDir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst );//(QDir::Filter::Files,QDir::SortFlag::NoSort)
//   if ( species.indexOf(protoCompare)>=0 )
//       {
//       protocols << "FA_Render_Static";
//       } 

 

  return allFiles.filter(protoCompare);
}

// //-----------------------------------------------------------------------------
// QStringList qSlicerCIVM_GalleryControlModuleWidget::GetDimEntries(QString library,QString dimension) {
//   // make one in each gallery class
//   QStringList dimValues;
//   // if dimension== contrast
//   // if dimension== time
//   dimValues << "adc" << "b0" << "dwi" << "fa" << "fa_color" << "freq" << "gre" << "rd"; 
//   return dimValues;
// }


//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::SetDisplayLayout(QString name)
{
  // make one in each gallery class
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildDisplayControls(QString protocol,QWidget panel)
{
// make one in each gallery class
  return;  
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::LoadData(){
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::nothing(){
  this->PrintText("I AM GALlERY CONTROL!");
  return;
}

void qSlicerCIVM_GalleryControlModuleWidget::PrintMethod(const QString text)
{
  QString pass="qSlicerCIVM_GalleryControlModuleModuleWidget method:"+text;
  this->PrintText(pass);
  return;
}


void qSlicerCIVM_GalleryControlModuleWidget::PrintText(const QString text)
{
  QTextStream out(stdout);
  out << text<<"\n";
  return;
}
