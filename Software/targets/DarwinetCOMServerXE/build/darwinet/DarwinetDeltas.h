//---------------------------------------------------------------------------

#ifndef DarwinetDeltasH
#define DarwinetDeltasH
//---------------------------------------------------------------------------
#include "DarwinetBase.h"
//---------------------------------------------------------------------------

namespace darwinet {

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


	} // namespace miv
} // namespace darwinet

#endif
