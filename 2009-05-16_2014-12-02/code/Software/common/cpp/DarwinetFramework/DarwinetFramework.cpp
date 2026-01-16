//---------------------------------------------------------------------------

#pragma hdrstop

#include "DarwinetFramework.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Implementation of darwinet object interfaces
  */
namespace darwinet {

	namespace detail {

		/**
		  * Models the type of change to a MIV.
		  * Note: All types must be reversable.
		  */
		enum e_MIVChange {
			 eMIVChange_Undefined
			,eMIVChange_CreateValueInstance
			,eMIVChange_DeleteValueInstance
			,eMIVChange_Unknown
		};

		/**
		  * Models a change to a MIV
		  */
		class c_MIVChange {
		public:

			typedef boost::shared_ptr<c_MIVChange> shared_ptr;

			c_MIVChange(e_MIVChange);
		};

	}

	/**
	  * Models a set of Deltas that defines a MIV.
	  */
	class c_DeltaMIV {
	public:

		// Begin c_DeltaMIV

		/**
		  * Creates a new value instance of model type with provided model path
		  * setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue) = 0;

		// End c_DeltaMIV
	};

	/**
	  * Implements c_DeltaMIV
	  */
	class c_DeltaMIVImpl : public c_DeltaMIV {
	public:

		c_DeltaMIVImpl();


		// Begin c_DeltaMIV

		/**
		  * Creates a new value instance of model type with provided model path.
		  * Setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue);

		// End c_DeltaMIV

	private:

		/**
		  * Private storage of our current record of MIV changes
		  */
		std::vector<detail::c_MIVChange::shared_ptr> m_Deltas;

	};

	//-----------------------------------------------------------------------
	class c_MIVImpl : public  c_MIV {
	public:

		/**
		  * Constructor
		  */
		c_MIVImpl();

		/**
		  * Virtual Destructor
		  */
		virtual ~c_MIVImpl();

		// begin c_MIV

		/**
		  * Creates a new value instance of model type with provided model path
		  * setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue);

		// End c_MIV

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

	class c_DomainViewImpl : public c_DomainView {
	public:
		c_DomainViewImpl();

		// Begin c_DomainView

		/**
		  * Reurns the current MIV
		  */
		virtual c_MIV::shared_ptr getMIV();

		// End c_DomainView

	private:

		/**
		  * private storage of our MIV instance
		  */
		c_MIV::shared_ptr m_pMIV;

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

	//-----------------------------------------------------------------------
	/**
	  * Models a darwinet network Node (The Client Engine)
	  */
	class c_DarwinetNodeImpl : public c_DarwinetNode {
	public:

		/**
		  * Constructor
		  */
		c_DarwinetNodeImpl();

		// Begin c_DarwinetNode

		/**
		  * Returns the domain with provided path
		  */
		virtual c_DarwinetDomain::shared_ptr get_domain(c_DomainPath::shared_ptr pDomainPath);

		// End c_DarwinetNode

	private:

		/**
		  * Private storage of our domain singleton
		  */
		c_DarwinetDomain::shared_ptr m_pDomainSingleton;

	};
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Constructor
	  */
	c_MIVImpl::c_MIVImpl()
	{
	}

	//-----------------------------------------------------------------------
	/**
	  * Virtual Destructor
	  */
	c_MIVImpl::~c_MIVImpl() {
	}

	// begin c_MIV
	//-----------------------------------------------------------------------
	/**
	  * Creates a new value instance of model type with provided model path
	  * setting it to provided initial value.
	  */
	void c_MIVImpl::createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue) {
		LOG_NOT_IMPLEMENTED;
		// TODO: Implement listener design pattern and instanciate a new instance
		//       when we receive "onNewInstance" asynchronous event from the deltaMIV.
	}
	// End c_MIV
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	c_DomainViewImpl::c_DomainViewImpl()
	{

	}

	// Begin c_DomainView

	/**
	  * Reurns the current MIV
	  */
	c_MIV::shared_ptr c_DomainViewImpl::getMIV() {
		if (!this->m_pMIV) {
			this->m_pMIV.reset(new c_MIVImpl());
		}
		return this->m_pMIV;
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
	c_DarwinetNodeImpl::c_DarwinetNodeImpl()
	{

	}

	// Begin c_DarwinetNode

	//-----------------------------------------------------------------------
	/**
	  * Returns the domain with provided path
	  */
	c_DarwinetDomain::shared_ptr c_DarwinetNodeImpl::get_domain(c_DomainPath::shared_ptr pDomainPath) {
		LOG_NOT_IMPLEMENTED;
		// TODO: Implement Domian handling.
		// For now, just return a singleton (disregard provided domain path if singleton already exists)
		if (!this->m_pDomainSingleton) {
			this->m_pDomainSingleton.reset(new c_DarwinetDomainImpl(pDomainPath));
		}
		return this->m_pDomainSingleton;
	}

	// End c_DarwinetNode

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Returns the local darwinet node
	  */
	c_DarwinetNode::shared_ptr local_node() {
		// Implement as a singleton
		static c_DarwinetNode::shared_ptr result(new c_DarwinetNodeImpl());
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

} // namespace darwinet
