//---------------------------------------------------------------------------
#ifndef DarwinetFrameworkH
#define DarwinetFrameworkH
//---------------------------------------------------------------------------
#include "DataRepresentationFrameWork.h"
#include <boost/shared_ptr.hpp>
#include "oprime/keypath.h"
//---------------------------------------------------------------------------

/**
  * Implementation of darwinet object interfaces
  */
namespace darwinet {

	typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;

	typedef c_DarwinetString c_CaptionNode;

	typedef oprime::c_KeyPath<c_CaptionNode> c_DomainPath;
	typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;
	typedef oprime::c_KeyPath<oprime::c_IndexedKeyNode<c_CaptionNode> > c_InstancePath;

	class c_MIV {
	public:
		typedef boost::shared_ptr<c_MIV> shared_ptr;

		// begin c_MIV

		/**
		  * Creates a new value instance of model type with provided model path
		  * setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue) = 0;

		// End c_MIV

	};

	/**
	  * Models a Domain view
	  */
	class c_DomainView {
	public:
		typedef boost::shared_ptr<c_DomainView> shared_ptr;


		// Begin c_DomainView

		/**
		  * Reurns the current MIV
		  */
		virtual c_MIV::shared_ptr getMIV() = 0;

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

	/**
	  * Models a darwinet network Node (The Client Engine)
	  */
	class c_DarwinetNode {
	public:
		typedef boost::shared_ptr<c_DarwinetNode> shared_ptr;

		// Begin c_DarwinetNode

		/**
		  * Returns the domain with provided path
		  */
		virtual c_DarwinetDomain::shared_ptr get_domain(c_DomainPath::shared_ptr pDomainPath) = 0;

		// End c_DarwinetNode

	};

	/**
	  * Returns the local darwinet node
	  */
	c_DarwinetNode::shared_ptr local_node();

	/**
	  * Creats a shared domain path instance from provided string
	  */
	c_DomainPath::shared_ptr shared_domain_path(c_DarwinetString sDomainPath);

	/**
	  * Creats a shared model path instance from provided string
	  */
	c_ModelPath::shared_ptr shared_model_path(c_DarwinetString sModelPath);

} // namespace darwinet

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

