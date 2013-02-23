/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef DataRepresentationFrameWorkH
#define DataRepresentationFrameWorkH

#include <vector>
#include <string>
#include <boost/strong_typedef.hpp> // BOOST_STRONG_TYPEDEF
#include <System.hpp> // Import IDE types

/*

	A note about representation aware strings

	The classes c_XXXString defines strong typed strings that inherits std::basic string.

	They allow overloading based on string representation while providing compability
	with STL string handling with the following additional behavior.

	They do NOT allow implicit construct os assignment to anonymous strings. Instead
	any string to be feed to the representation aware string class must be
	explicitally denoted as anonymous. The following mechanism are made available.

	1. Explicit call to constructor: c_XXXString myXXXString(<anonymous std::string och char*>)
	2. Feed with strong type wrapper: myXXXString = _XXXsz(<char array pointer>);
	3. Fall back to anonymous base string: myXXXString.anonymous() = <STL string>

	None of theese performs any encodings!! The programmes must use these constructs
	when knowing that the anonymous source string is in compatible representation!

	All string representation change is made with explcit clall to toXXXString() methods.
	This ensure that all represention domain crossing show up in the code.

	Good link on code pages: http://en.wikipedia.org/wiki/Code_page

	/Kjell-Olov Högdahl

*/

//---------------------------------------------------------------------------
/**
  * Helper class for methods to transform between different data buffer
  * representations.
  */
class c_DataRepresentationFramework {
public:

	/**
	  * Models the most basic raw byte of c_DataRepresentationFramework
	  */
	typedef unsigned char t_raw_byte;

	/**
	  * Models a vector of t_raw_byte
	  */
	typedef std::vector<t_raw_byte> t_raw_vector;

	/**
	  * Test method to test implicit cast to parameter T.
	  * Will generate compiler error of instansiated with type T
	  * that may not be constructed from provided type.
	  * Used to test cross casting between representation aware string classes below
	  */
	template <class T> void methodWithParameter(const T& t) {;}

	/**
	  * Wrapper for anonymous char.
	  * Note: Made as pre-processor macro to make declarations really strong typed.
	  * typedefs from template instanciated with the same class will be regarded as the same type by C++...
	  */
	#define TYPE_WRAPPED_CHAR(C,T) \
	class T { \
	public: \
		/* Construct from char array but require explicit type conversion */ \
		explicit T(const C ch) : m_ch(ch) {;} \
		\
		const C ref() const {return m_ch;}\
	private: \
		  /* Private storage of pointer to actual array */ \
		const C m_ch; \
	};

	/**
	  * Wrapper for anonymous char arrays.
	  * Note: Made as pre-processor macro to make declarations really strong typed.
	  * typedefs from template instanciated with the same class will be regarded as the same type by C++...
	  */
	#define TYPE_WRAPPED_CHAR_ARRAY(C,T) \
	class T { \
	public: \
		/* Construct from char array but require explicit type conversion */ \
		explicit T(const C* sz) : m_sz(sz) {;} \
		\
		const C* ref() const {return m_sz;}\
	private: \
		  /* Private storage of pointer to actual array */ \
		const C* m_sz; \
	};

	/**
	  * Wrapper for anonymous char arrays.
	  * Note: Made as pre-processor macro to make declarations really strong typed.
	  * typedefs from template instanciated with the same class will be regarded as the same type by C++...
	  */
	#define TYPE_WRAPPED_STDSTRING(S,T) \
	class T { \
	public: \
		/* Construct from string but require explicit type conversion */ \
		explicit T(const S& s) : m_s(s) {;} \
		\
		const S& ref() const {return m_s;}\
	private: \
		  /* Private storage of pointer to actual array */ \
		const S& m_s; \
	};


	/**
	  * Strong types that wraps basic anonymous char arrays and defines
	  * arrays of specified representation.
	  */
	TYPE_WRAPPED_CHAR(char32_t,UCF4c);
	TYPE_WRAPPED_CHAR(char,Latin1c);
	TYPE_WRAPPED_CHAR(char,Literalc);
	TYPE_WRAPPED_CHAR(char,Asciic);
	TYPE_WRAPPED_CHAR(char,UTF8c);

