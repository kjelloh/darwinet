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
	* Private storage to our actual SEPSI instance
	*/
  darwinet::c_SEPSI::shared_ptr m_pSEPSI;

public:
  __fastcall TDarwinetSEPSIImpl();
  __fastcall TDarwinetSEPSIImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetSEPSIImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);
  

  // IDarwinetSEPSI
protected:
  STDMETHOD(setValue(BSTR sInstancePath, BSTR sValue));
};




#endif //DarwinetSEPSIImplH
