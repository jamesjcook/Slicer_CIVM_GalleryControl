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

typedef std::map<std::string,std::string> std_str_hash ; // maybe i should declare as a pointer?
typedef std_str_hash::iterator s_hash_iter;


//// EXAMPLE from vtkSlicerCIVM_GalleryControlModuelLogic.h
/* #include "vtkSlicerCIVM_GalleryControlModuleLogicExport.h" */

/* /// \ingroup Slicer_QtModules_ExtensionTemplate */
/* class VTK_SLICER_CIVM_GALLERYCONTROL_MODULE_LOGIC_EXPORT vtkSlicerCIVM_GalleryControlLogic : */
/* public vtkSlicerModuleLogic */
/* { */
//// END EXAMPLE


//VTK_SLICER_MODULE_MRML_EXPORT
/*
#include "vtkMRMLNDLibraryNodeExport.h"//works
//#include "vtkMRMLNDLibraryExport.h"//works
//class VTK_MRML_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // fail
//class VTK_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // works
//class VTK_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode //works
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MODULE_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
//class VTK_SLICER_CIVM_GALLERYCONTROL_MODULE_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode//fails
class VTK_VTKMRMLNDLIBRARYNODE_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode//works(the capslock section is referenced in the cmake lists.
*/

//VTK_SLICER_MODULE_MRML_EXPORT
#include "vtkMRMLNDLibraryExport.h"//works
//class VTK_MRML_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // fail
//class VTK_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode // works
//class VTK_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode //works
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
//class VTK_SLICER_VTKMRMLNDLIBRARYNODE_MODULE_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode
//class VTK_SLICER_CIVM_GALLERYCONTROL_MODULE_LOGIC_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode//fails
class VTK_VTKMRMLNDLIBRARY_MRML_EXPORT vtkMRMLNDLibraryNode : public vtkMRMLHierarchyStorageNode//works(the capslock section is referenced in the cmake lists.
{
  // declare friends
  // friend class qslicer_CIVM_GalleryControlModule;// maybe?
  //// friend class qslicer_CIVM_GalleryControlModule;// maybe?
  friend class vtkMRMLNDLibraryBuilder;
 public:
/// Create a new vtkMRMLNDLibraryNode
  static vtkMRMLNDLibraryNode *New();
  //typedef vtkMRMLHierarchyStorageNode Superclass;//instead usetype macro
  //constructors
  vtkTypeMacro(vtkMRMLNDLibraryNode,vtkMRMLHierarchyStorageNode);
  vtkMRMLNDLibraryNode(void);
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


  ////
  // Accessors
  //   GETSET macros
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

  vtkGetMacro(isLeaf,bool);


  //problems with get tag cloud no matter how i use once we get to qt. 
  // creating custom accessors to address issue.
  //vtkSetMacro(TagCloud,std_str_hash *);
  // proabbly should make this do some kinda deep copy operation... maybe the macro can handle that? dont need it right away so we'll skip for now.
  //vtkGetMacro(TagCloud,std_str_hash *);
  std_str_hash GetTagCloud();
  void SetTagCloud(  std_str_hash tagCloud);

  std::map<std::string,vtkMRMLNDLibraryNode *>  GetSubLibraries(void); 
  std::vector<vtkMRMLNDLibraryNode * >          GetAncestorList(void);
  std::vector<std::string>                      GetCategoryPath(void);
  

  //public functions
  // perhaps these reset functions should be private? and only called by our builder?
/*   void ResetLibrary(void); */
/*   void ResetLibrary(std::string);  //reset lib using path sent in. */
  
  // moving away from the self populating lib in the future
/*   std::vector<std::string> * GetAllPaths(); */
  std::vector<std::map<std::string,std::string> > * GetLibTree(void); 


  /// required virtuals
  vtkMRMLNode* CreateNodeInstance() ;
  virtual const char* GetNodeTagName() {return "NDLibraryNode";};
  virtual const char* GetClassNameInternal() {return "NDLibraryNode";};

  //  virtual int IsA (const char *type);
  //  vtkTagTable * GetUserTagTable ();
  void PrintSelf(ostream& os, vtkIndent indent);
#ifdef storable

  bool CanReadInReferenceNode(vtkMRMLNode * RefNode) {return false; };

  void ReadXMLAttributes (const char **atts);
  void WriteXML (ostream &of, int indent);
  //  void SetSlicerDataType ( const char *type) ;
  //  void StorableModified ();
  bool GetModifiedSinceRead();
  //vtkMRMLHierarchyStorageNode * CreateDefaultStorageNode(void);
  void ProcessMRMLEvents (vtkObject *, unsigned long, void *);
  void UpdateScene (vtkMRMLScene *scene);
#endif

 protected:   
  std::string LibRoot;  // base path for the library
  std::string LibName;  // name displayed to user, the shortest unique name possible given the starting point of libroot. 
                        // names should encorporate the tag in each category the data belongs to that is distinct,
                        //  and where that category has more than one element populated.
  std::string Category; // the category our name belongs to, for example
                        // name is Brain, category is organ, 
                        // name is AdultRat, category is specimen. 
                        // name is Macaca_mulatta, category is species
  std_str_hash TagCloud; // pointer to a tag cloud. Lets dump the contents of our lib.conf there for now.
  // Still unsre how to use/set these fields, they will reamain blank for now. 
  // dimensions and dimension tags should be filled out during the buildlibrary stage, reported back from the children. 
  std::map<std::string,int> Dimensions; // dimension(category)/ size map, 
  // valuemap...?
  //   for each dimesnsion(by name) a list of entries. 
  std_str_hash Dimension_tags;///maybe make vtkTagtable here:? //should substitue std_str_hash in for the std::map<std::string,std::string>
  void operator=(vtkMRMLNDLibraryNode const & ) ; 



  void clearSubs(void);      //a clear self function.... for each sub , calls clear on sub, then calls delete on subour subs, once subs are done clears sublibraries map.
  vtkMRMLNDLibraryNode(vtkMRMLNDLibraryNode &);



#ifdef modlogic
  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
#endif
 private:
  //private vars
  vtkMRMLNDLibraryNode * ParentNode;  // holds pointer to our parent dataset for use when we've got a hierarchy so the gui knows where we are.
  vtkMRMLNDLibraryNode * CurrentSelection;  // can hold our selected dataset for use when we've got a hierarchy so the gui knows where we are. this is a bad way to handle the selection problem!, changed to emit a selected signal with a anode pointer in our guis
  bool isLeaf;
  std::map<std::string,vtkMRMLNDLibraryNode *> SubLibraries;
  //  std::vector<std::string> * FilePaths;


  //void GetAllPaths(std::vector<std::string> *); // called for each sub library of a current library(recursively!) each adding their entries to the vector
  //std::vector<std::string>* SubPaths(); // returns the list of sub libraries paths we need to continue building on.
  //std::vector<vtkMRMLNDLibraryNode *> * SubLibraries;
  //vtkMRMLNDLibraryNode(const vtkMRMLNDLibraryNode&);//Not implemented
  // helper functions
  //  void GetFilesInDirectory(std::vector<std::string> &, const std::string &);
/*   std::vector<std::string> &split(const std::string &, char, std::vector<std::string> &); */
/*   std::vector<std::string> split(const std::string &, char); */
};

#endif
