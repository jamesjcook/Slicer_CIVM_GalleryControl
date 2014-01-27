//vtkMRMLTagCategoryStorageNode
// hold a linked list of Category definitions. 
// categories are collections of strings which nodes could be tagged with using tagtables.

// Slicer Includes
#include "qSlicerApplication.h" // not found by default have to add dependency to cmake?


// MRML includes
#include <vtkMRMLTagCategoryStorageNode.h>

// VTK includes
#include <vtkMRMLNode.h>
#include <vtkCommand.h>
#include <vtkIntArray.h>
#include <vtkObjectFactory.h>
#include <vtkNew.h>
//#include <vtkMRMLStorageNode.h>
#include <vtkDirectory.h>

// STD includes
#include <cassert>
#include <limits>
#include <sstream>
#include <string> 


//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLTagCategoryStorageNode);
vtkMRMLTagCategoryStorageNode::vtkMRMLTagCategoryStorageNode(void)
{
  this->SetHideFromEditors(0);
  this->ObservedEvents = vtkIntArray::New();
  this->ObservedEvents->InsertNextValue(vtkCommand::StartEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::ModifiedEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::EndEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::StartInteractionEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::InteractionEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::EndInteractionEvent);
}
//----------------------------------------------------------------------------
vtkMRMLTagCategoryStorageNode::vtkMRMLTagCategoryStorageNode(std::string DataRoot)
{
  this->ObservedEvents = vtkIntArray::New();
  this->ObservedEvents->InsertNextValue(vtkCommand::StartEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::ModifiedEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::EndEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::StartInteractionEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::InteractionEvent);
  this->ObservedEvents->InsertNextValue(vtkCommand::EndInteractionEvent);
  
//   this->TagCategoryStorage = NULL;

//   vtkTagCategoryStorage *node  = vtkTagCategoryStorage::New();
//   vtkSetAndObserveMRMLObjectEventsMacro(
//     this->TagCategoryStorage, node, this->ObservedEvents);
//   node->Delete();

  // Observe the transfer functions
//   this->SetColor(node->GetRGBTransferFunction());
//   this->SetScalarOpacity(node->GetScalarOpacity());
//   this->SetGradientOpacity(node->GetGradientOpacity());

  this->BuildTagCategoryStorage(DataRoot);


  this->SetHideFromEditors(0);
}

//----------------------------------------------------------------------------
vtkMRMLTagCategoryStorageNode::~vtkMRMLTagCategoryStorageNode(void)
{
//   if(this->TagCategoryStorage)
//     {
//     vtkUnObserveMRMLObjectMacro(this->TagCategoryStorage->GetScalarOpacity());
//     vtkUnObserveMRMLObjectMacro(this->TagCategoryStorage->GetGradientOpacity());
//     vtkUnObserveMRMLObjectMacro(this->TagCategoryStorage->GetRGBTransferFunction());
//     vtkSetAndObserveMRMLObjectMacro(this->TagCategoryStorage, NULL);
//     }
//   this->ObservedEvents->Delete();
}


//----------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::BuildTagCategoryStorage(std::string DataPath) 
{
  // get directory listing, 
  //vtkGlobfileNames
//   vtkGlobfileNames* dir = vtkGlobfileNames::New();
//   dir->SetDirectory(DataPath.c_str());
//   dir->AddFilnames("*");
  vtkDirectory * dir = vtkDirectory::New();
  int goodPath = dir->Open(DataPath.c_str());
  if(goodPath) 
    { 
      for (int fn=0;fn<dir->GetNumberOfFiles() ; fn++) 
	{  // for entry in directyory 
	  const char * currentFile = dir->GetFile(fn);
	  if(!dir->FileIsDirectory(currentFile) ) 
	    {
	      // if not mrml, 
	      // if nii or nrrd
	      //   if imgname_tags exist  //check for image tags
	      //   load scene   // read image tags	      
// 	      qSlicerApplication * app = qSlicerApplication::application();
// 	      app->ioManager()->loadScene(DataPath+dir,false);  
	      // 
	      //   for each attribute of img check/add
	      //     check in CategoryNames, 
	    } 
	  else 
	    {
	      // if is dir 
	      //   BuildTagCategoryStorage(DatPath/dir)
	      this->BuildTagCategoryStorage(std::string(currentFile));
	    }

	}
    } 
  else 
    { 
      // dir failed.
    }
 
}

