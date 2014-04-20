//---------------------------------------------------------------------------

#pragma hdrstop

#include "SEPSISeed.h"
#include "BusinessLogUnit.h"
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/format.hpp>
# pragma warn +8072 // Enable again. See above
#include <algorithm> // std::find_if
#include <boost/algorithm/string.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)


/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */
namespace seedsrc {

	namespace miv5 {

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_SignalFieldMapper::c_SignalFieldMapper()
		{
			// Fill the map
			for (int i = eSignalField_Undefined+1; i < eSignalField_Unknown; ++i) {
				c_DarwinetString sSignalFieldIdString;
				e_SignalField eField = static_cast<e_SignalField>(i);
				switch (eField) {
					case eSignalField_Undefined: sSignalFieldIdString = _UTF8sz("Undefined"); break;
					case eSignalField_SignalSender: sSignalFieldIdString = _UTF8sz("head.Sender"); break;
					case eSignalField_SignalReceiver: sSignalFieldIdString = _UTF8sz("head.Receiver"); break;
					case eSignalField_SignalIdentifier: sSignalFieldIdString = _UTF8sz("Head.SignalId"); break;
					case eSignalField_MIVsOperationId: sSignalFieldIdString = _UTF8sz("Body.MIVsOperation.Id"); break;
					case eSignalField_MIVsOperationTargetId: sSignalFieldIdString = _UTF8sz("Body.MIVsOperation.Target"); break;
					case eSignalField_MIVsOperationNewValue: sSignalFieldIdString = _UTF8sz("Body.MIVsOperation.NewValue"); break;
					case eSignalField_MIVsEventId: sSignalFieldIdString = _UTF8sz("Body.MIVsEvent.Id"); break;
					case eSignalField_MIVsEventSourceId: sSignalFieldIdString = _UTF8sz("Body.MIVsEvent.Source"); break;
					case eSignalField_MIVsEventValue: sSignalFieldIdString = _UTF8sz("Body.MIVsEvent.Value"); break;
					case eSignalField_DeltaPredecessorIx: sSignalFieldIdString = _UTF8sz("Body.Delta.PredecessorIndex"); break;
					case eSignalField_DeltaIx: sSignalFieldIdString = _UTF8sz("Body.Delta.Index"); break;
					case eSignalField_DeltaTargetState: sSignalFieldIdString = _UTF8sz("Body.Delta.Target.State"); break;
					case eSignalField_DeltaTargetMIVId: sSignalFieldIdString = _UTF8sz("Body.Delta.Target.MIVId"); break;
					case eSignalField_DeltaOperationId: sSignalFieldIdString = _UTF8sz("Body.Delta.Operation.Id"); break;
					case eSignalField_DeltaOperationValue: sSignalFieldIdString = _UTF8sz("Body.Delta.Operation.Value"); break;
					case eSignalField_Unknown: break;
				default:
					;
				}
				(*this)[eField] = sSignalFieldIdString;
			}
		}

		c_DarwinetString& c_SignalFieldMapper::operator[](e_SignalField eKey) {
			if (_Base::operator [](eKey).length() == 0) {
				c_DarwinetString sName("??");
				sName += c_DataRepresentationFramework::intToDecimalString(eKey);
				sName += _UTF8sz("??");
				_Base::operator [](eKey) = sName;
			}
			return _Base::operator [](eKey);
		}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_SignalIdentifierMapper::c_SignalIdentifierMapper()
		{
			// Fill the map
			for (int i = eSignalIdentifier_Undefined+1; i < eSignalIdentifier_Unknown; ++i) {
				c_DarwinetString sSignalIdentifier;
				e_SignalIdentifier eField = static_cast<e_SignalIdentifier>(i);
				switch (eField) {
					case eSignalIdentifier_Undefined: sSignalIdentifier = _UTF8sz("Undefined"); break;
					case eSignalIdentifier_getMIVs: sSignalIdentifier = _UTF8sz("getMIVs"); break;
					case eSignalIdentifier_getMIVsResponse: sSignalIdentifier = _UTF8sz("getMIVsResponse"); break;
					case eSignalIdentifier_ModifyMIVRequest: sSignalIdentifier = _UTF8sz("ModifyMIVRequest"); break;
					case eSignalIdentifier_OnMIVEvent: sSignalIdentifier = _UTF8sz("OnMIVEvent"); break;
					case eSignalIdentifier_DeltaMIV: sSignalIdentifier = _UTF8sz("DeltaMIV"); break;

					case eSignalIdentifier_Unknown: sSignalIdentifier = _UTF8sz("Unknown"); break;
				default:
					;
				}
				(*this)[eField] = sSignalIdentifier;
			}
		}

		c_DarwinetString& c_SignalIdentifierMapper::operator[](e_SignalIdentifier eKey) {
			if (_Base::operator [](eKey).length() == 0) {
				c_DarwinetString sName("??");
				sName += c_DataRepresentationFramework::intToDecimalString(eKey);
				sName += _UTF8sz("??");
				_Base::operator [](eKey) = sName;
			}
			return _Base::operator [](eKey);
		}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_MIVsOperationMapper::c_MIVsOperationMapper()
		{
			// Fill the map
			for (int i = eMIVsOperation_Undefined+1; i < eMIVsOperation_Unknown; ++i) {
				c_DarwinetString sValue;
				e_MIVsOperation eKey = static_cast<e_MIVsOperation>(i);
				switch (eKey) {
					case eMIVsOperation_Undefined: sValue = _UTF8sz("Undefined"); break;
					case eMIVsOperation_Assign: sValue = _UTF8sz("Assign"); break;
					case eMIVsOperation_Unknown: sValue = _UTF8sz("Unknown"); break;
				default:
					;
				}
				(*this)[eKey] = sValue;
			}
		}

