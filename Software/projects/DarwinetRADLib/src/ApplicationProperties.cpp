/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#pragma hdrstop
#endif
//---------------------------------------------------------------------------
#include "ApplicationProperties.h"
#include "BusinessLogUnit.h" // DESIGN_INSUFFICIENCY_LOG(...)
#include <boost/algorithm/string.hpp>
#include <string>
//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#include <Dialogs.hpp>
#pragma package(smart_init)
#endif
//---------------------------------------------------------------------------

#ifdef __BCPLUSPLUS__
        // use VCL-classes. See header
#else
/**
 * Constructor
 */
c_PropertyList::c_PropertyList()
{
    
}

// Begin c_PropertyList


/**
 * Loads contents from file.
 * @param file_path, path to file to load properties from.
 */
void c_PropertyList::LoadFromFile(const c_FilePath& file_path) {
    LOG_NOT_IMPLEMENTED;
#warning c_PropertyList::LoadFromFile not implemented
}

/**
 * Saves our contents to file.
 * @param file_path, path to file to save to. Will create file if it does not exist.
 */
void c_PropertyList::SaveToFile(const c_FilePath& file_path) {
    LOG_NOT_IMPLEMENTED;    
#warning c_PropertyList::SaveToFile not implemented
}
#endif
/**
  * Creates an empty property model
  */
//c_ApplicationPropertiesModel::c_ApplicationPropertiesModel(const c_DataRepresentationFramework::c_UTF16String& sCaption)
c_ApplicationPropertiesModel::c_ApplicationPropertiesModel(const c_FileName& property_file_name)
	:  m_pProperties(new c_PropertyList())
	  ,m_pObsoleteNames(new c_PropertyList())
	  ,m_listeners()
	  ,m_IniFilePath()
