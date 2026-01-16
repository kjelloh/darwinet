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

#include "DataRepresentationFrameWork.h"
#include <stdio.h> // sprintf
#include <algorithm> // std::find...
#include <functional> // std::not1...
#include <ctype.h> // isspace...
#include "BusinessLogUnit.h"
#include <sstream>
// #include <locale>

#include <iomanip> // std::setfill(),std::setw()...

#ifdef __BCPLUSPLUS__
# pragma warn -8072 // Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#endif
#include <boost/format.hpp>
#ifdef __BCPLUSPLUS__
# pragma warn +8072 // Enable again. See above
#endif

// Defined way of including boost utf8 codecvt
#define BOOST_UTF8_BEGIN_NAMESPACE namespace boost {namespace utf8 {
#define BOOST_UTF8_END_NAMESPACE } }
#define BOOST_UTF8_DECL

// Note on Warning W8068 in utf8_codecvt_facet.hpp
// note the following code will generate on some platforms where
// wchar_t is defined as UCS2.  The warnings are superfluous as
// the specialization is never instantitiated with such compilers.
#ifdef __BCPLUSPLUS__
# pragma warn -8068 // See note above 101112/KoH
#endif
// #include <libs/detail/utf8_codecvt_facet.cpp>
#include "boost/detail/utf8_codecvt_facet.hpp"
#ifdef __BCPLUSPLUS__
# pragma warn .8068 // See note above 101112/KoH
#endif

#include "utf8/source/utf8.h" // From http://sourceforge.net/projects/utfcpp/
#include "common/unicode/unistr.h" // C++ UnicodeString from icu4c

#ifdef __BCPLUSPLUS__
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

/**
  * Test code for the methods of this unit
  */
