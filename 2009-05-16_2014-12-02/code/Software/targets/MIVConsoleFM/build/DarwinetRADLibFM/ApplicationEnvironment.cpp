//---------------------------------------------------------------------------

#pragma hdrstop

#include "ApplicationEnvironment.h"
#include "DataRepresentationFrameWork.h"
#include "ApplicationProperties.h"
#include "BusinessLogUnit.h"
#include "DateAndTimeFramework.h"
//#include "Forms.hpp" // Application instance
#include "versinfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Constructs a project using provided project root folder
  */
c_ApplicationProject::c_ApplicationProject(const c_FilePath& project_root_folder,const c_DataRepresentationFramework::c_UTF16String& sCaption)
	: m_project_root_folder(project_root_folder)
	  ,m_pPropertiesModel(NULL)
	  ,m_sCaption(sCaption)
{

}

/**
  * Returns the root folder path of this workspace
  */
c_FilePath& c_ApplicationProject::getRootPath() {
	return this->m_project_root_folder;
}

/**
  * Returns this project properties, creating it from file
  * in project folder if it does not yet exist.
  */
c_ApplicationPropertiesModel* const c_ApplicationProject::getProperties() {
	if (this->m_pPropertiesModel == NULL) {
		// Create it
//		this->m_pPropertiesModel = new c_ApplicationPropertiesModel(this->m_sCaption);
//		this->m_pPropertiesModel->loadProperties(this->getRootPath());

		this->m_pPropertiesModel = new c_ApplicationProperties(this->m_sCaption);

		try {
			// Load properties from current Application root
			this->m_pPropertiesModel->loadProperties(c_Application::getExeRootPath());
		}
		catch (...) {
			c_DataRepresentationFramework::c_UTF16String sMessage(L"Load of Applciation properties from \"");
			sMessage += this->m_pPropertiesModel->getPersistentStoragePath().toString();
			sMessage.anonymous() += L"\". Will create file.";
			LOG_BUSINESS(sMessage);
			// File may not exist. Create it.
			this->m_pPropertiesModel->saveProperties();
		}
	}
	return this->m_pPropertiesModel;
}

/**
  * Saves all data to persistent storage. Will call
  * child components to do the same.
  */
