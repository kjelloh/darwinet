//---------------------------------------------------------------------------

#ifndef DarwinetWindowsGUIInterfaceH
#define DarwinetWindowsGUIInterfaceH
#include <windows.h>
//---------------------------------------------------------------------------
namespace seedsrc {

	namespace miv5 {

		enum e_WINDOWS_MESSAGE_ID {
			eWINDOWS_MESSAGE_ID_Undefined
			,eWINDOWS_MESSAGE_ID_OnDarwinetSignal = WM_USER+1
			,eWINDOWS_MESSAGE_ID_OnDarwinetViewChange
			,eWINDOWS_MESSAGE_ID_Unknown
		};

	};
}

/**
  * Tie the GUI with the current iteration code
  */
namespace darwinet_seed = seedsrc::miv5;

#endif
