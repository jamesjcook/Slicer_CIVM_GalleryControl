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
  

  //  connect(d->PanelDataSelectorButton,SIGNAL(clicked()),SLOT(ButtonTest()));
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelDataSelectorWidget
::~qSlicerCIVM_GalleryControlPanelDataSelectorWidget()
{
}

// void qSlicerCIVM_GalleryControlPanelDataSelectorWidget
// ::ButtonTest()
// {
// //Q_D(
//   QTextStream out(stdout);
//   out << "button test"<<"\n";  
//   return;
// }
