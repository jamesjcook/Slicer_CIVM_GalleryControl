// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibrarayBuilder
// node to build a conter of information related to alibrary of data.
// this will abstract building from the container so we can change the libtary information storage system painlessly in the future



#ifndef __vtkMRMLNDLibraryBuilder_h
#define __vtkMRMLNDLibraryBuilder_h


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
//class VTK_VTKMRMLNDLIBRARYBUILDER_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode//works(the capslock section is referenced in the cmake lists.
class VTK_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLNode
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
  //// friend class qslicer_CIVM_GalleryControlModule;// maybe?
  typedef std::map<std::string,std::string> std_str_hash ;
 public:
/// Create a new vtkMRMLNDLibraryBuilder
  //static vtkMRMLNDLibraryBuilder *New();
  //typedef vtkMRMLStorableNode Superclass;//instead usetype macro
#ifndef storable
  typedef vtkMRMLNode Superclass;//instead usetype macro
#endif

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

  vtkSetMacro(LibPointer,vtkMRMLNDLibraryNode *);
  vtkMRMLNDLibraryBuilder(void);
  //vtkMRMLNDLibraryBuilder(vtkMRMLNDLibraryNode * libPointer=0);
  vtkMRMLNDLibraryBuilder(std::string);
  ~vtkMRMLNDLibraryBuilder(void);
  
  // differnet builder funtions
  // return true on success or false on fail
  //bool Build(void);
  bool Build(std::string);  // build an nd lib which must be set before hand in our ndlib pointer using a tag cloud at string.
  bool Build(std_str_hash); // build an nd lib which must be set before hand in our ndlib pointer using a tag cloud at string.
  bool Build(vtkMRMLNDLibraryNode *, std_str_hash);   // build an nd lib using a tag cloud at string.
  bool Build(vtkMRMLNDLibraryNode *);                                      // build the nd lib, which presumeable has alredy had its path name and category set.
  bool Build(vtkMRMLNDLibraryNode *,std::string);                          // build lib at path,
  bool Build(vtkMRMLNDLibraryNode *,std::string,std::string );             // build lib at path with name
  bool Build(vtkMRMLNDLibraryNode *,std::string,std::string,std::string ); // build lib at path with name and category

  
 protected:
  
 private:
  vtkMRMLNDLibraryNode * LibPointer;
  //vtkMRMLNDLibraryBuilder(const vtkMRMLNDLibraryBuilder&);//Not implemented
  void GetFilesInDirectory(std::vector<std::string> &, const std::string &);
  void GetSubDirs(std::vector<std::string> * , std::string ) ; 
  void GetSubCategoryies(std::vector<std::string> * , std::string ) ; // temporary placeholder for planning purposes.
  


  
};

#endif
