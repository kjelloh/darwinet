/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------


#pragma hdrstop

#include "BerTlv.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#include "BerTlv.h"
#include <cmath> // pow
#include "BusinessLogUnit.h"

# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
# pragma warn +8072 // Enable again. See above

namespace bertlv {

	// ============================ class BerTlvHelperMethods =================================
	bool BerTlvHelperMethods::isSet(t_byte byte, const int bitindex) {
		bool result = false;
		if ((bitindex >= 1) && (bitindex <= 8)) {
			// OK
//			VALIDATE(((bitindex >= 1) && (bitindex <= 8)));
			// bitindex in range 1-8
			// e.g. bitindex = 8, b = 10110001
			// mask -> 2^8 = 10000000
			// b & mask = 10000000
			// -> b = mask
			int mask = (int)std::pow((double)2, (double)(bitindex - 1));
			int res = byte & mask;
			if (res == mask) {
				result = true;
			}
			else {
				result = false;
			}
		}
		else {
			LOG_DESIGN_INSUFFICIENCY_I(_UTF8sz("BerTlvHelperMethods::isSet failed. Called with invalid bitindex=%d"),bitindex);
		}
		return result;
	}

	void BerTlvHelperMethods::safe_sprintf(c_DataRepresentationFramework::c_ISO_8859_1_String& buf, const c_DataRepresentationFramework::c_ISO_8859_1_String& format, int val) {
		buf.anonymous() = (boost::format(format) % val).str();
	}

	// ============================ (END) class BerTlvHelperMethods =================================
	// ============================ BerTlvPrimitiveContent =================================
	BerTlvPrimitiveContent::BerTlvPrimitiveContent(c_BertlvByteVector bytes) : bytes(bytes) {
	}

	BerTlvPrimitiveContent::~BerTlvPrimitiveContent() {
	}

	bool BerTlvPrimitiveContent::isComposite() const {
		return false;
	}

	c_BertlvByteVector BerTlvPrimitiveContent::byteVector() const {
		return bytes;
	}

	// ============================ (END) BerTlvPrimitiveContent =================================
} // namespace bertlv
