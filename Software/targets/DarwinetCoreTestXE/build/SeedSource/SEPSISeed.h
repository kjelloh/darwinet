//---------------------------------------------------------------------------

#ifndef SEPSISeedH
#define SEPSISeedH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <vector>
#include <boost/variant.hpp>
#include "DarwinetBase.h"
#include <map>
//---------------------------------------------------------------------------

/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */
namespace seedsrc {

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
		class c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_ObjectInstance> shared_ptr;

			void operator+=(const c_CreateIntInstanceDelta& delta);

		};

		//-------------------------------------------------------------------
		class c_IntObjectInstance : public c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_IntObjectInstance> shared_ptr;

			c_IntObjectInstance::c_IntObjectInstance(int raw_value);

			void operator+=(const c_IntValueDelta& delta);

		private:

			int m_raw_value;

		};

		//-------------------------------------------------------------------
		class c_StringObjectInstance : public c_ObjectInstance {
		public:
			typedef boost::shared_ptr<c_StringObjectInstance> shared_ptr;

		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		typedef boost::variant<c_IntObjectInstance,c_StringObjectInstance> c_VariantObjectInstance;
		typedef boost::shared_ptr<c_VariantObjectInstance> c_VariantObjectInstancePtr;

		class c_VariantObjectInstancesMap : public std::map<darwinet::c_InstancePath,c_VariantObjectInstancePtr> {
		public:
			typedef boost::shared_ptr<c_VariantObjectInstancesMap> shared_ptr;
		};

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


#endif
