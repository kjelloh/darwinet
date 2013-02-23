/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------


#pragma hdrstop

#include "DateAndTimeFramework.h"
#include <sstream>
#include <string>

# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
# pragma warn +8072 // Enable again. See above

#include "DataRepresentationFrameWork.h"
#include "BusinessLogUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/**
  * Creates a time stamp with current time setting
  */
c_YYYYMMDDHHMMSSmmm::c_YYYYMMDDHHMMSSmmm() {
	GetLocalTime(&this->m_DateAndTime);
}
//---------------------------------------------------------------------------

/**
  * Creates a time stamp from provided time stamp string
  */
c_YYYYMMDDHHMMSSmmm::c_YYYYMMDDHHMMSSmmm(c_DataRepresentationFramework::c_AsciiString sYYMMDDHHMMSSmmm) {
	try {
		if (sYYMMDDHHMMSSmmm.size()==17) {
			// The size is correct
			this->m_DateAndTime.wYear = atoi(sYYMMDDHHMMSSmmm.substr(0,4).c_str());
			this->m_DateAndTime.wMonth = atoi(sYYMMDDHHMMSSmmm.substr(2,2).c_str());
			this->m_DateAndTime.wDay = atoi(sYYMMDDHHMMSSmmm.substr(4,2).c_str());
			this->m_DateAndTime.wHour = atoi(sYYMMDDHHMMSSmmm.substr(6,2).c_str());
			this->m_DateAndTime.wMinute = atoi(sYYMMDDHHMMSSmmm.substr(8,2).c_str());
			this->m_DateAndTime.wSecond = atoi(sYYMMDDHHMMSSmmm.substr(10,2).c_str());
			this->m_DateAndTime.wMilliseconds = atoi(sYYMMDDHHMMSSmmm.substr(12,3).c_str());

			// Day of week not supported in this format
			this->m_DateAndTime.wDayOfWeek = 0;

			m_sYYYYMMDDHHMMSSmmm = sYYMMDDHHMMSSmmm;
		}
	}
//	catch (const std::exception& e) {
//		c_LogString sMessage("c_YYYYMMDDHHMMSSmmm::c_YYYYMMDDHHMMSSmmm failed. Exception=");
//		sMessage += e.what();
//		LOG_DESIGN_INSUFFICIENCY(sMessage);
//	}
//	catch (...) {
//		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_YYYYMMDDHHMMSSmmm::c_YYYYMMDDHHMMSSmmm failed"));
//	}
	CATCH_AND_LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY
	CATCH_AND_LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY
}
//---------------------------------------------------------------------------

c_DataRepresentationFramework::c_AsciiString c_YYYYMMDDHHMMSSmmm::getYYYYMMDDHHMMSSmmm() {
	if (m_sYYYYMMDDHHMMSSmmm.size()<15) {
//		char szBuf[4];
//		sprintf(szBuf,"%04d",this->m_DateAndTime.wYear);
//		m_sYYYYMMDDHHMMSSmmm = szBuf;
//		sprintf(szBuf,"%02d",this->m_DateAndTime.wMonth);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;
//		sprintf(szBuf,"%02d",this->m_DateAndTime.wDay);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;
//		sprintf(szBuf,"%02d",this->m_DateAndTime.wHour);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;
//		sprintf(szBuf,"%02d",this->m_DateAndTime.wMinute);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;
//		sprintf(szBuf,"%02d",this->m_DateAndTime.wSecond);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;
//		sprintf(szBuf,"%03d",this->m_DateAndTime.wMilliseconds);
//		m_sYYYYMMDDHHMMSSmmm += szBuf;

		m_sYYYYMMDDHHMMSSmmm.anonymous() = (boost::format(
			"%04d%02d%02d%02d%02d%02d%03d")
			% this->m_DateAndTime.wYear
			% this->m_DateAndTime.wMonth
			% this->m_DateAndTime.wDay
			% this->m_DateAndTime.wHour
			% this->m_DateAndTime.wMinute
			% this->m_DateAndTime.wSecond
			% this->m_DateAndTime.wMilliseconds).str();
	}
	return m_sYYYYMMDDHHMMSSmmm;
}
//---------------------------------------------------------------------------
/**
  * Returns this date and time as a formatted string
  */
c_DataRepresentationFramework::c_AsciiString c_YYYYMMDDHHMMSSmmm::getFormatedDateAndTime() const {
	c_DataRepresentationFramework::c_AsciiString result("# failed #");
	try {
		c_DataRepresentationFramework::c_AsciiString sYYMMDDHHMMSSmmm = const_cast<c_YYYYMMDDHHMMSSmmm*>(this)->getYYYYMMDDHHMMSSmmm();
		c_DataRepresentationFramework::c_AsciiString sAssembly;
		sAssembly += sYYMMDDHHMMSSmmm.substr(0,4); // year
		sAssembly.anonymous() += "-";
		sAssembly += sYYMMDDHHMMSSmmm.substr(4,2); // month
		sAssembly.anonymous() += "-";
		sAssembly += sYYMMDDHHMMSSmmm.substr(6,2); // day of month
		sAssembly.anonymous() += " ";
		sAssembly += sYYMMDDHHMMSSmmm.substr(8,2); // Hour
		sAssembly.anonymous() += ":";
		sAssembly += sYYMMDDHHMMSSmmm.substr(10,2); // minute
		sAssembly.anonymous() += ":";
		sAssembly += sYYMMDDHHMMSSmmm.substr(12,2); // second
		sAssembly.anonymous() += ".";
		sAssembly += sYYMMDDHHMMSSmmm.substr(14,3); // milli second

		result = sAssembly; // Assign to result if no exceptions on the way :)
	}
//	catch (const std::exception e) {
//		c_DataRepresentationFramework::c_UTF8String sMessage("c_YYYYMMDDHHMMSSmmm::getFormatedDateAndTime() failed. Exception=");
//		sMessage += _UTF8sz(e.what());
//		LOG_DESIGN_INSUFFICIENCY(sMessage);
//	}
//	catch (...) {
//		LOG_DESIGN_INSUFFICIENCY(_Asciisz("c_YYYYMMDDHHMMSSmmm::getFormatedDateAndTime() failed. General exception"));
//	}
	CATCH_AND_LOG_STD_EXCEPTION_DESIGN_INSUFFICIENCY
	CATCH_AND_LOG_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY
	return result;
}
//---------------------------------------------------------------------------
