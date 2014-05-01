//---------------------------------------------------------------------------

#ifndef SEPSISeedH
#define SEPSISeedH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>
#include <boost/variant.hpp>
#include "DarwinetBase.h"
#include <map>
#include <list>
#include <queue>
#include <boost/function.hpp>
#include "DarwinetWindowsGUIInterface.h"
//---------------------------------------------------------------------------

/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */

namespace seedsrc {

	namespace miv5 {
		// Iteration 8. Here we go again. Iteration 7 proved to be still to complicated
		//              for core MIV testing. Now we will simply focusing on
		//              having MIV's exchanging deltas!

		/**
		  *
		  * Consider to model members according to "UML in color" (http://en.wikipedia.org/wiki/UML_colors)
		  * 1. moment-interval — Does it represent a moment or interval of time
		  *    that we need to remember and work with for legal or business
		  *    reasons? Examples in business systems generally model activities
		  *    involving people, places and things such as a sale, an order,
		  *    a rental, an employment, making a journey, etc.
		  * 2. roles — Is it a way of participating in an activity
		  *   (by either a person, place, or thing)? A person playing the role
		  *   of an employee in an employment, a thing playing the role of a
		  *   product in a sale, a location playing the role of a classroom for
		  *   a training course, are examples of roles.
		  * 3. description — Is it simply a catalog-entry-like description which
		  *    classifies or 'labels' an object? For example, the make and
		  *    model of a car categorises or describes a number of physical
		  *    vehicles. The relationship between the blue description and
		  *    green party, place or thing is a type-instance relationship based
		  *    on differences in the values of data items held in the 'type' object.
		  * 4. party, place, or thing — Something tangible, uniquely identifiable.
		  *    Typically the role-players in a system. People are green.
		  *    Organizations are green. The physical objects involved in a rental
		  *    such as the physical DVDs are green things. Normally, if you get
		  *    through the above three questions and end up here,
		  *    your class is a "green."
		  */
		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		typedef oprime::c_KeyPath<c_CaptionNode> c_CaptionPath;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<oprime::c_IndexedKeyNode<c_CaptionNode> > c_MIVPath;
		typedef c_DarwinetString c_MIVsProducerIdentifier;
		typedef c_DarwinetString c_DeltaBranchIdentifier;
		typedef unsigned int t_DeltaSeqNo;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<oprime::c_IndexedKeyNode<c_CaptionNode> > c_MessageTargetId;
		typedef std::vector<c_MessageTargetId> c_MessageTargetIds;
		typedef boost::shared_ptr<c_MessageTargetIds> c_MessageTargetIds_shared_ptr;
		//-------------------------------------------------------------------
		enum e_SignalField {
			 eSignalField_Undefined
			 // Signal header elements
			,eSignalField_SignalSender
			,eSignalField_SignalReceiver
			,eSignalField_SignalIdentifier
			// ModifyMIVRequest
			,eSignalField_MIVsOperationId
			,eSignalField_MIVsOperationTargetId
			,eSignalField_MIVsOperationNewValue
			,eSignalField_MIVsEventId
			,eSignalField_MIVsEventSourceId
			,eSignalField_MIVsEventValue
			// Delta Signal elements
			,eSignalField_DeltaPredecessorIx
			,eSignalField_DeltaIx
			,eSignalField_DeltaTargetState
			,eSignalField_DeltaTargetMIVId
			,eSignalField_DeltaOperationId
			,eSignalField_IntDeltaOperationValue
			,eSignalField_StringDeltaOperationIndex
			,eSignalField_StringDeltaOperationValue
			,eSignalField_Unknown
		};

		class c_SignalFieldMapper
			: public std::map<e_SignalField,c_DarwinetString>
		{
		public:
			typedef boost::shared_ptr<c_SignalFieldMapper> shared_ptr;
			typedef std::map<e_SignalField,c_DarwinetString> _Base;

			c_SignalFieldMapper();

			virtual c_DarwinetString& operator[](e_SignalField eKey);

		};

		enum e_SignalIdentifier {
			eSignalIdentifier_Undefined
			,eSignalIdentifier_getMIVs
			,eSignalIdentifier_getMIVsResponse
			,eSignalIdentifier_ModifyMIVRequest
			,eSignalIdentifier_OnMIVEvent
			,eSignalIdentifier_DeltaMIV
			,eSignalIdentifier_Unknown
		};

		class c_SignalIdentifierMapper
			: public std::map<e_SignalIdentifier,c_DarwinetString>
		{
		public:
			typedef boost::shared_ptr<c_SignalIdentifierMapper> shared_ptr;
			typedef std::map<e_SignalIdentifier,c_DarwinetString> _Base;

			c_SignalIdentifierMapper();

			virtual c_DarwinetString& operator[](e_SignalIdentifier eKey);

		};

		enum e_MIVsOperation {
			eMIVsOperation_Undefined
			,eMIVsOperation_Assign
			,eMIVsOperation_Unknown
		};

		class c_MIVsOperationMapper
			: public std::map<e_MIVsOperation,c_DarwinetString>
		{
		public:
			typedef boost::shared_ptr<c_MIVsOperationMapper> shared_ptr;
			typedef std::map<e_MIVsOperation,c_DarwinetString> _Base;

			c_MIVsOperationMapper();

			virtual c_DarwinetString& operator[](e_MIVsOperation eKey);

		};

		enum e_MIVsEventId {
			eMIVsEventId_Undefined
			,eMIVsEventId_OnMIVValueChanged
			,eMIVsEventId_Unknown
		};

		class c_MIVsEventIdMapper
			: public std::map<e_MIVsEventId,c_DarwinetString>
		{
		public:
			typedef boost::shared_ptr<c_MIVsEventIdMapper> shared_ptr;
			typedef std::map<e_MIVsEventId,c_DarwinetString> _Base;

			c_MIVsEventIdMapper();

			virtual c_DarwinetString& operator[](e_MIVsEventId eKey);

		};

		enum e_DeltaOperationId {
			 eDeltaOperationId_Undefined
			,eDeltaOperationId_IntDeltaAdd
			,eDeltaOperationId_ArrayDeltaExtend
			,eDeltaOperationId_ArrayDeltaContract
			,eDeltaOperationId_Unknown
		};

		class c_DeltaOperationIdMapper
			: public std::map<e_DeltaOperationId,c_DarwinetString>
		{
		public:
			typedef boost::shared_ptr<c_DeltaOperationIdMapper> shared_ptr;
			typedef std::map<e_DeltaOperationId,c_DarwinetString> _Base;

			c_DeltaOperationIdMapper();

			virtual c_DarwinetString& operator[](e_DeltaOperationId eKey);

		};

		static c_SignalFieldMapper SIGNAL_FIELD_MAPPER;
		static c_SignalIdentifierMapper SIGNAL_IDENTIFIER_MAPPER;
		static c_MIVsOperationMapper MIVS_OPERATION_MAPPER;
		static c_MIVsEventIdMapper MIVS_EVENT_MAPPER;
		static c_DeltaOperationIdMapper DELTA_OPERATION_MAPPER;

		//-------------------------------------------------------------------
		class c_Signal : public std::vector<std::pair<c_CaptionNode,c_CaptionNode> > {
		private:
			typedef std::vector<std::pair<c_CaptionNode,c_CaptionNode> > _Base;
		public:
			typedef boost::shared_ptr<c_Signal> shared_ptr;
			typedef c_DarwinetString t_key;
			typedef c_DarwinetString t_value;
			typedef _Base::iterator iterator;
			typedef _Base::const_iterator const_iterator;
			typedef std::pair<c_CaptionNode,c_CaptionNode> Pair;

			const_iterator find(const c_CaptionNode& sKey);

			c_DarwinetString getValue(c_CaptionNode sKey);

//			void addElement(const c_DarwinetString& sKey,const c_DarwinetString& sValue);
			void addElement(e_SignalField eKey,const c_CaptionNode& sValue);

			c_MessageTargetId getTargetId();

		};
		//-------------------------------------------------------------------
		class c_SignalQueue
			: public std::queue<c_Signal::shared_ptr>
		{
		public:
			typedef boost::shared_ptr<c_SignalQueue> shared_ptr;

			void append(c_SignalQueue::shared_ptr pQueue);

		};
		//-------------------------------------------------------------------
		class c_SignalSinkIfc {
		public:
			typedef boost::shared_ptr<c_SignalSinkIfc> shared_ptr;
			typedef boost::weak_ptr<c_SignalSinkIfc> weak_ptr;

			// Begin c_SignalSinkIfc

			virtual c_MessageTargetId getId() = 0;

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal) = 0;

			// End c_SignalSinkIfc

		private:

			c_SignalSinkIfc::shared_ptr m_pSignalTarget;
		};
		//-------------------------------------------------------------------
		class c_Messenger {
		public:

			void send(c_Signal::shared_ptr pSignal);

