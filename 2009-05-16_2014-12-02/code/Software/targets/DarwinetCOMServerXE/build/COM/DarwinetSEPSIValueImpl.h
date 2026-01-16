// ---------------------------------------------------------------------------
// DarwinetSEPSIValueImpl.h : Declaration of the TDarwinetSEPSIValueImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetSEPSIValueImplH
#define DarwinetSEPSIValueImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"
#include "InProcDarwinetEngineFramework.h"

// ---------------------------------------------------------------------------
// TDarwinetSEPSIValueImpl     Implements IDarwinetSEPSIValue, default interface of DarwinetSEPSIValue
// Events         : Implements IDarwinetSEPSIValueEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    : 
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetSEPSIValueImpl :
	 public TCppAutoObjectEvent<IDarwinetSEPSIValue>
	,private darwinet::c_MIVValueInstanceListener
{
  typedef _COM_CLASS inherited;
  IDarwinetSEPSIValueEventsDisp FEvents;

public:
  __fastcall TDarwinetSEPSIValueImpl();
  __fastcall TDarwinetSEPSIValueImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetSEPSIValueImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);


  // IDarwinetSEPSIValue
protected:
  STDMETHOD(setTo(BSTR sValue));

private:

	/**
	  * Proprietary destructor
	  */
	__fastcall  ~TDarwinetSEPSIValueImpl();

	// Begin c_MIVValueInstanceListener

	/**
	  * Act on the change made to c_MIVValueInstance value
	  */
	virtual void actOnMIVValueInstanceValueChanged();

	// End c_MIVValueInstanceListener

};




#endif //DarwinetSEPSIValueImplH
