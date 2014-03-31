// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibraryNode
// node to hold onto information related to alibrary of data.
// we will start basically with hardcoded libraries at first then expand the class to use a database

#include <vtkMRMLNode.h>
#include <vtkObjectFactory.h>
#include <vtkNew.h>
#include <vtkMRMLVolumeNode.h>
#include <vtkSmartPointer.h>
#include <vtkMRMLNDLibraryNode.h>


// standard includes, most were added for our dir listing command.
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
//#include <dirent.h>
#include <string.h>
//#include <errno.h>




//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
// placeholder constructor, just creates itself and gives fills fields with bad info(error check vars)
vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(void)
{
  //this->DataRoot="";
  //   cout << "Library Node instantiated";
  //this->SlicerDataType="";//.clear();
  //this->SetLibRoot("/");
  LibRoot = "NoPath";
  Category= "NoCategory";
  LibName = "NoName";
  CurrentSelection = 0 ;
  ParentNode = 0 ;
  //this->SubLibraries["Parent"]=this;
}


//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode( std::string name,std::string path)
{
  LibRoot = path;
  Category= "NoCategory";
  //ResetLibrary(path);! cant do that...
  LibName = name;
  CurrentSelection = 0 ;
  ParentNode = 0 ;
}

//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode( std::string name,std::string category,std::string path)
{
  LibRoot = path;
  Category= category;
  //ResetLibrary(path);! cant do that...
  LibName = name;
  CurrentSelection = 0 ;
  ParentNode = 0 ;
}

//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLNDLibraryNode);
vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(std::string path)
{
  //   //  this->SetLibRoot("/DataLibraries");
  //   //
  LibRoot=path;//"/DataLibraries";
  //this->BuildLibrary();
  if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/average/00006912000" ) 
    {
      Category="time";
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar/average" ) 
    {
      Category="specimen"; 
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar" ) 
    {
      Category="Strain";  
    }
  else if ( LibRoot != "/DataLibraries/Brain")
    {
      Category="Species";
    } else {
    Category="organ";
  }
  char delim='/';
  std::vector<std::string> libPathParts=this->split(LibRoot,delim);
  //  LibName=libPathParts[libPathParts.size()-1];
  LibName=libPathParts.back();// this should be modified to give a better name.
  // read tag data from some where?
  // set name some way...
  // set sublibs
  CurrentSelection = 0 ;
  ParentNode = 0 ;
}

//----------------------------------------------------------------------------
vtkMRMLNode*  vtkMRMLNDLibraryNode::CreateNodeInstance(void)
{
  vtkSmartPointer<vtkMRMLNode> sp ;
  return sp;
}
//  {
//    vtkMRMLVolumeNode* np=new vtkMRMLVolumeNode();
//   return np;
//  }

//----------------------------------------------------------------------------
std::vector<std::string> * vtkMRMLNDLibraryNode::GetAllPaths() 
{
  std::vector<std::string> * pathList = new std::vector<std::string>;
  //pathList->reserve(SubLibraries->size());# nice idea but doesnt work...
  pathList->push_back(LibRoot);
//   for ( int i=0; i< SubLibraries->size(); i++ )
//     {
//       SubLibraries->at(i)->GetAllPaths(pathList);
//     }

  for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= SubLibraries.begin(); subIter!=SubLibraries.end();++subIter)
    {
      //subIter->second->PrintSelf(os,indent.GetNextIndent());
      subIter->second->GetAllPaths(pathList);
    }
  
  //std::pair<std::string, vtkMRMLNDLibraryNode *> l_p=SubLibraries[i];
  //vtkMRMLNDLibraryNode * l_p=SubLibraries[].second();
  //SubLibraries[i].second().GetAllPaths(pathList);
  return pathList;
}

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::GetAllPaths(std::vector<std::string> * pathList) 
{
  //std::vector<std::string> * pathList = new std::vector<std::string>;
  pathList->push_back(LibRoot);  
//   for ( int i=0; i< SubLibraries->size(); i++ )
//     {
//       SubLibraries->at(i)->GetAllPaths(pathList);
//     }
  for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= SubLibraries.begin(); subIter!=SubLibraries.end();++subIter)
    {
      //subIter->second->PrintSelf(os,indent.GetNextIndent());
      subIter->second->GetAllPaths(pathList);
    }    
  return ;
}


//----------------------------------------------------------------------------
std::map<std::string,vtkMRMLNDLibraryNode *> vtkMRMLNDLibraryNode::GetSubLibraries(void)
{
  return SubLibraries;
}