//----------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::WriteXML(ostream& of, int nIndent)
{
  // Write all attributes not equal to their defaults
  this->Superclass::WriteXML(of, nIndent);

  //vtkIndent indent(nIndent);
//   of << " interpolation=\"" <<this->TagCategoryStorage->GetInterpolationType()<< "\"";
//   of << " shade=\"" <<this->TagCategoryStorage->GetShade()<< "\"";
//   of << " diffuse=\"" <<this->TagCategoryStorage->GetDiffuse()<< "\"";
//   of << " ambient=\"" <<this->TagCategoryStorage->GetAmbient()<< "\"";
//   of << " specular=\"" <<this->TagCategoryStorage->GetSpecular()<< "\"";
//   of << " specularPower=\"" <<this->TagCategoryStorage->GetSpecularPower()<<"\"";
//   of << " scalarOpacity=\"" << this->GetPiecewiseFunctionString(this->TagCategoryStorage->GetScalarOpacity())  << "\"";
//   of << " gradientOpacity=\"" <<this->GetPiecewiseFunctionString(this->TagCategoryStorage->GetGradientOpacity())<< "\"";
//   of << " colorTransfer=\"" <<this->GetColorTransferFunctionString(this->TagCategoryStorage->GetRGBTransferFunction())<< "\"";

}

//----------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::ReadXMLAttributes(const char** atts)
{
  int disabledModify = this->StartModify();

  this->Superclass::ReadXMLAttributes(atts);

  const char* attName;
  const char* attValue;
  while (*atts!=NULL)
    {
    attName= *(atts++);
    attValue= *(atts++);
    if(!strcmp(attName,"scalarOpacity"))
      {
//       vtkPiecewiseFunction *scalarOpacity=vtkPiecewiseFunction::New();
//       this->GetPiecewiseFunctionFromString(attValue,scalarOpacity);
//       this->SetScalarOpacity(scalarOpacity);
//       scalarOpacity->Delete();
      }
    else if(!strcmp(attName,"gradientOpacity"))
      {
//       vtkPiecewiseFunction *gradientOpacity=vtkPiecewiseFunction::New();
//       this->GetPiecewiseFunctionFromString(attValue,gradientOpacity);
//       this->SetGradientOpacity(gradientOpacity);
//       gradientOpacity->Delete();
      }
    else if(!strcmp(attName,"colorTransfer"))
      {
//       vtkColorTransferFunction *colorTransfer=vtkColorTransferFunction::New();
//       this->GetColorTransferFunctionFromString(attValue,colorTransfer);
//       this->SetColor(colorTransfer);
//       colorTransfer->Delete();
      }
    else if(!strcmp(attName,"interpolation"))
      {
//       int interpolation;
//       std::stringstream ss;
//       ss <<attValue;
//       ss>>interpolation;
//       this->TagCategoryStorage->SetInterpolationType(interpolation);
      }
    else if(!strcmp(attName,"shade"))
      {
//       int shade;
//       std::stringstream ss;
//       ss <<attValue;
//       ss>>shade;
//       this->TagCategoryStorage->SetShade(shade);
      }
    else if(!strcmp(attName,"diffuse"))
      {
//       double diffuse;
//       std::stringstream ss;
//       ss<<attValue;
//       ss>>diffuse;
//       this->TagCategoryStorage->SetDiffuse(diffuse);
      }
    else if(!strcmp(attName,"ambient"))
      {
//       double ambient;
//       std::stringstream ss;
//       ss<<attValue;
//       ss>>ambient;
//       this->TagCategoryStorage->SetAmbient(ambient);
      }
    else if(!strcmp(attName,"specular"))
      {
//       double specular;
//       std::stringstream ss;
//       ss<<attValue;
//       ss>>specular;
//       this->TagCategoryStorage->SetSpecular(specular);
      }
    else if(!strcmp(attName,"specularPower"))
      {
//       int specularPower;
//       std::stringstream ss;
//       ss<<attValue;
//       ss>>specularPower;
//       this->TagCategoryStorage->SetSpecularPower(specularPower);
      }//else if
    }//while

  this->EndModify(disabledModify);
}

