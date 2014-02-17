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


// Panel includes
#include "qSlicerCIVM_GalleryControlPanelPGRWidget.h"

// SlicerQt includes
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
  d->setupUi(this);
  this->Superclass::setup();
#ifdef WIN32 
  this->ps=('\\');
  this->DataRoot=QString("C:");
#else
  this->ps=('/');
  this->DataRoot=QString("");
#endif
  this->DataRoot=DataRoot+ps+"DataLibraries"+ps+"Brain"; //
  this->SetLibraries(DataRoot); // replacement for getlibraries which only gets the data paths
  QStringList libraries=this->GetLibraries(DataRoot);
  this->PrintText("Datapath="+DataRoot);
  // populate our dropdown
  // need to setCollapsed true on gallery selection and gallery control during init,
  //d->DocumentationArea->setCollapsed(false);
  d->GalleryArea->setCollapsed(true);
  d->ControlArea->setCollapsed(true);

  //d->LibrarySelectorDropList->insertItems(0,libraries);
  d->LibrarySelectorDropList->insertItems(0,this->DataLibraries.keys());
  d->LibrarySelectorDropList->setDefaultText("Select Data");
  d->LibrarySelectorDropList->setCurrentIndex(-1);

  //connect LibrarySelectDropList to BuildGallery
  connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(BuildGallery()));
  //connect(d->LibrarySelectorDropList,SIGNAL(currentIndexChanged(int)),SLOT(d->GalleryArea->setCollapsed(false)));
    //d->ComboBoxA->currentText();
}
//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::SetLibraries(QString dataRoot) {
  QStringList libs=GetLibraries(dataRoot,-1);
  this->PrintMethod("SetLibraries");
  for (int lnum=0;lnum<libs.size(); lnum=lnum+2)
    {
      this->PrintText(libs.at(lnum)+" <="+libs.at(lnum+1));
      DataLibraries[libs.at(lnum)].setFile(libs.at(lnum+1));
    }
  return;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibraries(QString dataRoot) {
  // called on module start to populate our list of libraries.
  int maxDepth=1;
  QStringList libraries=GetLibraries(dataRoot,maxDepth);
  return libraries;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibraries(QString dataRoot,int maxDepth) {
  // get library locations starting at dataroot, this should return a listing of all relevent libraries we could look.
  // That list should include the leaf libraries, the maxDepth integer is a limiter for how deep we will traverse
  // the real work is not done yet in this function, we just return one library for now. 
  QStringList libraries;
  
  // get directory listing at dataRoot including all subdirs, add each (sorted somehow) to libraries list and return
  // rat times
  //   00000172800 00000345600 00000691200 00001036800 00001555200 00002073600 00003456000 00006912000
  QStringList rat_times;
  rat_times << "00000172800" << "00000345600" << "00000691200" << "00001036800" << "00001555200" << "00002073600" << "00003456000" << "00006912000";
  QString rat_adult_time=rat_times.last();
  QString rat_first_time=rat_times.first();
  //rat_adult_time="00000172800";//rat day 04 for testing.
  QString max_mamal_time="12623040000";
  QString human_adult_time = max_mamal_time;//max mamal for unknown adult age
  QString rat_spec = "average";
  QString mouse_spec = "DTI";
  QString human_spec = "130827-2-0";
  QString dog_spec = "AdultCanisL";
  QString monkey_spec="AdultMacacaM";
  QString monkey_spec2="AdultMacacaF";
  //  QStringList speciesList;
  //  speciesList << "Rat:Wistar" << "Human" << "Rhesus_macaque" << "Mouse" ;
//   for (int snum=0;snum<speciesList.size(); snum++)
//     {
// //libraries << "Brain:Rat:Wistar:Average_SPECCODE:00006912000";    
//       libraries << speciesList[snum];
//     }
  if ( maxDepth < 0 )  { libraries << "Rattus_norvegicus:Wistar:Adult" ; }
  libraries << "Rattus_norvegicus:Wistar:"+rat_spec+":"+rat_adult_time ;
  if ( maxDepth < 0 )  { libraries << "Rattus_norvegicus:Wistar:Juvenile"; }
  libraries << "Rattus_norvegicus:Wistar:"+rat_spec+":"+rat_first_time ;
  if ( maxDepth < 0 )  { libraries << "Human:Adult"; }
  //libraries << "Human:"+human_spec+":"+human_adult_time;
  libraries << "Human:"+human_spec;//+":"+human_adult_time;
  if ( maxDepth < 0 )  { libraries << "Mus_Musculus:Adult"; }
  //libraries << "Mus_Musculus:"+mouse_spec+":"+max_mamal_time;
  libraries << "Mus_Musculus:whs_atlas:"+mouse_spec;//+":"+max_mamal_time;
  if ( maxDepth < 0 )  { libraries << "Canis_Lupis"; }
  //libraries << "Canis_lupis:"+dog_spec+":"+max_mamal_time;
  //libraries << "Canis_lupis:"+dog_spec;//+":"+max_mamal_time;
  if ( maxDepth < 0 )  { libraries << "Macaca_mulatta"; }
  //libraries << "Macaca_mulatta:"+monkey_spec+":"+max_mamal_time;
  libraries << "Macaca_mulatta:"+monkey_spec;//+":"+max_mamal_time;
  if ( maxDepth < 0 )  { libraries << "Macaca_fasciularis"; }
  //libraries << "Macaca_fascicularis:"+monkey_spec2+":"+max_mamal_time;
  //libraries << "Macaca_fascicularis:"+monkey_spec2;//+":"+max_mamal_time;
  return libraries;
}

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModuleWidget::GetLibrary() {
  // called BuildGallery to get the name of the library from the index'd drop down.
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);
  //d->ComboBoxA->currentText();
  
  QString libraryName; //="Rat:Wistar";
  libraryName=d->LibrarySelectorDropList->currentText();
  QString library=this->DataLibraries[libraryName].filePath();
  this->PrintText("GetLibrary"+library+"\n");
  return library;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery () {
  QString library=this->GetLibrary();
  this->BuildGallery(library);
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildGallery (QString library) {
  // polls our data storage for the display protocols for a given library
  // this should be fired by any change to the library, eg connected to the drop down list of libraries.
  // insert a button into our gallery zone for each return value from GetDisplayProtocols
  Q_D(qSlicerCIVM_GalleryControlModuleWidget);

  ////
  // clear layout
  // d->GalleryLayout->delete
  this->clearLayout(d->GalleryLayout,true);
  this->clearLayout(d->ControlLayout,true);
  QStringList protocols = this->GetDisplayProtocols ();
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
      QString lP=library;
      //QString lN=library;
      lP.replace(':',ps);
      this->LibRoot=this->DataRoot+ps+lP;
      QString iconPath=this->LibRoot;
      //lN.replace(':','_');
      //iconPath=iconPath+ps+"GalleryIcons"+ps+library+'_'+protocols[i]+".png"; //+ps+"GalleryIcons"
      iconPath=DataRoot+ps+"GalleryIcons"+ps+library+'_'+protocols[i]+".png"; //+ps+"GalleryIcons"
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
      qSlicerCIVM_GalleryControlPanelPGRWidget * panel = new qSlicerCIVM_GalleryControlPanelPGRWidget(this,this->LibRoot); //Ui_
      //QSlicerModuleWidget
      d->ControlLayout->addWidget(panel);
    } 
  else
    {
    }
  d->ControlArea->setCollapsed(false); 
  d->GalleryArea->setCollapsed(true);
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::clearLayout(QLayout* layout, bool deleteWidgets = true)
{
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
  QStringList protocols;
  //get libdims? 
  //select layouts supporting up to number of libdims?
  //select layouts supporting each combination of libdims?
  protocols << "PGR" << "FA_Render" ;
  return protocols;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetLibDims(QString library ) 
{
  QStringList dimensions;
  dimensions << "contrast"; //<< "time" ;
  return dimensions;
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModuleWidget::GetDimEntries(QString library,QString dimension) 
{
  QStringList dimValues;
  // if dimension== contrast
  // if dimension== time
  dimValues << "adc" << "b0" << "dwi" << "fa" << "fa_color" << "freq" << "gre" << "rd"; 
  return dimValues;
}


//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::SetDisplayLayout(QString name){
  
  return;
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModuleWidget::BuildDisplayControls(QString protocol,QWidget panel){

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

