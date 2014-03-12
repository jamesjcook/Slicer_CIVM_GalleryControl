//vtkMRMLNDLibraryNode
// node to hold onto information related to alibrary of data.
// we will start basically with hardcoded libraries at first then expand the class to use a database

#include <vtkMRMLNode.h>
#include <vtkObjectFactory.h>
#include  <vtkNew.h>
#include <vtkMRMLVolumeNode.h>
#include <vtkSmartPointer.h>
#include <vtkMRMLNDLibraryNode.h>




//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(void)
{
  //this->DataRoot="";
//   cout << "Library Node instantiated";
  this->SlicerDataType="";//.clear();
  this->SetLibRoot("/");
}

//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
 vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(std::string path)
 {
//   //  this->SetLibRoot("/DataLibraries");
//   //
   this->SetLibRoot(path);//"/DataLibraries";

 }

//----------------------------------------------------------------------------
vtkMRMLNDLibraryNode::~vtkMRMLNDLibraryNode(void)
{
  // this->SlicerDataType.clear();
}

void vtkMRMLNDLibraryNode::SetSlicerDataType( const char * type ) 
{ 
  this->SlicerDataType.clear();
  this->SlicerDataType = type;
}
//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << indent << "NDLibraryNode (Printself)\n";
  os << indent << "LibRoot:" << this->GetLibRoot() << "\n";

  return;
}

vtkMRMLNode*  vtkMRMLNDLibraryNode::CreateNodeInstance(void)
{
  vtkSmartPointer<vtkMRMLNode> sp ;
  return sp;
}
//  {
//    vtkMRMLVolumeNode* np=new vtkMRMLVolumeNode();
//   return np;
//  }
