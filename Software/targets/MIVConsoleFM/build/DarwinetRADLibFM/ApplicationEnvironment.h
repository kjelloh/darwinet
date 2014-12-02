//---------------------------------------------------------------------------

#ifndef ApplicationEnvironmentH
#define ApplicationEnvironmentH
#include "FilePathFramework.h" // c_FilePath
#include "ApplicationProperties.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * An Applciation environment defines a run time envrionment.
  * The run time environment defines two other environments.
  * 1) The frame work environment.
  * 2) The workspapce environment.
  *
  * The framework environment is the base of any framework needed
  * and/or used by the Application.
  *
  * The Workspace is the root to to the environment where the work data of
  * the applciation is processed.
  *
  * Runtime environment ==> Framework
  * Runtime environment ==> WorkSpace
  *
  * Runtime environment ==> Framework
  *							==> Framework 1
  *							==> Framework 2
  *							==> Framework n
  *
  * Runtime environment ==> WorkSpace
  * 						==> Project 1
  * 						==> Project 2
  * 						==> Project n
  */

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Models a base class of anapplication project.
  */
class c_ApplicationProject {
public:
	/**
	  * Constructs a project using provided project root folder
	  */
	c_ApplicationProject(const c_FilePath& project_root_folder, const c_DataRepresentationFramework::c_UTF16String& sCaption);

	/**
	  * Returns the root folder path of this workspace
	  */
	c_FilePath& getRootPath();

	/**
	  * Returns this project properties, creating it from file
	  * in project folder if it does not yet exist.
	  */
	c_ApplicationPropertiesModel* const getProperties();

	/**
	  * Saves all data to persistent storage. Will call
	  * child components to do the same.
	  */
	void saveEnvironment();

private:

	/**
	  * Provate storage of our project root folder
	  */
	c_FilePath m_project_root_folder;

	/**
	  * private storage of the name of this project
	  */
	c_DataRepresentationFramework::c_UTF16String m_sCaption;

	/**
	  * Private storage of our properties model instance
	  */
	c_ApplicationPropertiesModel* m_pPropertiesModel;

};

/**
  * Handles one ipos Application work space.
  * A work space defines a root for several Project setups
  * and a set of common setup values of that workspace.
  */
class c_ApplicationWorkSpace {
public:
	/**
	  * Creates a workspace using the provided root path
	  * as the root folder defining the work space.
	  */
	c_ApplicationWorkSpace(c_FilePath workspace_root_path);

	/**
	  * Returns the root folder path of this workspace
	  */
	c_FilePath& getRootPath();

	/**
	  * Sets Application to use within current workspace.
	  * Will use a default work space if none has been set.
	  */
	void setCurrentProject(const c_DataRepresentationFramework::c_UTF16String& sApplicationRootFolderName);

	/**
	  * Returns current set Application.
	  * If none is set the default Application will be used.
	  */
	c_ApplicationProject* getCurrentProject();

	/**
	  * Saves all data to persistent storage. Will call
	  * child components to do the same.
	  */
	void saveEnvironment();

private:

	c_FilePath m_workspace_root_path;

	/**
	  * Private storage of current set Project
	  */
	c_ApplicationProject* m_pCurrentProject;

};

//---------------------------------------------------------------------------
/**
  * The iPos test bench framework aggregates a number of artefacts
  * that is needed to have a complete working application with a running
  * and configured test bench, a messaging engine for ipos etc...
  * The frame work is defined by current run time environment.
  * Path: c_ApplicationFrameWork (1) ==> (1) c_ApplicationWorkSpace
  */
class c_ApplicationFrameWork {
public:

	/**
	  * constructor taking root path to framework root folder.
	  * As of 071025 the exe run time folder.
	  * TODO: Considder to merge run time environment class and this class!
	  */
	c_ApplicationFrameWork(c_FilePath framework_root_path);

	/**
	  * Returns the root path to this frame work.
	  */
	c_FilePath getRootPath();

	/**
	  * Saves all data to persistent storage. Will call
	  * child components to do the same.
	  */
	void saveEnvironment();

private:

