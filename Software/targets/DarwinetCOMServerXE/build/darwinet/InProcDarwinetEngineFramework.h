//---------------------------------------------------------------------------
#include "DataRepresentationFrameWork.h"
#include <boost/shared_ptr.hpp>
#include "keypath.h"
//---------------------------------------------------------------------------

#ifndef InProcDarwinetEngineFrameworkH
#define InProcDarwinetEngineFrameworkH
//---------------------------------------------------------------------------
/**
  * The darwinet namespace implements the darwinet engine.
  * It models a Darwinet Engine to be used "in process", i.e. in the same execuatbel process
  * as the client. It may be used both in the client process or by a server process.
  */
namespace darwinet {

	typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;

	typedef c_DarwinetString c_CaptionNode;

	typedef oprime::c_KeyPath<c_CaptionNode> c_DomainPath;
	typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;
	typedef oprime::c_KeyPath<oprime::c_IndexedKeyNode<c_CaptionNode> > c_InstancePath;

	/**
	  * Darwinet Engine Core
	  */
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	class c_SEPSI {
	public:
		typedef boost::shared_ptr<c_SEPSI> shared_ptr;

		// begin c_SEPSI

		/**
		  * Creates a new value instance of model type with provided model path
		  * setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue) = 0;

		/**
		  * Sets the value instance with provided path to the provided value
		  */
		virtual void setValue(const c_DarwinetString& instance_path,const c_DarwinetString& sValue) = 0;

		// End c_SEPSI

	};

	/**
	  * Models a Domain view
	  */
	class c_DomainView {
	public:
		typedef boost::shared_ptr<c_DomainView> shared_ptr;


		// Begin c_DomainView

		/**
		  * Reurns the current SEPSI
		  */
		virtual c_SEPSI::shared_ptr getSEPSI() = 0;

		// End c_DomainView

	};

	/**
	  * Models a Darwinet Domain
	  */
	class c_DarwinetDomain {
	public:
		typedef boost::shared_ptr<c_DarwinetDomain> shared_ptr;

		// Begin c_DarwinetDomain

		/**
		  * Returns required view
		  */
		virtual c_DomainView::shared_ptr getView() = 0;

		// End c_DarwinetDomain

	};

	//-----------------------------------------------------------------------

	/**
	  * Models the interface to the Darwinet Client Proxy.
	  * This instance binds proxy instances to Engine instances.
	  * The Client Proxies at the server side uses these
	  * services to find "eachother" when they are created
	  * from the client side. It keeps track of what proxy
	  * is bound to which Engine artefact instance.
	  */
	class c_ClientProxyInterface {
	public:
		/**
		  * Shared pointer to this singleton
		  */
		typedef boost::shared_ptr<c_ClientProxyInterface> shared_ptr;

		// Begin c_ClientProxyInterface

		/**
		  * Returns the Engine SEPSI instance registered for provided Proxy Parent and Proxy.
		  * Will create the instance if it does not yet exist.
		  * Will return a NULL instance if Parent Proxy does not have a registered Engine instance.
		  */
		virtual c_SEPSI::shared_ptr getSEPSI(void* pParentProxy,void* pProxy) = 0;

		// End c_ClientProxyInterface

	private:

	};

	//-----------------------------------------------------------------------
	/**
	  * Models a Darwinet Engine interface
	  */
	class c_DarwinetEngine {
	public:
		typedef boost::shared_ptr<c_DarwinetEngine> shared_ptr;

		// Begin c_DarwinetEngine

		/**
		  * Returns the domain with provided path
		  */
		virtual c_DarwinetDomain::shared_ptr get_domain(c_DomainPath::shared_ptr pDomainPath = c_DomainPath::shared_ptr()) = 0;

		/**
		  * Returns our Client Proxy interface used by proxies
		  * to "find eachother".
		  */
		virtual c_ClientProxyInterface::shared_ptr getClientProxyInterface() = 0;

		// End c_DarwinetEngine

	};

	/**
	  * Returns the local Darwinet Engine
	  */
	c_DarwinetEngine::shared_ptr engine();

	/**
	  * Creats a shared domain path instance from provided string
	  */
	c_DomainPath::shared_ptr shared_domain_path(c_DarwinetString sDomainPath);

	/**
	  * Creats a shared model path instance from provided string
	  */
	c_ModelPath::shared_ptr shared_model_path(c_DarwinetString sModelPath);
}
#endif
