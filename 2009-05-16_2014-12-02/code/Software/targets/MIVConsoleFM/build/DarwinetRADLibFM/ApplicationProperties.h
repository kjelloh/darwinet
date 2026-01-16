//---------------------------------------------------------------------------

#ifndef ApplicationPropertiesH
#define ApplicationPropertiesH

#include <classes.hpp> // TStringList etc
#include "FilePathFramework.h" // c_FilePath
#include "DataRepresentationFrameWork.h"

//---------------------------------------------------------------------------

/**
  * Application properties classes.
  * The whole property environment operates using UTF-16 strings
  * based on IDE defined String.
  */

/**
  * Models a set of property values
  */
typedef std::vector<String> c_PropertyValues;

/**
  * Interface to be implemented by a Test bench properties
  * model listener.
  */
class c_ApplicationPropertiesModelListenerIfc {
public:

	// Begin c_ApplicationPropertiesModelListenerIfc

	/**
	  * Called by model when a property vale has been changed
	  * or added.
	  */
	virtual void onApplicationPropertiesModelValueChange(const String& name,const String& value)=0;

	/**
	  * Called when the model has been cleared of all contents
	  */
	virtual void onApplicationPropertiesModelClear()=0;

	/**
	  * Called when the model we are listening to is deleted.
	  */
	virtual void onApplicationPropertiesModelDeleted()=0;

	// End c_ApplicationPropertiesModelListenerIfc

};

/**
  * Models a collection of test bench properties
  */
class PACKAGE c_ApplicationPropertiesModel {
public:

	/**
	  * Creates an empty property model
	  */
//	c_ApplicationPropertiesModel(const c_DataRepresentationFramework::c_UTF16String& sCaption);
	c_ApplicationPropertiesModel(const c_FileName& property_file_name);

	/**
	  * Virtual destructor
	  */
	virtual ~c_ApplicationPropertiesModel();

	/**
	  * Adds provided listener to list of listeners that will
	  * be called by this model instance.
	  */
	void addListener(c_ApplicationPropertiesModelListenerIfc* pListener);

	/**
	  * Removes provided listener from list of listeners
	  */
	void removeListener(c_ApplicationPropertiesModelListenerIfc* pListener);

	/**
	  * Empties this collection of all properties
	  */
	void clear();

	/**
	  * Returns the undefined value for provided key.
	  */
	String getUndefinedValueOfKey(const String& name);

	/**
	  * Returns true if property with provided key is undefined or contains the
	  * value reserved for an undefined property (getUndefinedValueOfKey(name)).
	  */
	bool isUndefined(const String& name);

	/**
	  * Returns value of property with name. Returns default value
	  * if no value is defined for name.
	  */
	String getPropertyValue(const String& name,const String& defaultValue="");

	/**
	  * Returns a list of values of property of provided name.
	  * Used for properties that stores a list of values
	  */
	c_PropertyValues getPropertyValues(const String& name,const String& defaultValue="");

	/**
	  * Sets property of provided name to provided list of values
	  */
	void setPropertyValues(const String& name,const c_PropertyValues& values);

	/**
	  * Sets property with name to provided value
	  */
	void setPropertyValue(const String& name,const String& value);

	/**
	  * Will load properties from persistens storage
	  */
	void loadProperties(c_FilePath root_directory);

	/**
	  * Will update properties and save to persistent storage
	  */
	void saveProperties();

	/**
	  * Returns the string list containg property (name,value) pairs
	  */
	TStringList* getProperties();

	/**
	  * Marks provided property as obsolete
	  */
	void setObsoleteProperty(const String& name);

	/**
	  * Returns the string list containg obsolete property names
	  */
	TStringList* getObsoleteProperties();

	/**
	  * Sets obsolete properties list to the one provided.
	  * The list is cloned.
	  */
	void setObsoleteProperties(TStringList* pObsoleteNames);

	/**
	  * Returns true if provided property name is registered as obsolete
	  */
	bool isObsoleteProperty(const String& name);