//	  ,m_sCaption(sCaption)
	  ,m_property_file_name(property_file_name)
{
	LOG_METHOD_SCOPE_S(toLogString(property_file_name));
	try {
		if (this->m_property_file_name.hasExtension() == false) {
			// Us the deafult ".ini" extension
			this->m_property_file_name += _UTF8sz(".ini");
		}
	} catch (...) {
		c_LogString sMessage("c_ApplicationPropertiesModel::c_ApplicationPropertiesModel failed. Anonymous Exception cought");
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
};

//---------------------------------------------------------------------------

/**
  * Virtual destructor
  */
c_ApplicationPropertiesModel::~c_ApplicationPropertiesModel() {
	LOG_METHOD_SCOPE;
	this->reportDeletedToListeners();
}

//---------------------------------------------------------------------------
/**
  * Adds provided listener to list of listeners that will
  * be called by this model instance.
  */
void c_ApplicationPropertiesModel::addListener(c_ApplicationPropertiesModelListenerIfc* pListener) {
	if (this->getIApplicationPropertiesModelListener(pListener) == this->m_listeners.end()) {
		// Is not registered. OK to add
		this->m_listeners.push_back(pListener);
	}
	else {
		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_ApplicationPropertiesModel::addListener called with listener already in list. No Operation done"));
	}
}

//---------------------------------------------------------------------------
/**
  * Removes provided listener from list of listeners
  */
void c_ApplicationPropertiesModel::removeListener(c_ApplicationPropertiesModelListenerIfc* pListener) {
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator IListener(this->getIApplicationPropertiesModelListener(pListener));
	if ( IListener == this->m_listeners.end()) {
		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_ApplicationPropertiesModel::removeListener called with listener not in list. No Operation done"));
	}
	else {
		// Is not registered. OK to erase
		this->m_listeners.erase(IListener);
	}
}

//---------------------------------------------------------------------------
/**
  * Empties this collection of all properties
  */
void c_ApplicationPropertiesModel::clear() {
#ifdef __BCPLUSPLUS__
	this->m_pProperties->Clear();
	this->m_pObsoleteNames->Clear();
#else
	this->m_pProperties->clear();
	this->m_pObsoleteNames->clear();        
#endif
	this->reportClearToListeners();
}
//---------------------------------------------------------------------------

/**
  * Returns the string list containg property name,value pairs
  */
c_PropertyList* c_ApplicationPropertiesModel::getProperties() {
	return this->m_pProperties;
}

/**
  * Returns the string list containg obsolete property names
  */
c_PropertyList* c_ApplicationPropertiesModel::getObsoleteProperties() {
	return this->m_pObsoleteNames;
}

//---------------------------------------------------------------------------
/**
  * Sets obsolete properties list to the one provided.
  * The list is cloned.
  */
void c_ApplicationPropertiesModel::setObsoleteProperties(c_PropertyList* pObsoleteNames) {
#ifdef __BCPLUSPLUS__
	this->m_pObsoleteNames->Clear();       
	for (int i = 0; i < pObsoleteNames->Count; i++) {
		c_PropertyString name = pObsoleteNames->Strings[i];
		this->m_pObsoleteNames->Add(name);
	}
#else
	this->m_pObsoleteNames->clear();       
        this->m_pObsoleteNames->insert(pObsoleteNames->begin(),pObsoleteNames->end());
#endif
}

//---------------------------------------------------------------------------

/**
  * Returns true if provided property name is registered as obsolete
  */
bool c_ApplicationPropertiesModel::isObsoleteProperty(const c_PropertyString& name) {
	bool result = false; // default
#ifdef __BCPLUSPLUS__
	result =  (this->m_pObsoleteNames->IndexOf(name)>=0);
#else
        result = (this->m_pObsoleteNames->find(name) != this->m_pObsoleteNames->end());
#endif
	return result;
}

//---------------------------------------------------------------------------
/**
  * Returns an iterator referring to provided listener in listeners list
  */
std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator c_ApplicationPropertiesModel::getIApplicationPropertiesModelListener(c_ApplicationPropertiesModelListenerIfc* pListener) {
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator result = this->m_listeners.end();
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator iter = this->m_listeners.begin();
	while (iter != this->m_listeners.end()) {
		if (*iter == pListener) {
			// Found it! Stop
			break;
		}
		iter ++;
	}
	result = iter;
	return result;
}


//---------------------------------------------------------------------------
/**
  * Copies our properties to provided properties
  */
void c_ApplicationPropertiesModel::copyTo(c_ApplicationPropertiesModel* pProperties) {

#ifdef __BCPLUSPLUS__
	for (int i = 0; i < this->m_pProperties->Count; i++) {
//		pProperties->setPropertyValue(this->m_pProperties->Names[i],this->m_pProperties->ValueFromIndex[i]);
		pProperties->setPropertyValue(this->m_pProperties->Names[i],this->m_pProperties->Values[this->m_pProperties->Names[i]]);
	}
	pProperties->setObsoleteProperties(this->getObsoleteProperties());
#else
        for (c_PropertyList::const_iterator iter = this->m_pProperties->begin(); iter != this->m_pProperties->end();++iter) {
                pProperties->setPropertyValue(iter->first,iter->second);            
        }
#endif
}
//---------------------------------------------------------------------------
/**
  * Sets our properties to be as provided properties.
  * Any properties we have are cleared prior to the set.
  */
void c_ApplicationPropertiesModel::setTo(c_ApplicationPropertiesModel* pProperties) {
#ifdef __BCPLUSPLUS__
	this->m_pProperties->Clear();
	for (int i = 0; i < pProperties->m_pProperties->Count; i++) {
		c_PropertyString name = pProperties->m_pProperties->Strings[i];
		this->m_pProperties->Add(name);
		c_PropertyString value = pProperties->m_pProperties->Values[name];
		this->m_pProperties->Values[name] = value;
	}
	pProperties->setObsoleteProperties(this->getObsoleteProperties());
#else
        this->m_pProperties->clear();
        this->m_pProperties->insert(pProperties->m_pProperties->begin(), pProperties->m_pProperties->end());
#endif
}
//---------------------------------------------------------------------------
/**
  * Returns access to file path of persistent storage for this properties instance
  */
const c_FilePath& c_ApplicationPropertiesModel::getPersistentStoragePath() const {
	return this->m_IniFilePath;
}
//---------------------------------------------------------------------------

/**
  * Returns the undefined value for provided key.
  */
c_PropertyString c_ApplicationPropertiesModel::getUndefinedValueOfKey(const c_PropertyString& name) {
#ifdef __GNUC__
        /**
         * The compiler should find that the constructor implicitly takes a std::string and create a temporary         
         * from provided const char* to call that constructor.
         * Works in Rad Studion XE, why not in g++?
         * Well, this is a fix.
         */
        c_PropertyString result("undefined #");
        result += name;
        result += _UTF8sz("#");        
	return result;
#else
        /**
         * The compiler should find that the constructor implicitly takes a std::string and create a temporary         
         * from provided const char* to call that constructor.
         */ 
	return (c_PropertyString("undefined #") + name + "#");        
#endif
}

//---------------------------------------------------------------------------
/**
  * Returns true if property with provided key is undefined or contains the
  * value reserved for an undefined property.
  */
bool c_ApplicationPropertiesModel::isUndefined(const c_PropertyString& name) {
	bool result = false;
#ifdef __BCPLUSPLUS__        
	c_PropertyString sValue = m_pProperties->ValueFromIndex[m_pProperties->IndexOfName(name)];
	if (sValue.Length() == 0) {
		// undefined because no value set (or empty value)
		result = true;
	}
	else {
		// undefined if value is the value reserved for undefined property
		result = (sValue == this->getUndefinedValueOfKey(name));
	}
#else
        result = (this->m_pProperties->find(name) == this->m_pProperties->end());
#endif        
	return result;
}

//---------------------------------------------------------------------------
/**
  * Returns value of property with name. Returns default value
  * if no value is defined for name.
  */
c_PropertyString c_ApplicationPropertiesModel::getPropertyValue(const c_PropertyString& name,const c_PropertyString& defaultValue) {
        c_PropertyString result = getUndefinedValueOfKey(name); // default
#ifdef __BCPLUSPLUS__        
        result = m_pProperties->ValueFromIndex[m_pProperties->IndexOfName(name)];
        if (result.Length()==0) {
		// No value set. Set default value
		c_PropertyString sDefaultValue(defaultValue);
		if (sDefaultValue.Length()==0) {
			// No default value provided in call.
			// Set to undefined value
			sDefaultValue = getUndefinedValueOfKey(name);
		}
		setPropertyValue(name,sDefaultValue);
		result = sDefaultValue;
	}
#else
        c_PropertyList::iterator iter = this->m_pProperties->find(name);
        if (iter == this->m_pProperties->end()) {
            // Does not yet exist.
            if (defaultValue.length() > 0) {
                // Set to provided default value
                result = defaultValue;
            }
            // Add it
            this->m_pProperties->insert(std::make_pair(name,result));                
        }
#endif
	if (true) {
		// Trace the property get
		c_LogString sMessage(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this)));
		sMessage += _UTF8sz("  \"");\
		sMessage += toLogString(name);
		sMessage += _UTF8sz("\"=>\"");
		sMessage += toLogString(result);
		sMessage += _UTF8sz("\"");
		LOG_DEVELOPMENT_TRACE(sMessage);
	}
        
        return result;
}