void c_ApplicationProject::saveEnvironment() {
	if (this->m_pPropertiesModel != NULL) {
		this->m_pPropertiesModel->saveProperties();
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Creates a workspace using the provided root path
  * as the root folder defining the work space.
  */
c_ApplicationWorkSpace::c_ApplicationWorkSpace(c_FilePath workspace_root_path)
    :  m_workspace_root_path(workspace_root_path)
      ,m_pCurrentProject(NULL)
{

}

/**
  * Returns the root folder path of this workspace
  */
c_FilePath& c_ApplicationWorkSpace::getRootPath() {
	return this->m_workspace_root_path;
}

/**
  * Sets Application to use within current workspace.
  * Will use a default work space if none has been set.
  */
void c_ApplicationWorkSpace::setCurrentProject(const c_DataRepresentationFramework::c_UTF16String& sApplicationRootFolderName) {
	if (m_pCurrentProject != NULL) {
		delete m_pCurrentProject;
		m_pCurrentProject = NULL;
	}

	c_FilePath test_bench_root_folder = this->getRootPath();
	if (sApplicationRootFolderName.length() == 0) {
		test_bench_root_folder += u"default";
	}
	else {
		test_bench_root_folder += sApplicationRootFolderName;
	}

	m_pCurrentProject = new c_ApplicationProject(test_bench_root_folder,sApplicationRootFolderName);
}

//---------------------------------------------------------------------------
/**
  * Returns current set Application.
  * If none is set the default Application will be used.
  */
c_ApplicationProject* c_ApplicationWorkSpace::getCurrentProject() {
	if (this->m_pCurrentProject == NULL) {
		this->setCurrentProject(c_DataRepresentationFramework::c_UTF16String(L"")); // Use work space folder as Project folder
	}
	return m_pCurrentProject;
}

//---------------------------------------------------------------------------
/**
  * Saves all data to persistent storage. Will call
  * child components to do the same.
  */
void c_ApplicationWorkSpace::saveEnvironment() {
	if (this->m_pCurrentProject != NULL) {
		this->getCurrentProject()->saveEnvironment();
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Returns the root path to this frame work.
  */
c_FilePath c_ApplicationFrameWork::getRootPath() {
	return this->m_framework_root_path;
}

/**
  * Saves all data to persistent storage. Will call
  * child components to do the same.
  */
void c_ApplicationFrameWork::saveEnvironment() {
}

//---------------------------------------------------------------------------
/**
  * constructor taking root path to framework root folder.
  * As of 071025 the exe run time folder.
  * TODO: Considder to merge run time environment class and this class!
  */
c_ApplicationFrameWork::c_ApplicationFrameWork(c_FilePath framework_root_path)
	: m_framework_root_path(framework_root_path)
{

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Returns singleton instance, creating it if it not yet done.
  */
c_ApplicationRunTimeEnvironent* c_ApplicationRunTimeEnvironent::instance() {
	if (m_pInstance == NULL) {
		m_pInstance = new c_ApplicationRunTimeEnvironent();
	}
	return m_pInstance;
}

/**
  * Sets the workspace to use
  */
void c_ApplicationRunTimeEnvironent::setWorkSpace(c_FilePath workspace_root_path) {
	if (this->m_pCurrentWorkSpace != NULL) {
		delete this->m_pCurrentWorkSpace;
	}
	this->m_pCurrentWorkSpace = new c_ApplicationWorkSpace(workspace_root_path);
}
//---------------------------------------------------------------------------
/**
  * Returns current set workspace.
  * Will create a deafult work space if none exists
  */
c_ApplicationWorkSpace* c_ApplicationRunTimeEnvironent::getCurrentWorkSpace() {
	if (this->m_pCurrentWorkSpace == NULL) {
		// Read the path to the work space from the run time environment properties
		// TODO 090508 - read path from run time environment properties
		//               setting a default one if none exists yet.

		// Use our frame work as work space folder
		this->setWorkSpace(this->getRootPath());
	}
	return this->m_pCurrentWorkSpace;
}

//---------------------------------------------------------------------------
/**
  * Returns the property model for the run time environment.
  * WIll be created and loaded from file if not yet done.
  */
c_ApplicationPropertiesModel* c_ApplicationRunTimeEnvironent::getProperties() {
	if (this->m_RunTimePropertiesModel == NULL) {
		// Create it
		this->m_RunTimePropertiesModel = new c_ApplicationPropertiesModel(c_Application::ExeName().NameWithoutExtension());
		this->m_RunTimePropertiesModel->loadProperties(this->getRootPath());
	}
	return this->m_RunTimePropertiesModel;
}


//---------------------------------------------------------------------------
/**
  * Returns the set frame work to be used by this run time environment.
  * The run time environment is defined by a property file found in the same
  * directory as the application exe file.
  */
c_ApplicationFrameWork* c_ApplicationRunTimeEnvironent::getApplicationFrameWork() {
	if (this->m_pApplicationFrameWork == NULL) {
		this->m_pApplicationFrameWork = new c_ApplicationFrameWork(this->getRootPath());
	}
	return this->m_pApplicationFrameWork;
}

/**
  * Returns path to work space folder
  */
c_FilePath c_ApplicationRunTimeEnvironent::getWorkSpaceFolderPath() {
//    if (this->m_WorkSpaceFolderPath.toStdString().size()==0) {
	if (this->m_WorkSpaceFolderPath.size()==0) {
		// No path set. Use current run time environment root path as work space
		this->m_WorkSpaceFolderPath = this->getRootPath();
	}
	return this->m_WorkSpaceFolderPath;
}


/**
  * Returns path to this application root directory,
  * i.e the directory of the exe file.
  */
const c_FilePath& c_ApplicationRunTimeEnvironent::getRootPath() {
//	return m_ExeFilePath;
	return m_ExeFolderPath;
}

/**
  * Saves all data to persistent storage. Will call
  * child components to do the same.
  */
void c_ApplicationRunTimeEnvironent::saveEnvironment() {
	if (this->m_pApplicationFrameWork != NULL) {
		this->getApplicationFrameWork()->saveEnvironment();
	}
	if (this->m_pCurrentWorkSpace != NULL) {
		this->getCurrentWorkSpace()->saveEnvironment();
	}
}

//---------------------------------------------------------------------------
/**
  * Short-cut to current Project.
  */
c_ApplicationProject* c_ApplicationRunTimeEnvironent::getCurrentProject() {
	return this->getCurrentWorkSpace()->getCurrentProject();
}

//---------------------------------------------------------------------------
/**
  * Private constructor of this singleton
  */
c_ApplicationRunTimeEnvironent::c_ApplicationRunTimeEnvironent()
	: m_pCurrentWorkSpace(NULL)
//	  ,m_ExeFilePath(c_Application::getExeRootPath())
	  ,m_ExeFolderPath(c_Application::getExeRootPath())
	  ,m_pApplicationFrameWork(NULL)
	  ,m_RunTimePropertiesModel(NULL)
{

}
/**
  * Private storage of singleton instance
  */
c_ApplicationRunTimeEnvironent* c_ApplicationRunTimeEnvironent::m_pInstance = NULL;
//------------------------------------------------------------------------------

// TODO 130930, Replace with code that works in Windows 7 and 8 to.
// See: ms-help://embarcadero.rs_xe2/codeexamples/VCL.VersionInfo_Sample.html
/**
  * Models a singleton that provides access to this application
  * version info (Windows property of executable file)
  */
class c_VersionInfo : public VersionInfo {
public:

	/**
	  * Returns this singleton instance,
	  * creating it if it does not yet exist.
	  */
	static c_VersionInfo* instance() {
		if (m_pInstance == NULL) {
			m_pInstance = new c_VersionInfo();
		}
		return m_pInstance;
	}

private:

	/**
	  * Private constructor of this singleton
	  */
	c_VersionInfo() : VersionInfo(c_Application::ExeName())
	{
		if (!this->hasInfo()) {
			// Failed to retreive version info
			LOG_DESIGN_INSUFFICIENCY(_UTF8sz("c_VersionInfo failed to retreive version info for this application."));
		}
	};

	/**
	  * Private storage of this singleton instance
	  */
	static c_VersionInfo* m_pInstance;

};

/**
  * Definition of Version info singleton instance
  */
c_VersionInfo* c_VersionInfo::m_pInstance = NULL;

//------------------------------------------------------------------------------
/**
  * Returns the file path to current Application exectution folder
  */
c_FilePath c_Application::getExeRootPath() {
#ifdef INC_FMX
	// 141202, Getting root path of Application not yet implemented for FireMonkey
	//         Note that FireMonkey is multi platfrom and the local file system
	//         Differs (there may not even be a path to the "exe" file).
	c_FilePath result(u"??c_Application::getExeRootPath??");
//	We can't call LOG_NOT_IMPLEMENTED here as the Logger will try to open the log file using the path we return (eternal loop created)
	return result;
#else
	c_FilePath result(c_DataRepresentationFramework::c_UTF16String(ExtractFileDir(Application->ExeName).c_str()));
	return result;
#endif
}

///**
//  * Returns the name of this exe file.
//  */
//const c_DataRepresentationFramework::c_UTF16String c_Application::ExeName() {
//	c_DataRepresentationFramework::c_UTF16String result(ExtractFileName(Application->ExeName).c_str());
//	return result;
//}

/**
  * Returns the name of this exe file.
  */
const c_FileName c_Application::ExeName() {
#ifdef INC_FMX
	// 141202, Getting root path of Application not yet implemented for FireMonkey
	//         Note that FireMonkey is multi platfrom and the local file system
	//         Differs (there may not even be a path to the "exe" file).
	c_FileName result(u"c_FileName c_Application::ExeName()");
//	We can't call LOG_NOT_IMPLEMENTED here as the Logger will try to open the log file using the path we return (eternal loop created)
	return result;
#else
	c_FileName result(_UTF16sz(ExtractFileName(Application->ExeName).c_str()));
	return result;
#endif
}

/**
  * Returns this application version info product name field contents
  */
const c_DataRepresentationFramework::c_UTF16String c_Application::getVersionInfoProductName() {
	c_DataRepresentationFramework::c_UTF16String result = u"??";

	if (c_VersionInfo::instance()->hasInfo()) {
		result = c_VersionInfo::instance()->ProductName();
	}
	return result;
}

/**
  * Returns this application version info Version field contents
  */
const c_DataRepresentationFramework::c_UTF16String c_Application::getVersionInfoVersion() {
	c_DataRepresentationFramework::c_UTF16String result = u"??";

	if (c_VersionInfo::instance()->hasInfo()) {
		result = c_DataRepresentationFramework::intToDecimalString(c_VersionInfo::instance()->majorVersion());
		result += u".";
		result += c_DataRepresentationFramework::intToDecimalString(c_VersionInfo::instance()->minorVersion());
		result += u".";
		result += c_DataRepresentationFramework::intToDecimalString(c_VersionInfo::instance()->build());
		result += u".";
		result += c_DataRepresentationFramework::intToDecimalString(c_VersionInfo::instance()->subBuild());
	}
	return result;
}

/**
  * Returns this application version info Copyright field contents
  */
const c_DataRepresentationFramework::c_UTF16String c_Application::getVersionInfoCopyRight() {
	c_DataRepresentationFramework::c_UTF16String result = u"??";

	if (c_VersionInfo::instance()->hasInfo()) {
		result = c_VersionInfo::instance()->LegalCopyright();
	}
	return result;
}
/**
  * Returns this application version info Comments field contents
  */
const c_DataRepresentationFramework::c_UTF16String c_Application::getVersionInfoComments() {
	c_DataRepresentationFramework::c_UTF16String result = u"??";

	if (c_VersionInfo::instance()->hasInfo()) {
		result = c_VersionInfo::instance()->Comments();
	}
	return result;
}

/**
  * returns the Date and time when this application was built
  */
c_DataRepresentationFramework::c_UTF16String c_Application::getBuildVersionAndDateAndTimeString() {
	c_DataRepresentationFramework::c_UTF16String result(c_Application::getVersionInfoVersion());

	static c_DataRepresentationFramework::c_UTF16String BUILD_DATE_AND_TIME_STRING =  u" Build:" __DATE__ u"  " __TIME__;

	result += BUILD_DATE_AND_TIME_STRING;

//	VersionInfo anInfo(c_Application::ExeName());
//	String sVersion = "Version: ";
//	if (anInfo.hasInfo()) {
//		sVersion += anInfo.majorVersion();
//		sVersion += ".";
//		sVersion += anInfo.minorVersion();
//		sVersion += ".";
//		sVersion += anInfo.build();
//		sVersion += ".";
//		sVersion += anInfo.subBuild();
//	}
//	else {
//		LOG_DESIGN_INSUFFICIENCY(_Literalsz("TAboutBox::getBuildVersionAndDateAndTimeString, failed to retreive version information"));
//		sVersion += "??";
//	}
//
//	static String BUILD_DATE_AND_TIME_STRING = sVersion + " Build:" __DATE__ "  " __TIME__;
//
//	return BUILD_DATE_AND_TIME_STRING;
	return result;
}

