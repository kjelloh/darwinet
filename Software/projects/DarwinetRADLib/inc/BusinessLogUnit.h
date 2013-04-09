/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef BusinessLogUnitH
#define BusinessLogUnitH
//---------------------------------------------------------------------------
// RAD Studio XE compilation
//---------------------------------------------------------------------------
#include <string>
#include <queue>
#include "DateAndTimeFramework.h" // c_YYYYMMDDHHMMSSmmmm
#include "DataRepresentationFrameWork.h"

/**
  * Defines preferred string to use in business logging
  */
typedef c_DataRepresentationFramework::c_UTF8String c_LogString;

/**
  * Converts same type to LogString. Provided to enable
  * Macros to work with all string types
  */
c_LogString toLogString(const c_LogString& sEntry);

/**
  * Converts provided UTF16 string to Log string representation
  */
c_LogString toLogString(const c_DataRepresentationFramework::c_UTF16String& sEntry);

///**
//  * Converts provided C++ literal string to Log string representation
//  */
//c_LogString toLogString(const c_DataRepresentationFramework::c_CppLiteralString& sEntry);

/**
  * Converts provided C++ literal string to Log string representation
  */
c_LogString toLogString(const c_DataRepresentationFramework::c_ISO_8859_1_String& sEntry);

#ifdef __BCPLUSPLUS__ // RAD Studio XE compilation
/**
  * Converts provided IDE string to Log string representation.
  * Will use compile time information to determine
  * representation of IDE string (UTF16, Ansi etc...)
  */
c_LogString toLogString(const String& sEntry);
#endif

#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
/**
  * Returns a log string with a text describing the menaing of provided Windows api error code.
  */
c_LogString logStringOfWinApiErrorCode(DWORD api_error_code);
#endif

#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
/**
  * Returns provided Windows HRESULKT code as a descriptive Log string
  */
c_LogString logStringOfWinApiHResultCode(HRESULT hresult);
#endif

enum e_BussinessLogEntryType {
	e_BussinessLogEntryType_DesignInsufficiency
	,e_BussinessLogEntryType_DevelopmentTrace
	,e_BussinessLogEntryType_Bussiness
};

class c_BussinessLogEntry {
public:
	/**
	  * Constructs a log entry form provided entry type and entry body
	  */
	c_BussinessLogEntry(e_BussinessLogEntryType entry_type,const c_LogString& sBody);

	/**
	  * Returns the type of this entry
	  */
	e_BussinessLogEntryType getType() const;

	/**
	  * Returns the formatted header of this entry
	  */
	c_LogString header() const;

	/**
	  * Returns the formatted body of this entry
	  */
	c_LogString body() const;

	/**
	  * Returns the whole entry formatted as a string
	  */
	c_LogString toString() const;

	/**
	  * Static helper method that returns provided e_BussinessLogEntryType as a string
	  */
	static c_LogString StringOfBussinessLogEntryType(e_BussinessLogEntryType entry_type);

private:
	/**
	  * Private storage of the type of this entry
	  */
	e_BussinessLogEntryType m_entry_type;

	/**
	  * Private storage of this entry body
	  */
	c_LogString m_sBody;

	/**
	  * Private storage of date and time of this entry
	  */
	c_YYYYMMDDHHMMSSmmm m_YYYYMMDDHHMMSSmmm;

	DWORD m_ThreadId;
};

/**
  * Interface to Business logger singleton.
  * The business log is to be used to log normal and exceptional
  * activities of the application operations.
  * Note: The Logger is exposed though this interface to separate
  * this header file from dependence of other units of the application.
  * This enables it to be included in other header files without causing
  * circular references and cause compiler errors.
  */
class c_BussinessLoggerIfc {
public:

	// Begin c_BussinessLoggerIfc

	/**
	  * Returns this singleton instance
	  */
	static c_BussinessLoggerIfc* instance();

	/**
	  * returns true if this instance has a record of unread
	  * entries of provided entry type.
	  */
	virtual bool thereIsUnreadEntriesOfType(e_BussinessLogEntryType entry_type) = 0;

	/**
	  * sets the "Unread" state for entries of provided type
	  */
	virtual void setUnreadEntriesStateOfType(e_BussinessLogEntryType entry_type,bool isSet) = 0;

	/**
	  * Design insufficiency log about a not implemented function/Method
	  * Will assume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	virtual void LogNotImplemented(const c_DataRepresentationFramework::c_CppLiteralString& sFunctionName) = 0;

	/**
	  * Design insufficiency log.
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(const c_LogString& sEntry) = 0;

	/**
	  * Design insufficiency log for UTF16 string.
	  * Will decode to string representation used by Business Log engine
	  */
	virtual void LogDesignInsufficiency(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) = 0;

