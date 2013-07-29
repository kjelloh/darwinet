//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "DarwinetMessages.h"
#include "DarwinetDeltas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace darwinet {

	/**
	  * Creates a DeltaSEPSI instance from provided BERTLV
	  */
	miv::c_DeltaSEPSI::shared_ptr createDeltaSEPSI(const bertlv::c_BertlvByteVector& bytes) {
		miv::c_DeltaSEPSI::shared_ptr result;
		try {
			bertlv::asn1::c_ConstASN1BERTLVPtr  pBerTlv = bertlv::asn1::c_ASN1BERTLVParser::parseBerTlv(bytes);
			// Map the structure to a c_DeltaSEPSI instance
			// 130729, for now this should be a hard coded integer Delta
			// TODO: Implement message structure to represent any Delta
			if (pBerTlv->getTagValue() == bertlv::asn1::eASN1Tag_INTEGER) {
				// OK, it is an integer Delta
				c_DeltaIndex::shared_ptr pDeltaIndex(new c_DeltaIndex());
				*pDeltaIndex += c_DeltaIndex::Node(_UTF8sz("dummy_index")); // Dummy index
				int delta = bertlv::asn1::toASN1INTEGER(pBerTlv);
				result.reset(new miv::c_IntDeltaImpl(pDeltaIndex,delta));
			}
		} catch (...) {
		}
		return result;
	}

}