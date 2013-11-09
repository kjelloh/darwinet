//---------------------------------------------------------------------------

#pragma hdrstop

#include "SEPSISeed.h"
#include "BusinessLogUnit.h"
#include <boost/make_shared.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */
namespace seedsrc {

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
