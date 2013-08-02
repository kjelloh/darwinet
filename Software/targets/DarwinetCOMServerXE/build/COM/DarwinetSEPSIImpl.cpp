// ---------------------------------------------------------------------------
// DARWINETMIVIMPL : Implementation of TDarwinetSEPSIImpl (CoClass: DarwinetSEPSI, Interface: IDarwinetSEPSI)
// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DarwinetSEPSIImpl.h"
#include "BusinessLogUnit.h"

// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl()
{
	LOG_METHOD_SCOPE;
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl(const System::_di_IInterface Controller)
							  : inherited(Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("const System::_di_IInterface Controller"));
}


// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl
// ---------------------------------------------------------------------------
__fastcall TDarwinetSEPSIImpl::TDarwinetSEPSIImpl(Comobj::TComObjectFactory* Factory,
									  const System::_di_IInterface Controller)
							  : inherited(Factory, Controller)
{
	LOG_METHOD_SCOPE_S(_UTF8sz("Comobj::TComObjectFactory* Factory,const System::_di_IInterface Controller"));
	// Bind us to the Engine
	this->m_pDarwinetEngineSEPSI = darwinet::engine()->getClientProxyInterface()->getSEPSI(Controller,this);
}

void __fastcall TDarwinetSEPSIImpl::EventSinkChanged(const System::_di_IInterface EventSink)
{
	LOG_METHOD_SCOPE;
  FEvents.Bind(EventSink);
}

// ---------------------------------------------------------------------------
// TDarwinetSEPSIImpl - Class Factory
// ---------------------------------------------------------------------------
static void createFactory()
{
  new TCppAutoObjectFactory<TDarwinetSEPSIImpl>(Comserv::GetComServer(),
						   __classid(TDarwinetSEPSIImpl),
						   CLSID_DarwinetSEPSI,
						   Comobj::ciMultiInstance,
						   Comobj::tmApartment);
}
#pragma startup createFactory 32

STDMETHODIMP TDarwinetSEPSIImpl::getValue(BSTR sInstancePath, DarwinetSEPSIValue** ppValue)


{
	LOG_METHOD_SCOPE;

	// Code below based on discussion forum answer at https://forums.embarcadero.com/message.jspa?messageID=566825&tstart=0
	if (!ppValue) {
		// The caller did not provide the "pointer-to-pointer" we are to modify
		return E_POINTER;
	}

	try
	{
		*ppValue = NULL; // Deafult
		if (!m_COMIDarwinetSEPSIValue)
		{
			c_LogString sMessage(__FUNCTION__" Called CoDarwinetSEPSIValue::Create() to create m_COMIDarwinetSEPSIValue");
			LOG_DEVELOPMENT_TRACE(sMessage);
			m_COMIDarwinetSEPSIValue = CoDarwinetSEPSIValue::Create();
			if (!m_COMIDarwinetSEPSIValue) {
				// Failed to create the Value instance
				return E_FAIL;
			}
		}

		// Return the result of setting the returned parameter to the Value Interface (calls interface AddRef() internally)
		return m_COMIDarwinetSEPSIValue->QueryInterface(IID_IDarwinetSEPSIValue,(void**)ppValue);

		/* Alternatively:
		*ppValue = m_COMIDarwinetSEPSIValue;
		(*ppValue)->AddRef();
		return S_OK;
		*/
	}
	catch (const Exception &)
	{
		return E_UNEXPECTED;
	}
}

/**
* Destructor added to track destruction of this instance
*/
__fastcall TDarwinetSEPSIImpl::~TDarwinetSEPSIImpl() {
	LOG_METHOD_SCOPE;
}

