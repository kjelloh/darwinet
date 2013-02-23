/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef EditPropertiesFrameUnitH
#define EditPropertiesFrameUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Dialogs.hpp>
#include "ApplicationProperties.h"
#include <boost/shared_ptr.hpp>

/**
  * Intercace implemented by Properties editor decorator
  * that applies special interpretation to property values.
  */
class c_EditApplicationPropertiesFrameDecoratorIfc {
public:

	// Begin c_EditApplicationPropertiesFrameDecoratorIfc

	/**
	  * Returns possible values for property with provided name
	  */
	virtual TStrings* pickListOfProperty(const UnicodeString KeyName) = 0;

	/**
	  * Returns true if the property with provided name
	  * contains a file path
	  */
	virtual bool isFilePathProperty(UnicodeString name) = 0;

	// End c_EditApplicationPropertiesFrameDecoratorIfc
};

//---------------------------------------------------------------------------
#pragma warn -8130 // Do not warn that interface does not derive from IUknown
class TEditApplicationPropertiesFrame : public TFrame, public c_ApplicationPropertiesModelListenerIfc
{
__published:	// IDE-managed Components
	TValueListEditor *ValueListEditor1;
	TOpenDialog *OpenDialog1;
	void __fastcall ValueListEditor1EditButtonClick(TObject *Sender);
	void __fastcall ValueListEditor1Validate(TObject *Sender, int ACol, int ARow, const UnicodeString KeyName,
		  const UnicodeString KeyValue);
	void __fastcall ValueListEditor1GetPickList(TObject *Sender, const UnicodeString KeyName,
		  TStrings *Values);
private:	// User declarations

	/**
	  * Private storage of the properties edited in this frame
	  */
	boost::shared_ptr<c_ApplicationPropertiesModel> m_pApplicationPropertiesModel;

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

	/**
	  * Creates an editor entry for provided proeprty name and value
	  */
	void createEditorEntry(UnicodeString name, UnicodeString value);

	/**
	  * Flag indicating if current change is initiated in the GUI
	  * (I.e not programatically from a source outside the GUI)
	  */
	bool m_GuiInitiatedChange;

	/**
	  * Returns true if provided property name is
	  * known to be a file path.
	  * A file open dialog will be used to edit the value
	  */
	bool isFilePathProperty(UnicodeString name);

	/**
	  * Private storage of the decorator to use for Pick lists and such.
	  */
	c_EditApplicationPropertiesFrameDecoratorIfc* m_pEditApplicationPropertiesFrameDecoratorIfc;

public:		// User declarations

	/**
	  * Creates a property editor frame from provided properties source.
	  * The Editor will work with a clone of its own.
	  * The client must acces this clone and retreive edited contents
	  * if apropriate.
	  */
	__fastcall TEditApplicationPropertiesFrame(TComponent* Owner,c_EditApplicationPropertiesFrameDecoratorIfc* pEditApplicationPropertiesFrameDecoratorIfc);

	/**
	  * Builds GUI for editing provided string list of property values
	  */
	void buildPropertiesEditor(TStringList* pPropertiesList,TStringList* pObsoletePropertyList);

	/**
	  * Returns the Application properties model used by this frame.
	  * Changes to the model will update the frame.
	  */
	boost::shared_ptr<c_ApplicationPropertiesModel> getApplicationPropertiesModel();

};
#pragma warn .8130 // See above
//---------------------------------------------------------------------------
extern PACKAGE TEditApplicationPropertiesFrame *EditApplicationPropertiesFrame;
//---------------------------------------------------------------------------
#endif
