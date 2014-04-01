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

#ifndef WIN32
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#else

#endif
#include <string.h>


//#define storable


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
 vtkMRMLNDLibraryBuilder::vtkMRMLNDLibraryBuilder(vtkMRMLNDLibraryBuilder & builder)
 {
   
 }

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryBuilder::operator=(vtkMRMLNDLibraryBuilder const & builder)
{
  return;
}

//----------------------------------------------------------------------------
vtkMRMLNDLibraryBuilder::~vtkMRMLNDLibraryBuilder(void)
{
  // this->SlicerDataType.clear();
}

vtkMRMLNode*  vtkMRMLNDLibraryBuilder::CreateNodeInstance(void)
{
  vtkSmartPointer<vtkMRMLNode> sp ;
  return sp;
}
#ifdef storablenode 
bool vtkMRMLNDLibraryBuilder::
GetModifiedSinceRead()
{
  return false;
}

//----------------------------------------------------------------------------
void vtkMRMLNDLibraryBuilder::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  os << indent << "NDLibraryBuilder (Printself)\n";
  //os << indent << "LibRoot:" << this->GetLibRoot() << "\n";

  return;
}
void vtkMRMLNDLibraryBuilder::
ProcessMRMLEvents (vtkObject *, unsigned long, void *)
{
  return;
}

void vtkMRMLNDLibraryBuilder::
ReadXMLAttributes (const char **atts)
{
  return;
}


void vtkMRMLNDLibraryBuilder::SetSlicerDataType( const char * type ) 
{ 
  this->SlicerDataType.clear();
  this->SlicerDataType = type;
}


void vtkMRMLNDLibraryBuilder::
StorableModified ()
{
  return;
}

void vtkMRMLNDLibraryBuilder::
UpdateScene (vtkMRMLScene *scene)
{
  return;
}

void vtkMRMLNDLibraryBuilder::
WriteXML (ostream &of, int indent)
{
  return;
}
#endif

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

    for ( int i=0; i< pathList->size(); i++ ) 
      {
      std::cout << "Cout: Build libpointer(constructor call with path)" << pathList->at(i)<< "\n";    
      vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode(pathList->at(i));
      // build sublib from path, should create sublib with name and path set.
      // limited sub gathering for now
      subLib->SetParentNode(lib);
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

// //----------------------------------------------------------------------------
// void vtkMRMLNDLibraryBuilder::SetLibPointer(vtkMRMLNDLibraryNode * lib)
// {
//   LibPointer = lib;
// }

//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubCategoryies(std::vector<std::string > * path_vec, std::string dir_name) 
{ // get sub fields for a given nd library. This is hard problem since our cloud of data can have a very variable associateion. 
  
}


//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubDirs(std::vector<std::string > * path_vec, std::string dir_name) 
//void vtkMRMLNDLibraryBuilder::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{

  //unix way.
#ifndef WIN32
  DIR * d_h;
  // Open the current directory. 
  d_h = opendir (dir_name.c_str());
  if (! d_h) 
    {
      std::cout << "Cout:Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno) << "\n";
      return;
    }
  struct dirent * entry;
#else
  HANDLE d_h;
  WIN32_FIND_DATA entry;
  if ((d_h = FindFirstFile((dir_name + "/*").c_str(), &entry)) == INVALID_HANDLE_VALUE)
    {
      return; // No files found 
    }
  
#endif
  
// #ifndef WIN32
//   while (1) //unixloop
// { 
// }
// #else
//   while (! (!entry)) //winloop // hopefully this is a null check.
// { 
// }
// #endif
    while(1)
    {
#ifndef WIN32
      entry = readdir (d_h);
#else
      FindNextFile(d_h, &entry);
#endif
      if (! entry) 
	{
	  break;
	} 
      bool is_directory=false;
#ifndef WIN32
      if ( entry->d_type == 4 )
	is_directory = true;
      const std::string file_name = entry->d_name;
#else
      is_directory = (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
      const std::string file_name = entry.cFileName;
#endif

      if ( is_directory) 
	{
	  //for entry in ignore list, if ! match ignore list, add, else skip
	  if ( file_name[0] != '.' && file_name[0] != '_' ) //&& entry->d_name[0] != '0') 
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


#ifndef WIN32
  // Close the directory. 
  if (closedir (d_h)) 
    {
      return;
      std::cout<< "Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno);
    }
#else
  FindClose(d_h);
#endif

#ifndef WIN32
#else
   if ( 0 ) {
  HANDLE d_h;
  WIN32_FIND_DATA entry;

  if ((d_h = FindFirstFile((dir_name + "/*").c_str(), &entry)) == INVALID_HANDLE_VALUE)
    return; // No files found 

  do {
    const std::string file_name = entry.cFileName;
    const std::string full_file_name = dir_name + "/" + file_name;
    const bool is_directory = (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

    //handle exclusions
    if (file_name[0] == '.' && file_name[0] == '_')
      continue;
    //exclude non-directories
    if (!is_directory)
      continue;

    path_vec->push_back(full_file_name);
  } while (FindNextFile(d_h, &entry));

  FindClose(d_h);
}
#endif


  
   return ;
}



//----------------------------------------------------------------------------
// GetFilesInDirectory function code >90% copy pasta from website(in comments). user was Andreas Bonini
// http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c
/* Returns a list of files in a directory (except the ones that begin with a dot) */
void vtkMRMLNDLibraryBuilder::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{
  
#ifdef WIN32
  HANDLE dir;
  WIN32_FIND_DATA file_data;

  if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
    return; // * No files found * /

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
// unix way
/*  DIR *dir;
  class dirent *ent;
  class stat st;

  dir = opendir(directory);
  while ((ent = readdir(dir)) != NULL) {
  const std::string file_name = ent->d_name;
  const std::string full_file_name = directory + "/" + file_name;

    if (file_name[0] == '.')
      continue;

    if (stat(full_file_name.c_str(), &st) == -1)
      continue;

    const bool is_directory = (st.st_mode & S_IFDIR) != 0;

    if (is_directory)
      continue;

    out.push_back(full_file_name);
  }
  closedir(dir); */
#endif

    return;
} // GetFilesInDirectory
