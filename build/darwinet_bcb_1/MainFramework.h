//---------------------------------------------------------------------------

#ifndef MainFrameworkH
#define MainFrameworkH

#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Models the test application interface
  */
class c_TestApplicationIfc {
public:

	typedef boost::shared_ptr<c_TestApplicationIfc> pointer;

	/**
	  * Creates an instance implementing this interface
	  */
	static c_TestApplicationIfc::pointer create();

	/**
	  * Increment the test application test value
	  */
	virtual void incrementTestValue() = 0;

};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



#endif
