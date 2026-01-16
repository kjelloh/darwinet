//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#ifdef _DEBUG
	#define COMPILE_TEST_CODE
//	#define RUN_TEST_CODE
#endif
//---------------------------------------------------------------------------
#include "BusinessLogUnit.h"
#include "IDEInterfacedSource.h" // c_ThreadGate
#include <fstream>
#include "ApplicationEnvironment.h" // c_Application
//---------------------------------------------------------------------------
#ifdef COMPILE_TEST_CODE
	#include <boost/shared_ptr.hpp>
	#include <boost/foreach.hpp>
#endif
//---------------------------------------------------------------------------
#pragma warn -8072 // Disable. Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
#pragma warn .8072 // Restore
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#ifdef COMPILE_TEST_CODE
class c_UnitTest {
public:
	void test() {
		LOG_METHOD_SCOPE;
		{
			LOG_METHOD_SCOPE_S("Test of boost::format");
			c_LogString sMessage(
				boost::str(
					boost::format(
						METHOD_PREFIXED_LOG_STRING(" Testing boost::format to insert pointer this=%p into this string.")
					) % this));
			LOG_DEVELOPMENT_TRACE(sMessage);
		}
		int test_states[3] = {1,2,3};
		BOOST_FOREACH(const int test_state,test_states) {
			try {
				switch (test_state) {
				case 1: throw 0; // Test of catch(...)
				break;
				case 2: throw std::runtime_error("Test throw of std::runtime_error");
				break;
				case 3: throw Exception("Test throw of RAD Studio Exception");
				break;
				default:
					;
				}
			}
			CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;
		}
	}
};
//---------------------------------------------------------------------------
/**
  * Code to test complilation and execution of unit finctionality
  */
