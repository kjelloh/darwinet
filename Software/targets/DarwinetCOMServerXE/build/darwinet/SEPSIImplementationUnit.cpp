//---------------------------------------------------------------------------

#pragma hdrstop

#include "SEPSIImplementationUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace darwinet {
/**
  * The miv namespace
  */
namespace miv {




	/**
	  * namespace of SEPSI delta core
	  */
	namespace delta {
		/**
		  * Base interface of all SEPSI deltas.
		  */
		class c_DeltaSEPSI {
		public:
			// shared pointer to a c_DeltaSEPSI
			typedef boost::shared_ptr<c_DeltaSEPSI> shared_ptr;

		};

		/**
		  * base class of all SEPSI value changes
		  */
		class c_DeltaValue : public c_DeltaSEPSI {
		public:
			/**
			  * Cretaes a value change to provided instance_path
			  */
			c_DeltaValue(const c_InstancePath& instance_path);
		};

		class c_DeltaIntegerValue : public c_DeltaValue {
		public:
			/**
			  * Creates a change to a SEPSI integer instance
			  */
			c_DeltaIntegerValue(const c_InstancePath& instance_path,int delta_int);
		};

	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	/**
	  * Models a SEPSI History interface
	  */
	class c_SEPSIHistory {
	public:


		// models a shared pointer to a c_SEPSIHistory
		typedef boost::shared_ptr<c_SEPSIHistory> shared_ptr;

		// Begin c_SEPSIHistory

		virtual void actOnDelta(const );

		// End c_SEPSIHistory
	};


	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Constructor
	  */
	c_SEPSIImpl::c_SEPSIImpl()
	{
		LOG_METHOD_SCOPE;
	}

	//-----------------------------------------------------------------------
	/**
	  * Virtual Destructor
	  */
	c_SEPSIImpl::~c_SEPSIImpl() {
		LOG_METHOD_SCOPE;
	}

	// begin c_SEPSI
	//-----------------------------------------------------------------------
	/**
	  * Creates a new value instance of model type with provided model path
	  * setting it to provided initial value.
	  */
	void c_SEPSIImpl::createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue) {
		LOG_NOT_IMPLEMENTED;
		// TODO: Implement interface to the View SEPSIHistory
		//       (this) --> create instance --> view::SEPSIHistory
		//       (this) <-- on Instance Created <-- view::SEPSIHistory
		//  *create instance*
	}

	/**
	  * Sets the value instance with provided path to the provided value
	  */
	void c_SEPSIImpl::setValue(const c_DarwinetString& instance_path,const c_DarwinetString& sValue) {
		LOG_METHOD_SCOPE;
		LOG_NOT_IMPLEMENTED;
		// Update our state only on events from or view::SEPSIHistory. In this
		// way we use the same mechanism regardless of if "we" produced the change
		// or if another peer did it.

		// delta::c_DeltaSEPSI::shared_ptr pDeltaSEPSI = ...TODO...

	}

	// End c_SEPSI

} // namespace miv
} // namespace darwinet
