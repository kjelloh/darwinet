/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#ifdef __BCPLUSPLUS__
#pragma hdrstop
#endif
//---------------------------------------------------------------------------
#include "IDEInterfacedSource.h"
#ifdef __BCPLUSPLUS__
#include <SyncObjs.hpp> // TCriticalSection
#include <Forms.hpp>
#endif

//---------------------------------------------------------------------------

#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif




#ifdef __BCPLUSPLUS__
typedef TCriticalSection c_CriticalSection;
#else

class c_CriticalSectionImpl {
public:
	c_CriticalSectionImpl()
	{;}

	void Acquire() {
		#warning c_CriticalSectionImpl::Acquire() not implemented for this build environment
	}

	void Release() {
		#warning c_CriticalSectionImpl::Release() not implemented for this build environment
	}
private:
};

typedef c_CriticalSectionImpl c_CriticalSection;
#endif


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class c_ThreadGateImpl : public c_ThreadGateIfc {
public:

	/**
	  * Constructor
	  */
	c_ThreadGateImpl()
		: m_pCriticalSection(new c_CriticalSection()) {
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
	c_CriticalSection* m_pCriticalSection;
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
//---------------------------------------------------------------------------

