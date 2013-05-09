//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop



USEFORM("BusinessLogFormUnit.cpp", BusinessLogForm);
USEFORM("EditPropertiesFrameUnit.cpp", EditApplicationPropertiesFrame); /* TFrame: File Type */
USEFORM("EditPropertiesFormUnit.cpp", EditPropertiesForm);
USEFORM("ABOUT.cpp", AboutBox);
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

/**
  * RAD Studio XE Notes
  *
  * <package>
  *
  * Issues discussed and answered at:
  * https://forums.embarcadero.com/thread.jspa?threadID=86983&tstart=0
  * https://forums.embarcadero.com/thread.jspa?threadID=87057&tstart=0
  * https://forums.embarcadero.com/thread.jspa?threadID=86948&tstart=0
  *
  * Export classes using the PACKAGE macro.
  * class PACKAGE c_MyClass {
  *   // code goes here
  * }
  *
  * Ensure the "Requires" folder does not contain another package with the same contents.
  * RAD Studio will otherwise ask you to remove conflicting units from your package.
  *
  * By default RAD Stido will output the bpi and bpl files according to (Also see hel url ms-help://embarcadero.rs_xe2/rad/Paths_and_Directories_(C++).html)
  * <Tools>/<Options>/<Environment Options>/<Environment Variables> BDSCOMMONDIR (In Win7 "C:\Users\Public\Documents\RAD Studio\9.0")
  * <Tools>/<Options>/<Environment Options>/<C++ Options>/<Path and Directories>/<Package Output Directory> = $(BDSCOMMONDIR)\BPL
  * <Tools>/<Options>/<Environment Options>/<C++ Options>/<Path and Directories>/<BPI/LIB Output Directory> = $(BDSCOMMONDIR)\DCP
  *
  * <Client linking to Package>
  *
  * When linking to packge from another project note the following:
  * (*) Add path to the package header files to the <Project>/<Option>/<Directories and Conditionals>/<Include Path>.
  *     This enables your code to include these when compiling.
  * (*) Add "#pragma link "mypackage.bpi"" to one source unit of the client application.
  *     This seems to instruct the linker to link to the bpi-file.
  * (*) Add path to the package bpi-file files to the <Project>/<Option>/<Directories and Conditionals>/<Library Path>.
  *     This enables the linker to find the bpi-file.
  *     NOTE: The linker seems also use the PATH environment variable to search for files? I suspect that if the bpi-file
  *           is found in any of the paths defined in PATH it will find it regardless of the content of
  *           <Project>/<Option>/<Directories and Conditionals>/<Library Path>.
  * (*) Check the <Link with runtime packages> in <Project>/<Option>/<Packages>/<Runtime Packages>
  *     This seems to meand runtime linking. (I have not gotten static linking to work when the package conyains forms)
  * (*) Add the path to the bpi-file to enable compile time linkage to work. (bpi-file corresponds to lib-file for dll's)
  * (*) Distribute the bpl-file with the application (corresponds to a dll)
  *
  */

#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}
//---------------------------------------------------------------------------
