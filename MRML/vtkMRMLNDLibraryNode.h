// james cook
// Center for InVivo Microscopy,  Duke Universtiy North Carolina
// ~2014 
// vtkMRMLNDLibrarayNode
// node to hold onto information related to a library of data.
// 
// inital planning will be done with hardcoded libraries 
// later expand to use a directory listing 
// eventually use a database


#ifndef __vtkMRMLNDLibraryNode_h
#define __vtkMRMLNDLibraryNode_h

// MRML includes
//#include "vtkMRML.h"
#include <vtkMRMLHierarchyStorageNode.h>

// StdIncludes
#include <string>
#include <vector>
#include <map>



//// EXAMPLE from vtkSlicerCIVM_GalleryControlModuelLogic.h
/* #include "vtkSlicerCIVM_GalleryControlModuleLogicExport.h" */

/* /// \ingroup Slicer_QtModules_ExtensionTemplate */
/* class VTK_SLICER_CIVM_GALLERYCONTROL_MODULE_LOGIC_EXPORT vtkSlicerCIVM_GalleryControlLogic : */
/* public vtkSlicerModuleLogic */
/* { */
//// END EXAMPLE


//VTK_SLICER_MODULE_MRML_EXPORT
//class VTK_MRML_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // fail
//class VTK_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // works
//class VTK_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode //works
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MODULE_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
#include "vtkMRMLNDLibraryNodeExport.h"//works
class VTK_VTKMRMLNDLIBRARYNODE_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode//works(the capslock section is referenced in the cmake lists.
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
  //// friend class qslicer_CIVM_GalleryControlModule;// maybe?
  friend class vtkMRMLNDLibraryBuilder;
 public:
/// Create a new vtkMRMLNDLibraryNode
  //static vtkMRMLNDLibraryNode *New();
  //typedef vtkMRMLHierarchyStorageNode Superclass;//instead usetype macro
  vtkTypeMacro(vtkMRMLNDLibraryNode,vtkMRMLHierarchyStorageNode);
  vtkMRMLNDLibraryNode(std::string);
  vtkMRMLNDLibraryNode(std::string,std::string );
  vtkMRMLNDLibraryNode(std::string,std::string,std::string );
  ~vtkMRMLNDLibraryNode(void);
  //void GatherSubLibs();  // Uses libroot and builds our library, recursively building a lib
                         // for each directory encountered and storing it to sublibraries.
                         // this is the builder class's job.
                         //   
  // this should be rename=repurposed to gather a map of name-path values.
  // * ndlibrary=GetSublibAtPath(path) should return pointer to ndlib to go from path to values for later modules.
  //  void GetSubDirs(std::vector<std::string> * , std::string ) ; 

  vtkSetMacro(LibRoot,std::string);    
  vtkGetMacro(LibRoot,std::string);    

  vtkSetMacro(LibName,std::string);    
  vtkGetMacro(LibName,std::string);

  vtkSetMacro(Category,std::string);    
  vtkGetMacro(Category,std::string);    
  
  vtkSetMacro(CurrentSelection,vtkMRMLNDLibraryNode *);
  vtkGetMacro(CurrentSelection,vtkMRMLNDLibraryNode *);

  vtkSetMacro(ParentNode,vtkMRMLNDLibraryNode *);
  vtkGetMacro(ParentNode,vtkMRMLNDLibraryNode *);
  //vtkGetObjectMacro(SubLibraries,);
  std::map<std::string,vtkMRMLNDLibraryNode *>  GetSubLibraries(void); 
  void ResetLibrary(void);
  void ResetLibrary(std::string);


  
  // moving away from the self populating lib in the future
  std::vector<std::string> * GetAllPaths();
  std::vector<std::map<std::string,std::string> > * GetLibTree(void); // 

  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "NDLibraryNode";};
  virtual const char* GetClassNameInternal() {return "NDLibraryNode";};

  vtkMRMLNode* CreateNodeInstance() ;
  //  virtual vtkMRMLNode * CreateNodeInstance()=0;
  //  virtual int IsA (const char *type);
  //  vtkTagTable * GetUserTagTable ();

  bool CanReadInReferenceNode(vtkMRMLNode * RefNode) {return false; };
  void PrintSelf(ostream& os, vtkIndent indent);
  void ReadXMLAttributes (const char **atts);
  void WriteXML (ostream &of, int indent);
  //  void SetSlicerDataType ( const char *type) ;
  //  void StorableModified ();
  bool GetModifiedSinceRead();
  //vtkMRMLHierarchyStorageNode * CreateDefaultStorageNode(void);
  void ProcessMRMLEvents (vtkObject *, unsigned long, void *);
  void UpdateScene (vtkMRMLScene *scene);
  
 protected:   
  std::string LibRoot;  // base path for the library
  std::string LibName;  // name displayed to user, the shortest unique name possible given the starting point of libroot. 
                        // names should encorporate the tag in each category the data belongs to that is distinct,
                        //  and where that category has more than one element populated.
  std::string Category; // the category our name belongs to, for example
                        // name is Brain, category is organ, 
                        // name is AdultRat, category is specimen. 
                        // name is Macaca_mulatta, category is species
  
  // dimensions and dimension tags should be filled out during the buildlibrary stage, reported back from the children. 
  std::map<std::string,int> Dimensions; // dimension(category)/ size map, 

  // valuemap...?
  //   for each dimesnsion(by name) a list of entries. 
  std::map<std::string,std::string> Dimension_tags;///maybe make vtkTagtable here:?

  //private vars
  vtkMRMLNDLibraryNode * ParentNode;  // holds pointer to our parent dataset for use when we've got a hierarchy so the gui knows where we are.
  vtkMRMLNDLibraryNode * CurrentSelection;  // holds our selected dataset for use when we've got a hierarchy so the gui knows where we are.
  std::map<std::string,vtkMRMLNDLibraryNode *> SubLibraries;


  vtkMRMLNDLibraryNode(void);
/*   void operator=(vtkMRMLStorageNode const & ) ; */

 private:
  void GetAllPaths(std::vector<std::string> *); // called for each sub library of a current library(recursively!) each adding their entries to the vector
  std::vector<std::string>* SubPaths(); // returns the list of sub libraries paths we need to continue building on.
  //std::vector<vtkMRMLNDLibraryNode *> * SubLibraries;
  //vtkMRMLNDLibraryNode(const vtkMRMLNDLibraryNode&);//Not implemented
  // helper functions
  //  void GetFilesInDirectory(std::vector<std::string> &, const std::string &);
  std::vector<std::string> &split(const std::string &, char, std::vector<std::string> &);
  std::vector<std::string> split(const std::string &, char);
  
};

#endif
