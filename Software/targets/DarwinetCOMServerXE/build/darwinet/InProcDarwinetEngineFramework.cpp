//---------------------------------------------------------------------------

#pragma hdrstop

#include "InProcDarwinetEngineFramework.h"
#include "PeerSinkMail.h"
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
	  * Implementation of the miv namespace
	  */
	namespace miv {


		/**
		  * Base class of all Delta implementations
		  */
		class c_DeltaImpl : public c_DeltaSEPSI {
		public:

			/**
			  * Constructor
			  */
			c_DeltaImpl(const c_DeltaIndex::shared_ptr& pTargetIndex);

			// Begin c_DeltaSEPSI

			/**
			  * Returns the index of the target Delta to which we apply
			  */
			virtual c_DeltaIndex::shared_ptr getTargetIndex();

			// End c_DeltaSEPSI

		private:

			/**
			  * Private storage of the index of the target delta
			  * to which this delta applies.
			  */
			c_DeltaIndex::shared_ptr m_pTargetIndex;

		};

		/**
		  * Implements an Integer Delta
		  */
		class c_IntDeltaImpl : public c_DeltaImpl {
		public:

			/**
			  * Creates and integer delta
			  */
			c_IntDeltaImpl(const c_DeltaIndex::shared_ptr& pTargetIndex,int int_diff);

		private:

			/**
			  * Private storage of the ingerer diff we represent.
			  */
			int m_int_diff;
		};

		//-----------------------------------------------------------------------

		/**
		  * Models an implementation of the c_MIVValueInstance interface
		  */
		class c_MIVValueInstanceImpl : public c_MIVValueInstance {
		public:

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
		  * Models a Peer sink that connects to "us"
		  */
		class c_PeerSinkSelf : public c_PeerSink {
		public:

			typedef boost::shared_ptr<c_PeerSinkSelf> shared_ptr;

			/**
			  * Creates a new implementation of this interface
			  */
			static c_PeerSinkSelf::shared_ptr create();

		};

		class c_PeerSinkSelfImpl : public c_PeerSinkSelf {
		public:

			/**
			  * Constructor
			  */
			c_PeerSinkSelfImpl();

			// Begin c_PeerSink

			/**
			  * Send provided delta to the Sink we represent
			  */
			virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta);

			// End c_PeerSink

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

			// this->distribute(pDelta,this->getPeerSinksToDistributeTo());

			/**
			  * Distributes provided delta to provided Peers
			  */
			void distribute(const c_DeltaSEPSI::shared_ptr& pDelta,const c_PeerSinks_shared_ptr& pPeers);

			/**
			  * Returns an instance of Peers selected to be targets of our delta distributions
			  */
			c_PeerSinks_shared_ptr getPeerSinksToDistributeTo();

		};

		//-----------------------------------------------------------------------
		/**
		  * Models an implementation of the c_SEPSI interface
		  */
		class c_SEPSIImpl : public  c_SEPSI {
		public:

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
		c_DomainViewImpl();

		// Begin c_DomainView

		/**
		  * Reurns the current SEPSI
		  */
		virtual c_SEPSI::shared_ptr getSEPSI();

		// End c_DomainView

	private:

		/**
		  * private storage of our SEPSI instance
		  */
		c_SEPSI::shared_ptr m_pSEPSI;

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
		  * Returns access to our c_DeltaMIVDistributorImpl
		  */
		miv::c_DeltaMIVDistributorImpl::shared_ptr getDistrubutorImpl();

		// End c_DarwinetDomainImpl


	private:

		/**
		  * private storage of our domain path
		  */
		c_DomainPath::shared_ptr m_pDomainPath;

		/**
		  * Private storage of our view singleton
		  */
		c_DomainView::shared_ptr m_pViewSingleton;

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


	private:

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
	  * MIV namespace implementation
	  */
	namespace miv {

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		/**
		  * Constructor
		  */
		c_DeltaImpl::c_DeltaImpl(const c_DeltaIndex::shared_ptr& pTargetIndex)
			: m_pTargetIndex(pTargetIndex)
		{
			LOG_METHOD_SCOPE;
		}

		// Begin c_DeltaSEPSI

		/**
		  * Returns the index of the target Delta to which we apply
		  */
		c_DeltaIndex::shared_ptr c_DeltaImpl::getTargetIndex() {
			return this->m_pTargetIndex;
		}

		// End c_DeltaSEPSI


		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		/**
		  * Creates and integer delta
		  */
		c_IntDeltaImpl::c_IntDeltaImpl(const c_DeltaIndex::shared_ptr& pTargetIndex,int int_diff)
			:  c_DeltaImpl(pTargetIndex)
			  ,m_int_diff(int_diff)
		{
			LOG_METHOD_SCOPE;
		}

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
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
		c_PeerSinkSelfImpl::c_PeerSinkSelfImpl()
		{
			LOG_METHOD_SCOPE;
		}

		// Begin c_PeerSink

		/**
		  * Send provided delta to the Sink we represent
		  */
		void c_PeerSinkSelfImpl::send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) {
			LOG_NOT_IMPLEMENTED;
		}

		// End c_PeerSink

		/**
		  * Creates a new implementation of this interface
		  */
		c_PeerSinkSelf::shared_ptr c_PeerSinkSelf::create() {
			c_PeerSinkSelf::shared_ptr result(new c_PeerSinkSelfImpl());
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
			this->distribute(pDelta,this->getPeerSinksToDistributeTo());
		}

		// End c_DeltaMIVDistributor

		/**
		  * Distributes provided delta to provided Peers
		  */
		void c_DeltaMIVDistributorImpl::distribute(const c_DeltaSEPSI::shared_ptr& pDelta,const c_PeerSinks_shared_ptr& pPeers) {
			if (pDelta) {
				if (pPeers) {
					for (c_PeerSinks::const_iterator iter = pPeers->begin(); iter != pPeers->end(); ++iter) {
						(*iter)->send(pDelta);
					}
				}
			}
		}

		/**
		  * Returns an instance of Peers selected to be targets of our delta distributions
		  */
		c_PeerSinks_shared_ptr c_DeltaMIVDistributorImpl::getPeerSinksToDistributeTo() {
			c_PeerSinks_shared_ptr result(new c_PeerSinks());
			LOG_NOT_IMPLEMENTED;
			c_PeerSink::shared_ptr pTestPeer2(c_PeerSinkMail::create(_UTF8sz("peer2@darwinet.se")));
			result->push_back(pTestPeer2);
			c_PeerSink::shared_ptr pThisPeer(c_PeerSinkSelf::create());
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
			// TODO: Implement retruning the actual instance in our storage.
			//       For now, simply return a lpocal static instance
			static c_MIVValueInstance::shared_ptr static_value_instance;
			if (!static_value_instance) {
				c_DeltaIndex::shared_ptr pDummyIndex(new c_DeltaIndex()); // Dummy
				static_value_instance.reset(new c_MIVValueInstanceImpl(pDummyIndex));
			}
			return static_value_instance;
		}

		// End c_SEPSI

	} // namespace miv

	c_DomainViewImpl::c_DomainViewImpl()
	{

	}

	// Begin c_DomainView

	/**
	  * Reurns the current SEPSI
	  */
	c_SEPSI::shared_ptr c_DomainViewImpl::getSEPSI() {
		if (!this->m_pSEPSI) {
			this->m_pSEPSI.reset(new miv::c_SEPSIImpl());
		}
		return this->m_pSEPSI;
	}

	// End c_DomainView


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
		if (!this->m_pViewSingleton) {
			this->m_pViewSingleton.reset(new c_DomainViewImpl());
		}
		return this->m_pViewSingleton;
	}

	// End c_DarwinetDomain

	// Begin c_DarwinetDomainImpl

	/**
	  * Returns access to our c_DeltaMIVDistributorImpl
	  */
	miv::c_DeltaMIVDistributorImpl::shared_ptr c_DarwinetDomainImpl::getDistrubutorImpl() {
		if (!this->m_pDistributor) {
			this->m_pDistributor.reset(new miv::c_DeltaMIVDistributorImpl());
		}
		return this->m_pDistributor;
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


}
