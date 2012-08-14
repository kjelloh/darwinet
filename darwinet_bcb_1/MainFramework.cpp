//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainFramework.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Models the test application
  */
class c_TestApplication : public c_TestApplicationIfc {
public:

	/**
	  * Increment the test application test value
	  */
	virtual void incrementTestValue();

};


/**
  * Creates an instance implementing this interface
  */
c_TestApplicationIfc::pointer c_TestApplicationIfc::create() {
	c_TestApplicationIfc::pointer result(new c_TestApplication());
	return result;
}
