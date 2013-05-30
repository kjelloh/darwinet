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
	  * Models a Peer Sink
	  */
	class c_PeerSink {
	public:

		typedef boost::shared_ptr<c_PeerSink> shared_ptr;

		// Begin c_PeerSink

		/**
		  * Send provided delta to the Sink we represent
		  */
		virtual void send(const miv::c_DeltaSEPSI::shared_ptr& pDelta) = 0;

		// End c_PeerSink
	};

	// Models a set of Peers
	typedef std::vector<c_PeerSink::shared_ptr> c_PeerSinks;
	typedef boost::shared_ptr<c_PeerSinks> c_PeerSinks_shared_ptr;

}
#endif
