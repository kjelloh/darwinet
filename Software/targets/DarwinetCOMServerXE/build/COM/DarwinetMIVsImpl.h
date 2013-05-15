// ---------------------------------------------------------------------------
// DarwinetMIVsImpl.h : Declaration of the TDarwinetMIVsImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetMIVsImplH
#define DarwinetMIVsImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"
#include "InProcDarwinetEngineFramework.h"

// ---------------------------------------------------------------------------
// TDarwinetMIVsImpl     Implements IDarwinetMIVs, default interface of DarwinetMIVs
// Events         : Implements IDarwinetMIVsEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    :
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetMIVsImpl : public TCppAutoObjectEvent<IDarwinetMIVs>
{
  typedef _COM_CLASS inherited;
  IDarwinetMIVsEventsDisp FEvents;

  /**
	* Private storage to our actual MIVs instance
	*/
  darwinet::c_MIVs::shared_ptr m_pMIVs;

public:
  __fastcall TDarwinetMIVsImpl();
  __fastcall TDarwinetMIVsImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetMIVsImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);
  

  // IDarwinetMIVs
protected:
  STDMETHOD(setValue(BSTR sInstancePath, BSTR sValue));
};




#endif //DarwinetMIVsImplH
