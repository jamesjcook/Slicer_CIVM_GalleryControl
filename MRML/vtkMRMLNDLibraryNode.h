//vtkMRMLNDLibrarayNode
// node to hold onto information related to alibrary of data.
// we will start basically with hardcoded libraries at first then expand the class to use a database


#ifndef __vtkMRMLNDLibraryNode_h



// MRML includes
#include "vtkMRML.h"
#include "vtkMRMLStorableNode.h"

// StdIncludes
#include <string>



//VTK_SLICER_VOLUMERENDERING_MODULE_MRML_EXPORT
class VTK_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLStorableNode
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
 public:
/// Create a new vtkMRMLNDLibraryNode
  //static vtkMRMLNDLibraryNode *New();
  //typedef vtkMRMLStorableNode Superclass;//instead usetype macro
  vtkTypeMacro(vtkMRMLNDLibraryNode,vtkMRMLStorableNode);
  //void PrintSelf(ostream& os, vtkIndent indent);
  
  void SetSlicerDataType ( const char *type) ;
  vtkSetMacro(DataRoot,std::string);    
  vtkMRMLNode* CreateNodeInstance() ;
  
  /// Get node XML tag name (like Volume, Model)
  //virtual const char* GetNodeTagName() {return "NDLibraryNode";};

  
 protected:
  //name
  //path
  vtkMRMLNDLibraryNode(void);
  //vtkMRMLNDLibraryNode(std::string);
  ~vtkMRMLNDLibraryNode(void);
  
  std::string DataRoot; // base path for the library
  //dimensionss a list.
  //..
  // valuemap...?
  //   for each dimesnsion(by name) a list of entries. 
  
 private:
  
  //vtkMRMLNDLibraryNode(const vtkMRMLNDLibraryNode&);//Not implemented
  
};

#endif
