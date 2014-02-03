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

// FooBar Widgets includes
#include "qSlicerCIVM_GalleryControlFooBarWidget.h"
#include "ui_qSlicerCIVM_GalleryControlFooBarWidget.h"

// FooBar modification
#include <QDebug>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_CIVM_GalleryControl
class qSlicerCIVM_GalleryControlFooBarWidgetPrivate
  : public Ui_qSlicerCIVM_GalleryControlFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerCIVM_GalleryControlFooBarWidget);
protected:
  qSlicerCIVM_GalleryControlFooBarWidget* const q_ptr;

public:
  qSlicerCIVM_GalleryControlFooBarWidgetPrivate(
    qSlicerCIVM_GalleryControlFooBarWidget& object);
  virtual void setupUi(qSlicerCIVM_GalleryControlFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerCIVM_GalleryControlFooBarWidgetPrivate
::qSlicerCIVM_GalleryControlFooBarWidgetPrivate(
  qSlicerCIVM_GalleryControlFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlFooBarWidgetPrivate
::setupUi(qSlicerCIVM_GalleryControlFooBarWidget* widget)
{
  this->Ui_qSlicerCIVM_GalleryControlFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlFooBarWidget
::qSlicerCIVM_GalleryControlFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerCIVM_GalleryControlFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerCIVM_GalleryControlFooBarWidget);
  d->setupUi(this);

  connect(d->FooBarButton,SIGNAL(clicked()),SLOT(ButtonTest()));
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlFooBarWidget
::~qSlicerCIVM_GalleryControlFooBarWidget()
{
}

void qSlicerCIVM_GalleryControlFooBarWidget
::ButtonTest()
{
//Q_D(
  QTextStream out(stdout);
  out << "button test"<<"\n";  
  return;
}