	TYPE_WRAPPED_CHAR_ARRAY(wchar_t,UTF16sz); // Or use u"bla bla" for UTF-16 literals
	TYPE_WRAPPED_CHAR_ARRAY(wchar_t,WideAsciisz); // whar_t array containing Ascii chars only
	TYPE_WRAPPED_CHAR_ARRAY(char,UTF8sz);
	TYPE_WRAPPED_CHAR_ARRAY(char,Literalsz);
	TYPE_WRAPPED_CHAR_ARRAY(char,Latin1sz);
	TYPE_WRAPPED_CHAR_ARRAY(char,Asciisz);

	TYPE_WRAPPED_STDSTRING(std::wstring,UTF16s);
	TYPE_WRAPPED_STDSTRING(std::string,UTF8s);
	TYPE_WRAPPED_STDSTRING(std::string,Literals);
	TYPE_WRAPPED_STDSTRING(std::string,Latin1s);
	TYPE_WRAPPED_STDSTRING(std::string,Asciis);

	// Inspired by BOOST_STRONG_TYPEDEF in <boost/strong_typedef.hpp>

	/**
	  * Do NOT allow implicit cast/assign or construct from anonymous input
	  */
	#define STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE \
	public: \
	D() : S() {;} /* Default constructor */                                                     \
	D(const D & d_) : S(d_) {;} /* Copy constructor */                                 \
	explicit D(const S& s_) : S(s_) {;} /* Require explicit construct from anonymous input */                         \
	explicit D(const C* sz) : S(sz) {;} /* Require explicit construct from anonymous input */\
	explicit D(S::const_iterator _begin,S::const_iterator _end) : S(_begin,_end) {;};

	/**
	  * Do allow implicit cast/assign or construct from anonymous input
	  */
	#define STRONG_STRING_TYPE_CONSTRUCTORS_IMPLICIT_FROM_ANONYMOUS_BASE \
	public: \
	D() : S() {;} /* Default constructor */                                                     \
	D(const D & d_) : S(d_) {;} /* Copy constructor */                                 \
	D(const S& s_) : S(s_) {;} /* Allow implicit construct from anonymous input */                         \
	D(const C* sz) : S(sz) {;} /* Allow implicit construct from anonymous input */\
	D(S::const_iterator _begin,S::const_iterator _end) : S(_begin,_end) {;};

	/**
	  * Allow modification from ascii input
	  */
	#define STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII \
	public:\
	D(const c_AsciiString& sAscii): S() {std::copy(sAscii.begin(),sAscii.end(),std::back_inserter(*this));} /* Allow implicit construct from Ascii strings */\
	D(const Asciis& asciis): S() {*this = c_AsciiString(asciis);} /* Allow implicit construct from wrapped Ascii string */\
	D(const Asciisz& asciisz): S() {*this = c_AsciiString(asciisz);} /* Allow implicit construct from wrapped Ascii char array */\
	D(const c_DataRepresentationFramework::Asciic asciic) : S() {*this = c_AsciiString(asciic);}\

	/**
	  * Common constructors and operators of strong typed string
	  */
	#define STRONG_STRING_TYPE_COMMON_BODY \
	public: \
	typedef std::basic_string<C> S;                          \
	typedef C CharType; \
	D & operator=(const D & rhs) { this->anonymous() = rhs.anonymous(); return *this;}   /* Assign to other D */ \
	S& anonymous() {return (*this);} \
	const S& anonymous() const {return (*this);} \
	bool operator==(const D & rhs) const { return (this->anonymous() == rhs.anonymous()); } \
	bool operator<(const D & rhs) const { return (this->anonymous() < rhs.anonymous()); }   \
	D& operator+=(const D& other_instance) {this->anonymous() += other_instance; return *this;} \
	D operator+(const D& other_instance) {D result(*this); result += other_instance; return result;} \
	void test(const D& d) {;};

	/**
	  * Strong typed Ascii string class.
	  * Ascii is char codes 0..0x7F
	  */
	#define  D c_AsciiString
	#define  C char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_COMMON_BODY

	public:

