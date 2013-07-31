//---------------------------------------------------------------------------

#pragma hdrstop

#include "InProcDarwinetEngineFramework.h"
#include "DarwinetDeltas.h"
#include "PeerProxyMail.h"
#include "PeerSourceMail.h"
#include <map>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace darwinet {

	/**
	  * MIV name space header
	  */
	namespace miv {

		/**
		  * Models a Distributor of MIV deltas
		  */
		class c_DeltaMIVDistributor {
		public:

			// Begin c_DeltaMIVDistributor

			/**
			  * Distributes provided delta to peers and to ourself.
			  */
			virtual void distribute(const c_DeltaSEPSI::shared_ptr& pDelta) = 0;

			// End c_DeltaMIVDistributor


		};

	}; // end namespace miv


	/**
	  * Implementes c_PeerPackage interface
	  */
	class c_PeerPackageImpl : public c_PeerPackage {
	public:

		/**
		  * Constructor
		  */
		c_PeerPackageImpl();

		// Begin c_PeerPackage

		/**
		  * Adds provided c_DeltaSEPSI instace to "us"
		  */
		virtual void add(const miv::c_DeltaSEPSI::shared_ptr& pDeltaSEPSI);

		// End c_PeerPackage

	};

	/**
	  * Implementation of the miv namespace
	  */
	namespace miv {

		/**
		  * Models an implementation of the c_MIVValueInstance interface
		  */
		class c_MIVValueInstanceImpl : public c_MIVValueInstance {
		public:

			typedef boost::shared_ptr<c_MIVValueInstanceImpl> shared_ptr;

			/**
			  * Constructor
			  */
			c_MIVValueInstanceImpl(const c_DeltaIndex::shared_ptr& pCurrentDeltaIndex);

			/**
			  * Virtual destructor
			  */
			virtual ~c_MIVValueInstanceImpl();

			// Begin c_MIVValueInstance

			/**
			  * Sets this Instance Value to the provided Value represented as a string
			  */
			virtual void setValue(const c_DarwinetString& sValue);

			/**
			  * Returns the index of the last Delta applied to get our current Value.
			  */
			virtual c_DeltaIndex::shared_ptr getCurrentDeltaIndex();


			// End c_MIVValueInstance

			// Begin c_MIVValueInstanceImpl

			/**
			  * Applies provided Delta to this instance
			  */
			virtual void applyDelta(miv::c_DeltaSEPSI::shared_ptr pDelta);

			// End c_MIVValueInstanceImpl

		private:

			/**
			  * Returns the difference between provided value and the value
			  * we actually have
			  */
			c_DeltaSEPSI::shared_ptr diff(const c_DarwinetString& sValue);

			/**
			  * Private storage of the index of the last delta applied to us.
			  */
			c_DeltaIndex::shared_ptr m_pCurrentDeltaIndex;

			/**
			  * Private storage of our Integer Value
			  */
			int m_value;


		};

		/**
		  * Models a Peer Proxy that connects to "us"
		  */
		class c_PeerProxySelf : public c_PeerProxy {
		public:

			typedef boost::shared_ptr<c_PeerProxySelf> shared_ptr;

			/**
			  * Creates a new implementation of this interface
			  */
			static c_PeerProxySelf::shared_ptr create();

		};

		class c_PeerProxySelfImpl : public c_PeerProxySelf {
		public:

			/**
			  * Constructor
			  */
			c_PeerProxySelfImpl();

			// Begin c_PeerProxy

			/**
			  * Send provided delta to the Peer we represent
			  */
			virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

			// End c_PeerProxy

		};

		/**
		  * Implements the c_DeltaMIVDistributor interface
		  */
		class c_DeltaMIVDistributorImpl : public c_DeltaMIVDistributor {
		public:

			typedef boost::shared_ptr<c_DeltaMIVDistributorImpl> shared_ptr;

			/**
			  * Constructor
			  */
			c_DeltaMIVDistributorImpl();

			// Begin c_DeltaMIVDistributor

			/**
			  * Distributes provided delta to peers and to ourself.
			  */
			virtual void distribute(const c_DeltaSEPSI::shared_ptr& pDelta);

			// End c_DeltaMIVDistributor

		private:

			/**
			  * Distributes provided delta to provided Peers
			  */
			void distribute(const c_DeltaSEPSI::shared_ptr& pDelta,const c_PeerProxies_shared_ptr& pPeers);

			/**
			  * Returns an instance of Peers selected to be targets of our delta distributions
			  */
			c_PeerProxies_shared_ptr getPeersToDistributeTo();

		};

		//-----------------------------------------------------------------------
		/**
		  * Models an implementation of the c_SEPSI interface
		  */
		class c_SEPSIImpl : public  c_SEPSI {
		public:

			typedef boost::shared_ptr<c_SEPSIImpl> shared_ptr;

			/**
			  * Constructor
			  */
			c_SEPSIImpl();

			/**
			  * Virtual Destructor
			  */
			virtual ~c_SEPSIImpl();

			// begin c_SEPSI

			/**
			  * Returns access to the Value Instance in the SEPSI with provided path.
			  */
			virtual c_MIVValueInstance::shared_ptr getInstance(const c_InstancePath::shared_ptr& pInstancePath);

			// End c_SEPSI

			// Begin c_SEPSIImpl

			/**
			  * Returns access to the Value Instance impl. in the SEPSI with provided path.
			  */
			virtual c_MIVValueInstanceImpl::shared_ptr getInstanceImpl(const c_InstancePath::shared_ptr& pInstancePath);

			/**
			  * Processes provided c_DeltaSEPSI instance
			  */
			void actOnDelta(miv::c_DeltaSEPSI::shared_ptr pDelta);

			// End c_SEPSIImpl

		private:

			/**
			  * Models a value instance
			  */
			typedef std::pair<c_ModelPath::shared_ptr,c_DarwinetString> c_Instance;

			/**
			  * Private storage of current value instances
			  */
			std::vector<c_Instance> m_Instances;

		};
	} // namespace miv

	class c_DomainViewImpl : public c_DomainView {
	public:

		typedef boost::shared_ptr<c_DomainViewImpl> shared_ptr;

		c_DomainViewImpl();

		// Begin c_DomainView

		/**
		  * Reurns the current SEPSI
		  */
		virtual c_SEPSI::shared_ptr getSEPSI();

		// End c_DomainView

		// Begin c_DomainViewImpl

		/**
		  * Returns access to our c_SEPSIImpl instance
		  */
		miv::c_SEPSIImpl::shared_ptr getSEPSIImpl();

		// End c_DomainViewImpl

	private:

		/**
		  * private storage of our SEPSI instance
		  */
		miv::c_SEPSIImpl::shared_ptr m_pSEPSIImpl;

	};
	//-----------------------------------------------------------------------
	/**
	  * Models a Darwinet Domain
	  */
	class c_DarwinetDomainImpl : public c_DarwinetDomain {
	public:

		typedef boost::shared_ptr<c_DarwinetDomainImpl> shared_ptr;

		/**
		  * Constructor
		  */
		c_DarwinetDomainImpl(c_DomainPath::shared_ptr pDomainPath);

		// Begin c_DarwinetDomain

		/**
		  * Returns required view
		  */
		virtual c_DomainView::shared_ptr getView(const c_ViewPath::shared_ptr& pViewPath);

		// End c_DarwinetDomain

		// Begin c_DarwinetDomainImpl

		/**
		  * Returns c_DomainViewImpl instance
		  */
		c_DomainViewImpl::shared_ptr getViewImpl();

		/**
		  * Returns access to our c_DeltaMIVDistributorImpl
		  */
		miv::c_DeltaMIVDistributorImpl::shared_ptr getDistrubutorImpl();

		/**
		  * Processes provided c_DeltaSEPSI instance
		  */
		void actOnDelta(miv::c_DeltaSEPSI::shared_ptr pDelta);

		// End c_DarwinetDomainImpl


	private:

		/**
		  * private storage of our domain path
		  */
		c_DomainPath::shared_ptr m_pDomainPath;

		/**
		  * Private storage of our c_DomainViewImpl singleton
		  */
		c_DomainViewImpl::shared_ptr m_pViewImplSingleton;

		/**
		  * Private storage of access to our c_DeltaMIVDistributorImpl
		  */
		miv::c_DeltaMIVDistributorImpl::shared_ptr m_pDistributor;

	};

	/**
	  * Implements the c_ClientProxyInterface
	  */
	class c_ClientProxyInterfaceImpl : public c_ClientProxyInterface {
	public:
		/**
		  * Constructor
		  */
		c_ClientProxyInterfaceImpl();

		// Begin c_ClientProxyInterface

		/**
		  * Returns the Engine SEPSI instance registered for provided Proxy Parent and Proxy.
		  * Will create the instance if it does not yet exist.
		  * Will return a NULL instance if Parent Proxy does not have a registered Engine instance.
		  */
		virtual c_SEPSI::shared_ptr getSEPSI(void* pParentProxy,void* pProxy);

		// End c_ClientProxyInterface

	private:

		/**
		  * Maps SEPSI Proxy Instances to SEPSI Instances
		  */
		std::map<void*,c_SEPSI::shared_ptr> m_SEPSIProxyMap;
	};
	//-----------------------------------------------------------------------
	/**
	  * Models a darwinet network Node (The Client Engine)
	  */
	class c_DarwinetEngineImpl : public c_DarwinetEngine {
	public:

		typedef boost::shared_ptr<c_DarwinetEngineImpl> shared_ptr;

		/**
		  * Constructor
		  */
		c_DarwinetEngineImpl();

		// Begin c_DarwinetEngine

		/**
		  * Returns the domain with provided path
		  */
		virtual c_DarwinetDomain::shared_ptr getDomain(const c_DomainPath::shared_ptr& pDomainPath);

		/**
		  * Returns our Client Proxy interface used by proxies
		  * to "find eachother".
		  */
		virtual c_ClientProxyInterface::shared_ptr getClientProxyInterface();

		// End c_DarwinetEngine

		// Begin c_DarwinetEngineImpl

		/**
		  * Returns access to the c_DarwinetDomainImpl of provided path
		  */
		virtual c_DarwinetDomainImpl::shared_ptr getDomainImpl();

		// End c_DarwinetEngineImpl

		/**
		  * Process incoming messages to this engine
		  */
		void processIncomingMessages();

	private:

		/**
		  * Private storage of our Message Source
		  */
		c_PeerSource::shared_ptr m_pPeerSource;

		/**
		  * Returns the PeerSource we are to use to receive messages
		  *, creating it if we don't have one yet.
		  */
		c_PeerSource::shared_ptr getOurPeerSource();

		/**
		  * Private storage of our domain singleton
		  */
		c_DarwinetDomainImpl::shared_ptr m_pDomainSingleton;

		c_ClientProxyInterface::shared_ptr m_pClientProxyInterface;

	};

	/**
	  * Returns the default c_DarwinetEngineImpl instance
	  */
	c_DarwinetEngineImpl::shared_ptr engineImpl();

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Creates a new instance implementing this interface
	  */
	c_PeerPackage::shared_ptr c_PeerPackage::create() {
		c_PeerPackage::shared_ptr result(new c_PeerPackageImpl());
		return result;
	}

	/**
	  * Constructor
	  */
	c_PeerPackageImpl::c_PeerPackageImpl()
		: c_PeerPackage()
	{

	}

	// Begin c_PeerPackage

	/**
	  * Adds provided c_DeltaSEPSI instace to "us"
	  */
	void c_PeerPackageImpl::add(const miv::c_DeltaSEPSI::shared_ptr& pDeltaSEPSI) {
		// We are a friend of miv::c_DeltaSEPSI so we have access to
		// the actual contents :)
		LOG_NOT_IMPLEMENTED;
	}

	// End c_PeerPackage

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * MIV namespace implementation
	  */
	namespace miv {

		/**
		  * Constructor
		  */
		c_MIVValueInstanceImpl::c_MIVValueInstanceImpl(const c_DeltaIndex::shared_ptr& pCurrentDeltaIndex)
			: m_pCurrentDeltaIndex(pCurrentDeltaIndex)
			  ,m_value(0)
		{
			LOG_METHOD_SCOPE;
		}

		/**
		  * Virtual destructor
		  */
		c_MIVValueInstanceImpl::~c_MIVValueInstanceImpl() {
			LOG_METHOD_SCOPE;
		}

		// Begin c_MIVValueInstance

		/**
		  * Sets this Instance Value to the provided Value represented as a string
		  */
		void c_MIVValueInstanceImpl::setValue(const c_DarwinetString& sValue) {
			LOG_NOT_IMPLEMENTED;
			c_DeltaSEPSI::shared_ptr pDelta = this->diff(sValue);
			if (pDelta) {
				// Distribute the change
				// Note: The actual change to our state takes place when we process the delta distributed to ourselves.
				//       In this way we change state through the same channel regardless of wether the change
				//       occurred internally or at a remote peer.
				engineImpl()->getDomainImpl()->getDistrubutorImpl()->distribute(pDelta);
			}
		}

		/**
		  * Returns the index of the last Delta applied to get our current Value.
		  */
		c_DeltaIndex::shared_ptr c_MIVValueInstanceImpl::getCurrentDeltaIndex() {
			return this->m_pCurrentDeltaIndex;
		}

		// End c_MIVValueInstance

		// Begin c_MIVValueInstanceImpl

		/**
		  * Applies provided Delta to this instance
		  */
		void c_MIVValueInstanceImpl::applyDelta(miv::c_DeltaSEPSI::shared_ptr pDelta) {
			if (*this->m_pCurrentDeltaIndex == *pDelta->getTargetIndex()) {
				// Correct target Index. Apply the Delta
				// For now, hard code that we are an integer and the provided Delta must by an integer Delta
				c_IntDeltaImpl::shared_ptr pIntDelta = boost::dynamic_pointer_cast<c_IntDeltaImpl>(pDelta);
				if (pIntDelta) {
					// Yes, we received an Integer Delta
					this->m_value += pIntDelta->getValue();
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Provided Delta not an c_IntDeltaImpl");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}
			else {
				c_LogString sMessage(__FUNCTION__" failed. Instance index \"");
				sMessage += this->m_pCurrentDeltaIndex->toString<c_LogString>();
				sMessage += _UTF8sz("\" <> Delta Target Index \"");
				sMessage += pDelta->getTargetIndex()->toString<c_LogString>();
				sMessage += _UTF8sz("\"");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

		// End c_MIVValueInstanceImpl


		/**
		  * Returns the difference between provided value and the value
		  * we actually have
		  */
		c_DeltaSEPSI::shared_ptr c_MIVValueInstanceImpl::diff(const c_DarwinetString& sValue) {
			c_DeltaSEPSI::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			// TODO: Implement the real diff mechanism.
			//       For now, simply asume we are an integer and calculate the int difference
			try {
				int other_int_value = c_DataRepresentationFramework::intValueOfDecimalString(sValue);
				int int_diff = this->m_value - other_int_value;
				if (int_diff != 0) {
					// Yes, We have changed!
					c_DeltaSEPSI::shared_ptr pDelta(new c_IntDeltaImpl(this->getCurrentDeltaIndex(),int_diff));
					result = pDelta;
				}
			}
			catch (...) {
				c_LogString sMessage(__FUNCTION__" failed. ");
				sMessage += _UTF8sz(" Integer Diff calculation throwed an excpetion!");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}

			return result;
		}

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		/**
		  * Constructor
		  */
		c_PeerProxySelfImpl::c_PeerProxySelfImpl()
		{
			LOG_METHOD_SCOPE;
		}

		// Begin c_PeerProxy

		/**
		  * Send provided delta to the Peer we represent
		  */
		void c_PeerProxySelfImpl::send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
			LOG_NOT_IMPLEMENTED;
		}

		// End c_PeerProxy

		/**
		  * Creates a new implementation of this interface
		  */
		c_PeerProxySelf::shared_ptr c_PeerProxySelf::create() {
			c_PeerProxySelf::shared_ptr result(new c_PeerProxySelfImpl());
			return result;
        }

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------

		/**
		  * Constructor
		  */
		c_DeltaMIVDistributorImpl::c_DeltaMIVDistributorImpl()
		{

		}

		// Begin c_DeltaMIVDistributor

		/**
		  * Distributes provided delta to peers and to ourself.
		  */
		void c_DeltaMIVDistributorImpl::distribute(const c_DeltaSEPSI::shared_ptr& pDelta) {
			LOG_NOT_IMPLEMENTED;
			this->distribute(pDelta,this->getPeersToDistributeTo());
		}

		// End c_DeltaMIVDistributor

		/**
		  * Distributes provided delta to provided Peers
		  */
		void c_DeltaMIVDistributorImpl::distribute(const c_DeltaSEPSI::shared_ptr& pDelta,const c_PeerProxies_shared_ptr& pPeers) {
			if (pDelta) {
				if (pPeers) {
					for (c_PeerProxies::const_iterator iter = pPeers->begin(); iter != pPeers->end(); ++iter) {
						(*iter)->send(pDelta);
					}
				}
			}
		}

		/**
		  * Returns an instance of Peers selected to be targets of our delta distributions
		  */
		c_PeerProxies_shared_ptr c_DeltaMIVDistributorImpl::getPeersToDistributeTo() {
			c_PeerProxies_shared_ptr result(new c_PeerProxies());
			LOG_NOT_IMPLEMENTED;
			c_PeerProxy::shared_ptr pTestPeer2(c_PeerProxyMail::create(_UTF8sz("peer2@darwinet.se")));
			result->push_back(pTestPeer2);
			c_PeerProxy::shared_ptr pThisPeer(c_PeerProxySelf::create());
			result->push_back(pThisPeer);
			return result;
		}

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		/**
		  * Constructor
		  */
		c_SEPSIImpl::c_SEPSIImpl()
		{
			LOG_METHOD_SCOPE;
		}

		//-----------------------------------------------------------------------
		/**
		  * Virtual Destructor
		  */
		c_SEPSIImpl::~c_SEPSIImpl() {
			LOG_METHOD_SCOPE;
		}

		// begin c_SEPSI
		//-----------------------------------------------------------------------

		/**
		  * Returns access to the Value Instance in the SEPSI with provided path.
		  */
		c_MIVValueInstance::shared_ptr c_SEPSIImpl::getInstance(const c_InstancePath::shared_ptr& pInstancePath) {
			return this->getInstanceImpl(pInstancePath);
		}

		// End c_SEPSI

		// Begin c_SEPSIImpl

		/**
		  * Returns access to the Value Instance impl. in the SEPSI with provided path.
		  */
		c_MIVValueInstanceImpl::shared_ptr c_SEPSIImpl::getInstanceImpl(const c_InstancePath::shared_ptr& pInstancePath) {
			// TODO: Implement retruning the actual instance in our storage.
			//       For now, simply return a local static instance
			static c_MIVValueInstanceImpl::shared_ptr static_value_instance_impl;
			if (!static_value_instance_impl) {
				c_DeltaIndex::shared_ptr pDummyIndex(new c_DeltaIndex(c_DeltaIndex::Node(_UTF8sz("dummy_index")))); // Dummy
				static_value_instance_impl.reset(new c_MIVValueInstanceImpl(pDummyIndex));
			}
			return static_value_instance_impl;
        }

		/**
		  * Processes provided c_DeltaSEPSI instance
		  */
		void c_SEPSIImpl::actOnDelta(miv::c_DeltaSEPSI::shared_ptr pDelta) {
			LOG_NOT_IMPLEMENTED;
			c_MIVValueInstanceImpl::shared_ptr pInstance = this->getInstanceImpl(pDelta->getTargetInstancePath());
			if (pInstance) {
				// The instance exists
				pInstance->applyDelta(pDelta);
			}
			else {
				// Trying to apply a change to an instance that does not yet exist!
				c_LogString sMessage(__FUNCTION__" failed. Can't change instance that does not exist. Path=");
				sMessage += pDelta->getTargetInstancePath()->toString<c_LogString>();
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

		// End c_SEPSIImpl


	} // namespace miv

	c_DomainViewImpl::c_DomainViewImpl()
	{

	}

	// Begin c_DomainView

	/**
	  * Reurns the current SEPSI
	  */
	c_SEPSI::shared_ptr c_DomainViewImpl::getSEPSI() {
		return this->getSEPSIImpl();
	}

	// End c_DomainView

	// Begin c_DomainViewImpl

	/**
	  * Returns access to our c_SEPSIImpl instance
	  */
	miv::c_SEPSIImpl::shared_ptr c_DomainViewImpl::getSEPSIImpl() {
		if (!this->m_pSEPSIImpl) {
			this->m_pSEPSIImpl.reset(new miv::c_SEPSIImpl());
		}
		return this->m_pSEPSIImpl;
    }

	// End c_DomainViewImpl


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Constructor
	  */
	c_DarwinetDomainImpl::c_DarwinetDomainImpl(c_DomainPath::shared_ptr pDomainPath)
		: m_pDomainPath(pDomainPath)
	{

	}

	// Begin c_DarwinetDomain

	/**
	  * Returns required view
	  */
	c_DomainView::shared_ptr c_DarwinetDomainImpl::getView(const c_ViewPath::shared_ptr& pViewPath) {
		return this->getViewImpl();
	}

	// End c_DarwinetDomain

	// Begin c_DarwinetDomainImpl

	/**
	  * Returns c_DomainViewImpl instance
	  */
	c_DomainViewImpl::shared_ptr c_DarwinetDomainImpl::getViewImpl() {
		if (!this->m_pViewImplSingleton) {
			this->m_pViewImplSingleton.reset(new c_DomainViewImpl());
		}
		return this->m_pViewImplSingleton;
    }

	/**
	  * Returns access to our c_DeltaMIVDistributorImpl
	  */
	miv::c_DeltaMIVDistributorImpl::shared_ptr c_DarwinetDomainImpl::getDistrubutorImpl() {
		if (!this->m_pDistributor) {
			this->m_pDistributor.reset(new miv::c_DeltaMIVDistributorImpl());
		}
		return this->m_pDistributor;
	}

	/**
	  * Processes provided c_DeltaSEPSI instance
	  */
	void c_DarwinetDomainImpl::actOnDelta(miv::c_DeltaSEPSI::shared_ptr pDelta) {
		if (pDelta) {
			this->getViewImpl()->getSEPSIImpl()->actOnDelta(pDelta);
		}
	}

	// End c_DarwinetDomainImpl

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Constructor
	  */
	c_ClientProxyInterfaceImpl::c_ClientProxyInterfaceImpl()
	{
		LOG_METHOD_SCOPE;
	}

	// Begin c_ClientProxyInterface

	/**
	  * Returns the Engine SEPSI instance registered for provided Proxy Parent and Proxy.
	  * Will create the instance if it does not yet exist.
	  * Will return a NULL instance if Parent Proxy does not have a registered Engine instance.
	  */
	c_SEPSI::shared_ptr c_ClientProxyInterfaceImpl::getSEPSI(void* pParentProxy,void* pProxy) {
		LOG_METHOD_SCOPE;
		c_SEPSI::shared_ptr result = this->m_SEPSIProxyMap[pProxy];
		if (!result) {
			// Mapping did not exist to map created a new mapping to empty c_SEPSI::shared_ptr.
			// Now assign an actual instance to the pointer.
			// TODO: Find and call parent View and let it return the correct SEPSI instace.
			//       For now, just use a dummy/default one.
			c_LogString sMessage("c_ClientProxyInterfaceImpl::getSEPSI, Mapped new SEPSI Proxy");
			LOG_DEVELOPMENT_TRACE(sMessage);
			result = engine()->getDomain()->getView()->getSEPSI();
			this->m_SEPSIProxyMap[pProxy] = result;
		}
		return result;
	}

	// End c_ClientProxyInterface

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Constructor
	  */
	c_DarwinetEngineImpl::c_DarwinetEngineImpl()
	{

	}

	// Begin c_DarwinetEngine

	//-----------------------------------------------------------------------
	/**
	  * Returns the domain with provided path
	  */
	c_DarwinetDomain::shared_ptr c_DarwinetEngineImpl::getDomain(const c_DomainPath::shared_ptr& pDomainPath) {
		return this->getDomainImpl();
	}

	/**
	  * Returns our Client Proxy interface used by proxies
	  * to "find eachother".
	  */
	c_ClientProxyInterface::shared_ptr c_DarwinetEngineImpl::getClientProxyInterface() {
		if (!this->m_pClientProxyInterface) {
			this->m_pClientProxyInterface.reset(new c_ClientProxyInterfaceImpl());
		}
		return this->m_pClientProxyInterface;
	}

	// End c_DarwinetEngine

	// Begin c_DarwinetEngineImpl

	/**
	  * Returns access to the c_DarwinetDomainImpl of provided path
	  */
	c_DarwinetDomainImpl::shared_ptr c_DarwinetEngineImpl::getDomainImpl() {
		LOG_NOT_IMPLEMENTED;
		// TODO: Implement Domain handling.
		// For now, just return a singleton (disregard provided domain path if singleton already exists)
		if (!this->m_pDomainSingleton) {
			c_DomainPath::shared_ptr pDomainPath; // NULL path (dummy)
			this->m_pDomainSingleton.reset(new c_DarwinetDomainImpl(pDomainPath));
		}
		return this->m_pDomainSingleton;
	}

	// End c_DarwinetEngineImpl

	//-----------------------------------------------------------------------
	/**
	  * Process incoming messages to this engine
	  */
	void c_DarwinetEngineImpl::processIncomingMessages() {
		// Read any deltas from our Source
		miv::c_DeltaSEPSI::shared_ptr pDelta = this->getOurPeerSource()->receive();
		if (pDelta) {
			// Process the Delta we have received
			this->getDomainImpl()->actOnDelta(pDelta);
		}
	}

	//-----------------------------------------------------------------------
	/**
	  * Returns the PeerSource we are to use to receive messages
	  *, creating it if we don't have one yet.
	  */
	c_PeerSource::shared_ptr c_DarwinetEngineImpl::getOurPeerSource() {
		if (!this->m_pPeerSource) {
			this->m_pPeerSource = c_PeerSourceMail::create();
		}
		return this->m_pPeerSource;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Returns the default c_DarwinetEngineImpl instance
	  */
	c_DarwinetEngineImpl::shared_ptr engineImpl() {
		static c_DarwinetEngineImpl::shared_ptr pInstance;
		if (!pInstance) {
			pInstance.reset(new c_DarwinetEngineImpl());
		}
		return pInstance;
	}

	/**
	  * Returns the local Darwinet Engine
	  */
	c_DarwinetEngine::shared_ptr engine() {
		return engineImpl();
	}

	/**
	  * Creats a shared domain path instance from provided string
	  */
	c_DomainPath::shared_ptr shared_domain_path(c_DarwinetString sDomainPath) {
		c_DomainPath::shared_ptr result(new c_DomainPath(sDomainPath));
		return result;
	}

	/**
	  * Creats a shared model path instance from provided string
	  */
	c_ModelPath::shared_ptr shared_model_path(c_DarwinetString sModelPath) {
		c_ModelPath::shared_ptr result(new c_ModelPath(sModelPath));
		return result;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Call this method from a worker thread to process incoming Darwinet Messages
	  * to this engine.
	  */
	void processIncomingMessages() {
		engineImpl()->processIncomingMessages();
	}
}