			void send(c_SignalQueue::shared_ptr pSignals);

			void connect(c_SignalSinkIfc::weak_ptr pSignalSink);

			void process();

		private:

			std::map<c_MessageTargetId,c_SignalSinkIfc::weak_ptr> m_SignalSinks;
			c_SignalQueue m_SignalQueue;

		};
		//-------------------------------------------------------------------
//		class c_SignalPipe :
//			 public std::queue<c_Signal::shared_ptr>
//		{
//		public:
//
//			c_SignalPipe() {
//				LOG_METHOD_SCOPE;
//			}
//
//			typedef boost::shared_ptr<c_SignalPipe> shared_ptr;
//
//			virtual void actOnInSignal(const c_Signal::shared_ptr& pSignal);
//
//			void process();
//
//			boost::function<void (const c_Signal::shared_ptr& pSignal)> onSignalToTarget;
//
//		};

		//-------------------------------------------------------------------
//		class c_SignalPipes : public std::map<int,c_SignalPipe::shared_ptr> {
//		public:
//			typedef boost::shared_ptr<c_SignalPipes> shared_ptr;
//
//		};
		//-------------------------------------------------------------------

		class c_DarwinetException
			: public std::runtime_error
		{
		public:
//			c_DarwinetException(const c_LogString& sMessage) : std::runtime_error(sMessage.c_str()) {};
			c_DarwinetException(const c_LogString& sHeading,const c_LogString& sMessage) : std::runtime_error((sHeading + sMessage).c_str()) {};
		};

		#define DARWINET_EXCEPTION_CLASS(X,Y) class X : public c_DarwinetException {public: X(const c_LogString& sMessage): c_DarwinetException(c_LogString(Y),sMessage) {};}

		DARWINET_EXCEPTION_CLASS(c_InvalidActorIdException,"Invalid Actor Id. ");
		DARWINET_EXCEPTION_CLASS(c_IllformedSignalStringException,"Illformed signal string representation. ");
		DARWINET_EXCEPTION_CLASS(c_NoSuchMIVException,"No such MIV. ");
		DARWINET_EXCEPTION_CLASS(c_NULLDeltaException,"NULL Delta. ");
		DARWINET_EXCEPTION_CLASS(c_IllFormedSignalFieldException,"Illformed Signal Field. ");
		DARWINET_EXCEPTION_CLASS(c_DeltaApplicationException," Failed to apply Delta. ");
		DARWINET_EXCEPTION_CLASS(c_NULLMIVBodyException,"NULL MIV Body. ");
		DARWINET_EXCEPTION_CLASS(c_UnknownDeltaOperation,"Unknown Delta Operation. ");
		DARWINET_EXCEPTION_CLASS(c_StringDeltaCreationFailed,"String Delta Creation Failed. ");
		DARWINET_EXCEPTION_CLASS(c_UnknownMIVValueType,"Unknown MIV Value Type. ");

		//-------------------------------------------------------------------
		c_DarwinetString toString(const c_Signal& signal);
		//-------------------------------------------------------------------
		c_Signal createSignalFromString(const c_DarwinetString& sSignal);
		//-------------------------------------------------------------------


		const INT_INIT_VALUE = 0;
		class c_IntValue {
		public:
			typedef boost::shared_ptr<c_IntValue> shared_ptr;

			c_IntValue(int raw_value = INT_INIT_VALUE) : m_raw_value(raw_value) {;}

			int getRawValue() const {return m_raw_value;}
			void setRawValue(int raw_value) {m_raw_value = raw_value;}

		private:
			int m_raw_value;
		};

		class c_StringValue {
		public:
			typedef c_DarwinetString _RawValueType;
			typedef boost::shared_ptr<c_StringValue> shared_ptr;

			c_StringValue(const _RawValueType& raw_value = _RawValueType()) : m_raw_value(raw_value) {;}

			const _RawValueType& getRawValue() const {return m_raw_value;}

			c_StringValue& extend(int target_index,const c_StringValue& string_value) {
				m_raw_value.insert(target_index,string_value.getRawValue());
				return *this;
			}

			c_StringValue& contract(int target_index,const c_StringValue& string_value) {
				m_raw_value.erase(target_index,string_value.getRawValue().length());
				return *this;
			}

		private:
			_RawValueType m_raw_value;
		};

		class c_ArrayValue {
		public:
			typedef boost::shared_ptr<c_ArrayValue> shared_ptr;
			// Vector of same type c_V
		};

		class c_RecordValue {
		public:
			typedef boost::shared_ptr<c_RecordValue> shared_ptr;
			// Vector of different type c_V
		};

		typedef boost::variant<c_IntValue,c_StringValue,c_RecordValue, c_ArrayValue> c_Value;
		typedef boost::shared_ptr<c_Value> c_Value_shared_ptr;


		//-------------------------------------------------------------------
		/**
		  * Moment
		  */
		class c_DeltaIndex {
		public:

//			c_DeltaIndex(const c_MIVsProducerIdentifier& producer = _UTF8sz("??producer??"),const c_DeltaBranchIdentifier& branch = _UTF8sz("??branch??"),const t_DeltaSeqNo& seq_no = 0);

			c_MIVsProducerIdentifier getProducer() const {return m_Producer;}
			c_DeltaBranchIdentifier getBranch() const {return m_Branch;}
			t_DeltaSeqNo getSeqNo() const {return m_SeqNo;}

			void setProducer(const c_MIVsProducerIdentifier& producer) {m_Producer = producer;}
			void setBranch(const c_DeltaBranchIdentifier& branch) {m_Branch = branch;}
			void setSeqNo(const t_DeltaSeqNo& seq_no) {m_SeqNo = seq_no;}

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
		class c_V {
		public:
			typedef boost::shared_ptr<c_V> shared_ptr;

			const c_DeltaIndex& getState() const {return m_State;}
			const c_Value& getValue() const {return m_Value;}
			c_Value& getValue() {return m_Value;}

			void setState(const c_DeltaIndex& state) {m_State = state;}
			void setValue(const c_Value& value) {m_Value = value;}

		private:
			c_DeltaIndex m_State;
			c_Value m_Value;
		};

		typedef std::map<c_MIVPath,c_V::shared_ptr> c_MappedVs;

		class c_I {
		public:
			typedef boost::shared_ptr<c_I> shared_ptr;

			c_V::shared_ptr getV() {return m_pV;}
			void setV(c_V::shared_ptr pV) {m_pV = pV;}

		private:
			c_V::shared_ptr m_pV;
		};

		typedef std::map<c_MIVPath,c_I::shared_ptr> c_MappedIs;

		class c_M {
		public:
			typedef boost::shared_ptr<c_M> shared_ptr;
		private:
			typedef std::vector<c_I::shared_ptr> c_Is;
		};

		typedef std::map<c_MIVPath,c_M::shared_ptr> c_MappedMs;

		//-------------------------------------------------------------------
		/**
		  * Description
		  */
		class c_MIVTarget {
		public:

			// Needed because - Failed to create default assignment operator for c_MIVTarget := (const c_MIVTarget)
			//                   due to member m_MIVId (Why? nothing wrong with c_MIVPath copy constructor nor assignment operator?)
			c_MIVTarget& operator=(c_MIVTarget other_instance_copy) {std::swap(m_State,other_instance_copy.m_State);std::swap(m_MIVId,other_instance_copy.m_MIVId); return *this;}

			c_DeltaIndex getState() const {return m_State;}
			c_MIVPath getMIVId() const {return m_MIVId;}

			void setState(const c_DeltaIndex& state) {m_State = state;}
			void setMIVId(const c_MIVPath& miv_id) {m_MIVId = miv_id;}

		private:
			c_DeltaIndex m_State;
			c_MIVPath m_MIVId;
		};
		//-------------------------------------------------------------------
		enum e_IntOperationId {
			eIntOperationId_Undefined
			,eIntOperationId_ADD
			,eIntOperationId_Unknown
		};

		class c_IntDeltaOperation {
		public:
			c_IntDeltaOperation(e_IntOperationId int_operation_id, const c_IntValue& delta_value);

			c_IntValue operator()(c_IntValue& current_value) const;

			c_IntValue getValue() const {return m_delta_value;}
			e_IntOperationId getIntOperationId() const {return m_int_operation_id;}

		private:
			c_IntValue m_delta_value;
			e_IntOperationId m_int_operation_id;
		};

