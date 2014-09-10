//---------------------------------------------------------------------------

#pragma hdrstop

#include "DarwinetThinkTank.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Seed Source namespace. This is working source that
  * candidates to become part of the Darwinet framework
  */

namespace seedsrc {

	namespace miv6 {

		void test() {
			LOG_NOT_IMPLEMENTED;
			c_MIVs::shared_ptr pMIVs(new c_MIVs());
			c_CommandFactory::shared_ptr pCommandFactory(new c_CommandFactory());

			// 1. Simulate client calling root M to execute a command
			c_ForwardDelta::shared_ptr pDelta = pMIVs->executeCommand(pCommandFactory->newNullCommand());
			// 2. The created Delta should here be P2P distributed into all MIVs in the Domain
			// 3. Simulate applying Delta to ourselves.
			c_Event::shared_ptr pEvent = pMIVs->applyForwardDelta(pDelta);
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

		c_M::shared_ptr c_MIVs::getM(const c_MIVId& id) {
			c_M::shared_ptr result(new c_M());
			LOG_NOT_IMPLEMENTED;
			throw c_NotImplemented(__func__);
			return result;
		}

		c_I::shared_ptr c_MIVs::getI(const c_MIVId& id) {
			c_I::shared_ptr result(new c_I());
			LOG_NOT_IMPLEMENTED;
			return result;
		}

		c_V::shared_ptr c_MIVs::getV(const c_MIVId& id) {
			c_V::shared_ptr result(new c_V());
			LOG_NOT_IMPLEMENTED;
			return result;
		}

	} // namespace miv6

} // namespace seedsrc