//----------------------------------------------------------------------------
// Copy the node's attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, ID
void vtkMRMLTagCategoryStorageNode::Copy(vtkMRMLNode *anode)
{
  int disabledModify = this->StartModify();

  this->Superclass::Copy(anode);

  this->CopyParameterSet(anode);
  
  this->EndModify(disabledModify);
}

//----------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::CopyParameterSet(vtkMRMLNode *anode)
{
  //cast
  vtkMRMLTagCategoryStorageNode *node = (vtkMRMLTagCategoryStorageNode *) anode;

//   this->TagCategoryStorage->SetIndependentComponents(
//     node->TagCategoryStorage->GetIndependentComponents());
//   this->TagCategoryStorage->SetInterpolationType(
//     node->TagCategoryStorage->GetInterpolationType());

//   //TagCategoryStorage
//   for (int i=0;i<VTK_MAX_VRCOMP;i++)
//     {
//     this->TagCategoryStorage->SetComponentWeight(
//       i,node->GetTagCategoryStorage()->GetComponentWeight(i));
//     //TODO problem no set method
//     // vtkPiecewiseFunction *gray=node->GetTagCategoryStorage()->GetGrayTransferFunction=());L
//     //   this->TagCategoryStorage->SetGry
//     //TODO problem no set ColorChannels Method
//     //this->TagCategoryStorage->SetCGetColorChannels(
//     //mapping functions
//     vtkColorTransferFunction *rgbTransfer=vtkColorTransferFunction::New();
//     rgbTransfer->DeepCopy(
//       node->GetTagCategoryStorage()->GetRGBTransferFunction(i));
//     this->SetColor(rgbTransfer, i);
//     rgbTransfer->Delete();

//     vtkPiecewiseFunction *scalar=vtkPiecewiseFunction::New();
//     scalar->DeepCopy(node->GetTagCategoryStorage()->GetScalarOpacity(i));
//     this->SetScalarOpacity(scalar, i);
//     scalar->Delete();
//     this->TagCategoryStorage->SetScalarOpacityUnitDistance(
//       i,this->TagCategoryStorage->GetScalarOpacityUnitDistance(i));

//     vtkPiecewiseFunction *gradient=vtkPiecewiseFunction::New();
//     gradient->DeepCopy(node->GetTagCategoryStorage()->GetGradientOpacity(i));
//     this->SetGradientOpacity(gradient, i);
//     gradient->Delete();

//     //TODO Copy default gradient?
//     this->TagCategoryStorage->SetDisableGradientOpacity(
//       i,node->GetTagCategoryStorage()->GetDisableGradientOpacity(i));
//     this->TagCategoryStorage->SetShade(i,node->GetTagCategoryStorage()->GetShade(i));
//     this->TagCategoryStorage->SetAmbient(i, node->TagCategoryStorage->GetAmbient(i));
//     this->TagCategoryStorage->SetDiffuse(i, node->TagCategoryStorage->GetDiffuse(i));
//     this->TagCategoryStorage->SetSpecular(i, node->TagCategoryStorage->GetSpecular(i));
//     this->TagCategoryStorage->SetSpecularPower(
//       i, node->TagCategoryStorage->GetSpecularPower(i));
//     }
}

//----------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
//   os<<indent<<"TagCategoryStorage: ";
//   this->TagCategoryStorage->PrintSelf(os,indent.GetNextIndent());
}

