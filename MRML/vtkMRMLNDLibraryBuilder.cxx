// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibraryBuilder
// node to insert information into a datastructure related to alibrary of data.
// we will start basically with hardcoded libraries at first then expand the class to use a database

#include <vtkMRMLNode.h>
#include <vtkObjectFactory.h>
#include <vtkNew.h>
#include <vtkMRMLVolumeNode.h>
#include <vtkSmartPointer.h>
#include <vtkMRMLNDLibraryBuilder.h>

//typedef std::map<std::string,std::vector<std::string>  > std_str_hash ;
//typedef std::map<std::string,std::vector<std::string>  > std_str_hash ;
// typedefs moved to the ndlibrary
//typedef std::map<std::string,std::string> std_str_hash ;
//typedef std_str_hash::iterator s_hash_iter;

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
std::string vtkMRMLNDLibraryBuilder::AgeTimeConvert(std::string zeroPadSeconds) 
{
  float tollerance=0.5; // 0-1 value to tollerate remainder
  return AgeTimeConvert(zeroPadSeconds,tollerance);
}

// a fucntion to take time in integer seconds and return a "better"(more human readable/comprehensiable) string representation 
// returns qstringlist of new time number(floord) and time units(days,months,years)
//----------------------------------------------------------------------------
std::string vtkMRMLNDLibraryBuilder::AgeTimeConvert(std::string zeroPadSeconds,float tollerance) 
{
  std::vector<std::string> returnValues;
  int seconds=std::atoi(zeroPadSeconds.c_str());
  float dayseconds=24*60*60;
  float monthseconds=dayseconds*30.437; // this is the number of days with a 12month year lasting 365.24 days
  float yearseconds=dayseconds*365.25;
  // algorithm should be some kinda if remainder < percentage of unit seconds.

  int multiplier=0;
  int remainder=1;
  std::vector<float> divisors ;
  divisors.push_back(yearseconds);
  divisors.push_back(monthseconds);
  divisors.push_back(dayseconds); 
  std::vector<std::string> divisornames;
  divisornames.push_back("year");
  divisornames.push_back("month");
  divisornames.push_back("day");

  for (int dIt=0;dIt<divisors.size();dIt++) 
    {
    multiplier=floor(float(seconds)/divisors.at(dIt));  
    remainder=seconds-multiplier*divisors.at(dIt);
    if ( remainder>tollerance*divisors.at(dIt) )
      {
      multiplier=0;
      }
    else
      {
      seconds=remainder;    
      }
    if ( multiplier > 0 ) 
      {
      returnValues.push_back(divisornames.at(dIt));
      char buffer [50];
      int l=sprintf(buffer,"%d",multiplier);
      returnValues.push_back(std::string(buffer,0,l));
      }
    if ( seconds == 0 ) //for perfect division loop end condition
      { 
      dIt=dIt+divisors.size();
      }
    }
  if ( returnValues.size()>0 ) 
    {
    return join(returnValues,"_");
    } 
  else
    {
    return "_";
    }
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(std_str_hash tagCloud)
{
  return this->Build(LibPointer,tagCloud); 
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib, std_str_hash tagCloud)
{
  lib->SetTagCloud(tagCloud);
  return this->Build(lib);
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
//does a create by path of the sublibs in lib. 
bool vtkMRMLNDLibraryBuilder::Build(vtkMRMLNDLibraryNode * lib)
{
  bool status=false;
  std_str_hash tagCloud=lib->GetTagCloud();
  if (tagCloud.size()>0) 
    { 
    std::cout  << "lib:"<< lib->GetLibName()<< ", "<<tagCloud.size() 
               << " element tagCloud found, not loading! "  << std::endl;    
    } else 
    { // if tagcloud is empty, read lib file
    std::cout  << "lib:"<< lib->GetLibName()<< ", tagCloud not found, loading! "  << std::endl;    
    tagCloud = libFileRead(lib); //readlib.
    bool libchange=this->ParseCloud(lib,tagCloud);
    lib->SetTagCloud(tagCloud);
    }
  if ( lib->GetCategory() == "NoCategory" && tagCloud.find("Category") != tagCloud.end() ) 
    {
    lib->SetCategory(tagCloud["Category"]);
    std::cout  << "Cout: Parent didnt give me a category, added on build." << std::endl;
    }
  if ( lib->GetLibName() == "NoName" && tagCloud.find("LibName") != tagCloud.end() ) 
    { 
    lib->SetLibName(tagCloud["LibName"]);
    std::cout  << "Cout: Parent didnt give me a LibName, added on build." << std::endl;
    }

  testDataOk=getTestStatus(lib);  //When should testDataOk be true? when env var DATALIBRARIES_TEST exists
  std::vector<std::string> * subLibPathList = new std::vector<std::string>;
  this->GetSubDirs(subLibPathList,lib->GetLibRoot());
/*
  //going to let this condition be handled by the add code integral to this loop, this is just doing double work for nothing.
  std::cout << "Cout: considering " << subLibPathList->size() << " dirs";
  this->RemoveNonLibDirs(subLibPathList); //remove invalid entries
  std::cout << "Cout: kept " << subLibPathList->size() << " dirs" << std::endl;
*/
  //check to see if there will be a change in size of our sublib list, and only re-create them if there is.
  // this requires improvement, it should doa check per element that they're all present.
  //if( subLibPathList->size() != lib->SubLibraries.size() && subLibPathList->size()>0 ) 
    {
    //lib->clearSubs();
    char delim = '/';
    // for every dir in path make new sublib.
    // check if it exists in dir already, and add if missing.
    for ( int i=0; i< subLibPathList->size(); i++ ) 
      {
      ////
      // Process lib.conf file
      std_str_hash subLibCloud=libFileRead(subLibPathList->at(i) + "/lib.conf");
      if (subLibCloud.find("Category") == subLibCloud.end() )
        subLibCloud.clear();//if the sublibcloud does not have category it is invalid.
      if (!subLibCloud.empty() )
        {
        std::vector<std::string> libPathParts=this->split(subLibPathList->at(i),delim);
        // at the minimum there should always be a category field in our tag cloud
        vtkMRMLNDLibraryNode * subLib = new vtkMRMLNDLibraryNode(
          subLibPathList->at(i),libPathParts.back(),subLibCloud["Category"]);
        bool libchange=this->ParseCloud(subLib,subLibCloud);
        if ( testDataOk) 
          {
          std::cout << "Cout: vtkMRMLNDLibraryNode constructor call with " << std::endl
                    << "\tpath: \t"     << subLib->GetLibRoot() << std::endl 
                    << "\tname: \t"     << subLib->GetLibName() << std::endl 
                    << "\tcategory: \t" << subLib->GetCategory()<< std::endl ;
          }
        // only add a lib if there is no entry matching it yet,
        // and it is not a testinglib, or testing is ok.
        if ( lib->SubLibraries.find(libPathParts.back()) == lib->SubLibraries.end() 
             && ( subLibCloud.find("TestingLib") == subLibCloud.end() || testDataOk ) )
          {
          std::cout  << "Cout: Add Lib at path " << subLibPathList->at(i) << std::endl;
          subLib->SetParentNode(lib);
          subLib->SetTagCloud(subLibCloud);
          lib->SubLibraries[libPathParts.back()]=subLib; 
          //store subs by disk name, but let our sublibs report their name as what ever they wish.
          }
        }
      }
    if ( subLibPathList->size()>0 )
      {
      status=true;
      //delete subLibPathList;//no need to delete a 0 length path list so we dont always delete?
      }
    else 
      { 
      std::cout << "Cout: subLibPathList empty.\n";
      }
    } 
  if( subLibPathList->size()>0 )
    {
    std::cout << "Cout: Clearing pathlist\n";
    subLibPathList->clear();      
    }
  this->GetSubFiles(subLibPathList,lib->GetLibRoot());  
  //if (subLibPathList->size() != lib->SubLibraries.size()-subLibPathList->size())
    {
    char delim = '/';
    for ( int i=0; i< subLibPathList->size(); i++ ) 
      {
      ////
      // Process lib.conf file
      std_str_hash subLibCloud=tagCloud;
      // our sub build code for example, lef thtis here for now in case we decide that files are also libs
      vtkMRMLNDLibraryNode * subLib;
      std::vector<std::string> libPathParts=this->split(subLibPathList->at(i),delim);
      if ( subLibCloud["childCategory"] != "NoCategory" )
        {
        std::string subCategory=subLibCloud["childCategory"];
        std::cout << "Cout: Build libpointer(constructor call with path), " 
		  << subLibPathList->at(i)+"," << libPathParts.back()+"," << subCategory << "\n";
        // build sublib from path, should create sublib with name and path set.
        // limited sub gathering for now
        subLib = new vtkMRMLNDLibraryNode(subLibPathList->at(i),libPathParts.back(),subCategory);
        subLib->isLeaf=true;
        //std::cout << "Cout: Setting leaf staus\n";
        }
      else 
        {
        subLib = new vtkMRMLNDLibraryNode(subLibPathList->at(i),libPathParts.back());
        subLib->isLeaf=true;
        }
      // build sublib from path, should create sublib with name and path set.
      // limited sub gathering for now
      //subLib->SetTagCloud(&tagCloud); //last second put the tag cloud into the data lib on load. might need to copy it toa pointer object to avoid falling out of scope.
      //clean up values in the sublibcloud
      subLibCloud["Category"]=subLibCloud["childCategory"];
      subLibCloud.erase("childCategory");

      if ( lib->SubLibraries.find(libPathParts.back()) == lib->SubLibraries.end() 
           && ( subLibCloud.find("TestingLib") == subLibCloud.end() || testDataOk ) )
        {
        std::cout  << "Cout: Add Lib at path " << subLibPathList->at(i) << std::endl;
        std::cout << "Cout: Add tagcloud" << std::endl ;
        subLib->SetParentNode(lib);
        subLib->SetTagCloud(subLibCloud);
        lib->SubLibraries[subLib->GetLibName()]=subLib; 
        }
      }
    if ( subLibPathList->size()>=1 )
      {
      status=true;
      delete subLibPathList;//no need to delete a 0 length path list so we dont always delete?
      }
    else 
      { 
      std::cout << "Cout: subLibPathList empty.\n";
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
void  vtkMRMLNDLibraryBuilder::GetSubCategories(std::vector<std::string > * path_vec, std::string dir_name) 
{ // get sub fields for a given nd library. This is hard problem since our cloud of data can have a very variable associateion. 


  return;
}

// core of get subdirs and get sub files, pass output pointer, path, exclusion list and, flag for get sub files, or get sub dirs
void vtkMRMLNDLibraryBuilder::GetSubCont(std::vector<std::string> * path_vec, std::string dir_name,std::vector<std::string> *patternList, int fileTypeFlag)
{
  //fileTypeFlag, 
  //  1 for directories, with exclusionfilter, 
  //  2 for directories, with inclusionfilter
  //  3 for files, with exclusionfilter
  //  4 for files, with inclusionfilter
  //  anythingelse, no get.
  //odd patterns are exclusion 
  //even patterns are inclusion
  // div 2 will have remainder 0 for even
  bool excludePat=fileTypeFlag%2;
  //unix way.
#ifndef WIN32
  DIR * d_h;
  // Open the current directory. 
  d_h = opendir (dir_name.c_str());
  if (! d_h) 
    {
    std::cout << "Cout: Cannot open directory, "<< dir_name.c_str() << " : " << strerror (errno) << "\n";
    return;
    }
  struct dirent * entry;
#else
  HANDLE d_h;
  WIN32_FIND_DATA entry;
  if ((d_h = FindFirstFile((dir_name + "/*").c_str(), &entry)) == INVALID_HANDLE_VALUE)
    return; // No files found 
#endif
  while(1) // loop until we call our break condition, breaks on bad entry.
    {
#ifndef WIN32
    entry = readdir (d_h);
    if (! entry) 
      break;
#else
    if ( ! FindNextFile(d_h, &entry))
      break;
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

    bool considerEntry=false;
    if ( is_directory && ( fileTypeFlag == 1 || fileTypeFlag == 2 ) ) 
      {
      considerEntry=true;
      //std::cout << "Cout: is dir\t" << file_name << std::endl;
      } 
    else if (!is_directory && ( fileTypeFlag == 3 || fileTypeFlag == 4 ) ) 
      {
      considerEntry=true;
      //std::cout << "Cout: is file\t" << file_name << std::endl;
      }
    else 
      {
      //nothing
      }
    bool includeFile=considerEntry;
    if(considerEntry)
      { //for entry in patternlist, if match , set include for odd, set exclude for even
      for (std::vector<std::string>::iterator sIt=patternList->begin();sIt<patternList->end();sIt++)
        { 
        bool patMatched=false;
        if ( sIt->size()>=2 && file_name.size()>=sIt->size()-1 )//check for good pattern.
          { //our file lenght must be at least size of pattern-1 long
          /*if(getTestStatus(0)) // check if we're a tesing system, show pattern if we are
            std::cout <<  "Cout: P: '" << *sIt << "' ";*/
          if ( sIt->at(0) == '^' ) //check for front load pattern
            {//startswith
            int stridx=1;
            if ( 1 ) 
              { //strcmp? 
              //our pattern should skip the first letter.
              stridx=strcmp(sIt->substr(1).c_str(),file_name.substr(0,sIt->size()-1).c_str());//this doesnt account for filename too small.
              if(stridx==0)
                patMatched=true;
              } else
              {
              do //match checking, letter by letter :p
                {
                std::cout << "Cout: \t" << file_name[stridx-1] << sIt->at(stridx) << std::endl;
                if( file_name[stridx-1]==sIt->at(stridx) )
                  patMatched=true;
                else
                  patMatched=false;
                stridx++;
                } while(patMatched && stridx<sIt->size() && stridx<file_name.size() );
              }
            }//close prefix pattern
          else if ( sIt->at(sIt->size()-1)== '$' ) //check for end load pattern
            {//ends with
            int stridx=0;
            if ( 1 ) 
              {
              stridx=strcmp(
                sIt->substr(0,sIt->size()-1).c_str(),//whole pattern except last char
                file_name.substr(file_name.size()-sIt->size()+1).c_str());
              //starting at fnsize-patsize+1(because bogus pattern size).
              if(stridx==0)
                patMatched=true;
              } else
              {
              int n_idx=file_name.size();
              do //match checking
                {
                n_idx=file_name.size()-((sIt->size()-1)-stridx);
                std::cout << "Cout: \t" << file_name[n_idx] << sIt->at(stridx) << std::endl;
                if( file_name[n_idx]==sIt->at(stridx) )
                  patMatched=true;
                else
                  patMatched=false;
                stridx++;
                } while(patMatched && stridx<sIt->size()-1 && stridx<file_name.size() );
              }
            }//close postfix pattern
          } else
          {
          if(getTestStatus(0))
            std::cout << "Cout: Bad pattern given or very short filename, pattern and filename must be at least 2 characters." << std::endl;
          }
          if(patMatched&&excludePat) 
            includeFile=false;
        }//end patternlist processing
      }//end filetypecontinue
    
    if ( includeFile ) 
      {
      //std::cout << "Cout: include, "<< dir_name.c_str() << "/" << file_name<< "\n";
      path_vec->push_back(dir_name+"/"+file_name);
      }
    else 
      {
      if(getTestStatus(0)&&considerEntry)
        {
        std::cout << "Cout: exclude: "<< dir_name.c_str() << "/" << file_name<< "\n";
        }
      }
    }//end loop for each dir entry

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
  std::vector<std::string> * patternList = new std::vector<std::string>;
  patternList->push_back("^.");
  int typeFlag = 1; //get dirs, exclude from list
  GetSubCont(path_vec,dir_name,patternList,typeFlag);
  return;
}


//----------------------------------------------------------------------------
void  vtkMRMLNDLibraryBuilder::GetSubFiles(std::vector<std::string > * path_vec, std::string dir_name) 
//void vtkMRMLNDLibraryBuilder::GetFilesInDirectory(std::vector<std::string> &out, const std::string &directory)
{
  std::vector<std::string> * patternList = new std::vector<std::string>;
  if ( 1 ) 
    {
      int typeFlag = 3;// get files, exclude from list.
      patternList->push_back("^.");    //excluding start with .
      patternList->push_back("~$");    //excluding end with ~
      patternList->push_back("^#");    //excluding start with #
      patternList->push_back("#$");    //excluding end with #
      patternList->push_back(".conf$");//excluding end with .conf
      GetSubCont(path_vec,dir_name,patternList,typeFlag);
    } else 
    {
      patternList->push_back("nhdr$");
      //commented section was the original behavior, switched so that this acts more predictably.
      /* patternList->push_back("nrrd$");
      patternList->push_back("nii.gz$");
      patternList->push_back("nii$");
      patternList->push_back("txt$");*/
      int typeFlag = 4;// get files, include from list.
      GetSubCont(path_vec,dir_name,patternList,typeFlag);
    }
  return;
}

bool vtkMRMLNDLibraryBuilder::getTestStatus(vtkMRMLNDLibraryNode * lib) // boondoggle of a function which will look backwards through libs until it finds any lib which turns tetsing on, or reaches the first lib(null pointer)
{
  std::string testvar="DATALIBRARIES_TEST";
  if ( 1 ) // could play if !lib, so we check system test status if there is no lib.
    {
//#ifndef WIN32
    //    char * testInfo=getenv(testvar.c_str());
//#else 
    //char * testInfo=System::Environment::Collections::GetEnvironmentVariable(testvar.c_str());
    //wchar_t environmentBuffer[10000];
    //GetEnvironmentVariable(L"<<DATALIBRARIES_TEST>>", _countof(environmentBuffer));
//#endif
    char * testInfo=getenv(testvar.c_str());
    if ( testInfo ) 
      {
      return true;
      }
    } else 
    {// never runs because we have the better getenv way now.
    // while our parent lib is defined, get and build the tag cloud, if its a TestingLib(devlib)
    //vtkMRMLNDLibraryNode * temp=lib->getParentNode;
    while (lib)
      {
      //std_str_hash tagCloud=libFileRead(lib->GetLibRoot()+"/lib.conf");
      std_str_hash tagCloud=lib->GetTagCloud();
      //std_str_hash subLibCloud=libFileRead(subLibPathList->at(i) + "/lib.conf");  
      //if ( tagCloud.find("devLib") == tagCloud.end() ) //renamed var in lib.conf
      if ( tagCloud.find("TestingLib") == tagCloud.end() ) 
        {
        std::cout << "TestLib in " << lib->GetLibName()<< std::endl;
        return true;
        } 
      else
        {
        std::cout << "not test lib" << lib->GetLibName() << std::endl;
        }
      lib=lib->GetParentNode();
      }
    }
  return false;
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

//----------------------------------------------------------------------------
// takes lib and tagcloud
// makes sure "required" vars are in the tagcloud
// fixes libpath if it is different from tagcloud
// updates lib category if it is missing.
bool vtkMRMLNDLibraryBuilder::ParseCloud(vtkMRMLNDLibraryNode * lib, std_str_hash  tagCloud)
{
  bool status=false;// hold wether we've made changes or not.
  bool setNewPath=false;
  //// 
  // debug print of the tag cloud
  if ( !tagCloud.empty() ) 
    {
    if ( getTestStatus(0) ) //only print on test sys.
      for ( s_hash_iter tCI=tagCloud.begin(); tCI!=tagCloud.end() ;tCI++ )
        std::cout << "Cout:TAG" <<tCI->first << "=" << tCI->second << std::endl ;
    }
  else 
    {
    std::cout << "Cout: tagCloud empty on parse!"<<std::endl;
    return status;
    }
  //
  if ( tagCloud.find("LibConfPath") == tagCloud.end()) 
    {
    std::cout << "Cout: libconfpath not set in cloud, cloud load failure" << std::endl;
    return false;
    }
  //// 
  //compare TagCloud Path with LibRoot path, if different change lib root to use tagcloud path
  char delim = '/';//path delimiter.
  if ( tagCloud.find("Path") != tagCloud.end() ) 
    {
    std::cout << "Cout: TagCloud: Path found, modifying LibRoot with " 
              << (tagCloud)["Path"] << "." << std::endl;
    std::vector<std::string> tCPath=this->split((tagCloud)["Path"],delim);//vec of tagcloudpath
    std::vector<std::string> lRPath=this->split(lib->GetLibRoot(),delim); //vec of libroot path
    int trimCount=0;
    for (std::vector<std::string>::const_iterator tIt=tCPath.begin();
         tIt!=tCPath.end();++tIt)
      { // get the number of leading '..' we'll need to cut the end of our normal path with.
      if ( *tIt == ".." ) 
        trimCount++;
      }
    //trimCount=std::min(trimCount,lRPath.size());// if there are more trim parts than length of orig path.
    //std::min throws compile err.
    std::cout << "Cout: " << "found " << trimCount << " path parts to trim" << std::endl;
    if ( 1 ) 
      {
      std::vector<std::string>::iterator eit=tCPath.begin()+trimCount;
      tCPath.erase(tCPath.begin(),eit);
      std::vector<std::string>::reverse_iterator lpr= lRPath.rbegin()+trimCount;
      std::vector<std::string>::iterator lpf=lpr.base();
      lRPath.erase(lpf,lRPath.end());
      }
    std::string nLPath=join(lRPath,"/"); // new lib path after trimming.
    nLPath.append("/");
    nLPath.append(join(tCPath,"/"));
    (tagCloud)["Path"]=nLPath;
    setNewPath=true;
    std::cout << "Cout: found new path "<<nLPath <<std::endl;
#ifdef PATHTRIM
    std::vector<std::string> * sPtr ;
    std::vector<std::string> * lPtr ;
    int sdiff=0;
    if ( tCPath.size() <= lRPath.size() ) 
      {
      lPtr = &lRPath;
      sPtr = &tCPath;
      }
    else 
      {
      sPtr = &lRPath;
      lPtr = &tCPath;
      }
    sdiff = lPtr->size() - sPtr->size(); 
    // remove blank entries from paths?
    // remove from the front of longest path until they equal size of small length
    if( sdiff > 0)
      {
      lPtr->erase(lPtr->begin(),lPtr->begin()+sdiff);
      }
    std::vector<std::string>::iterator i1=sPtr->begin();
    std::vector<std::string>::iterator i2=lPtr->begin();
    while (i1!=sPtr->end() && i2!=lPtr->end())
      {
      //    std::cout << "Cout: comp i1,i2," << *i1 << " " << *i2 << std::endl;
      if ( *i1 != *i2) 
        {
        //cout << "  Diff!"<< std::endl;
        setNewPath=true;
        }
      i1++;
      i2++;
      }
#endif
    }
  else
    {
    (tagCloud)["Path"]=lib->GetLibRoot();
    }
  ////
  // update our library with information from lib.conf.
  // if path vectors are different.
  if( setNewPath )
    {
    //lib->SetLibRoot(libConfDir+"/"+(tagCloud)["Path"]); 
    std::cout << "Cout: Lib specifies change path. " << lib->GetLibRoot() 
              << " becomes " << tagCloud["Path"] << std::endl;
    lib->SetLibRoot((tagCloud)["Path"]); 
    status=true;
    }
  ////
  // set the name by tag cloud
  std::vector<std::string> libPathParts=this->split(lib->GetLibRoot(),delim);
  if( libPathParts.size()>0  && (tagCloud)["Category"] == "Time(s)") // this should be regex'd to be if category is a measurement of time
    {
    if ( tagCloud.find("LibName") == tagCloud.end() )
      (tagCloud)["LibName"]=AgeTimeConvert(libPathParts.back(),0.01);
    }
  else 
    {
    if ( tagCloud.find("LibName") == tagCloud.end() )
      (tagCloud)["LibName"]=libPathParts.back();
    }
  //std::string parentCategory("NoCategory");
  if ( tagCloud.find("LibName") !=tagCloud.end()) 
    lib->SetLibName((tagCloud)["LibName"]);
  if ( tagCloud.find("Category") !=tagCloud.end()) 
    {
    //parentCategory=(tagCloud)["Category"];
    lib->SetCategory((tagCloud)["Category"]);
    status=true;
    }
    
  return status; 
}

void vtkMRMLNDLibraryBuilder::ResetLib()   // clear out the lib
{
  // i think we should loop over each element of sublibraries calling delete on the value part of the map, and then clear.
  //For now we'll leave this behavior
  LibPointer->clearSubs();
  LibPointer->CurrentSelection=0;
  return;
}
bool vtkMRMLNDLibraryBuilder::ReBuild()    // rebuild the lib(first resets)
{
  this->ResetLib();
  return this->Build(LibPointer);
}
void vtkMRMLNDLibraryBuilder::RemoveNonLibDirs(std::vector<std::string> * subLibPathList) 
{
  std::vector<std::string>::iterator it=subLibPathList->begin();
  while ( it !=subLibPathList->end() )
    {
    ////
    // Check for lib.conf file
    std::string confPath = *it;
    confPath = confPath+"/lib.conf";
    std_str_hash tagCloud=libFileRead(confPath);
    bool libBad=false;
    if ( tagCloud.find("Category") == tagCloud.end() ||  tagCloud.empty() )
      {
      std::cout << "Cout: missing category or no tagfile, ";
      libBad=true;
      }
    else if ( tagCloud["Category"] == "NoCategory" || ( tagCloud.find("TestingLib") != tagCloud.end() && !testDataOk ) )
      {
      //// debug prints
      if ( tagCloud.find("TestingLib") != tagCloud.end() )
        std::cout << "Cout: testinglib" ;
      if ( !testDataOk ) 
        std::cout << "Cout: not testsystem" ; //<< std::endl;
      if ( tagCloud["Category"] == "NoCategory" )
        std::cout << "Cout: bad category or testinglib";
      ////
      libBad=true;
      }

    //{
    //tagCloud["Category"] = "NoCategory" ;
    //}
    
    //|| ( tagCloud.find("TestingLib") != tagCloud.end() && !testDataOk ) )
    //if ( tagCloud["Category"] == "NoCategory" && tagCloud.find("TestingLib") != tagCloud.end() ) 
    if ( libBad)
      {
      std::cout << "Cout: Remove path from consideration" << *it << std::endl;
      it=subLibPathList->erase(it);
      }
    else
      {
      it++;
      }
    }

  //std::cout << "Cout: remove invalid" << std::endl;
  return;
}

std::string vtkMRMLNDLibraryBuilder::join(std::vector<std::string> &stringList , const std::string &s )
{


  //  return std::copy(stringList, stringList+stringList.size(), std::ostream_iterator<int>(std::cout,s));
  //  return std::copy(stringList.begin(), stringList.end(), std::ostream_iterator<std::string>(std::cout,s));

  //  return std::copy(stringList, stringList+stringList.size(), std::ostream_iterator<int>(std::cout,s));

  std::string out;
  int strSize=0;
  for (std::vector<std::string>::iterator sIt=stringList.begin();sIt<stringList.end();sIt++)
    {
    out.append(*sIt);
    if ( sIt !=stringList.end()-1 )
      out.append(s);
    }  
  return out;
  //   std::string out=std::string(strSize, ' ');
  
  //   int o_i=0;
  //   for (std::vector<std::string>::iterator sIt=patternList->begin();sIt<patternList->end();sIt++)
  //     {
  //     out[o_i
  //     o_i=sIt.length();
  //     }  
}


//----------------------------------------------------------------------------
// split function code >90% copy pasta from website(in comments). user was Evan Teran
// http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
//std::vector<std::string> &vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim, std::vector<std::string> &elems);
//std::vector<std::string> vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim);

std::vector<std::string> & vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim, std::vector<std::string> &elems) 
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) 
    {
    elems.push_back(item);
    }
  return elems;
}

std::vector<std::string> vtkMRMLNDLibraryBuilder::split(const std::string &s, char delim) 
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::fexists(const char *filename) 
{
#ifdef WIN32
  DWORD dwAttrib = GetFileAttributes(filename);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
	  !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
//#include <fstream>
  ifstream ifile(filename);
  return ifile.good();
#endif
}

//----------------------------------------------------------------------------
bool vtkMRMLNDLibraryBuilder::confCheck (std::string confPath)
{ 
  std::string cp=confPath+"/lib.conf";
  return !fexists(cp.c_str());
}

//----------------------------------------------------------------------------
//str2int code >90% copy pasta from website(in comments). user was dan moulding
// http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
//enum STR2INT_ERROR { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
//STR2INT_ERROR
//int vtkMRMLNDLibraryBuilder::str2int (int &i, char const *s, int base = 0)
//{
//   char *end;
//   long  l;
//   errno = 0;
//   l = strtol(s, &end, base);
//   if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
//     return 1;
//   }
//   if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
//     return 2;
//   }
//   if (*s == '\0' || *end != '\0') {
//     return 3;
//   }
//   i = l;
//  return 0;
//}


std_str_hash vtkMRMLNDLibraryBuilder::libFileRead(vtkMRMLNDLibraryNode * lib)
{
  std::string libConfPath = lib->GetLibRoot();
  libConfPath=libConfPath+"/lib.conf";
  return libFileRead(libConfPath);
}

std_str_hash vtkMRMLNDLibraryBuilder::libFileRead(std::string libConfPath  )
{
  std_str_hash tagCloud;
  //int fileFound=false;
  bool fileFound=fexists( libConfPath.c_str() );
  if (libConfPath.length()>255 )
    {
    std::cout << "Cout: ERROR path too long!";
    return tagCloud;
    }

  /*
    #ifndef WIN32
    if ( libConf.good() )
    {
    fileFound=true;
    } 
    #else 
    fileFound = fexists( libConfPath.c_str() );
    #endif
  
    if ( fileFound )
    {
    //    cout << "Cout: opened conf file " << libConfPath << std::endl;
    fileFound=true;
    }
    else
  */
  if ( ! fileFound )
    {
    cout << "Cout:failed to open conf file " << libConfPath << std::endl;
    return tagCloud;
    }
  tagCloud["LibConfPath"]=libConfPath;
  std::string line;
  int lineNum=0;//line counter to keep track of which line we're on for old style files. 
  ifstream libConf ( libConfPath.c_str() );
  while (std::getline(libConf, line))
    {
    //    std::cout << "Cout: lib line " << line << std::endl;
    lineNum++;
    // Process str
    // ignore lines starting in #
    // split line
    std::vector<std::string> p=this->split(line,'=' );
    //std_str_hash[*p.begin()]=p.back();
    //tagcloud["test"]=p.back();
    if (p.size()==1 && ( lineNum==1 || lineNum==2) )// when we do not find an = on a line. 
      {//push_front?
      if ( 1 ) 
        {
        if (lineNum==1) // when its the first line.
          p.insert(p.begin(),"Category");
        if (lineNum==2) // when its the second line. 
          p.insert(p.begin(),"ChildCategory");
        } else 
        {
        if (lineNum==1) // when its the first line.
          p.push_back("Category");
        if (lineNum==2) // when its the second line. 
          p.push_back("ChildCategory");
        p.push_back(p.front());
        p.erase(p.begin());
        }
      //      it=subLibPathList->erase(it);
      }
    while ( p.size()<2 ) 
      {
      p.push_back("_");
      }
    //    std::cout << p.front() << "=" << p.back() << std::endl;
    tagCloud[p.front()]=p.back();
    }
  //  std::cout << "End Lib Read" << std::endl;
  return tagCloud;

#ifdef qt
  /* I DON'T THINK THIS CODE WILL EVER RUN< IT SHOULD BE REMOVED*/
  QString libName =QString::fromStdString(selectedLib->GetLibName());
  QStringList protocols;
  QStringList panels;
  panels << "PGR";
  panels << "FA_Render_Static";
  //for each panel
  //// SUPPORTLIST HACK.
  QString panelSupportDri = QString::fromStdString(DataStore->GetLibRoot());
  for (int i = 0; i < panels.size(); ++i)
    {
    this->PrintText("support check for "+panels.at(i));
    QFile panelConfFile(panelSupportDir+"/"+panels.at(i)+".conf");
    QStringList panelSupportList;//supported libnames for this panel
    if ( panelConfFile.open(QIODevice::ReadOnly) ) 
      {
      QTextStream in(&panelConfFile);
      while(!in.atEnd() )
        {
        QString line= in.readLine();
        //if(!line.empty())
        panelSupportList << line;
	  
        }
      QRegExp protoCompare("^"+libName+"$");
      if ( panelSupportList.indexOf(protoCompare)>=0 )
        {
        protocols << panels.at(i);
        }  
      panelConfFile.close();
      }
    else
      {
      //QMessageBox::information(0, "error", file.errorString());
      this->PrintText("Panel conf file failed to open! "+panelConfFile.fileName());
      this->PrintText(panelConfFile.errorString());
      }
    }
#endif
  
}
