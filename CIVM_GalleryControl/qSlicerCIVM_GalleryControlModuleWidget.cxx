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
#include "vtkMRMLNDLibraryBuilder.h"

// Panel includes
#include "qSlicerCIVM_GalleryControlPanelPGRWidget.h"
#include "qSlicerCIVM_GalleryControlPanelDataSelectorWidget.h"

// SlicerQt includes
#include "qSlicerApplication.h"
#include "qSlicerIOManager.h"
#include "qSlicerCIVM_GalleryControlModuleWidget.h"
#include "ui_qSlicerCIVM_GalleryControlModuleWidget.h"



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
  this->ps=('/');
#ifdef WIN32 
  //this->ps=('\\');
  this->DataRoot=QString("C:");
#else
  this->ps=('/');
  this->DataRoot=QString("");
#endif
  DataRoot=DataRoot+ps+"DataLibraries"+ps+"Brain"; //
  DataStore = new vtkMRMLNDLibraryNode(DataRoot.toStdString());
  //DataStore -> SetParentNode(DataStore);// becuase of behavior this has to be added.

  //DataStore->SetLibRoot();
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

  qSlicerCIVM_GalleryControlPanelDataSelectorWidget * panelDataSelector =
    new qSlicerCIVM_GalleryControlPanelDataSelectorWidget(this,DataStore);
  d->SelectionLayout->addWidget(panelDataSelector);
  //d->SelectionLayout->
  connect(panelDataSelector,SIGNAL(DataSelected()),SLOT(BuildGallery()));
  
//   if ( 0 )
//     {//code superseeded by the paneldataselctor
//     //connect LibrarySelectDropList to filllibselector, and to build gallery
//     connect(d->LibrarySelectorDropList,SIGNAL(activated(int)),SLOT(FillDataLibraries()));
//     connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(BuildGallery()));
//     connect(d->HomeDataPushButton,SIGNAL(clicked()),SLOT(HomeButton()));
//     connect(d->BackDataPushButton,SIGNAL(clicked()),SLOT(BackButton()));
//     }
  
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

// void qSlicerCIVM_GalleryControlModuleWidget::DataSelected(void)
// {
  

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

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryPath(void) {
  this->PrintText("ReadLibraryPath Slot");
  return this->ReadLibraryPath(this->ReadLibraryName());
}

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryPath(QString libraryName) {
  // Read the library path from the ndlib referenced by the libraryName entry in our datastore qhash 
  QString library="NoPath";
    if ( !DataStore->GetCurrentSelection() )//if no selection
      {
      return library;
      }
  this->PrintText("ReadLibraryName "+libraryName);
  if (libraryName=="<No Data Selected>"|| libraryName=="NoName") 
    {
    this->PrintText("Lib path blank");
    } 
  else if ( libraryName == QString::fromStdString(DataStore->GetLibName()) ) 
    {
    library=QString::fromStdString(DataStore->GetLibRoot() );//GetCurrentSelection()
    }
  else
    {
    library=QString::fromStdString(DataStore->GetCurrentSelection()->GetLibRoot());
    this->PrintText("ReadLibraryPath "+libraryName+":"+library);
    }
  return library;
}

