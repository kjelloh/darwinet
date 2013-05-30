// ---------------------------------------------------------------------------
// DarwinetSEPSIImpl.h : Declaration of the TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetSEPSIImplH
#define DarwinetSEPSIImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"
#include "InProcDarwinetEngineFramework.h"

// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl     Implements IDarwinetSEPSI, default interface of DarwinetSEPSI
// Events         : Implements IDarwinetSEPSIEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    :
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetSEPSIImpl : public TCppAutoObjectEvent<IDarwinetSEPSI>
{
  typedef _COM_CLASS inherited;
  IDarwinetSEPSIEventsDisp FEvents;

  /**
	* Private storage to our actual SEPSI instance of the Darwinet Engine
	*/
  darwinet::c_SEPSI::shared_ptr m_pDarwinetEngineSEPSI;

public:
  __fastcall TDarwinetSEPSIImpl();
  __fastcall TDarwinetSEPSIImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetSEPSIImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);

  // IDarwinetSEPSI
protected:
  STDMETHOD(getValue(BSTR sInstancePath, DarwinetSEPSIValue** pValue));


private:

  /**
	* Destructor added to track destruction of this instance
	*/
  virtual __fastcall ~TDarwinetSEPSIImpl();

	/**
	  * Dummy instance of the value we return in getValue() method.
	  * TODO: Replace by mechanism that really finds an existing instance
	  * bound to the actual instance in our Darwinet Engine.
	  */
	TCOMIDarwinetSEPSIValue m_COMIDarwinetSEPSIValue;
};




#endif //DarwinetSEPSIImplH
