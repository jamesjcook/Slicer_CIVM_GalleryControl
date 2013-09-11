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
}

