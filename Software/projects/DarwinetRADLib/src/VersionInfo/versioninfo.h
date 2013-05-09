//---------------------------------------------------------------------------

#ifndef VERSINFOH
#define VERSINFOH

// #include "DataRepresentationFrameWork.h"
#include "FilePathFramework.h"
#include "windows.h" // WORD
#include "ApplicationEnvironment.h" // c_ApplicationStrimg

//---------------------------------------------------------------------------

//=============================================================================
//  General component library for WIN32
//  Copyright (C) 2000, UAB BBDSoft ( http://www.bbdsoft.com/ )
//
// This material is provided "as is", with absolutely no warranty expressed
// or implied. Any use is at your own risk.
//
// Permission to use or copy this software for any purpose is hereby granted
// without fee, provided the above notices are retained on all copies.
// Permission to modify the code and to distribute modified code is granted,
// provided the above notices are retained, and a notice that the code was
// modified is included with the above copyright notice.
//
//  The author of this program may be contacted at developers@bbdsoft.com
//=============================================================================

/*
===============================================================================
Changes by ITfied AB

101111 KoH This file has been changed. Introduced application specific logging
		   use of std::strings and converted to whar_t usage.
		   Also getters has been added.
===============================================================================
*/

// #include <string>

typedef c_ApplicationString c_VersionInfoString;

class VersionInfo
{
public:

   VersionInfo (const c_FileName& sFilename);
   ~VersionInfo();

   bool hasInfo () const
		  {return m_pTheVersionInfo!=0 ;}

   unsigned short majorVersion () ;
   unsigned short minorVersion () ;
   unsigned short build () ;
   unsigned short subBuild () ;

   unsigned short productMajorVersion () ;
   unsigned short productMinorVersion () ;
   unsigned short productBuild () ;
   unsigned short productSubBuild () ;

   unsigned long fileFlagsMask() ;
   unsigned long fileFlags() ;
   unsigned long fileOS() ;
   unsigned long fileType() ;
   unsigned long fileSubType() ;

   /**
	 * returns the Comments as set
	 * in our version info
	 */
   c_VersionInfoString Comments() ;

   /**
	 * returns the Product name as set
	 * in our version info
	 */
   c_VersionInfoString ProductName() ;


   /**
	 * returns the LegalCopyright as set
	 * in our version info
	 */
   c_VersionInfoString LegalCopyright() ;

	/*
	Comments
	InternalName
	ProductName
	CompanyName
	LegalCopyright
	ProductVersion
	FileDescription
	LegalTrademarks
	PrivateBuild
	FileVersion
	OriginalFilename
	SpecialBuild
	*/


protected:
private:

	c_FileName m_sFilename;

	t_AppChar* m_pTheVersionInfo;
	unsigned long m_VersionInfoSize;

	void * m_pTheFixedInfo;

	/**
	 * Returns File Version Info memory block of current application exe file
	 */
	t_AppChar* getCurrentExeFileVersionInfo() ;

	/**
	 * Returns Size of File Version Info memory block of current application exe file
	 */
	int getCurrentExeFileVersionInfoSize() ;

	struct LANGANDCODEPAGE {
	  WORD wLanguage;
	  WORD wCodePage;
	};

	/**
	  * private storage of read Version info code page and language array
	  */
	LANGANDCODEPAGE* m_pVersionInfoCodePageAndLanguageArray;

	unsigned int m_VersionInfoCodePageAndLanguageArraySize;

	/**
	  * Returns the code page and language information array
	  * of current file version info
	  */
	LANGANDCODEPAGE* getVersionInfoCodePageAndLanguageArray();

	/**
	  * Returns size of the code page and language information array
	  * of current file version info
	  */
	unsigned int getVersionInfoCodePageAndLanguageArraySize();

	/**
	  * Returns the version info of provided index.
	  * Index <0 will return the fixed version info
	  */
	c_VersionInfoString readStringValueOfFileInfoOfIndex(const c_VersionInfoString& sValueName,unsigned int index);

	/**
	 * returns the value defined by provided name as
	 * set by our version info
	 */
	c_VersionInfoString readStringValue(const c_VersionInfoString& sValueName) ;

}; // end VersionInfo class declaration

#endif
