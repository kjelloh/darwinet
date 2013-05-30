//---------------------------------------------------------------------------

#ifndef PeerSinkMailH
#define PeerSinkMailH
//---------------------------------------------------------------------------
#include "DarwinetBase.h"
//---------------------------------------------------------------------------

namespace darwinet {
	/**
	  * Models a Peer Sink that uses mail for message exchange
	  */
	class c_PeerSinkMail : public c_PeerSink {
	public:

		/**
		  * Creates a Mail Sink defined by provided mail adress
		  */
		c_PeerSinkMail(const c_DarwinetString& sMailAdress);

		// Begin c_PeerSink

		/**
		  * Send provided delta to the Sink we represent
		  */
		virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

		// End c_PeerSink

	};

};

#endif
