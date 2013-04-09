/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 #ifdef __BCPLUSPLUS__
// RAD Studio XE compilation
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
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
#endif // __BCPLUSPLUS__