//---------------------------------------------------------------------------
/**
  * Returns a list of values of property of provided name.
  * Used for properties that stores a list of values
  */
c_PropertyValues c_ApplicationPropertiesModel::getPropertyValues(const c_PropertyString& name,const c_PropertyString& defaultValue) {
	c_PropertyValues result;
	c_PropertyString sPropertyValue = this->getPropertyValue(name,defaultValue);
	// split stored value on ';'

	int firstPosOfItem = 1;
	int itemLength = 0;
#ifdef __BCPLUSPLUS__        
	for (int i = 1; i <= sPropertyValue.Length(); i++) { // VCL String uses index 1..len
		if ((sPropertyValue[i] == ';') || (i >= sPropertyValue.Length()) ) {
			// Found separator
			if (sPropertyValue[i] == ';') {
				itemLength = i-firstPosOfItem;
			}
			else {
				itemLength = i-firstPosOfItem+1;
			}
			if (itemLength <= 0) {
				// Skip zero items.
			}
			else {
				result.push_back(sPropertyValue.SubString(firstPosOfItem,itemLength));
			}
			if (sPropertyValue[i] == ';') {
				firstPosOfItem = i+1; // skip ';'
			}
			else {
				firstPosOfItem = i;
			}
		}
	}
#else
        // Note that this code (nor the original) is safe on UTF strings. They may encode a char with multiple bytes!
#warning Splitting on delimiter unsafe on UTF-strings.
        boost::iter_split(result, sPropertyValue, boost::first_finder(";"));
#endif            
	return result;
}

