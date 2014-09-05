//---------------------------------------------------------------------------

#ifndef BusinessLogUnitH
#define BusinessLogUnitH
#include <string>
#include <boost/shared_ptr.hpp> // Boost Requires e.g., $(CG_64_BOOST_ROOT) in the include path
#include <boost/make_shared.hpp>
//---------------------------------------------------------------------------

typedef std::string c_LogString;

class c_BussinessLoggerIfc {
private:
	typedef c_BussinessLoggerIfc c_this;
public:
	typedef boost::shared_ptr<c_this> shared_ptr;

	static shared_ptr instance() {
		if (!m_pInstance) {
			m_pInstance = boost::make_shared<c_this>();
		}
		return m_pInstance;
	}

	virtual void LogNotImplemented(const c_LogString& sEntry) {
		/* Not implemented */
	}

private:
	static shared_ptr m_pInstance;
};

#define METHOD_NAME c_LogString(__func__)

// Log a design insufficiency

// Log a design insufficiency about current function not implemented
#define LOG_NOT_IMPLEMENTED c_BussinessLoggerIfc::instance()->LogNotImplemented(__FUNC__);

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
		c_LogString sFunctionEntryString("::"__FUNCTION__);\
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);
	#define LOG_METHOD_SCOPE \
		c_LogString sFunctionEntryString(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this))); \
		sFunctionEntryString += _UTF8sz("::");\
		sFunctionEntryString += _UTF8sz(__FUNCTION__);\
		c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(sFunctionEntryString);

	#define LOG_SCOPE_S(S) c_DevelopmentLogTraceIndentator DevelopmentLogTraceIndentator(S);
	#define LOG_FUNCTION_SCOPE_S(S) \
		c_LogString sFunctionEntryString("::"__FUNCTION__"(");\
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
		c_LogString sMessage(__FUNCTION__" failed. Exception=");\
		sMessage += toLogString(e.Message);\
		LOG_DESIGN_INSUFFICIENCY(sMessage);

#define LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY \
		c_LogString sMessage(__FUNCTION__" failed. Exception=");\
		sMessage += _UTF8sz(e.what());\
		LOG_DESIGN_INSUFFICIENCY(sMessage)

#define LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY \
		c_LogString sMessage(__FUNCTION__" failed. General Exception cought.");\
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
