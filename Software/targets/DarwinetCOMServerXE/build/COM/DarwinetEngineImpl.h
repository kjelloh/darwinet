// ---------------------------------------------------------------------------
// DarwinetEngineImpl.h : Declaration of the TDarwinetEngineImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetEngineImplH
#define DarwinetEngineImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"

// ---------------------------------------------------------------------------
// TDarwinetEngineImpl     Implements IDarwinetEngine, default interface of DarwinetEngine
// Events         : Implements IDarwinetEngineEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    : The Core Darwinet Engine
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetEngineImpl : public TCppAutoObjectEvent<IDarwinetEngine>
{
  typedef _COM_CLASS inherited;
  IDarwinetEngineEventsDisp FEvents;

public:
  __fastcall TDarwinetEngineImpl();
  __fastcall TDarwinetEngineImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetEngineImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);
  

  // IDarwinetEngine
protected:
  IDarwinetDomain* STDMETHODCALLTYPE getDomain();
};




#endif //DarwinetEngineImplH
