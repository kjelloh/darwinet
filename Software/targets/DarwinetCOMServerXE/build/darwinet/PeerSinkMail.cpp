//---------------------------------------------------------------------------

#pragma hdrstop

#include "PeerSinkMail.h"
#include "PeerMailFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Models Sinks that are defined by an e-mail adress
  */
namespace darwinet {

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	class c_PeerSinkMailImpl : public c_PeerSinkMail {
	public:

		/**
		  * Constructor
		  */
		c_PeerSinkMailImpl(const c_DarwinetString& sMailAdress);

		// Begin c_PeerSink

		/**
		  * Send provided delta to the Sink we represent
		  */
		virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

		// End c_PeerSink

	private:
		/**
		  * Private storage of our TPeerMailFrame instance
		  */
		boost::shared_ptr<TPeerMailFrame> m_pPeerMailFrame;

		/**
		  * Returns our TPeerMailFrame instance, creating it if it does not yet exist
		  */
		boost::shared_ptr<TPeerMailFrame> getPeerMailFrame();

		/**
		  * Creates a string representation of provided delta
		  * to be sent with mail
		  */
		c_DarwinetString toMailString(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

	};

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Creates a Mail Sink defined by provided mail adress
	  */
	c_PeerSinkMailImpl::c_PeerSinkMailImpl(const c_DarwinetString& sMailAdress)
	{
		LOG_METHOD_SCOPE;
	}

	// Begin c_PeerSink

	/**
	  * Send provided delta to the Sink we represent
	  */
	void c_PeerSinkMailImpl::send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
		LOG_NOT_IMPLEMENTED;
		// Transform the Delta into sendable text string
		c_DarwinetString sMessage = this->toMailString(pDelta);
		// Send it to Peer Sink
		this->getPeerMailFrame()->send(sMessage.c_str());
	}

	// End c_PeerSink

	/**
	  * Returns our TPeerMailFrame instance, creating it if it does not yet exist
	  */
	boost::shared_ptr<TPeerMailFrame> c_PeerSinkMailImpl::getPeerMailFrame() {
		if (!this->m_pPeerMailFrame) {
			this->m_pPeerMailFrame.reset(new TPeerMailFrame(Application));
		}
		return this->m_pPeerMailFrame;
	}

	/**
	  * Creates a string representation of provided delta
	  * to be sent with mail
	  */
	c_DarwinetString c_PeerSinkMailImpl::toMailString(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
		c_DarwinetString result;
		LOG_NOT_IMPLEMENTED;
		return result;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Creates an implementation of this interface
	  */
	c_PeerSinkMail::shared_ptr c_PeerSinkMail::create(const c_DarwinetString& sMailAdress) {
		c_PeerSinkMail::shared_ptr result(new c_PeerSinkMailImpl(sMailAdress));
		return result;
	}


}