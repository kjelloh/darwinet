//---------------------------------------------------------------------------

#ifndef DateAndTimeFrameworkH
#define DateAndTimeFrameworkH
//---------------------------------------------------------------------------
//#include <string> // std::string
#include <stdio.h> // sprintf...
#include <windows.h> // SYSTEMTIME, GetSystemTime()...
#include "DataRepresentationFrameWork.h" // c_DataRepresentationFramework::c_AsciiString

//---------------------------------------------------------------------------
/**
  * Represents a time string of the format YYMMDDHHMMSSmmm
  * that is Year,Month,Date,Hour,Minutes,Seconds and finally milliseconds
  */
class PACKAGE c_YYYYMMDDHHMMSSmmm {
public:
	/**
	  * Creates a time stamp with current time setting
	  */
	c_YYYYMMDDHHMMSSmmm();

	/**
	  * Creates a time stamp from provided time stamp string
	  */
	c_YYYYMMDDHHMMSSmmm(c_DataRepresentationFramework::c_AsciiString sYYMMDDHHMMSSmmm);

	/**
	  * Returns formatted time string
	  */
	c_DataRepresentationFramework::c_AsciiString getYYYYMMDDHHMMSSmmm();

    /**
      * Returns this date and time as a formatted string
      */
    c_DataRepresentationFramework::c_AsciiString getFormatedDateAndTime() const;

private:
	SYSTEMTIME m_DateAndTime;

	/**
	  * Private storage of raw time string. Created on demand
	  */
	c_DataRepresentationFramework::c_AsciiString m_sYYYYMMDDHHMMSSmmm;

};

#endif
