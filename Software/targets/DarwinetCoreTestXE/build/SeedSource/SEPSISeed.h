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

	namespace integrate2 {
		// The namespace integrate failed short on a number of requirements.
		// Lets start over again

//		typedef std::string c_DarwinetString;
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

		class c_IntValue {
		};

		class c_StringValue {
		};

		class c_RecordValue {
		};

		class c_ArrayValue {
		};

		typedef boost::variant<c_IntValue,c_StringValue,c_RecordValue, c_ArrayValue> c_VariantValue;

		typedef oprime::c_KeyPath<c_CaptionNode> c_InstancePath;

		class c_Object {
		public:
			typedef boost::shared_ptr<c_Object> shared_ptr;

			c_Object(const c_ModelPath& model_path = c_ModelPath());

			const c_ModelPath& getModelPath();
		private:
			const c_ModelPath m_model_path;
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


#endif