		c_DarwinetString& c_MIVsOperationMapper::operator[](e_MIVsOperation eKey) {
			if (_Base::operator [](eKey).length() == 0) {
				c_DarwinetString sName("??");
				sName += c_DataRepresentationFramework::intToDecimalString(eKey);
				sName += _UTF8sz("??");
				_Base::operator [](eKey) = sName;
			}
			return _Base::operator [](eKey);
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_MIVsEventIdMapper::c_MIVsEventIdMapper()
		{
			// Fill the map
			for (int i = eMIVsEventId_Undefined+1; i < eMIVsEventId_Unknown; ++i) {
				c_DarwinetString sValue;
				e_MIVsEventId eKey = static_cast<e_MIVsEventId>(i);
				switch (eKey) {
					case eMIVsEventId_Undefined: sValue = _UTF8sz("Undefined"); break;
					case eMIVsEventId_OnMIVValueChanged: sValue = _UTF8sz("OnMIVValueChanged"); break;
					case eMIVsEventId_Unknown: sValue = _UTF8sz("Unknown"); break;
				default:
					;
				}
				(*this)[eKey] = sValue;
			}
		}

		c_DarwinetString& c_MIVsEventIdMapper::operator[](e_MIVsEventId eKey) {
			if (_Base::operator [](eKey).length() == 0) {
				c_DarwinetString sName("??");
				sName += c_DataRepresentationFramework::intToDecimalString(eKey);
				sName += _UTF8sz("??");
				_Base::operator [](eKey) = sName;
			}
			return _Base::operator [](eKey);
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_DeltaOperationIdMapper::c_DeltaOperationIdMapper()
		{
			// Fill the map
			for (int i = eDeltaOperationId_Undefined+1; i < eDeltaOperationId_Unknown; ++i) {
				c_DarwinetString sValue;
				e_DeltaOperationId eKey = static_cast<e_DeltaOperationId>(i);
				switch (eKey) {
					case eDeltaOperationId_Undefined: sValue = _UTF8sz("Undefined"); break;
					case eDeltaOperationId_IntDeltaAdd: sValue = _UTF8sz("IntDeltaAdd"); break;
					case eDeltaOperationId_Unknown: sValue = _UTF8sz("Unknown"); break;
				default:
					;
				}
				(*this)[eKey] = sValue;
			}
		}

		c_DarwinetString& c_DeltaOperationIdMapper::operator[](e_DeltaOperationId eKey) {
			if (_Base::operator [](eKey).length() == 0) {
				c_DarwinetString sName("??");
				sName += c_DataRepresentationFramework::intToDecimalString(eKey);
				sName += _UTF8sz("??");
				_Base::operator [](eKey) = sName;
			}
			return _Base::operator [](eKey);
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		struct is_parameter_key {
			is_parameter_key(const c_DarwinetString& sKey)
				: m_sKey(sKey)
			{
			};

			bool operator()(const c_Signal::Pair& pair) {
				return (pair.first == m_sKey);
			};

			c_DarwinetString m_sKey;

		};

		c_Signal::const_iterator c_Signal::find(const c_DarwinetString& sKey) {
			c_Signal::const_iterator result = std::find_if(this->begin(),this->end(),is_parameter_key(sKey));
			return result;
		}

		c_DarwinetString c_Signal::getValue(c_DarwinetString sKey) {
			c_DarwinetString result = c_DarwinetString("??") + sKey + c_DarwinetString("??");
			c_Signal::const_iterator iter = this->find(sKey);
			if (iter != this->end()) {
				result = iter->second;
			}
			return result;
		}

		void c_Signal::addElement(e_SignalField eKey,const c_DarwinetString& sValue) {
			this->push_back(std::make_pair(SIGNAL_FIELD_MAPPER[eKey],sValue));
		}

		c_MessageTargetId c_Signal::getTargetId() {
			c_MessageTargetId result(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("??Signal Target??")));
			c_Signal::const_iterator iter = this->find(SIGNAL_FIELD_MAPPER[eSignalField_SignalReceiver]);
			if (iter != this->end()) {
				result = c_MessageTargetId::fromString(iter->second);
			}
			return result;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		void c_SignalQueue::append(c_SignalQueue::shared_ptr pQueue) {
			if (pQueue) {
				while (pQueue->size() > 0) {
					this->push(pQueue->front());
					pQueue->pop();
				}
			}
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		void c_Messenger::send(c_Signal::shared_ptr pSignal) {
			if (pSignal) {
				this->m_SignalQueue.push(pSignal);
				log::logSignalSend(pSignal);
			}
		}

		void c_Messenger::send(c_SignalQueue::shared_ptr pSignals) {
			if (pSignals) {
				while (pSignals->size() > 0) {
					c_Signal::shared_ptr pSignal = pSignals->front();
					pSignals->pop();
					this->send(pSignal);
				}
			}
		}

		void c_Messenger::connect(c_SignalSinkIfc::weak_ptr pSignalSink) {
			c_SignalSinkIfc::shared_ptr pLockedSignalSink = pSignalSink.lock();
			if (pLockedSignalSink) {
				if (!m_SignalSinks[pLockedSignalSink->getId()].lock()) {
					m_SignalSinks[pLockedSignalSink->getId()] = pSignalSink;
				}
				else {
					// A target with the same ID already exists
					c_LogString sMessage("Failed to connect Target=");
					sMessage += pLockedSignalSink->getId().toString<c_LogString>();
					sMessage += _UTF8sz(". Target with the same ID already exists. Target discarded.");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}
			else {
				c_LogString sMessage("Failed to connect NULL target");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			};
		}

		void c_Messenger::process() {
			try {
				if (this->m_SignalQueue.size() > 0) {
					c_Signal::shared_ptr pSignal(this->m_SignalQueue.front());
					this->m_SignalQueue.pop();
					c_SignalSinkIfc::shared_ptr pSignalSink = m_SignalSinks[pSignal->getTargetId()].lock();
					if (pSignalSink) {
						{
							c_LogString sMessage("Sinkning signal={");
							sMessage += log::toLogString(pSignal);
							sMessage += _UTF8sz("}");
							LOG_BUSINESS(sMessage);
						}
						this->send(pSignalSink->actOnSignal(pSignal));
					}
					else {
						c_LogString sMessage("Failed to send signal={");
						sMessage += log::toLogString(pSignal);
						sMessage += _UTF8sz("}. Receiver does not exist.");
						LOG_DESIGN_INSUFFICIENCY(sMessage);
					};
				}
			}
			CATCH_AND_LOG_IDE_STD_AND_GENERAL_EXCEPTION_DESIGN_INSUFFICIENCY;
		}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_DarwinetString toString(const c_Signal& signal) {
			c_DarwinetString result;
			for (c_Signal::const_iterator iter = signal.begin(); iter != signal.end(); ++iter) {
				if (result.size() > 0) {
//					result += _UTF8sz("\n"); // Separate fields
					result += _UTF8sz(";"); // Separate fields
				}
				result += iter->first;
				result += _UTF8sz("=");
				result += iter->second;
			}
			return result;
		}

		c_Signal createSignalFromString(const c_DarwinetString& sSignal) {
			c_Signal result;
			std::vector<c_DarwinetString> value_pairs;
			boost::split(value_pairs,sSignal,boost::is_any_of(";\n"));
			for (std::vector<c_DarwinetString>::const_iterator iter = value_pairs.begin(); iter != value_pairs.end(); ++iter) {
				std::vector<c_DarwinetString> value_pair;
				boost::split(value_pair,*iter,boost::is_any_of("="));
				if (value_pair.size() == 2) {
					result.push_back(std::make_pair(value_pair[0],value_pair[1]));
				}
				else {
					// Wrong format
					c_LogString sMessage("Failed to create Signal from string=\"");
					sMessage += _UTF8sz("\". Wrong format found in value pair string = \"");
					sMessage += *iter;
					sMessage += _UTF8sz("\"");
					throw c_IllformedSignalStringException(sMessage);
				}
			}
			return result;
		}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_IntDeltaOperation::c_IntDeltaOperation(const c_IntValue& delta_value,e_IntOperationId int_operation_id)
			:  m_delta_value(delta_value)
			  ,m_int_operation_id(int_operation_id)
		{
			LOG_METHOD_SCOPE;
		}

		c_IntValue c_IntDeltaOperation::operator()(c_IntValue& current_value) const {
			c_IntValue result(current_value);
			switch (this->getIntOperationId()) {
				case eIntOperationId_ADD: {
					result.setRawValue(current_value.getRawValue() + m_delta_value.getRawValue());
				}
				break;
				default: {
					throw c_UnknownDeltaOperation(c_LogString("c_IntDeltaOperation is not eIntOperationId_ADD"));
				}
			}
			return result;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_DeltaIndex c_Delta::getPredecessor() const {return m_Predecessor;}
		c_MIVTarget c_Delta::getMIVtarget() const { return m_Target;}
		c_DeltaIndex c_Delta::getIndex() const { return m_Index;}
		c_DeltaOperation_shared_ptr c_Delta::getDeltaOperation() const {return m_pDeltaOperation;}

		void c_Delta::setPredecessor(const c_DeltaIndex& predecessor) {m_Predecessor = predecessor;}
		void c_Delta::setMIVtarget(const c_MIVTarget& target) { m_Target = target;}
		void c_Delta::setIndex(const c_DeltaIndex& index) { m_Index = index;}
		void c_Delta::setDeltaOperation(const c_DeltaOperation_shared_ptr& pDeltaOperation) {m_pDeltaOperation = pDeltaOperation;}
		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		class c_CreateSetValueDeltaOperation : public boost::static_visitor<c_DeltaOperation> {
		public:

			c_CreateSetValueDeltaOperation(c_Value_shared_ptr pNewValue) : m_pNewValue(pNewValue) {};

			c_DeltaOperation operator()(c_IntValue& current_value) const {
				LOG_METHOD_SCOPE;
				int integer_delta = boost::get<c_IntValue>(*m_pNewValue).getRawValue() - current_value.getRawValue();
				return c_IntDeltaOperation(c_IntValue(integer_delta),eIntOperationId_ADD);
			}

			c_DeltaOperation operator()(const c_StringValue& current_value) const {
				LOG_METHOD_SCOPE;
				c_StringDeltaOperation result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}

			c_DeltaOperation operator()(const c_RecordValue& current_value) const {
				LOG_METHOD_SCOPE;
				c_RecordDeltaOperation result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}

			c_DeltaOperation operator()(const c_ArrayValue& current_value) const {
				LOG_METHOD_SCOPE;
				c_ArrayDeltaOperation result;
				LOG_NOT_IMPLEMENTED;
				return result;
			}
		private:
			c_Value_shared_ptr m_pNewValue;
		};


		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_Delta::shared_ptr c_MIVs::createSetValueDelta(c_MIVPath id,c_Value_shared_ptr pNewValue) {
			LOG_METHOD_SCOPE;
			c_Delta::shared_ptr result(new c_Delta());
			c_MIV::shared_ptr pMIV = this->getMIV(id);
			if (pMIV) {
				// It's there
				c_MIVTarget miv_target;
				miv_target.setState(pMIV->getState());
				miv_target.setMIVId(id);
				result->setMIVtarget(miv_target);
				{
					c_DeltaIndex new_delta_index = this->m_LastCreatedDeltaIndex;
					LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(", m_LastCreatedDeltaIndex not incremented for new Delta. All created delta will have the same predecessor"));
// Dont yet work. Created Signal Field value will be a path with the first node being a path (Producer = c_MIVPath). This is not parseable by receiver.
//					result->setIndex(new_delta_index);
					this->m_LastCreatedDeltaIndex = new_delta_index;
				}
				result->setPredecessor(this->m_LastAppliedDeltaIndex);
				c_CreateSetValueDeltaOperation visitor(pNewValue);
				{
					LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(", Will Asume provided MIV is a V"));
					// Asume provided id leads to a V
					c_V current_V = boost::get<c_V>(*pMIV->getBody());
					c_Value current_value = current_V.getValue();
					c_DeltaOperation_shared_ptr pDeltaOperation = boost::make_shared<c_DeltaOperation>(boost::apply_visitor(visitor,current_value));
					result->setDeltaOperation(pDeltaOperation);
				}
			}
			else {
				throw c_NoSuchMIVException(METHOD_NAME + c_LogString(" failed. No MIV found for id=") + id.toString<c_LogString>());
			}
			return result;
		}


		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_MIV::shared_ptr c_MIVs::getMIV(const c_MIVPath& miv_path) {
			c_MIV::shared_ptr result;
			c_MappedMIVs::iterator iter_MIV = this->m_MappedMIVs.find(miv_path);
			if (iter_MIV != m_MappedMIVs.end()) {
				result = iter_MIV->second;
			}
			else {
				// No such instance
				bool auto_create_unexisting_instance = true;
				if (auto_create_unexisting_instance) {
					c_LogString sMessage("MIV Instance ");
					sMessage += miv_path.toString<c_LogString>();
					sMessage += _UTF8sz(" does not exist.");
					sMessage += _UTF8sz(" Will auto-create it. Please remove when dM processing is in place!");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
					// Create a new V instance

					{
						LOG_DESIGN_INSUFFICIENCY(c_LogString("Auo-created MIV ") + miv_path.toString<c_LogString>() + c_LogString(" will be set to integer V = 0. Auto-creation of M or I not yet implemented."));
					}
					c_MIV::shared_ptr pNewMIV = boost::make_shared<c_MIV>();
					c_V new_V;
					c_IntValue int_value(0);
					new_V.setValue(int_value);
					pNewMIV->setBody(boost::make_shared<c_MIVBody>(new_V));
					{
						LOG_DESIGN_INSUFFICIENCY(c_LogString("Auo-created MIV ") + miv_path.toString<c_LogString>() + c_LogString(" will have no corresponding M or I to describe it"));
					}
					m_MappedMIVs[miv_path] = pNewMIV;
					result = pNewMIV;
				}
			}
			return result;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_MIVsHandler::c_MIVsHandler(c_MessageTargetId id)
			:  m_id(id)
			  ,m_listening_client_id()
		{
		}

		// Begin c_SignalSinkIfc

		c_MessageTargetId c_MIVsHandler::getId() {
			return m_id;
		}

		c_SignalQueue::shared_ptr c_MIVsHandler::actOnSignal(const c_Signal::shared_ptr& pSignal) {
			c_SignalQueue::shared_ptr result = boost::make_shared<c_SignalQueue>();
			LOG_NOT_IMPLEMENTED;
			if (pSignal) {
				c_LogString sMessage(this->getId().toString<c_LogString>());
				sMessage += _UTF8sz("::actOnSignal(\"");
				sMessage += toLogString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalIdentifier]));
				sMessage += _UTF8sz("\")");
				LOG_BUSINESS(sMessage);

				c_MessageTargetId sender = c_MessageTargetId::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender]));
				if (sender.size() == 1) {
					// asume it is from a client (id Client::n)
					if (pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalIdentifier]) == SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_getMIVs]) {
						// Set sender as listener to us
						this->m_listening_client_id = c_MessageTargetId::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender]));
						c_Signal::shared_ptr pReply = boost::make_shared<c_Signal>();
						pReply->addElement(eSignalField_SignalSender,this->getId().toString<c_DarwinetString>());
						pReply->addElement(eSignalField_SignalReceiver,pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender]));
						pReply->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_getMIVsResponse]);
						result->push(pReply);
					}
					else if (pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_MIVsOperationId]) == MIVS_OPERATION_MAPPER[eMIVsOperation_Assign]) {
						// Value Assign request
						bool simulate_direct_call_back = false;
						if (simulate_direct_call_back) {

							c_Signal::shared_ptr pReply = boost::make_shared<c_Signal>();
							pReply->addElement(eSignalField_SignalSender,this->getId().toString<c_DarwinetString>());
							pReply->addElement(eSignalField_SignalReceiver,pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender]));
							pReply->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_OnMIVEvent]);

							pReply->addElement(eSignalField_MIVsEventId,MIVS_EVENT_MAPPER[eMIVsEventId_OnMIVValueChanged]);
							pReply->addElement(eSignalField_MIVsEventSourceId,pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_MIVsOperationTargetId]));
							pReply->addElement(eSignalField_MIVsEventValue,pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_MIVsOperationNewValue]));
							result->push(pReply);
						}
						else {
							// Get the MIV we want to change
							c_DarwinetString sTargetId = pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_MIVsOperationTargetId]);
							c_MIVPath target_miv_path = c_MIVPath::fromString(sTargetId);
							c_DarwinetString sNewValue = pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_MIVsOperationNewValue]);
							c_Delta::shared_ptr pDelta;
							{
								// Qick fix for now to test int or string value assign
								if (sTargetId == _UTF8sz("myInt:0")) {
									{
										c_LogString sMessage(METHOD_NAME + c_LogString(", Actual MIV model of target "));
										sMessage += sTargetId;
										sMessage += _UTF8sz(" not determined. Will assume integer instance");
										LOG_DESIGN_INSUFFICIENCY(sMessage);
									}
									c_Value_shared_ptr pNewValue = boost::make_shared<c_Value>(c_IntValue(c_DataRepresentationFramework::intValueOfDecimalString(sNewValue)));
									pDelta = this->createSetValueDelta(target_miv_path,pNewValue);
								}
								else if (sTargetId == _UTF8sz("myString:0")) {
//									{
//										c_LogString sMessage(METHOD_NAME + c_LogString(", Actual MIV model of target "));
//										sMessage += sTargetId;
//										sMessage += _UTF8sz(" not determined. Will assume string instance");
//										LOG_DESIGN_INSUFFICIENCY(sMessage);
//									}
//									c_Value_shared_ptr pNewValue = boost::make_shared<c_Value>(c_StringValue(sNewValue));
//									pDelta = this->createSetValueDelta(target_miv_path,pNewValue);

									/*
									TODO 140420

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

									*/
								}
								else {
									LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. Assigning MIV ") + target_miv_path.toString<c_LogString>() + c_LogString(" not implemented"));
								}
							}
							if (pDelta) {
								// Distribute the created Delta
								bool short_cut_delta_distribution = false;
								if (short_cut_delta_distribution) {
									c_SignalQueue::shared_ptr pDeltaCreationResponse = this->actOnDelta(pDelta);
									result->append(pDeltaCreationResponse);
								}
								else {
									c_LogString sMessage(METHOD_NAME + c_LogString(", Distribution of created Delta not yet Implemented"));
									LOG_DESIGN_INSUFFICIENCY(sMessage);

									// Create a signal of pDelta and distribute to all MIVs
									c_MessageTargetIds_shared_ptr pMIVHanlderIds =  c_DarwinetTestBench::instance()->getAllMIVHandlerIds();
									for (c_MessageTargetIds::iterator iter = pMIVHanlderIds->begin(); iter != pMIVHanlderIds->end(); ++iter) {
										c_Signal::shared_ptr pDeltaSignal = c_DarwinetTestBench::instance()->createSignal(this->getId(),*iter);
										pDeltaSignal->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_DeltaMIV]);
	//									,eSignalField_DeltaPredecessorIx
										c_CaptionPath delta_predecessor_ix_path;
										delta_predecessor_ix_path += c_CaptionPath::Node(pDelta->getPredecessor().getProducer());
										delta_predecessor_ix_path += c_CaptionPath::Node(pDelta->getPredecessor().getBranch());
										delta_predecessor_ix_path += c_CaptionPath::Node(c_DataRepresentationFramework::intToDecimalString(pDelta->getPredecessor().getSeqNo()));
										pDeltaSignal->addElement(eSignalField_DeltaPredecessorIx,delta_predecessor_ix_path.toString<c_CaptionNode>());
	//									,eSignalField_DeltaIx
										c_CaptionPath delta_ix_path;
										delta_ix_path += c_CaptionPath::Node(pDelta->getIndex().getProducer());
										delta_ix_path += c_CaptionPath::Node(pDelta->getIndex().getBranch());
										delta_ix_path += c_CaptionPath::Node(c_DataRepresentationFramework::intToDecimalString(pDelta->getIndex().getSeqNo()));
										pDeltaSignal->addElement(eSignalField_DeltaIx,delta_ix_path.toString<c_CaptionNode>());
	//									,eSignalField_DeltaTargetState
										c_CaptionPath delta_target_state_path;
										delta_target_state_path += c_CaptionPath::Node(pDelta->getMIVtarget().getState().getProducer());
										delta_target_state_path += c_CaptionPath::Node(pDelta->getMIVtarget().getState().getBranch());
										delta_target_state_path += c_CaptionPath::Node(c_DataRepresentationFramework::intToDecimalString(pDelta->getMIVtarget().getState().getSeqNo()));
										pDeltaSignal->addElement(eSignalField_DeltaTargetState,delta_target_state_path.toString<c_CaptionNode>());
	//									,eSignalField_DeltaTargetMIVId
										pDeltaSignal->addElement(eSignalField_DeltaTargetMIVId,pDelta->getMIVtarget().getMIVId().toString<c_CaptionNode>());
										if (pDelta->getDeltaOperation()->type() == typeid(c_IntDeltaOperation)) {
											c_IntDeltaOperation int_delta_operation = boost::get<c_IntDeltaOperation>(*pDelta->getDeltaOperation());
	//										,eSignalField_DeltaOperationId
											if (int_delta_operation.getIntOperationId() == eIntOperationId_ADD) {
												pDeltaSignal->addElement(eSignalField_DeltaOperationId,DELTA_OPERATION_MAPPER[eDeltaOperationId_IntDeltaAdd]);
	//											,eSignalField_DeltaOperationValue
												pDeltaSignal->addElement(eSignalField_DeltaOperationValue,c_DataRepresentationFramework::intToDecimalString(int_delta_operation.getValue().getRawValue()));
											}
										}
										result->push(pDeltaSignal);
									}
								}
							}
							else {
								// No Delta was created
								LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. No Delta created for Assigning MIV ") + target_miv_path.toString<c_LogString>() + c_LogString(" to value ") + sNewValue);
							}
						}
					}
					else {
						c_LogString sMessage;
						sMessage += this->getId().toString<c_LogString>();
						sMessage += _UTF8sz(": Acting on signal from ");
						sMessage += sender.toString<c_LogString>();
						sMessage += _UTF8sz(" Not implemented. Signal Discarded. ");
						LOG_BUSINESS(sMessage);
					}
				}
				else if (pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalIdentifier]) == SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_DeltaMIV]) {
					// Apply the received Delta
					c_Delta::shared_ptr pDelta(new c_Delta());
					{
						// Create Delta from Signal
//						,eSignalField_DeltaPredecessorIx
						c_CaptionPath delta_predecessor_ix_path = c_CaptionPath::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaPredecessorIx]));
						if (delta_predecessor_ix_path.size() == 3) {
							c_DeltaIndex delta_index;
							delta_index.setProducer(delta_predecessor_ix_path[0]);
							delta_index.setBranch(delta_predecessor_ix_path[1]);
							delta_index.setSeqNo(c_DataRepresentationFramework::intValueOfDecimalString(delta_predecessor_ix_path[2]));
							pDelta->setPredecessor(delta_index);
						}
						else {
							throw c_IllFormedSignalFieldException(c_LogString(" Incomplete Signal Field DeltaPredecessorIx=") + delta_predecessor_ix_path.toString<c_LogString>());
						}
//						,eSignalField_DeltaIx
						c_CaptionPath delta_ix_path = c_CaptionPath::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaIx]));
						if (delta_ix_path.size() == 3) {
							c_DeltaIndex delta_index;
							delta_index.setProducer(delta_ix_path[0]);
							delta_index.setBranch(delta_ix_path[1]);
							delta_index.setSeqNo(c_DataRepresentationFramework::intValueOfDecimalString(delta_ix_path[2]));
							pDelta->setIndex(delta_index);
						}
						else {
							throw c_IllFormedSignalFieldException(c_LogString(" Incomplete Signal Field DeltaIx=") + delta_ix_path.toString<c_LogString>());
						}
