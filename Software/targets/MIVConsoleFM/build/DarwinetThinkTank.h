//---------------------------------------------------------------------------

#ifndef DarwinetThinkTankH
#define DarwinetThinkTankH
#include <boost/shared_ptr.hpp> // Boost Requires e.g., $(CG_64_BOOST_ROOT) in the include path
#include "BusinessLogUnit.h"

//---------------------------------------------------------------------------
/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */

namespace seedsrc {

	namespace miv6 {
		// Iteration 9. Time to try yet another remake.  (Continued from SepsiSeed in DarwinetCoreTestXE)

		// In the last iteration we got MIV exchange to work between MIVs on a basic level.
		// But the MIVs internal design did not cut it.
		// So this time we focus on the MIVs Core to find a design that kan
		// handle M, I and V aspects of the data storage.

		// Core Idea:	<Client> --> Command --> <MIV> --> DeltaMIV --> <Domain>
		//              <Client> <-- Event <---  <MIV> <-- DeltaMIV <-- <Domain>

		//-------------------------------------------------------------------
		void test();
		//-------------------------------------------------------------------
		typedef std::string c_DarwinetString;
		typedef c_DarwinetString c_MIVId;
		//-------------------------------------------------------------------

		class c_DarwinetException
			: public std::runtime_error
		{
		public:
			c_DarwinetException(const c_LogString& sHeading,const c_LogString& sMessage) : std::runtime_error((sHeading + sMessage).c_str()) {};
		};

		#define DARWINET_EXCEPTION_CLASS(X,Y) class X : public c_DarwinetException {public: X(const c_LogString& sMessage): c_DarwinetException(c_LogString(Y),sMessage) {};}

		DARWINET_EXCEPTION_CLASS(c_NotImplemented,"Not Implemented. ");
		DARWINET_EXCEPTION_CLASS(c_UnknownMIVId,"Unknown MIV Id. ");

		//-------------------------------------------------------------------
		class c_Command {
		private:
			typedef c_Command C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};


		//-------------------------------------------------------------------
		class c_CommandFactory {
		private:
			typedef c_CommandFactory C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_Command::shared_ptr newNullCommand();
		};
		//-------------------------------------------------------------------
		class c_Event {
		private:
			typedef c_Event C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_Delta {
		private:
			typedef c_Delta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_CommandSinkIfc {
		private:
			typedef c_CommandSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_CommandSinkIfc

			/**
			  * Execute provided command and return created Delta.
			  */
			virtual c_Delta::shared_ptr executeCommand(c_Command::shared_ptr pCommand) = 0;

			// End c_CommandSinkIfc

		};

		//-------------------------------------------------------------------
		class c_DeltaSinkIfc {
		private:
			typedef c_DeltaSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_DeltaSinkIfc

			/**
			  * Apply provided delta and return Event about made change
			  */
			virtual c_Event::shared_ptr applyDelta(c_Delta::shared_ptr pDelta) = 0;

			// End c_DeltaSinkIfc

		};

		//-------------------------------------------------------------------
		class c_MIV:
			 public c_CommandSinkIfc
			,public c_DeltaSinkIfc
		{
		private:
			typedef c_DeltaSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_CommandSinkIfc

			/**
			  * Execute provided command and return created Delta.
			  */
			virtual c_Delta::shared_ptr executeCommand(c_Command::shared_ptr pCommand) {
				c_Delta::shared_ptr result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}

			// End c_CommandSinkIfc

			// Begin c_DeltaSinkIfc

			/**
			  * Apply provided delta and return Event about made change
			  */
			virtual c_Event::shared_ptr applyDelta(c_Delta::shared_ptr pDelta) {
				c_Event::shared_ptr result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}

			// End c_DeltaSinkIfc

		};

		//-------------------------------------------------------------------
		class c_M : public c_MIV
		{
		private:
			typedef c_M C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_I : public c_MIV {
		private:
			typedef c_I C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_V : public c_MIV {
		private:
			typedef c_V C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_MIVs {
		private:
			typedef c_MIVs C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_M::shared_ptr getM(const c_MIVId& id);
			c_I::shared_ptr getI(const c_MIVId& id);
			c_V::shared_ptr getV(const c_MIVId& id);

		private:
		};
		//-------------------------------------------------------------------

	}
}

#endif
