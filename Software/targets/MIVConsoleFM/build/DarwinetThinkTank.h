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

		class c_DeltaOperation {
		private:
			typedef c_DeltaOperation C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;
		};
		//-------------------------------------------------------------------
		typedef std::string c_MIVsProducerIdentifier;
		typedef std::string c_DeltaBranchIdentifier;
		typedef std::string t_DeltaSeqNo;
		//-------------------------------------------------------------------
		class c_DeltaIndex {
		public:

			c_DeltaIndex(c_MIVsProducerIdentifier producer_id,c_DeltaBranchIdentifier branch_id,t_DeltaSeqNo seqno);

			c_MIVsProducerIdentifier getProducer() const {return m_Producer;}
			c_DeltaBranchIdentifier getBranch() const {return m_Branch;}
			t_DeltaSeqNo getSeqNo() const {return m_SeqNo;}

			bool operator==(const c_DeltaIndex& other_value) const {
				return (      (m_Producer == other_value.m_Producer)
						   && (m_Branch == other_value.m_Branch)
						   && (m_SeqNo == other_value.m_SeqNo));
			}

		private:
			c_MIVsProducerIdentifier m_Producer;
			c_DeltaBranchIdentifier m_Branch;
			t_DeltaSeqNo m_SeqNo;
		};
		//-------------------------------------------------------------------
		class c_DeltaTarget {
		public:

			c_DeltaTarget(c_DeltaIndex target_miv_state, c_MIVId target_miv_id);

			c_DeltaIndex getState() const {return m_target_miv_state;}
			c_MIVId getId() const {return m_target_miv_id;}

		private:
			c_DeltaIndex m_target_miv_state;
			c_MIVId m_target_miv_id;
		};
		//-------------------------------------------------------------------

		class c_Delta {
		private:
			typedef c_Delta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_DeltaBase(c_DeltaTarget target, c_DeltaIndex index, c_DeltaOperation delta_operation);

			c_DeltaTarget getTarget() const;
			c_DeltaIndex getIndex() const;
			c_DeltaOperation getDeltaOperation() const ;
		private:

			c_DeltaTarget m_DeltaTarget;
			c_DeltaIndex m_DeltaIndex;
			c_DeltaOperation m_delta_operation;

		};
		//-------------------------------------------------------------------
		class c_ForwardDelta
			: public c_Delta
		{
		private:
			typedef c_ForwardDelta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_ForwardDelta(c_DeltaTarget target, c_DeltaIndex index, c_DeltaOperation delta_operation,c_DeltaIndex predecessor) : c_DeltaBase(target, index, delta_operation),m_predecessor(predecessor) {;}

			c_DeltaIndex getPredecessor() const;

		private:

			c_DeltaIndex m_predecessor;
		};

		//-------------------------------------------------------------------
		class c_BackwardDelta
			: public c_Delta
		{
		private:
			typedef c_BackwardDelta C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			c_BackwardDelta(c_DeltaTarget target, c_DeltaIndex index, c_DeltaOperation delta_operation,c_DeltaIndex succsessor) : c_DeltaBase(target, index, delta_operation),m_succsessor(succsessor) {;}

			c_DeltaIndex getSuccessor() const;

		private:

			c_DeltaIndex m_succsessor;
		};

		class c_ForwardDeltaSignal {
		private:
			typedef c_DeltaSignal C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

		private:
			c_ForwardDelta m_delta;
		};

		//-------------------------------------------------------------------
		class c_CommandSinkIfc {
		private:
			typedef c_CommandSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_CommandSinkIfc

			/**
			  * Execute provided command and return created Delta operation.
			  */
			virtual c_ForwardDelta::shared_ptr executeCommand(c_Command::shared_ptr pCommand) = 0;

			// End c_CommandSinkIfc

		};

		class c_DeltaOperationSinkIfc {
		private:
			typedef c_DeltaOperationSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

			// Begin c_DeltaOperationSinkIfc

			/**
			  * Apply provided delta operation and return Event about made change
			  */
			virtual c_Event::shared_ptr applyDeltaOperation(c_DeltaOperation::shared_ptr pDeltaOperation) = 0;

			// End c_DeltaOperationSinkIfc
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
			virtual c_Event::shared_ptr applyForwardDelta(c_ForwardDelta::shared_ptr pForwardDelta) = 0;

			// End c_DeltaSinkIfc

		};

		//-------------------------------------------------------------------
		class c_MIV
		{
		private:
			typedef c_DeltaSinkIfc C_THIS;
		public:
			typedef boost::shared_ptr<C_THIS> shared_ptr;

		private:


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

			c_MIV::shared_ptr getMIV(const c_MIVId& id);
			c_M::shared_ptr getM(const c_MIVId& id);
			c_I::shared_ptr getI(const c_MIVId& id);
			c_V::shared_ptr getV(const c_MIVId& id);

			// Begin c_CommandSinkIfc

			/**
			  * Execute provided command and return created Delta operation.
			  */
			virtual c_ForwardDelta::shared_ptr executeCommand(c_Command::shared_ptr pCommand) {
				c_ForwardDelta::shared_ptr result;
				LOG_NOT_IMPLEMENTED;
				// 1. Find the command target
				// 2. Apply the Command operation to the target
				return result;
			}

			// End c_CommandSinkIfc

			// Begin c_DeltaSinkIfc

			/**
			  * Apply provided delta and return Event about made change
			  */
			virtual c_Event::shared_ptr applyForwardDelta(c_ForwardDelta::shared_ptr pForwardDelta) {
				c_Event::shared_ptr result;
				LOG_NOT_IMPLEMENTED;
				// 1. Find the delta target
				// 2. Apply the delta operation to the target
				return result;
			}

			// End c_DeltaSinkIfc

		private:
		};
		//-------------------------------------------------------------------

	}
}

#endif