//						,eSignalField_DeltaTargetState
						c_CaptionPath delta_target_state_path = c_CaptionPath::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaTargetState]));
						if (delta_target_state_path.size() == 3) {
							c_DeltaIndex delta_index;
							delta_index.setProducer(delta_target_state_path[0]);
							delta_index.setBranch(delta_target_state_path[1]);
							delta_index.setSeqNo(c_DataRepresentationFramework::intValueOfDecimalString(delta_target_state_path[2]));
							c_MIVTarget delta_target;
							delta_target.setState(delta_index);
							delta_target.setMIVId(c_MIVPath::fromString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaTargetMIVId])));
							pDelta->setMIVtarget(delta_target);
						}
						else {
							throw c_IllFormedSignalFieldException(c_LogString(" Incomplete Signal Field DeltaIx=") + delta_ix_path.toString<c_LogString>());
						}
						if (pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaOperationId]) == DELTA_OPERATION_MAPPER[eDeltaOperationId_IntDeltaAdd]) {
							int raw_int_value = c_DataRepresentationFramework::intValueOfDecimalString(pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_DeltaOperationValue]));
							c_IntValue int_value(raw_int_value);
							e_IntOperationId int_operation_id = eIntOperationId_ADD;
							c_IntDeltaOperation int_delta_operation(int_value,int_operation_id);
							pDelta->setDeltaOperation(boost::make_shared<c_DeltaOperation>(int_delta_operation));
						}
					}
					c_SignalQueue::shared_ptr pDeltaCreationResponse = this->actOnDelta(pDelta);
					result->append(pDeltaCreationResponse);
				}
				else {
					c_LogString sMessage;
					sMessage += this->getId().toString<c_LogString>();
					sMessage += _UTF8sz(": Acting on signal from ");
					sMessage += sender.toString<c_LogString>();
					sMessage += _UTF8sz(" Not implemented. Signal Discarded. ");
					LOG_BUSINESS(sMessage);
				}
			}
			return result;
		}

		// End c_SignalSinkIfc

		c_Delta::shared_ptr c_MIVsHandler::createSetValueDelta(c_MIVPath id,c_Value_shared_ptr pNewValue) {
			{
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" should implement c_MIVs::createSetValueDelta() itself"));
			}
			return this->getMIVs()->createSetValueDelta(id,pNewValue);
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		class c_ApplyDeltaToMIVBody : public boost::static_visitor<> {
		public:

			c_ApplyDeltaToMIVBody(const c_MIVBody_shared_ptr& pMIVBody) : m_pMIVBody(pMIVBody) {;}

			void operator()(c_IntDeltaOperation& op) {
				try {
					if (m_pMIVBody) {
						c_V v = boost::get<c_V>(*m_pMIVBody);
						c_IntValue int_value = boost::get<c_IntValue>(v.getValue());
						int_value = op(int_value);
						v.setValue(int_value);
						*m_pMIVBody = v;
					}
					else {
						throw c_NULLMIVBodyException(c_LogString("Can't apply Delta"));
					}
				}
				catch (std::runtime_error& e) {
					throw c_DeltaApplicationException(METHOD_NAME + c_LogString(" failed to apply c_IntDeltaOperation to MIV. Excpetion=") + toLogString(e.what()));
				}
				catch (...) {
					throw c_DeltaApplicationException(METHOD_NAME + c_LogString(" failed to apply c_IntDeltaOperation to MIV. General Exception cought."));
				}
			}

			void operator()(c_StringDeltaOperation& op) {
				LOG_NOT_IMPLEMENTED;
			}

			void operator()(c_RecordDeltaOperation& op) {
				LOG_NOT_IMPLEMENTED;
			}

			void operator()(c_ArrayDeltaOperation& op) {
				LOG_NOT_IMPLEMENTED;
			}

		private:
			c_MIVBody_shared_ptr m_pMIVBody;
		};


		c_SignalQueue::shared_ptr c_MIVsHandler::actOnDelta(c_Delta::shared_ptr pDelta) {
			c_SignalQueue::shared_ptr result(new c_SignalQueue());

			// Find the MIV to apply the delta to
			if (pDelta) {
				c_MIV::shared_ptr pTargetMIV = this->getMIVs()->getMIV(pDelta->getMIVtarget().getMIVId());
				if (pTargetMIV) {
					// Apply the delta operation to the MIV body (they shall match)
					if (pTargetMIV->getState() == pDelta->getMIVtarget().getState()) {
//						c_ApplyDeltaToMIVBody visitor(pDelta->getDeltaOperation());
//						boost::apply_visitor(visitor,pTargetMIV->getBody());
						c_ApplyDeltaToMIVBody visitor(pTargetMIV->getBody());
						boost::apply_visitor(visitor,*pDelta->getDeltaOperation());
						{
							// Create the signal that alerts the Client about the change
							c_Signal::shared_ptr pReply = boost::make_shared<c_Signal>();
							pReply->addElement(eSignalField_SignalSender,this->getId().toString<c_DarwinetString>());
							pReply->addElement(eSignalField_SignalReceiver,this->m_listening_client_id.toString<c_DarwinetString>()); // Report event to client
							pReply->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_OnMIVEvent]);

							pReply->addElement(eSignalField_MIVsEventSourceId,pDelta->getMIVtarget().getMIVId().toString<c_DarwinetString>());
							if (pTargetMIV->getBody()->type() == typeid(c_V)) {
								// It is a V
								pReply->addElement(eSignalField_MIVsEventId,MIVS_EVENT_MAPPER[eMIVsEventId_OnMIVValueChanged]);
								c_V newV = boost::get<c_V>(*pTargetMIV->getBody());
								if (newV.getValue().type() == typeid(c_IntValue)) {
									c_IntValue newIntValue = boost::get<c_IntValue>(newV.getValue());
									pReply->addElement(eSignalField_MIVsEventValue,c_DataRepresentationFramework::intToDecimalString(newIntValue.getRawValue()));
								}
							}
							result->push(pReply);
						}
					}
					else {
						LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed to match MIV state ") + log::toLogString(pTargetMIV->getState()) + c_LogString(" with delta target state ") + log::toLogString(pDelta->getMIVtarget().getState()));
					}
				}
				else {
					throw c_NoSuchMIVException(METHOD_NAME + c_LogString(" failed. No MIV found for delta target =") + pDelta->getMIVtarget().getMIVId().toString<c_LogString>());
				}
			}
			else {
				throw c_NULLDeltaException(METHOD_NAME + c_LogString(" Called with NULL pDelta"));
			}
			return result;

		}

		c_MIVs::shared_ptr c_MIVsHandler::getMIVs() {
			if (!this->m_pMIVs) {
				c_DeltaIndex last_created_delta_index;
				last_created_delta_index.setProducer(this->getId().toString<c_MIVsProducerIdentifier>());
				last_created_delta_index.setBranch(c_DeltaBranchIdentifier("root"));
				last_created_delta_index.setSeqNo(0);
				this->m_pMIVs = boost::make_shared<c_MIVs>(last_created_delta_index);
			}
			return this->m_pMIVs;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_ViewHandler::c_ViewHandler(c_MessageTargetId id)
			: m_id(id)
		{
		}

		// Begin c_SignalSinkIfc

		c_MessageTargetId c_ViewHandler::getId() {
			return m_id;
		}

		c_SignalQueue::shared_ptr c_ViewHandler::actOnSignal(const c_Signal::shared_ptr& pSignal) {
			c_SignalQueue::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			return result;
		}

		// End c_SignalSinkIfc

		c_MIVsHandler::shared_ptr c_ViewHandler::getMIVsHandler() {
			if (!this->m_pMIVsHandler) {
				c_MessageTargetId MIVsHandlerId = this->getId()+ c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("MIVs1"));
				this->m_pMIVsHandler = boost::make_shared<c_MIVsHandler>(MIVsHandlerId);
			}
			return this->m_pMIVsHandler;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_DomainHandler::c_DomainHandler(c_MessageTargetId id)
			: m_id(id)
		{
		}

		// Begin c_SignalSinkIfc

		c_MessageTargetId c_DomainHandler::getId() {
			return m_id;
		}

		c_SignalQueue::shared_ptr c_DomainHandler::actOnSignal(const c_Signal::shared_ptr& pSignal) {
			c_SignalQueue::shared_ptr result;
			LOG_NOT_IMPLEMENTED;
			return result;
		}

		// End c_SignalSinkIfc

		c_ViewHandler::shared_ptr c_DomainHandler::getViewHandler(int view_index) {
			if (m_ViewHandlers.count(view_index) == 0) {
				c_MessageTargetId ViewHandlerId = this->getId() + c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("View"),view_index);
				m_ViewHandlers[view_index] = boost::make_shared<c_ViewHandler>(ViewHandlerId);
			}
			return m_ViewHandlers[view_index];
		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_DarwinetEngine::c_DarwinetEngine(c_MessageTargetId id)
			: m_id(id)
		{
		}

		c_MessageTargetId c_DarwinetEngine::getId() {
			return m_id;
		}

		c_DomainHandler::shared_ptr c_DarwinetEngine::getDomainHandler(int domain_index) {
			if (!m_pDomainHandler) {
				c_MessageTargetId DomainHandlerId = this->getId() + c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Domain"),domain_index);
				m_pDomainHandler = boost::make_shared<c_DomainHandler>(DomainHandlerId);
			}
			return m_pDomainHandler;
		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_TestClient::c_TestClient(c_MessageTargetId id)
			: m_id(id)
			  ,m_isOpen(false)
		{
		}

		void c_TestClient::open() {
			bool simulate_direct_call_back = false;
			if (simulate_direct_call_back) {
				// Short cut the call-back for test
				c_Signal::shared_ptr pSignal = c_DarwinetTestBench::instance()->createSignal(this->getId(),this->getId());
				pSignal->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_getMIVsResponse]);
				c_DarwinetTestBench::instance()->sendMessage(pSignal);
			}
			else {
				LOG_NOT_IMPLEMENTED;
				// Ask the View to connect us to its MIVs
				c_Signal::shared_ptr pSignal = c_DarwinetTestBench::instance()->createSignal(this->getId(),this->getMIVsHandlerId());
				pSignal->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_getMIVs]);
				c_DarwinetTestBench::instance()->sendMessage(pSignal);
			}
		}

		bool c_TestClient::isOpen() {
			return this->m_isOpen;
		}

		void c_TestClient::setMIVsid(c_MessageTargetId MIVsMessageTargetId) {
			{
				c_LogString sMessage;
				sMessage += this->getId().toString<c_LogString>();
				sMessage += _UTF8sz(": Setting MIVs Id to ");
				sMessage += MIVsMessageTargetId.toString<c_LogString>();
				LOG_BUSINESS(sMessage);
			}
			this->m_MIVsHandlerId = MIVsMessageTargetId;
		}

		void c_TestClient::connect(boost::shared_ptr<c_GUIClientproxy> pClientProxy) {
			if (!this->m_pClientProxy) {
				this->m_pClientProxy = pClientProxy;
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. m_pClientProxy already assigned. New assignment disregarded."));
			}
		}

		c_MessageTargetId c_TestClient::getId() {
			return m_id;
		}

		// Begin c_SignalSinkIfc

		c_SignalQueue::shared_ptr c_TestClient::actOnSignal(const c_Signal::shared_ptr& pSignal) {
			c_SignalQueue::shared_ptr result;
			if (pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalIdentifier]) == SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_getMIVsResponse]) {
				this->m_isOpen = true;
			}
			if (this->m_pClientProxy) {
				result = this->m_pClientProxy->actOnSignal(pSignal);
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClientProxy"));
			}
			return result;
		}

		// End c_SignalSinkIfc

		void c_TestClient::setMIVsValue(c_MIVPath MIVsId,c_TestClient::c_MIVsValue value) {
			bool simulate_direct_call_back = false;
			if (simulate_direct_call_back) {
				// Short cut back to Proxy for test
				if (this->m_pClientProxy) {
					c_Signal::shared_ptr pSignal = boost::make_shared<c_Signal>();
					pSignal->addElement(eSignalField_MIVsEventId,MIVS_EVENT_MAPPER[eMIVsEventId_OnMIVValueChanged]);
					pSignal->addElement(eSignalField_MIVsEventSourceId,MIVsId.toString<c_DarwinetString>());
					pSignal->addElement(eSignalField_MIVsEventValue,value);
					this->m_pClientProxy->actOnSignal(pSignal);
				}
				else {
					LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClientProxy"));
				}
			}
			else {
				c_Signal::shared_ptr pSignal = c_DarwinetTestBench::instance()->createSignal(this->getId(),this->getMIVsHandlerId());
				pSignal->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_ModifyMIVRequest]);
				pSignal->addElement(eSignalField_MIVsOperationId,MIVS_OPERATION_MAPPER[eMIVsOperation_Assign]);
				pSignal->addElement(eSignalField_MIVsOperationTargetId,MIVsId.toString<c_DarwinetString>());
				pSignal->addElement(eSignalField_MIVsOperationNewValue,value);
				c_DarwinetTestBench::instance()->sendMessage(pSignal);
			}
		}

		c_MessageTargetId c_TestClient::getMIVsHandlerId() {
			if (m_MIVsHandlerId.size() == 0) {
				c_LogString sMessage("NULL Client Id");
				throw c_InvalidActorIdException(sMessage);
			}
			return m_MIVsHandlerId;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_DarwinetTestBench::shared_ptr c_DarwinetTestBench::instance() {
			if (!m_pSharedInstance) {
				m_pSharedInstance.reset(new c_DarwinetTestBench());
			}
			return m_pSharedInstance;
		}

		c_DarwinetEngine::shared_ptr c_DarwinetTestBench::getDarwinetEngine() {
			if (!m_pDarwinetEngine) {
				m_pDarwinetEngine = boost::make_shared<c_DarwinetEngine>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Engine"),1)));
			}
			return m_pDarwinetEngine;
		};

		c_Signal::shared_ptr c_DarwinetTestBench::createSignal(c_MessageTargetId senderMessageTargetId,c_MessageTargetId receiverMessageTargetId) {
			c_Signal::shared_ptr result = boost::make_shared<c_Signal>();
			result->push_back(std::make_pair(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender],senderMessageTargetId.toString<c_DarwinetString>()));
			result->push_back(std::make_pair(SIGNAL_FIELD_MAPPER[eSignalField_SignalReceiver],receiverMessageTargetId.toString<c_DarwinetString>()));
			LOG_NOT_IMPLEMENTED;
			return result;
		}

		c_TestClient::shared_ptr c_DarwinetTestBench::getTestClient(unsigned int index) {
			if (!m_TestCients[index]) {
				c_MessageTargetId client_id(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Client"),index));
				c_TestClient::shared_ptr pTestClient = boost::make_shared<c_TestClient>(client_id);
				c_MessageTargetId MIVsMessageTargetId = this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(index)->getMIVsHandler()->getId();
				pTestClient->setMIVsid(MIVsMessageTargetId);
				m_Messenger.connect(pTestClient);
				m_TestCients[index] = pTestClient;
			}
			return m_TestCients[index];
		}

		void c_DarwinetTestBench::sendMessage(c_Signal::shared_ptr pSignal) {
			this->m_Messenger.send(pSignal);
		}

		c_MessageTargetIds_shared_ptr c_DarwinetTestBench::getAllMIVHandlerIds() {
			/**
			  * TODO: remove this mecanism when proper Doman handling is in place.
			  * This list defines all MIVs in the Domain for now during test of Delta Processing.
			  */
			c_MessageTargetIds_shared_ptr result(new c_MessageTargetIds());
			result->push_back(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(1)->getMIVsHandler()->getId());
			result->push_back(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(2)->getMIVsHandler()->getId());
			result->push_back(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(3)->getMIVsHandler()->getId());
			return result;
		}

		void c_DarwinetTestBench::processMessages() {
			for (int i = 0; i < 10; i++) {
				m_Messenger.process();
			}
		}

		c_DarwinetTestBench::c_DarwinetTestBench()
		{
			// TODO: Find a way to automatically scale up the Darwinet actors on new GUI clients (and optionally ned Domains)
			// For now, Hard code what actors we have for intra-messaging.
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1));
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(1));
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(2));
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(3));
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(1)->getMIVsHandler());
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(2)->getMIVsHandler());
			m_Messenger.connect(this->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(3)->getMIVsHandler());
			LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" uses Hard Coded Domain and View instances. Will NOT adapt to dynamic instancing of Clients."));
		}

		c_DarwinetTestBench::shared_ptr c_DarwinetTestBench::m_pSharedInstance;

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		namespace log {

			c_LogString toLogString(const c_Signal& signal) {
				c_LogString result;
				for (c_Signal::const_iterator iter = signal.begin(); iter != signal.end(); ++iter) {
					result += _UTF8sz("\n\t\""); // Infdent each key, value row
					result += toLogString(iter->first);
					result += _UTF8sz("\"=\"");
					result += toLogString(iter->second);
					result += _UTF8sz("\"");
				}
				return result;
			}

			c_LogString toLogString(c_Signal::shared_ptr pSignal) {
				c_LogString result;
				if (pSignal) {
					result = toLogString(*pSignal);
				}
				else {
					result = _UTF8sz("NULL");
				}
				return result;
			}

			c_LogString toLogString(const c_DeltaIndex& index) {
				c_LogString result;
				result += _UTF8sz("index{");
				result += toLogString(index.getProducer());
				result += _UTF8sz(", ");
				result += toLogString(index.getBranch());
				result += _UTF8sz(", ");
				result += c_DataRepresentationFramework::intToDecimalString(index.getSeqNo());
				result += _UTF8sz("}");
				return result;
			}

			c_LogString toLogString(const c_MIVTarget& miv_target) {
				c_LogString result;
				result += _UTF8sz("state{");
				result += toLogString(miv_target.getState());
				result += _UTF8sz(", ");
				result += miv_target.getMIVId().toString<c_LogString>();
				result += _UTF8sz("}");
				return result;
			}

			void logSignalSend(c_Signal::shared_ptr pSignal) {
				c_LogString sMessage("NULL Signal");
				if (pSignal) {
					sMessage = pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalSender]);
					sMessage += _UTF8sz(" ==> ");
					sMessage += pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalIdentifier]);
					sMessage += _UTF8sz(" ==> ");
					sMessage += pSignal->getValue(SIGNAL_FIELD_MAPPER[eSignalField_SignalReceiver]);
				}
				LOG_BUSINESS(sMessage);
			}

		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		void test() {

			if (true) {
				c_TestClient::shared_ptr pClient1 = boost::make_shared<c_TestClient>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Client"),1)));
				c_TestClient::shared_ptr pClient2 = boost::make_shared<c_TestClient>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Client"),2)));

				c_Messenger Messenger;
				Messenger.connect(pClient1);
				Messenger.connect(pClient2);
				Messenger.connect(c_DarwinetTestBench::instance()->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(1)->getMIVsHandler());
				Messenger.connect(c_DarwinetTestBench::instance()->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(2)->getMIVsHandler());
				Messenger.connect(c_DarwinetTestBench::instance()->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(1));
				Messenger.connect(c_DarwinetTestBench::instance()->getDarwinetEngine()->getDomainHandler(1)->getViewHandler(2));
				Messenger.connect(c_DarwinetTestBench::instance()->getDarwinetEngine()->getDomainHandler(1));

//				Messenger.send(pClient1->testMIVChange());
				for (int i = 0; i < 10; i++) {
					Messenger.process();
				}
			}
			else {
//				c_TestClient::shared_ptr pClient1 = boost::make_shared<c_TestClient>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Client"),1)));
//				c_TestClient::shared_ptr pClient2 = boost::make_shared<c_TestClient>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Client"),2)));
//
//				c_DarwinetEngine::shared_ptr pEngine = boost::make_shared<c_DarwinetEngine>(c_MessageTargetId(c_MessageTargetId::Node(c_MessageTargetId::Node::t_key("Engine"),1)));
//
//				c_SignalPipes::shared_ptr pMessenger = boost::make_shared<c_SignalPipes>();
//
//				// About function pointers; See http://stackoverflow.com/questions/15323299/passing-function-pointer-arguments-with-boost
//				// Note: boost::bind stores copies of all provided parameters. But as we provide a smart pointer as the object pointer
//				//       the copied smart pointer still refers to the same object :)
//				//       I make this node because I tried providing *pSmartPointer as second parameter to bind. But
//				//       then bind stored and called a copy (!) of the provided instance (took me a while to realize)
//
//				// Bind Client -> MIVs Queue -> MIVs
//				c_SignalPipe::shared_ptr pClientToMIVs1SignalPipe = boost::make_shared<c_SignalPipe>();
//				// Bind Client -> MIVs Queue
//				pClient1->onSignalToMIVs = boost::bind(&c_SignalPipe::actOnInSignal,pClientToMIVs1SignalPipe,_1);
//				// Bind           MIVs Queue -> MIVs
//				pClientToMIVs1SignalPipe->onSignalToTarget = boost::bind(&c_MIVsHandler::actOnSignalFromClient,pEngine->getDomainHandler(1)->getViewHandler(1)->getMIVsHandler(),_1);
//				// Bind MIVs -> Client Queue -> Client
//				c_SignalPipe::shared_ptr pMIVsToClient1SignalPipe = boost::make_shared<c_SignalPipe>();
//				// Bind MIVs -> Client Queue
//				pEngine->getDomainHandler(1)->getViewHandler(1)->getMIVsHandler()->onSignalToClient
//					= boost::bind(&c_SignalPipe::actOnInSignal,pMIVsToClient1SignalPipe,_1);
//				// Bind         Client Queue -> Client
//				pMIVsToClient1SignalPipe->onSignalToTarget = boost::bind(&c_TestClient::actOnSignalFromMIVs,pClient1,_1);
//
//				pClient1->testMIVChange();
//				pClientToMIVs1SignalPipe->process();
			}
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_GUIClientproxy::c_GUIClientproxy(c_TestClient::shared_ptr pClient)
			:  m_pGUIWindow(NULL)
			  ,m_pClient(pClient)
		{};

		void c_GUIClientproxy::open() {
			if (this->m_pClient) {
				this->m_pClient->open();
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClient."));
			}
		}

		bool c_GUIClientproxy::isOpen()  {
			bool result = false;
			if (this->m_pClient) {
				result =  this->m_pClient->isOpen();
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClient."));
			}
			return result;
		}

		void c_GUIClientproxy::setMIVsValue(c_GUIClientproxy::c_MIVId MIVId,c_GUIClientproxy::c_MIVValue value) {
			bool simulate_direct_call_back = false;
			if (simulate_direct_call_back) {
				// Short cut the call-back for test
				if (this->m_pGUIWindow) {
					c_Signal::shared_ptr pSignal = boost::make_shared<c_Signal>();
					pSignal->addElement(eSignalField_SignalIdentifier,SIGNAL_IDENTIFIER_MAPPER[eSignalIdentifier_OnMIVEvent]);
					pSignal->addElement(eSignalField_MIVsEventId,MIVS_EVENT_MAPPER[eMIVsEventId_OnMIVValueChanged]);
					pSignal->addElement(eSignalField_MIVsEventSourceId,MIVId);
					pSignal->addElement(eSignalField_MIVsEventValue,_UTF8sz("23"));
					c_DarwinetString sSignal(toString(*pSignal));
					char* szRawSignalString = new char[sSignal.length()+1];
					strcpy(szRawSignalString,sSignal.c_str());
//					PostMessage(this->m_pGUIWindow,WM_USER+1,0,reinterpret_cast<LPARAM>(szRawSignalString));
					PostMessage(this->m_pGUIWindow,eWINDOWS_MESSAGE_ID_OnDarwinetSignal,0,reinterpret_cast<LPARAM>(szRawSignalString));

				}
				else {
					LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pGUIWindow"));
				}
			}
			else {
				if (this->m_pClient) {
					this->m_pClient->setMIVsValue(c_MIVPath::fromString<c_GUIClientproxy::c_MIVId>(MIVId),value);
				}
				else {
					LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClient."));
				}
			}

		};

		void c_GUIClientproxy::setGUIWindowhandle(HWND pGUIWindow) {
			LOG_METHOD_SCOPE;
			this->m_pGUIWindow = pGUIWindow;
		}

		// Begin c_SignalSinkIfc

		c_MessageTargetId c_GUIClientproxy::getId() {
			c_MessageTargetId result;
			if (this->m_pClient) {
				result = this->m_pClient->getId();
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pClient. Will return undefined id"));
			}
			return result;
		}

		c_SignalQueue::shared_ptr c_GUIClientproxy::actOnSignal(const c_Signal::shared_ptr& pSignal) {
			c_SignalQueue::shared_ptr result;
			if (this->m_pGUIWindow) {
				c_DarwinetString sSignal(toString(*pSignal));
				char* szRawSignalString = new char[sSignal.length()+1];
				strcpy(szRawSignalString,sSignal.c_str());
				PostMessage(this->m_pGUIWindow,WM_USER+1,0,reinterpret_cast<LPARAM>(szRawSignalString));
			}
			else {
				LOG_DESIGN_INSUFFICIENCY(METHOD_NAME + c_LogString(" failed. NULL m_pGUIWindow"));
			}
			return result;
		}

		// End c_SignalSinkIfc

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_TestBenchClientSideProxy::c_TestBenchClientSideProxy()
			:  m_pGUIWindow(NULL)
		{
			LOG_METHOD_SCOPE;
		};

		c_GUIClientproxy::shared_ptr c_TestBenchClientSideProxy::getGUIClientproxy(int index) {
			if (!m_GUIClientproxies[index]) {
				c_TestClient::shared_ptr pTestClient = c_DarwinetTestBench::instance()->getTestClient(index);
				c_GUIClientproxy::shared_ptr pGUIClientproxy = boost::make_shared<c_GUIClientproxy>(pTestClient);
				pTestClient->connect(pGUIClientproxy);
				m_GUIClientproxies[index] = pGUIClientproxy;
			}
			return m_GUIClientproxies[index];
		};

		void c_TestBenchClientSideProxy::processMessages() {
			c_DarwinetTestBench::instance()->processMessages();
		}

	}


	namespace miv4 {


		struct is_parameter_key {
			is_parameter_key(const c_DarwinetString& sKey)
				: m_sKey(sKey)
			{
			};

			bool operator()(const c_Signal::Pair& pair) {
				return (pair.first == m_sKey);
			};

			c_DarwinetString m_sKey;

		};

		c_Signal::const_iterator c_Signal::find(const c_DarwinetString& sKey) {
			c_Signal::const_iterator result = std::find_if(this->begin(),this->end(),is_parameter_key(sKey));
			return result;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		int c_TestClient::m_class_state = 0;

		c_TestClient::c_TestClient(const c_StackActorPath& stack_path)
			:  m_stack_path(stack_path)
			  ,m_pToViewSignalQueue(boost::make_shared<c_SignalQueue>())
		{

		}

		const c_StackActorPath& c_TestClient::getStackActorPath() const {
			return m_stack_path;
		}

		void c_TestClient::performTestAction() {

			c_Signal::shared_ptr pToViewSignal;
			switch (m_class_state) {
			case 0:
				pToViewSignal = boost::make_shared<c_Signal>();
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("MODEL")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("ADD")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("model"),c_DarwinetString("RECORD")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("member"),c_DarwinetString("myRecord")));
				break;
			case 1:
				pToViewSignal = boost::make_shared<c_Signal>();
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("MODEL")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root.myRecord")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("ADD")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("model"),c_DarwinetString("STRING")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("member"),c_DarwinetString("myString")));
				break;
			case 2:
				pToViewSignal = boost::make_shared<c_Signal>();
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("INSTANCE")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("CREATE")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("member"),c_DarwinetString("myRecord")));
				break;
			case 3:
				pToViewSignal = boost::make_shared<c_Signal>();
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("INSTANCE")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root.myRecord")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("CREATE")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("member"),c_DarwinetString("myString")));
				break;
			case 4:
				pToViewSignal = boost::make_shared<c_Signal>();
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("VALUE")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root.myRecord.myString")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("SET")));
				pToViewSignal->push_back(std::make_pair(c_DarwinetString("value"),c_DarwinetString("Hello Darwinet World!")));
				break;

			default:
				;
			}
			if (pToViewSignal) {
				this->m_pToViewSignalQueue->push(pToViewSignal);
			}
			++m_class_state;
		}

		void c_TestClient::actOnSignalFromView(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			this->performTestAction(); // Initiate the next test action
		}

		c_SignalQueue::shared_ptr c_TestClient::getToViewSignalQueue() {
			return this->m_pToViewSignalQueue;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------

		c_TestView::c_TestView(const c_StackActorPath& stack_path)
			:  m_stack_path(stack_path)
			  ,m_last_used_seq_no(-1)
			  ,m_pToDomainSignalQueue(boost::make_shared<c_SignalQueue>())
			  ,m_pToClientSignalQueue(boost::make_shared<c_SignalQueue>())
		{

		}

		const c_StackActorPath& c_TestView::getStackActorPath() const {
			return m_stack_path;
		}

		unsigned int c_TestView::reserveSeqNo() {
			return m_last_used_seq_no+1;
		}

		void c_TestView::allocateSeqNo(unsigned int seq_no) {
			if (seq_no != static_cast<unsigned int>(m_last_used_seq_no+1)) {
				c_LogString sMessage(__FUNCTION__" failed. m_last_used_seq_no=");
				sMessage += c_DataRepresentationFramework::intToDecimalString(m_last_used_seq_no);
				sMessage += _UTF8sz(" and provided seq_no=");
				sMessage += c_DataRepresentationFramework::intToDecimalString(seq_no);
				sMessage += _UTF8sz(" is not in seqeunce. Will set new seq_no anyhow.");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
			m_last_used_seq_no = seq_no;
		};

		void c_TestView::actOnSignalFromClient(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			c_Signal::shared_ptr pToDomainSignal;

			c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("miv_class"));
			if (iter != pSignal->end()) {
				if (iter->second == c_DarwinetString("MODEL")) {
					// A Model modification request
					c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("target"));
					if (iter != pSignal->end()) {
						c_DarwinetString sTarget = iter->second;
						c_MIVPath miv_target_path = c_MIVPath::fromString(sTarget);
						c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("operation"));
						if (iter != pSignal->end()) {
							if (iter->second == c_DarwinetString("ADD")) {
								// An ADD to Model request
								c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("model"));
								if (iter != pSignal->end()) {
									c_DarwinetString sModel = iter->second;
									c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("member"));
									if (iter != pSignal->end()) {
										{
											c_LogString sMessage(__FUNCTION__" failed. Not fully implemented for creating a true dM");
											LOG_DESIGN_INSUFFICIENCY(sMessage);
										}
										c_DarwinetString sMember = iter->second;
										unsigned int seq_no = this->reserveSeqNo(); // Start transaction
										pToDomainSignal = boost::make_shared<c_Signal>();
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("producer"),this->getStackActorPath().toString<c_DarwinetString>()));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("seq_no"),c_DataRepresentationFramework::intToDecimalString(seq_no)));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("dM")));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("target"),miv_target_path.toString<c_DarwinetString>()));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("ADD")));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("model"),sModel));
										pToDomainSignal->push_back(std::make_pair(c_DarwinetString("member"),sMember));
										this->allocateSeqNo(seq_no); // End transaction
									}
									else {
										log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No MODEL ADD Member"));
									}
								}
								else {
									log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No MODEL ADD Model"));
								}
							}
							else {
								c_LogString sMessage(__FUNCTION__" failed. Unknown Model Operation \"");
								sMessage += toLogString(iter->second);
								sMessage += _UTF8sz("\"");
								log::logDesignInsufficiency(*this,sMessage);
							}
						}
						else {
							log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No MODEL target operation"));
						}
					}
					else {
						log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Model target"));
					}
				}
				else if (iter->second == c_DarwinetString("INSTANCE")) {
					// An Instance Set Modifiation Request
					c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("target"));
					if (iter != pSignal->end()) {
						c_DarwinetString sTarget = iter->second;
						c_MIVPath miv_target_path = c_MIVPath::fromString(sTarget);
						c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("operation"));
						if (iter != pSignal->end()) {
							if (iter->second == c_DarwinetString("CREATE")) {
								c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("member"));
								if (iter != pSignal->end()) {
									{
										c_LogString sMessage(__FUNCTION__" failed. Not fully implemented for creating a true dI");
										LOG_DESIGN_INSUFFICIENCY(sMessage);
									}
									c_DarwinetString sMember = iter->second;
									unsigned int seq_no = this->reserveSeqNo(); // Start transaction
									pToDomainSignal = boost::make_shared<c_Signal>();
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("producer"),this->getStackActorPath().toString<c_DarwinetString>()));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("seq_no"),c_DataRepresentationFramework::intToDecimalString(seq_no)));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("dI")));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("target"),miv_target_path.toString<c_DarwinetString>()));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("CREATE")));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("member"),sMember));
									this->allocateSeqNo(seq_no); // End transaction
								}
								else {
									log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No INSTANCE target member"));
								}
							}
							else {
								c_LogString sMessage(__FUNCTION__" failed. Unknown Instance Operation \"");
								sMessage += toLogString(iter->second);
								sMessage += _UTF8sz("\"");
								log::logDesignInsufficiency(*this,sMessage);
							}
						}
						else {
							log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No INSTANCE target operation"));
						}
					}
					else {
						log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No INSTANCE target"));
					}
				}
				else if (iter->second == c_DarwinetString("VALUE")) {
					// An Instance Value Modifiation Request
					log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. Target VALUE not implemented"));
					/*
					pToViewSignal->push_back(std::make_pair(c_DarwinetString("miv_class"),c_DarwinetString("VALUE")));
					pToViewSignal->push_back(std::make_pair(c_DarwinetString("target"),c_DarwinetString("root.myRecord.myString")));
					pToViewSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("SET")));
					pToViewSignal->push_back(std::make_pair(c_DarwinetString("value"),c_DarwinetString("Hello Darwinet World!")));
					*/
					c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("target"));
					if (iter != pSignal->end()) {
						c_DarwinetString sTarget = iter->second;
						c_MIVPath miv_target_path = c_MIVPath::fromString(sTarget);
						c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("operation"));
						if (iter != pSignal->end()) {
							if (iter->second == c_DarwinetString("SET")) {
								c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("value"));
								if (iter != pSignal->end()) {
									{
										c_LogString sMessage(__FUNCTION__" failed. Not fully implemented for creating a true dV");
										LOG_DESIGN_INSUFFICIENCY(sMessage);
									}
									c_DarwinetString sValue = iter->second;
									c_DarwinetString sDelta("??=>");
									sDelta += sValue;
									unsigned int seq_no = this->reserveSeqNo(); // Start transaction
									pToDomainSignal = boost::make_shared<c_Signal>();
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("producer"),this->getStackActorPath().toString<c_DarwinetString>()));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("seq_no"),c_DataRepresentationFramework::intToDecimalString(seq_no)));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("dV")));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("target"),miv_target_path.toString<c_DarwinetString>()));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("operation"),c_DarwinetString("STRING_PATCH")));
									pToDomainSignal->push_back(std::make_pair(c_DarwinetString("delta"),sDelta));
									this->allocateSeqNo(seq_no); // End transaction
								}
								else {
									log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No VALUE target value"));
								}
							}
							else {
								c_LogString sMessage(__FUNCTION__" failed. Unknown Value Operation \"");
								sMessage += toLogString(iter->second);
								sMessage += _UTF8sz("\"");
								log::logDesignInsufficiency(*this,sMessage);
							}
						}
						else {
							log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No VALUE target operation"));
						}
					}
					else {
						log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No VALUE target"));
					}
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Unknown MIV Class \"");
					sMessage += toLogString(iter->second);
					sMessage += _UTF8sz("\"");
					log::logDesignInsufficiency(*this,sMessage);
				}
			}
			else {
				log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Signal Target"));
			}
			if (pToDomainSignal) {
				this->m_pToDomainSignalQueue->push(pToDomainSignal); // Dummy
			}
		}

		void c_TestView::actOnSignalFromDomain(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			c_Signal::shared_ptr pToClientSignal;

			c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("signal_id"));
			if (iter != pSignal->end()) {
				if (iter->second == c_DarwinetString("dM")) {
					pToClientSignal = boost::make_shared<c_Signal>();
					pToClientSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("onModelChange")));
				}
				else if (iter->second == c_DarwinetString("dI")) {
					pToClientSignal = boost::make_shared<c_Signal>();
					pToClientSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("onInstanceChange")));
				}
				else if (iter->second == c_DarwinetString("dV")) {
					pToClientSignal = boost::make_shared<c_Signal>();
					pToClientSignal->push_back(std::make_pair(c_DarwinetString("signal_id"),c_DarwinetString("onValueChange")));
				}
				else {
					c_LogString sMessage(c_LogString(__FUNCTION__" failed. Unknown Signal Id"));
					sMessage += iter->second;
					log::logDesignInsufficiency(*this,sMessage);
				}
			}
			else {
				log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Signal Id"));
			}

			if (pToClientSignal) {
				this->m_pToClientSignalQueue->push(pToClientSignal);
			}
		}

		c_SignalQueue::shared_ptr c_TestView::getToDomainSignalQueue() {
			return this->m_pToDomainSignalQueue;
		}

		c_SignalQueue::shared_ptr c_TestView::getToClientSignalQueue() {
			return this->m_pToClientSignalQueue;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_TestDomain::c_TestDomain(const c_StackActorPath& stack_path)
			:  m_stack_path(stack_path)
			  ,m_pToOtherNodeSignalQueue(boost::make_shared<c_SignalQueue>())
			  ,m_pToViewSignalQueue(boost::make_shared<c_SignalQueue>())
		{

		}

		const c_StackActorPath& c_TestDomain::getStackActorPath() const {
			return m_stack_path;
		}

		void c_TestDomain::actOnSignalFromView(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			c_Signal::shared_ptr pToOtherNodesSignal;

			c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("signal_id"));
			if (iter != pSignal->end()) {
				if (    (iter->second == c_DarwinetString("dM"))
					 || (iter->second == c_DarwinetString("dI"))
					 || (iter->second == c_DarwinetString("dV"))) {
					pToOtherNodesSignal = boost::make_shared<c_Signal>(*pSignal); // Forward a copy to other node
				}
				else {
					c_LogString sMessage(c_LogString(__FUNCTION__" failed. Unknown Signal Id"));
					sMessage += iter->second;
					log::logDesignInsufficiency(*this,sMessage);
				}
			}
			else {
				log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Signal Id"));
			}

			if (pToOtherNodesSignal) {
				this->m_pToOtherNodeSignalQueue->push(pToOtherNodesSignal);
			}
		}

		void c_TestDomain::actOnSignalFromNode(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			c_Signal::shared_ptr pToViewSignal;

			c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("signal_id"));
			if (iter != pSignal->end()) {
				if (    (iter->second == c_DarwinetString("dM"))
					 || (iter->second == c_DarwinetString("dI"))
					 || (iter->second == c_DarwinetString("dV"))) {
					pToViewSignal = boost::make_shared<c_Signal>(*pSignal); // Forward a copy to View
				}
				else {
					c_LogString sMessage(c_LogString(__FUNCTION__" failed. Unknown Signal Id"));
					sMessage += iter->second;
					log::logDesignInsufficiency(*this,sMessage);
				}
			}
			else {
				log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Signal Id"));
			}

			if (pToViewSignal) {
				this->m_pToViewSignalQueue->push(pToViewSignal);
			}
		}

		c_SignalQueue::shared_ptr c_TestDomain::getToOtherNodeSignalQueue() {
			return this->m_pToOtherNodeSignalQueue;
		}

		c_SignalQueue::shared_ptr c_TestDomain::getToViewSignalQueue() {
			return this->m_pToViewSignalQueue;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_TestNode::c_TestNode(const c_StackActorPath& stack_path)
			:  m_stack_path(stack_path)
			  ,m_pToDomainSignalQueue(boost::make_shared<c_SignalQueue>())
		{

		}

		const c_StackActorPath& c_TestNode::getStackActorPath() const {
			return m_stack_path;
		}

		void c_TestNode::actOnSignalFromOtherNode(c_Signal::shared_ptr pSignal) {
			log::logInSignal(*this,pSignal);
			c_Signal::shared_ptr pToDomainSignal;

			c_Signal::const_iterator iter = pSignal->find(c_DarwinetString("signal_id"));
			if (iter != pSignal->end()) {
				if (    (iter->second == c_DarwinetString("dM"))
					 || (iter->second == c_DarwinetString("dI"))
					 || (iter->second == c_DarwinetString("dV"))) {
					pToDomainSignal = boost::make_shared<c_Signal>(*pSignal); // Forward a copy to View
				}
				else {
					c_LogString sMessage(c_LogString(__FUNCTION__" failed. Unknown Signal Id"));
					sMessage += iter->second;
					log::logDesignInsufficiency(*this,sMessage);
				}
			}
			else {
				log::logDesignInsufficiency(*this,c_LogString(__FUNCTION__" failed. No Signal Id"));
			}

			if (pToDomainSignal) {
				this->m_pToDomainSignalQueue->push(pToDomainSignal);
			}
		}

		c_SignalQueue::shared_ptr c_TestNode::getToDomainSignalQueue() {
			return this->m_pToDomainSignalQueue;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		c_TestPeerConfiguration::c_TestPeerConfiguration(const c_StackActorPath& stack_path)
			:  m_pTestClient(boost::make_shared<c_TestClient>(stack_path + c_StackActorPath::Node("CLIENT")))
			  ,m_pTestView(boost::make_shared<c_TestView>(stack_path + c_StackActorPath::Node("VIEW")))
			  ,m_pTestDomain(boost::make_shared<c_TestDomain>(stack_path + c_StackActorPath::Node("DOMAIN")))
			  ,m_pTestNode(boost::make_shared<c_TestNode>(stack_path + c_StackActorPath::Node("NODE")))
		{

		}

		void c_TestPeerConfiguration::processSignals() {
			while (    (m_pTestClient->getToViewSignalQueue()->size() > 0)
					|| (m_pTestView->getToDomainSignalQueue()->size() > 0)
					|| (m_pTestNode->getToDomainSignalQueue()->size() > 0)
					|| (m_pTestDomain->getToViewSignalQueue()->size() > 0)
					|| (m_pTestView->getToClientSignalQueue()->size() > 0)) {
				// Transfer from Client to View
				if (m_pTestClient->getToViewSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromClientToView = m_pTestClient->getToViewSignalQueue()->front();
					m_pTestClient->getToViewSignalQueue()->pop();
					m_pTestView->actOnSignalFromClient(pSignalFromClientToView);
				}
				// Transfer from View to Domain
				if (m_pTestView->getToDomainSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromViewToDomain = m_pTestView->getToDomainSignalQueue()->front();
					m_pTestView->getToDomainSignalQueue()->pop();
					m_pTestDomain->actOnSignalFromView(pSignalFromViewToDomain);
				}
				// Transfer from Domain to Other node is handled externally
				// Transfer from Other Node to Domain
				if (m_pTestNode->getToDomainSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromNodeToDomain = m_pTestNode->getToDomainSignalQueue()->front();
					m_pTestNode->getToDomainSignalQueue()->pop();
					m_pTestDomain->actOnSignalFromNode(pSignalFromNodeToDomain);
				}
				// Transfer from Domain to View
				if (m_pTestDomain->getToViewSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromDomainToView = m_pTestDomain->getToViewSignalQueue()->front();
					m_pTestDomain->getToViewSignalQueue()->pop();
					m_pTestView->actOnSignalFromDomain(pSignalFromDomainToView);
				}
				if (m_pTestView->getToClientSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromViewToClient = m_pTestView->getToClientSignalQueue()->front();
					m_pTestView->getToClientSignalQueue()->pop();
					m_pTestClient->actOnSignalFromView(pSignalFromViewToClient);
				}

			}
		}

		c_TestClient::shared_ptr c_TestPeerConfiguration::getTestClient() {
			return this->m_pTestClient;
		}

		c_TestView::shared_ptr c_TestPeerConfiguration::getTestView() {
			return this->m_pTestView;
		}

		c_TestDomain::shared_ptr c_TestPeerConfiguration::getTestDomain() {
			return this->m_pTestDomain;
		}

		c_TestNode::shared_ptr c_TestPeerConfiguration::getTestNode() {
			return this->m_pTestNode;
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		namespace log {

			c_LogString toLogString(c_Signal::shared_ptr pSignal) {
				c_LogString result;
				if (pSignal) {
					bool is_first_parameter = true;
					for (c_Signal::const_iterator iter = pSignal->begin(); iter != pSignal->end(); ++iter) {
						if (result.size() > 0) {
							result += _UTF8sz(" "); // add separator
						}
//						result += toLogString(iter->first);
//						result += _UTF8sz(":");
						result += toLogString(iter->second);
					}
				}
				else {
					result = _UTF8sz("NULL");
				}
				return result;
			}
		}

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		void test() {
			// 1. The Client requests the viewed MIV to be modified
			// 2. The View produces a Delta that defines the change
			// 3. The Domain distributes the Delta within the Domain
			// 4. The View applies the distributed Delta and reports the change to the Client

			c_TestPeerConfiguration::shared_ptr pTestPeerConfiguration1 = boost::make_shared<c_TestPeerConfiguration>(c_StackActorPath::fromString(c_DarwinetString("P1")));
			c_TestPeerConfiguration::shared_ptr pTestPeerConfiguration2 = boost::make_shared<c_TestPeerConfiguration>(c_StackActorPath::fromString(c_DarwinetString("P2")));

			pTestPeerConfiguration1->getTestClient()->performTestAction();
			pTestPeerConfiguration1->processSignals();

			while (    (pTestPeerConfiguration1->getTestDomain()->getToOtherNodeSignalQueue()->size() > 0)
					|| (pTestPeerConfiguration2->getTestDomain()->getToOtherNodeSignalQueue()->size() > 0)) {
				if (pTestPeerConfiguration1->getTestDomain()->getToOtherNodeSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromDomainToOtherNode = pTestPeerConfiguration1->getTestDomain()->getToOtherNodeSignalQueue()->front();
					pTestPeerConfiguration1->getTestDomain()->getToOtherNodeSignalQueue()->pop();
					// Forward the signal both to "self" and other nodes in the domain
					pTestPeerConfiguration1->getTestNode()->actOnSignalFromOtherNode(pSignalFromDomainToOtherNode);
					pTestPeerConfiguration2->getTestNode()->actOnSignalFromOtherNode(boost::make_shared<c_Signal>(*pSignalFromDomainToOtherNode)); // Forward a copy
				}
				pTestPeerConfiguration2->processSignals();
				if (pTestPeerConfiguration2->getTestDomain()->getToOtherNodeSignalQueue()->size() > 0) {
					c_Signal::shared_ptr pSignalFromDomainToOtherNode = pTestPeerConfiguration2->getTestDomain()->getToOtherNodeSignalQueue()->front();
					pTestPeerConfiguration2->getTestDomain()->getToOtherNodeSignalQueue()->pop();

					// Forward the signal both to "self" and other nodes in the domain
					pTestPeerConfiguration2->getTestNode()->actOnSignalFromOtherNode(pSignalFromDomainToOtherNode);
					pTestPeerConfiguration1->getTestNode()->actOnSignalFromOtherNode(boost::make_shared<c_Signal>(*pSignalFromDomainToOtherNode)); // Forward a copy
				}
				pTestPeerConfiguration1->processSignals();
			}
		}
	}

	namespace miv3 {
		// Iteration 6. Iteration 5 failed to provide a good design for the roundtrip
		// MIV += change through Evolution manager and back to another MIV.
		// The problem is naming of all the artefacts needed to make this processing clean.
		// lets see if we can improve on the design this time.

		namespace client {
			c_ClientDelta::c_ClientDelta(const core::c_CoreDelta& CoreDelta, const c_MIVPath& TargetMIVPath)
				:  core::c_CoreDelta(CoreDelta)
				  ,m_TargetMIVPath(TargetMIVPath)
			{
			}
		};

		namespace view {

			c_ViewDelta::c_ViewDelta(const client::c_ClientDelta& ClientDelta, const domain::c_DeltaIndex& TargetDeltaIndex)
				:  client::c_ClientDelta(ClientDelta)
				  ,m_TargetDeltaIndex(TargetDeltaIndex)
			{

			}

			c_SEPSI::c_SEPSI(boost::shared_ptr<domain::c_EvolutionManager> pEvolutionManager)
				: m_pEvolutionManager(pEvolutionManager)
			{

			}

			void c_SEPSI::initAddM(const c_MIVPath& MIVPath,const view::c_TypePath& TypePath) {
				c_MIVPath target_miv_path = MIVPath.getParentPath();
				c_ViewM::shared_ptr pViewM = this->getViewM(MIVPath);
				if (pViewM) {
					// OK, we have the target
					this->m_pEvolutionManager->initAddM(MIVPath,pViewM->m_state_index,TypePath);
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Target path \"");
					sMessage += MIVPath.toString<c_LogString>();
					sMessage += _UTF8sz("\" does not exist.");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			c_ViewM::shared_ptr c_SEPSI::getViewM(const c_MIVPath& MIVPath) {
				c_ViewM::shared_ptr result;
                LOG_NOT_IMPLEMENTED;
				return result;
            }

			c_View::c_View(boost::shared_ptr<domain::c_EvolutionManager> pEvolutionManager)
				: m_pEvolutionManager(pEvolutionManager)
			{

			}

			void c_View::initAddM(const c_MIVPath& MIVPath,const view::c_TypePath& TypePath) {
				this->getSEPSI()->initAddM(MIVPath,TypePath);
			}

			c_SEPSI::shared_ptr c_View::getSEPSI() {
				if (!m_pSEPSI) {
					m_pSEPSI = boost::make_shared<c_SEPSI>(m_pEvolutionManager);
				}
				return m_pSEPSI;
			}

		}

		namespace domain {

			c_DomainDelta::c_DomainDelta(const view::c_ViewDelta& ViewDelta, const domain::c_DeltaIndex& DeltaIndex)
				:  view::c_ViewDelta(ViewDelta)
				  ,m_DeltaIndex(DeltaIndex)
			{

            }

			void c_EvolutionManager::addView(boost::shared_ptr<view::c_View> pView) {
				m_Views.push_back(pView);
			}

			void c_EvolutionManager::initAddM(const c_MIVPath& MIVPath,const c_DeltaIndex& target_index,const view::c_TypePath& TypePath) {
				LOG_NOT_IMPLEMENTED;
			}

			void c_EvolutionManager::process() {
				LOG_NOT_IMPLEMENTED;
			}
		}


		void test() {
			domain::c_EvolutionManager::shared_ptr pEvolutionManager(new domain::c_EvolutionManager());

			view::c_View::shared_ptr pView1(new view::c_View(pEvolutionManager));
			pEvolutionManager->addView(pView1);

			view::c_View::shared_ptr pView2(new view::c_View(pEvolutionManager));
			pEvolutionManager->addView(pView2);

			pView1->initAddM(c_MIVPath::fromString(c_DarwinetString("root.myInt")),c_MIVPath::fromString(c_DarwinetString("darwinet.integer")));
			pView1->initAddM(c_MIVPath::fromString(c_DarwinetString("root.myClass")),c_MIVPath::fromString(c_DarwinetString("darwinet.class")));
			pView1->initAddM(c_MIVPath::fromString(c_DarwinetString("root.myClass.myInt")),c_MIVPath::fromString(c_DarwinetString("darwinet.integer")));

			pEvolutionManager->process();
		}
	}

	namespace miv2 {

		namespace view {

			c_SEPSI::c_SEPSI(boost::shared_ptr<delta::c_EvolutionManager> pEvolutionManager)
				: m_pEvolutionManager(pEvolutionManager)
			{

				m_DataTypes.insert(std::make_pair(view::c_MIVPath::fromString(c_DarwinetString("type.integer")),type::c_DataType(type::eDataType_Integer)));
				m_DataTypes.insert(std::make_pair(view::c_MIVPath::fromString(c_DarwinetString("type.string")),type::c_DataType(type::eDataType_String)));
				m_DataTypes.insert(std::make_pair(view::c_MIVPath::fromString(c_DarwinetString("type.array")),type::c_DataType(type::eDataType_Array)));
				m_DataTypes.insert(std::make_pair(view::c_MIVPath::fromString(c_DarwinetString("type.class")),type::c_DataType(type::eDataType_Class)));

				c_MIVPath root_path = c_MIVPath::fromString(c_DarwinetString("root"));
				delta::c_DeltaIndex root_index(0);
				m_Ms.insert(std::make_pair(
					 root_path
					,boost::make_shared<c_M>(root_path,root_index,type::c_DataType(type::eDataType_Class))
				));
			}

			c_M::shared_ptr c_SEPSI::getM(const c_MIVPath& miv_path) {
				c_M::shared_ptr result;
				c_Ms::const_iterator iter = m_Ms.find(miv_path);
				if (iter != m_Ms.end()) {
					result = iter->second;
				}
				return result;
			}

			void c_SEPSI::initiateMAdd(const view::c_MIVPath& miv_path,const view::c_MIVPath& type_path) {
				LOG_METHOD_SCOPE;
				view::c_MIVPath target_path = miv_path.getParentPath();
				c_M::shared_ptr pTargetM = this->getM(target_path);
				if (pTargetM) {
					// OK, the target exists
					delta::c_DeltaIndex target_index = pTargetM->m_state_index ;
					delta::c_DeltaIndex dummy_state_index(0);
					this->m_pEvolutionManager->initiateMAdd(
						 delta::edDir_Add
						,target_index
						,boost::make_shared<view::c_M>(
							 miv_path
							,dummy_state_index
							,this->getTypeOf(type_path)));
				}
			}

			void c_SEPSI::initiateMAdd(const c_DarwinetString& sMIVPath,const c_DarwinetString& sTypePath) {
				LOG_METHOD_SCOPE;
				view::c_MIVPath miv_path = view::c_MIVPath::fromString(sMIVPath);
				view::c_MIVPath type_path = view::c_MIVPath::fromString(sTypePath);;
				this->initiateMAdd(miv_path,type_path);
			}

			void c_SEPSI::actOndMIV(delta::c_dMIV::shared_ptr pdMIV) {
				// Delegate to delta to apply its change
				pdMIV->applyToSEPSI(*this);
			}

			type::c_DataType c_SEPSI::getTypeOf(const view::c_MIVPath& type_path) {
				type::c_DataType result;
				c_DataTypes::const_iterator iter = this->m_DataTypes.find(type_path);
				if (iter != this->m_DataTypes.end()) {
					result = iter->second;
				}
				return result;
			}

			c_View::c_View(boost::shared_ptr<delta::c_EvolutionManager> pEvolutionManager)
				: m_pEvolutionManager(pEvolutionManager)
			{
			}

			c_SEPSI::shared_ptr c_View::getSEPSI() {
				if (!this->m_pSEPSI) {
					this->m_pSEPSI = boost::make_shared<c_SEPSI>(this->m_pEvolutionManager);
				}
				return this->m_pSEPSI;
			}

			c_MIV::c_MIV(const c_MIVPath& miv_path,const delta::c_DeltaIndex& state_index)
				: m_miv_path(miv_path)
				  ,m_state_index(state_index)
			{

			}

			namespace type {
				c_DataType::c_DataType(type::e_DataType data_type)
					: m_data_type(data_type)
				{

				}
			}

			c_M::c_M(const c_MIVPath& miv_path,const delta::c_DeltaIndex& state_index,const type::c_DataType& DataType)
				:  c_MIV(miv_path,state_index)
				  ,m_DataType(DataType)
			{

			}

		}

		namespace delta {

			c_IndexFactory::c_IndexFactory(c_DeltaIndex branch,t_IndexNode seq)
				:  m_branch(branch)
				  ,m_seq(seq)
			{
			}

			c_DeltaIndex c_IndexFactory::currentIndex() {
				c_DeltaIndex result(m_branch);
				result += m_seq;
				return result;
			}

			c_DeltaIndex c_IndexFactory::nextIndex() {
				c_DeltaIndex result(m_branch);
				result += (++m_seq);
				return result;
			}

			c_dMIV::c_dMIV(e_dDir dDir,const c_DeltaIndex& target_index,view::c_MIVPath target_miv_path,const c_DeltaIndex& index)
				:  m_dDir(dDir)
				  ,m_target_index(target_index)
				  ,m_target_miv_path(target_miv_path)
				  ,m_index(index)
			{

			}

			c_dM::c_dM(e_dDir dDir,const c_DeltaIndex& target_index,const c_DeltaIndex& index,boost::shared_ptr<view::c_M> pM)
				:  c_dMIV(dDir,target_index,pM->m_miv_path.getParentPath(),index)
				  ,m_pM(pM)
			{

			}

			// Begin c_dMIV

			void c_dM::applyToSEPSI(view::c_SEPSI& sepsi) {
				LOG_METHOD_SCOPE;
				view::c_M::shared_ptr pTargetM = sepsi.getM(this->m_target_miv_path);
				if (pTargetM) {
					// We have the target ok.
					if (pTargetM->m_state_index == this->m_target_index) {
						// OK. We may apply the delta
						switch (this->m_dDir) {
							case edDir_Undefined:
							break;
							case edDir_Add: {
								c_LogString sMessage;
								sMessage += c_LogStringilizer::toLogCaption(*pTargetM);
								sMessage += _UTF8sz(" += ");
								sMessage += c_LogStringilizer::toLogCaption(*this);

								sepsi.m_Ms.insert(std::make_pair(this->m_pM->m_miv_path,this->m_pM));
								pTargetM->m_state_index = this->m_index;

								sMessage += _UTF8sz(" := ");
								sMessage += c_LogStringilizer::toLogCaption(*pTargetM);
								LOG_BUSINESS(sMessage);
							}
							break;
							case edDir_Remove:
							break;
							case edDir_Unknown:
							break;
						default:
							;
						}

					}
					else {
						c_LogString sMessage(__FUNCTION__" failed. State index=\"");
						sMessage += pTargetM->m_state_index.toString<c_LogString>();
						sMessage += _UTF8sz(" differs from target index=\"");
						sMessage += this->m_target_index.toString<c_LogString>();
						sMessage += _UTF8sz("\". Delta not applied!");
						LOG_DESIGN_INSUFFICIENCY(sMessage);
					}

				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Target=\"");
					sMessage += this->m_target_miv_path.toString<c_LogString>();
					sMessage += _UTF8sz("\" does not exist.");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			// End c_dMIV


			c_dMIVs::c_dMIVs()
			{

			}

			bool c_dMIVs::dontExist(const delta::c_dMIV& dMIV) {
				bool result = true;
				const_iterator iter = this->find(dMIV.m_index);
				if (iter != this->end()) {
					result = iter->second;
				}
				return result;
			}

			void c_EvolutionManager::addView(view::c_View::shared_ptr pView) {
				this->m_Views.push_back(pView);
			}

			void c_EvolutionManager::initiateMAdd(e_dDir dDir,const c_DeltaIndex& target_index,boost::shared_ptr<view::c_M> pM) {
				LOG_METHOD_SCOPE;
				c_dM::shared_ptr pdM(new c_dM(
					// e_dDir dDir,const c_DeltaIndex& target_index,const c_DeltaIndex& index,boost::shared_ptr<view::c_M> pM
					 dDir
					,target_index
					,m_IndexFactory.nextIndex()
					,pM
				));
				this->addToInQueue(pdM);
				this->processInQueue();
			}

			void c_EvolutionManager::addToInQueue(delta::c_dMIV::shared_ptr pdMIV) {
				this->m_dMIVQueue.push(pdMIV);
			}

			void c_EvolutionManager::processInQueue() {
				while (!this->m_dMIVQueue.empty()) {
					delta::c_dMIV::shared_ptr pdMIV = this->m_dMIVQueue.front();
					this->m_dMIVQueue.pop();
					this->processdMIV(pdMIV);
				}
			}

			void c_EvolutionManager::processdMIV(delta::c_dMIV::shared_ptr pdMIV) {
				if (this->m_dMIVs.dontExist(*pdMIV)) {
					this->m_dMIVs.insert(std::make_pair(pdMIV->m_index,pdMIV));

					for (c_Views::iterator iter = m_Views.begin(); iter != m_Views.end(); ++iter) {
						(*iter)->getSEPSI()->actOndMIV(pdMIV);
					}
				}
				else {
					// We have already received and processed this delta. Skip it!
					c_LogString sMessage("Skipped redundant ");
					sMessage += c_LogStringilizer::toLogCaption(*pdMIV);
					LOG_BUSINESS(sMessage);
				}
			}

		}

		c_LogString c_LogStringilizer::toLogCaption(const delta::c_dMIV& dMIV) {
			c_LogString sMessage;
			sMessage += dMIV.m_index.toString<c_LogString>();
			sMessage += _UTF8sz(":dMIV[");
			sMessage += dMIV.m_target_miv_path.toString<c_LogString>();
			sMessage += _UTF8sz(",");
			sMessage += dMIV.m_target_index.toString<c_LogString>();
			sMessage += _UTF8sz("]");
			return sMessage;
		}

		c_LogString c_LogStringilizer::toLogCaption(const delta::c_dM& dM) {
			c_LogString sMessage;
			sMessage += dM.m_index.toString<c_LogString>();
			sMessage += _UTF8sz(":dM[");
			sMessage += dM.m_target_miv_path.toString<c_LogString>();
			sMessage += _UTF8sz(",");
			sMessage += dM.m_target_index.toString<c_LogString>();
			sMessage += _UTF8sz("] + ");
			sMessage += c_LogStringilizer::toLogCaption(*(dM.m_pM));
			return sMessage;
		}
		c_LogString c_LogStringilizer::toLogCaption(const view::type::c_DataType& DataType) {
			c_LogString result = c_LogString("??") + c_DataRepresentationFramework::intToDecimalString(DataType.m_data_type) + c_LogString("??");
			switch (DataType.m_data_type) {
				case view::type::eDataType_Undefined: result = _UTF8sz("Undefined"); break;
				case view::type::eDataType_Integer: result = _UTF8sz("Integer"); break;
				case view::type::eDataType_String: result = _UTF8sz("String"); break;
				case view::type::eDataType_Array: result = _UTF8sz("Array"); break;
				case view::type::eDataType_Class: result = _UTF8sz("Class"); break;
				case view::type::eDataType_Unknown: result = _UTF8sz("Unknown"); break;
			default:
				;
			}
			return result;
		}
		c_LogString c_LogStringilizer::toLogCaption(const view::c_M& M) {
			c_LogString sMessage;
			sMessage += _UTF8sz("M[");
			sMessage += M.m_miv_path.toString<c_LogString>();
			sMessage += _UTF8sz(",");
			sMessage += M.m_state_index.toString<c_LogString>();
			sMessage += _UTF8sz("] ");
			sMessage += c_LogStringilizer::toLogCaption(M.m_DataType);
			return sMessage;
		}

		void test() {
			LOG_FUNCTION_SCOPE;
			delta::c_EvolutionManager::shared_ptr pEvolutionManager(new delta::c_EvolutionManager());
			view::c_View::shared_ptr pView1(new view::c_View(pEvolutionManager));
			pEvolutionManager->addView(pView1);

			view::c_View::shared_ptr pView2(new view::c_View(pEvolutionManager));
			pEvolutionManager->addView(pView2);

			pView1->getSEPSI()->initiateMAdd(c_DarwinetString("root.myInt"),c_DarwinetString("type.integer"));
			pView1->getSEPSI()->initiateMAdd(c_DarwinetString("root.myClass"),c_DarwinetString("type.class"));
			pView1->getSEPSI()->initiateMAdd(c_DarwinetString("root.myClass.myInt"),c_DarwinetString("type.integer"));
			pView1->getSEPSI()->initiateMAdd(c_DarwinetString("root.myClass"),c_DarwinetString("type.class"));
		}
	}

	namespace miv1 {

		c_MIVId::c_MIVId(unsigned int raw_id) // TODO, Change to GUID
			: m_raw_id(raw_id)
		{

		}

		c_UserID::c_UserID(unsigned int raw_id) // TODO, Change to GUID
			: m_raw_id(raw_id)
		{

		}

		c_DataObjectModelType::c_DataObjectModelType(e_DataObjectModelType DataObjectModelType)
			: m_DataObjectModelType(DataObjectModelType)
		{

		}

		c_Cardinality::c_Cardinality(unsigned int min_no_instances,unsigned int max_no_instances)
			:  m_min_no_instances(min_no_instances)
			  ,m_max_no_instances(max_no_instances)
		{

		}

		c_DataObjectModelInstanceConstraints::c_DataObjectModelInstanceConstraints(const c_Cardinality& cardinality)
			: m_cardinality(cardinality)
		{

		}

		c_ModelMember::~c_ModelMember() {

        }

		c_DataObjectModel::c_DataObjectModel(const c_DataObjectModelType& DataObjectModelType,const c_DataObjectModelInstanceConstraints& DataObjectModelInstanceConstraints)
			:  m_DataObjectModelType(DataObjectModelType)
			  ,m_DataObjectModelInstanceConstraints(DataObjectModelInstanceConstraints)
		{

		}

		namespace delta {
			c_ModelDelta::c_ModelDelta(e_DeltaDirection DeltaDirection,const c_ModelPath& target_path)
				:  m_DeltaDirection(DeltaDirection)
				  ,m_target_path(target_path)
			{

			}

			// Begin c_Delta

			void c_ModelDelta::applyToMIV(c_MIV& miv) const {
				miv.m_Model += *this;
			}

			// End c_Delta


			c_DataObjectModelInstanceDelta::c_DataObjectModelInstanceDelta(e_DeltaDirection DeltaDirection,const c_ModelPath& member_path,c_ModelMember::shared_ptr pMember)
				:  c_ModelDelta(DeltaDirection,member_path.getParentPath())
				  ,m_member_name(member_path.back())
				  ,m_pMember(pMember)
			{

			}

			// Begin c_ModelDelta

			void c_DataObjectModelInstanceDelta::applyToModel(c_Model& model) const {

				c_ModelMember::shared_ptr pTargetMember;
				c_ModelMembers::const_iterator iter = model.m_ModelMembers.find(m_target_path);
				if (iter != model.m_ModelMembers.end()) {
					pTargetMember = iter->second;
				}

				if (pTargetMember) {
					// The target data model object exists ok.
					c_DataObjectModel::shared_ptr pDataObjectModelTarget = boost::dynamic_pointer_cast<c_DataObjectModel>(pTargetMember);
					if (pDataObjectModelTarget) {
						// We have a target data object model
						{
							c_LogString sMessage(__FUNCTION__", Check of data model target type is not yet implemented. delta always applied.");
							LOG_DESIGN_INSUFFICIENCY(sMessage);
						}
						c_ModelPath model_path(m_target_path);
						model_path += m_member_name;
						model.m_ModelMembers.insert(std::make_pair(model_path,m_pMember));
						{
							c_LogString sMessage("dM: ");
							sMessage += m_target_path.toString<c_LogString>();
							sMessage += _UTF8sz(" += ");
							sMessage += m_member_name; // works as long as sMessage and m_member_name are of same string encoding
							LOG_BUSINESS(sMessage);
						}
					}
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Target member \"");
					sMessage += m_target_path.toString<c_LogString>();
					sMessage += _UTF8sz("\" does not exist.");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			// End c_ModelDelta


			c_DeltaSignalSource::c_DeltaSignalSource(const c_MIVId& MIV_Id,const c_UserID& User_Id)
				:  m_MIV_Id(MIV_Id)
				  ,m_User_Id(User_Id)
			{

			}

		}

		c_Model::c_Model()
			: m_ModelMembers()
		{
			// We alwyas need "root" record in the model
			m_ModelMembers.insert(
				std::make_pair(
					 c_ModelPath::fromString(c_DarwinetString("root"))
					,boost::make_shared<c_DataObjectModel>(
						c_DataObjectModelType(eDataObjectModelType_Record)
					)
				)
			);
		}

		void c_Model::operator+=(const delta::c_ModelDelta& ModelDelta) {
			// Delegate to delta to operate on us.
			ModelDelta.applyToModel(*this);
        }

		void c_MIV::operator+=(const delta::c_Delta& Delta) {
			// Delagate application to c_DeltaSignal
			Delta.applyToMIV(*this);
		}

		namespace delta {
			c_DeltaSignal::c_DeltaSignal(const c_DeltaSignalSource& source,const c_DeltaIndex& target_index, c_Delta::shared_ptr pDelta)
				:  m_source(source)
				  ,m_target_index(target_index)
				  ,m_pDelta(pDelta)
			{

			}

			void c_DeltaSignal::applyToMIV(c_MIV& miv) const {
				c_LogString sMessage;
				sMessage += this->m_target_index.toString<c_LogString>();
				sMessage += _UTF8sz(":dM:");
				LOG_BUSINESS(sMessage);
				LOG_NOT_IMPLEMENTED;
			}


			c_DeltaSignalFactory::c_DeltaSignalFactory(const c_DeltaSignalSource& DeltaSignalSource)
				:  m_DeltaSignalSource(DeltaSignalSource)
				  ,m_current_delta_index(0)
			{

			}

			c_DeltaSignal::shared_ptr c_DeltaSignalFactory::createDeltaSignal(c_Delta::shared_ptr pDelta) {
				c_DeltaSignal::shared_ptr result = boost::make_shared<c_DeltaSignal>(m_DeltaSignalSource,m_current_delta_index,pDelta);
				m_current_delta_index.back()++; // Increment index
				return result;
			}

			c_MIVController::c_MIVController(c_MIV::shared_ptr pMIV)
				: m_pMIV(pMIV)
			{

			}

			void c_MIVController::operator+=(const c_DeltaSignal& DeltaSignal) {
				{
					c_LogString sMessage(__FUNCTION__", Check of c_DeltaSignal index not yet implemented. Delta always applied");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
				*m_pMIV += *DeltaSignal.m_pDelta;
			}

			void c_DeltaManager::addMIV(c_MIV::shared_ptr pMIV) {
				m_MIVControllers.push_back(boost::make_shared<c_MIVController>(pMIV));
			}

			void c_DeltaManager::operator+=(const c_DeltaSignal& DeltaSignal) {
				for (c_MIVControllers::const_iterator iter = m_MIVControllers.begin(); iter != m_MIVControllers.end(); ++iter) {
					**iter += DeltaSignal;
				}
			}

		}

		/**
		  * Dummy to access our c_DeltaSignalSource unti proper impl. is in place
		  */
		const delta::c_DeltaSignalSource& getDeltaSource() {
			static delta::c_DeltaSignalSource DeltaSignalSource(c_MIVId(1),c_UserID(1)); // dummy. MIV 1 and User 1.
			return DeltaSignalSource;
		}

		void test() {
			LOG_FUNCTION_SCOPE;
			c_MIV::shared_ptr pMIV = boost::make_shared<c_MIV>();
			delta::c_DeltaManager::shared_ptr pDeltaManager(new delta::c_DeltaManager());
			pDeltaManager->addMIV(pMIV);

			delta::c_DeltaSignalFactory::shared_ptr pDeltaSignalFactory(new delta::c_DeltaSignalFactory());

			delta::c_DeltaSignals::shared_ptr pDeltaSignals = boost::make_shared<delta::c_DeltaSignals>();
			pDeltaSignals->push_back(
				pDeltaSignalFactory->createDeltaSignal(
					boost::make_shared<delta::c_DataObjectModelInstanceDelta>(
						delta::eDeltaDirection_Add
						,c_ModelPath::fromString<c_DarwinetString>(c_DarwinetString("root.myInteger"))
						,boost::make_shared<c_DataObjectModel>(c_DataObjectModelType(eDataObjectModelType_Integer),c_DataObjectModelInstanceConstraints())
					)
				)
			);
			for (delta::c_DeltaSignals::const_iterator iter = pDeltaSignals->begin(); iter != pDeltaSignals->end(); ++iter) {
				*pDeltaManager += **iter; // update miv with delta
			}
		}

	}

	namespace integrate3 {
		// The namespace integrate2 failed short in defining a recursive data model.
		// Here we will try for a data model using ascociations.

		c_Aggregation::c_Aggregation(c_ModelPath::shared_ptr_const pModelPath)
			:  m_pModelPath(pModelPath)
		{

		}

		namespace delta {

			c_DeltaM::c_DeltaM(c_ModelPath::shared_ptr pTargetPath)
				: m_pTargetPath(pTargetPath)
			{

			}

			c_DeltaAggregation::c_DeltaAggregation(c_ModelPath::shared_ptr pTargetPath,c_ModelPath::Node id, c_Aggregation::shared_ptr_const pAggregation)
				:  c_DeltaM(pTargetPath)
				  ,m_id(id)
				  ,m_pAggregation(pAggregation)
			{

			}

			void c_DeltaAggregation::applyTo(c_MIV& miv) const {
				// get the target member
				c_AssociationList::shared_ptr pAssociationList = miv.getAssociationList(this->m_pTargetPath).lock();
				if (pAssociationList) {
					// The target exists
					pAssociationList->insert(std::make_pair(this->m_id,this->m_pAggregation));
					c_LogString sMessage("dM:");
					sMessage += this->m_pTargetPath->toString<c_LogString>();
					sMessage += _UTF8sz("+=");
					sMessage += m_id; // Works as c_LogString is compatible to c_CaptionNode
					LOG_BUSINESS(sMessage);
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Unable to find parent model = ");
					sMessage += this->m_pTargetPath->toString<c_LogString>();
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			c_Delta::shared_ptr c_DeltaFactory::createDeltaAggregation(const std::string& sMemberPath,const std::string& sModelPath) {
				c_Delta::shared_ptr result;
				c_ModelPath member_path = c_ModelPath::fromString(c_DarwinetString(sMemberPath));
				c_ModelPath::shared_ptr pTargetPath(new c_ModelPath(member_path.getParentPath()));
				c_ModelPath::shared_ptr pModelPath(new c_ModelPath(c_ModelPath::fromString(c_DarwinetString(sModelPath))));
				c_Aggregation::shared_ptr pAggregation(new c_Aggregation(pModelPath));
				c_DeltaAggregation::shared_ptr pDeltaAggregation(new c_DeltaAggregation(pTargetPath,member_path.back(),pAggregation));
				result = pDeltaAggregation;
				return result;
			}

		}

		c_MIV::c_MIV()
			: m_pAssociationLists(boost::make_shared<c_AssociationLists>())
		{
			m_pAssociationLists->insert(std::make_pair(c_ModelPath::fromString(c_DarwinetString("root")),boost::make_shared<c_AssociationList>()));
		}

		void c_MIV::operator+=(const delta::c_Delta& delta) {
			// delegate to delta to do its stuff on us.
			delta.applyTo(*this);
		}

		c_AssociationList::weak_ptr c_MIV::getAssociationList(c_ModelPath::shared_ptr_const pTargetPath) {
			c_AssociationList::weak_ptr result;
			if (m_pAssociationLists) {
				result = (*m_pAssociationLists)[*pTargetPath];
			}
			return result;
		}

		void test() {
			LOG_FUNCTION_SCOPE;
			c_MIV::shared_ptr pMIV(new c_MIV());
			delta::c_Deltas::shared_ptr pDeltas(new delta::c_Deltas());
			delta::c_DeltaFactory::shared_ptr pDeltaFactory(new delta::c_DeltaFactory);
			pDeltas->push_back(pDeltaFactory->createDeltaAggregation("root.myInt","darwinet.integer"));

			/**
			  * No, this still does not feel good. There is still something not right with how we represent the
			  * data model.
			  */

			for (delta::c_Deltas::const_iterator iter = pDeltas->begin(); iter != pDeltas->end(); ++iter) {
				*pMIV += **iter;
			}

		}
	}

	namespace integrate2 {
		// The namespace integrate failed short on a number of requirements.
		// Lets start over again with integrate2

		c_Model::c_Model(e_Type type)
			: m_type(type)
		{

		}

		e_Type c_Model::type() {
			return m_type;
		}


		c_IntValue::c_IntValue()
			: m_raw_value(INT_INIT_VALUE)
		{

		}

		void c_IntValue::applyDeltaV(const delta::c_IntAdd& delta) {
			m_raw_value += delta.m_raw_delta;
		}

		int c_IntValue::raw_value() {
			return m_raw_value;
        }


		c_Object::c_Object(e_Type type,const c_ModelPath& model_path)
			:  m_type(type)
			  ,m_model_path(model_path)
			  ,m_pVariantValue()
		{

		}

		const c_ModelPath& c_Object::getModelPath() {
			return m_model_path;
		}

		c_VariantValuePtr c_Object::getVariantValue() {
			if (!m_pVariantValue) {
				switch (m_type) {
					case eType_Undefined:
						LOG_DESIGN_INSUFFICIENCY(c_LogString(__FUNCTION__" failed. type = eType_Undefined"));
					break;
					case eType_Int:
						m_pVariantValue = boost::make_shared<c_VariantValue>(c_IntValue());
					break;
					case eType_String:
						m_pVariantValue = boost::make_shared<c_VariantValue>(c_StringValue());
					break;
					case eType_Record:
						m_pVariantValue = boost::make_shared<c_VariantValue>(c_RecordValue());
					break;
					case eType_Array:
						m_pVariantValue = boost::make_shared<c_VariantValue>(c_ArrayValue());
					break;
					case eType_Unknown:
						LOG_DESIGN_INSUFFICIENCY(c_LogString(__FUNCTION__" failed. type = eType_Unknown"));
					break;
				default:
					;
				}
			}
			return m_pVariantValue;
		}

		namespace delta {


			c_DeltaM::c_DeltaM(const c_ModelPath& target_path)
				: c_Delta()
				  ,m_target_path(target_path)
			{
			}

			c_AddModel::c_AddModel(const c_ModelPath& model_path,const c_Model& model)
				:  c_DeltaM(model_path.getParentPath())
				  ,m_memberId(model_path.back())
				  ,m_model(model)
			{
			}

			void c_AddModel::applyTo(c_MIV& miv) const {
				// Check that parent exists
				// Then create new model member
				c_Model::shared_ptr pParentModel = miv.m_models[this->m_target_path];
				if (pParentModel) {
					// OK, create the member
					c_ModelPath model_path = this->m_target_path;
					model_path += m_memberId;
					miv.m_models.insert(std::make_pair(model_path,boost::make_shared<c_Model>(this->m_model)));
					c_LogString sMessage("dM:");
					sMessage += this->m_target_path.toString<c_LogString>();
					sMessage += _UTF8sz("+=");
					sMessage += m_memberId; // Works as c_LogString is compatible to c_CaptionNode
					LOG_BUSINESS(sMessage);
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Unable to find parent model = ");
					sMessage += this->m_target_path.toString<c_LogString>();
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

		}

		namespace delta {


			c_DeltaIV::c_DeltaIV(const c_InstancePath& target_path)
				: m_target_path(target_path)
			{
			}

			c_DeltaI::c_DeltaI(const c_InstancePath& target_path)
				: c_DeltaIV(target_path)
			{

            }


			c_CreateInstance::c_CreateInstance(const c_InstancePath& instance_path)
				:  c_DeltaI(instance_path.getParentPath())
				  ,m_memberId(instance_path.back())
			{
			};

			// Begin c_Delta

			void c_CreateInstance::applyTo(c_MIV& miv) const {
				// Check that parent object exists
				c_Object::shared_ptr pParentObject = miv.m_objects[this->m_target_path];
				if (pParentObject) {
					// Now get the model to use for the new member object
					c_ModelPath model_path = pParentObject->getModelPath();
					model_path += m_memberId;
					c_Model::shared_ptr pModel = miv.m_models[model_path];
					if (pModel) {
						// Ok, the model is defined
						c_InstancePath instance_path = this->m_target_path;
						instance_path += m_memberId;
						miv.m_objects.insert(std::make_pair(instance_path,boost::make_shared<c_Object>(pModel->type(),model_path)));
						c_LogString sMessage("dI:");
						sMessage += this->m_target_path.toString<c_LogString>();
						sMessage += _UTF8sz("+=");
						sMessage += m_memberId; // Works as c_LogString is compatible to c_CaptionNode
						LOG_BUSINESS(sMessage);
					}
					else {
						c_LogString sMessage(__FUNCTION__" failed. Unable to find object model = ");
						sMessage += model_path.toString<c_LogString>();
						LOG_DESIGN_INSUFFICIENCY(sMessage);
					}
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Unable to find parent object = ");
					sMessage += this->m_target_path.toString<c_LogString>();
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			// End c_Delta


			c_DeltaV::c_DeltaV(const c_InstancePath& target_path)
				: c_DeltaIV(target_path)
			{

			}

			c_IntAdd::c_IntAdd(const c_InstancePath& target_path,int raw_delta)
				:  c_DeltaV(target_path)
				  ,m_raw_delta(raw_delta)
			{

			}

			// Begin c_Delta

			void c_IntAdd::applyTo(c_MIV& miv) const {
				c_Object::shared_ptr pObject = miv.m_objects[this->m_target_path];
				if (pObject) {
					// Apply to Integer value
					boost::get<c_IntValue>(*pObject->getVariantValue()).applyDeltaV(*this);
					c_LogString sMessage("dV:");
					sMessage += this->m_target_path.toString<c_LogString>();
					sMessage += _UTF8sz("+=");
					sMessage += c_DataRepresentationFramework::intToDecimalString(this->m_raw_delta);
					sMessage += _UTF8sz(" == ");
					sMessage += c_DataRepresentationFramework::intToDecimalString(boost::get<c_IntValue>(*pObject->getVariantValue()).raw_value());
					LOG_BUSINESS(sMessage);
				}
				else {
					c_LogString sMessage(__FUNCTION__" failed. Unable to find object = ");
					sMessage += this->m_target_path.toString<c_LogString>();
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			}

			// End c_Delta

		}

		c_MIV::c_MIV()
			:  m_models()
			  ,m_objects()
		{
			c_ModelPath model_path = c_ModelPath::fromString(c_DarwinetString("root"));
			m_models.insert(std::make_pair(model_path,boost::make_shared<c_Model>(eType_Record)));
			m_objects.insert(std::make_pair(c_InstancePath::fromString(c_DarwinetString("root")),boost::make_shared<c_Object>(eType_Record,model_path)));
		}

		void c_MIV::operator+=(const delta::c_Delta& delta) {
			// Delegate to specialization
			delta.applyTo(*this);
		}

		void test() {
			LOG_FUNCTION_SCOPE;
			c_MIV::shared_ptr pMIV(new c_MIV());
			delta::c_Deltas::shared_ptr pDeltas(new delta::c_Deltas());
			pDeltas->push_back(boost::make_shared<delta::c_AddModel>(c_ModelPath::fromString(c_DarwinetString("root.myInt")),c_Model(eType_Int)));
			pDeltas->push_back(boost::make_shared<delta::c_CreateInstance>(c_InstancePath::fromString(c_DarwinetString("root.myInt"))));
			pDeltas->push_back(boost::make_shared<delta::c_IntAdd>(c_InstancePath::fromString(c_DarwinetString("root.myInt")),4));
			pDeltas->push_back(boost::make_shared<delta::c_IntAdd>(c_InstancePath::fromString(c_DarwinetString("root.myInt")),2));
			for (delta::c_Deltas::const_iterator iter = pDeltas->begin(); iter != pDeltas->end(); ++iter) {
				*pMIV += **iter;
			}
		}
	}

	namespace integrate {


		/**
		  * Create a delta reporting creation of a new object instance
		  * with provided darwinet::c_InstancePath and of type defined
		  * by provided darwinet::c_ModelPath
		  */
		c_CreateIntInstanceDelta::c_CreateIntInstanceDelta(const darwinet::c_InstancePath& InstancePath,const darwinet::c_ModelPath& ModelPath)
			:  m_InstancePath(InstancePath)
			  ,m_ModelPath(ModelPath)
		{

		}

		// Begin c_Delta

		/**
		  * Apply "us" to provided c_MIV
		  */
		void c_CreateIntInstanceDelta::applyTo(c_MIV& miv) const {
			c_VariantObjectInstancePtr pVariantObjectInstance = miv.getInstance(this->getTargetInstancePath());
			if (pVariantObjectInstance) {
				boost::get<c_ObjectInstance>(*pVariantObjectInstance) += *this;
			}
			else {
				// Received a Delta to an instance that does not exist!
				// This is a design insufficiency.
				c_LogString sMessage(__FUNCTION__" failed. Provided Delta refers to an instance we could not find. Target = \"");
				sMessage += this->getTargetInstancePath().toString<c_LogString>();
				sMessage += _UTF8sz("\"");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

		// End c_Delta

		const darwinet::c_InstancePath& c_CreateIntInstanceDelta::getInstancePath() const {
			return this->m_InstancePath;
        }


		const darwinet::c_InstancePath c_CreateIntInstanceDelta::getTargetInstancePath() const {
			// The instance we create must define at least the object identifier.
			// If instance path is only the root obejct idenitifer then parent path is empty.
			// AN excpetion here means we are trying to create an object with no identitier (design insufficiency)
			return m_InstancePath.getParentPath();
		}


		c_ValueDelta::c_ValueDelta()
			: m_pInstancePath(new darwinet::c_InstancePath())
		{

		}

		const darwinet::c_InstancePath& c_ValueDelta::getTargetInstancePath() const {
			return *m_pInstancePath;
		}

		/**
		  * Creates a c_IntValueDelta from provided raw delta value
		  */
		c_IntValueDelta::c_IntValueDelta(int raw_delta)
			: m_raw_delta(raw_delta)
		{
		};

		// Begin c_Delta

		/**
		  * Apply "us" to provided c_MIV
		  */
		void c_IntValueDelta::applyTo(c_MIV& miv) const {
			c_VariantObjectInstancePtr pVariantObjectInstance = miv.getInstance(this->getTargetInstancePath());
			if (pVariantObjectInstance) {
				boost::get<c_IntObjectInstance>(*pVariantObjectInstance) += *this;
			}
			else {
				// Received a Delta to an instance that does not exist!
				// This is a design insufficiency.
				c_LogString sMessage(__FUNCTION__" failed. Provided Delta refers to an instance we could not find. Target = \"");
				sMessage += this->getTargetInstancePath().toString<c_LogString>();
				sMessage += _UTF8sz("\"");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

		/**
		  * Apply us to raw value
		  */
		void c_IntValueDelta::applyTo(int& raw_value) const {
			raw_value += m_raw_delta;
		}


		// End c_Delta

		c_ObjectInstance::c_ObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap)
			: m_pVariantObjectInstancesMap(pVariantObjectInstancesMap)
		{

		}

		void c_ObjectInstance::operator+=(const c_CreateIntInstanceDelta& delta) {
			// Create an c_IntObjectInstance
			c_VariantObjectInstancePtr pVariantObjectInstancePtr(new c_VariantObjectInstance());
			*pVariantObjectInstancePtr = c_IntObjectInstance(this->getInstanceMap());
			this->getInstanceMap()->insert(std::make_pair(delta.getInstancePath(),pVariantObjectInstancePtr));
			// createInstance();
		}

		c_VariantObjectInstancesMap::shared_ptr c_ObjectInstance::getInstanceMap() {
			return this->m_pVariantObjectInstancesMap;
		}

		c_IntObjectInstance::c_IntObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap,int raw_value)
			:  c_ObjectInstance(pVariantObjectInstancesMap)
			  ,m_raw_value(raw_value)
		{
		}

		void c_IntObjectInstance::operator+=(const c_IntValueDelta& delta) {
			delta.applyTo(m_raw_value);
		}

		c_StringObjectInstance::c_StringObjectInstance(const c_VariantObjectInstancesMap::shared_ptr& pVariantObjectInstancesMap,darwinet::c_DarwinetString raw_value)
			:  c_ObjectInstance(pVariantObjectInstancesMap)
			  ,m_raw_value(raw_value)
		{

		}

		c_MIV::c_MIV()
			: m_pVariantValuesMap(new c_VariantObjectInstancesMap())
		{

		}

		/**
		  * Applies provided delta to us, updating our state
		  * as defined by the delta.
		  */
		void c_MIV::operator+=(const c_Delta& delta) {
			// Apply the delta to us
			delta.applyTo(*this);
		};

		c_VariantObjectInstancePtr c_MIV::getInstance(const darwinet::c_InstancePath& InstancePath) {
			c_VariantObjectInstancePtr result = (*m_pVariantValuesMap)[InstancePath];
			return result;
		}

		/**
		  * Create a new instance with provided path
		  */
		c_VariantObjectInstancePtr c_MIV::createInstance(const darwinet::c_ModelPath& ModelPath) {
			c_VariantObjectInstancePtr result;
			return result;
		}

		/**
		  * Creates a MIV instance with the state defined by provided
		  * c_MIVEvolutionHistory instance.
		  */
		c_MIV::shared_ptr c_Integrator::integrate(c_MIVEvolutionHistory::shared_ptr pEvolutionHistory) {
			c_MIV::shared_ptr result(new c_MIV());
			for (c_MIVEvolutionHistory::const_iterator iter = pEvolutionHistory->begin(); iter != pEvolutionHistory->end(); ++iter) {
				*result += **iter;
			}
			return result;
		}

		/**
		  * Test this module
		  */
		void test() {
			LOG_FUNCTION_SCOPE;
			c_Integrator::shared_ptr pIntegrator(new c_Integrator());
			c_MIVEvolutionHistory::shared_ptr pMIVEvolutionHistory(new c_MIVEvolutionHistory());
			pMIVEvolutionHistory->push_back(boost::make_shared<c_CreateIntInstanceDelta>(
				 darwinet::c_InstancePath(darwinet::c_DarwinetString("myfirstint:1"))
				,darwinet::c_ModelPath(darwinet::c_DarwinetString("integer"))));
			pMIVEvolutionHistory->push_back(boost::make_shared<c_IntValueDelta>(4));

			c_MIV::shared_ptr pMIV = pIntegrator->integrate(pMIVEvolutionHistory);
		}
	}
}

namespace lessons_learnt {

		class X {
		public:

			X() {
				LOG_METHOD_SCOPE;
			}

			void MemberDoIt(int x) {
				LOG_METHOD_SCOPE;
			}

			boost::function<void (int)> onX;

		};

		void test() {

			{
				// Test of boost function pointer and bind
				// http://www.boost.org/doc/libs/1_34_0/libs/bind/bind.html

				X x;
				/**
				  * Bind to the pointer to instance x.
				  * Note that Bind copies all provided parameters. By providing
				  * the &x pointer the function will be bound to
				  * the x instance.
				  */
				x.onX = boost::bind(&X::MemberDoIt,&x,_1);
				/**
				  * Bind to a copy of x.
				  * Note that Bind copies all provided parameters. By providing
				  * the x reference the function will be bound to
				  * an x copy instance! (not what you want if you want to bind to an existing object instance!)
				  */
				x.onX = boost::bind(&X::MemberDoIt,x,_1);

				x.onX(1);

			}

			{
				// Test of boost function pointer

				{
					X x;
					/**
					  * Bind to the pointer to instance x.
					  * bind copies all provided parameters. By providing
					  * the &x pointer the function will be bound to
					  * the x instance.
					  */
					x.onX = boost::bind(&X::MemberDoIt,&x,_1);

					x.onX(1);
				}
				{
					X x;

					/**
					  * Bind to a copy of x.
					  * bind copies all provided parameters. By providing
					  * the x reference the function will be bound to
					  * an x copy instance!
					  */
					x.onX = boost::bind(&X::MemberDoIt,x,_1);

					x.onX(1);
				}

			}
		}
}

