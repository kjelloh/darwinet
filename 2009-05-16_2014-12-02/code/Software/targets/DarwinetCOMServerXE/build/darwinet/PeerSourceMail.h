//---------------------------------------------------------------------------

#ifndef PeerSourceMailH
#define PeerSourceMailH
//---------------------------------------------------------------------------
#include "DarwinetBase.h"
//---------------------------------------------------------------------------

namespace darwinet {
	/**
	  * Implements a Peer Source that is a amil account
	  */
	class c_PeerSourceMail : public c_PeerSource {
	public:

		typedef boost::shared_ptr<c_PeerSourceMail> shared_ptr;

		/**
		  * Creates an instance that implements this interface
		  */
		static c_PeerSourceMail::shared_ptr create();

	};


}; // namespace darwinet
#endif
