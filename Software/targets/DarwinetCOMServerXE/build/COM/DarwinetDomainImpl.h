// ---------------------------------------------------------------------------
// DarwinetDomainImpl.h : Declaration of the TDarwinetDomainImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetDomainImplH
#define DarwinetDomainImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"

// ---------------------------------------------------------------------------
// TDarwinetDomainImpl     Implements IDarwinetDomain, default interface of DarwinetDomain
// Events         : Implements IDarwinetDomainEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    : Represents a Darwinet Domain
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetDomainImpl : public TCppAutoObjectEvent<IDarwinetDomain>
{
  typedef _COM_CLASS inherited;
  IDarwinetDomainEventsDisp FEvents;

public:
  __fastcall TDarwinetDomainImpl();
  __fastcall TDarwinetDomainImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetDomainImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);
  

  // IDarwinetDomain
protected:
};




#endif //DarwinetDomainImplH
