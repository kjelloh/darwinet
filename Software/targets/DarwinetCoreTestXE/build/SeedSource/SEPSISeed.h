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
//---------------------------------------------------------------------------

/**
  * Seed Source namespace. This is working source that
  * are candiates to become part of the Darwinet framework
  */

namespace seedsrc {

	namespace miv3 {
		// Iteration 6. Iteration 5 failed to provide a good design for the roundtrip
		// MIV += change through Evolution manager and back to another MIV.
		// The problem is naming of all the artefacts needed to make this processing clean.
		// lets see if we can improve on the design this time.

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


#endif