	/**
	  * Design insufficiency log for  C++ String literal array.
	  * Will assume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	virtual void LogDesignInsufficiency(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) = 0;

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(const c_LogString& sEntry,int i1) = 0;

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(const c_LogString& sEntry,int i1,int i2) = 0;

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1) = 0;

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2) = 0;

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(const c_LogString& sEntry) = 0;

	/**
	  * Development trace log for UTF16 char array.
	  * Will decode to string represetnation used by Business Log engine
	  */
	virtual void LogDevelopmentTrace(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) = 0;

	/**
	  * Development trace log for C++ String literal string
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	virtual void LogDevelopmentTrace(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) = 0;

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(const c_LogString& sEntry,int i1) = 0;

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1) = 0;

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2) = 0;

	/**
	  * Logs an entry to a scope. szEntry is the name of the scope.
	  */
	virtual void LogScopeEntry(const c_LogString& sEntry) = 0;

	/**
	  * Business log used to log events of normal application
	  * execution. This Log is for released application execution logging.
	  */
	virtual void LogBussiness(const c_LogString& sEntry) = 0;

	/**
	  * Business log for UTF16 char array.
	  * Will decode to string representation used by Business Log engine
	  */
	virtual void LogBussiness(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) = 0;

	/**
	  * Development trace log for C++ String literal string
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	virtual void LogBussiness(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) = 0;

	/**
	  * Design insufficiency log of an object instance using an instance Id 0,1,2...
	  * Used to trace events where the application design
	  * is insufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	virtual void LogDesignInsufficiency(int instance_id,const c_LogString& sEntry) = 0;

	/**
	  * Development trace of an object instance using an instance Id 0,1,2...
	  * log used during development of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(int instance_id,const c_LogString& sEntry) = 0;

	/**
	  * Business log used to log events
	  * of normal application execution.
	  * This Log is for released application execution logging.
	  */
	virtual void LogBussiness(int instance_id,const c_LogString& sEntry) = 0;

	/**
	  * Returns next stored log entry from the log entry storage
	  * and removes it from the storage. Used by user interface to poll
	  * for entries that are to be shown in the user interface.
	  * Returns NULL if there are no entries to return.
	  */
	virtual c_BussinessLogEntry* popUILogEntry() = 0;

	/**
	  * Returns number of entries in the logger that is not popped
	  * for UI view.
	  */
	virtual int unPoppedUIEntriesCount() = 0;

	/**
	  * Increments the indentations used for development trace log entries
	  */
	virtual void incrementDevelopmentTraceIndent() = 0;

	/**
	  * Decrements the indentations used for development trace log entries
	  */
	virtual void decrementDevelopmentTraceIndent() = 0;

	// End c_BussinessLoggerIfc

private:

	/**
	  * Private storage if this singleton instance
	  */
	static c_BussinessLoggerIfc* m_instance;


};

class c_DevelopmentLogTraceIndentator {
public:
	c_DevelopmentLogTraceIndentator(const c_LogString& sScopeCaption)
		: m_sScopeCaption(sScopeCaption)
	{
		c_LogString sMessage("{ \\\\ ");
		sMessage += m_sScopeCaption;
		c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(sMessage);
		c_BussinessLoggerIfc::instance()->incrementDevelopmentTraceIndent();
	}

	~c_DevelopmentLogTraceIndentator() {
		c_BussinessLoggerIfc::instance()->decrementDevelopmentTraceIndent();
		c_LogString sMessage("} \\\\ ");
		sMessage += m_sScopeCaption;
		c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(sMessage);
	}
private:
	/**
	  * private storage of the caption of the scope we have entered
	  */
	c_LogString m_sScopeCaption;

};

// Log a design insufficiency

// Log a design insufficiency about current function not implemented
#define LOG_NOT_IMPLEMENTED c_BussinessLoggerIfc::instance()->LogNotImplemented(_Literalsz(__FUNCTION__));

#define LOG_DESIGN_INSUFFICIENCY(S) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(S)
// Log a design insufficiency integrating an integer into supplied text
#define LOG_DESIGN_INSUFFICIENCY_I(S,X) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(S,X)
// Log a design insufficiency integrating two integers into supplied text
#define LOG_DESIGN_INSUFFICIENCY_II(S,X,Y) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(S,X,Y)
// Log a design insufficiency integrating a string into supplied text
#define LOG_DESIGN_INSUFFICIENCY_S(S,S1) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(S,S1)
// Log a design insufficiency integrating two strings into supplied text
#define LOG_DESIGN_INSUFFICIENCY_2S(S,S1,S2) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(S,S1,S2)
// Log a design insufficiency integrating a object instance ID into the logged entry
#define LOG_DESIGN_INSUFFICIENCY_O(O,S) c_BussinessLoggerIfc::instance()->LogDesignInsufficiency(O,S)

