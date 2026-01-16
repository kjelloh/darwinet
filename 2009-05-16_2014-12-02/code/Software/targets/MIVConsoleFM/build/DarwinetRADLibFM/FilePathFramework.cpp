//---------------------------------------------------------------------------
#pragma hdrstop

#include "FilePathFramework.h"
//---------------------------------------------------------------------------
#ifdef _DEBUG
	#define COMPILE_TEST_CODE
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

int FilePathFramework_main() {
#ifdef COMPILE_TEST_CODE
	// Test compile
	// Code will be removed by linker optimizer (not called)
	c_FilePath test_path; // test template instansiation.
	c_FilePathFramework test_framework; // test template instansiation.
	if (c_FilePathFramework::fileExists(c_FilePath(u"dummy_file.txt"))) {
		LOG_BUSINESS(_UTF8sz("File Exists"));
	}
#endif
	return 0;
}

#undef COMPILE_TEST_CODE

