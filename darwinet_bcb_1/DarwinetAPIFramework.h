//---------------------------------------------------------------------------

#ifndef DarwinetAPIFrameworkH
#define DarwinetAPIFrameworkH

#include <string>
//---------------------------------------------------------------------------
namespace darwinet {

/**
  * Models an ID that uniquilly identifies a data field instance.
  */
typedef std::string c_DataValueId;

/**
  * Models a Darwinet view definition
  */
class c_DarwinetViewDefinition {

};

/**
  * Models a value of a data field of a darwinet data model
  */
class c_DarwinetDataValue {
public:
	/**
	  * returns this value in a string representation
	  */
	std::string toString();

};

/**
  * The Darwinet View interface to be implemented
  * by a darwinet view provider.
  */
class c_DarwinetViewIfc {
public:

	// Begin c_DarwinetViewIfc

	/**
	  * Returns the data value of provided value ID.
	  */
	virtual c_DarwinetDataValue getValue(const c_DataValueId& id) = 0;

	// End c_DarwinetViewIfc

};

/**
  *
  */
class c_DarwinetView : public  c_DarwinetViewIfc {

	// Begin c_DarwinetViewIfc

	/**
	  * Returns the data value of provided value ID.
	  */
	virtual c_DarwinetDataValue getValue(const c_DataValueId& id);

	// End c_DarwinetViewIfc

};

/**
  * The Darwinet node API interface to
  * be implemented by a Darwinet node engine
  */
class c_DarwinetNodeAPI {
public:
	/**
	  * Returns an interface to the required view
	  */
	c_DarwinetViewIfc* getView(const c_DarwinetViewDefinition& def);
};

}
#endif