	/**
	  * Copies our properties to provided properties
	  */
	void copyTo(c_ApplicationPropertiesModel* pProperties);

	/**
	  * Sets our properties to be as provided properties.
	  * Any properties we have are cleared prior to the set.
	  */
	void setTo(c_ApplicationPropertiesModel* pProperties);

	/**
	  * Returns access to file path of persistent storage for this properties instance
	  */
	const c_FilePath& getPersistentStoragePath() const;


private:

//	/**
//	  * private storage of this properties caption
//	  */
//	c_DataRepresentationFramework::c_UTF16String m_sCaption;

	/**
	  * Private storage of the name of the property file
	  */
	c_FileName m_property_file_name;

	/**
	  * Private storage of property values
	  */
	TStringList* m_pProperties;

	/**
	  * Private storage of complete path to the Application ini file
	  */
	c_FilePath m_IniFilePath;

	/**
	  * Private storage of property values
	  */
	TStringList* m_pObsoleteNames;

	std::vector<c_ApplicationPropertiesModelListenerIfc*> m_listeners;

	/**
	  * Returns an iterator referring to provided listener in listeners list
	  */
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator getIApplicationPropertiesModelListener(c_ApplicationPropertiesModelListenerIfc* pListener);

	/**
	  * Report change of name to all registered listeners
	  */
	void reportChangeToListeners(const String& name,const String& value);

	/**
	  * Report cleared model to all registered listeners
	  */
	void reportClearToListeners();

	/**
	  * Report to all listeneres that we are being deleted
	  */
	void reportDeletedToListeners();

};

/**
  * Models a propertis model change detector tha may be used
  * as a flag object by a client when only detecton of change
  * is needed.
  */
class PACKAGE c_ApplicationPropertiesModelChangeDetector : public c_ApplicationPropertiesModelListenerIfc {
public:
	/**
	  * Constructs an instance with initial state set to provided flag state
	  * that listens to provided model.
	  */
	c_ApplicationPropertiesModelChangeDetector(c_ApplicationPropertiesModel* pModel,bool isInitiallySet);

	/**
	  * Detector destructor. Unregisters as listener to Property changes.
	  */
	~c_ApplicationPropertiesModelChangeDetector();

	/**
	  * Sets the Property model this detector is listening to.
	  */
	void listenTo(c_ApplicationPropertiesModel* pModel);

	/**
	  * Sets the change reported flag to false
	  */
	void reset();

	/**
	  * Returns true if the change flag is set.
	  */
	bool isSet();

private:
	/**
	  * Flag set if a change is reported.
	  * May be reset by client of this instance.
	  */
	bool m_AChangeHaBeenReported;

	/**
	  * The model of which we are listening for changes
	  */
	c_ApplicationPropertiesModel* m_pModel;

	// Begin c_ApplicationPropertiesModelListenerIfc

	/**
	  * Called by model when a property vale has been changed
	  * or added.
	  */
	virtual void onApplicationPropertiesModelValueChange(const String& name,const String& value);

	/**
	  * Called when the model has been cleared of all contents
	  */
	virtual void onApplicationPropertiesModelClear();

	/**
	  * Called when the model we are listening to is deleted.
	  */
	virtual void onApplicationPropertiesModelDeleted();

	// End c_ApplicationPropertiesModelListenerIfc

};




// Removed 101113/KoH. Application properties should not be accessible through
// singleton. Implement own accessor in Application environment structure
// or use default accessor in Application runtime environment instance

///**
//  * Application properties singleton
//  */
//class c_ApplicationProperties : public c_ApplicationPropertiesModel {
//public:
//
//	/**
//	  * Returns singleton instance
//	  */
//	static c_ApplicationProperties* instance();
//
//private:
//	/**
//	  * Private singleton constructor
//	  */
//	c_ApplicationProperties();
//
//	/**
//	  * Private singleton instance storage
//	  */
//	static c_ApplicationProperties* m_instance;
//
//};
typedef c_ApplicationPropertiesModel c_ApplicationProperties;

#endif
