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
				LOG_NOT_IMPLEMENTED;
				// Chekk that parent exists
				// Then create new model member
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
				LOG_NOT_IMPLEMENTED;
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
				LOG_NOT_IMPLEMENTED;
            }

			// End c_Delta

		}

		c_MIV::c_MIV()
			:  m_models()
			  ,m_objects()
		{
			m_models.insert(std::make_pair(c_ModelPath("root"),boost::make_shared<c_Model>(eType_Record)));
		}

		void c_MIV::operator+=(const delta::c_Delta& delta) {
			// Delegate to specialization
			delta.applyTo(*this);
		}

		void test() {
			LOG_FUNCTION_SCOPE;
			c_MIV::shared_ptr pMIV(new c_MIV());
			delta::c_Deltas::shared_ptr pDeltas(new delta::c_Deltas());
			pDeltas->push_back(boost::make_shared<delta::c_AddModel>(c_ModelPath("root.myInt"),c_Model(eType_Int)));
			pDeltas->push_back(boost::make_shared<delta::c_CreateInstance>(c_InstancePath("root.myInt")));
			pDeltas->push_back(boost::make_shared<delta::c_IntAdd>(c_InstancePath("root.myInt"),4));
//			*pMIV += delta::c_IntAdd("root.myInt",4);
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
