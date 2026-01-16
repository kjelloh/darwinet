//---------------------------------------------------------------------------

#ifndef PeerProxyMailH
#define PeerProxyMailH
//---------------------------------------------------------------------------
#include "DarwinetBase.h"
//---------------------------------------------------------------------------

namespace darwinet {

	/**
	  * Models a Peer Proxy that uses mail for message exchange
	  */
	class c_PeerProxyMail : public c_PeerProxy {
	public:

		typedef boost::shared_ptr<c_PeerProxyMail> shared_ptr;

		/**
		  * Creates an implementation of this interface
		  */
		static c_PeerProxyMail::shared_ptr create(const c_DarwinetString& sMailAdress);

	};

};

#endif
