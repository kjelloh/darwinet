//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "BerTlv.h"
#include <cmath> // pow
#include "BusinessLogUnit.h"

# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
# pragma warn +8072 // Enable again. See above
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

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

//	void BerTlvHelperMethods::safe_sprintf(c_DataRepresentationFramework::c_ISO_8859_1_String& buf, const c_DataRepresentationFramework::c_ISO_8859_1_String& format, int val, int maxchars) {
// maxchars not used after refactoring below 101118/KoH
	void BerTlvHelperMethods::safe_sprintf(c_DataRepresentationFramework::c_ISO_8859_1_String& buf, const c_DataRepresentationFramework::c_ISO_8859_1_String& format, int val) {
		buf.anonymous() = (boost::format(format) % val).str();
//		int ret = sprintf(buf, format, val);
//		if ((ret < 0) || (ret > maxchars)) {
//			throw std::runtime_error("error writing to buffer");
//		}
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

	namespace asn1 {

		/**
		  * Interprets provided c_ASN1BERTLV as an INTEGER and returns the value
		  */
		int toASN1INTEGER(c_ConstASN1BERTLVPtr pASN1BERTL) {
			int result = 0;
			/*
			8.3.3

			The contents octets shall be a two's complement binary number equal to the integer value,
			and consisting of bits 8 to 1 of the first octet, followed by bits 8 to 1 of the second octet,
			followed by bits 8 to 1 of each octet in turn up to and including the last octet of the contents octets.
			NOTE – The value of a two's complement binary number is derived by numbering the bits
			in the contents octets, starting with bit 1 of the last octet as bit zero
			and ending the numbering with bit 8 of the first octet.
			Each bit is assigned a numerical value of 2N, where N is its position in the above numbering
			sequence. The value of the two's complement binary number is obtained by
			summing the numerical values assigned to each bit for those bits which are set to one,
			excluding bit 8 of the first octet, and then reducing this value by the numerical value
			assigned to bit 8 of the first octet if that bit is set to one.
			*/

			if (pASN1BERTL->getTagValue() == eASN1Tag_INTEGER) {
				// OK. It is an integer
				if (pASN1BERTL->getContent()->isComposite() == false) {
					// OK. It is primitive
					c_BertlvByteVector bytes = pASN1BERTL->getContent()->byteVector();
					unsigned int unsigned_value = 0;
					unsigned int first_octet_bit8_value = 0x80; // start of with value of one octet
					for (c_BertlvByteVector::iterator iter = bytes.begin(); iter != bytes.end(); ++iter) {
						unsigned_value <<= 8; // shift one octet left
						first_octet_bit8_value <<= 8; // shift highst bit to next octet
						unsigned_value += *iter; // Add current byte
					}
					first_octet_bit8_value >>= 8; // Correct for one-shift-to-much
					if (unsigned_value > first_octet_bit8_value) {
						// The value is a negative value in twos complement representation
						result = first_octet_bit8_value - unsigned_value; // the signed value of the twos-complement representation
					}
					else {
						result = unsigned_value;
					}
				}
			}
			return result;
		}

	}
} // namespace bertlv
