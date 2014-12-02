//---------------------------------------------------------------------------


#pragma hdrstop

#include "IDEInterfacedSource.h"
#include <SyncObjs.hpp> // TCriticalSection
//#include <Forms.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class c_ThreadGateImpl : public c_ThreadGateIfc {
public:

	/**
	  * Constructor
	  */
	c_ThreadGateImpl()
		: m_pCriticalSection(new TCriticalSection()) {
	}
	/**
	  * Claim access through the gate.
	  * Only one thread at a time will gain access.
	  * This method retrusn when access is provided by the gate
	  * (Any other thread has left the scope guarded by the gate)
	  */
	virtual void claim() {
		m_pCriticalSection->Acquire();
	}

	/**
	  * Release the thread gate. This will enable any other thread
	  * to claim access to the scope guarded by this thread gate.
	  */
	virtual void release() {
		m_pCriticalSection->Release();
	}

private:
	/**
	  * Private storage of thread synchronizing instance to use
	  */
	TCriticalSection* m_pCriticalSection;
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/**
  * Constructs a new thread gate
  */
c_ThreadGate::c_ThreadGate()
	: m_pGate(new c_ThreadGateImpl()) {
}
//---------------------------------------------------------------------------
/**
  * Claim access through the gate.
  * Only one thread at a time will gain access.
  * This method retrusn when access is provided by the gate
  * (Any other thread has left the scope guarded by the gate)
  */
void c_ThreadGate::claim() {
	m_pGate->claim();
}
//---------------------------------------------------------------------------
/**
  * Release the thread gate. This will enable any other thread
  * to claim access to the scope guarded by this thread gate.
  */
void c_ThreadGate::release() {
	m_pGate->release();
}

