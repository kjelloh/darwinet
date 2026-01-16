//---------------------------------------------------------------------------

#pragma hdrstop

#include "ThreadHiveFrameWork.h"
#include "BusinessLogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/**
  * Provided client request a Hived Thread to do work.
  * When this Hive becomes active a Thread will call the client
  * to do work until the client cancels the work or the Hive becomes inactive.
  */
void c_ThreadHive::requestWork(c_HivedThreadClientIfc* pHivedThreadClient) {
	LOG_NOT_IMPLEMENTED;
}

