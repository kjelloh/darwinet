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

		typedef boost::shared_ptr<c_PeerSinkMail> shared_ptr;

		/**
		  * Creates an implementation of this interface
		  */
		static c_PeerSinkMail::shared_ptr create(const c_DarwinetString& sMailAdress);

	};

};

#endif
