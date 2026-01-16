//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "PeerProxyMail.h"
#include "PeerMailFrameUnit.h"
#include <boost/iostreams/concepts.hpp>  // sink
#include <boost/iostreams/stream.hpp>
#include "bertlv/BerTlv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

/**
  * Models Proxies that are defined by an e-mail adress
  */
namespace darwinet {

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	class c_PeerProxyMailImpl : public c_PeerProxyMail {
	public:

		/**
		  * Constructor
		  */
		c_PeerProxyMailImpl(const c_DarwinetString& sMailAdress);

		// Begin c_PeerProxy

		/**
		  * Send provided delta to the Peer we represent
		  */
		virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

		// End c_PeerProxy

	protected:

		/**
		  * Returns the Package instance that is up for sending
		  * creating the instance if none exists
		  */
		virtual c_PeerPackage::shared_ptr getPackage();

		/**
		  * Sends the package that is up for sending and deletes the current instance
		  */
		virtual void purge();

	private:

		/**
		  * Private storage of our current package up for sending to
		  * our remote peer.
		  */
		c_PeerPackage::shared_ptr m_pPeerPackage;

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
	  * Creates a Mail Peer Proxy defined by provided mail adress
	  */
	c_PeerProxyMailImpl::c_PeerProxyMailImpl(const c_DarwinetString& sMailAdress)
	{
		LOG_METHOD_SCOPE;
	}

	// Begin c_PeerProxy

	/**
	  * Send provided delta to the Peer we represent
	  */
	void c_PeerProxyMailImpl::send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
		LOG_NOT_IMPLEMENTED;

		if (true) {
			// Transform the Delta into sendable text string
			c_DarwinetString sMessage = this->toMailString(pDelta);
			// Stream it to Peer Sink
			this->getPeerMailFrame()->send(sMessage.c_str());
		}

		if (false) {
			// Add to package and stream package to Mail sink
			this->getPackage()->add(pDelta);
			this->purge();
		}
	}

	// End c_PeerProxy

	/**
	  * Returns the Package instance that is up for sending
	  * creating the instance if none exists
	  */
	c_PeerPackage::shared_ptr c_PeerProxyMailImpl::getPackage() {
		if (!this->m_pPeerPackage) {
			this->m_pPeerPackage = c_PeerPackage::create();
		}
		return this->m_pPeerPackage;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Models a Mail Sink to be used as Device for Boost streaming
	  */
	class c_MailSink : public boost::iostreams::sink {
	public:
		// begin boost::iostreams::sink

		std::streamsize write(const char* s, std::streamsize n);

		// End boost::iostreams::sink

		/* Other members */
	};

	// begin boost::iostreams::sink

	std::streamsize c_MailSink::write(const char* s, std::streamsize n) {
		LOG_NOT_IMPLEMENTED;
		return n;
	}

	// End boost::iostreams::sink

	/**
	  * Stream package to an ostream
	  */
	std::ostream& operator<<(const std::ostream& ostream,const c_PeerPackage& package);

	/**
	  * Stream package to an ostream
	  */
	std::ostream& operator<<(std::ostream& ostream,const c_PeerPackage& package) {
		LOG_NOT_IMPLEMENTED;
		return ostream;
    }

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Sends the package that is up for sending and deletes the current instance
	  */
	void c_PeerProxyMailImpl::purge() {
		if (this->m_pPeerPackage) {
			/*
			From: http://objectmix.com/c/403601-stringstream-strstream-memory-buffers.html
			If you want a different data source resp. sink, you typically
			- create a std::[io]stream object and initialize it with
			an appropriate streambuf object providing that data source/sink, or
			- write your own convenience classes (or templates) derived from
			std::basic_[io]stream (or specializations thereof)
			*/
			/*
			http://www.boost.org/doc/libs/1_53_0/libs/iostreams/doc/guide/generic_streams.html
			Good information of boost stream using sinks and sources to direct streaming
			*/
			// Send the package we have in store for sending
			boost::iostreams::stream<c_MailSink> out;
			out << *this->m_pPeerPackage;
			this->m_pPeerPackage.reset(); // Release our instance
		}
	}

	/**
	  * Returns our TPeerMailFrame instance, creating it if it does not yet exist
	  */
	boost::shared_ptr<TPeerMailFrame> c_PeerProxyMailImpl::getPeerMailFrame() {
		if (!this->m_pPeerMailFrame) {
			this->m_pPeerMailFrame.reset(new TPeerMailFrame(Application));
		}
		return this->m_pPeerMailFrame;
	}

	/**
	  * Creates a string representation of provided delta
	  * to be sent with mail
	  */
	c_DarwinetString c_PeerProxyMailImpl::toMailString(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
		c_DarwinetString result;
		// Encode in BERTLV
		bertlv::c_BertlvByteVector value;
		value.push_back(17);
		LOG_NOT_IMPLEMENTED;
		boost::shared_ptr<const bertlv::asn1::c_ASN1BERTLV> pBERTLV(bertlv::asn1::c_ASN1BERTLV::createPrimitiveBerTlv(bertlv::asn1::eASN1Tag_INTEGER,value));
		result = c_DataRepresentationFramework::createHexNibbleString(pBERTLV->byteVector());
		return result;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Creates an implementation of this interface
	  */
	c_PeerProxyMail::shared_ptr c_PeerProxyMail::create(const c_DarwinetString& sMailAdress) {
		c_PeerProxyMail::shared_ptr result(new c_PeerProxyMailImpl(sMailAdress));
		return result;
	}


}