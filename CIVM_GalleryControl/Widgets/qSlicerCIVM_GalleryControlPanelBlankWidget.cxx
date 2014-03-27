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

// PanelBlank Widgets includes
#include "qSlicerCIVM_GalleryControlPanelBlankWidget.h"
#include "ui_qSlicerCIVM_GalleryControlPanelBlankWidget.h"

// PanelBlank modification
#include <QDebug>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_CIVM_GalleryControl
class qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate
  : public Ui_qSlicerCIVM_GalleryControlPanelBlankWidget
{
  Q_DECLARE_PUBLIC(qSlicerCIVM_GalleryControlPanelBlankWidget);
protected:
  qSlicerCIVM_GalleryControlPanelBlankWidget* const q_ptr;

public:
  qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate(
    qSlicerCIVM_GalleryControlPanelBlankWidget& object);
  virtual void setupUi(qSlicerCIVM_GalleryControlPanelBlankWidget*);
};

// --------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate
::qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate(
  qSlicerCIVM_GalleryControlPanelBlankWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate
::setupUi(qSlicerCIVM_GalleryControlPanelBlankWidget* widget)
{
  this->Ui_qSlicerCIVM_GalleryControlPanelBlankWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlPanelBlankWidget methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelBlankWidget
::qSlicerCIVM_GalleryControlPanelBlankWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerCIVM_GalleryControlPanelBlankWidgetPrivate(*this) )
{
  Q_D(qSlicerCIVM_GalleryControlPanelBlankWidget);
  d->setupUi(this);

  //connect(d->PanelBlankButton,SIGNAL(clicked()),SLOT(ButtonTest()));
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlPanelBlankWidget
::~qSlicerCIVM_GalleryControlPanelBlankWidget()
{
}

// void qSlicerCIVM_GalleryControlPanelBlankWidget
// ::ButtonTest()
// {
// //Q_D(
//   QTextStream out(stdout);
//   out << "button test"<<"\n";  
//   return;
// }