void unit_test() {
	LOG_FUNCTION_SCOPE;
	{
		LOG_FUNCTION_SCOPE_S("Testing object logging");
		boost::shared_ptr<c_UnitTest> pUnitTest(new c_UnitTest()) ;
		pUnitTest->test();
	}
}
#endif // COMPILE_TEST_CODE
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class c_ObjectInfo {
public:
	typedef boost::shared_ptr<c_ObjectInfo> shared_ptr;

	/**
	  * Constructor
	  */
	c_ObjectInfo(const void* pObject,int object_size_in_bytes);

	/**
	  * Destructor
	  */
	virtual ~c_ObjectInfo();

	/**
	  * Compares object instance contents with its initial contents
	  * and logs any changes found.
	  */
	void logState();

	/**
	  * Returns true if provided memory location is that of our object instance
	  */
	bool isObject(const void* pObject);

private:
	/**
	  * Private storage of pointer to minitored object
	  */
	const void* m_pObject;

	/**
	  * private storage of the size in bytes of monitored object
	  */
	const int m_object_size_in_bytes;

	/**
	  * Private storage of initial contens of monitored object
	  */
	void* m_pInitialContens;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Implementation of the c_HeapSupervisor
  */
class c_HeapSupervisorImpl : public c_HeapSupervisor {
public:

	/**
	  * Constructor
	  */
	c_HeapSupervisorImpl();

	// Begin c_HeapSupervisor
	/**
	  * Adds provided object adress to the list of heap locations to monitor
	  */
	virtual void startMonitoring(void* pObject,int size_in_bytes);

	/**
	  * Removes provided object adress from the list of heap locations to minitor
	  */
	virtual void stopMonitoring(void* pObject);

	/**
	  * Will log any changes to monitored objects
	  */
	virtual void logMonitoredObjectState();

	// End c_HeapSupervisor

	/**
	  * Logs provided string to Development Trace Log
	  */
	static void logDevelopmentTraceEntry(const c_LogString& sEntry);

	/**
	  * Logs provided string to Design Insufficiency Log
	  */
	static void logDesignInsufficiencyEntry(const c_LogString& sEntry);

private:

	typedef std::vector<c_ObjectInfo::shared_ptr> c_ObjectInfoList;

	/**
	  * Returns iterator reference to the object monitor information instance
	  * of provided address.
	  */
	c_ObjectInfoList::iterator findSupervicedObject(const void* pObject);

	/**
	  * Private storage of the heap objects we are monitoring
	  */
	 c_ObjectInfoList m_objectInfoList;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Constructor
  */
c_ObjectInfo::c_ObjectInfo(const void* pObject,int object_size_in_bytes)
	:  m_pObject(pObject)
	  ,m_object_size_in_bytes(object_size_in_bytes)
	  ,m_pInitialContens(malloc(m_object_size_in_bytes))
{
	// Copy the initial contents of object instance
	memcpy(m_pInitialContens,m_pObject,m_object_size_in_bytes);
	c_LogString sMessage(boost::str(boost::format("Added view of object at %p") % m_pObject));
	c_HeapSupervisorImpl::logDevelopmentTraceEntry(sMessage);
}

//---------------------------------------------------------------------------
/**
  * Destructor
  */
c_ObjectInfo::~c_ObjectInfo() {
	free(m_pInitialContens);
	c_LogString sMessage(boost::str(boost::format("Removed view of object at %p") % m_pObject));
	c_HeapSupervisorImpl::logDevelopmentTraceEntry(sMessage);
}

//---------------------------------------------------------------------------
/**
  * Compares object instance contents with its initial contents
  * and logs any changes found.
  */
void c_ObjectInfo::logState() {
	int cmp_result = memcmp(m_pInitialContens,m_pObject,m_object_size_in_bytes);
	if (cmp_result != 0) {
		// The contents no longer matches initial contents
		c_LogString sMessage(boost::str(boost::format("Object at %p of size %d has new contents") % m_pObject % m_object_size_in_bytes));
		c_HeapSupervisorImpl::logDesignInsufficiencyEntry(sMessage);
	}
	else {
//		c_LogString sMessage(boost::str(boost::format("Object at %p has initial contents") % m_pObject));
//		c_HeapSupervisorImpl::logDevelopmentTraceEntry(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Returns true if provided memory location is that of our object instance
  */
bool c_ObjectInfo::isObject(const void* pObject) {
	return (pObject == m_pObject);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Constructor
  */
c_HeapSupervisorImpl::c_HeapSupervisorImpl()
	: m_objectInfoList()
{

}

// Begin c_HeapSupervisor
//---------------------------------------------------------------------------
/**
  * Adds provided object adress to the list of heap locations to monitor
  */
void c_HeapSupervisorImpl::startMonitoring(void* pObject,int size_in_bytes) {
	c_ObjectInfoList::iterator iObject(this->findSupervicedObject(pObject));
	if (iObject == m_objectInfoList.end()) {
		c_ObjectInfo::shared_ptr pObjectInfo(new c_ObjectInfo(pObject,size_in_bytes));
		this->m_objectInfoList.push_back(pObjectInfo);
	}
	else {
		// The object is already monitored. Replace
//		c_LogString sMessage(boost::str(boost::format(__FUNCTION__" called with adress %p which is already monitored. Current Monitor will be removed and the new added") % pObject));
		c_LogString sMessage(boost::str(boost::format(METHOD_PREFIXED_LOG_STRING(" called with adress %p which is already monitored. Current Monitor will be removed and the new added")) % pObject));
		c_HeapSupervisorImpl::logDesignInsufficiencyEntry(sMessage);
		this->stopMonitoring(pObject); // Remove existing monitor
		this->startMonitoring(pObject,size_in_bytes); // try again recursivelly
	}
}

//---------------------------------------------------------------------------
/**
  * Removes provided object adress from the list of heap locations to minitor
  */
void c_HeapSupervisorImpl::stopMonitoring(void* pObject) {
	c_ObjectInfoList::iterator iObject = findSupervicedObject(pObject);
	if (iObject != m_objectInfoList.end()) {
		m_objectInfoList.erase(iObject);
	}
	else {
		// The object is not in the monitor list!
//		c_LogString sMessage(boost::str(boost::format(__FUNCTION__" failed! called with adress %p which is NOT monitored.") % pObject));
		c_LogString sMessage(boost::str(boost::format(METHOD_PREFIXED_LOG_STRING(" failed! called with adress %p which is NOT monitored.")) % pObject));
		c_HeapSupervisorImpl::logDesignInsufficiencyEntry(sMessage);
		this->logMonitoredObjectState();
	}
}

//---------------------------------------------------------------------------
/**
  * Will log any changes to monitored objects
  */
void c_HeapSupervisorImpl::logMonitoredObjectState() {
	// Loop through the list and check if any object contents has changed
	for (c_ObjectInfoList::const_iterator iter = m_objectInfoList.begin(); iter != m_objectInfoList.end(); ++iter) {
		(*iter)->logState();
	}
}

// End c_HeapSupervisor

/**
  * Logs provided string to Development Trace Log
  */
void c_HeapSupervisorImpl::logDevelopmentTraceEntry(const c_LogString& sEntry) {
	c_LogString sMessage("HeapSupervisor:");
	sMessage += sEntry;
	LOG_DEVELOPMENT_TRACE(sMessage);
}

/**
  * Logs provided string to Design Insufficiency Log
  */
void c_HeapSupervisorImpl::logDesignInsufficiencyEntry(const c_LogString& sEntry) {
	c_LogString sMessage("HeapSupervisor:");
	sMessage += sEntry;
	LOG_DESIGN_INSUFFICIENCY(sMessage);
}

//---------------------------------------------------------------------------
/**
  * Returns iterator reference to the object monitor information instance
  * of provided address.
  */
c_HeapSupervisorImpl::c_ObjectInfoList::iterator c_HeapSupervisorImpl::findSupervicedObject(const void* pObject) {
	c_ObjectInfoList::iterator result = m_objectInfoList.begin();
	// Loop through the list and remove the entry of this object
	for (; result != m_objectInfoList.end(); ++result) {
		if ((*result)->isObject(pObject)) {
			break;
		}
	}
	return result;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Private static storage of this singleton instance
  */
c_HeapSupervisor::shared_ptr c_HeapSupervisor::m_pInstance;

c_HeapSupervisor::shared_ptr c_HeapSupervisor::instance() {
	if (!c_HeapSupervisor::m_pInstance) {
		c_HeapSupervisor::m_pInstance.reset(new c_HeapSupervisorImpl());
	}
	return c_HeapSupervisor::m_pInstance;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Defines the number of blanks used when indentation level is changed.
  */
const unsigned int INDENT_CHANGE_WIDTH = 4;

/**
  * Class that encapsulates the business log.
  * The business log is to be used to log normal and excpetional
  * activites of the application operations.
  */
class c_BussinessLogger : public c_BussinessLoggerIfc {
public:

	/**
	  * Default constructor
	  */
	c_BussinessLogger();

	// Begin c_BussinessLoggerIfc

	/**
	  * returns true if this instance has a record of unread
	  * entries of provided entry type.
	  */
	bool thereIsUnreadEntriesOfType(e_BussinessLogEntryType entry_type);

	/**
	  * sets the "Unread" state for entries of provided type
	  */
	void setUnreadEntriesStateOfType(e_BussinessLogEntryType entry_type,bool isSet);

	/**
	  * Design insufficiency log about a not implemented function/Method
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	void LogNotImplemented(const c_DataRepresentationFramework::c_CppLiteralString& sFunctionName);

	/**
	  * Design insufficiency log.
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(const c_LogString& sEntry);

	/**
	  * Design insufficiency log for UTF16 string.
	  * Will decode to string represetnation used by Business Log engine
	  */
	void LogDesignInsufficiency(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry);

	/**
	  * Design insufficiency log for  C++ String literal array.
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	void LogDesignInsufficiency(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry);

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(const c_LogString& sEntry,int i1);

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(const c_LogString& sEntry,int i1,int i2);

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1);

	/**
	  * Design insufficiency log
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2);

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	void LogDevelopmentTrace(const c_LogString& sEntry);

	/**
	  * Development trace log for UTF16 char array.
	  * Will decode to string represetnation used by Business Log engine
	  */
	void LogDevelopmentTrace(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry);

	/**
	  * Development trace log for C++ String literal string
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	void LogDevelopmentTrace(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry);

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	void LogDevelopmentTrace(const c_LogString& sEntry,int i1);

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	void LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1);

	/**
	  * Development trace log used during development
	  * of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	virtual void LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2);

	/**
	  * Logs an entry to a scope. szEntry is the name of the scope.
	  */
	void LogScopeEntry(const c_LogString& sEntry);

	/**
	  * Business log used to log events of normal application
	  * execution. This Log is for released application execution logging.
	  */
	void LogBussiness(const c_LogString& sEntry);

	/**
	  * Business log for UTF16 char array.
	  * Will decode to string representation used by Business Log engine
	  */
	void LogBussiness(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry);

	/**
	  * Development trace log for C++ String literal string
	  * Will asume C++ string literal allows ascii 0..255 and
	  * decode to string representation used by Business Log engine
	  */
	void LogBussiness(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry);

	/**
	  * Design insufficiency log of an object instance using an instance Id 0,1,2...
	  * Used to trace events where the application design
	  * is unsufficient to handle an event in run-time.
	  * This log is active in released application execution.
	  */
	void LogDesignInsufficiency(int instance_id,const c_LogString& sEntry);

	/**
	  * Development trace of an object instance using an instance Id 0,1,2...
	  * log used during development of application used to trace execution.
	  * This log is NOT active in released application execution.
	  */
	void LogDevelopmentTrace(int instance_id,const c_LogString& sEntry);

	/**
	  * Business log used to log events
	  * of normal application execution.
	  * This Log is for released application execution logging.
	  */
	void LogBussiness(int instance_id,const c_LogString& sEntry);

	/**
	  * Returns next stored log entry from the log entry storage
	  * and removes it from the storage. Used by user interface to poll
	  * for entries that are to be shown in the user interface.
	  * Returns NULL if there are no entries to return.
	  */
	c_BussinessLogEntry* popUILogEntry();

	/**
	  * Returns number of entries in the logger that is not popped
	  * for UI view.
	  */
	int unPoppedUIEntriesCount();

	/**
	  * Increments the indentations used for development trace log entries
	  */
	virtual void incrementDevelopmentTraceIndent();

	/**
	  * Decrements the indentations used for development trace log entries
	  */
	virtual void decrementDevelopmentTraceIndent();

	// End c_BussinessLoggerIfc

private:
	/**
	  * Private storage of thread gate to protect multipple thread call to the
	  * business logger
	  */
	c_ThreadGate m_ThreadGate;

	/**
	  * Private aggrehation of thread gate used to synchronize
	  * thread access to the log resources.
	  */
	c_ThreadGate m_LogEntryThreadGate;

	/**
	  * Private storage of output file stream to store
	  * logged entries
	  */
	std::ofstream m_LogStream;

	/**
	  * Private storage of queued enrties to be shown in the user
	  * interface.
	  */
	std::queue<c_BussinessLogEntry*> m_UILogEntries;

	/**
	  * Private helper method that stores provided entry into the Log.
	  * Will store the entry to persistent storage (file)
	  * and into queue to be fetched and shown by user interface.
	  */
	void StoreEntryInLog(c_BussinessLogEntry* pEntry);

	/**
	  * Private storage of flag indicating that there is unread entries
	  * of type Business
	  * Note 100916. There is currentlly no entry type for error entries
	  * in Business log. But the mechanism for "Unread entries" is implemented
	  * for Business error entries only.
	  */
	bool m_thereIsUnreadEntriesOfTypeBusiness;

//	/**
//	  * Current string used to undent Development trace entries
//	  */
//	c_LogString m_sCurrentDevelopmentTraceIndentString;

	/**
	  * returns the indent string to be used for current exectuion thread
	  */
	c_LogString getThreadDependentIndentString();

};

/**
  * Unique per therad Class member variable that
  * holds the current indentation of the current thread log.
  * Each thread of execution has its own indentation.
  */
int __thread m_indentOfCurrentThreadLog = 0;

//---------------------------------------------------------------------------

/**
  * Converts same type to LogString. Provided to enable
  * Macros to work with all string types
  */
c_LogString toLogString(const c_LogString& sEntry) {
	return c_DataRepresentationFramework::toUTF8String(sEntry);
}

/**
  * Converts provided UTF16 string to Log string representation
  */
c_LogString toLogString(const c_DataRepresentationFramework::c_UTF16String& sEntry) {
	return c_DataRepresentationFramework::toUTF8String(sEntry);
}

///**
//  * Converts provided IDE string to Log string representation.
//  * Will use compile time information to determine
//  * representation of IDE string (UTF16, Ansi etc...)
//  */
//c_LogString toLogString(const String& sEntry) {
//#ifdef _DELPHI_STRING_UNICODE
//	// IDE uses UTF16 for String
//	return c_DataRepresentationFramework::toUTF8String(_UTF16sz(sEntry.c_str()));
//#else // #ifdef _DELPHI_STRING_UNICODE
//	// IDE uses Ansi for String.
//	// Note - Asume Ascii for now. Ansi may actually contain chars 0..255 but we avoid this problem for now...
//	// TODO 101119: Consider handling 0..255 char array in some safe way here. Check String code page?
//	return c_DataRepresentationFramework::toUTF8String(_Asciisz(sEntry.c_str()));
//#endif // _DELPHI_STRING_UNICODE
//}

/**
  * Converts RAD Studio XE System::UnicodeString to c_LogString
  * Note: RAD Studio XE type String may be this type depedning on project settings.
  */
c_LogString toLogString(const System::UnicodeString& sEntry) {
	// IDE uses UTF16 for String
	return c_DataRepresentationFramework::toUTF8String(_UTF16sz(sEntry.c_str()));
}

///**
//  * Converts RAD Studio XE System::AnsiString to c_LogString
//  * Note: RAD Studio XE type String may be this type depedning on project settings.
//  */
//c_LogString toLogString(const System::AnsiString& sEntry) {
//	// IDE uses Ansi for String.
//	// Assume UTF8 encoded string
//	return c_DataRepresentationFramework::toUTF8String(_UTF8sz(sEntry.c_str()));
//}

///**
//  * Converts provided C++ literal string to Log string representation
//  */
//c_LogString toLogString(const c_DataRepresentationFramework::c_CppLiteralString& sEntry) {
//	return c_DataRepresentationFramework::toUTF8String(sEntry);
//}

/**
  * Converts provided C++ literal string to Log string representation
  */
c_LogString toLogString(const c_DataRepresentationFramework::c_ISO_8859_1_String& sEntry) {
	return c_DataRepresentationFramework::toUTF8String(sEntry);
}

/**
  * Returns a log string with a text describing the menaing of provided Windows api error code.
  */
c_LogString logStringOfWinApiErrorCode(DWORD api_error_code) {
	c_LogString result = c_DataRepresentationFramework::intToDecimalString(api_error_code);
	result += _Asciic(':');
	// Retrieve the system error message for the last-error code

	LPWSTR lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		api_error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	result += toLogString(_UTF16sz(lpMsgBuf));
	LocalFree(lpMsgBuf);

	return result;
}

/**
  * Returns provided Windows HRESULKT code as a descriptive Log string
  */
c_LogString logStringOfWinApiHResultCode(HRESULT hresult) {
	c_LogString result = c_DataRepresentationFramework::intToHexString(hresult);
	result += _Asciic(':');
	if (SUCCEEDED(hresult)) {
		result += _UTF8sz("OK");
	}
	else {
		result += _UTF8sz("FAILED");
	}
	return result;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Constructs a log entry form provided entry type and entry body
  */
c_BussinessLogEntry::c_BussinessLogEntry(e_BussinessLogEntryType entry_type,const c_LogString& sBody)
	:  m_entry_type(entry_type)
	  ,m_sBody(sBody)
	  ,m_YYYYMMDDHHMMSSmmm()
	  ,m_ThreadId(GetCurrentThreadId())
{

}

/**
  * Returns the type of this entry
  */
e_BussinessLogEntryType c_BussinessLogEntry::getType() const {
	return this->m_entry_type;
}


/**
  * Returns the formatted header of this entry
  */
c_LogString c_BussinessLogEntry::header() const {
	c_LogString result(c_DataRepresentationFramework::intToHexString(this->m_ThreadId,4));
	result.anonymous() += ":";
	result.anonymous() += this->m_YYYYMMDDHHMMSSmmm.getFormatedDateAndTime();
	result.anonymous() += " ";
	result += c_BussinessLogEntry::StringOfBussinessLogEntryType(this->m_entry_type);
	return result;
}

/**
  * Returns the formatted body of this entry
  */
c_LogString c_BussinessLogEntry::body() const {
	return this->m_sBody;

}

/**
  * Returns the whole entry formatted as a string
  */
c_LogString c_BussinessLogEntry::toString() const {
	c_LogString result;
	result += this->header();
	result.anonymous() += ":";
	result += this->body();
	return result;
}

/**
  * Static helper method that returns provided e_BussinessLogEntryType as a string
  */
c_LogString c_BussinessLogEntry::StringOfBussinessLogEntryType(e_BussinessLogEntryType entry_type) {
	c_LogString result("#unknown type#");
	switch (entry_type) {
		case e_BussinessLogEntryType_DesignInsufficiency:
			result = c_LogString("DESIGN INSUFFICIENCY");
		break;
		case e_BussinessLogEntryType_DevelopmentTrace:
			result = c_LogString("DEVELOPMENT TRACE");
		break;
		case e_BussinessLogEntryType_Bussiness:
			result = c_LogString("BUSSINESS");
		break;
	default:
		;
	}
	return result;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Private class storage if this singleton instance
  */
c_BussinessLoggerIfc* c_BussinessLoggerIfc::m_instance = NULL;

/**
  * Returns this singleton instance
  */
c_BussinessLoggerIfc* c_BussinessLoggerIfc::instance() {
	if (m_instance == NULL) {
		m_instance = new c_BussinessLogger();
	}
	return m_instance;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * returns true if this instance has a record of unread
  * entries of provided entry type.
  */
bool c_BussinessLogger::thereIsUnreadEntriesOfType(e_BussinessLogEntryType entry_type) {
	bool result = false;
	switch (entry_type) {
		case e_BussinessLogEntryType_DesignInsufficiency:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::thereIsUnreadEntriesOfType not implemented for type e_BussinessLogEntryType_DesignInsufficiency"));
		break;
		case e_BussinessLogEntryType_DevelopmentTrace:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::thereIsUnreadEntriesOfType not implemented for type e_BussinessLogEntryType_DevelopmentTrace"));
		break;
		case e_BussinessLogEntryType_Bussiness:
			result = this->m_thereIsUnreadEntriesOfTypeBusiness;
		break;
	default:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::thereIsUnreadEntriesOfType failed. Called with unknown entry type"));
		;
	}
	return result;
}

//---------------------------------------------------------------------------
/**
  * sets the "Unread" state for entries of provided type
  */
void c_BussinessLogger::setUnreadEntriesStateOfType(e_BussinessLogEntryType entry_type,bool isSet) {
	switch (entry_type) {
		case e_BussinessLogEntryType_DesignInsufficiency:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::setUnreadEntriesStateOfType not implemented for type e_BussinessLogEntryType_DesignInsufficiency"));
		break;
		case e_BussinessLogEntryType_DevelopmentTrace:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::setUnreadEntriesStateOfType not implemented for type e_BussinessLogEntryType_DevelopmentTrace"));
		break;
		case e_BussinessLogEntryType_Bussiness:
			this->m_thereIsUnreadEntriesOfTypeBusiness = isSet;
		break;
	default:
			LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_BussinessLogger::resetUnreadEntriesStateOfType failed. Called with unknown entry type"));
		;
	}
}

//---------------------------------------------------------------------------
/**
  * Private constructor to make this class a singleton
  */
c_BussinessLogger::c_BussinessLogger()
	:  m_LogEntryThreadGate()
	  ,m_UILogEntries()
	  ,m_LogStream()
	  ,m_thereIsUnreadEntriesOfTypeBusiness(false)
//	  ,m_sCurrentDevelopmentTraceIndentString("")
{
}

//---------------------------------------------------------------------------

/**
  * Design insufficiency log about a not implemented function/Method
  * Will asume C++ string literal allows ascii 0..255 and
  * decode to string representation used by Business Log engine
  */
void c_BussinessLogger::LogNotImplemented(const c_DataRepresentationFramework::c_CppLiteralString& sFunctionName) {
	c_LogString sEntry(toLogString(sFunctionName)); // Asume Literal is allowed to cover whole local code page = needs conversion
	sEntry.anonymous() += " not fully implemented";
	this->LogDesignInsufficiency(sEntry);
}

//---------------------------------------------------------------------------
/**
  * Desing insufficiency log
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_LogString& sEntry) {
	this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_DesignInsufficiency,sEntry));
}

/**
  * Design insufficiency log for  C++ String literal array.
  * Will asume C++ string literal allows ascii 0..255 and
  * decode to string representation used by Business Log engine
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) {
	this->LogDesignInsufficiency(toLogString(sCppLiteralEntry)); // De-encode and Log it
}

//---------------------------------------------------------------------------
/**
  * Design insufficiency log for UTF16 char array.
  * Will decode to string represetnation used by Business Log engine
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) {
	this->LogDesignInsufficiency(toLogString(sUTF16Entry));
}
//---------------------------------------------------------------------------

/**
  * Desing insufficiency log
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_LogString& sEntry,int i1) {
	try {
		// Use boost format instance and % operator to format the integer into the
		// provided format string sEntry. boost::format() creates the formatter object
		// which will then execute the % operator on following parameters.
		// The result is a boost::format object that is cast to a std::string using
		// boost::str. (Note, the format object also has a .str() member function)
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % i1));
		this->LogDesignInsufficiency(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDesignInsufficiency failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Desing insufficiency log
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_LogString& sEntry,int i1,int i2) {
	try {
		// Use boost format instance and % operator to format the integer into the
		// provided format string sEntry. boost::format() creates the formatter object
		// which will then execute the % operator on the following parameters.
		// The result is a boost::format object that is cast to a std::string using
		// boost::str. (Note, the format object also has a .str() member function)
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % i1 % i2));
		this->LogDesignInsufficiency(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDesignInsufficiency failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Desing insufficiency log
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1) {
	try {
		// Format and call simpler method for logging
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % s1));
		this->LogDesignInsufficiency(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDesignInsufficiency failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\" with provided parameter s1=\"";
		sMessage += s1;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

/**
  * Design insufficiency log
  */
void c_BussinessLogger::LogDesignInsufficiency(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2) {
	try {
		// Format and call base method for logging
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % s1 % s2));
		this->LogDesignInsufficiency(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDesignInsufficiency failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\" with provided parameter s1=\"";
		sMessage += s1;
		sMessage.anonymous() += "\" and s2=\"";
		sMessage += s2;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}
//---------------------------------------------------------------------------
/**
  * Development trace log used during development
  * of application used to trace execution.
  * This log is NOT active in released application execution.
  */
//void c_BussinessLogger::LogDevelopmentTrace(const char* szEntry) {
//	this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_DevelopmentTrace,szEntry));
//}
void c_BussinessLogger::LogDevelopmentTrace(const c_LogString& sEntry) {
//	c_LogString sIndentedString = this->m_sCurrentDevelopmentTraceIndentString + sEntry;
	c_LogString sIndentedString = getThreadDependentIndentString() + sEntry;
	this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_DevelopmentTrace,sIndentedString));
}

//---------------------------------------------------------------------------

/**
  * Development trace log for UTF16 char array.
  * Will decode to string represetnation used by Business Log engine
  */
void c_BussinessLogger::LogDevelopmentTrace(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) {
	this->LogDevelopmentTrace(toLogString(sUTF16Entry));
}

/**
  * Development trace log for C++ String literal string
  * Will asume C++ string literal allows ascii 0..255 and
  * decode to string representation used by Business Log engine
  */
void c_BussinessLogger::LogDevelopmentTrace(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) {
	this->LogDevelopmentTrace(toLogString(sCppLiteralEntry));
}

//---------------------------------------------------------------------------
/**
  * Development trace log used during development
  * of application used to trace execution.
  * This log is NOT active in released application execution.
  */
//void c_BussinessLogger::LogDevelopmentTrace(const char* szEntry,int i1) {
void c_BussinessLogger::LogDevelopmentTrace(const c_LogString& sEntry,int i1) {
	c_ThreadSynchronizer ts(m_ThreadGate);
	try {
		// Use boost format instance and % operator to format the integer into the
		// provided format string sEntry. boost::format() creates the formatter object
		// which will then execute the % operator on the following parameters.
		// The result is a boost::format object that is cast to a std::string using
		// boost::str. (Note, the format object also has a .str() member function)
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % i1));
		this->LogDevelopmentTrace(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDevelopmentTrace failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

//---------------------------------------------------------------------------

/**
  * Development trace log used during development
  * of application used to trace execution.
  * This log is NOT active in released application execution.
  */
void c_BussinessLogger::LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1) {
	c_ThreadSynchronizer ts(m_ThreadGate);
	try {
		// Use boost format instance and % operator to format the integer into the
		// provided format string sEntry. boost::format() creates the formatter object
		// which will then execute the % operator on the following parameters.
		// The result is a boost::format object that is cast to a std::string using
		// boost::str. (Note, the format object also has a .str() member function)
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % s1));
		this->LogDevelopmentTrace(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDevelopmentTrace failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\" with provided parameter s1=\"";
		sMessage += s1;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

/**
  * Development trace log used during development
  * of application used to trace execution.
  * This log is NOT active in released application execution.
  */
void c_BussinessLogger::LogDevelopmentTrace(const c_LogString& sEntry,const c_LogString& s1,const c_LogString& s2) {
	c_ThreadSynchronizer ts(m_ThreadGate);
	try {
		// Use boost format instance and % operator to format the integer into the
		// provided format string sEntry. boost::format() creates the formatter object
		// which will then execute the % operator on the following parameters.
		// The result is a boost::format object that is cast to a std::string using
		// boost::str. (Note, the format object also has a .str() member function)
		c_LogString sFormattedEntry(boost::str(boost::format(sEntry) % s1 % s2));
		this->LogDevelopmentTrace(sFormattedEntry);
	} catch (std::exception& e) {
		c_LogString sMessage("c_BussinessLogger::LogDevelopmentTrace failed processing entry=\"");
		sMessage += sEntry;
		sMessage.anonymous() += "\" with provided parameter s1=\"";
		sMessage += s1;
		sMessage.anonymous() += "\". Exception=";
		sMessage += c_LogString(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Logs an entry to a scope. szEntry is the name of the scope.
  */
void c_BussinessLogger::LogScopeEntry(const c_LogString& sEntry) {
	c_LogString sFormattedEntry = sEntry;
	sFormattedEntry.anonymous() += " entered.";
	this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_DevelopmentTrace,sFormattedEntry));
}

//---------------------------------------------------------------------------
/**
  * Business log used to log events of normal application
  * execution. This Log is for released application execution logging.
  */
void c_BussinessLogger::LogBussiness(const c_LogString& sEntry) {
	this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_Bussiness,sEntry));
}

//---------------------------------------------------------------------------
/**
  * Business log for UTF16 char array.
  * Will decode to string representation used by Business Log engine
  */
void c_BussinessLogger::LogBussiness(const c_DataRepresentationFramework::c_UTF16String& sUTF16Entry) {
	this->LogBussiness(toLogString(sUTF16Entry));
}

//---------------------------------------------------------------------------
/**
  * Development trace log for C++ String literal string
  * Will asume C++ string literal allows ascii 0..255 and
  * decode to string representation used by Business Log engine
  */
void c_BussinessLogger::LogBussiness(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralEntry) {
	this->LogBussiness(toLogString(sCppLiteralEntry));
}

//---------------------------------------------------------------------------

/**
  * Design insufficiency log of an object instance using an instance Id 0,1,2...
  * Used to trace events where the application design
  * is unsufficient to handle an event in run-time.
  * This log is active in released application execution.
  */
void c_BussinessLogger::LogDesignInsufficiency(int instance_id,const c_LogString& sEntry) {
	c_LogString sFormattedEntry("[");
	sFormattedEntry += c_DataRepresentationFramework::intToDecimalString(instance_id);
	sFormattedEntry.anonymous() += "] ";
	sFormattedEntry += sEntry;
	this->LogDesignInsufficiency(sFormattedEntry);
}

/**
  * Development trace of an object instance using an instance Id 0,1,2...
  * log used during development of application used to trace execution.
  * This log is NOT active in released application execution.
  */
void c_BussinessLogger::LogDevelopmentTrace(int instance_id,const c_LogString& sEntry) {
	c_LogString sFormattedEntry("[");
	sFormattedEntry += c_DataRepresentationFramework::intToDecimalString(instance_id);
	sFormattedEntry.anonymous() += "] ";
	sFormattedEntry += sEntry;
	this->LogDevelopmentTrace(sFormattedEntry);
}

/**
  * Business log used to log events
  * of normal application execution.
  * This Log is for released application execution logging.
  */
void c_BussinessLogger::LogBussiness(int instance_id,const c_LogString& sEntry) {
	c_LogString sFormattedEntry("[");
	sFormattedEntry += c_DataRepresentationFramework::intToDecimalString(instance_id);
	sFormattedEntry.anonymous() += "] ";
	sFormattedEntry += sEntry;
	this->LogBussiness(sFormattedEntry);
}

//---------------------------------------------------------------------------
/**
  * Private helper method that stores provided entry into the Log
  */
void c_BussinessLogger::StoreEntryInLog(c_BussinessLogEntry* pEntry) {
	c_ThreadSynchronizer ts(this->m_LogEntryThreadGate);
	m_UILogEntries.push(pEntry);
	if (!this->m_LogStream.is_open()) {
		// Try to open the file
		c_FilePath LogFilePath = c_Application::getExeRootPath();
		c_FileName exeFileName = c_Application::ExeName();
		c_DataRepresentationFramework::c_UTF16String sLogFileName = exeFileName.NameWithoutExtension();
		sLogFileName.anonymous() += L".log";
		LogFilePath += sLogFileName;
		try {
			this->m_LogStream.open(LogFilePath.toString().c_str());
			if (this->m_LogStream) {
				c_LogString sMessage("Openend business log file ");
				sMessage += c_DataRepresentationFramework::toUTF8String(LogFilePath.toString());
				this->StoreEntryInLog(new c_BussinessLogEntry(e_BussinessLogEntryType_Bussiness,sMessage));
			}
			else {
				c_LogString sMessage("Failed to create test bench persistent log file. Write protected? File Name=");
				sMessage += c_DataRepresentationFramework::toUTF8String(LogFilePath.toString());
				throw std::runtime_error(sMessage.c_str());
			}
		}
		catch (std::exception& e) {
//			c_LogString sMessage(__FUNCTION__". Exception = \"");
			c_LogString sMessage(METHOD_PREFIXED_LOG_STRING(". Exception = \""));
			sMessage += _UTF8sz(e.what());
			sMessage += _UTF8sz("\"");
			// Failed to open the file. Add log entry directlly to queue
			m_UILogEntries.push(new c_BussinessLogEntry(e_BussinessLogEntryType_DesignInsufficiency,sMessage));
		}
		catch (...) {
//			c_LogString sMessage(__FUNCTION__". General Ecxception cought. Failed to create test bench persistent log file. Name=\"");
			c_LogString sMessage(METHOD_PREFIXED_LOG_STRING(". General Ecxception cought. Failed to create test bench persistent log file. Name=\""));
			sMessage += c_DataRepresentationFramework::toUTF8String(LogFilePath.toString());
			sMessage += _UTF8sz("\"");
			// Failed to open the file. Add log entry directlly to queue
			m_UILogEntries.push(new c_BussinessLogEntry(e_BussinessLogEntryType_DesignInsufficiency,sMessage));
		}
	}

	if (this->m_LogStream.is_open()) {
		this->m_LogStream << pEntry->toString() << std::endl;
		this->m_LogStream.flush();
	}
}
//---------------------------------------------------------------------------
/**
  * returns the indent string to be used for current exectuion thread
  */
c_LogString c_BussinessLogger::getThreadDependentIndentString() {
	c_LogString result;
	result.resize(m_indentOfCurrentThreadLog,' ');
	return result;
}

//---------------------------------------------------------------------------

/**
  * Returns next stored log entry from the log entry storage
  * and removes it from the storage. Used by user interface to poll
  * for entries that are to be shown in the user interface.
  * Returns NULL if there are no entries to return.
  */
c_BussinessLogEntry* c_BussinessLogger::popUILogEntry() {
	c_ThreadSynchronizer ts(this->m_LogEntryThreadGate);
	c_BussinessLogEntry* result = NULL;
	if (!this->m_UILogEntries.empty()) {
		result = this->m_UILogEntries.front();
		this->m_UILogEntries.pop();
	}
	return result;
}

//---------------------------------------------------------------------------
/**
  * Returns number of entries in the logger that is not popped
  * for UI view.
  */
int c_BussinessLogger::unPoppedUIEntriesCount() {
	c_ThreadSynchronizer ts(this->m_LogEntryThreadGate);
	return m_UILogEntries.size();
}

/**
  * Increments the indentations used for development trace log entries
  */
void c_BussinessLogger::incrementDevelopmentTraceIndent() {
	m_indentOfCurrentThreadLog += INDENT_CHANGE_WIDTH;
//	this->m_sCurrentDevelopmentTraceIndentString.resize(this->m_sCurrentDevelopmentTraceIndentString.size()+INDENT_CHANGE_WIDTH,' ');
}

/**
  * Decrements the indentations used for development trace log entries
  */
void c_BussinessLogger::decrementDevelopmentTraceIndent() {
	if (true) {
		m_indentOfCurrentThreadLog -= INDENT_CHANGE_WIDTH;
	}
	else {
		m_indentOfCurrentThreadLog = 0;
    }
//	if (this->m_sCurrentDevelopmentTraceIndentString.size() >= 2) {
//		this->m_sCurrentDevelopmentTraceIndentString.resize(this->m_sCurrentDevelopmentTraceIndentString.size()-INDENT_CHANGE_WIDTH);
//	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


int BusinessLogUnit_main() {
#ifdef COMPILE_TEST_CODE
	unit_test();
#endif // COMPILE_TEST_CODE
	return 0;
}

#ifdef RUN_TEST_CODE
	int test_result = BusinessLogUnit_main(); // Exeute main
#endif // RUN_TEST_CODE

#undef COMPILE_TEST_CODE
#undef RUN_TEST_CODE

