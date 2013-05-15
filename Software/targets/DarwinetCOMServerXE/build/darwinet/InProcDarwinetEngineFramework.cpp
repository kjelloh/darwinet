//---------------------------------------------------------------------------

#pragma hdrstop

#include "InProcDarwinetEngineFramework.h"
#include "SEPSIImplementationUnit.h"
#include <map>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace darwinet {

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

		/**
		  * Constructor
		  */
		c_DarwinetDomainImpl(c_DomainPath::shared_ptr pDomainPath);

		// Begin c_DarwinetDomain

		/**
		  * Returns required view
		  */
		virtual c_DomainView::shared_ptr getView();

		// End c_DarwinetDomain

	private:

		/**
		  * private storage of our domain path
		  */
		c_DomainPath::shared_ptr m_pDomainPath;

		/**
		  * Private storage of our view singleton
		  */
		c_DomainView::shared_ptr m_pViewSingleton;


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

		/**
		  * Constructor
		  */
		c_DarwinetEngineImpl();

		// Begin c_DarwinetEngine

		/**
		  * Returns the domain with provided path
		  */
		virtual c_DarwinetDomain::shared_ptr get_domain(c_DomainPath::shared_ptr pDomainPath);

		/**
		  * Returns our Client Proxy interface used by proxies
		  * to "find eachother".
		  */
		virtual c_ClientProxyInterface::shared_ptr getClientProxyInterface();

		// End c_DarwinetEngine

	private:

		/**
		  * Private storage of our domain singleton
		  */
		c_DarwinetDomain::shared_ptr m_pDomainSingleton;

		c_ClientProxyInterface::shared_ptr m_pClientProxyInterface;

	};
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

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
	c_DomainView::shared_ptr c_DarwinetDomainImpl::getView() {
		if (!this->m_pViewSingleton) {
			this->m_pViewSingleton.reset(new c_DomainViewImpl());
		}
		return this->m_pViewSingleton;
	}

	// End c_DarwinetDomain

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
			result = engine()->get_domain()->getView()->getSEPSI();
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
	c_DarwinetDomain::shared_ptr c_DarwinetEngineImpl::get_domain(c_DomainPath::shared_ptr pDomainPath) {
		LOG_NOT_IMPLEMENTED;
		// TODO: Implement Domian handling.
		// For now, just return a singleton (disregard provided domain path if singleton already exists)
		if (!this->m_pDomainSingleton) {
			this->m_pDomainSingleton.reset(new c_DarwinetDomainImpl(pDomainPath));
		}
		return this->m_pDomainSingleton;
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

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Returns the local Darwinet Engine
	  */
	c_DarwinetEngine::shared_ptr engine() {
		// Implement as a singleton
		static c_DarwinetEngine::shared_ptr result(new c_DarwinetEngineImpl());
		return result;
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
