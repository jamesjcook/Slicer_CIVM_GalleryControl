// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibrarayBuilder
// node to build a conter of information related to alibrary of data.
// this will abstract building from the container so we can change the libtary information storage system painlessly in the future



#ifndef __vtkMRMLNDLibraryBuilder_h
#define __vtkMRMLNDLibraryBuilder_h

//to change to inherrrit from storaeble if that make smore sense.
// #define storable 

// MRML includes
//#include "vtkMRML.h"
#include "vtkMRMLNode.h"
//#include "vtkMRMLStorableNode.h"
#include "vtkMRMLNDLibraryNode.h"
// StdIncludes
#include <string>
#include <map>

//#define storable

//VTK_SLICER_VOLUMERENDERING_MODULE_MRML_EXPORT
//should change inherritance to vtkmrmlnode.h
//class VTK_EXPORT vtkMRMLNDLibraryBuilder //: public vtkMRMLNode

//class VTK_MRML_LOGIC_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode
//class VTK_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode // works
//class VTK_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode //works
//class VTKMRMLNDLIBRARYBUILDER_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode
#include "vtkMRMLNDLibraryBuilderExport.h"//works
//missing, hopefully the above is correct. #include "vtkMRMLNDLibraryExport.h"//only active in windows, test comment out in windows
//class VTK_VTKMRMLNDLIBRARYBUILDER_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode//works(the capslock section is referenced in the cmake lists.
class VTK_VTKMRMLNDLIBRARYBUILDER_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLNode //(the capslock section is referenced in the cmake lists.
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
  //// friend class qslicer_CIVM_GalleryControlModule;// maybe?
  typedef std::map<std::string,std::string> std_str_hash ;
 public:
/// Create a new vtkMRMLNDLibraryBuilder
  //static vtkMRMLNDLibraryBuilder *New();

#ifndef storable
  typedef vtkMRMLNode Superclass;//instead usetype macro
#else 
  //typedef vtkMRMLStorableNode Superclass;//instead usetype macro
#endif
  ////
  // *constructors
  vtkMRMLNDLibraryBuilder(void);
  //vtkMRMLNDLibraryBuilder(vtkMRMLNDLibraryNode * libPointer=0);
  vtkMRMLNDLibraryBuilder(std::string);
  ~vtkMRMLNDLibraryBuilder(void);


  //these two are required for any mrmlnode
  vtkMRMLNode* CreateNodeInstance() ;
  virtual const char* GetNodeTagName() {return "NDLibraryBuilder";};

#ifdef storable
  vtkTypeMacro(vtkMRMLNDLibraryBuilder,vtkMRMLStorableNode);

  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetClassNameInternal() {return "NDLibraryBuilder";};

  void PrintSelf(ostream& os, vtkIndent indent);
  void SetSlicerDataType ( const char *type) ;

  void ReadXMLAttributes (const char **atts);
  void WriteXML (ostream &of, int indent);
  void StorableModified ();
  bool GetModifiedSinceRead();
  //vtkMRMLStorageNode * CreateDefaultStorageNode(void);
  void ProcessMRMLEvents (vtkObject *, unsigned long, void *);
  void UpdateScene (vtkMRMLScene *scene);
#endif
  ////
  //accessors
  vtkSetMacro(LibPointer,vtkMRMLNDLibraryNode *);
  
  // differnet builder funtions
  // return true on success with work done or false for no work done(or fail)
  bool Build(void);         // build our currently set lib
  bool Build(std::string);  // build an nd lib which must be set before hand in our ndlib pointer.

  bool Build(std_str_hash); // build an nd lib which must be set before hand in our ndlib pointer using a tag cloud at string.
  bool Build(vtkMRMLNDLibraryNode *, std_str_hash);   // build an nd lib using a tag cloud at string.
  
  bool Build(vtkMRMLNDLibraryNode *);                                      // build the nd lib, which presumeable has alredy had its path name and category set.
  bool Build(vtkMRMLNDLibraryNode *,std::string);                          // build lib at path,
  bool Build(vtkMRMLNDLibraryNode *,std::string,std::string );             // build lib at path with name
  bool Build(vtkMRMLNDLibraryNode *,std::string,std::string,std::string ); // build lib at path with name and category
  
  void ResetLib();   // clear out the lib
  bool ReBuild();    // rebuild the lib(first resets)
  
 protected:
  vtkMRMLNDLibraryBuilder(vtkMRMLNDLibraryBuilder &);
  void operator=(vtkMRMLNDLibraryBuilder const & ) ; 
 private:
  vtkMRMLNDLibraryNode * LibPointer;
  //vtkMRMLNDLibraryBuilder(const vtkMRMLNDLibraryBuilder&);//Not implemented
  void GetFilesInDirectory(std::vector<std::string> &, const std::string &);
  void GetSubCont(std::vector<std::string> * , std::string ,std::vector<std::string> *, int) ;  
  // core of get subdirs and get sub files, pass output pointer, path, exclusion list and, flag for get sub files, or get sub dirs
  void GetSubDirs(std::vector<std::string> * , std::string ) ; 
  void GetSubFiles(std::vector<std::string> * , std::string ) ; 
  void GetSubCategoryies(std::vector<std::string> * , std::string ) ; // temporary placeholder for planning purposes.
  std::vector<std::string> &split(const std::string &, char, std::vector<std::string> &);
  std::vector<std::string> split(const std::string &, char);
  std::string AgeTimeConvert(std::string zeroPadSeconds);
  std::string AgeTimeConvert(std::string zeroPadSeconds,float tollerance);

  std_str_hash libFileRead(vtkMRMLNDLibraryNode * lib);
  bool fexists(const char *);
  //enum STR2INT_ERROR { SUCCESS, OVERFLOW, UNDERFLOW, INCONVERTIBLE };
  //STR2INT_ERROR
  // int str2int (int &i, char const *s, int base = 0);
  std::string join(std::vector<std::string> &stringList , const std::string &s );

  bool confCheck (std::string );
  
};

#endif
