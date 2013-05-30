//---------------------------------------------------------------------------

#pragma hdrstop

#include "PeerSinkMail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Models Sinks that are defined by an e-mail adress
  */
namespace darwinet {

	/**
	  * Creates a Mail Sink defined by provided mail adress
	  */
	c_PeerSinkMail::c_PeerSinkMail(const c_DarwinetString& sMailAdress)
	{
		LOG_METHOD_SCOPE;
	}

	// Begin c_PeerSink

	/**
	  * Send provided delta to the Sink we represent
	  */
	void c_PeerSinkMail::send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
		LOG_NOT_IMPLEMENTED;
    }

	// End c_PeerSink


}