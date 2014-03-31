// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
//vtkMRMLNDLibrarayBuilder
// node to build a conter of information related to alibrary of data.
// this will abstract building from the container so we can change the libtary information storage system painlessly in the future



#ifndef __vtkMRMLNDLibraryBuilder_h
#define __vtkMRMLNDLibraryBuilder_h


// MRML includes
#include "vtkMRML.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLStorableNode.h"
#include "vtkMRMLNDLibraryNode.h"
// StdIncludes
#include <string>
#include <map>


//VTK_SLICER_VOLUMERENDERING_MODULE_MRML_EXPORT
//should change inherritance to vtkmrmlnode.h
//class VTK_EXPORT vtkMRMLNDLibraryBuilder //: public vtkMRMLNode
class VTK_MRML_EXPORT vtkMRMLNDLibraryBuilder : public vtkMRMLStorableNode
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
  //// friend class qslicer_CIVM_GalleryControlModule;// maybe?
  typedef std::map<std::string,std::string> std_str_hash ;
 public:
/// Create a new vtkMRMLNDLibraryBuilder
  //static vtkMRMLNDLibraryBuilder *New();
  //typedef vtkMRMLStorableNode Superclass;//instead usetype macro
  vtkTypeMacro(vtkMRMLNDLibraryBuilder,vtkMRMLStorableNode);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  void SetSlicerDataType ( const char *type) ;
  vtkMRMLNode* CreateNodeInstance() ;
  vtkSetMacro(LibPointer,vtkMRMLNDLibraryNode *);    
  //void SetLibPointer(vtkMRMLNDLibraryNode * ) ;
  
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "NDLibraryBuilder";};
  virtual const char* GetClassNameInternal() {return "NDLibraryBuilder";};

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
