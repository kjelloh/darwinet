//---------------------------------------------------------------------------

#ifndef SEPSIsImplementationUnitH
#define SEPSIsImplementationUnitH
//---------------------------------------------------------------------------
#include "InProcDarwinetEngineFramework.h"
//---------------------------------------------------------------------------
/**
  * The Darwinet SEPSI namespace
  */
namespace darwinet {
namespace miv {

	//-----------------------------------------------------------------------
	class c_SEPSIImpl : public  c_SEPSI {
	public:

		/**
		  * Constructor
		  */
		c_SEPSIImpl();

		/**
		  * Virtual Destructor
		  */
		virtual ~c_SEPSIImpl();

		// begin c_SEPSI

		/**
		  * Creates a new value instance of model type with provided model path
		  * setting it to provided initial value.
		  */
		virtual void createInstance(c_ModelPath::shared_ptr pModelPath,const c_DarwinetString& sInitialValue);

		/**
		  * Sets the value instance with provided path to the provided value
		  */
		virtual void setValue(const c_DarwinetString& instance_path,const c_DarwinetString& sValue);

		// End c_SEPSI

	private:

		/**
		  * Models a value instance
		  */
		typedef std::pair<c_ModelPath::shared_ptr,c_DarwinetString> c_Instance;

		/**
		  * Private storage of current value instances
		  */
		std::vector<c_Instance> m_Instances;

	};
} // namespace miv
} // namespace darwinet
#endif
