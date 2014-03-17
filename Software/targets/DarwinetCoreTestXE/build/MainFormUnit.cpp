//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormUnit.h"
#include "BusinessLogFormUnit.h"
#include "BusinessLogUnit.h"
#include "SEPSISeed.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DarwinetRADLibXE.bpi"

#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------

c_TestBenchClientSideProxy::shared_ptr pTestBenchClientSideProxy;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	if (!pTestBenchClientSideProxy) {
		pTestBenchClientSideProxy.reset(new c_TestBenchClientSideProxy());
		pTestBenchClientSideProxy->m_pGUIWindow = this->Handle;
	}
	// Dock the Business Log form to our main windows
	this->BottomPanel->Caption = "";
	TBusinessLogForm::instance()->ManualDock(this->BottomPanel,NULL,alClient);
	TBusinessLogForm::instance()->Align = alClient;
	TBusinessLogForm::instance()->Visible = true;
	LOG_BUSINESS(_UTF8sz("Application Started!"));

	this->GridPanel1->Caption = "";
	for (int i = 0; i < 4; ++i) {
		TMIVsViewFrame* pTMIVsViewFrame = new TMIVsViewFrame(this,i);
		m_MIVsViewFrames.push_back(pTMIVsViewFrame);
		pTMIVsViewFrame->Visible = true;
		pTMIVsViewFrame->Align = alClient;
		pTMIVsViewFrame->Parent = this->GridPanel1;
	}

//	seedsrc::integrate::test();
//	seedsrc::integrate2::test();
//	seedsrc::integrate3::test();
//	seedsrc::miv1::test();
//	seedsrc::miv2::test();
//	seedsrc::miv3::test();
//	seedsrc::miv4::test();
	seedsrc::miv5::test();
}
//---------------------------------------------------------------------------