bool c_DataRepresentationFramework::doTests() {

	bool result = true; // default

	// Test of representation aware string classes

	/*

	Representation aware strings enforces the following policy:

	1. Explicit Construct from anonymous strings trusted. The programmer
	   expresses in code that input string is in correct representation.
	2. Implicit type-cast from anonymous string NOT allowed. Will generate
	   a compile error. The programmer is forced to express asumed representation
	   of anonymous string using wrapper or explicit construct.
	3. Assign or append from anonymous string is NOT allowed. Will generate
	   a compile error. The programmer is forced to use explicit constructor
	   or wrapper to express the assumed representation of the anonymous string
	4. Type-cast from representation conformant string class is allowed
	   when possible. Like from ASCII to most of the other classes.
	5. Any representation transformation must be expressed explicitly
	   using toXXX methods. No representation change will take place
	   Implicitly. The programmer is forced to express representation
	   transformation in code.
	6. Data type transformation will occur implicit. Like between
	   char strings, wide char strings and four byte char strings.
	   The framework guards string encoding, not string memory construct.

	*/

//	#define COMPILE_UNALLOWED_CONSTRUCTS // Try to compile constructs that must generate compile errors
	#undef COMPILE_UNALLOWED_CONSTRUCTS // Do NOT compile constructs that must generate compile errors

	// OK: Default construct
	{
		c_DataRepresentationFramework::c_AsciiString sAsciiString;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String;
		c_DataRepresentationFramework::c_UTF8String sUTF8String;
		c_DataRepresentationFramework::c_BinaryString sBinaryString;
		c_DataRepresentationFramework::c_UTF16String sUTF16String;
		c_DataRepresentationFramework::c_UCF4String sUCF4String;
	}

	// Operators on Ascii strings
	{
		typedef c_DataRepresentationFramework::c_AsciiString t_tested_string;

		t_tested_string s1;
		t_tested_string s2;

		s1 = s1 + s2;
	}
	// Operators on Ascii strings
	{
		typedef c_DataRepresentationFramework::c_UTF8String t_tested_string;

		t_tested_string s1;
		t_tested_string s2;

		s1 = s1 + s2;
	}

	// Explicit from anonymous char.
	{

		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		char source = 'c';
		c_DataRepresentationFramework::c_AsciiString sAsciiString(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Explicit from anonymous char array.
	{
		const char* source = "This is an anonymous string";

		c_DataRepresentationFramework::c_AsciiString sAsciiString(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String(source);
	}

	// Explicit from anonymous string
	{
		std::string source("This is an anonymous string");

		c_DataRepresentationFramework::c_AsciiString sAsciiString(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String(source);
	}

	{
		c_DataRepresentationFramework::c_ISO_8859_1_String source1("This is an ISO 8859 string with едц");
		c_DataRepresentationFramework::c_ISO_8859_1_String source2("This is an ISO 8859 string with едц");

		source1 = source2;
		source1 += source2;
		source1 = source1 + source2;

	}

	// Implicit from anonymous char.
	{
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		char source = 'c';
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Copy construct
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source;
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source;
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = source;
		sCppLiteralString = source;
		sISO_8859_1_String = source;
		sUTF8String = source;
		sBinaryString = source;
		sUTF16String = source;
		sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += source;
		sCppLiteralString += source;
		sISO_8859_1_String += source;
		sUTF8String += source;
		sBinaryString += source;
		sUTF16String += source;
		sUCF4String += source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Implicit from anonymous char array.
	{
		const char* source = "This is an anonymous char array";

		// Copy construct
		#ifdef __BCPLUSPLUS__
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source;
		#else
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source);
		#endif
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source;
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sBinaryString = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = source;
		sCppLiteralString = source;
		sISO_8859_1_String = source;
		sUTF8String = source;
		sUTF16String = source;
		sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sBinaryString += source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += source;
		sCppLiteralString += source;
		sISO_8859_1_String += source;
		sUTF8String += source;
		sUTF16String += source;
		sUCF4String += source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Implicit from anonymous string
	{
		std::string source("This is an anonymous string");

		// Copy construct
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source;
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sBinaryString = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = source;
		sCppLiteralString = source;
		sISO_8859_1_String = source;
		sUTF8String = source;
		sUTF16String = source;
		sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sBinaryString += source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += source;
		sCppLiteralString += source;
		sISO_8859_1_String += source;
		sUTF8String += source;
		sUTF16String += source;
		sUCF4String += source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Explicit from ascii
	{
		c_DataRepresentationFramework::c_AsciiString source("This is an ascii string");

		// Note. Asuming the AScii string holds only 0..127 ascii chars the following holds.
		//       But Ascii is allowed to be constructed from anonymous input which potentially
		//       may result in AScii string containing non-ascii chars... But this
		//       is a coding error.
		c_DataRepresentationFramework::c_AsciiString sAsciiString(source); // Ascii is Ascii
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString(source); // Ascii is CPP literal
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String(source); // Ascii is ISO 8859-1
		c_DataRepresentationFramework::c_UTF8String sUTF8String(source); // Ascii 0..127 is UTF-8
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source); // Binary holds anything
		c_DataRepresentationFramework::c_UTF16String sUTF16String(source); // Ascii is UTF-16
		c_DataRepresentationFramework::c_UCF4String sUCF4String(source); // Ascii is UFC-4
	}
	// Assign to ascii string
	{
		c_DataRepresentationFramework::c_AsciiString source("This is an ascii string");

		// Copy construct
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source;
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source; // Not needed. Assign to anonymous instead.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sAsciiString = source;
		sCppLiteralString = source;
		sISO_8859_1_String = source;
		sUTF8String = source;
		sUTF16String = source;
		sUCF4String = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString = source; // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sAsciiString += source;
		sCppLiteralString += source;
		sISO_8859_1_String += source;
		sUTF8String += source;
		sUTF16String += source;
		sUCF4String += source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString += source; // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Assign to wrapped ascii char array
	{
		const char* source = "This is an ascii string";
		typedef _Asciis t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sAsciiString = t_Wrapper(source);
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString = t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sAsciiString += t_Wrapper(source);
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString += t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}
	// Assign to wrapped ascii string
	{
		std::string source("This is an ascii string");
		typedef _Asciis t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sAsciiString = t_Wrapper(source);
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString = t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sAsciiString += t_Wrapper(source);
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString += t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}
	// Assign to Literal string
	{
		c_DataRepresentationFramework::c_CppLiteralString source("This is a C++ literal string with ц");

		/**
		  * Current framework asumes that the code is compiled in an environment
		  * where the source code character set is actually represented by windows code page 1252.
		  * C++ string literals will then be in windows code page 1252 which is
		  * 1-to-1 with ISO-8859-1 except code 0x80..0x9F which are asumed to
		  * be control characters in ISO-8859-1 but are printable characters in Code Page 1252.
		  * We choose to not bother with that distinction.
		  */

		// Copy construct
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source;
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source; // Provide this for conveniance
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source; // Not needed. Assign to anonymous instead.
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sCppLiteralString = source;
		sISO_8859_1_String = source; // Provide this for conveniance
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = source;
		sUTF8String = source;
		sBinaryString = source; // Not needed. Use append to anonymous char.
		sUTF16String = source;
		sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sISO_8859_1_String += source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += source;
		sUTF8String += source;
		sCppLiteralString += source; // Do not provide this. Should not be needed.
		sBinaryString += source; // Not needed. Use append to anonymous char.
		sUTF16String += source;
		sUCF4String += source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Assign to ISO 8859-1 string
	{
		c_DataRepresentationFramework::c_ISO_8859_1_String source("This is an ISO-8859-1 string with ц");

		// Copy construct
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = source;
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = source; // Do not provide this. Should not be needed.
		c_DataRepresentationFramework::c_UTF8String sUTF8String = source;
		c_DataRepresentationFramework::c_BinaryString sBinaryString = source; // Not needed. Assign to anonymous instead.
		c_DataRepresentationFramework::c_UTF16String sUTF16String = source;
		c_DataRepresentationFramework::c_UCF4String sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sISO_8859_1_String = source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = source;
		sCppLiteralString = source; // Do not provide this. Should not be needed.
		sUTF8String = source;
		sBinaryString = source; // Not needed. Use append to anonymous char.
		sUTF16String = source;
		sUCF4String = source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sISO_8859_1_String += source;
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += source;
		sUTF8String += source;
		sCppLiteralString += source; // Do not provide this. Should not be needed.
		sBinaryString += source; // Not needed. Use append to anonymous char.
		sUTF16String += source;
		sUCF4String += source;
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Explicit wrapped from Literal
	{
		c_DataRepresentationFramework::c_CppLiteralString source("This is an c++ literal string with едц");

		// Construct
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString(source); // Literal is literal :)
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String(source); // Asume Compiled in environment where Literal is Windows code page 1272 (A superset of ISO 8859-1). Note: Range 0x80..0x9F may contain printable chars in Code Page 1272 but is reserved for control chars in ISO-8859-1
		c_DataRepresentationFramework::c_BinaryString sBinaryString(source); // Binary holds everything
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString(source); // Needs narrowing
		c_DataRepresentationFramework::c_UTF8String sUTF8String(source); // Need expanding to multi byte
		c_DataRepresentationFramework::c_UTF16String sUTF16String(source); // Need expanding to multi byte
		c_DataRepresentationFramework::c_UCF4String sUCF4String(source); // Needs mapping to UCF. Range 0x80 .. 0x9F may contain printable chars but is reserved for UCF control chars
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

	}

	// Assign to wrapped literal char array
	{
		const char* source = "This is an literal string";
		typedef _Literalsz t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sBinaryString = t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sBinaryString += t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}
	// Assign to wrapped literal string
	{
		std::string source("This is an ascii string");
		typedef _Literals t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sBinaryString = t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sBinaryString += t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Assign to wrapped ascii char
	{
		char source('c');
		typedef _Asciic t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sAsciiString = t_Wrapper(source);
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString = t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sAsciiString += t_Wrapper(source);
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sBinaryString += t_Wrapper(source); // Not needed. Use append to anonymous char.
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Assign to wrapped literal char
	{
		char source('ц');
		typedef _Literalc t_Wrapper;

		// Copy construct
		c_DataRepresentationFramework::c_CppLiteralString sCppLiteralString = t_Wrapper(source);
		c_DataRepresentationFramework::c_ISO_8859_1_String sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		c_DataRepresentationFramework::c_AsciiString sAsciiString = t_Wrapper(source);
		c_DataRepresentationFramework::c_UTF8String sUTF8String = t_Wrapper(source);
		c_DataRepresentationFramework::c_BinaryString sBinaryString = t_Wrapper(source); // Not needed. Assign to anonymous instead.
		c_DataRepresentationFramework::c_UTF16String sUTF16String = t_Wrapper(source);
		c_DataRepresentationFramework::c_UCF4String sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Assign
		sCppLiteralString = t_Wrapper(source);
		sISO_8859_1_String = t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString = t_Wrapper(source);
		sUTF8String = t_Wrapper(source);
		sBinaryString = t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String = t_Wrapper(source);
		sUCF4String = t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS

		// Append
		sCppLiteralString += t_Wrapper(source);
		sISO_8859_1_String += t_Wrapper(source);
		#ifdef COMPILE_UNALLOWED_CONSTRUCTS
		sAsciiString += t_Wrapper(source);
		sUTF8String += t_Wrapper(source);
		sBinaryString += t_Wrapper(source); // Not needed. use anonymous rvalue
		sUTF16String += t_Wrapper(source);
		sUCF4String += t_Wrapper(source);
		#endif // COMPILE_UNALLOWED_CONSTRUCTS
	}

	// Implicit cast to ISO 8859-1 from wrapped anonymous char array
	{
		const char* source = "This is an anonymous string";

		methodWithParameter<c_DataRepresentationFramework::c_ISO_8859_1_String>(_Asciisz(source));
		methodWithParameter<c_DataRepresentationFramework::c_ISO_8859_1_String>(_Literalsz(source));
	}

	// Implicit cast to ISO 8859-1 from wrapped anonymous string
	{
		std::string source("This is an anonymous string");

		methodWithParameter<c_DataRepresentationFramework::c_ISO_8859_1_String>(_Asciis(source));
		methodWithParameter<c_DataRepresentationFramework::c_ISO_8859_1_String>(_Literals(source));
	}

	return result;


	#undef COMPILE_UNALLOWED_CONSTRUCTS // Do NOT compile constructs that must generate compile errors
}

/**
  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
  * Characters out of range will be logged.
  */
template <class S> c_DataRepresentationFramework::c_AsciiString toAsciiStringT(const S& s_) {
	c_DataRepresentationFramework::c_AsciiString result;
	// Copy only ascii chars (they map 1-to-1 between UTF-16 and Ascii)
	for (typename S::const_iterator iter = s_.begin(); iter != s_.end(); iter++) {
		if (*iter <= 0x7F) {
			result.anonymous() += static_cast<char>(*iter);
		}
		else {
			// Replace it
			result.anonymous() += '?';
			LOG_DESIGN_INSUFFICIENCY_I(c_DataRepresentationFramework::c_UTF8String("c_DataRepresentationFramework::toAsciiString failed for char 0x%X"),*iter);
		}
	}
	return result;
}

/**
  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
  * Characters out of range will be logged.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const std::string& sString) {
	return toAsciiStringT(sString);
}

/**
  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
  * Characters out of range will be logged.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const std::wstring& sWideString) {
	return toAsciiStringT(sWideString);
}

/**
  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
  * Characters out of range will be logged.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const c_DataRepresentationFramework::c_UTF16String& sUTF16String) {
	return toAsciiStringT(sUTF16String);
}

#ifdef __BCPLUSPLUS__
/**
  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
  * Characters out of range will be logged.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const c_IDEString& sIDEString) {
	c_DataRepresentationFramework::c_UTF16String sUTF16String(sIDEString.c_str());
	return toAsciiStringT(sUTF16String);
}
#endif

/**
  * Decodes provided string to an UTF-8 string
  */
c_DataRepresentationFramework::c_UTF8String c_DataRepresentationFramework::toUTF8String(const c_DataRepresentationFramework::c_UTF16String& sUTF16String) {
	c_DataRepresentationFramework::c_UTF8String result;
	/*
	From: http://lists.boost.org/boost-users/2009/06/49039.php

	The conversion routines you are looking for are std::mbsrtowcs() and
	std::wcsrtombs() in <cwchar>. You must set the global locale first before
	you use them so they know which multi-byte encoding they should use (try
	for example "en_US.UTF-8"). If you want your application to work on
	Windows, too, you can't use those functions unfortunately but must use
	MultiByteToWideChar() and WideCharToMultiByte() instead (as there is no
	UTF-8 locale on Windows).
	*/
// 101216/KoH Returns empty string... Have not time to investigate why this does not work
//	c_DataRepresentationFramework::c_UTF8String result;
//	utf8::utf16to8(sUTF16String.begin(), sUTF16String.end(), std::back_inserter(result));
//	return result;

	#ifdef __BCPLUSPLUS__
	UTF8String sUTF8String = UnicodeString(sUTF16String.c_str());
	result = _UTF8sz(sUTF8String.c_str());
	#else
	/**
	 * 130407/KoH
	 * icu::UnicodeString requires icu4c from http://site.icu-project.org.
	 * If you compiler does not recognize the code it may be that you have not Install it to your build environment or missed to add it to include paths.
	 * TODO: Add it as subversion external to this library (e.g. http://source.icu-project.org/repos/icu/icu/tags/release-51-1)
	 */
	icu::UnicodeString sUnicodeString(sUTF16String.c_str());
	sUnicodeString.toUTF8String(result);
	c_LogString sMessage("c_DataRepresentationFramework::toUTF8String not tested for using icu::UnicodeString");
	LOG_DESIGN_INSUFFICIENCY(sMessage);
	#warning "c_DataRepresentationFramework::toUTF8String not tested for using icu::UnicodeString"
	#endif
	return result;
}

/**
  * Decodes provided string to an UTF-16 string
  */
c_DataRepresentationFramework::c_UTF16String c_DataRepresentationFramework::toUTF16String(const c_DataRepresentationFramework::c_UTF8String& sUTF8String) {
	/*
	From: http://lists.boost.org/boost-users/2009/06/49039.php

	The conversion routines you are looking for are std::mbsrtowcs() and
	std::wcsrtombs() in <cwchar>. You must set the global locale first before
	you use them so they know which multi-byte encoding they should use (try
	for example "en_US.UTF-8"). If you want your application to work on
	Windows, too, you can't use those functions unfortunately but must use
	MultiByteToWideChar() and WideCharToMultiByte() instead (as there is no
	UTF-8 locale on Windows).
	*/

	c_DataRepresentationFramework::c_UTF16String result;
	utf8::utf8to16(sUTF8String.begin(), sUTF8String.end(), std::back_inserter(result));
	return result;
}


/**
  * Decodes provided string to an UTF-8 string
  */
c_DataRepresentationFramework::c_UTF8String c_DataRepresentationFramework::toUTF8String(const c_DataRepresentationFramework::c_UCF4String& sUCF4String) {
	c_DataRepresentationFramework::c_UTF8String result;
	std::ostringstream sTargetUTF8Stream;                // Create the stream

	try {
		std::locale loc(std::locale::classic(),new boost::utf8::utf8_codecvt_facet());	// Create a locale using utf8 facet
		sTargetUTF8Stream.imbue(loc);								// Set stream to use locale with utf8 facet
		sTargetUTF8Stream << sUCF4String.c_str(); // Stream the UCF-4 string to the Ascii string using UTF-8 facet
	}
	catch (std::exception& e) {
		c_LogString sMessage("c_DataRepresentationFramework::toAsciiString failed to convert UCF4String");
		sMessage += _Asciisz("\". Exception=");
		sMessage += _UTF8sz(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);

		sTargetUTF8Stream << "...UTF-8 encoding failed!";
	}
	result.anonymous() = sTargetUTF8Stream.str();
/*
	Good article on: http://www.codeproject.com/KB/stl/utf8facet.aspx

*/
/*
   From http://www.edobashira.com/2010/03/using-boost-code-facet-for-reading-utf8.html

	#include <iostream>
	#include <fstream>
	#include <locale>

	#define BOOST_UTF8_BEGIN_NAMESPACE
	#define BOOST_UTF8_END_NAMESPACE
	#define BOOST_UTF8_DECL

	#include <boost/detail/utf8_codecvt_facet.hpp>

	//This file wasn't present in Fedora boost package
	// but was under Windows
	//#include <libs/detail/utf8_codecvt_facet.cpp>
	#include "utf8_codecvt_facet.cpp"

	...

   std::wifstream wifs("utf8.txt");
	wifs.imbue(std::locale(std::locale(), new utf8_codecvt_facet));
	std::wstring wstr;
	wifs >> wstr;
	wifs.close();
*/

	return result; // Return the result
}

/**
  * De-Encode provided C++ literal string as an UTF-8 string.
  * Will asume C++ literal string to cover chars 0..255 in current code page
  * and encode it in UTF8.
  */
c_DataRepresentationFramework::c_UTF8String c_DataRepresentationFramework::toUTF8String(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralString) {
	c_DataRepresentationFramework::c_UTF8String result;
	#ifdef __BCPLUSPLUS__
	// Use IDE strings for conversion
	AnsiString sCPPLiteral(sCppLiteralString.c_str()); // Will use current code page by default which we asume the literal to be in
	UTF8String sResult(sCPPLiteral); // Encode in UTF8 string
	result = _UTF8sz(sResult.c_str());
	#else
	#warning  c_DataRepresentationFramework::toUTF8String not adapted to this build environment
	#endif
	return result;
}

/**
  * De-Encode provided ISO-8859-1 string as an UTF-8 string.
  * Will asume C++ literal string to cover chars 0..255 in current code page
  * and encode it in UTF8.
  */
c_DataRepresentationFramework::c_UTF8String c_DataRepresentationFramework::toUTF8String(const c_DataRepresentationFramework::c_ISO_8859_1_String& sISO_8859_1_String) {
	c_DataRepresentationFramework::c_UTF8String result;
	#ifdef __BCPLUSPLUS__
	// Use IDE strings for conversion
	AnsiString sCodePage1252(sISO_8859_1_String.c_str()); // Asume current code page is windows 1252 which is a superset of ISO-8859-1
	UTF8String sResult(sCodePage1252); // Encode in UTF8 string
	result = _UTF8sz(sResult.c_str());
	#else
	#warning  c_DataRepresentationFramework::toUTF8String not adapted to this build environment
	#endif
	return result;
}

/**
  * Decodes provided string to an UCF-4 string
  */
c_DataRepresentationFramework::c_UCF4String c_DataRepresentationFramework::toUCF4String(const c_UTF8String& sUTF8String) {
	c_DataRepresentationFramework::c_UCF4String result;
	std::wostringstream sTargetUCF4Stream;                // Create the stream

	try {
		std::locale loc(std::locale::classic(),new boost::utf8::utf8_codecvt_facet());	// Create a locale using utf8 facet
		sTargetUCF4Stream.imbue(loc);								// Set stream to use locale with utf8 facet
		sTargetUCF4Stream << sUTF8String.c_str(); // Stream the UTF-8 string to the UCF-4 string using UTF-8 facet
	}
	catch (std::exception& e) {
		c_LogString sMessage("c_DataRepresentationFramework::toAsciiString failed to convert UTF8String=");
		sMessage += sUTF8String;
		sMessage += _Asciisz("\". Exception=");
		sMessage += _UTF8sz(e.what());
		LOG_DESIGN_INSUFFICIENCY(sMessage);

		sTargetUCF4Stream << U"...UTF-16 encoding failed!";
	}
	result.anonymous() = sTargetUCF4Stream.str();
	return result;
}

//---------------------------------------------------------------------------
/**
  * De-Encode provided Ascii string as an UTF-8 string
  */
c_DataRepresentationFramework::c_UTF8String c_DataRepresentationFramework::toUTF8String(const c_DataRepresentationFramework::c_AsciiString& sAsciiString) {
	c_DataRepresentationFramework::c_UTF8String result;
	std::copy(sAsciiString.begin(), sAsciiString.end(), std::back_inserter(result));
	return result;
}

//---------------------------------------------------------------------------
/**
  * De-Encode provided Ascii string as an UTF-16 string
  */
c_DataRepresentationFramework::c_UTF16String c_DataRepresentationFramework::toUTF16String(const c_DataRepresentationFramework::c_AsciiString& sAsciiString) {
	c_DataRepresentationFramework::c_UTF16String result;
	std::copy(sAsciiString.begin(), sAsciiString.end(), std::back_inserter(result));
	return result;
}
//---------------------------------------------------------------------------

/**
  * De-Encode provided ISO 8859-1 string as an UTF-16 string
  */
c_DataRepresentationFramework::c_UTF16String c_DataRepresentationFramework::toUTF16String(const c_DataRepresentationFramework::c_ISO_8859_1_String& sISO_8859_1_String) {
	c_DataRepresentationFramework::c_UTF16String result;
	#ifdef __BCPLUSPLUS__
	// Use IDE strings for conversion
	AnsiString sCodePage1252(sISO_8859_1_String.c_str()); // Wrap in Code Page 1252 string (Should be compile environment default Ansi code page)
	String sUTF16String(sCodePage1252); // De-encode from Code Page 1252 to UTF16 string
	result = _UTF16sz(sUTF16String.c_str());
	#else
	#warning  c_DataRepresentationFramework::toUTF16String not adapted to this build environment
	#endif

	return result;
}
//---------------------------------------------------------------------------
/**
  * De-encodes provded UTF16 string to ISO 8859-1 string
  */
c_DataRepresentationFramework::c_ISO_8859_1_String c_DataRepresentationFramework::toISO_8859_1_String(const c_DataRepresentationFramework::c_UTF16String& sUTF16String) {
	c_DataRepresentationFramework::c_ISO_8859_1_String result;
	#ifdef __BCPLUSPLUS__
	// Use IDE strings for conversion
	AnsiString sWindows1252(sUTF16String.c_str()); // Will encode to current code page by default
												   // which we asume to be standard widnows code page 1252
												   // which in turn is the same as ISO 8859-1 except that
												   // 0x80 .. 0x9F may contain printable characters.
	result.anonymous() = sWindows1252.c_str();
	#else
	#warning  c_DataRepresentationFramework::toISO_8859_1_String not adapted to this build environment
	#endif
	return result;
}
//---------------------------------------------------------------------------

/**
  * De-encodes provded UTF16 string to ISO 8859-1 string
  */
c_DataRepresentationFramework::c_ISO_8859_1_String c_DataRepresentationFramework::toISO_8859_1_String(const c_DataRepresentationFramework::c_UTF8String& sUTF8String) {
	c_DataRepresentationFramework::c_ISO_8859_1_String result;
	#ifdef __BCPLUSPLUS__
	// Use IDE strings for conversion
	System::UTF8String systemUTF8String(sUTF8String.c_str()); // Use RAD studio UTF8 String instance
	System::AnsiString sWindows1252(systemUTF8String); // Encode to Ansi string which should use current code page which should be default 1252.
													   // And Code Page 1252 is a supereset of ISO 8859-1.
	result.anonymous() = sWindows1252.c_str();
	#else
	#warning  c_DataRepresentationFramework::toISO_8859_1_String not adapted to this build environment
	#endif
	return result;
}

//---------------------------------------------------------------------------

///**
//  * De-Encode provided UTF-16 string as an Ascii string
//  */
//c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const c_DataRepresentationFramework::c_UTF16String& sUTF16String) {
//	c_DataRepresentationFramework::c_AsciiString result;
//	// Copy only ascii chars (they map 1-to-1 between UTF-16 and Ascii)
//	for (c_DataRepresentationFramework::c_UTF16String::const_iterator iter = sUTF16String.begin(); iter != sUTF16String.end(); iter++) {
//		if (*iter <= 0x7F) {
//			result.anonymous() += static_cast<char>(*iter);
//		}
//		else {
//			// Replace it
//			result.anonymous() += '?';
//			LOG_DESIGN_INSUFFICIENCY_I(c_DataRepresentationFramework::c_UTF8String("UTF16->Ascii failed for char 0x%X"),*iter);
//		}
//	}
//	return result;
//}

//---------------------------------------------------------------------------
/**
  * Parses provided string containg a currency value and converts it to an int
  * with the corresponding cent value.
  * Example: "1428,50" is converted to int 142850.
  * Will throw an  std::exception in case of failure.
  */
int c_DataRepresentationFramework::CurrencyValueStringToCentInteger(const c_DataRepresentationFramework::c_AsciiString& sCurrencyValueString,char cCommaChar) {
	int result = -1; // Default

	try {
		// Convert input string to a Cent value string
		c_DataRepresentationFramework::c_AsciiString sCentValue = sCurrencyValueString;

		// Remove ',' if any
		int indexOfCommaChar = sCentValue.find_first_of(cCommaChar,0);
		if (indexOfCommaChar > 0) {
			sCentValue.erase(indexOfCommaChar,1);
		}
		else {
			// No comma found. Add two '0' to make value into cents
			sCentValue.anonymous() += "00";
		}
		// Convert to integer
		result = c_DataRepresentationFramework::intValueOfDecimalString(sCentValue);
	}
	catch (std::runtime_error& e) {
		throw; // just forward
	}
	catch (...) {
		std::string sMessage = "Failed to parse Currency string=\"";
		sMessage += sCurrencyValueString;
		sMessage += "\"";
		sMessage += "\nGeneral Exception";
//		throw DRFWException(sMessage);
		throw std::runtime_error(sMessage);
	}

	return result;
}

/**
  * Creates a string representation of provided Amount in cents.
  * Example:  The cent value 142850 is converted to the string "1428,50". (cCommaChar = ',' default)
  * Will throw an data representation framework excpeiton DRFWException in case
  * of failure.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::CentIntegerToCurrencyValueString(int centInteger,char cCommaChar) {
	c_DataRepresentationFramework::c_AsciiString result;
	float f_Amount = centInteger/100.0;
	result = _Asciis((boost::format("%05.2f") % f_Amount).str());
	return result;
}

//---------------------------------------------------------------------------
/**
  * Parses a string where unprintable chars are represented with <value>
  * value are two digits hex values.
  */
//c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::parseBracketedHexValueCharString(const c_DataRepresentationFramework::c_AsciiString& buf) {
c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::parseBracketedHexValueCharString(const c_DataRepresentationFramework::c_AnonymousString& buf) {

	c_DataRepresentationFramework::t_raw_vector result;

	// Loop through string and parse for <...>

	c_DataRepresentationFramework::c_AsciiString::const_iterator iter = buf.begin();
	int state = 0;
	std::string valueStr;
	while (iter != buf.end()) {
		switch (state) {
		  case 0: // Wait for '<' or '>'
			if (*iter == '<') {
			  valueStr = "";
			  state = 1; // Read value in '<'value'>'
			}
			else if (*iter == '>') {
			  // Malformed string!!
				std::string eStr = "c_DataRepresentationFramework::parseBracketedHexValueCharString failed.\n  =>";
				eStr.append("Unmatched \'>\' found");
//				throw DRFWException(eStr);
				throw std::runtime_error(eStr);
			}
			else {
			  result.push_back(*iter);
			}
			break;
		  case 1: // Wait for '>'
			if (*iter == '>') {
				int valueChar = hexValueOfHexDigit(valueStr[0])*0x10 + hexValueOfHexDigit(valueStr[1]);
				result.push_back(valueChar);
				state = 0;
			}
			else {
			  valueStr += *iter;
			}
			break;
		default:
			;
		}
		iter++; // Next char
	}
	return result;
}

/**
  * creates a hex value brackated Ascii char string where unprintable charachters
  * are represented as two chars hex values between <..>.
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::createBracketedHexValueAsciiString(const c_DataRepresentationFramework::t_raw_vector& buf) {
	c_DataRepresentationFramework::c_AsciiString result;

	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();
	while (iter != buf.end()) {
		if ((*iter >= 0x20) && (*iter <= 0x7E)) {
		  result += _Asciic(*iter);
		}
		else {
//		  result += '<';
//		  char szValue[4];
//		  sprintf(szValue,"%02x",*iter);
//		  result.append(szValue);
//		  result += '>';
		  // Not printable
		  // Use boost format. Note: Works onlyu if unsigned char is casted to an int. Strange...
		  // If not, then for 'ц' the format call below returns "<0ц>"...
		  result += _Asciis((boost::format("<%x>") % boost::io::group(std::setfill('0'), std::setw(2), static_cast<int>(*iter))).str());
		}
		iter++;
	}

	return result;
}

/**
  * creates a hex value brackated ISO 8859-1 string where unprintable charachters
  * are represented as two chars hex values between <..>.
  */
c_DataRepresentationFramework::c_ISO_8859_1_String c_DataRepresentationFramework::createBracketedHexValueISO8859_1String(const c_DataRepresentationFramework::t_raw_vector& buf,bool hexBracketBlankAlso) {
	c_DataRepresentationFramework::c_AsciiString result;
	int lower_limit_for_non_bracketed_value = hexBracketBlankAlso?0x20+1:0x20;

	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();
	while (iter != buf.end()) {
		if (     ((*iter >= lower_limit_for_non_bracketed_value) && (*iter <= 0x7E)) /* ascii */
			  || ((*iter >= 0xA0) && (*iter <= 0xFF)) /* ISO 8859 extension */ ) {
		  result += _Asciic(*iter);
		}
		else {
		  // Not printable
		  // Use boost format. Note: Works onlyu if unsigned char is casted to an int. Strange...
		  // If not, then for 'ц' the format call below returns "<0ц>"...
		  result += _Asciis((boost::format("<%x>") % boost::io::group(std::setfill('0'), std::setw(2), static_cast<int>(*iter))).str());
		}
		iter++;
	}

	return result;
}


/**
  * Parses a string of hex digits where each two digits are interpreted as
  * one byte hex value. Fx. "091F7A" is parsed into
  * a vector of bytes with values 0x09, 0x1F, 0x7A
  */
c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::parseHexNibblePairString(const c_DataRepresentationFramework::c_AsciiString& HexNibblePairString) {
	// Convert into binary format
	c_DataRepresentationFramework::t_raw_vector result;

	c_DataRepresentationFramework::c_AsciiString::const_iterator iter = HexNibblePairString.begin();
	bool isFirstChar = true;
	int intValue;
	try {
		while (iter != HexNibblePairString.end()) {
			if (isFirstChar) {
				intValue = hexValueOfHexDigit(*iter)*0x10;
			}
			else {
				intValue += hexValueOfHexDigit(*iter);
				result.push_back(intValue);
			}
			isFirstChar = !isFirstChar; // Toggle first <-> second
			iter++;
		}
	} catch (std::exception& e) {
		c_LogString sMessage("c_DataRepresentationFramework::parseHexNibblePairString failed.\n  =>");
		sMessage.anonymous() += "Parsing hex string: ";
		sMessage.anonymous() += HexNibblePairString;
		sMessage.anonymous() += "\nException: ";
		sMessage += toLogString(_UTF8sz(e.what()));
		throw std::runtime_error(sMessage);
	}
	return result;
}

/**
  * Cretaes a string of hex nibble pairs from provided data buffer.
  * Each byte in the buffer is transalted into a two digit hexadecimal output.
  * data[0x23, 0x34 ...] is output in string as "2334..."
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::createHexNibbleString(const c_DataRepresentationFramework::t_raw_vector& buf) {
	c_DataRepresentationFramework::c_AsciiString result;

	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();
	while (iter != buf.end()) {
//		char szValue[4];
//		sprintf(szValue,"%02X",*iter);
//		result.append(szValue);
		result += _Asciis((boost::format("%02X") % static_cast<int>(*iter)).str());
		++iter;
	}
	return result;
}

/**
  * Creates a vector of unsigned chars from provided string
  */
c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::createUCharVector(const c_DataRepresentationFramework::c_AnonymousString& buf) {
	c_DataRepresentationFramework::t_raw_vector result;
	c_DataRepresentationFramework::c_AnonymousString::const_iterator iter = buf.begin();
	for (iter = buf.begin(); iter != buf.end(); iter++) {
		result.push_back(static_cast<unsigned char>(*iter));
	}
	return result;
}

/**
  * Creates a string from provided vector of unsigned chars
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::createString(const c_DataRepresentationFramework::t_raw_vector& buf) {
	c_DataRepresentationFramework::c_AsciiString result;
	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();
	for (iter = buf.begin(); iter != buf.end(); iter++) {
		result.anonymous() += static_cast<char>(*iter);
	}
	return result;
}

/**
  * Returns the integer value of provided hex digit
  */
int c_DataRepresentationFramework::hexValueOfHexDigit(char hex_char) {
	int result = 0;
	if (hex_char >= '0' && hex_char <='9') {
		result = hex_char - '0';
	}
	else if (hex_char >='a' && hex_char <= 'f') {
		result = 10 + hex_char - 'a';
	}
	else if (hex_char >= 'A' && hex_char <= 'F' ) {
		result = 10 + hex_char - 'A';
	}
	else {
		std::string eStr = "Not a Hex char [";
		eStr += hex_char;
		eStr += "]";
//		throw DRFWException(eStr);
		throw std::runtime_error(eStr);
	}
	return result;
}

/**
  * Returns provided hex digit string as a long value
  */
unsigned long c_DataRepresentationFramework::intValueOfHexString(const std::string& sHexString) {
	unsigned long result = 0;
	std::string::const_iterator iter = sHexString.begin();
	while (iter != sHexString.end()) {
		result = result*0x10 + c_DataRepresentationFramework::hexValueOfHexDigit(*iter);
		iter++;
	}
	return result;
}
unsigned long c_DataRepresentationFramework::intValueOfHexString(const c_DataRepresentationFramework::c_AsciiString& sHexString) {
	return c_DataRepresentationFramework::intValueOfHexString(sHexString.anonymous());
}
unsigned long c_DataRepresentationFramework::intValueOfHexString(const c_DataRepresentationFramework::c_UTF8String& sHexString) {
	return c_DataRepresentationFramework::intValueOfHexString(sHexString.anonymous());
}

/**
  * Returns provided decimal digit string as a long value
  */
unsigned long c_DataRepresentationFramework::intValueOfDecimalString(const std::string& sDecimalString) {
	unsigned long result = 0;
	std::string::const_iterator iter = sDecimalString.begin();
	while (iter != sDecimalString.end()) {
		if ((*iter >= '0') && (*iter <= '9') ) {
			result = result*10 + (*iter - '0');
		}
		else {
			// Error, not a decimal string!
			std::string sMessage = "Not a decimal string \"";
			sMessage += sDecimalString;
			sMessage += "\"";
//			throw DRFWException(sMessage);
			throw std::runtime_error(sMessage);
		}
		iter++;
	}
	return result;
}
unsigned long c_DataRepresentationFramework::intValueOfDecimalString(const c_DataRepresentationFramework::c_AsciiString& sDecimalString) {
	return c_DataRepresentationFramework::intValueOfDecimalString(sDecimalString.anonymous());
}

/**
  * Create a 7 bit ascii buffer
  */
c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::create7BitAsciiBuffer(const c_DataRepresentationFramework::t_raw_vector& buf) {
	c_DataRepresentationFramework::t_raw_vector result;

	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();

	while (iter != buf.end()) {
		result.push_back(*iter & 0x7F);
		++iter;
	}
	return result;
}

	/**
	  * Creates a buffer with the same data as provided bufer but with even parity added
	  */
c_DataRepresentationFramework::t_raw_vector c_DataRepresentationFramework::createEvenParityBuffer(const c_DataRepresentationFramework::t_raw_vector& buf) {
	c_DataRepresentationFramework::t_raw_vector result;

	c_DataRepresentationFramework::t_raw_vector::const_iterator iter = buf.begin();

	while (iter != buf.end()) {
		result.push_back(c_DataRepresentationFramework::charWithEvenParity(*iter));
		++iter;
	}
	return result;
}

/**
  * Returns provided char with parity bit set to even parity
  */
char c_DataRepresentationFramework::charWithEvenParity(char ch) {
	char result = ch;

	bool isEvenParity = true; // start even

	unsigned char d = static_cast<unsigned char>(ch);

	for (int i = 0; i < 8; i++) {
	  // Flip parity flag if bit found
	  isEvenParity = isEvenParity ^ ((d & 0x01) > 0);
	  d = d >> 1; // Shift bits left
	}

	if (!isEvenParity) {
		result = result | 0x80;
	}
	return result;
}

/**
  * Returns provided char with parity bit removed
  */
char c_DataRepresentationFramework::charWithoutParityBit(char ch) {
	return (ch & 0x7F);
}

/**
  * Returns provided integer as a decimal string
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::intToDecimalString(int val,int minNoOfDigits) {
//	c_DataRepresentationFramework::c_AsciiString result("????");
//	char sprintBuf[32];
//	if (minNoOfDigits>0 && minNoOfDigits<10) {
//		char szFormatString[8] = "%0 d";
//		szFormatString[2] = static_cast<char>(minNoOfDigits + '0');
//		sprintf(sprintBuf,szFormatString,val);
//	}
//	else {
//		sprintf(sprintBuf,"%d",val);
//	}
//	result = sprintBuf;

	c_DataRepresentationFramework::c_AsciiString result;
	result.anonymous() +=  (boost::format("%d") % boost::io::group(std::setfill('0'), std::setw(minNoOfDigits), val)).str();
	return result;
}

/**
  * Returns provided integer as a hexadecimal string
  */
c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::intToHexString(int val,int minNoOfDigits) {
//	c_DataRepresentationFramework::c_AsciiString result("????");
//	char sprintBuf[32];
//	std::string sFormatString;
//	if (val < 0) {
//		sFormatString += "-";
//		val = std::abs(val); // Set to positive value
//	}
//	if (minNoOfDigits>0 && minNoOfDigits<10) {
//		// char szFormatString[8] = "%0 x";
//		// szFormatString[2] = static_cast<char>(minNoOfDigits + '0');
//		// sprintf(sprintBuf,szFormatString,val);
//		sFormatString += "%0";
//		sFormatString.push_back(static_cast<char>(minNoOfDigits + '0'));
//		sFormatString += "X";
//		sprintf(sprintBuf,sFormatString.c_str(),val);
//	}
//	else {
//		sFormatString += "%X";
//		// sprintf(sprintBuf,"%x",val);
//		sprintf(sprintBuf,sFormatString.c_str(),val);
//	}
//	result = sprintBuf;

	c_DataRepresentationFramework::c_AsciiString result;
	// Handle sign manually to behave as decimal numbers. Hex generation may show two complements value which is not what we whant
	if (val < 0) {
		result.anonymous() = (boost::format("-%X") % boost::io::group(std::setfill('0'), std::setw(minNoOfDigits), abs(val))).str();
	}
	else {
		result.anonymous() = (boost::format("%X") % boost::io::group(std::setfill('0'), std::setw(minNoOfDigits), val)).str();
	}

	return result;
}

