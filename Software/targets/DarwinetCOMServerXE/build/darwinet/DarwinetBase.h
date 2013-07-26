//---------------------------------------------------------------------------

#ifndef DarwinetBaseH
#define DarwinetBaseH
//---------------------------------------------------------------------------
#include "DataRepresentationFrameWork.h"
#include <boost/shared_ptr.hpp>
#include "keypath.h"
//---------------------------------------------------------------------------
namespace darwinet {

	typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;

	typedef c_DarwinetString c_CaptionNode;

	typedef oprime::c_KeyPath<c_CaptionNode> c_DomainPath;
	typedef oprime::c_KeyPath<c_CaptionNode> c_ViewPath;
	typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;
	typedef oprime::c_KeyPath<oprime::c_IndexedKeyNode<c_CaptionNode> > c_InstancePath;

	typedef oprime::c_KeyPath<c_CaptionNode> c_DeltaIndex; // Models the index of a Delta

	namespace miv {
		/**
		  * Base interface of all SEPSI deltas.
		  */
		class c_DeltaSEPSI {
		public:
			// shared pointer to a c_DeltaSEPSI
			typedef boost::shared_ptr<c_DeltaSEPSI> shared_ptr;

			// Begin c_DeltaSEPSI

			/**
			  * Returns the index of the target Delta to which we apply
			  */
			virtual c_DeltaIndex::shared_ptr getTargetIndex() = 0;

			// End c_DeltaSEPSI

		};
	}; // namespace miv

	/**
	  * Models a Peer Message interface
	  */
	class c_PeerPackage {
	public:

		typedef boost::shared_ptr<c_PeerPackage> shared_ptr;

		/**
		  * Creates a new instance implementing this interface
		  */
		static c_PeerPackage::shared_ptr create();

		// Begin c_PeerPackage

		/**
		  * Adds provided c_DeltaSEPSI instace to "us"
		  */
		virtual void add(const miv::c_DeltaSEPSI::shared_ptr& pDeltaSEPSI) = 0;

		// End c_PeerPackage

	};

	/**
	  * Models a Peer Proxy
	  */
	class c_PeerProxy {
	public:

		typedef boost::shared_ptr<c_PeerProxy> shared_ptr;

		// Begin c_PeerProxy

		/**
		  * Send provided delta to the Peer we represent
		  */
		virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) = 0;

		// End c_PeerProxy

	};

	// Models a set of Peers
	typedef std::vector<c_PeerProxy::shared_ptr> c_PeerProxies;
	typedef boost::shared_ptr<c_PeerProxies> c_PeerProxies_shared_ptr;

	/**
	  * Models a Peer Source we may call to read
	  * Messages to a Peer
	  */
	class c_PeerSource {
	public:

		typedef boost::shared_ptr<c_PeerSource> shared_ptr;

		// Begin c_PeerSource

		/**
		  * Receive a delta from this source.
		  */
		virtual miv::c_DeltaSEPSI::shared_ptr receive()=0;

		// End c_PeerSource

	};

}
#endif
