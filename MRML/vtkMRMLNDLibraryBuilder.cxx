// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibraryBuilder
// node to hold onto information related to alibrary of data.
// we will start basically with hardcoded libraries at first then expand the class to use a database

#include <vtkMRMLNode.h>
#include <vtkObjectFactory.h>
#include <vtkNew.h>
#include <vtkMRMLVolumeNode.h>
#include <vtkSmartPointer.h>
#include <vtkMRMLNDLibraryBuilder.h>

typedef std::map<std::string,std::string> std_str_hash ;


// standard includes, most were added for our dir listing command.
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryBuilder);
vtkMRMLNDLibraryBuilder::vtkMRMLNDLibraryBuilder(void)
{
//   this->DataRoot="";
//   cout << "Library Node instantiated";
//   this->SlicerDataType="";//.clear();
//   this->SetLibRoot("/");
}

//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryBuilder);
// vtkMRMLNDLibraryBuilder::vtkMRMLNDLibraryBuilder(vtkMRMLNDLibraryNode * lib)
// {
//   //this->DataRoot="";
// //   cout << "Library Node instantiated";
//   //this->SlicerDataType="";//.clear();
//   //this->SetLibRoot("/");
//   LibPointer = lib;
// }

//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryBuilder);
 vtkMRMLNDLibraryBuilder::vtkMRMLNDLibraryBuilder(std::string path)
 {
//   //  this->SetLibRoot("/DataLibraries");
//   //
   //this->SetLibRoot(path);//"/DataLibraries";

 }

//----------------------------------------------------------------------------
vtkMRMLNDLibraryBuilder::~vtkMRMLNDLibraryBuilder(void)
{
  // this->SlicerDataType.clear();
}

void vtkMRMLNDLibraryBuilder::SetSlicerDataType( const char * type ) 
{ 
  this->SlicerDataType.clear();
  this->SlicerDataType = type;
}
//----------------------------------------------------------------------------
void vtkMRMLNDLibraryBuilder::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << indent << "NDLibraryBuilder (Printself)\n";
  //os << indent << "LibRoot:" << this->GetLibRoot() << "\n";

  return;
}

vtkMRMLNode*  vtkMRMLNDLibraryBuilder::CreateNodeInstance(void)
{
  vtkSmartPointer<vtkMRMLNode> sp ;
  return sp;
}
//  {
//    vtkMRMLVolumeNode* np=new vtkMRMLVolumeNode();
//   return np;
//  }

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(std_str_hash tagCloud)
{
  this->Build(LibPointer,tagCloud);
  return true; 
}


//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(std::string path)
{
  this->Build(LibPointer,path);
  return true; 
}



//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std_str_hash)
{
  //this->Build(LibPointer,path);
  return true; 
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib)
{
  //lib->GatherSubLibs();
  std::vector<std::string> * pathList = new std::vector<std::string>;
  this->GetSubDirs(pathList,lib->GetLibRoot());
  bool status=false;
  
  bool singleEntryOptimization=false;
  // this optimizatoin removed for now, it will be harder to follow this through in the future.
  
  if( pathList->size() == 1 && singleEntryOptimization) // if singular path remove it and descend one more.
    {
    this->GetSubDirs(pathList,pathList->at(0));
    pathList->erase(pathList->begin());
    }
  
  if( pathList->size() != lib->SubLibraries.size() ) 
    {
    lib->SubLibraries.clear();
//     {
//     for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= lib->SubLibraries.begin(); subIter!=lib->SubLibraries.end();++subIter)
//         {
//         vtkMRMLNDLibraryNode * subLib =  subIter->second();
//         delete subLib;

//         }
    for ( int i=0; i< pathList->size(); i++ ) 
      {
      std::cout << "Cout: Build libpointer(constructor call with path)" << pathList->at(i)<< "\n";    
      vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(pathList->at(i));
      // build sublib from path, should create sublib with name and path set.
      // limited sub gathering for now
      subLib->SetParentNode(lib);
//       if ( 
//         ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus") 
//          || ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus/Wistar" ) 
//          || ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus/Wistar/average" ) )
//         {
	
//         }  
      lib->SubLibraries[subLib->GetLibName()]=subLib; 
      }
    
    if ( pathList->size()>=1 )
      {
      status=true;
      delete pathList;//no need to delete a 0 length path list so we dont always delete?
      }
    else 
      { 
      std::cout << "Cout: pathList empty.\n";
      }
    } 
  
  return status; 
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib,  std::string name,std::string path)
{
  bool status = this->Build(lib,name,std::string("NoCategory"),path);
  return status;
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std::string name,std::string category,std::string path)
{
  lib->SetLibName(name);
  lib->SetCategory(category);
  lib->SetLibRoot(path); 
  bool status = this->Build(lib);
  return status;
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std::string path)
{
  bool status = this->Build(lib,std::string("NoName"),path);
  return status;
}

//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubCategoryies(std::vector<std::string > * path_vec, std::string dir_name) 
{ // get sub fields for a given nd library. This is hard problem since our cloud of data can have a very variable associateion. 
  
}


//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubDirs(std::vector<std::string > * path_vec, std::string dir_name) 
{

  //unix way.
  DIR * d_h;
  // Open the current directory. 
  d_h = opendir (dir_name.c_str());
   if (! d_h) 
     {
     std::cout << "Cout:Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno) << "\n";
     return;
     }
   while (1) 
     {
     struct dirent * entry;
     
     entry = readdir (d_h);
     if (! entry) 
       {
       break;
       } 
     else 
       { 
       // if is dir, get entry.
       if ( entry->d_type == 4 )
         //d_type==4
         {
         
         //for entry in ignore list, if ! match ignore list, add, else skip
         
         if ( entry->d_name[0] != '.' && entry->d_name[0] != '_' ) //&& entry->d_name[0] != '0') 
           {
           std::cout << "cout: diradd"<< dir_name.c_str() << "/" << entry->d_name<< "\n";
           path_vec->push_back(dir_name+"/"+entry->d_name);
           }
         else 
           {
           std::cout << "cout: ignore"<< dir_name.c_str() << "/" << entry->d_name<< "\n";
           }


         }
       }
     }
   // Close the directory. 
   if (closedir (d_h)) 
     {
     return;
     std::cout<< "Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno);
     }
   
   
   return ;
}
