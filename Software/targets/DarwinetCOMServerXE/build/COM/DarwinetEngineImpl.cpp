// ---------------------------------------------------------------------------
// DARWINETENGINEIMPL : Implementation of TDarwinetEngineImpl (CoClass: DarwinetEngine, Interface: IDarwinetEngine)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetEngineImpl.h"


// ---------------------------------------------------------------------------
// TDarwinetEngineImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetEngineImpl::TDarwinetEngineImpl()
{
}


// ---------------------------------------------------------------------------
// TDarwinetEngineImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetEngineImpl::TDarwinetEngineImpl(const System::_di_IInterface Controller)
                              : inherited(Controller)
{
}


// ---------------------------------------------------------------------------
// TDarwinetEngineImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetEngineImpl::TDarwinetEngineImpl(Comobj::TComObjectFactory* Factory,
                                      const System::_di_IInterface Controller)
                              : inherited(Factory, Controller)
{
}

void __fastcall TDarwinetEngineImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
	/**
	  * Bug fix of generated code.
	  * Original code was
	  * {
	  *   		FEvents.Bind(EventSink);
	  * }
	  *
	  * This method is called also when the client doisconnects from
	  * the server. It will then be called with a NULL sink (why?).
	  * Never the less, we add a check for NULL so that we do not call Bind with a NULL sink.
	  * Bug in auto-generated code for events. See https://forums.embarcadero.com/message.jspa?messageID=445574&tstart=0
	  * See http://www.techvanguards.com
	  */
	if (FEvents) {
		FEvents.Bind(EventSink);
	}
}

// ---------------------------------------------------------------------------
// TDarwinetEngineImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetEngineImpl>(Comserv::GetComServer(),
                           __classid(TDarwinetEngineImpl),
                           CLSID_DarwinetEngine,
                           Comobj::ciMultiInstance,
                           Comobj::tmApartment);
}
#pragma startup createFactory 32


IDarwinetDomain* STDMETHODCALLTYPE TDarwinetEngineImpl::getDomain()
{
}


