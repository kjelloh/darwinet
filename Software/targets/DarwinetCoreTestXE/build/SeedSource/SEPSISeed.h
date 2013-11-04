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
		class c_Value {
		public:
			typedef boost::shared_ptr<c_Value> shared_ptr;

		};

		//-------------------------------------------------------------------
		class c_IntValue : public c_Value {
		public:
			typedef boost::shared_ptr<c_IntValue> shared_ptr;

			c_IntValue::c_IntValue(int raw_value);

			void operator+=(const c_IntValueDelta& delta);

		private:

			int m_raw_value;

		};

		//-------------------------------------------------------------------
		class c_StringValue : public c_Value {
		public:
			typedef boost::shared_ptr<c_StringValue> shared_ptr;

		};

		//-------------------------------------------------------------------
		//-------------------------------------------------------------------
		typedef boost::variant<c_IntValue,c_StringValue> c_VariantValue;
		typedef boost::shared_ptr<c_VariantValue> c_VariantValuePtr;

		class c_VariantValuesMap : public std::map<darwinet::c_InstancePath,c_VariantValuePtr> {
		public:
			typedef boost::shared_ptr<c_VariantValuesMap> shared_ptr;
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

			c_VariantValuePtr getInstance(const darwinet::c_InstancePath& InstancePath);

			// End c_MIV

		private:

			c_VariantValuesMap::shared_ptr m_pVariantValuesMap;

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