//---------------------------------------------------------------------------
void vtkMRMLTagCategoryStorageNode::ProcessMRMLEvents ( vtkObject *caller,
                                                    unsigned long event,
                                                    void *callData )
{
  this->Superclass::ProcessMRMLEvents(caller, event, callData);
  switch (event)
    {
    case vtkCommand::StartEvent:
    case vtkCommand::EndEvent:
    case vtkCommand::StartInteractionEvent:
    case vtkCommand::InteractionEvent:
    case vtkCommand::EndInteractionEvent:
      this->InvokeEvent(event);
      break;
    case vtkCommand::ModifiedEvent:
      this->Modified();
      break;
    }
}

//---------------------------------------------------------------------------
std::string vtkMRMLTagCategoryStorageNode
::DataToString(double* data, int size)
{
  std::stringstream resultStream;
  double *it = data;
  // Write header
  resultStream << size;
  resultStream.precision(std::numeric_limits<double>::digits10);
  for (int i=0; i < size; ++i)
    {
    resultStream << " ";
    resultStream << *it;
    it++;
    }
  return resultStream.str();
}

//---------------------------------------------------------------------------
int vtkMRMLTagCategoryStorageNode
::DataFromString(const std::string& dataString, double* &data)
{
  std::stringstream stream;
  stream << dataString;

  int size=0;
  stream >> size;
  if (size==0)
    {
    return 0;
    }
  data = new double[size];
  for(int i=0; i < size; ++i)
    {
    std::string s;
    stream >> s;
    data[i] = atof(s.c_str());
    }
  return size;
}

//---------------------------------------------------------------------------
int vtkMRMLTagCategoryStorageNode
::NodesFromString(const std::string& dataString, double* &nodes, int nodeSize)
{
  int size = vtkMRMLTagCategoryStorageNode::DataFromString(dataString, nodes);
  if (size % nodeSize)
    {
    std::cerr << "Error parsing data string" << std::endl;
    return 0;
    }
  // Ensure uniqueness
  double previous = VTK_DOUBLE_MIN;
  for (int i = 0; i < size; i+= nodeSize)
    {
//     nodes[i] = vtkMRMLTagCategoryStorageNode::HigherAndUnique(nodes[i], previous);
    }
  return size / nodeSize;
}

// //---------------------------------------------------------------------------
// std::string vtkMRMLTagCategoryStorageNode
// ::GetPiecewiseFunctionString(vtkPiecewiseFunction* function)
// {
//   return vtkMRMLTagCategoryStorageNode::DataToString(
//     function->GetDataPointer(), function->GetSize() * 2);
// }

// //---------------------------------------------------------------------------
// std::string vtkMRMLTagCategoryStorageNode
// ::GetColorTransferFunctionString(vtkColorTransferFunction* function)
// {
//   return vtkMRMLTagCategoryStorageNode::DataToString(
//     function->GetDataPointer(), function->GetSize() * 4);
// }

// //---------------------------------------------------------------------------
// void vtkMRMLTagCategoryStorageNode
// ::GetPiecewiseFunctionFromString(
//   const std::string& str,vtkPiecewiseFunction* result)
// {
//   double* data = 0;
//   int size = vtkMRMLTagCategoryStorageNode::NodesFromString(str, data, 2);
//   if (size)
//     {
//     result->FillFromDataPointer(size, data);
//     }
//   delete [] data;
// }

// //---------------------------------------------------------------------------
// void vtkMRMLTagCategoryStorageNode
// ::GetColorTransferFunctionFromString(
//   const std::string& str, vtkColorTransferFunction* result)
// {
//   double* data = 0;
//   int size = vtkMRMLTagCategoryStorageNode::NodesFromString(str, data, 4);
//   if (size)
//     {
//     result->FillFromDataPointer(size, data);
//     }
//   delete [] data;
// }