		/**
		  * Allow implicit construction from wrapped ascii char array
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Asciisz& asciisz) : S(asciisz.ref()) {;}

		/**
		  * Allow implicit construction from wrapped ascii std string
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Asciis& asciis) : S(asciis.ref()) {;}

		/**
		  * Allow implicit construction from wrapped ascii char
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Asciic asciic) : S() {*this = asciic;}

		/**
		  * Allow assignment to wrapper of ascii char array.
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D & operator=(const c_DataRepresentationFramework::Asciisz& asciisz) { this->anonymous() = asciisz.ref(); return *this;}

		/**
		  * Allow assignment to wrapper of ascii string.
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D & operator=(const c_DataRepresentationFramework::Asciis& asciis) { this->anonymous() = asciis.ref(); return *this;}

		/**
		  * Allow assignment to wrapper of ascii string.
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D & operator=(const c_DataRepresentationFramework::Asciic asciic) { this->anonymous() = asciic.ref(); return *this;}

		/**
		  * Allow substr() on Ascii string
		  */
		D substr(size_type off = 0,size_type count = npos) const {return D(this->anonymous().substr(off,count));}

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong types string class to hold C++ string literal chars.
	  * These are defined as C++ source code character set,
	  * (See http://www.glenmccl.com/charset.htm)
	  * Encoded in the standard locale of the compiling environment.
	  * May contain multibyte sequences.
	  * Basically it is a subset of the standard Ascii character set plus a subset of
	  * the implementation dependent extended Ascii character set. This means that
	  * C++ string literals are not 1-t-1 with ascii strings nor with f.x ISO 8859-1,
	  * nor with UTF-8 etc.
	  */
	#define  D c_CppLiteralString
	#define  C char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	public:
		/**
		  * Allow implicit type conversion from wrapped C++ literal char array
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Literalsz& literalsz) : S(literalsz.ref()) {;}

		/**
		  * Allow implicit type conversion from wrapped C++ literal std string
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Literals& literals) : S(literals.ref()) {;}

		/**
		  * Allow implicit construction from wrapped literal char
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Literalc& literalc) : S() {*this = literalc;}\

		/**
		  * Allow assignment to wrapper of literal char.
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D & operator=(const c_DataRepresentationFramework::Literalc& literalc) { this->anonymous() = literalc.ref(); return *this;}

		/**
		  * Allow substr() on C++ literal
		  */
		D substr(size_type off = 0,size_type count = npos) const {return D(this->anonymous().substr(off,count));}
	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong typed ISO 8859-1 class.
	  * This is basically the whole set of Ascii chars
	  * extended with special characters making it covering
	  * a large part of latin languages char sets (including swedish).
	  */
	#define  D c_ISO_8859_1_String
	#define  C char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	public:

		/**
		  * Allow implicit construction from C++ literal.
		  * We asume the code is compiled in windows 1252 code page.
		  * All printable characters of ISO 8859-1 are 1-to-1 with Windows code page 1252.
		  */
		D(const c_DataRepresentationFramework::c_CppLiteralString& sLiteral) : S(sLiteral) {;};

		/**
		  * Allow implicit construction from wrapped C++ literal char array.
		  * We asume the code is compiled in windows 1252 code page.
		  * All printable characters of ISO 8859-1 are 1-to-1 with Windows code page 1252.
		  */
		D(const c_DataRepresentationFramework::Literals& literals) : S(literals.ref()) {;};

		/**
		  * Allow implicit construction from wrapped C++ literal char array.
		  * We asume the code is compiled in windows 1252 code page.
		  * All printable characters of ISO 8859-1 are 1-to-1 with Windows code page 1252.
		  */
		D(const c_DataRepresentationFramework::Literalsz& literalsz) : S(literalsz.ref()) {;};

		/**
		  * Allow implicit construction from wrapped literal char
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::Literalc& literalc) : S() {this->anonymous() = literalc.ref();}\

		/**
		  * Allow substr() on ISO 8859-1 string
		  */
		D substr(size_type off = 0,size_type count = npos) const {return D(this->anonymous().substr(off,count));}

	};
	#undef  D
	#undef  C
	#undef S

	#define  D c_UTF8String
	#define  C char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	public:
		/**
		  * Allow implicit type conversion from UTF8sz wrapped char arrays
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::UTF8sz& utf8sz) : S(utf8sz.ref()) {;}

		/**
		  * Allow implicit type conversion from UTF8sz wrapped std string
		  * 1-to-1 mapping applicable, no decoding needed
		  */
		D(const c_DataRepresentationFramework::UTF8s& utf8s) : S(utf8s.ref()) {;}

