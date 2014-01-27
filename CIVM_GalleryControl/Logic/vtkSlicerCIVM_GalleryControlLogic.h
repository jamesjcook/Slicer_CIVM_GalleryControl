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

// .NAME vtkSlicerCIVM_GalleryControlLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerCIVM_GalleryControlLogic_h
#define __vtkSlicerCIVM_GalleryControlLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes

// STD includes
#include <cstdlib>

#include "vtkSlicerCIVM_GalleryControlModuleLogicExport.h"


/// \ingroup Slicer_QtModules_ExtensionTemplate
class VTK_SLICER_CIVM_GALLERYCONTROL_MODULE_LOGIC_EXPORT vtkSlicerCIVM_GalleryControlLogic :
public vtkSlicerModuleLogic
{
public:

  static vtkSlicerCIVM_GalleryControlLogic *New();
  vtkTypeMacro(vtkSlicerCIVM_GalleryControlLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);
  //put some data container here for library data. just one i think, we'll presume only one libraray is looked at at a time if libraries cross that should be determined by their disk layout, allowing libraries to be sub collecitons via using the data root 
  
protected:
  vtkSlicerCIVM_GalleryControlLogic();
  virtual ~vtkSlicerCIVM_GalleryControlLogic();
  
  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
private:

  vtkSlicerCIVM_GalleryControlLogic(const vtkSlicerCIVM_GalleryControlLogic&); // Not implemented
  void operator=(const vtkSlicerCIVM_GalleryControlLogic&);               // Not implemented
};

#endif