	/**
	  * Private storage of root path of frame work.
	  * Normally the folder of the exe file
	  */
	c_FilePath m_framework_root_path;

};

//---------------------------------------------------------------------------
/**
  * Represents the run time environment of current application.
  * The run time environment has a work space set.
  * Path: c_ApplicationRunTimeEnvironent (1) ==> (1) c_ApplicationFrameWork
  */
class c_ApplicationRunTimeEnvironent {
public:
	/**
	  * Returns signleton instance, creating it if it not yet done.
	  */
	static c_ApplicationRunTimeEnvironent* instance();

	/**
	  * Sets the workspace to use
	  */
	void setWorkSpace(c_FilePath workspace_root_path);

	/**
	  * Returns current set workspace.
	  * Will create a deafult work space if none exists
	  */
	c_ApplicationWorkSpace* getCurrentWorkSpace();

	/**
	  * Returns the property model for the run time environment.
	  * Will be created and loaded from file if not yet done.
	  */
	c_ApplicationPropertiesModel* getProperties();

	/**
	  * Returns path to this application root directory,
	  * i.e the directory of the exe file.
	  */
	const c_FilePath& getRootPath();

	/**
	  * Returns the set frame work to be used by this run time environment.
	  * The run time environment is defined by a property file found in the same
	  * directory as the application exe file.
	  */
	c_ApplicationFrameWork* getApplicationFrameWork();

	/**
	  * Saves all data to persistent storage. Will call
	  * child components to do the same.
	  */
	void saveEnvironment();

	/**
	  * Short-cut to current Project.
	  */
	c_ApplicationProject* getCurrentProject();

private:

	/**
	  * Private constructor of this singleton
	  */
	c_ApplicationRunTimeEnvironent();

	/**
	  * Private storage of current set workspace
	  */
	c_ApplicationWorkSpace* m_pCurrentWorkSpace;


	/**
	  * Private storage of the properties model instance
	  * of this run time instance.
	  */
	c_ApplicationPropertiesModel* m_RunTimePropertiesModel;

	/**
	  * Private storage of set work space
	  */
	c_ApplicationFrameWork* m_pApplicationFrameWork;

	/**
	  * Returns path to work space folder
	  */
	c_FilePath getWorkSpaceFolderPath();

	/**
	  * Private storage os set work space folder path
	  */
	c_FilePath m_WorkSpaceFolderPath;

	/**
	  * Private storage of singleton instance
	  */
	static c_ApplicationRunTimeEnvironent* m_pInstance;

//	/**
//	  * Private storage of path to exe file of this application
//	  */
//	c_FilePath m_ExeFilePath;

	/**
	  * private storage of the root path of this application
	  * (the path to the folder of the exe-file)
	  */
	c_FilePath m_ExeFolderPath;

};

//---------------------------------------------------------------------------

/**
  * Provides static access to application general properties
  */
class PACKAGE c_Application {
public:
	/**
	  * Returns the file path to current Application exectution folder
	  */
	static c_FilePath getExeRootPath();

//	/**
//	  * Returns the name of this exe file.
//	  */
//	static const c_DataRepresentationFramework::c_UTF16String c_Application::ExeName();

	/**
	  * Returns the name of this exe file.
	  */
	static const c_FileName ExeName();

	/**
	  * Returns this application version info product name field contents
	  */
	static const c_DataRepresentationFramework::c_UTF16String getVersionInfoProductName();

	/**
	  * Returns this application version info Version field contents
	  */
	static const c_DataRepresentationFramework::c_UTF16String getVersionInfoVersion();

	/**
	  * Returns this application version info Copyright field contents
	  */
	static const c_DataRepresentationFramework::c_UTF16String getVersionInfoCopyRight();
	/**
	  * Returns this application version info Comments field contents
	  */
	static const c_DataRepresentationFramework::c_UTF16String getVersionInfoComments();

	/**
	  * returns the Version and Date and time when this application was built
	  */
	static c_DataRepresentationFramework::c_UTF16String getBuildVersionAndDateAndTimeString();


};

#endif