	private:

		/**
		  * Do NOT Allow substr() on UTF16 string. May contain multibyte chars.
		  * Use s.anonymous().substr() if you are sure there are no multibytes in the string
		  */
		D substr(size_type off = 0,size_type count = npos) const {throw std::runtime_error("call to c_UTF8String::substr() not allowed!");}

	};
	#undef  D
	#undef  C
	#undef S

	#define  D c_BinaryString
	#define  C unsigned char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_COMMON_BODY

	public:
		// Allow implicit construct from anonymous strings
		D(const std::string& sAnonymous):S() { std::copy(sAnonymous.begin(),sAnonymous.end(),std::back_inserter(*this));}

		// Allow assign from anonymous string
		D& operator=(const std::string& sAnonymous) { this->clear();std::copy(sAnonymous.begin(),sAnonymous.end(),std::back_inserter(*this));return *this;}

		// Allow append from anonymous string
		D& operator+=(const std::string& sAnonymous) { std::copy(sAnonymous.begin(),sAnonymous.end(),std::back_inserter(*this));return *this;}

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong typed as a string with unknown char contents format.
	  * May be used to direct to appropriate constructor or method
	  * of representation dependent code.
	  */
	#define  D c_AnonymousString
	#define  C char
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_IMPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_COMMON_BODY

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong typed as a string with unknown char contents format.
	  * May be used to direct to appropriate constructor or method
	  * of representation dependent code.
	  */
	#define  D c_AnonymousWideString
	#define  C wchar_t
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong type for UTF-16 strings but with all operations of std::basic_string.
	  * The different strong string types differs slightly in construction behavior
	  * so definition could not be templetized nor macro-based.
	  */
	#define  D c_UTF16String
	#define  C wchar_t
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	public:

		/**
		  * Allow implicit type conversion from UTF16sz wrapped char arrays
		  */
		D(const c_DataRepresentationFramework::UTF16sz& utf16sz) : S(utf16sz.ref()) {;}

		/**
		  * Implicitally construct from char16_t.
		  * Allows c_UTF16String(u"abcd...") // u defines type of string to char16_t*
		  */
		D(const char16_t* szString) : S()
		{
			try {
				std::basic_string<char16_t> _s(szString);
				std::copy(_s.begin(),_s.end(),std::back_inserter(*this));
			}
			catch (...) {
			}
		}

		// Allow explicit construct from anonymous strings
		explicit D(const std::string& sAnonymous):S() { std::copy(sAnonymous.begin(),sAnonymous.end(),std::back_inserter(*this));}

		/**
		  * Allow implicit type conversion from WideAsciisz wrapped char arrays
		  */
		D(const c_DataRepresentationFramework::WideAsciisz& wide_ascii_sz) : S(wide_ascii_sz.ref()) {;}

	private:
		/**
		  * Do NOT Allow substr() on UTF16 string. May contain multibyte chars.
		  * Use s.anonymous().substr() if you are sure there are no multibytes in the string
		  */
		D substr(size_type off = 0,size_type count = npos) const {throw std::runtime_error("call to c_UTF16String::substr() not allowed!");}

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Strong type for UCF-4 strings but with all operations of std::basic_string.
	  * The different strong string types differs slightly in construction behavior
	  * so definition could not be templetized nor macro-based.
	  */
	#define  D c_UCF4String
	#define  C wchar_t /* Boost uses wchar_t for UCF-4 encoding */
	#define S std::basic_string<C>
	class D :
		boost::addable<S>
		,public S
	{
		// Note 101111/KoH. Can't allow implicit construct from C based types
		// while C is whar_t. whar_t is UTF-16 in Windows!
		STRONG_STRING_TYPE_CONSTRUCTORS_EXPLICIT_FROM_ANONYMOUS_BASE
		STRONG_STRING_TYPE_MODIFIABLE_FROM_ASCII
		STRONG_STRING_TYPE_COMMON_BODY

	public:
		// Allow explicit construct from anonymous strings
		explicit D(const std::string& sAnonymous):S() { std::copy(sAnonymous.begin(),sAnonymous.end(),std::back_inserter(*this));}

		/**
		  * Allow substr() on UCF4 sttring
		  */
		D substr(size_type off = 0,size_type count = npos) const {return D(this->anonymous().substr(off,count));}

	};
	#undef  D
	#undef  C
	#undef S

	/**
	  * Dymmy NOP method to encode UTF8 to UTF8.
	  * Used to enable templates call toUTF8String() method when specilized on string type that happens to be UTF8STring already
	  */
	static c_DataRepresentationFramework::c_UTF8String& toUTF8String(const c_DataRepresentationFramework::c_UTF8String& sUT8String) {return const_cast<c_DataRepresentationFramework::c_UTF8String&>(sUT8String);}

	/**
	  * De-Encode provided UTF-16 string as an UTF-8 string
	  */
	static c_DataRepresentationFramework::c_UTF8String toUTF8String(const c_DataRepresentationFramework::c_UTF16String& sUTF16String);

	/**
	  * De-Encode provided UCF4 string as an UTF-8 string
	  */
	static c_DataRepresentationFramework::c_UTF8String toUTF8String(const c_DataRepresentationFramework::c_UCF4String& sUCF4String);

	/**
	  * De-Encode provided C++ literal string as an UTF-8 string.
	  * Will asume C++ literal string to cover chars 0..255 in current code page
	  * and encode it in UTF8.
	  */
	static c_DataRepresentationFramework::c_UTF8String toUTF8String(const c_DataRepresentationFramework::c_CppLiteralString& sCppLiteralString);

	/**
	  * De-Encode provided ISO-8859-1 string as an UTF-8 string.
	  * Will asume C++ literal string to cover chars 0..255 in current code page
	  * and encode it in UTF8.
	  */
	static c_DataRepresentationFramework::c_UTF8String toUTF8String(const c_DataRepresentationFramework::c_ISO_8859_1_String& sISO_8859_1_String);

	/**
	  * De-Encode provided UTF-8 string as an UCF4 string
	  */
	static c_DataRepresentationFramework::c_UCF4String toUCF4String(const c_UTF8String& sUTF8String);

	/**
	  * De-Encode provided UTF-8 string as an UTF-16 string
	  */
	static c_DataRepresentationFramework::c_UTF16String toUTF16String(const c_DataRepresentationFramework::c_UTF8String& sUTF8String);

	/**
	  * De-Encode provided Ascii string as an UTF-8 string
	  */
	static c_DataRepresentationFramework::c_UTF8String toUTF8String(const c_DataRepresentationFramework::c_AsciiString& sAsciiString);

	/**
	  * De-Encode provided Ascii string as an UTF-16 string
	  */
	static c_DataRepresentationFramework::c_UTF16String toUTF16String(const c_DataRepresentationFramework::c_AsciiString& sAsciiString);

	/**
	  * De-Encode provided ISO 8859-1 string as an UTF-16 string
	  */
	static c_DataRepresentationFramework::c_UTF16String toUTF16String(const c_DataRepresentationFramework::c_ISO_8859_1_String& sISO_8859_1_String);

	/**
	  * De-encodes provded UTF16 string to ISO 8859-1 string
	  */
	static c_DataRepresentationFramework::c_ISO_8859_1_String toISO_8859_1_String(const c_DataRepresentationFramework::c_UTF16String& sUTF16String);

	/**
	  * De-encodes provded UTF16 string to ISO 8859-1 string
	  */
	static c_DataRepresentationFramework::c_ISO_8859_1_String toISO_8859_1_String(const c_DataRepresentationFramework::c_UTF8String& sUTF8String);

	/**
	  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
	  * Characters out of range will be logged.
	  */
	static c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const std::string& sString);

	/**
	  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
	  * Characters out of range will be logged.
	  */
	static c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const std::wstring& sWideString);

	/**
	  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
	  * Characters out of range will be logged.
	  */
	static c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const c_DataRepresentationFramework::c_UTF16String& sUTF16String);

	/**
	  * map String used by IDE to typedef
	  */
	typedef String c_IDEString;

	/**
	  * Narrows provided string to an c_DataRepresentationFramework::c_AsciiString.
	  * Characters out of range will be logged.
	  */
	static c_DataRepresentationFramework::c_AsciiString c_DataRepresentationFramework::toAsciiString(const c_IDEString& sIDEString);

	/**
	  * Parses provided string containg a currency value and converts it to an int
	  * with the corresponding cent value.
	  * Example: "1428,50" is converted to int 142850. (cCommaChar = ',' default)
	  * Will throw an  std::exception in case of failure.
	  */
	static int CurrencyValueStringToCentInteger(const c_DataRepresentationFramework::c_AsciiString& sCurrencyValueString,char cCommaChar=',');

	/**
	  * Creates a string representation of provided Amount in cents.
	  * Example:  The cent value 142850 is converted to the string "1428,50". (cCommaChar = ',' default)
	  * Will throw an  std::exception in case of failure.
	  */
	static c_DataRepresentationFramework::c_AsciiString CentIntegerToCurrencyValueString(int centInteger,char cCommaChar=',');

	/**
	  * Parses a string where unprintable chars are represented with <value>
	  * value are two digits hex values.
	  */
	static t_raw_vector parseBracketedHexValueCharString(const c_DataRepresentationFramework::c_AnonymousString& buf);

	/**
	  * creates a hex value brackated Ascii char string where unprintable charachters
	  * are represented as two chars hex values between <..>.
	  */
	static  c_DataRepresentationFramework::c_AsciiString createBracketedHexValueAsciiString(const t_raw_vector& buf);

	/**
	  * creates a hex value brackated ISO 8859-1 string where unprintable charachters
	  * are represented as two chars hex values between <..>.
	  */
	static  c_DataRepresentationFramework::c_ISO_8859_1_String createBracketedHexValueISO8859_1String(const t_raw_vector& buf,bool hexBracketBlankAlso=false);

	/**
	  * Parses a string of hex digits where each two digits are interpreted as
	  * one byte hex value. Fx. "091F7A" is parsed into
	  * a vector of bytes with values 0x09, 0x1F, 0x7A
	  */
	static t_raw_vector parseHexNibblePairString(const c_DataRepresentationFramework::c_AsciiString& HexNibblePairString);

	/**
	  * Cretaes a string of hex nibble pairs from provided data buffer.
	  * Each byte in the buffer is transalted into a two digit hexadecimal output.
	  * data[0x23, 0x34 ...] is output in string as "2334..."
	  */
	static c_DataRepresentationFramework::c_AsciiString createHexNibbleString(const t_raw_vector& buf);

	/**
	  * Creates a vector of unsigned chars from provided string
	  */
	static t_raw_vector createUCharVector(const c_DataRepresentationFramework::c_AnonymousString& buf);

	/**
	  * Creates a string from provided vector of unsigned chars
	  */
	static c_DataRepresentationFramework::c_AsciiString createString(const t_raw_vector& buf);

	/**
	  * Create a 7 bit ascii buffer
	  */
	static t_raw_vector create7BitAsciiBuffer(const t_raw_vector& buf);

	/**
	  * Creates a buffer with the same data as provided bufer but with even parity added
	  */
	static t_raw_vector createEvenParityBuffer(const t_raw_vector& buf);

	/**
	  * Returns the integer value of provided hex digit
	  */
	static int hexValueOfHexDigit(char hex_char);

	/**
	  * Returns provided hex digit string as a long value
	  */
	static unsigned long intValueOfHexString(const std::string& sHexString);
	static unsigned long intValueOfHexString(const c_DataRepresentationFramework::c_AsciiString& sHexString);
	static unsigned long intValueOfHexString(const c_DataRepresentationFramework::c_UTF8String& sHexString);

	/**
	  * Returns provided decimal digit string as a long value
	  */
	static unsigned long intValueOfDecimalString(const std::string& sDecimalString);
	static unsigned long intValueOfDecimalString(const c_DataRepresentationFramework::c_AsciiString& sDecimalString);

	/**
	  * Returns provided char with parity bit set to even parity
	  */
	static char charWithEvenParity(char ch);

	/**
	  * Returns provided char with parity bit removed
	  */
	static char charWithoutParityBit(char ch);

	/**
	  * Returns provided integer as a decimal string
	  */
	static c_DataRepresentationFramework::c_AsciiString intToDecimalString(int val,int minNoOfDigits=-1);

	/**
	  * Returns provided integer as a hexadecimal string
	  */
	static c_DataRepresentationFramework::c_AsciiString intToHexString(int val,int minNoOfDigits=-1);

