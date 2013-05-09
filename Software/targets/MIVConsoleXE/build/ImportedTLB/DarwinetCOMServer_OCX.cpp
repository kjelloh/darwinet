// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 46046 $
// File generated on 2013-05-09 19:06:35 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\subversion\darwinet\trunk\Software\targets\DarwinetCOMServerXE\build\.\Win32\Debug\DarwinetCOMServerXE.exe (1)
// LIBID: {C10A9DE6-1B79-4C29-8CD8-B621544D80F2}
// LCID: 0
// Helpfile: 
// HelpString: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// SYS_KIND: SYS_WIN32
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#pragma option -w-8122
#include "DarwinetCOMServer_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Darwinetcomserver_tlb
{

IDarwinetEnginePtr& TDarwinetEngine::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TDarwinetEngine::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TDarwinetEngine::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TDarwinetEngine::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TDarwinetEngine::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TDarwinetEngine::ConnectTo(IDarwinetEnginePtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TDarwinetEngine::InitServerData()
{
  static Vcl::Oleserver::TServerData sd;
  sd.ClassID = CLSID_DarwinetEngine;
  sd.IntfIID = __uuidof(IDarwinetEngine);
  sd.EventIID= __uuidof(IDarwinetEngineEvents);
  ServerData = &sd;
}

void __fastcall TDarwinetEngine::InvokeEvent(int id, Vcl::Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 201: {
      if (OnonCreated) {
        (OnonCreated)(this);
      }
      break;
      }
    default:
      break;
  }
}

Darwinetcomserver_tlb::IDarwinetDomain* __fastcall TDarwinetEngine::getDomain(void)
{
  return  GetDefaultInterface()->getDomain();
}

IDarwinetDomainPtr& TDarwinetDomain::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TDarwinetDomain::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TDarwinetDomain::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TDarwinetDomain::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TDarwinetDomain::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TDarwinetDomain::ConnectTo(IDarwinetDomainPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TDarwinetDomain::InitServerData()
{
  static Vcl::Oleserver::TServerData sd;
  sd.ClassID = CLSID_DarwinetDomain;
  sd.IntfIID = __uuidof(IDarwinetDomain);
  sd.EventIID= __uuidof(IDarwinetDomainEvents);
  ServerData = &sd;
}

void __fastcall TDarwinetDomain::InvokeEvent(int id, Vcl::Oleserver::TVariantArray& params)
{
  switch(id)
  {
    default:
      break;
  }
}

Darwinetcomserver_tlb::IDarwinetDomainView* __fastcall TDarwinetDomain::getView(void)
{
  return  GetDefaultInterface()->getView();
}

IDarwinetDomainViewPtr& TDarwinetDomainView::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TDarwinetDomainView::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TDarwinetDomainView::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TDarwinetDomainView::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TDarwinetDomainView::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TDarwinetDomainView::ConnectTo(IDarwinetDomainViewPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TDarwinetDomainView::InitServerData()
{
  static Vcl::Oleserver::TServerData sd;
  sd.ClassID = CLSID_DarwinetDomainView;
  sd.IntfIID = __uuidof(IDarwinetDomainView);
  sd.EventIID= __uuidof(IDarwinetDomainViewEvents);
  ServerData = &sd;
}

void __fastcall TDarwinetDomainView::InvokeEvent(int id, Vcl::Oleserver::TVariantArray& params)
{
  switch(id)
  {
    default:
      break;
  }
}

Darwinetcomserver_tlb::IDarwinetMIV* __fastcall TDarwinetDomainView::getMIV(void)
{
  return  GetDefaultInterface()->getMIV();
}

IDarwinetMIVPtr& TDarwinetMIV::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TDarwinetMIV::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TDarwinetMIV::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TDarwinetMIV::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TDarwinetMIV::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TDarwinetMIV::ConnectTo(IDarwinetMIVPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TDarwinetMIV::InitServerData()
{
  static Vcl::Oleserver::TServerData sd;
  sd.ClassID = CLSID_DarwinetMIV;
  sd.IntfIID = __uuidof(IDarwinetMIV);
  sd.EventIID= __uuidof(IDarwinetMIVEvents);
  ServerData = &sd;
}

void __fastcall TDarwinetMIV::InvokeEvent(int id, Vcl::Oleserver::TVariantArray& params)
{
  switch(id)
  {
    default:
      break;
  }
}

void __fastcall TDarwinetMIV::setValue(BSTR sInstancePath/*[in]*/, BSTR sValue/*[in]*/)
{
  GetDefaultInterface()->setValue(sInstancePath/*[in]*/, sValue/*[in]*/);
}


};     // namespace Darwinetcomserver_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Darwinetcomserver_ocx
{

void __fastcall PACKAGE Register()
{
  // [4]
  System::Classes::TComponentClass cls_svr[] = {
                              __classid(Darwinetcomserver_tlb::TDarwinetEngine), 
                              __classid(Darwinetcomserver_tlb::TDarwinetDomain), 
                              __classid(Darwinetcomserver_tlb::TDarwinetDomainView), 
                              __classid(Darwinetcomserver_tlb::TDarwinetMIV)
                           };
  System::Classes::RegisterComponents("ActiveX", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Darwinetcomserver_ocx
