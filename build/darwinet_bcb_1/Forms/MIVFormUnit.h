//---------------------------------------------------------------------------

#ifndef MIVFormUnitH
#define MIVFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMIVForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TMIVForm(TComponent* Owner);

	/**
	  * Returns the singleton instance of this form.
	  * Creating it if it does not yet exist.
	  */
	static TMIVForm* instance();

};
//---------------------------------------------------------------------------
extern PACKAGE TMIVForm *MIVForm;
//---------------------------------------------------------------------------
#endif
