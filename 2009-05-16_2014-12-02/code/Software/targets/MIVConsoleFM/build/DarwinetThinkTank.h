//---------------------------------------------------------------------------

#ifndef DarwinetThinkTankH
#define DarwinetThinkTankH
#include <boost/shared_ptr.hpp> // Boost Requires e.g., $(CG_64_BOOST_ROOT) in the include path
#include <boost/make_shared.hpp>
#include "BusinessLogUnit.h"
#include <vector>
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
		typedef c_DarwinetString c_MIVMemberId;
		//-------------------------------------------------------------------
		class c_CommandOperation {
		private:
			typedef c_CommandOperation C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

		};
		//-------------------------------------------------------------------
		class c_Command {
		private:
			typedef c_Command C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;


			c_MIVMemberId getTarget() {return m_pTarget;}
			c_CommandOperation::shared_ptr getOperation() {return m_pOperation;}

		private:
			c_MIVMemberId m_pTarget;
			c_CommandOperation::shared_ptr m_pOperation;
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
		class c_DeltaOperation {
		private:
			typedef c_DeltaOperation C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};
		//-------------------------------------------------------------------
		typedef c_DarwinetString c_DeltaProducerId;
		typedef c_DarwinetString c_DeltaBranchId;
		typedef c_DarwinetString c_DeltaSeqNo;
		//-------------------------------------------------------------------
		class c_DeltaIndex {
		private:
			typedef c_DeltaIndex C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			c_DeltaProducerId m_Producer;
			c_DeltaBranchId m_Branch;
			c_DeltaSeqNo m_SeqNo;
		};
		//-------------------------------------------------------------------
		class c_DeltaTarget {
		private:
			typedef c_DeltaTarget C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			c_DeltaIndex m_State;
			c_MIVMemberId m_MIVMemberId;
		};
		//-------------------------------------------------------------------
		class c_Delta {
		private:
			typedef c_Delta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_DeltaTarget::shared_ptr getTarget() {return m_pTarget;}
			c_DeltaIndex::shared_ptr getIndex() {return m_pIndex;}
			c_DeltaOperation::shared_ptr getOperation() {return m_pOperation;}

		private:
			c_DeltaTarget::shared_ptr m_pTarget;
			c_DeltaIndex::shared_ptr m_pIndex;

			c_DeltaOperation::shared_ptr m_pOperation;
		};

		//-------------------------------------------------------------------
		class c_ForwardDelta : public c_Delta {
		private:
			typedef c_ForwardDelta C_THIS;
			c_DeltaIndex::shared_ptr getPredecessor() {return m_pPredecessor;}
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			c_DeltaIndex::shared_ptr m_pPredecessor;
		};

		//-------------------------------------------------------------------
		class c_BackwardDelta : public c_Delta {
		private:
			typedef c_ForwardDelta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
			c_DeltaIndex::shared_ptr getSuccessor() {return m_pSuccessor;}
		private:
			c_DeltaIndex::shared_ptr m_pSuccessor;
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
			virtual c_ForwardDelta::shared_ptr executeCommand(c_Command::shared_ptr pCommand) = 0;

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
			  * Apply provided delta and return Event about result
			  */
			virtual c_Event::shared_ptr applyDelta(c_Delta::shared_ptr pDelta) = 0;

			// End c_DeltaSinkIfc

		};

		class c_MIVMember {
		private:
			typedef c_MIVMember C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_MIVMemberId getId() {return m_id;}

			// Begin c_MIVMember

			virtual c_ForwardDelta::shared_ptr applyCommandOperation(c_CommandOperation::shared_ptr pCommandOperation) = 0;
			virtual c_Event::shared_ptr applyDeltaOperation(c_DeltaOperation::shared_ptr pDeltaOperation) = 0;

			// End c_MIVMember

		private:
			c_MIVMemberId m_id;
		};
		//-------------------------------------------------------------------
		class c_MIV; // Forward
		class c_I; // Forward
		class c_M : public c_MIVMember {
		private:
			typedef c_M C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			boost::shared_ptr<c_I> getI() {return m_pI;}

			// Begin c_MIVMember

			virtual c_ForwardDelta::shared_ptr applyCommandOperation(c_CommandOperation::shared_ptr pCommandOperation) {
				c_ForwardDelta::shared_ptr result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}

			// End c_MIVMember

		private:
			boost::shared_ptr<c_I> m_pI;
			boost::shared_ptr<c_MIV> m_pMIV;
		};

		//-------------------------------------------------------------------
		class c_V; // Forward;
		class c_I  {
		private:
			typedef c_I C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			boost::shared_ptr<c_V> m_pV;
			c_M::shared_ptr m_pM;
		};

		//-------------------------------------------------------------------
		class c_V  {
		private:
			typedef c_V C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			c_I::shared_ptr m_pI;
		};
		//-------------------------------------------------------------------
		class c_MIV:
			 public c_CommandSinkIfc
			,public c_DeltaSinkIfc
		{
		private:
			typedef c_MIV C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_CommandSinkIfc

			/**
			  * Execute provided command and return created Delta.
			  */
			virtual c_ForwardDelta::shared_ptr executeCommand(c_Command::shared_ptr pCommand);

			// End c_CommandSinkIfc

			// Begin c_DeltaSinkIfc

			/**
			  * Apply provided delta and return Event about made change
			  */
			virtual c_Event::shared_ptr applyDelta(c_Delta::shared_ptr pDelta);

			// End c_DeltaSinkIfc

			c_MIVMember::shared_ptr getMember(const c_MIVMemberId& id);
			c_MIVMember::shared_ptr getMember(c_DeltaTarget::shared_ptr pDeltaTarget);

		private:

			c_M::shared_ptr m_pRootM; // Only M members imppemented

		};
		//-------------------------------------------------------------------
		class c_ViewPoint {
		private:
			typedef c_ViewPoint C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};

		class c_View {
		private:
			typedef c_View C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_View() {;}

			c_MIV::shared_ptr getMIV() {
				if (!m_pMIV) {
					m_pMIV = boost::make_shared<c_MIV>();
				}
				return m_pMIV;
			}

		private:

			c_ViewPoint::shared_ptr m_pViewPoint;
			c_ViewPoint::shared_ptr getViewPoint() {
				if (!m_pViewPoint) {
					m_pViewPoint = boost::make_shared<c_ViewPoint>();
				}
				return m_pViewPoint;
			}

			c_MIV::shared_ptr m_pMIV;

		};

		class c_dMIVs {
		private:
			typedef c_dMIVs C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		private:
			std::vector<c_BackwardDelta::shared_ptr> m_BackwardDeltas;
		};

		class c_Domain {
		private:
			typedef c_Domain C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_dMIVs::shared_ptr getdMIVs() {
				if (!m_pdMIVs) {
					m_pdMIVs = boost::make_shared<c_dMIVs>();
				}
				return m_pdMIVs;
			}

		private:
			c_dMIVs::shared_ptr m_pdMIVs;
		};


	}
}

#endif
