//---------------------------------------------------------------------------
#ifndef DarwinetMessagesH
#define DarwinetMessagesH
//---------------------------------------------------------------------------
#include "DarwinetBase.h"
#include "BerTlv.h"
//---------------------------------------------------------------------------

namespace darwinet {

	/**
	  * Creates a DeltaSEPSI instance from provided BERTLV
	  */
	miv::c_DeltaSEPSI::shared_ptr createDeltaSEPSI(const bertlv::c_BertlvByteVector& bytes);

} // namespace darwinet

#endif
