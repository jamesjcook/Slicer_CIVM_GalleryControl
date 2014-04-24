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

typedef std::map<std::string,std::vector<std::string> * > * std_str_hash ;


// standard includes, most were added for our dir listing command.
#include <stdlib.h>
#include <stdio.h>

#ifndef WIN32
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#else
#include <windows.h>
//#include <iostream.h>
#include "Shlwapi.h"
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
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std_str_hash tagCloud)
{
  //this->Build(LibPointer,path);
  return true; 
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(void) 
{
  return this->Build(LibPointer);
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(std::string path)
{
  return this->Build(LibPointer,path);
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib)
{
  //does a create by path of the sublibs in lib. 
  std::vector<std::string> * pathList = new std::vector<std::string>;
  this->GetSubDirs(pathList,lib->GetLibRoot());
  bool status=false;
 
  std::string pConfPath = lib->GetLibRoot();
  pConfPath=pConfPath+"/lib.conf";
  std::string parentCategory("NoCategory");
  std::string childCategory("NoCategory");
  int fileFound=false;
  ifstream pLibConf ( pConfPath.c_str() );
  #ifdef WIN32 
  fileFound = fexists(pConfPath.c_str());
#else
    if ( pLibConf ) 
  {
	  fileFound=true;
  }
#endif	
  if (  fileFound ) 
    {
      pLibConf >> parentCategory;
      pLibConf >> childCategory;
      pLibConf.close();
    }
  

  std::vector<std::string>::iterator it=pathList->begin();
  while ( it !=pathList->end() )
    {
    ////
    // Check for lib.conf file
    std::string confPath = *it;
    confPath = confPath+"/lib.conf";
    std::string category("NoCategory");
    int fileFound = false;
    ifstream libConf ( confPath.c_str() );
#ifdef WIN32 
    fileFound = fexists(confPath.c_str());
#else
    if ( libConf ) 
      {
	  fileFound=true;
      }
#endif	
	if (  fileFound ) 
      {
	  libConf >> category;
      libConf.close();
      }
	//return false;
    ////
    if ( category == "NoCategory" )
      {
      ////
      // this cauess errors in winodws!
      ////
      std::cout << "cout: Remove path from consideration" << *it << "\n";
	    it=pathList->erase(it);
      }
	else
	{
		it++;
	}
  } // end loop to clear elements from path which dont have a lib.conf


  //check to see if there will be a change in size of our sublib list, and only re-create them if there is.
  if( pathList->size() != lib->SubLibraries.size() && pathList->size()>0 ) 
    {
    lib->clearSubs();
    char delim = '/';
    for ( int i=0; i< pathList->size(); i++ ) 
      {
      
      //std::string subName=this->split(pathList->at(i),delim).back();//cacl path parts
      //vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode(pathList->at(i),subName); // these two commands do not produce expected result

      ////
      // Process lib.conf file
      std::string confPath = pathList->at(i);
      confPath=confPath+"/lib.conf";
      std::string category("NoCategory");//<< b_file;//>> str;

    int fileFound=false;
    ifstream libConf ( confPath.c_str() );
  #ifdef WIN32 
//#include "Shlwapi.h"
  fileFound = fexists(confPath.c_str());
#else
    if ( libConf ) 
  {
	  fileFound=true;
  }
#endif	
      //category << libConf ;//>> str;
	  if ( fileFound ) 
	    {
          libConf >> category;
          libConf.close();
	    }
      ////
      if ( category != "NoCategory" )
        {        }
      std::vector<std::string> libPathParts=this->split(pathList->at(i),delim);
      std::cout << "Cout: Build libpointer(constructor call with path), " << pathList->at(i)  << pathList->at(i)+"," << libPathParts.back()+"," << category << "\n";
      // build sublib from path, should create sublib with name and path set.
      // limited sub gathering for now
      vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode(pathList->at(i),libPathParts.back(),category);
      subLib->SetParentNode(lib);
      lib->SubLibraries[subLib->GetLibName()]=subLib; 
      }
    if ( pathList->size()>0 )
      {
      status=true;
      //delete pathList;//no need to delete a 0 length path list so we dont always delete?
      }
    else 
      { 
      std::cout << "Cout: pathList empty.\n";
      }
    } 
  if( pathList->size()>0 )
    {
    std::cout << "Clearing pathlist\n";
    pathList->clear();      
    }
  //// temporary always return after directory listings.
  return status;
  this->GetSubFiles(pathList,lib->GetLibRoot());  
  if( pathList->size() != lib->FilePaths->size() ) 
    {
    lib->FilePaths->clear();
    char delim = '/';
    for ( int i=0; i< pathList->size(); i++ ) 
      {
      if ( 0 ) 
        {
        std::cout << "Cout: FilePaths add, " << pathList->at(i)<< "\n";    
        lib->FilePaths->push_back(pathList->at(i));
        }
      else 
        {// our sub build code for example, lef thtis here for now in case we decide that files are also libs
        vtkMRMLNDLibraryNode * subLib;
        if ( childCategory != "NoCategory" )
          {
          std::string category=childCategory;
          std::vector<std::string> libPathParts=this->split(pathList->at(i),delim);
          std::cout << "Cout: Build libpointer(constructor call with path), " << pathList->at(i)+"," << libPathParts.back()+"," << category << "\n";
          // build sublib from path, should create sublib with name and path set.
          // limited sub gathering for now
          subLib = new vtkMRMLNDLibraryNode(pathList->at(i),libPathParts.back(),category);
          subLib->isLeaf=true;
          //std::cout << "Cout: Setting leaf staus\n";
          }
        else 
          {
          std::vector<std::string> libPathParts=this->split(pathList->at(i),delim);
          subLib = new vtkMRMLNDLibraryNode(pathList->at(i),libPathParts.back());
          subLib->isLeaf=true;
          }
        // build sublib from path, should create sublib with name and path set.
        // limited sub gathering for now
        subLib->SetParentNode(lib);
        lib->SubLibraries[subLib->GetLibName()]=subLib; 
        }
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
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std::string path)
{
  char delim='/';
  std::vector<std::string> libPathParts=this->split(path,delim);
  //LibName=libPathParts.back();// this should be modified to give a better name.
  return this->Build(lib,path,libPathParts.back());
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib,std::string path, std::string name)
{
  return this->Build(lib,path,name,std::string("NoCategory"));
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib,std::string path, std::string name,std::string category)
{
  lib->SetLibName(name);
  lib->SetCategory(category);
  lib->SetLibRoot(path); 
  return this->Build(lib);
}

//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubCategoryies(std::vector<std::string > * path_vec, std::string dir_name) 
{ // get sub fields for a given nd library. This is hard problem since our cloud of data can have a very variable associateion. 


  return;
}

// core of get subdirs and get sub files, pass output pointer, path, exclusion list and, flag for get sub files, or get sub dirs
void vtkMRMLNDLibraryBuilder::GetSubCont(std::vector<std::string> * path_vec, std::string dir_name,std::vector<std::string> *exclusionList, int fileTypeFlag)
{
  //fileTypeFlag, 
  //  1 for directories, with exclusionfilter, 
  //  2 for directories, with inclusionfilter
  //  3 for files, with exclusionfilter
  //  4 for files, with inclusionfilter
  //  anythingelse, no get.

  //unix way.
#ifndef WIN32
  DIR * d_h;
  // Open the current directory. 
  d_h = opendir (dir_name.c_str());
  if (! d_h) 
    {
    std::cout << "Cout:Cannot open directory, "<< dir_name.c_str() << " : " << strerror (errno) << "\n";
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

  while(1) // loop until we call our break condition, breaks on bad entry.
    {
#ifndef WIN32
    entry = readdir (d_h);
    if (! entry) 
      {
      break;
      } 
#else
    if ( ! FindNextFile(d_h, &entry))
      {
      break;
      }
      
#endif
    bool is_directory=false;
#ifndef WIN32
    if ( entry->d_type == 4 )
      is_directory = true;
    const std::string file_name = entry->d_name;
#else
    is_directory = (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    const std::string file_name = entry.cFileName;
#endif

    bool returnResults=false;
    if ( is_directory && ( fileTypeFlag == 1 || fileTypeFlag == 2 ) ) 
      {
      returnResults=true;
      } 
    else if (!is_directory && ( fileTypeFlag == 3 || fileTypeFlag == 4 ) ) 
      {
      returnResults=true;
      }
    else 
      {
      //nothing
      }
    bool fileTypeContinue=returnResults;
    if(fileTypeContinue)
      {
      //for entry in ignore list, if ! match ignore list, add, else skip
      for (std::vector<std::string>::iterator sIt=exclusionList->begin();sIt<exclusionList->end();sIt++)
        {
        //std::cout
        int fname_index;
        if ( sIt->at(0) == '^' ) //check for front load exclusion
          {//startswith
          //fname_index=0;
          for(int stridx=1;stridx<sIt->size();stridx++)
            {
            if( file_name[stridx-1]==sIt->at(stridx) )
              {
              if ( fileTypeFlag%2 != 0 ) 
                returnResults = false;
              } 
            else
              {
              if ( fileTypeFlag%2 == 0  ) 
                returnResults = false;
              }
            }

          }
        else if ( sIt->at(sIt->size()-1)== '$' ) //check for end load exclusion.
          {//ends with
          int n_idx=file_name.size();
          for(int stridx=0;stridx<sIt->size()-1;stridx++)
            {//iterates over our file ending, n h d r($) with the $ skipped.
            n_idx=file_name.size()-((sIt->size()-1)-stridx);
            if( file_name[n_idx]==sIt->at(stridx))
              {
              if ( fileTypeFlag%2 != 0  ) 
                returnResults = false;
              } 
            else
              {
              if ( fileTypeFlag%2 == 0  ) 
                returnResults = false;
              }
            }
          }
        }//end exclusionlist processing
      }//end filetypecontinue
    
    if ( returnResults ) 
      {
      //std::cout << "cout: include, "<< dir_name.c_str() << "/" << file_name<< "\n";
      path_vec->push_back(dir_name+"/"+file_name);
      }
    else 
      {
      //std::cout << "cout: exclude, "<< dir_name.c_str() << "/" << file_name<< "\n";
      }
    }

#ifndef WIN32
  // Close the directory. 
  if (closedir (d_h)) //return on sucessful unix close?
    {
    return;
    } 
  else 
    {
    //not sure this is where this belongs.
    //std::cout<< "Cannot open directory "<< dir_name.c_str() << " : " << strerror (errno);
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
void  vtkMRMLNDLibraryBuilder::GetSubDirs(std::vector<std::string > * path_vec, std::string dir_name) 
//void vtkMRMLNDLibraryBuilder::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{
  std::vector<std::string> * exclusionList = new std::vector<std::string>;
  exclusionList->push_back("^.");
  int typeFlag = 1;
  GetSubCont(path_vec,dir_name,exclusionList,typeFlag);
  return;
}


//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubFiles(std::vector<std::string > * path_vec, std::string dir_name) 
//void vtkMRMLNDLibraryBuilder::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{
  std::vector<std::string> * inclusionList = new std::vector<std::string>;
  inclusionList->push_back("nhdr$");
  int typeFlag = 4;
  GetSubCont(path_vec,dir_name,inclusionList,typeFlag);
  return;
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


void vtkMRMLNDLibraryBuilder::ResetLib()   // clear out the lib
{
  // i think we should loop over each element of sublibraries calling delete on the value part of the map, and then clear.
  //For now we'll leave this behavior
  LibPointer->clearSubs();
  return;
}
bool vtkMRMLNDLibraryBuilder::ReBuild()    // rebuild the lib(first resets)
{
  this->ResetLib();
  return this->Build(LibPointer);
}
//----------------------------------------------------------------------------
// split function code >90% copy pasta from website(in comments). user was Evan Teran
// http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
//std::vector<std::string> &vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim, std::vector<std::string> &elems);
//std::vector<std::string> vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim);

std::vector<std::string> & vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
  elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

//#include <fstream>
bool vtkMRMLNDLibraryBuilder::fexists(const char *filename) {
  ifstream ifile(filename);
  return ifile;
}


bool vtkMRMLNDLibraryBuilder::confCheck (std::string confPath)
{ 
	std::string cp=confPath+"/lib.conf";
	return !fexists(cp.c_str());
}