//---------------------------------------------------------------------------
/**
  * Sets property of provided name to provided list of values
  */
void c_ApplicationPropertiesModel::setPropertyValues(const c_PropertyString& name,const c_PropertyValues& values) {
	// Assemble property value as a string with values separated by ';'
	c_PropertyString sPropertyValue;
	bool isFirstItem = true;
	c_PropertyValues::const_iterator iter = values.begin();
	while (iter != values.end()) {
		if (isFirstItem) {
			isFirstItem = false;
		}
		else {
			// Add separator
			sPropertyValue.anonymous() += ";";
		}
		sPropertyValue += *iter;
		iter++;
	}
	this->setPropertyValue(name,sPropertyValue);
}

//---------------------------------------------------------------------------
/**
  * Sets property with name to provided value
  */
void c_ApplicationPropertiesModel::setPropertyValue(const c_PropertyString& name,const c_PropertyString& value) {
	if (this->isObsoleteProperty(name)) {
		// Do nothing. Keep value unchanged for obsolete values
	}
#ifdef __BCPLUSPLUS__        
	else if (name.Length() > 0) {
		c_PropertyString sValueBeforeChange;
		int indexOfName = m_pProperties->IndexOfName(name);
		if (indexOfName>=0) {
			sValueBeforeChange = m_pProperties->Values[name];
			m_pProperties->Values[name] = value;
		}
		else {
			// Create a new one
			m_pProperties->Add(name+"="+value);
		}
#else
	else if (name > "") {
		c_PropertyString sValueBeforeChange;
                c_PropertyList::iterator iter = m_pProperties->find(name);
		if (iter != m_pProperties->end()) {
                        // Replace existing value
			 iter->second.swap(sValueBeforeChange);
		}
		else {
			// Create a new one
			m_pProperties->insert(std::make_pair(value,name));
		}                
#endif
		if (value != sValueBeforeChange) {
			// Report that the value has really changed
			this->reportChangeToListeners(name,value);
		}

		if (true) {
			// Trace the property get
			c_LogString sMessage(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this)));
			sMessage += _UTF8sz("  \"");\
			sMessage += toLogString(name);
			sMessage += _UTF8sz("\"<=\"");
			sMessage += toLogString(value);
			sMessage += _UTF8sz("\"");
			LOG_DEVELOPMENT_TRACE(sMessage);
		}
	}
	else {
		c_LogString sMessage(__FUNCTION__);
                sMessage += _Asciisz(" failed. Called with null property name.");
		LOG_DESIGN_INSUFFICIENCY(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Will load properties from persistent storage
  */
void c_ApplicationPropertiesModel::loadProperties(c_FilePath root_directory) {
	if (this->m_IniFilePath.size() == 0) {
		this->m_IniFilePath = root_directory;
//		c_FilePathNode exeName = c_Application::ExeName();
//		std::string sLogFileName = exeName.NameWithoutExtension() + ".ini";
//		c_PropertyString sIniFileName = c_PropertyString(m_sCaption.c_str()) + u".ini";
//		this->m_IniFilePath +=  _UTF16sz(sIniFileName.c_str());
		this->m_IniFilePath += this->m_property_file_name;
	}

	if (m_pProperties == NULL) {
		m_pProperties = new c_PropertyList();
	}
#ifdef __BCPLUSPLUS__        
        // Note 130411, Is this really necessary? Is it not cleared when loaded from file?/KoH
	m_pProperties->Clear(); // Make sure "we" are empty
#endif

	if (c_FilePathFramework::fileExists(this->m_IniFilePath)) {
#ifdef __BCPLUSPLUS__        
		m_pProperties->LoadFromFile(this->m_IniFilePath.toString().c_str());
#else
		m_pProperties->LoadFromFile(this->m_IniFilePath);                
#endif
		// Dummy, report a dummy change to alert listeners that as change has been made.
		// TODO 080516 - Consider implementing a specific event to report for this.
		//                Do not report each added property! (?)
		this->reportChangeToListeners(_Asciisz(""),_Asciisz(""));
	}
	else {
		// Do nothing. The file and path will be created when saved
		c_LogString sMessage("The property file=");
		sMessage += c_DataRepresentationFramework::toUTF8String(this->m_IniFilePath.toString());
		sMessage.anonymous() += " Does not exist. No properties loaded.";
		LOG_BUSINESS(sMessage);
	}
}

//---------------------------------------------------------------------------
/**
  * Will update properties and save to persistent storage
  */
void c_ApplicationPropertiesModel::saveProperties() {
	try {
		c_FilePathFramework::ensureDirectoryPathExists(this->m_IniFilePath.getParentPath());
		// Save ini-file to same location as it was loaded from.
#ifdef __BCPLUSPLUS__        
		m_pProperties->SaveToFile(this->m_IniFilePath.toString().c_str());
#else
		m_pProperties->SaveToFile(this->m_IniFilePath);
#endif
	} catch (...) {
		// Failed to save properties
		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_ApplicationPropertiesModel::saveProperties failed. Anonymous Exception cought"));
	}
}
//---------------------------------------------------------------------------
/**
  * Marks provided property as obsolete
  */
void c_ApplicationPropertiesModel::setObsoleteProperty(const c_PropertyString& name) {
#ifdef __BCPLUSPLUS__        
	this->m_pObsoleteNames->Add(name);
#else
	this->m_pObsoleteNames->insert(std::make_pair(name,_Asciisz("")));        
#endif
}

//---------------------------------------------------------------------------
/**
  * Report change of name to all registered listeners
  */
void c_ApplicationPropertiesModel::reportChangeToListeners(const c_PropertyString& name,const c_PropertyString& value) {
	if (false) {
		// Trace the property change
		c_LogString sMessage(c_DataRepresentationFramework::intToHexString(reinterpret_cast<unsigned int>(this)));
		sMessage += _UTF8sz("  \"");\
		sMessage += toLogString(name);
		sMessage += _UTF8sz("\"<=\"");
		sMessage += toLogString(value);
		sMessage += _UTF8sz("\"");
		LOG_DEVELOPMENT_TRACE(sMessage);
	}

	// Tell all listeners
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator iter = this->m_listeners.begin();
	while (iter != this->m_listeners.end()) {
		(*iter)->onApplicationPropertiesModelValueChange(name,value);
		iter++;
	}

}
//---------------------------------------------------------------------------
/**
  * Report cleared model to all registered listeners
  */
void c_ApplicationPropertiesModel::reportClearToListeners() {
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator iter = this->m_listeners.begin();
	while (iter != this->m_listeners.end()) {
		(*iter)->onApplicationPropertiesModelClear();
		iter++;
	}
}
//---------------------------------------------------------------------------

/**
  * Report to all listeneres that we are being deleted
  */
void c_ApplicationPropertiesModel::reportDeletedToListeners() {
	std::vector<c_ApplicationPropertiesModelListenerIfc*>::iterator iter = this->m_listeners.begin();
	while (iter != this->m_listeners.end()) {
		(*iter)->onApplicationPropertiesModelDeleted();
		iter++;
	}
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * Constructs an instance with initial state set to provided flag state
  * that listens to provided model.
  */
c_ApplicationPropertiesModelChangeDetector::c_ApplicationPropertiesModelChangeDetector(c_ApplicationPropertiesModel* pModel,bool isInitiallySet)
	: m_AChangeHaBeenReported(isInitiallySet)
	  ,m_pModel(NULL)
{
	this->listenTo(pModel);
}

//---------------------------------------------------------------------------
/**
  * Detector destructor. Unregisters as listener to Property changes.
  */
c_ApplicationPropertiesModelChangeDetector::~c_ApplicationPropertiesModelChangeDetector() {
	if (m_pModel != NULL) {
		m_pModel->removeListener(this);
	}
	else {
		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_ApplicationPropertiesModelChangeDetector::~c_ApplicationPropertiesModelChangeDetector called with NULL model. This listener will never be called!"));
	}
}

//---------------------------------------------------------------------------
/**
  * Sets the Property model this detector is listening to.
  */
void c_ApplicationPropertiesModelChangeDetector::listenTo(c_ApplicationPropertiesModel* pModel) {
	if (m_pModel != NULL) {
		m_pModel->removeListener(this);
	}
	this->m_pModel = pModel;

	if (m_pModel != NULL) {
		m_pModel->addListener(this);
	}
	else {
		LOG_DESIGN_INSUFFICIENCY(_Literalsz("c_ApplicationPropertiesModelChangeDetector::listenTo called with NULL model. This listener will never be called!"));
	}
}


//---------------------------------------------------------------------------
/**
  * Sets the change reported flag to false
  */
void c_ApplicationPropertiesModelChangeDetector::reset() {
	this->m_AChangeHaBeenReported = false;
}

//---------------------------------------------------------------------------
/**
  * Returns true if the change flag is set.
  */
bool c_ApplicationPropertiesModelChangeDetector::isSet() {
	return this->m_AChangeHaBeenReported;
}

// Begin c_ApplicationPropertiesModelListenerIfc

//---------------------------------------------------------------------------
/**
  * Called by model when a property vale has been changed
  * or added.
  */
void c_ApplicationPropertiesModelChangeDetector::onApplicationPropertiesModelValueChange(const c_PropertyString& name,const c_PropertyString& value) {
	this->m_AChangeHaBeenReported = true;
}

//---------------------------------------------------------------------------
/**
  * Called when the model has been cleared of all contents
  */
void c_ApplicationPropertiesModelChangeDetector::onApplicationPropertiesModelClear() {
	this->m_AChangeHaBeenReported = true;
}

//---------------------------------------------------------------------------
/**
  * Called when the model we are listening to is deleted.
  */
void c_ApplicationPropertiesModelChangeDetector::onApplicationPropertiesModelDeleted() {
	this->m_pModel = NULL;
}

// End c_ApplicationPropertiesModelListenerIfc


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

///**
//  * static access of singleton instance
//  */
//c_ApplicationProperties* c_ApplicationProperties::instance() {
//	if (m_instance == NULL) {
//		m_instance = new c_ApplicationProperties();
//
//		try {
//			// Load properties from current Application root
//			m_instance->loadProperties(c_Application::getExeRootPath());
//
//		} catch (...) {
//			// File may not exit
//			m_instance->saveProperties();
//		}
//	}
//	return m_instance;
//}
//
///**
//  * Singleton Instance storage definition
//  */
//c_ApplicationProperties* c_ApplicationProperties::m_instance=NULL;
//
///**
//  * Private singleton constructor
//  */
//c_ApplicationProperties::c_ApplicationProperties()
//	: c_ApplicationPropertiesModel(c_Application::ExeName())
//{
//
//}