#ifdef _DEBUG
	// Log a development trace
	#define LOG_DEVELOPMENT_TRACE(S) c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(S)
	// Log a development trace integrating an integer into supplied text
	#define LOG_DEVELOPMENT_TRACE_I(S,X) c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(S,X)
	// Log a development trace integrating a string into supplied text
	#define LOG_DEVELOPMENT_TRACE_S(S,S1) c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(S,S1)
	// Log a development trace integrating a string into supplied text
	#define LOG_DEVELOPMENT_TRACE_2S(S,S1,S2) c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(S,S1,S2)
	// Log a development trace integrating a object instance ID into the logged entry
	#define LOG_DEVELOPMENT_TRACE_O(O,S) c_BussinessLoggerIfc::instance()->LogDevelopmentTrace(O,S)

//	#define LOG_SCOPE_ENTRY(S) c_BussinessLoggerIfc::instance()->LogScopeEntry(S)

	#define LOG_FUNCTION_SCOPE\
		c_LogString sFunctionEntryString(__FUNCTION__);\
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);
	#define LOG_METHOD_SCOPE \
		c_LogString sFunctionEntryString(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this))); \
		sFunctionEntryString += _UTF8sz("::"__FUNCTION__);\
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);

	#define LOG_SCOPE_S(S) c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(S);
	#define LOG_FUNCTION_SCOPE_S(S) \
		sFunctionEntryString += _UTF8sz("::"__FUNCTION__"(");\
		sFunctionEntryString += toLogString(S); \
		sFunctionEntryString += _UTF8sz(")"); \
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);
	#define LOG_METHOD_SCOPE_S(S) \
		c_LogString sFunctionEntryString(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this))); \
		sFunctionEntryString += _UTF8sz("::"__FUNCTION__"(");\
		sFunctionEntryString += toLogString(S); \
		sFunctionEntryString += _UTF8sz(")"); \
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);
	/**
	  * Conveniant macro to define code that executes and
	  * traces provided statement
	  */
	#define TRACE_STATEMENT(X) \
		LOG_DEVELOPMENT_TRACE(_UTF8sz("BEGIN: " #X)); \
		X; \
		LOG_DEVELOPMENT_TRACE(_UTF8sz("END  : " #X));

#else
	/**
	  * Not a Debug version. Define as empty macros
	  */

	// Log a development trace
	#define LOG_DEVELOPMENT_TRACE(S)
	// Log a development trace integrating an integer into supplied text
	#define LOG_DEVELOPMENT_TRACE_I(S,X)
	// Log a development trace integrating a string into supplied text
	#define LOG_DEVELOPMENT_TRACE_S(S,S1)
	// Log a development trace integrating a string into supplied text
	#define LOG_DEVELOPMENT_TRACE_2S(S,S1,S2)
	// Log a development trace integrating a object instance ID into the logged entry
	#define LOG_DEVELOPMENT_TRACE_O(O,S)

	#define LOG_FUNCTION_SCOPE
	#define LOG_METHOD_SCOPE

	#define LOG_SCOPE_S(S)
	#define LOG_FUNCTION_SCOPE_S(S)
	#define LOG_METHOD_SCOPE_S(S)
	#define TRACE_STATEMENT(X)
#endif

// Log an application business event
#define LOG_BUSINESS(S) c_BussinessLoggerIfc::instance()->LogBussiness(S)
// Log an application business event integrating a object instance ID into the logged entry
#define LOG_BUSINESS_O(O,S) c_BussinessLoggerIfc::instance()->LogBussiness(O,S)

#define LOG_IDE_EXCEPTION_DESIGN_INSUFFICIENCY \
		c_LogString sMessage(__FUNCTION__);\
		sMessage += _UTF8sz(" failed. Exception="); \
		sMessage += toLogString(e.Message);\
		LOG_DESIGN_INSUFFICIENCY(sMessage);

#define LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY \
		c_LogString sMessage(__FUNCTION__);\
		sMessage += _UTF8sz(" failed. Exception=");\
		sMessage += _UTF8sz(e.what());\
		LOG_DESIGN_INSUFFICIENCY(sMessage)

#define LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY \
		c_LogString sMessage(__FUNCTION__);\
		sMessage += _UTF8sz(" failed. General Exception cought.");\
		LOG_DESIGN_INSUFFICIENCY(sMessage)

#define CATCH_AND_LOG_IDE_EXCEPTION_DESIGN_INSUFFICIENCY \
	catch (const Exception& e) {\
		LOG_IDE_EXCEPTION_DESIGN_INSUFFICIENCY;\
	}

#define CATCH_LOG_AND_THROW_IDE_EXCEPTION_DESIGN_INSUFFICIENCY \
	catch (const Exception& e) { \
		LOG_IDE_EXCEPTION_DESIGN_INSUFFICIENCY;\
		throw; \
	}

#define CATCH_AND_LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY \
	catch (const std::exception& e) { \
		LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY;\
	}

#define CATCH_AND_LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY \
	catch (...) { \
		LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;\
	}

#define CATCH_AND_LOG_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY \
	CATCH_AND_LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY\
	CATCH_AND_LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY

#define CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY \
	CATCH_AND_LOG_IDE_EXCEPTION_DESIGN_INSUFFICIENCY\
	CATCH_AND_LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY\
	CATCH_AND_LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY

#endif
