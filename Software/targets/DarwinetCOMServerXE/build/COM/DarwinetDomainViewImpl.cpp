// ---------------------------------------------------------------------------
// DARWINETDOMAINVIEWIMPL : Implementation of TDarwinetDomainViewImpl (CoClass: DarwinetDomainView, Interface: IDarwinetDomainView)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetDomainViewImpl.h"


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl()
{
}


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl(const System::_di_IInterface Controller)
                              : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetDomainViewImpl::TDarwinetDomainViewImpl(Comobj::TComObjectFactory* Factory,
                                      const System::_di_IInterface Controller)
                              : inherited(Factory, Controller)
{
}

void __fastcall TDarwinetDomainViewImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetDomainViewImpl>(Comserv::GetComServer(),
                           __classid(TDarwinetDomainViewImpl),
                           CLSID_DarwinetDomainView,
                           Comobj::ciMultiInstance,
                           Comobj::tmApartment);
}
#pragma startup createFactory 32