		enum e_StringDeltaOperation {
			 eStringDeltaOperation_Undefined
			,eStringDeltaOperation_Extend
			,eStringDeltaOperation_Contract
			,eStringDeltaOperation_Unknown
		};
		class c_StringDeltaOperation {
		/*
			Implement only "array expand" and "array contract"

			array expand = {position,+,value_to_insert}
			array contratc = {position,-,value_to_remove}

			forward: "Hej" + {3,+,'!'} := "Hej!"
			backward: "hej!" + {3,-,'!'} := "Hej"

			This works for modifications to.

			forward: "Hej+Hopp" + {{3,-,'+'};{3,+,'-'}} := "Hej-Hopp"
			backward: "Hej-Hopp" + {{3,-,'-'};{3,+,'+'}} := "Hej+Hopp"

			Note: The backward delta {{3,-,'-'};{3,+,'+'}} is the forward delta {{3,-,'+'};{3,+,'-'}} with each operation reversed and applied in reverse order.

			This works for ranges to!

			forward: "Hej Hopp" + {3,+," and"} := "Hej and Hopp"
			reverse: "Hej and Hopp" + {3,-," and"} := "Hej Hopp"

			And consequensly for modification.

			forward: "Hej and Hopp" + {{3,-," and"};{3,+," och"} := "Hej och Hopp"
			backward: "Hej och Hopp" + {{3,-," och"};{3,+," and"}} := "Hej and Hopp"

			Note: forward delta {target_index,+,value} means backward delta is {{target_index,-,value}}
				  forward delta {target_index,-,value} means backward delta is {{target_index,+,value}}

		*/

		public:

			c_StringDeltaOperation(e_StringDeltaOperation StringDeltaOperation = eStringDeltaOperation_Undefined,unsigned int target_index=0,const c_StringValue& sDeltaValue = c_StringValue())
				: m_sDeltaValue(sDeltaValue)
				 ,m_target_index(target_index)
				 ,m_StringDeltaOperation(StringDeltaOperation)
			{;}

			unsigned int getTargetIndex() const {return m_target_index;}
			e_StringDeltaOperation getOperation() const {return m_StringDeltaOperation;}
			const c_StringValue& getDeltaValue() const {return m_sDeltaValue;}

			c_StringValue operator()(c_StringValue& current_value) const;

			void setTargetIndex(unsigned int target_index) {m_target_index = target_index;}
			void setOperation(e_StringDeltaOperation StringDeltaOperation) {m_StringDeltaOperation = StringDeltaOperation;}
			void setDeltaValue(const c_StringValue& sDeltaValue) {m_sDeltaValue = sDeltaValue;}

		private:
			unsigned int m_target_index;
			e_StringDeltaOperation m_StringDeltaOperation;
			c_StringValue m_sDeltaValue;
		};

		class c_RecordDeltaOperation {
		};

		class c_ArrayDeltaOperation {
		};

		typedef boost::variant<c_IntDeltaOperation,c_StringDeltaOperation,c_RecordDeltaOperation, c_ArrayDeltaOperation> c_DeltaOperation;
		typedef boost::shared_ptr<c_DeltaOperation> c_DeltaOperation_shared_ptr;

		//-------------------------------------------------------------------
		class c_Delta {
		public:
			typedef boost::shared_ptr<c_Delta> shared_ptr;

			c_DeltaIndex getPredecessor() const;// {return m_Predecessor;}
			c_MIVTarget getMIVtarget() const;// { return m_Target;}
			c_DeltaIndex getIndex() const; // { return m_Index;}
			c_DeltaOperation_shared_ptr getDeltaOperation() const ;// {return m_pDeltaOperation;}

			void setPredecessor(const c_DeltaIndex& predecessor);// {m_Predecessor = predecessor;}
			void setMIVtarget(const c_MIVTarget& target);// { m_Target = target;}
			void setIndex(const c_DeltaIndex& index);// { m_Index = index;}
			void setDeltaOperation(const c_DeltaOperation_shared_ptr& pDeltaOperation);// {m_pDeltaOperation = pDeltaOperation;}

		private:
			c_DeltaIndex m_Predecessor;
			c_MIVTarget m_Target;
			c_DeltaIndex m_Index;

			c_DeltaOperation_shared_ptr m_pDeltaOperation;
		};
		//-------------------------------------------------------------------

		typedef boost::variant<c_M,c_I,c_V> c_MIVBody;
		typedef boost::shared_ptr<c_MIVBody> c_MIVBody_shared_ptr;

		class c_MIV {
		public:
			typedef boost::shared_ptr<c_MIV> shared_ptr;
			c_DeltaIndex getState() {return m_State;}
//			c_MIVBody& getBody() {return m_MIVBody;} // Return ref to allow variant visitor to visit
			c_MIVBody_shared_ptr getBody() {return m_pMIVBody;}

			void setState(const c_DeltaIndex& state) {m_State = state;}
//			void setBody(const c_MIVBody& body) {m_MIVBody = body;}
			void setBody(const c_MIVBody_shared_ptr& pBody) {m_pMIVBody = pBody;}

		private:
			c_DeltaIndex m_State; // Index of last applied Delta defining this state
//			c_MIVBody m_MIVBody;
			c_MIVBody_shared_ptr m_pMIVBody;
		};

		typedef std::map<c_MIVPath,c_MIV::shared_ptr> c_MappedMIVs;


		class c_MIVs {
		public:
			typedef boost::shared_ptr<c_MIVs> shared_ptr;

			c_MIVs(const c_DeltaIndex& last_created_delta_index)
				:  m_LastCreatedDeltaIndex(last_created_delta_index)
			{;}

			c_Delta::shared_ptr createSetValueDelta(const c_MIVPath& id,c_Value_shared_ptr pNewValue);

			c_MIV::shared_ptr getMIV(const c_MIVPath& miv_path);

			bool isIntV(const c_MIVPath& miv_path);
			bool isStringV(const c_MIVPath& miv_path);
			bool isV(const c_MIVPath& miv_path);

		private:

			c_DeltaIndex m_LastCreatedDeltaIndex;
			c_DeltaIndex m_LastAppliedDeltaIndex;
			c_MappedMIVs m_MappedMIVs;
		};

		//-------------------------------------------------------------------
		class c_MIVsHandler
			: public c_SignalSinkIfc
		{
		public:
			typedef boost::shared_ptr<c_MIVsHandler> shared_ptr;

			c_MIVsHandler(c_MessageTargetId id);

			// Begin c_SignalSinkIfc

			virtual c_MessageTargetId getId();

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal);

			// End c_SignalSinkIfc

			void setListeningClientId(c_MessageTargetId listening_client_id);

		private:

			c_Delta::shared_ptr createSetValueDelta(c_MIVPath id,c_Value_shared_ptr pNewValue);
			c_SignalQueue::shared_ptr actOnDelta(c_Delta::shared_ptr pDelta);

			c_MIVs::shared_ptr getMIVs();

			c_MessageTargetId m_id;
			c_MIVs::shared_ptr m_pMIVs;

			c_MessageTargetId m_listening_client_id;

		};

		//-------------------------------------------------------------------
		class c_MIVsView {
		private:
			c_DeltaIndex m_ViewPoint;
		};

		class c_ViewHandler
			: public c_SignalSinkIfc
		{
		public:
			typedef boost::shared_ptr<c_ViewHandler> shared_ptr;

			c_ViewHandler(c_MessageTargetId id);

			// Begin c_SignalSinkIfc

			virtual c_MessageTargetId getId();

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal);

			// End c_SignalSinkIfc

			c_MIVsHandler::shared_ptr getMIVsHandler();

		private:
			c_MessageTargetId m_id;
			c_MIVsView m_MIVsView;
			c_MIVsHandler::shared_ptr m_pMIVsHandler;
		};
		//-------------------------------------------------------------------
		typedef std::map<int,c_ViewHandler::shared_ptr> c_ViewHandlers;
		//-------------------------------------------------------------------
		class c_DomainHandler
			: public c_SignalSinkIfc
		{
		public:
			typedef boost::shared_ptr<c_DomainHandler> shared_ptr;

			c_DomainHandler(c_MessageTargetId id);

			// Begin c_SignalSinkIfc

			virtual c_MessageTargetId getId();

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal);

			// End c_SignalSinkIfc

			c_ViewHandler::shared_ptr getViewHandler(int view_index);

		private:
			c_MessageTargetId m_id;
			c_ViewHandlers m_ViewHandlers;
		};

		//-------------------------------------------------------------------
		class c_DarwinetEngine {
		public:
			typedef boost::shared_ptr<c_DarwinetEngine> shared_ptr;

			c_DarwinetEngine(c_MessageTargetId id);

			virtual c_MessageTargetId getId();

			c_DomainHandler::shared_ptr getDomainHandler(int domain_index);
		private:

			c_MessageTargetId m_id;

			c_DomainHandler::shared_ptr m_pDomainHandler;
		};
		//-------------------------------------------------------------------
		// Test clients

		//-------------------------------------------------------------------
		class c_GUIClientproxy; // Forward
		//-------------------------------------------------------------------
		class c_TestClient
			: public c_SignalSinkIfc
		{
		public:
			typedef boost::shared_ptr<c_TestClient> shared_ptr;
			typedef c_DarwinetString c_MIVsValue;

			c_TestClient(c_MessageTargetId id);

			void connect(boost::shared_ptr<c_GUIClientproxy> pClientProxy);

			void open();

			bool isOpen();

			void setMIVsid(c_MessageTargetId MIVsMessageTargetId);

			// Begin c_SignalSinkIfc

			c_MessageTargetId getId();

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal);

			// End c_SignalSinkIfc