//	// trim from both ends (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
//	static c_DataRepresentationFramework::c_AsciiString& trimLeftAndRight(c_DataRepresentationFramework::c_AsciiString &s);
//
//	// trim from start (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
//	static c_DataRepresentationFramework::c_AsciiString& trimLeft(c_DataRepresentationFramework::c_AsciiString &s);
//
//	// trim from end (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
//	static c_DataRepresentationFramework::c_AsciiString& trimRight(c_DataRepresentationFramework::c_AsciiString &s);

	// trim from both ends (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
	static template <class S> S& trimLeftAndRight(S &s) {
		return trimLeft(trimRight(s));
	}

	// trim from start (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
	static template <class S> S& trimLeft(S &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end (from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring)
	static template <class S> S& trimRight(S &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	/**
	  * Test code for the methods of this unit
	  */
	bool doTests();

};

/**
  * Exposes char and char array wrapper classes that may be used to
  * wrap an anonymous char, char array into a strong typed char or array
  * that defines representation.
  */
typedef c_DataRepresentationFramework::UCF4c _UCF4c;
typedef c_DataRepresentationFramework::Latin1c _Latin1c;
typedef c_DataRepresentationFramework::Literalc _Literalc;
typedef c_DataRepresentationFramework::Asciic _Asciic;
typedef c_DataRepresentationFramework::UTF8c _UTF8c;

typedef c_DataRepresentationFramework::UTF8sz _UTF8sz;
typedef c_DataRepresentationFramework::UTF16sz _UTF16sz;
typedef c_DataRepresentationFramework::WideAsciisz _WideAsciisz;

typedef c_DataRepresentationFramework::Literalsz _Literalsz;
typedef c_DataRepresentationFramework::Latin1sz _Latin1sz;
typedef c_DataRepresentationFramework::Asciisz _Asciisz;

typedef c_DataRepresentationFramework::UTF8s _UTF8s;
typedef c_DataRepresentationFramework::UTF16s _UTF16s;
typedef c_DataRepresentationFramework::Literals _Literals;
typedef c_DataRepresentationFramework::Latin1s _Latin1s;
typedef c_DataRepresentationFramework::Asciis _Asciis;

/**
  * The DataRepresentationFramework namespace
  * that holds source for representing data
  * in different forms.
  */
namespace DataRepresentationFramework {

	// General template, converting from one string representation to another.
	// Note: This one is selected only if none of the specilaizations below applies
	template <typename _ThisString,typename _OtherString>
	struct StringConvertTrait {
		// This un-specilized template simply returns the provided string as is.
		// NOTE: If you get a compiler error here it is becaus you have not provided
		// a specialization below that converts provided string to the type _OtherString.
		static _OtherString toString(const _ThisString& s) {return s;}; // convert to same type
	};

	// Specilize to return Ascii string
	template <typename _ThisString>
	struct StringConvertTrait<_ThisString,c_DataRepresentationFramework::c_AsciiString> {
		static c_DataRepresentationFramework::c_AsciiString toString(const _ThisString& s) {
			// Specilized to return Ascii string
			return c_DataRepresentationFramework::toAsciiString(s);
		};
	};

	// Specilize to return UTF16 string
	template <typename _ThisString>
	struct StringConvertTrait<_ThisString,c_DataRepresentationFramework::c_UTF16String> {
		static c_DataRepresentationFramework::c_UTF16String toString(const _ThisString& s) {
			// Specilized to return Ascii string
			return c_DataRepresentationFramework::toUTF16String(s);
		};
	};

	// TODO 120129. Provide traits that converts to UTF8String, UTF16String, etc...
	//              At least the ones we expect to need.

	/**
	  * toOtherString<_OtherString> template for UTF8 string that instanciates correct call to
	  * transform provided string to the required "other" representation
	  */
	template <typename _OtherString>
	_OtherString toOtherString(const c_DataRepresentationFramework::c_UTF8String& s) {
		/**
		  * The compiler will match to the trait that converts from UTF8 to Other String
		  */
		return StringConvertTrait<c_DataRepresentationFramework::c_UTF8String,_OtherString>::toString(s);
	};

};

#endif
