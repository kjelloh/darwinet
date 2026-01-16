//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "DarwinetDeltas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

namespace darwinet {

	namespace miv {

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------
		/**
		  * Constructor
		  */
		c_DeltaImpl::c_DeltaImpl(const c_DeltaIndex::shared_ptr& pTargetIndex)
			:  m_pTargetIndex(pTargetIndex)
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

		/**
		  * Returns access to The Instance to wich we apply
		  */
		c_InstancePath::shared_ptr c_DeltaImpl::getTargetInstancePath() {
			return this->m_pTargetInstancePath;
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

		// Begin c_IntDeltaImpl

		int c_IntDeltaImpl::getValue() {
            return this->m_int_diff;
        }

		// End c_IntDeltaImpl

		//-----------------------------------------------------------------------
		//-----------------------------------------------------------------------

	} // namespace miv
} //  namespace darwinet
