//---------------------------------------------------------------------------

#ifndef IDEInterfacedSourceH
#define IDEInterfacedSourceH
//---------------------------------------------------------------------------
#include "FilePathFramework.h" // c_FilePath
//---------------------------------------------------------------------------

/**
  * This unit contains classes and types that tries to hide
  * the actual development tool (IDE = Integrated development environment) from the client code.
  * Use these types in other units where you whant
  * to isolate the source code from the libraries provided
  * by the IDE/development tool.
  */

/**
  * Implements an interface to a thread gate.
  * The actual implementation of the thread gate is hidden
  * from the client.
  */
class c_ThreadGateIfc {
public:
	/**
	  * Claim access through the gate.
	  * Only one thread at a time will gain access.
	  * This method returns when access is provided by the gate
	  * (Any other thread has left the scope guarded by the gate)
	  */
	virtual void claim()=0;

	/**
	  * Release the thread gate. This will enable any other thread
	  * to claim access to the scope guarded by this thread gate.
	  */
	virtual void release()=0;
};

/**
  * Helper class to instanciate development tool and environment independent
  * thread gate instances.
  * Instanciate one for each scope you whant to synchronize thread access too.
  * Use the instance together with c_ThreadSynchronizer in the following way.
  * ...
  * // Define the thread gate somewhere for your resource
  * c_ThreadGate myThreadGate;
  * ...
  * Use the gate through an accessor (Constructor will wait for access and
  * destructor will release access)
  * {
  *     c_ThreadSynchronizer ts(myThreadGate);
  *     // The following section of this scope will have only one thread at a time
  *     // run through it.
  * }
  */
class PACKAGE c_ThreadGate : public c_ThreadGateIfc {
public:
	/**
	  * Constructs a new thread gate
	  */
	c_ThreadGate();

	/**
	  * Claim access through the gate.
	  * Only one thread at a time will gain access.
	  * This method retrusn when access is provided by the gate
	  * (Any other thread has left the scope guarded by the gate)
	  */
	virtual void claim();

	/**
	  * Release the thread gate. This will enable any other thread
	  * to claim access to the scope guarded by this thread gate.
	  */
	virtual void release();

private:
	/**
	  * Private storage of actual thread gate to use.
	  * Instanciated by the constructor
	  */
	c_ThreadGateIfc* m_pGate;
};

/**
  * Class that implements a gate that will allow only
  * one thread at a time to pass through.
  * Hides the actual implementation.
  */
class c_ThreadSynchronizer {
public:
	/**
	  * Creates a thread synchronizer using provided
	  * thread gate. Constructor will not return until
	  * access to gate is provided.
	  */
	c_ThreadSynchronizer(c_ThreadGate& gate)
		: m_gate(gate) {
		m_gate.claim();
	}

	/**
	  * Destructs the synchronizer again. The desctructor
	  * will free the gate for others to access it.
	  */
	~c_ThreadSynchronizer() {
		m_gate.release();
	}

private:

	/**
	  * Private storage of thread gate instance to use
	  */
	c_ThreadGate m_gate;
};

#endif
