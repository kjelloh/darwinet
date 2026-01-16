//---------------------------------------------------------------------------


#pragma hdrstop

#include "VERSINFO.h"
#include "BusinessLogUnit.h" // DESIGN_INSUFFICIENCY_LOG(...)

# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
# pragma warn +8072 // Enable again. See above

#include <mbctype.h> // Get multibyte code page method
//---------------------------------------------------------------------------

#pragma package(smart_init)

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

#ifndef _STDEXCEPT_
   #include "stdexcept"
#endif

#ifndef _WINDOWS_
   #define WIN32_LEAN_AND_MEAN
   #include <windows.h>
#endif

using namespace std;

//--------------------------------------------------------------------------------
VersionInfo::VersionInfo (const c_DataRepresentationFramework::c_UTF16String& sFilename)
   :  m_pTheVersionInfo (NULL)
	 ,m_VersionInfoSize(0)
	 ,m_pVersionInfoCodePageAndLanguageArray(NULL)
	 ,m_VersionInfoCodePageAndLanguageArraySize(0)
	 ,m_pTheFixedInfo (NULL)
	 ,m_sFilename(sFilename)
{
	this->m_VersionInfoSize = GetFileVersionInfoSize (sFilename.c_str(),&this->m_VersionInfoSize);
	if (this->m_VersionInfoSize > 0) {
	   m_pTheVersionInfo = new char [this->m_VersionInfoSize];
	   if (!GetFileVersionInfo ( sFilename.c_str()
							   , 0
							   , this->m_VersionInfoSize
							   , m_pTheVersionInfo
							   ) ) {
	//	  throw runtime_error ("VersionInfo: can not retrieve version information");
		  LOG_DESIGN_INSUFFICIENCY(_UTF8sz("VersionInfo: can not retrieve version information"));
	   } // endif
	   unsigned int aSize = 0;
	   if (!VerQueryValue( m_pTheVersionInfo
						 , L"\\"
						 , &m_pTheFixedInfo
						 , &aSize)) {
	//	  throw runtime_error ("VersionInfo: can not retrieve version information");
		  LOG_DESIGN_INSUFFICIENCY(_UTF8sz("VersionInfo: can not retrieve version information"));
	   } // endif
	} // endif
} // end constructor


//--------------------------------------------------------------------------------
VersionInfo::~VersionInfo ()
{
delete m_pTheVersionInfo;
} // end destructor


//--------------------------------------------------------------------------------
unsigned short VersionInfo::majorVersion () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwFileVersionMS >> 16);
} // end VersionInfo::majorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::minorVersion () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwFileVersionMS);
} // end VersionInfo::minorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::build () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwFileVersionLS >> 16);
} // end VersionInfo::build () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::subBuild () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwFileVersionLS);
} // end VersionInfo::subBuild () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productMajorVersion () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwProductVersionMS >> 16);
} // end VersionInfo::productMajorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productMinorVersion () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwProductVersionMS);
} // end VersionInfo::productMinorVersion () const


//--------------------------------------------------------------------------------
unsigned short VersionInfo::productBuild () {
if (!m_pTheFixedInfo) return 0;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwProductVersionLS >> 16);
} // end VersionInfo::productBuild () const

//--------------------------------------------------------------------------------
unsigned short VersionInfo::productSubBuild () {
if (!m_pTheFixedInfo) return 1;
VS_FIXEDFILEINFO * aInfo = (VS_FIXEDFILEINFO *) m_pTheFixedInfo;
return (aInfo -> dwProductVersionLS);
} // end VersionInfo::productSubBuild () const

/**
 * returns the Comments as set
 * in our version info
 */
c_DataRepresentationFramework::c_UTF16String VersionInfo::Comments() {
	c_DataRepresentationFramework::c_UTF16String result = this->readStringValue(u"Comments");
	return result;
}

/**
 * returns the Product name as set
 * in our version info
 */
c_DataRepresentationFramework::c_UTF16String VersionInfo::ProductName() {
	c_DataRepresentationFramework::c_UTF16String result = this->readStringValue(u"ProductName");
	return result;
}

/**
 * returns the LegalCopyright as set
 * in our version info
 */
