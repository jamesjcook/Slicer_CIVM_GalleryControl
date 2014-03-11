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
#include <QtPlugin>

// CIVM_GalleryControl Logic includes
#include <vtkSlicerCIVM_GalleryControlLogic.h>

// CIVM_GalleryControl includes
#include "qSlicerCIVM_GalleryControlModule.h"
#include "qSlicerCIVM_GalleryControlModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerCIVM_GalleryControlModule, qSlicerCIVM_GalleryControlModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerCIVM_GalleryControlModulePrivate
{
public:
  qSlicerCIVM_GalleryControlModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModulePrivate
::qSlicerCIVM_GalleryControlModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerCIVM_GalleryControlModule methods

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModule
::qSlicerCIVM_GalleryControlModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerCIVM_GalleryControlModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerCIVM_GalleryControlModule::~qSlicerCIVM_GalleryControlModule()
{
  //destructoR
}

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModule::helpText()const
{
  return "This is a loadable module bundled in an extension. ";
}

//-----------------------------------------------------------------------------
QString qSlicerCIVM_GalleryControlModule::acknowledgementText()const
{
  return "This work was was partially funded by NIH grants";// 3P41RR013218-12S1";
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("James Cook (CIVM)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerCIVM_GalleryControlModule::icon()const
{
  return QIcon(":/Icons/CIVM_GalleryControl.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModule::categories() const
{
  return QStringList() << "Work in Progress";
}

//-----------------------------------------------------------------------------
QStringList qSlicerCIVM_GalleryControlModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerCIVM_GalleryControlModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerCIVM_GalleryControlModule
::createWidgetRepresentation()
{
  return new qSlicerCIVM_GalleryControlModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerCIVM_GalleryControlModule::createLogic()
{
  return vtkSlicerCIVM_GalleryControlLogic::New();
}