//----------------------------------------------------------------------------
std::vector<std::map<std::string,std::string> > * vtkMRMLNDLibraryNode::GetLibTree() 
{
  std::vector<std::map<std::string,std::string> > * libTree = new std::vector<std::map<std::string,std::string> > ; 


  return libTree;
}

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::GatherSubLibs()
{
  // set sublibs
  std::vector<std::string> * libRoots = this->SubPaths();  
  //if ( 0 ) { 
  //if ( libRoots!=NULL ) {
  for ( int i=0; i< libRoots->size(); i++ ) 
    {

      vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode::vtkMRMLNDLibraryNode(libRoots->at(i));
      //SubLibraries->push_back(subLib);
      // limited sub gathering for now
      if ( 
	  ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus") 
	  || ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus/Wistar" ) 
	  || ( subLib->GetLibRoot() == "/DataLibraries/Brain/Rattus_norvegicus/Wistar/average" ) )
	{

	}  
      //subLib->GatherSubLibs();
      SubLibraries[subLib->GetLibName()]=subLib; 
      
      
    }
  //}
  return;
}



//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::ResetLibrary(void)
{
  ResetLibrary(this->LibRoot);
  return;
}

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::ResetLibrary(std::string path)
{
  LibRoot=path;//"/DataLibraries";
  //this->BuildLibrary();
  if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/average/00006912000" ) 
    {
      Category="time";
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar/average" ) 
    {
      Category="specimen"; 
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar" ) 
    {
      Category="Strain";  
    }
  else if ( LibRoot != "/DataLibraries/Brain")
    {
      Category="Species";
    } else {
    Category="organ";
  }
  char delim='/';
  std::vector<std::string> libPathParts=this->split(LibRoot,delim);
  //  LibName=libPathParts[libPathParts.size()-1];
  LibName=libPathParts.back();// this should be modified to give a better name.
  SubLibraries.clear();
  //SubLibraries = new std::map<std::string,vtkMRMLNDLibraryNode *>;

  // read tag data from some where?
  
  // set name some way...
  // set sublibs
return; 
}


void vtkMRMLNDLibraryNode::SetSlicerDataType( const char * type ) 
{ 
  this->SlicerDataType.clear();
  this->SlicerDataType = type;
}

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryNode::PrintSelf(ostream& os, vtkIndent indent)
{
  //Superclass::PrintSelf(os, indent);// i really dont care about that fornow. 
  os << indent << "NDLibraryNode (" << LibName << ") <-";
  os << "Category:" << Category << "\n";
  os << indent.GetNextIndent() << "->LibRoot:" << LibRoot << "\n";
  
  if ( SubLibraries.size()>0 ) 
  //if ( 0 ) 
    {
//   for ( int i=0; i< SubLibraries->size(); i++ )
//     {
//       //subLib = vtkMRMLNDLibrarynode(*it);
//       //subLib = subLib;
//       //os << indent.GetNextIndent() << "SubLibraryPrint: " << i << "\n" ;
//       SubLibraries[i]->PrintSelf(os,indent.GetNextIndent());
//     }
      for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= SubLibraries.begin(); subIter!=SubLibraries.end();++subIter)
	{
	  //SubLibraries[]
	  subIter->second->PrintSelf(os,indent.GetNextIndent());
	}
    } else { 
  os << indent << "Leaf Node Sub" << "\n";
  }

  return;
}

//----------------------------------------------------------------------------
std::vector<std::string> * vtkMRMLNDLibraryNode::SubPaths()
{
  std::vector<std::string> * pathList = new std::vector<std::string>;
  //may want to convert this to 
  //    a pointer to a vector of pointers to strings instead of
  //    a pointer to a vector of strings
  int const_paths=false;
  // get vector of dirs in LibRoot
  // for each dir which has a lib.conf inside it add to the path list
  // lib.conf handling not implimented yet.
  
  // hack to stop recursion while our paths are hard coded;

  if ( const_paths ) { 
  if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar/average" ) 
    {
      pathList->push_back(LibRoot + "/00006912000");
      return pathList;
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus/Wistar" ) 
    {
      pathList->push_back(LibRoot + "/average");    
      return pathList;
    }
  else if ( LibRoot == "/DataLibraries/Brain/Rattus_norvegicus" ) 
    {
      pathList->push_back(LibRoot + "/Wistar");    
      return pathList;
    }
  else if ( LibRoot == "/DataLibraries/Brain")
    {
      //pathList=NULL;

  //this->PrintSelf(std::cout,vtkIndent::vtkIndent(0));
  pathList->push_back(LibRoot + "/0_species");
  pathList->push_back(LibRoot + "/Canis_lupus");
  pathList->push_back(LibRoot + "/Human");
  pathList->push_back(LibRoot + "/Macaca_fascicularis");
  pathList->push_back(LibRoot + "/Macaca_mulatta");
  pathList->push_back(LibRoot + "/Mus_Musculus");
  pathList->push_back(LibRoot + "/Rattus_norvegicus");
  
    } else
    {
      return pathList;
    }  
  } else {
    //GetFilesInDirectory(*pathList,LibRoot);
//     GetSubDirs(pathList,LibRoot);
    
//     if( pathList->size() == 1 )
//       {
// 	GetSubDirs(pathList,pathList->at(0));
// 	pathList->erase(pathList->begin());
//       }
  }


  // for each entry of pathlist, check if valid.
  

  return pathList;
}

//----------------------------------------------------------------------------
// split function code >90% copy pasta from website(in comments). user was Evan Teran
// http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
//std::vector<std::string> &vtkMRMLNDLibraryNode::split(const std::string &s, char delim, std::vector<std::string> &elems);
//std::vector<std::string> vtkMRMLNDLibraryNode::split(const std::string &s, char delim);

std::vector<std::string> & vtkMRMLNDLibraryNode::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
  elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> vtkMRMLNDLibraryNode::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

// //----------------------------------------------------------------------------
// // GetSubDirs based on heavilty modified code at website. 
// // http://www.lemoda.net/c/list-directory/ld.c
// void  vtkMRMLNDLibraryNode::GetSubDirs(std::vector<std::string > * path_vec, std::string dir_name) 
// {

//   //unix way.
//   DIR * d_h;
//   // Open the current directory. 
//   d_h = opendir (dir_name.c_str());
//    if (! d_h) {
// //     //this->PrintSelf(std::cout,vtkIndent::vtkIndent(0));
// //     fprintf (std::err, "Cannot open directory '%s': %s\n",
// // 	     dir_name.c_str(), strerror (errno));
// //     exit (EXIT_FAILURE);
//      std::cout << "Cout:Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno) << "\n";
//      //     std::cerr << "Cerr:Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno)<< "\n";

//      return;
//    }
//   while (1) {
//     struct dirent * entry;

//     entry = readdir (d_h);
//     if (! entry) 
//       {
// 	break;
//       } 
//     else 
//       { 
// 	// if is dir, get entry.
// 	if ( entry->d_type == 4  )// && entry->d_name[0] != '.' ) 
// 	  {
// 	std::cout << "cout: "<< dir_name.c_str() << "/" << entry->d_name<< "\n";

// 	//d_type==4
// // 	struct stat s;
// // 	if( stat(dir_name.path,&s) == 0 )
// // 	  {
// // 	    if( s.st_mode & S_IFDIR )      
// 	path_vec->push_back(dir_name+"/"+entry->d_name);
// 	  }
//       }

//   }
//   // Close the directory. 
//   if (closedir (d_h)) {
//     return;
//     std::cout<< "Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno);
//   }


//   return ;
// }


//----------------------------------------------------------------------------
// GetFilesInDirectory function code >90% copy pasta from website(in comments). user was Andreas Bonini
// http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c
/* Returns a list of files in a directory (except the ones that begin with a dot) */
// void vtkMRMLNDLibraryNode::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
// {
  /*
#ifdef WINDOWS
  HANDLE dir;
  WIN32_FIND_DATA file_data;

  if ((dir = FindFirstFile((directory + "/ *").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
    return; / * No files found * /

  do {
    const std::string file_name = file_data.cFileName;
    const std::string full_file_name = directory + "/" + file_name;
    const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

    if (file_name[0] == '.')
      continue;

    if (is_directory)
      continue;

    out.push_back(full_file_name);
  } while (FindNextFile(dir, &file_data));

  FindClose(dir);
#else
  DIR *dir;
  class dirent *ent;
  class stat st;

  dir = opendir(directory);
  while ((ent = readdir(dir)) != NULL) {
    const string file_name = ent->d_name;
    const string full_file_name = directory + "/" + file_name;

    if (file_name[0] == '.')
      continue;

    if (stat(full_file_name.c_str(), &st) == -1)
      continue;

    const bool is_directory = (st.st_mode & S_IFDIR) != 0;

    if (is_directory)
      continue;

    out.push_back(full_file_name);
  }
  closedir(dir);
#endif
*/
//     return;
// } // GetFilesInDirectory

//----------------------------------------------------------------------------
vtkMRMLNDLibraryNode::~vtkMRMLNDLibraryNode(void)

{
  // this->SlicerDataType.clear();

  for(std::map<std::string,vtkMRMLNDLibraryNode *>::iterator subIter= SubLibraries.begin(); subIter!=SubLibraries.end();++subIter)
    {
      //SubLibraries[]
      //subIter->second->PrintSelf(os,indent.GetNextIndent());
      
      //delete[] subIter->second();// failure, objectype is not a function of funtion pointer
      //delete subIter->second();// failure, objectype is not a function of funtion pointer
    }
  //
}