c_DataRepresentationFramework::c_UTF16String VersionInfo::LegalCopyright() {
	c_DataRepresentationFramework::c_UTF16String result = this->readStringValue(u"LegalCopyright");
	return result;
}

/**
 * Returns Size of File Version Info memory block of current application exe file
 */
int VersionInfo::getCurrentExeFileVersionInfoSize() {
	if (this->m_VersionInfoSize == 0) {
		DWORD dummy;
		this->m_VersionInfoSize = GetFileVersionInfoSize (this->m_sFilename.c_str(),&dummy);
		if (this->m_VersionInfoSize <= 0) {
			// failed
			DWORD api_error_code = GetLastError();
			c_LogString sMessage = _Asciisz("VersionInfo::getCurrentExeFileVersionInfo() failed. GetFileVersionInfoSize returned error code ");
			sMessage += logStringOfWinApiErrorCode(api_error_code);
			throw std::runtime_error(sMessage.c_str());
		}
	}
	return this->m_VersionInfoSize;
}

/**
 * Returns File Version Info of current application exe file
 */
void* VersionInfo::getCurrentExeFileVersionInfo() {
	if (this->m_pTheVersionInfo == NULL) {
		// allocate memopry block and fill it with version information
		this->m_pTheVersionInfo = new char [this->getCurrentExeFileVersionInfoSize()];
		if (!GetFileVersionInfo ( this->m_sFilename.c_str()
							   , 0
							   , this->getCurrentExeFileVersionInfoSize()
							   , this->m_pTheVersionInfo
							   ) ) {
			throw runtime_error ("VersionInfo: can not retrieve version information");
		}
		else {
			// Success
			LOG_DEVELOPMENT_TRACE_I(_Asciisz("VersionInfo::getCurrentExeFileVersionInfo() returns memory block of size %d"),this->m_VersionInfoSize);
		}
	}
	return this->m_pTheVersionInfo;
}

/**
  * Returns the code page and language information array
  * of current file version info
  */
VersionInfo::LANGANDCODEPAGE* VersionInfo::getVersionInfoCodePageAndLanguageArray() {
	if (this->m_pVersionInfoCodePageAndLanguageArray == NULL) {
		// Read the list of languages and code pages.

		if (!VerQueryValue(this->getCurrentExeFileVersionInfo(),
					  TEXT("\\VarFileInfo\\Translation"),
					  (LPVOID*)&this->m_pVersionInfoCodePageAndLanguageArray,
					  &this->m_VersionInfoCodePageAndLanguageArraySize)) {

			c_LogString sMessage = _UTF8sz("VersionInfo::getVersionInfoCodePageAndLanguageArray() failed. VerQueryValue() returns false");
			throw std::runtime_error (sMessage.c_str());
		}
		else {
			// Success
		}
	}
	return this->m_pVersionInfoCodePageAndLanguageArray;
}

/**
  * Returns size of the code page and language information array
  * of current file version info
  */
unsigned int VersionInfo::getVersionInfoCodePageAndLanguageArraySize() {
	if (this->getVersionInfoCodePageAndLanguageArray() != NULL) {
		return this->m_VersionInfoCodePageAndLanguageArraySize;
	}
	else {
		c_LogString sMessage = _UTF8sz("VersionInfo::getVersionInfoCodePageAndLanguageArraySize() failed. this->getVersionInfoCodePageAndLanguageArray() returns NULL");
		throw std::runtime_error (sMessage.c_str());
	}
}

/**
  * Returns the version info of provided index.
  * Index <0 will return the fixed version info
  */