// //----------------------------------------------------------------------------
// double vtkMRMLTagCategoryStorageNode
// ::NextHigher(double value)
// {
//   if (value == 0.)
//     {
//     // special case to avoid denormalized numbers
//     return std::numeric_limits<double>::min();
//     }
//   // Increment the value by the smallest offset possible
//   // The challenge here is to find the offset, if the value is 100000000., an
//   // offset of espilon won't work.
//   typedef union {
//       long long i64;
//       double d64;
//     } dbl_64;
//   dbl_64 d;
//   d.d64 = value;
//   d.i64 += (value < 0.) ? -1 : 1;
//   return d.d64;
// }

// //----------------------------------------------------------------------------
// double vtkMRMLTagCategoryStorageNode
// ::HigherAndUnique(double value, double &previousValue)
// {
//   value = std::max(value, previousValue);
//   if (value == previousValue)
//     {
//     value = vtkMRMLTagCategoryStorageNode::NextHigher(value);
//     }
//   assert (value != previousValue);
//   previousValue = value;
//   return value;
// }


// //---------------------------------------------------------------------------
// vtkMRMLStorageNode* vtkMRMLTagCategoryStorageNode::CreateDefaultStorageNode()
// {
//   return vtkMRMLStorageNode::New();
// }

// //---------------------------------------------------------------------------
// void vtkMRMLTagCategoryStorageNode
// ::SetScalarOpacity(vtkPiecewiseFunction* newScalarOpacity, int component)
// {
//   vtkUnObserveMRMLObjectMacro(
//     this->TagCategoryStorage->GetScalarOpacity(component));

//   this->TagCategoryStorage->SetScalarOpacity(component, newScalarOpacity);

//   vtkObserveMRMLObjectEventsMacro(
//     this->TagCategoryStorage->GetScalarOpacity(component),
//     this->ObservedEvents);
// }

// //---------------------------------------------------------------------------
// vtkPiecewiseFunction* vtkMRMLTagCategoryStorageNode
// ::GetScalarOpacity(int component)
// {
//   return this->TagCategoryStorage->GetScalarOpacity(component);
// }

// //---------------------------------------------------------------------------
// void vtkMRMLTagCategoryStorageNode
// ::SetGradientOpacity(vtkPiecewiseFunction* newGradientOpacity, int component)
// {
//   vtkUnObserveMRMLObjectMacro(
//     this->TagCategoryStorage->GetGradientOpacity(component));

//   this->TagCategoryStorage->SetGradientOpacity(component, newGradientOpacity);

//   vtkObserveMRMLObjectEventsMacro(
//     this->TagCategoryStorage->GetGradientOpacity(component),
//     this->ObservedEvents);
// }

// //---------------------------------------------------------------------------
// vtkPiecewiseFunction* vtkMRMLTagCategoryStorageNode
// ::GetGradientOpacity(int component)
// {
//   return this->TagCategoryStorage->GetGradientOpacity(component);
// }

// //---------------------------------------------------------------------------
// void vtkMRMLTagCategoryStorageNode
// ::SetColor(vtkColorTransferFunction* newColorFunction, int component)
// {
//   vtkUnObserveMRMLObjectMacro(
//     this->TagCategoryStorage->GetRGBTransferFunction(component));

//   this->TagCategoryStorage->SetColor(component, newColorFunction);

//   vtkObserveMRMLObjectEventsMacro(
//     this->TagCategoryStorage->GetRGBTransferFunction(component),
//     this->ObservedEvents);
// }

// //---------------------------------------------------------------------------
// vtkColorTransferFunction* vtkMRMLTagCategoryStorageNode
// ::GetColor(int component)
// {
//   return this->TagCategoryStorage->GetRGBTransferFunction(component);
// }

//---------------------------------------------------------------------------
bool vtkMRMLTagCategoryStorageNode::GetModifiedSinceRead()
{
//   return this->Superclass::GetModifiedSinceRead() ||
//     (this->TagCategoryStorage &&
//      this->TagCategoryStorage->GetMTime() > this->GetStoredTime());


  return this->Superclass::GetModifiedSinceRead();//  ||
//     (this->TagCategoryStorage &&
//      this->TagCategoryStorage->GetMTime() > this->GetStoredTime());
}
