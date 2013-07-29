//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "PeerSourceMail.h"
#include "IMAPClientFrameUnit.h"
#include "DarwinetMessages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace darwinet {

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Implements the c_PeerSourceMail interface
	  */
	class c_PeerSourceMailImpl : public c_PeerSourceMail {
	public:

		/**
		  * Constructor
		  */
		c_PeerSourceMailImpl();

		// Begin c_PeerSource

		/**
		  * Receive a delta from this source.
		  */
		virtual miv::c_DeltaSEPSI::shared_ptr receive();

		// End c_PeerSource
	private:

		/**
		  * Private storage of our TIMAPClientFrame instance
		  */
		TIMAPClientFrame* m_pIMAPClientFrame;

		/**
		  * Returns access to our IMAPClientFrame
		  * ,Creating it if it does not yet exist.
		  */
		TIMAPClientFrame* getIMAPClientFrame();


	};


	/**
	  * Constructor
	  */
	c_PeerSourceMailImpl::c_PeerSourceMailImpl()
		: m_pIMAPClientFrame(NULL)
	{
	};

	// Begin c_PeerSource

	/**
	  * Returns access to our IMAPClientFrame
	  * ,Creating it if it does not yet exist.
	  */
	TIMAPClientFrame* c_PeerSourceMailImpl::getIMAPClientFrame() {
		if (this->m_pIMAPClientFrame == NULL) {
			this->m_pIMAPClientFrame = new TIMAPClientFrame(Application);
		}
		return this->m_pIMAPClientFrame;
	}

	/**
	  * Receive a delta from this source.
	  */
	miv::c_DeltaSEPSI::shared_ptr c_PeerSourceMailImpl::receive() {
		miv::c_DeltaSEPSI::shared_ptr result;
		try {
			LOG_NOT_IMPLEMENTED;
			String sMessage = this->getIMAPClientFrame()->GetMessage();
			// The string should be a Peer message represented in BERTLV
			c_DataRepresentationFramework::c_AsciiString sBERTLV = c_DataRepresentationFramework::toAsciiString(sMessage);
			c_DataRepresentationFramework::t_raw_vector bertlv_vector = c_DataRepresentationFramework::parseHexNibblePairString(sBERTLV);
			result = createDeltaSEPSI(bertlv_vector);
		}
		CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;
		return result;
	}

	// End c_PeerSource


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Creates an instance that implements this interface
	  */
	c_PeerSourceMail::shared_ptr c_PeerSourceMail::create() {
		c_PeerSourceMail::shared_ptr result(new c_PeerSourceMailImpl());
		return result;
    }

}