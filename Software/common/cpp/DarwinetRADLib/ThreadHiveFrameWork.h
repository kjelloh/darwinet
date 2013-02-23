/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef ThreadHiveFrameWorkH
#define ThreadHiveFrameWorkH
#include <boost/shared_ptr.hpp>
#include <map>
//---------------------------------------------------------------------------
class c_HivedThreadClientIfc; // Forward
//---------------------------------------------------------------------------
class c_ThreadHive; // Forward
//---------------------------------------------------------------------------
/**
  * Models a Thread in the Hive
  */
class c_HivedThread {
public:

	typedef boost::shared_ptr<c_HivedThread> shared_ptr;

	/**
	  * Creates a new instance and returns it as a shared pointer
	  */
	static c_HivedThread* create(c_ThreadHive* pThreadHive);

	/**
	  * Virtual Destructor
	  */
	virtual ~c_HivedThread();

private:
	/**
	  * Private constructor to force usage of create()
	  */
	c_HivedThread(c_ThreadHive* pThreadHive);

	c_ThreadHive* m_pThreadHive;

};
//---------------------------------------------------------------------------
class c_ThreadHiveOwnerIfc; // Forward
//---------------------------------------------------------------------------
/**
  * Models a Hive of worker threads.
  */
class c_ThreadHive {
public:

	typedef boost::shared_ptr<c_ThreadHive> shared_ptr;

	/**
	  * Creates a new instance and returns it as a shared pointer
	  */
	static c_ThreadHive* create(c_ThreadHiveOwnerIfc* pClient);

	/**
	  * Virtual Destructor
	  */
	virtual ~c_ThreadHive();

	/**
	  * Provided client request a Hived Thread to do work.
	  * When this Hive becomes active a Thread will call the client
	  * to do work until the client cancels the work or the Hive becomes inactive.
	  */
	void requestWork(c_HivedThreadClientIfc* pHivedThreadClient);

	/**
	  * provided client requests work to be canceled.
	  * The Clients Thread will be catched in the Hive.
	  */
	void cancelWork(c_HivedThreadClientIfc* pHivedThreadClient);

	/**
	  * Sets the Active property of this Hive.
	  * If set to true all Hived Threads will be put to work.
	  * If set to false, threads that returns to the Hiove will not be let out again.
	  */
	void setActive(bool active);

	/**
	  * Will not return until all threads are in the Hive.
	  */
	void deactivateNadWaitForAllThreadsInHive();

private:

	/**
	  * Returns the Hived Thread for provided client,
	  * Creating it is it does not yet exist.
	  */
	c_HivedThread::shared_ptr getHivedThread(c_HivedThreadClientIfc* pHivedThreadClient);

	/**
	  * Private constructor to force usage of create()
	  */
	c_ThreadHive(c_ThreadHiveOwnerIfc* pOwner);

	c_ThreadHiveOwnerIfc* m_pOwner;

	/**
	  * Private storage of the threads of this Hive
	  */
	std::map<c_HivedThreadClientIfc*,c_HivedThread::shared_ptr> m_HivedThreads;

};
//---------------------------------------------------------------------------
/**
  * Models the interface to be implemented by a owner of a thread hive
  */
class c_ThreadHiveOwnerIfc {
public:

	// Begin c_ThreadHiveOwnerIfc

	/**
	  * Called by Thread Hive constructor
	  */
	virtual void onThreadHiveConstructing(c_ThreadHive* pThreadHive) = 0;

	// End c_ThreadHiveOwnerIfc
};
//---------------------------------------------------------------------------
/**
  * Models the interface to be implemented by the client of a Hived Thread
  */
class c_HivedThreadClientIfc {
public:

	// Begin c_HivedThreadClientIfc

	/**
	  * Called by Hived Thread constructor
	  */
	virtual void onHivedThreadConstruct(c_HivedThread* pThread) = 0;

	/**
	  * Called by Hived Thread to do some work.
	  * Do not block this call. The Hive Thread
	  * will continue to call this method as long as the thread
	  * is active.
	  */
	virtual void onHiveThreadWork(c_HivedThread* pThread) = 0;

	// End c_HivedThreadClientIfc
};
//---------------------------------------------------------------------------


#endif
