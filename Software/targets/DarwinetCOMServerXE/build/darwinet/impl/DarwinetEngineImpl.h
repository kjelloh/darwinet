//---------------------------------------------------------------------------

#ifndef DarwinetEngineImplH
#define DarwinetEngineImplH
//---------------------------------------------------------------------------
#include "InProcDarwinetEngineFramework.h"
#include <map>
//---------------------------------------------------------------------------
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

			/**
			  * Adds provided listener to this instance
			  */
			virtual void addListener(c_MIVValueInstanceListener* pListener);

			/**
			  * Removes provided listener from this instance
			  */
			virtual void removeListener(c_MIVValueInstanceListener* pListener);

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

			/**
			  * Report "Value Changed" to all our listeners
			  */
			void reportValueChanged();

			/**
			  * Private storage of our only listener
			  */
			c_MIVValueInstanceListener* m_pListener;

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

} // namespace darwinet

#endif
