// ---------------------------------------------------------------------------
// DarwinetDomainViewImpl.h : Declaration of the TDarwinetDomainViewImpl
// ---------------------------------------------------------------------------
#ifndef DarwinetDomainViewImplH
#define DarwinetDomainViewImplH

#include <ComServ.hpp>
#include <axbase.h>
#include "DarwinetCOMServer_TLB.h"

// ---------------------------------------------------------------------------
// TDarwinetDomainViewImpl     Implements IDarwinetDomainView, default interface of DarwinetDomainView
// Events         : Implements IDarwinetDomainViewEvents, the default source interface
// ThreadingModel : tmApartment
// Dual Interface : TRUE
// Event Support  : TRUE
// Description    : 
// ---------------------------------------------------------------------------
class DAX_COM_CLASS TDarwinetDomainViewImpl : public TCppAutoObjectEvent<IDarwinetDomainView>
{
  typedef _COM_CLASS inherited;
  IDarwinetDomainViewEventsDisp FEvents;

public:
  __fastcall TDarwinetDomainViewImpl();
  __fastcall TDarwinetDomainViewImpl(const System::_di_IInterface Controller);
  __fastcall TDarwinetDomainViewImpl(Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller);
  void __fastcall EventSinkChanged(const System::_di_IInterface EventSink);
  

  // IDarwinetDomainView
protected:
  IDarwinetSEPSI* STDMETHODCALLTYPE getSEPSI();
private:
	/**
	  * Private storage of a smart pointer to our MIV instance
	  */
	TCOMIDarwinetSEPSI m_COMIDarwinetSEPSI;
};




#endif //DarwinetDomainViewImplH