//-----------------------------------------------------------------------------
// 
QString qSlicerCIVM_GalleryControlModuleWidget::ReadLibraryName(void) {
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  QString libraryName="<No Data Selected>"; 
  //libraryName=d->LibrarySelectorDropList->currentText().trimmed();
  if ( !DataStore->GetCurrentSelection() )//if no selection
    {
    return libraryName;
    }
  libraryName=QString::fromStdString(DataStore->GetCurrentSelection()->GetLibName());
  this->PrintText("ReadLibraryName "+libraryName);
  if (libraryName=="<No Data Selected>") 
    {
    this->PrintText("Lib name blank");
    libraryName="NoName";
    }
  return libraryName;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery (void) {
  this->PrintMethod("BuildGallery slot");
  this->BuildGallery(this->ReadLibraryName());
  
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery (QString library) {
  // polls our data storage for the display protocols for a given library
  // this should be fired by any change to the library, eg connected to the drop down list of libraries.
  // insert a button into our gallery zone for each return value from GetDisplayProtocols
  this->PrintMethod("BuildGallery");  
  if (library=="<No Data Selected>" || library=="NoName" || library == "" ) 
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
  this->clearLayout(d->ControlLayout,true);
  QStringList protocols = this->GetDisplayProtocols (); // currently a hardcoded list of PGR and FA_Render
  QList<QPushButton*> galleryButtons;

  // prune protocol list
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
      QPushButton * widge=  new QPushButton;
      //QIcon * ico = new QIcon(this->DataRoot+ps+"GalleryIcons"+ps+library+"_"+protocols[i]);
  
      widge->setText(protocols[i]);
      widge->setObjectName(protocols[i]);
      //QString lP=library;
      //QString lN=library;
      //lP.replace(':',ps);
      //this->ReadLibraryPath=this->DataRoot+ps+lP;
      //this->ReadLibraryPath=this->ReadLibraryPath(this->ReadLibraryName());
      
      //this->SelectedLib=d->LibrarySelectorDropList->currentText().trimmed();
      //this->SelectedLibName=this->ReadLibraryName();


      //lN.replace(':','_');
      //iconPath=iconPath+ps+"GalleryIcons"+ps+library+'_'+protocols[i]+".png"; //+ps+"GalleryIcons"
      QString iconPath=ReadLibraryPath(library)+"/GalleryIcons"+ps+library+'_'+protocols[i]+".png"; 
      this->PrintText(iconPath);
      //iconPath.replace(':',ps);
      widge->setIcon(QIcon(iconPath));
      galleryButtons.push_back(widge);
      d->GalleryLayout->addWidget(galleryButtons.at(i));
      
      //set button connections
      connect(widge,SIGNAL(clicked()),SLOT(SetControls()));//widge->text())));
    }
  
  d->GalleryArea->setCollapsed(false);
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::DataSelected (void) {
  this->BuildGallery(QString::fromStdString(DataStore->GetCurrentSelection()->GetLibName()));
  return;
}


//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::SetControls()
{
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  QObject * panelButton=this->sender();
  QString panelName=panelButton->objectName();
  this->clearLayout(d->ControlLayout,true);
  //protocols[0]
  if ( panelName == "PGR" ) 
    {
      //qSlicerCIVM_GalleryControlPanelPGRWidget * panel = new qSlicerCIVM_GalleryControlPanelPGRWidget(this); //Ui_
    qSlicerCIVM_GalleryControlPanelPGRWidget * panelPGR = new qSlicerCIVM_GalleryControlPanelPGRWidget(this,this->ReadLibraryPath(this->ReadLibraryName())); //Ui_
    this->PrintText( "adding controls using "+this->ReadLibraryName());
      //QSlicerModuleWidget
      d->ControlLayout->addWidget(panelPGR);
    } 
  else if ( panelName == "FA_Render" ) 
    {
    QString out_path = "FARenderScenes"+ps+this->ReadLibraryName()+".mrml";
    out_path.replace(':','_');
    out_path=this->DataRoot+ps+out_path;
    this->PrintText("FA_Render load of "+out_path);
    //out_path.replace("C_","C:");
    //out_path.replace("DataLibraries"+ps,"");
    qSlicerApplication::application()->ioManager()->loadScene(out_path,false);
    
    }
  else
    {
    this->PrintText("Unreconized Panel selection");
    }
  d->ControlArea->setCollapsed(false); 
  d->GalleryArea->setCollapsed(true);
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

// //-----------------------------------------------------------------------------
// QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibDims(QString library ) {
//   // make one in each gallery class
//   QStringList dimensions;
//   dimensions << "contrast"; //<< "time" ;
//   return dimensions;
// }

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
void qSlicerCIVM_GalleryControlModuleWidget::SetDisplayLayout(QString name){
  // make one in each gallery class
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildDisplayControls(QString protocol,QWidget panel){
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

