/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EditPropertiesFrameUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditApplicationPropertiesFrame *EditApplicationPropertiesFrame;
//---------------------------------------------------------------------------
__fastcall TEditApplicationPropertiesFrame::TEditApplicationPropertiesFrame(TComponent* Owner,c_EditApplicationPropertiesFrameDecoratorIfc* pEditApplicationPropertiesFrameDecoratorIfc)
	: TFrame(Owner)
	  ,m_pApplicationPropertiesModel(new c_ApplicationPropertiesModel(c_FileName(u""))) // Empty anonymous propery instance
	  ,m_pEditApplicationPropertiesFrameDecoratorIfc(pEditApplicationPropertiesFrameDecoratorIfc)
{
	static int instance_count=0;
	++instance_count;
	String sName = "EditApplicationPropertiesFrame" + instance_count;
	this->Name = sName;
	m_pApplicationPropertiesModel->addListener(this);
}
//---------------------------------------------------------------------------

/**
  * Builds GUI for editing provided string list of property values
  */
void TEditApplicationPropertiesFrame::buildPropertiesEditor(TStringList* pPropertiesList,TStringList* pObsoletePropertyList) {
	this->ValueListEditor1->Strings->Clear();
	this->m_pApplicationPropertiesModel->setObsoleteProperties(pObsoletePropertyList);

	pPropertiesList->Sort();
	for (int i = 0; i < pPropertiesList->Count; i++) {
		UnicodeString name = pPropertiesList->Names[i];
		UnicodeString value = pPropertiesList->Values[name];
		this->createEditorEntry(name,value);
	}
}

void __fastcall TEditApplicationPropertiesFrame::ValueListEditor1EditButtonClick(
	  TObject *Sender)
{
	int row_index = this->ValueListEditor1->Row;

	if (row_index > this->ValueListEditor1->RowCount) {
		 // Do nothing. For some reason this event handler may be called with an invalid Row value
	}
	else {
		// Get name of selected row

		UnicodeString name = this->ValueListEditor1->Keys[row_index];
		if (this->isFilePathProperty(name)) {

			// Perform a file select dialog to get path of selected parameter
			if (this->OpenDialog1->Execute()) {
				// Save the selected path
				this->getApplicationPropertiesModel()->setPropertyValue(name,OpenDialog1->FileName);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditApplicationPropertiesFrame::ValueListEditor1GetPickList(TObject *Sender,
		  const UnicodeString KeyName, TStrings *Values)
{

	UnicodeString value = this->ValueListEditor1->Values[KeyName];
	if (    (value == "true")
		 || (value == "false")
		 || (value == "TRUE")
		 || (value == "FALSE")
	   )
	{
		// Add a drop down property editor for this value
		Values->Add("true");
		Values->Add("false");
	}
	else if (this->m_pEditApplicationPropertiesFrameDecoratorIfc != NULL) {
		// Use decorator to return a pick list of values for provided property
		Values->AddStrings(this->m_pEditApplicationPropertiesFrameDecoratorIfc->pickListOfProperty(KeyName));
	}
}

//---------------------------------------------------------------------------

/**
  * Returns the Application properties model used by this frame.
  * Changes to the model will update the frame.
  */
boost::shared_ptr<c_ApplicationPropertiesModel> TEditApplicationPropertiesFrame::getApplicationPropertiesModel() {
	return this->m_pApplicationPropertiesModel;
}

// Begin c_ApplicationPropertiesModelListenerIfc

/**
  * Called by model when a property vale has been changed
  * or added.
  */
void TEditApplicationPropertiesFrame::onApplicationPropertiesModelValueChange(const String& name,const String& value) {

	// Perform the change in the GUI if the change did not originate from the GUI
	// in the first place.
	if (!m_GuiInitiatedChange) {
		// Find the name in the GUI and update the value
		bool nameFound = false;
		// Skip first entry which contains column names and loop
		// through all name=value pairs
		for (int i = 1; i < this->ValueListEditor1->Strings->Count; i++) {
			if (this->ValueListEditor1->Keys[i] == name) {
				// Found it. Set the value
				this->ValueListEditor1->Values[name] = value;
				nameFound = true;
				break;
			}
		}
		if (!nameFound) {
			// Add new one
			this->createEditorEntry(name,value);
		}
	}
}

/**
  * Called when the model has been cleared of all contents
  */
void TEditApplicationPropertiesFrame::onApplicationPropertiesModelClear() {
	// Perform the change in the GUI if the change did not originate from the GUI
	// in the first place.
	if (!m_GuiInitiatedChange) {
		this->ValueListEditor1->Strings->Clear();
	}
}

/**
  * Called when the model we are listening to is deleted.
  */
void TEditApplicationPropertiesFrame::onApplicationPropertiesModelDeleted() {
	this->m_pApplicationPropertiesModel.reset(); // Nothing shared
}

// End c_ApplicationPropertiesModelListenerIfc

/**
  * Creates an editor entry for provided proeprty name and value
  */
void TEditApplicationPropertiesFrame::createEditorEntry(UnicodeString name, UnicodeString value) {

	bool propertyIsObsolete = (this->m_pApplicationPropertiesModel->isObsoleteProperty(name));
	if (propertyIsObsolete) {
		value = "Obsolete in this version";
	}

	int added_item_row_index = this->ValueListEditor1->InsertRow(name,value,true);
	int added_item_array_index = added_item_row_index - 1;

	if (propertyIsObsolete) {
		// The name value is in the obsolete list. Show as inactive
		this->ValueListEditor1->ItemProps[added_item_array_index]->ReadOnly = true;
	}
	else {
		// The name is not in the obsolete propeties list
		// Add a drop down property list if the value is boolean
		if (    (value == "true")
			 || (value == "false")
			 || (value == "TRUE")
			 || (value == "FALSE")
		   )
		{
			this->ValueListEditor1->ItemProps[added_item_array_index]->EditStyle = esPickList;
		}
		else if (this->isFilePathProperty(name)) {
			// Add a dialog editor
			this->ValueListEditor1->ItemProps[added_item_array_index]->EditStyle = esEllipsis;
		}
	}
}

/**
  * Returns true if provided property name is
  * known to be a file path.
  * A file open dialog will be used to edit the value
  */
bool TEditApplicationPropertiesFrame::isFilePathProperty(UnicodeString name) {
	bool result = false;
	if (this->m_pEditApplicationPropertiesFrameDecoratorIfc != NULL) {
		// Use decorator to apply its knowledge
		result = this->m_pEditApplicationPropertiesFrameDecoratorIfc->isFilePathProperty(name);
	}
	return result;
}
//---------------------------------------------------------------------------

void __fastcall TEditApplicationPropertiesFrame::ValueListEditor1Validate(TObject *Sender,
		  int ACol, int ARow, const UnicodeString KeyName, const UnicodeString KeyValue)

{
	// The user has finished editing a value.
	// Update the model
	m_GuiInitiatedChange = true;
	this->m_pApplicationPropertiesModel->setPropertyValue(KeyName,KeyValue);
	m_GuiInitiatedChange = false;
}
//---------------------------------------------------------------------------

