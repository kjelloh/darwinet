//---------------------------------------------------------------------------

#pragma hdrstop

#include "DarwinetThinkTank.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */

namespace seedsrc {

	namespace miv6 {

		void test() {
			LOG_NOT_IMPLEMENTED;
			c_View::shared_ptr pView(new c_View());
			c_CommandFactory::shared_ptr pCommandFactory(new c_CommandFactory());

			// 1. Simulate client calling root M to execute a command
			auto pDelta = pView->getMIV()->executeCommand(pCommandFactory->newNullCommand());
			// 2. The created Delta should here be P2P distributed into all MIVs in the Domain
			// 3. Simulate applying Delta to ourselves.
			auto pEvent = pView->getMIV()->applyDelta(pDelta);
			// 4. The Event should here be sent to all listeners
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_Command::shared_ptr c_CommandFactory::newNullCommand() {
			c_Command::shared_ptr result(new c_Command());
			return result;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		// Begin c_CommandSinkIfc

		/**
		  * Execute provided command and return created Delta.
		  */
		c_ForwardDelta::shared_ptr c_MIV::executeCommand(c_Command::shared_ptr pCommand) {
			c_ForwardDelta::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			c_MIVMember::shared_ptr pMIVMember = this->getMember(pCommand->getTarget());
			if (pMIVMember) {
				result = pMIVMember->applyCommandOperation(pCommand->getOperation());
			}
			return result;
		}

		// End c_CommandSinkIfc

		// Begin c_DeltaSinkIfc

		/**
		  * Apply provided delta and return Event about made change
		  */
		c_Event::shared_ptr c_MIV::applyDelta(c_Delta::shared_ptr pDelta) {
			c_Event::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			c_MIVMember::shared_ptr pMIVMember = this->getMember(pDelta->getTarget());
			if (pMIVMember) {
				result = pMIVMember->applyDeltaOperation(pDelta->getOperation());
			}
			return result;
		}

		// End c_DeltaSinkIfc

		c_MIVMember::shared_ptr c_MIV::getMember(const c_MIVMemberId& id) {
			c_MIVMember::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			throw c_NotImplemented(METHOD_NAME);
//			throw c_NotImplemented(__FUNCTION__);
//			throw c_NotImplemented(typeid(*this).name());
			return result;
		}

		c_MIVMember::shared_ptr c_MIV::getMember(c_DeltaTarget::shared_ptr pDeltaTarget) {
			c_MIVMember::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			throw c_NotImplemented(METHOD_NAME);
//			throw c_NotImplemented(__FUNCTION__);
//			throw c_NotImplemented(typeid(*this).name());
			return result;
		}


	} // namespace miv6

} // namespace seedsrc