c_DataRepresentationFramework::c_UTF16String VersionInfo::readStringValueOfFileInfoOfIndex(const c_DataRepresentationFramework::c_UTF16String& sValueName,unsigned int index) {
	c_DataRepresentationFramework::c_UTF16String result((boost::wformat(L"#??%1%??#") % sValueName).str());

	unsigned int aSize = 0;
	if (index < (this->getVersionInfoCodePageAndLanguageArraySize()/sizeof(struct LANGANDCODEPAGE))) {
		LANGANDCODEPAGE* lpTranslate = this->getVersionInfoCodePageAndLanguageArray();

		// return part with provided index
		wchar_t* szValue;
		unsigned int length;
		c_DataRepresentationFramework::c_UTF16String sSubBlock((boost::wformat(L"\\StringFileInfo\\%04x%04x\\%s") % lpTranslate[index].wLanguage % lpTranslate[index].wCodePage % sValueName.c_str()).str());
	   if (!VerQueryValue( this->getCurrentExeFileVersionInfo()
						 , /* szSubBlock */ sSubBlock.c_str()
						 , reinterpret_cast<void**>(&szValue)
						 , &length)) {
			// Failed
			c_DataRepresentationFramework::c_UTF8String sMessage("VersionInfo::readStringValue failed to retreive value with name ");
			sMessage += c_DataRepresentationFramework::toUTF8String(sValueName);
			LOG_DESIGN_INSUFFICIENCY(sMessage);
	   }
	   else {
		   // Success
		   result.anonymous() = szValue;
	   }
	}
	else {
		// Index out of range
		c_LogString sMessage = _UTF8sz("VersionInfo::getVersionInfoCodePageAndLanguageArraySize() failed. this->getVersionInfoCodePageAndLanguageArray() returns NULL");
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}

	return result;
}

/**
 * returns the value defined by provided name as
 * set by our version info
 */
c_DataRepresentationFramework::c_UTF16String VersionInfo::readStringValue(const c_DataRepresentationFramework::c_UTF16String& sValueName) {
	// From URL: http://msdn.microsoft.com/en-us/library/ms647464(v=vs.85).aspx
	/*
	// Structure used to store enumerated languages and code pages.

	HRESULT hr;

	struct LANGANDCODEPAGE {
	  WORD wLanguage;
	  WORD wCodePage;
	} *lpTranslate;

	// Read the list of languages and code pages.

	VerQueryValue(pBlock,
				  TEXT("\\VarFileInfo\\Translation"),
				  (LPVOID*)&lpTranslate,
				  &cbTranslate);

	// Read the file description for each language and code page.

	for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
	{
	  hr = StringCchPrintf(SubBlock, 50,
				TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
				lpTranslate[i].wLanguage,
				lpTranslate[i].wCodePage);
		if (FAILED(hr))
		{
		// TODO: write error handler.
		}

	  // Retrieve file description for language and code page "i".
	  VerQueryValue(pBlock,
					SubBlock,
					&lpBuffer,
					&dwBytes);
	}
	*/

	c_DataRepresentationFramework::c_UTF16String result((boost::wformat(L"#%1%??#") % sValueName).str());

	WORD wLanguage = GetUserDefaultUILanguage(); // Use language set by current user

	WORD wCodePage = _getmbcp(); // Try to use current set multibyte code page
	if (wCodePage == 0) {
		wCodePage = 1252; // Code page used in sweden and western contries
		LOG_BUSINESS(_UTF8sz("No mutlibyte codepage is set. Will use default Code page 1252"));
	}

	wchar_t* szValue;
	unsigned int length;
//	sprintf(szSubBlock,"\\StringFileInfo\\%04x%04x\\%s",wLanguage,wCodePage,sValueName.c_str());
	c_DataRepresentationFramework::c_UTF16String sSubBlock((boost::wformat(L"\\StringFileInfo\\%04x%04x\\%s") % wLanguage % wCodePage % sValueName.c_str()).str());
   if (!VerQueryValue( this->getCurrentExeFileVersionInfo()
					 , /* szSubBlock */ sSubBlock.c_str()
					 , reinterpret_cast<void**>(&szValue)
					 , &length)) {
		// Failed
		c_DataRepresentationFramework::c_UTF8String sMessage("VersionInfo::readStringValue failed to retreive value with name ");
		sMessage += c_DataRepresentationFramework::toUTF8String(sValueName);
		LOG_DESIGN_INSUFFICIENCY(sMessage);

		// Try to read information from first found indexed information
		result = this->readStringValueOfFileInfoOfIndex(sValueName,0);
   }
   else {
	   // Success
	   result.anonymous() = szValue;
   }

	c_DataRepresentationFramework::c_UTF8String sMessage("VersionInfo::readStringValue for name ");
	sMessage += c_DataRepresentationFramework::toUTF8String(sValueName);
	sMessage.anonymous() += " returns ";
	sMessage += c_DataRepresentationFramework::toUTF8String(result);
	LOG_DEVELOPMENT_TRACE(sMessage);
	return result;
}