//			boost::function<void (const c_Signal::shared_ptr& pSignal)> onSignalToMIVs;
//
//			void actOnSignalFromMIVs(const c_Signal::shared_ptr& pSignal);
//
//			c_SignalQueue::shared_ptr testMIVChange();

			void setMIVsValue(c_MIVPath MIVsId,c_TestClient::c_MIVsValue value);

		private:

			c_MessageTargetId m_id;
			boost::shared_ptr<c_GUIClientproxy> m_pClientProxy;
			bool m_isOpen;
			c_MessageTargetId m_MIVsHandlerId;

			c_MessageTargetId getMIVsHandlerId();
		};

		typedef std::map<unsigned int,c_TestClient::shared_ptr> c_TestClients;

		/**
		  * The c_DarwinetTestBench singleton
		  */
		class c_DarwinetTestBench {
		public:
			typedef boost::shared_ptr<c_DarwinetTestBench> shared_ptr;

			static c_DarwinetTestBench::shared_ptr instance();

			c_DarwinetEngine::shared_ptr getDarwinetEngine();

			c_Signal::shared_ptr createSignal(c_MessageTargetId senderMessageTargetId,c_MessageTargetId receiverMessageTargetId);

			c_TestClient::shared_ptr getTestClient(unsigned int index);

			void sendMessage(c_Signal::shared_ptr pSignal);

			c_MessageTargetIds_shared_ptr getAllMIVHandlerIds();

			void processMessages();

		private:

			c_DarwinetTestBench();

			static c_DarwinetTestBench::shared_ptr m_pSharedInstance;

			c_DarwinetEngine::shared_ptr m_pDarwinetEngine;

			c_TestClients m_TestCients;

			c_Messenger m_Messenger;

		};

		namespace log {
			c_LogString toLogString(const c_Signal& signal);
			c_LogString toLogString(c_Signal::shared_ptr pSignal);
			c_LogString toLogString(const c_MIVTarget& miv_target);
			c_LogString toLogString(const c_DeltaIndex& index);

			void logSignalSend(c_Signal::shared_ptr pSignal);
		}

		void test();

		class c_GUIClientproxy
			: public c_SignalSinkIfc
		{
		public:
			typedef boost::shared_ptr<c_GUIClientproxy> shared_ptr;
			typedef c_DarwinetString c_SignalString;
			typedef c_DarwinetString c_MIVsId; // Identifier of a whole MIVs
			typedef c_DarwinetString c_MIVId; // Identifier of one MIV
			typedef c_DarwinetString c_MIVValue;

			c_GUIClientproxy(c_TestClient::shared_ptr pClient);

			void open();

			bool isOpen();

			void setMIVsValue(c_GUIClientproxy::c_MIVId MIVId,c_GUIClientproxy::c_MIVValue value);

			void setGUIWindowhandle(HWND pGUIWindow);

			// Begin c_SignalSinkIfc

			c_MessageTargetId getId();

			virtual c_SignalQueue::shared_ptr actOnSignal(const c_Signal::shared_ptr& pSignal);

			// End c_SignalSinkIfc

		private:
			HWND m_pGUIWindow;

			c_TestClient::shared_ptr m_pClient;
		};

		/**
		  * helper class to interface client side with server side Testbench
		  */
		class c_TestBenchClientSideProxy {
		public:
			typedef boost::shared_ptr<c_TestBenchClientSideProxy> shared_ptr;

			c_TestBenchClientSideProxy();

			c_GUIClientproxy::shared_ptr getGUIClientproxy(int index);

			HWND m_pGUIWindow;

			void processMessages();

		private:

			std::map<unsigned int,c_GUIClientproxy::shared_ptr> m_GUIClientproxies;

		};
	} // namespace miv5

	namespace miv4 {
		// Iteration 7. Going for the Delta with {Predecessor, Producer, Target, Index} properties.
		//              Focusing on getting the synchronizarion to work.

		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<c_CaptionNode> c_MIVPath;
		typedef oprime::c_KeyPath<c_CaptionNode> c_StackActorPath;
		typedef unsigned int t_DeltaProducerId;
		typedef unsigned int t_DeltaSequenceNumber;

		//-------------------------------------------------------------------
		class c_DeltaId {
		private:
			t_DeltaProducerId m_DeltaProducerId;
			t_DeltaSequenceNumber m_DeltaSequenceNumber;
		};

		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<c_DeltaId> c_DeltaBranchId;

		//-------------------------------------------------------------------
		class c_Delta {
		private:
			c_DeltaId m_Predecessor;
			t_DeltaProducerId m_DeltaProducerId;
			t_DeltaSequenceNumber m_DeltaSequenceNumber;
			c_MIVPath m_Target;
		};

		//-------------------------------------------------------------------
		class c_Signal : public std::vector<std::pair<c_DarwinetString,c_DarwinetString> > {
		private:
			typedef std::vector<std::pair<c_DarwinetString,c_DarwinetString> > _Base;
		public:
			typedef boost::shared_ptr<c_Signal> shared_ptr;
			typedef _Base::iterator iterator;
			typedef _Base::const_iterator const_iterator;
			typedef std::pair<c_DarwinetString,c_DarwinetString> Pair;

			const_iterator find(const c_DarwinetString& sKey);
		};

		//-------------------------------------------------------------------
		class c_SignalQueue : public std::queue<c_Signal::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_SignalQueue> shared_ptr;
		};

		//-------------------------------------------------------------------
		class c_TestClient {
		public:
			typedef boost::shared_ptr<c_TestClient> shared_ptr;

			c_TestClient(const c_StackActorPath& stack_path);
			const c_StackActorPath& getStackActorPath() const;

			void performTestAction();

		private:
			friend class c_TestPeerConfiguration;
			static int m_class_state;
			c_StackActorPath m_stack_path;

			void actOnSignalFromView(c_Signal::shared_ptr pSignal);

			c_SignalQueue::shared_ptr m_pToViewSignalQueue;
			c_SignalQueue::shared_ptr getToViewSignalQueue();
		};

		//-------------------------------------------------------------------
		class c_TestView {
		public:
			typedef boost::shared_ptr<c_TestView> shared_ptr;

			c_TestView(const c_StackActorPath& stack_path);
			const c_StackActorPath& getStackActorPath() const;

		private:
			friend class c_TestPeerConfiguration;
			c_StackActorPath m_stack_path;

			int m_last_used_seq_no;
			unsigned int reserveSeqNo();
			void allocateSeqNo(unsigned int seq_no);

			void actOnSignalFromClient(c_Signal::shared_ptr pSignal);
			void actOnSignalFromDomain(c_Signal::shared_ptr pSignal);
			c_SignalQueue::shared_ptr m_pToDomainSignalQueue;
			c_SignalQueue::shared_ptr getToDomainSignalQueue();
			c_SignalQueue::shared_ptr m_pToClientSignalQueue;
			c_SignalQueue::shared_ptr getToClientSignalQueue();
		};

		//-------------------------------------------------------------------
		class c_TestDomain {
		public:
			typedef boost::shared_ptr<c_TestDomain> shared_ptr;

			c_TestDomain(const c_StackActorPath& stack_path);
			const c_StackActorPath& getStackActorPath() const;

		private:
			friend class c_TestPeerConfiguration;
			friend void test();
			c_StackActorPath m_stack_path;

			void actOnSignalFromView(c_Signal::shared_ptr pSignal);
			void actOnSignalFromNode(c_Signal::shared_ptr pSignal);
			c_SignalQueue::shared_ptr m_pToOtherNodeSignalQueue;
			c_SignalQueue::shared_ptr getToOtherNodeSignalQueue();
			c_SignalQueue::shared_ptr m_pToViewSignalQueue;
			c_SignalQueue::shared_ptr getToViewSignalQueue();
		};

		//-------------------------------------------------------------------
		class c_TestNode {
		public:
			typedef boost::shared_ptr<c_TestNode> shared_ptr;

			c_TestNode(const c_StackActorPath& stack_path);
			const c_StackActorPath& getStackActorPath() const;

		private:
			friend class c_TestPeerConfiguration;
			friend void test();
			c_StackActorPath m_stack_path;

			void actOnSignalFromOtherNode(c_Signal::shared_ptr pSignal);
			c_SignalQueue::shared_ptr m_pToDomainSignalQueue;
			c_SignalQueue::shared_ptr getToDomainSignalQueue();
		};

		//-------------------------------------------------------------------
		class c_TestPeerConfiguration {
		public:
			typedef boost::shared_ptr<c_TestPeerConfiguration> shared_ptr;

			c_TestPeerConfiguration(const c_StackActorPath& stack_path);

			void processSignals();

			c_TestClient::shared_ptr getTestClient();
			c_TestView::shared_ptr getTestView();
			c_TestDomain::shared_ptr getTestDomain();
			c_TestNode::shared_ptr getTestNode();

		private:
			friend void test();

			c_TestClient::shared_ptr m_pTestClient;
			c_TestView::shared_ptr m_pTestView;
			c_TestDomain::shared_ptr m_pTestDomain;
			c_TestNode::shared_ptr m_pTestNode;

		};
		//-------------------------------------------------------------------
		namespace log {
			c_LogString toLogString(c_Signal::shared_ptr pSignal);

			template <class _Actor>
			void logBusiness(const _Actor& actor,const c_LogString& sMessageIn) {
				c_LogString sMessage(actor.getStackActorPath().toString<typename c_LogString>());
				sMessage += _UTF8sz(": ");
				sMessage += sMessageIn;
				LOG_BUSINESS(sMessage);
			}

			template <class _Actor>
			void logDesignInsufficiency(const _Actor& actor,const c_LogString& sMessageIn) {
				c_LogString sMessage(actor.getStackActorPath().toString<c_LogString>());
				sMessage += _UTF8sz(": ");
				sMessage += sMessageIn;
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}

			template <class _Actor>
			void logTrace(const _Actor& actor,const c_LogString& sMessageIn) {
				c_LogString sMessage(actor.getStackActorPath().toString<c_LogString>());
				sMessage += _UTF8sz(": ");
				sMessage += sMessageIn;
				LOG_DEVELOPMENT_TRACE(sMessage);
			}

			template <class _Actor>
			void logInSignal(const _Actor& actor,c_Signal::shared_ptr pSignal) {
				c_LogString sMessage;
				sMessage += _UTF8sz(" Rx \"");
				sMessage += toLogString(pSignal);
				sMessage += _UTF8sz("\"");
				log::logBusiness(actor,sMessage);
			}

		}

		//-------------------------------------------------------------------
		void test();

	};

	namespace miv3 {
		// Iteration 6. Iteration 5 failed to provide a good design for the roundtrip
		// MIV += change through Evolution manager and back to another MIV.
		// The problem is naming of all the artefacts needed to make this processing clean.
		// lets see if we can improve on the design this time.

		// 131121, Consider to use JSON strings to pass deltas
		// See: http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented

		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<c_CaptionNode> c_MIVPath;

		namespace view {
			typedef c_MIVPath c_ModelPath;
			typedef c_MIVPath c_InstancePath;
			typedef c_MIVPath c_TypePath;
		}

		namespace domain {
			typedef unsigned int t_IndexNode;
			typedef oprime::c_KeyPath<t_IndexNode> c_DeltaIndex;

			class c_EvolutionManager; // Forward;
		}

		namespace core {

			class c_CoreInt {
				int m_raw_value;
			};

			class c_CoreString {
				c_DarwinetString m_raw_value;
			};

			typedef boost::variant<c_CoreInt,c_CoreString> c_CoreV;

			class c_CoreM {
			};

			class c_CoreI {
			public:
				c_CoreI(const view::c_ModelPath& ModelPath,const c_CoreV& CoreV);
			protected:
				view::c_ModelPath m_ModelPath;
				c_CoreV m_CoreV;
			};

			class c_CoreDelta {
			public:
			};

		}

		namespace client {

			class c_ClientDelta : public core::c_CoreDelta {
			public:
				c_ClientDelta(const core::c_CoreDelta& CoreDelta,const c_MIVPath& TargetMIVPath);
			protected:
				const c_MIVPath m_TargetMIVPath;
			};
		};

		namespace view {

			class c_ViewDelta : public client::c_ClientDelta {
			public:
				c_ViewDelta(const client::c_ClientDelta& ClientDelta,const domain::c_DeltaIndex& TargetDeltaIndex);
			protected:
				domain::c_DeltaIndex m_TargetDeltaIndex;
			};

			class c_ViewMIV {
			public:
				typedef boost::shared_ptr<c_ViewMIV> shared_ptr;

			protected:
				domain::c_DeltaIndex m_state_index;
			};

			class c_ViewM : public c_ViewMIV {
			public:
				typedef boost::shared_ptr<c_ViewM> shared_ptr;
				friend class c_SEPSI;

			};

			class c_SEPSI {
			public:
				typedef boost::shared_ptr<c_SEPSI> shared_ptr;

				c_SEPSI(boost::shared_ptr<domain::c_EvolutionManager> pEvolutionManager);

				void initAddM(const c_MIVPath& MIVPath,const view::c_TypePath& TypePath);

			private:
				boost::shared_ptr<domain::c_EvolutionManager> m_pEvolutionManager;

				c_ViewM::shared_ptr getViewM(const c_MIVPath& MIVPath);

			};

			class c_View {
			public:
				typedef boost::shared_ptr<c_View> shared_ptr;

				c_View(boost::shared_ptr<domain::c_EvolutionManager> pEvolutionManager);

				void initAddM(const c_MIVPath& MIVPath,const view::c_TypePath& TypePath);

			private:
				boost::shared_ptr<domain::c_EvolutionManager> m_pEvolutionManager;
				c_SEPSI::shared_ptr m_pSEPSI;
				c_SEPSI::shared_ptr getSEPSI();
			};

		}

		namespace domain {

			class c_DomainDelta : public view::c_ViewDelta {
			public:
				c_DomainDelta(const view::c_ViewDelta& ViewDelta, const domain::c_DeltaIndex& DeltaIndex);
			private:
				domain::c_DeltaIndex m_DeltaIndex;
			};

			class c_EvolutionManager {
			public:
				typedef boost::shared_ptr<c_EvolutionManager> shared_ptr;

				void addView(boost::shared_ptr<view::c_View> pView);

				void initAddM(const c_MIVPath& MIVPath,const c_DeltaIndex& target_index,const view::c_TypePath& TypePath);

				void process();

			private:
				typedef std::vector<boost::shared_ptr<view::c_View> > c_Views;
				c_Views m_Views;

			};
		}

		void test();
	}

	namespace miv2 {

		void test();

		// Iteration 5. Now adjusting the design to better accomodfate the notion
		// of delta target index and MIV instance.

		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		//-------------------------------------------------------------------

		class c_LogStringilizer; // Forward
		namespace view {
			typedef oprime::c_KeyPath<c_CaptionNode> c_MIVPath;
			class c_M; // Forward
			class c_SEPSI;
		}

		namespace delta {
			typedef unsigned int t_IndexNode;
			typedef oprime::c_KeyPath<t_IndexNode> c_DeltaIndex;

			class c_IndexFactory {
			public:
				typedef boost::shared_ptr<c_IndexFactory> shared_ptr;

				c_IndexFactory(c_DeltaIndex branch = c_DeltaIndex(),t_IndexNode seq = 0);

				c_DeltaIndex currentIndex();

				c_DeltaIndex nextIndex();
			private:
				c_DeltaIndex m_branch;
				t_IndexNode m_seq;
			};

			class c_EvolutionManager; // Forward

			enum e_dDir {
				 edDir_Undefined
				,edDir_Add
				,edDir_Remove
				,edDir_Unknown
			};

			class c_dMIVs; // Forward
			class c_dMIV {
			public:
				typedef boost::shared_ptr<c_dMIV> shared_ptr;
				friend class c_LogStringilizer;
				friend class c_dMIVs;
				friend class view::c_M;
				friend class c_EvolutionManager;

				c_dMIV(e_dDir dDir,const c_DeltaIndex& target_index,view::c_MIVPath target_miv_path,const c_DeltaIndex& index);

				// Begin c_dMIV

				virtual void applyToSEPSI(view::c_SEPSI& sepsi) = 0;

				// End c_dMIV

			protected:
				e_dDir m_dDir;
				c_DeltaIndex m_target_index;
				view::c_MIVPath m_target_miv_path;
				c_DeltaIndex m_index;
			};

			class c_dM : public c_dMIV {
			public:
				typedef boost::shared_ptr<c_dM> shared_ptr;
				friend class c_LogStringilizer;

				c_dM(e_dDir dDir,const c_DeltaIndex& target_index,const c_DeltaIndex& index,boost::shared_ptr<view::c_M> pM);

				// Begin c_dMIV

				virtual void applyToSEPSI(view::c_SEPSI& sepsi);

				// End c_dMIV

			private:
				boost::shared_ptr<view::c_M> m_pM;
			};

			class c_dI : public c_dMIV {
			public:
				typedef boost::shared_ptr<c_dI> shared_ptr;
			};

			class c_dV : public c_dMIV {
			public:
				typedef boost::shared_ptr<c_dV> shared_ptr;
			};

		};

		namespace view {
			class c_MIV {
			public:
				typedef boost::shared_ptr<c_MIV> shared_ptr;
				friend class delta::c_dM;

				c_MIV(const c_MIVPath& miv_path,const delta::c_DeltaIndex& state_index);

			protected:
				c_MIVPath m_miv_path;
				delta::c_DeltaIndex m_state_index;
			};

			class c_V : public c_MIV {
			public:
				typedef boost::shared_ptr<c_V> shared_ptr;
			private:
			};

			class c_I : public c_MIV {
			public:
				typedef boost::shared_ptr<c_I> shared_ptr;
			private:
				c_V::shared_ptr m_pV;
			};

			namespace type {
				enum e_DataType {
					 eDataType_Undefined
					,eDataType_Integer
					,eDataType_String
					,eDataType_Array
					,eDataType_Class
					,eDataType_Unknown

				};
				class c_DataType {
				public:
					typedef boost::shared_ptr<c_DataType> shared_ptr;
					friend class c_LogStringilizer;

					c_DataType(e_DataType data_type = eDataType_Undefined);
				private:
					e_DataType m_data_type;

				};
			};

			class c_M : public c_MIV {
			public:
				typedef boost::shared_ptr<c_M> shared_ptr;
				friend class c_LogStringilizer;
				friend class delta::c_dM;
				friend class c_SEPSI;

				c_M(const c_MIVPath& miv_path,const delta::c_DeltaIndex& state_index,const type::c_DataType& DataType);

			private:
				type::c_DataType m_DataType;
				typedef std::map<c_MIVPath::Node,c_I::shared_ptr> c_Is;
				c_Is m_Is;
			};

			class c_Ms : public std::map<c_MIVPath,c_M::shared_ptr> {
			public:
				typedef boost::shared_ptr<c_Ms> shared_ptr;

			};

			class c_Is : public std::map<c_MIVPath,c_I::shared_ptr> {
			public:
				typedef boost::shared_ptr<c_Is> shared_ptr;

			};

			/**
			  * Shared Evolving Privately Stored Information
			  */
			class c_SEPSI {
			public:
				typedef boost::shared_ptr<c_SEPSI> shared_ptr;
				friend class delta::c_dM;
				friend class delta::c_EvolutionManager;

				c_SEPSI(boost::shared_ptr<delta::c_EvolutionManager> pEvolutionManager);

				c_M::shared_ptr getM(const c_MIVPath& miv_path);

				void initiateMAdd(const view::c_MIVPath& miv_path,const view::c_MIVPath& type_path);
				void initiateMAdd(const c_DarwinetString& sMIVPath,const c_DarwinetString& sTypePath);

			private:
				boost::shared_ptr<delta::c_EvolutionManager> m_pEvolutionManager;

				c_Ms m_Ms;
				c_Is m_Is;

//				void operator+=(delta::c_dMIV& dMIV);
				void actOndMIV(delta::c_dMIV::shared_ptr pdMIV);

				typedef std::map<view::c_MIVPath,type::c_DataType> c_DataTypes;
				c_DataTypes m_DataTypes;

				type::c_DataType getTypeOf(const view::c_MIVPath& type_path);


			};

			class c_View {
			public:
				typedef boost::shared_ptr<c_View> shared_ptr;

				c_View(boost::shared_ptr<delta::c_EvolutionManager> pEvolutionManager);

				c_SEPSI::shared_ptr getSEPSI();

			private:
				boost::shared_ptr<delta::c_EvolutionManager> m_pEvolutionManager;
				c_SEPSI::shared_ptr m_pSEPSI;
			};

		}

		namespace delta {

			class c_dMIVs : public std::map<c_DeltaIndex,c_dMIV::shared_ptr> {
			public:
				typedef boost::shared_ptr<view::c_M> shared_ptr;

				c_dMIVs();

				bool dontExist(const delta::c_dMIV& dMIV);
			};

			class c_EvolutionManager {
			public:
				typedef boost::shared_ptr<c_EvolutionManager> shared_ptr;
				friend void seedsrc::miv2::test();

				void addView(view::c_View::shared_ptr pView);

//				void operator+=(delta::c_dMIV& dMIV);

				void initiateMAdd(e_dDir dDir,const c_DeltaIndex& target_index,boost::shared_ptr<view::c_M> pM);


			private:

				delta::c_IndexFactory m_IndexFactory;

				c_dMIVs m_dMIVs;

				typedef std::queue<delta::c_dMIV::shared_ptr> c_dMIVQueue;
				c_dMIVQueue m_dMIVQueue;
				void addToInQueue(delta::c_dMIV::shared_ptr pdMIV);
				void processInQueue();
				void processdMIV(delta::c_dMIV::shared_ptr pdMIV);

				typedef std::vector<view::c_View::shared_ptr> c_Views;
				c_Views m_Views;
			};
		}

		class c_LogStringilizer {
		public:
			static c_LogString toLogCaption(const delta::c_dMIV& dMIV);
			static c_LogString toLogCaption(const delta::c_dM& dM);
			static c_LogString toLogCaption(const view::type::c_DataType& DataType);
			static c_LogString toLogCaption(const view::c_M& M);

		};

	}

	namespace miv1 {
		// iteration 4. Now decided to use flat model object list
		// and add delta index and producer
		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;

		class c_MIVId {
		public:
			typedef boost::shared_ptr<c_MIVId> shared_ptr;

			c_MIVId(unsigned int raw_id); // TODO, Change to GUID
		private:
			unsigned int m_raw_id;
		};

		class c_UserID {
		public:
			typedef boost::shared_ptr<c_UserID> shared_ptr;

			c_UserID(unsigned int raw_id); // TODO, Change to GUID
		private:
			unsigned int m_raw_id;

		};

		class c_ModelMember {
		public:
			typedef boost::shared_ptr<c_ModelMember> shared_ptr;

			virtual ~c_ModelMember();
		};

		enum e_DataObjectModelType {
			 eDataObjectModelType_Undefined
			,eDataObjectModelType_Integer
			,eDataObjectModelType_String
			,eDataObjectModelType_Record
			,eDataObjectModelType_Array
			,eDataObjectModelType_Unknown
		};

		class c_DataObjectModelType {
		public:
			typedef boost::shared_ptr<c_DataObjectModelType> shared_ptr;

			c_DataObjectModelType(e_DataObjectModelType DataObjectModelType);
		private:
			e_DataObjectModelType m_DataObjectModelType;
		};

		class c_Cardinality {
		public:
			typedef boost::shared_ptr<c_Cardinality> shared_ptr;

			c_Cardinality(unsigned int min_no_instances,unsigned int max_no_instances);
		private:
			unsigned int m_min_no_instances;
			unsigned int m_max_no_instances;
		};

		class c_DataObjectModelInstanceConstraints {
		public:
			typedef boost::shared_ptr<c_Cardinality> shared_ptr;

			c_DataObjectModelInstanceConstraints(const c_Cardinality& cardinality = c_Cardinality(0,1));
		private:
			const c_Cardinality m_cardinality;
		};

		class c_DataObjectModel : public c_ModelMember {
		public:
			typedef boost::shared_ptr<c_DataObjectModel> shared_ptr;

			c_DataObjectModel(const c_DataObjectModelType& DataObjectModelType,const c_DataObjectModelInstanceConstraints& DataObjectModelInstanceConstraints = c_DataObjectModelInstanceConstraints());
		private:
			c_DataObjectModelType m_DataObjectModelType;
			c_DataObjectModelInstanceConstraints m_DataObjectModelInstanceConstraints;

		};

		class c_ModelMembers : public std::map<c_ModelPath,c_ModelMember::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_ModelMembers> shared_ptr;

		};

		class c_MIV; // Forward
		class c_Model; // Forward
		namespace delta {

			enum e_DeltaDirection {
				 eDeltaDirection_Undefined
				,eDeltaDirection_Add
				,eDeltaDirection_Remove
				,eDeltaDirection_Unknown
			};

			class c_Delta {
			public:
				typedef boost::shared_ptr<c_Delta> shared_ptr;

				// Begin c_Delta

				virtual void applyToMIV(c_MIV& miv) const = 0;

				// End c_Delta
			};

			class c_ModelDelta : public c_Delta {
			public:
				typedef boost::shared_ptr<c_ModelDelta> shared_ptr;

				c_ModelDelta(e_DeltaDirection DeltaDirection,const c_ModelPath& target_path);

				// Begin c_Delta

				virtual void applyToMIV(c_MIV& miv) const;

				// End c_Delta

				// Begin c_ModelDelta

				virtual void applyToModel(c_Model& model) const = 0;

				// End c_ModelDelta

			protected:
				e_DeltaDirection m_DeltaDirection;
				c_ModelPath m_target_path;
			};

			class c_DataObjectModelInstanceDelta : public c_ModelDelta {
			public:
				typedef boost::shared_ptr<c_DataObjectModelInstanceDelta> shared_ptr;

				c_DataObjectModelInstanceDelta(e_DeltaDirection DeltaDirection,const c_ModelPath& member_path,c_ModelMember::shared_ptr pMember);

				// Begin c_ModelDelta

				virtual void applyToModel(c_Model& model) const;

				// End c_ModelDelta

			private:
				c_ModelPath::Node m_member_name;
				c_ModelMember::shared_ptr m_pMember;
			};

			class c_InstanceDelta : public c_Delta {
			public:
				typedef boost::shared_ptr<c_InstanceDelta> shared_ptr;
			};

			class c_ValueDelta : public c_Delta {
			public:
				typedef boost::shared_ptr<c_InstanceDelta> shared_ptr;
			};

		}

		class c_Model {
		public:
			typedef boost::shared_ptr<c_Model> shared_ptr;
			friend class delta::c_DataObjectModelInstanceDelta;
			c_Model();

			void operator+=(const delta::c_ModelDelta& ModelDelta);

		private:
			c_ModelMembers m_ModelMembers;
		};

		class c_MIV {
		public:
			typedef boost::shared_ptr<c_MIV> shared_ptr;
			friend class delta::c_ModelDelta;

			void operator+=(const delta::c_Delta& Delta);

		private:
			c_Model m_Model;
		};

		namespace delta {
			class c_DeltaSignalSource {
			public:
				typedef boost::shared_ptr<c_DeltaSignalSource> shared_ptr;

				c_DeltaSignalSource(const c_MIVId& MIV_Id = c_MIVId(0),const c_UserID& User_Id = c_UserID(0));

			private:
				c_MIVId m_MIV_Id;
				c_UserID m_User_Id;
			};

			typedef oprime::c_KeyPath<unsigned int> c_DeltaIndex;

			class c_MIVController; // Forward

			class c_DeltaSignal {
			public:
				typedef boost::shared_ptr<c_DeltaSignal> shared_ptr;
				friend class c_MIVController;

				c_DeltaSignal(const c_DeltaSignalSource& source,const c_DeltaIndex& target_index,c_Delta::shared_ptr pDelta);

				virtual void applyToMIV(c_MIV& miv) const;

			private:
				c_DeltaSignalSource m_source;
				c_DeltaIndex m_target_index;
				c_Delta::shared_ptr m_pDelta;
			};

			class c_DeltaSignals : public std::list<c_DeltaSignal::shared_ptr> {
			public:
				typedef boost::shared_ptr<c_DeltaSignals> shared_ptr;

			};

			class c_DeltaSignalFactory {
			public:
				typedef boost::shared_ptr<c_DeltaSignalFactory> shared_ptr;

				c_DeltaSignalFactory(const c_DeltaSignalSource& DeltaSignalSource = c_DeltaSignalSource());

				c_DeltaSignal::shared_ptr createDeltaSignal(c_Delta::shared_ptr pDelta);

			private:
				c_DeltaSignalSource m_DeltaSignalSource;
				c_DeltaIndex m_current_delta_index;

			};

			class c_MIVController {
			public:
				typedef boost::shared_ptr<c_MIVController> shared_ptr;

				c_MIVController(c_MIV::shared_ptr pMIV);

				void operator+=(const c_DeltaSignal& DeltaSignal);

			private:
				delta::c_DeltaIndex m_current_delta_index;
				c_MIV::shared_ptr m_pMIV;
			};

			class c_DeltaManager {
			public:
				typedef boost::shared_ptr<c_DeltaManager> shared_ptr;

				void addMIV(c_MIV::shared_ptr pMIV);

				void operator+=(const c_DeltaSignal& DeltaSignal);

			private:
				typedef std::list<c_MIVController::shared_ptr> c_MIVControllers;
				c_MIVControllers m_MIVControllers;

			};

		}

		/**
		  * Dummy to access our c_DeltaSignalSource unti proper impl. is in place
		  */
		const delta::c_DeltaSignalSource& getDeltaSource();

		void test();

	}

	namespace integrate3 {

		// The namespace integrate2 failed short in defining a recursive data model.
		// Here we will try for a data model using ascociations.

		//-------------------------------------------------------------------
		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;
		//-------------------------------------------------------------------
		typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;

		class c_Association {
		public:
			typedef boost::shared_ptr<c_Association> shared_ptr;

		};

		class c_Aggregation : public c_Association {
		public:
			typedef boost::shared_ptr<c_Aggregation> shared_ptr;
			typedef boost::shared_ptr<const c_Aggregation> shared_ptr_const;

			c_Aggregation(c_ModelPath::shared_ptr_const pModelPath);

		private:
			c_ModelPath::shared_ptr_const m_pModelPath;
		};

		class c_AssociationList : public std::map<c_ModelPath::Node,c_Association::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_AssociationList> shared_ptr;
			typedef boost::weak_ptr<c_AssociationList> weak_ptr;
		};

		class c_AssociationLists : public std::map<c_ModelPath,c_AssociationList::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_AssociationLists> shared_ptr;
		};

		class c_MIV; // Forward
		namespace delta {

			class c_Delta {
			public:
				typedef boost::shared_ptr<c_Delta> shared_ptr;

				virtual void applyTo(c_MIV& miv) const = 0;

			};

			class c_DeltaM : public c_Delta {
			public:
				typedef boost::shared_ptr<c_DeltaM> shared_ptr;

				c_DeltaM(c_ModelPath::shared_ptr pTargetPath);

			protected:
				c_ModelPath::shared_ptr m_pTargetPath;
			};

			class c_DeltaAggregation : public c_DeltaM {
			public:
				typedef boost::shared_ptr<c_DeltaAggregation> shared_ptr;

				c_DeltaAggregation(c_ModelPath::shared_ptr pTargetPath,c_ModelPath::Node id,c_Aggregation::shared_ptr_const pAggregation);

				virtual void applyTo(c_MIV& miv) const;
			private:
				c_ModelPath::Node m_id;
				c_Aggregation::shared_ptr_const m_pAggregation;
			};

			class c_Deltas : public std::list<c_Delta::shared_ptr> {
			public:
				typedef boost::shared_ptr<c_Deltas> shared_ptr;

			};

			class c_DeltaFactory {
			public:
				typedef boost::shared_ptr<c_DeltaFactory> shared_ptr;

				c_Delta::shared_ptr createDeltaAggregation(const std::string& sMemberPath,const std::string& sModelPath);
			};

		}

		class c_MIV {
		public:
			typedef boost::shared_ptr<c_MIV> shared_ptr;
			friend class delta::c_DeltaAggregation;

			c_MIV();

			void operator+=(const delta::c_Delta& delta);

		private:
			c_AssociationLists::shared_ptr m_pAssociationLists;

			c_AssociationList::weak_ptr getAssociationList(c_ModelPath::shared_ptr_const pTargetPath);

		};

		void test();
	}

	namespace integrate2 {
		// The namespace integrate failed short on a number of requirements.
		// Lets start over again

		typedef c_DataRepresentationFramework::c_UTF8String c_DarwinetString;
		typedef c_DarwinetString c_CaptionNode;

		enum e_Type {
			eType_Undefined
			,eType_Int
			,eType_String
			,eType_Record
			,eType_Array
			,eType_Unknown

		};

		typedef oprime::c_KeyPath<c_CaptionNode> c_ModelPath;

		class c_Model {
		public:
			typedef boost::shared_ptr<c_Model> shared_ptr;

			c_Model(e_Type type);

			e_Type type();
		private:
			e_Type m_type;
		};

		class c_MIV; // Forward
		namespace delta {

			class c_Delta {
			public:
				typedef boost::shared_ptr<c_Delta> shared_ptr;

				// Begin c_Delta

				virtual void applyTo(c_MIV& miv) const = 0;

				// End c_Delta

			private:

			};

			class c_DeltaM : public c_Delta {
			public:
				typedef boost::shared_ptr<c_DeltaM> shared_ptr;

				c_DeltaM(const c_ModelPath& target_path);

			protected:
				const c_ModelPath m_target_path;

			};

			class c_AddModel : public c_DeltaM {
			public:
				typedef boost::shared_ptr<c_AddModel> shared_ptr;

				c_AddModel(const c_ModelPath& model_path,const c_Model& model);

				// Begin c_Delta

				virtual void applyTo(c_MIV& miv) const;

				// End c_Delta

			private:
				const c_ModelPath::Node m_memberId;
				const c_Model m_model;
			};

			class c_Deltas : public std::vector<c_Delta::shared_ptr> {
			public:
				typedef boost::shared_ptr<c_Deltas> shared_ptr;

			};
		}

		class c_Models : public std::map<c_ModelPath,c_Model::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_Models> shared_ptr;

		};

		namespace delta {
			class c_IntAdd; // forward
		}

		const INT_INIT_VALUE = 0;
		class c_IntValue {
		public:
			typedef boost::shared_ptr<c_IntValue> shared_ptr;

			c_IntValue();

			void applyDeltaV(const delta::c_IntAdd& delta);

			int raw_value();

		private:
			int m_raw_value;
		};

		class c_StringValue {
		};

		class c_RecordValue {
		};

		class c_ArrayValue {
		};

		typedef boost::variant<c_IntValue,c_StringValue,c_RecordValue, c_ArrayValue> c_VariantValue;
		typedef boost::shared_ptr<c_VariantValue> c_VariantValuePtr;

		typedef oprime::c_KeyPath<c_CaptionNode> c_InstancePath;

		class c_Object {
		public:
			typedef boost::shared_ptr<c_Object> shared_ptr;
			friend class delta::c_IntAdd;

			c_Object(e_Type type,const c_ModelPath& model_path = c_ModelPath());

			const c_ModelPath& getModelPath();

		private:
			const c_ModelPath m_model_path;
			const e_Type m_type;
			c_VariantValuePtr m_pVariantValue;

			c_VariantValuePtr getVariantValue();
		};

		namespace delta {

			class c_DeltaIV : public c_Delta {
			public:
				typedef boost::shared_ptr<c_DeltaIV> shared_ptr;

				c_DeltaIV(const c_InstancePath& target_path);

			protected:
				const c_InstancePath m_target_path;

			};

			class c_DeltaI : public c_DeltaIV {
			public:
				typedef boost::shared_ptr<c_DeltaIV> shared_ptr;

				c_DeltaI(const c_InstancePath& target_path);
			};

			class c_CreateInstance : public c_DeltaI {
			public:
				typedef boost::shared_ptr<c_CreateInstance> shared_ptr;

				c_CreateInstance(const c_InstancePath& instance_path);

				// Begin c_Delta

				virtual void applyTo(c_MIV& miv) const;

				// End c_Delta
			private:
				c_InstancePath::Node m_memberId;

			};

			class c_DeltaV : public c_DeltaIV {
			public:
				typedef boost::shared_ptr<c_DeltaV> shared_ptr;

				c_DeltaV(const c_InstancePath& target_path);

			};

			class c_IntAdd : public c_DeltaV {
			public:
				typedef boost::shared_ptr<c_IntAdd> shared_ptr;
				friend class c_IntValue;

				c_IntAdd(const c_InstancePath& target_path,int raw_delta);

				// Begin c_Delta

				virtual void applyTo(c_MIV& miv) const;

				// End c_Delta

			private:
				int m_raw_delta;
			};

		}

		class c_Objects : public std::map<c_InstancePath,c_Object::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_Objects> shared_ptr;
		};

		class c_MIV {
		public:
			typedef boost::shared_ptr<c_MIV> shared_ptr;
			friend class delta::c_AddModel;
			friend class delta::c_CreateInstance;
			friend class delta::c_IntAdd;

			c_MIV();

			void operator+=(const delta::c_Delta& delta);

		private:

			c_Models m_models;
			c_Objects m_objects;
		};
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		void test();

	}

	namespace integrate {

		class c_MIV; // Forward
		//-------------------------------------------------------------------
		class c_Delta {
		public:
			typedef boost::shared_ptr<c_Delta> shared_ptr;

			// Begin c_Delta

			/**
			  * Apply "us" to provided c_MIV
			  */
			virtual void applyTo(c_MIV& miv) const = 0;

			// End c_Delta

		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		class c_ModelDelta : public c_Delta {
		public:
			typedef boost::shared_ptr<c_ModelDelta> shared_ptr;

		};

		//-------------------------------------------------------------------
		class c_InstanceDelta : public c_Delta {
		public:
			typedef boost::shared_ptr<c_InstanceDelta> shared_ptr;

		};

		class c_CreateIntInstanceDelta : public c_InstanceDelta {
		public:
			typedef boost::shared_ptr<c_CreateIntInstanceDelta> shared_ptr;

			/**
			  * Create a delta reporting creation of a new object instance
			  * with provided darwinet::c_InstancePath and of type defined
			  * by provided darwinet::c_ModelPath
			  */
			c_CreateIntInstanceDelta(const darwinet::c_InstancePath& InstancePath,const darwinet::c_ModelPath& ModelPath);

			// Begin c_Delta

			/**
			  * Apply "us" to provided c_MIV
			  */
			virtual void applyTo(c_MIV& miv) const;

			// End c_Delta

			const darwinet::c_InstancePath& getInstancePath() const;

		private:

			darwinet::c_InstancePath m_InstancePath;
			darwinet::c_ModelPath m_ModelPath;

			const darwinet::c_InstancePath getTargetInstancePath() const;

		};

		//-------------------------------------------------------------------
		class c_ValueDelta : public c_Delta {
		public:
			typedef boost::shared_ptr<c_ValueDelta> shared_ptr;

			c_ValueDelta();

			const darwinet::c_InstancePath& getTargetInstancePath() const;

		private:
			/**
			  * Private storage of shared reference to instance
			  */
			darwinet::c_InstancePath::shared_ptr m_pInstancePath;
		};
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		class c_IntValueDelta : public c_ValueDelta {
		public:
			typedef boost::shared_ptr<c_IntValueDelta> shared_ptr;

			/**
			  * Creates a c_IntValueDelta from provided raw delta value
			  */
			c_IntValueDelta(int raw_delta);

			// Begin c_Delta

			/**
			  * Apply "us" to provided c_MIV
			  */
			void applyTo(c_MIV& miv) const;

			/**
			  * Apply us to raw value
			  */
			void applyTo(int& raw_value) const;

			// End c_Delta

		private:
			int m_raw_delta;
		};

		//-------------------------------------------------------------------
		class c_StringValueDelta : public c_ValueDelta {
		public:
			typedef boost::shared_ptr<c_IntValueDelta> shared_ptr;

		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		class c_ObjectInstance; // Forward
		class c_IntObjectInstance; // forward
		class c_StringObjectInstance; // forward
		typedef boost::variant<c_IntObjectInstance,c_StringObjectInstance> c_VariantObjectInstance;
		typedef boost::shared_ptr<c_VariantObjectInstance> c_VariantObjectInstancePtr;

		class c_VariantObjectInstancesMap : public std::map<darwinet::c_InstancePath,c_VariantObjectInstancePtr> {
		public:
			typedef boost::shared_ptr<c_VariantObjectInstancesMap> shared_ptr;

		};
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		class c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_ObjectInstance> shared_ptr;

			c_ObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap);

			void operator+=(const c_CreateIntInstanceDelta& delta);

		protected:

			c_VariantObjectInstancesMap::shared_ptr getInstanceMap();

		private:

			c_VariantObjectInstancesMap::shared_ptr m_pVariantObjectInstancesMap;

		};

		//-------------------------------------------------------------------
		const DEFAULT_INT_OBJECT_VALUE = 0;
		class c_IntObjectInstance : public c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_IntObjectInstance> shared_ptr;

			c_IntObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap = c_VariantObjectInstancesMap::shared_ptr(),int raw_value = DEFAULT_INT_OBJECT_VALUE);

			void operator+=(const c_IntValueDelta& delta);

		private:

			int m_raw_value;

		};

		//-------------------------------------------------------------------
		const darwinet::c_DarwinetString DEFAULT_STRING_OBJECT_VALUE = _UTF8sz("");
		class c_StringObjectInstance : public c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_StringObjectInstance> shared_ptr;

			c_StringObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap = c_VariantObjectInstancesMap::shared_ptr(),darwinet::c_DarwinetString raw_value = DEFAULT_STRING_OBJECT_VALUE);

		private:
			darwinet::c_DarwinetString m_raw_value;
		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		class c_MIV {
		public:
			typedef boost::shared_ptr<c_MIV> shared_ptr;

			c_MIV();

			// Begin c_MIV

			/**
			  * Applies provided delta to us, updating our state
			  * as defined by the delta.
			  */
			void operator+=(const c_Delta& delta);

			c_VariantObjectInstancePtr getInstance(const darwinet::c_InstancePath& InstancePath);

			// End c_MIV

		private:

			c_VariantObjectInstancesMap::shared_ptr m_pVariantValuesMap;

			/**
			  * Create a new instance of type defined by provided darwinet::c_ModelPath
			  */
			c_VariantObjectInstancePtr createInstance(const darwinet::c_ModelPath& ModelPath);

		};

		//-------------------------------------------------------------------
		class c_MIVEvolutionHistory : public std::vector<c_Delta::shared_ptr> {
		public:
			typedef boost::shared_ptr<c_MIVEvolutionHistory> shared_ptr;

		};

		//-------------------------------------------------------------------
		class c_Integrator {
		public:
			typedef boost::shared_ptr<c_Integrator> shared_ptr;

			/**
			  * Creates a MIV instance with the state defined by provided
			  * c_MIVEvolutionHistory instance.
			  */
			c_MIV::shared_ptr integrate(c_MIVEvolutionHistory::shared_ptr pEvolutionHistory);

		};

		/**
		  * Test this module
		  */
		void test();
	}

}

/**
  * Tie the GUI with the current iteration code
  */
namespace darwinet_seed = seedsrc::miv5;

#endif
