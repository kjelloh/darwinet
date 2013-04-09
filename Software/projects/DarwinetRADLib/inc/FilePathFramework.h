/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef FilePathFrameworkH
#define FilePathFrameworkH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "DataRepresentationFrameWork.h"
#include "BusinessLogUnit.h"

//------------------------------------------------------------------------------

/**
  * Invalid File Path Node Append exception class
  * for File Path of type A
  */
template <class A>
class c_InvalidFilePathNodeAppend : public std::runtime_error {
public:
	typedef typename A::node_type N;

	/**
	  * Creates an exception object about invalid node append
	  */
	c_InvalidFilePathNodeAppend(const A* pArray,const N& node)
		: std::runtime_error(
			   std::string("Failed to append \"")
			+  c_DataRepresentationFramework::toUTF8String(pArray->toString()).anonymous()
			+  std::string("\" with \"")
			+  c_DataRepresentationFramework::toUTF8String(node.getCaption()).anonymous()
			+  std::string("\""))
			// TODO 101110, Risk of throw which is not allowed in constructor. Consider storing node and array and build string on what() call.
	{
	}

};

//---------------------------------------------------------------------------
/**
  * Possible types of the nodes of a file path
  */
enum e_FilePahNodeType {
	 eFilePahNodeType_Undefined
	,eFilePahNodeType_Drive
	,eFilePahNodeType_Server
	,eFilePahNodeType_Directory
	,eFilePahNodeType_File
	,eFilePahNodeType_FileOrDirectory
	,eFilePahNodeType_Unknown
};

/**
  * Models a file path node (File name or folder name of a file path)
  * where the name is a string of type S
  */
template <class S>
class c_FilePathNode : public S {
public:

	/**
	  * Conveniant typedef
	  */
	typedef S string_type;

	/**
	  * Constructs a file path node with provided caption and type
	  */
	c_FilePathNode(const S& sCaption=S(_Asciisz("")),e_FilePahNodeType type=eFilePahNodeType_Undefined)
		:  S(sCaption)
		  ,m_type(type)
	{

	}

	/**
	  * Copy constructor
	  */
	c_FilePathNode(const c_FilePathNode<S>& other_value)
	{
		*this = other_value; // use asignment operator
	}

	/**
	  * Asignment operator
	  */
	c_FilePathNode<S>& operator=(const c_FilePathNode<S>& other_value) {
		static_cast<S*>(this)->operator =(other_value);
		this->m_type = other_value.m_type;
		return *this;
	}

	/**
	  * Returns this node caption (string contents)
	  */
	S getCaption() const {
		return *this;
	}

	/**
	  * Returns the file name without the extension.
	  * I.e the part of the name before '.'
	  */
	S NameWithoutExtension() const {
		S result;
		int posOfSeparator = this->find('.',0);
		if (posOfSeparator>0) {
			// Process as anonymous string. The '.' is spotted correct also if string is multi-byte
			result.anonymous() = this->anonymous().substr(0,posOfSeparator);
		}
		return result;
	}

	bool hasExtension() const {
		bool result = false;
		int posOfSeparator = this->find('.',0);
		result = (posOfSeparator >= 0);
		return result;
	}

	/**
	  * Returns this node type
	  */
	e_FilePahNodeType getType() const {
		return this->m_type;
	}

	/**
	  * Sets this node type
	  */
	void setType(e_FilePahNodeType type) {
		this->m_type = type;
	}

	/**
	  * Returns true if the node may be a
	  * directory node. For example a drive node
	  * or a server node may NOT be a directory node.
	  * Used by directory creating method to know if
	  * the node shall be cerated as directory
	  * in the file system.
	  */
	bool mayBeDirectoryNode() const {
		bool result = (    (this->getType() != eFilePahNodeType_Drive)
						&& (this->getType() != eFilePahNodeType_Server));
		return result;
	}

private:
	/**
	  * Private storage of this node type
	  */
	e_FilePahNodeType m_type;
};


/**
  * File path made up of nodes of type N
  */
template <class N>
class c_FilePathNodeArray : public std::vector<N> {
public:
	typedef typename N::string_type  S;

	/**
	  * Constructs an array of file path nodes from provided file path string.
	  */
	c_FilePathNodeArray(const S& sFilePath = S(_Asciisz("")))
		: std::vector<N>()
	{
		this->buildArrayFromString(sFilePath);
	}

	//------------------------------------------------------------------------------
	/**
	  * Copy constructor
	  */
	c_FilePathNodeArray(const c_FilePathNodeArray<N>& other_value)
		: std::vector<N>(other_value)
	{

	}

	//------------------------------------------------------------------------------
	/**
	  * Asignment operator
	  */
	c_FilePathNodeArray<N>& operator=(const c_FilePathNodeArray<N>& other_value) {
		c_FilePathNodeArray<N> temp_copy(other_value);
		static_cast<std::vector<N>&>(*this).swap(temp_copy);
		return *this;
	}

	//------------------------------------------------------------------------------
	/**
	  * Asignment to string path operator
	  */
	c_FilePathNodeArray<N>& operator=(const typename N::string_type& sFilePath) {
		c_FilePathNodeArray<N> temp_copy(sFilePath);
		static_cast<std::vector<N>&>(*this).swap(temp_copy);
		return *this;
	}

	//------------------------------------------------------------------------------
	/**
	  * Add operator
	  */
	c_FilePathNodeArray<N> operator+(const c_FilePathNodeArray<N>& other_value) const {
		c_FilePathNodeArray<N> result(*this);
		result.append(other_value);
		return result;
	}

	//------------------------------------------------------------------------------
	/**
	  * Sum operator array + string path
	  */
	c_FilePathNodeArray<N> operator+(const typename N::string_type& sFilePath) const {
		c_FilePathNodeArray<N> result(*this);
		result += c_FilePathNodeArray<N>(sFilePath);
		return result;
	}

	//------------------------------------------------------------------------------
	/**
	  * Add operator to add node
	  */
	void operator+=(const N& node) {
		this->append(node);
	}

	//------------------------------------------------------------------------------
	/**
	  * Add operator add node array
	  */
	void operator+=(const c_FilePathNodeArray<N>& other_value) {
		this->append(other_value);
	}

	//------------------------------------------------------------------------------
	/**
	  * Add operator to add null terminated path string
	  */
	void operator+=(const S& sFilePath) {
		this->append(c_FilePathNodeArray<N>(sFilePath));
	}

	//------------------------------------------------------------------------------
	/**
	  * Path contents Equal test operator.
	  * Two paths are equal if all nodes match.
	  */
	bool operator==(const c_FilePathNodeArray<N>& other_value) const {
// DEBUG
c_LogString sMessage(__FUNCTION__);
sMessage += " Comparing ";
sMessage += toLogString(this->toDebugString());
sMessage += _Asciisz(" to ");
sMessage += toLogString(other_value.toDebugString());
LOG_DEVELOPMENT_TRACE(sMessage);

		bool result = false;
		if (this->size() == other_value.size()-1) {
			if (other_value.back().getCaption().size() == 0) {
				// Match "\MyRoot\MyDir" and "\MyRoot\MyDir\"
				result = (*this == other_value.getParentPath());
			}
		}
		else if (this->size()-1 == other_value.size()) {
			if (this->back().getCaption().size() == 0) {
				// Match \MyRoot\MyDir\ and \MyRoot\MyDir
				result = (this->getParentPath() == other_value);
			}
		}
		else if (this->size() == other_value.size()) {
			// May be equal contents
			c_FilePathNodeArray<N>::const_iterator this_iter = this->begin();
			c_FilePathNodeArray<N>::const_iterator other_iter = other_value.begin();
			while (this_iter != this->end()) {
				// Compare captions in same case as DOS does
				typename N::string_type sThisCaption = this_iter->getCaption();
				typename N::string_type sOtherCaption = other_iter->getCaption();
				#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
				std::transform (sThisCaption.begin (), sThisCaption.end (), sThisCaption.begin (), (int(*)(int)) std::toupper);
				std::transform (sOtherCaption.begin (), sOtherCaption.end (), sOtherCaption.begin (), (int(*)(int)) std::toupper);
				#endif // (__BCPLUSPLUS__ || __CYGWIN32__)
				if (!(sThisCaption == sOtherCaption)) {
					break; // Give up
				}
				this_iter++;
				other_iter++;
			}
			result = (this_iter == this->end()); // Came to end without break = equal
		}
		return result;
	}

	#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
	/**
	  * Appends provided node as last node in the array.
	  * Will throw an exception if the node violates current path.
	  */
	void append(const N& node) {
		if (this->size() == 0) {
			// The array is empty. Add anything
			this->push_back(node);
		}
		else {
			// Apply node append restriction rules based
			// on added node type
			switch (node.getType()) {
				case eFilePahNodeType_Drive:
					// Failure. Drive must be first!
					throw c_InvalidFilePathNodeAppend<c_FilePathNodeArray<N> >(this,node);
				break;
				case eFilePahNodeType_Undefined:
				case eFilePahNodeType_Directory:
				case eFilePahNodeType_File:
				case eFilePahNodeType_FileOrDirectory:
				case eFilePahNodeType_Unknown:
					// Ok to append to anything but a file or an empty node.
					// (No empty nodes allowed within the path as this will cause
					//  mutlipple separators).
					if (this->back().getType() != eFilePahNodeType_File) {
						// Remove prevous node if it is empty.
						// An empty node is only allowed as first or last node.
						// This handles path like "\MyDir" as node("") + Node("MyDir")
						// and "MyDir\" as node("Mydir") + node("")
						// or "C:\" as node("C:") + node("")
						if (this->back().getCaption().size() == 0) {
							this->pop_back();
						}
						this->push_back(node);

						// Update type of previous node. We now know it has
						// to be a drive, server or a directory as these are the only ones
						// allowed to have preceding nodes.
						if (    (this->back().getType() != eFilePahNodeType_Drive)
							 && (this->back().getType() != eFilePahNodeType_Server)) {
							this->back().setType(eFilePahNodeType_Directory);
						}
					}
					else {
						throw c_InvalidFilePathNodeAppend<c_FilePathNodeArray<N> >(this,node);
					}
				break;

			default:
				;
			}

		}
	}
	#endif // defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)


	/**
	  * Appends provided array after our current nodes.
	  * Will throw an exception if the nodes violates current path.
	  */
	void append(const c_FilePathNodeArray<N>& other_value) {
		// Append each node of provided array
		c_FilePathNodeArray::const_iterator iter = other_value.begin();
		while (iter != other_value.end()) {
			this->append(*iter);
			iter++;
		}
	}

	/**
	  * Returns this path with the last node removed
	  */
	c_FilePathNodeArray<N> getParentPath() const {
		c_FilePathNodeArray<N> result = *this;
		result.pop_back();
		return result;
	}

    #if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
	/**
	  * Returns this node path as a string path
	  */
	typename N::string_type toString() const {
		typename N::string_type result;
		c_FilePathNodeArray<N>::const_iterator iter = this->begin();
		bool firstNode = true;
		while (iter != this->end()) {
			if (firstNode) {
				firstNode = false;
			}
			else {
				// Add separator from previous node
				result += _Asciisz("\\"); // Always between nodes of path
			}
			// Then add the next node caption
			result += iter->getCaption();

			iter++;
		}
		// Add end	"//"
		return result;
	}
    #else
    #error "Not defined for this environment"
    #endif

	#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
	/**
	  * Returns this node path as a debug information string
	  */
	typename N::string_type toDebugString() const {
		typename N::string_type result;
		c_FilePathNodeArray<N>::const_iterator iter = this->begin();
		int index = 0;
		while (iter != this->end()) {
			// Add separator from previous node
			result += _Asciisz("[");
			result += c_DataRepresentationFramework::intToDecimalString(index);
			result += _Asciisz("]\"");
			// Then add the next node caption
			result += iter->getCaption();
			result += _Asciisz("\"");

			iter++;
			index++;
		}
		// Add end
	//
		return result;
	}
	#else
	#error "Not defined for this environment"
	#endif

	typedef typename std::vector<N>::iterator iterator;
	typedef typename std::vector<N>::const_iterator const_iterator;
	typedef N node_type;
private:


	#if defined(__BCPLUSPLUS__) || defined(__CYGWIN32__)
	/**
	  * Builds this array from privded file path string
	  */
	void buildArrayFromString(const S& sFilePath) {
		try {
			// MyDirectory
			// \MyDirectory
			// MyFile
			// MyFile.txt
			// c:\MyDirectory
			// c:\MyDirectory\MyDirectory
			// c:\MyDirectory\MyFile.txt
			// c:\MyDirectory\MyFile
			// \\server\dir\dir

			// Separate on ':','\','.'

			typename N::string_type::const_iterator iter = sFilePath.begin();
			typename N::string_type node_caption;

			// Start by checking if there is a preceeding server node, one started with '\\'
			bool thisIsAServerNode = false;
			if (*iter == '\\') {
				if ((iter+1) != sFilePath.end()) {
					if (*(iter+1) == '\\') {
						// It is \\ at the beginning
						iter++; // skip first backslash
						iter++; // skip second backslash
						thisIsAServerNode = true;
						node_caption = _Asciisz("\\\\"); // Server node caption includes the '\\'
					}
				}
			}
			while (iter != sFilePath.end()) {
				switch (*iter) {
				case ':': {
					// Drive separator
					node_caption.anonymous() += *iter;
					this->append(N(node_caption,eFilePahNodeType_Drive));
					node_caption = _Asciisz("");
				}
				break;
				case '\\': {
					// Path separator.
					if (thisIsAServerNode) {
						this->append(N(node_caption,eFilePahNodeType_Server));
						thisIsAServerNode = false;
					}
					else {
						this->append(N(node_caption,eFilePahNodeType_FileOrDirectory));
					}
					node_caption = _Asciisz("");
				}
				break;

				default:
					// Not a separator. Add to node caption
					node_caption.anonymous() += *iter;
					;
				}
				iter++;
			}
			// Add the tail node. Must be a file or a directory
			if (node_caption.size() > 0) {
				this->append(N(node_caption,eFilePahNodeType_FileOrDirectory));
			}
		}
		catch (...) {
		}
	}
	#else
	#error "Not defined for this environment"
	#endif

};

//------------------------------------------------------------------------------
/**
  * Creates a static facade towards routines associated with file path handling
  */
template <class A>
class c_FilePathFrameworkT {
public:

	/**
	  * Convenient typedef
	  */
	typedef typename A::node_type N;

	/**
	  * Creates provided directory path in file system.
	  * Each node in the path will be created if it does not yet exist
	  */
	static bool directoryPathExists(const A& directory_path) {
		bool result = false; // default
		#if defined(__BCPLUSPLUS__)
		result = DirectoryExists(directory_path.toString().c_str());
		#else
		LOG_NOT_IMPLEMENTED;
		#endif
		return result;
	}

	//------------------------------------------------------------------------------
	/**
	  * Creates provided directory path in file system.
	  * Each node in the path will be created if it does not yet exist
	  */
	static bool ensureDirectoryPathExists(const A& directory_path) {
		bool result = false; // default

		#if defined(__BCPLUSPLUS__)
		// Loop through the path and ensure that each directory node exists
		typename A::const_iterator iter = directory_path.begin();
		A current_path;
		while (iter != directory_path.end()) {
			current_path += *iter;
			if (iter->mayBeDirectoryNode()) {
				if (!c_FilePathFrameworkT::directoryPathExists(current_path)) {
					// Try to create it
					c_DataRepresentationFramework::c_UTF8String sMessage("Creating directory=");
					sMessage += c_DataRepresentationFramework::toUTF8String(current_path.toString());
					LOG_BUSINESS(sMessage);
					if (!CreateDir(current_path.toString().c_str())) {
						// Failed to create it. Give up
						DWORD api_error_code = GetLastError();
						c_LogString sMessage(__FUNCTION__);
						sMessage += " failed. CreateDir() returned error ";
						sMessage += logStringOfWinApiErrorCode(api_error_code);
						LOG_DESIGN_INSUFFICIENCY(sMessage);
						break;
					}
				}
			}
			iter++;
		}
		result = (iter == directory_path.end()); // true if did not break in the process
		#else
		LOG_NOT_IMPLEMENTED;
		#endif

		return result;
	}

	//------------------------------------------------------------------------------
	/**
	  * Returns true if the file defined by provided file path exists
	  * in the file system.
	  */
	static bool fileExists(const A& file_path) {
		bool result = false; // default
		#if defined(__BCPLUSPLUS__)
		String sFilePath(file_path.toString().c_str());
		if (FileExists(sFilePath)) {
			// Get the file attributes to detect it is really a file
			unsigned short Attributes = FileGetAttr(sFilePath);
			result = !(Attributes & faDirectory); // Not a directory
		}
		#else
		LOG_NOT_IMPLEMENTED;
		#endif

		return result;
	}

	//------------------------------------------------------------------------------
	/**
	  * Deletes the file at provided path
	  */
	static void deleteFile(const A& file_path) {
		#if defined(__BCPLUSPLUS__)
		DeleteFile(file_path.toString().c_str());
		#else
		LOG_NOT_IMPLEMENTED;
		#endif

	}

	/**
	  * Renames file with provided old file name in provided folder path to provided new file name.
	  */
	static void renameFile(const A& folderPath,const N& oldFileName,const N& newFileName) {
		A old_file_name_path = folderPath;
		old_file_name_path += oldFileName;
		A new_file_name_path = folderPath;
		new_file_name_path += newFileName;

		// Now rename the saved live log to this name
		#if defined(__BCPLUSPLUS__)
		RenameFile(old_file_name_path.toString().c_str(),new_file_name_path.toString().c_str());
		#else
		LOG_NOT_IMPLEMENTED;
		#endif
	}

	/**
	  * Copies file at proived sorce path to provided target path
	  */
	static bool copyFile(const A& source_path,const A& target_path) {
		bool result = false; // default
		#if defined(__BCPLUSPLUS__)
		ensureDirectoryPathExists(target_path.getParentPath());
		// Call Windows API
		result = CopyFile(source_path.toString().c_str(),target_path.toString().c_str(),false); // Copy and succeed even if target exists
		#else
		LOG_NOT_IMPLEMENTED;
		#endif
		return result;
	}

	//------------------------------------------------------------------------------

	/**
	  * Performs tests on functionality of this unit
	  */
	static void doTest() {

	//	#define COMPILE_UNALLOWED_CONSTRUCTS // DOcompile constructs that must generate compile errors
		#undef COMPILE_UNALLOWED_CONSTRUCTS // Do NOT compile constructs that must generate compile errors

		{
			#if defined(__BCPLUSPLUS__)

			std::string s1;
			std::string s2;
			c_DataRepresentationFramework::c_UTF8String sUTF8String;

			throw std::runtime_error(s1+sUTF8String+"Hej");

			typedef c_FilePathNode<c_DataRepresentationFramework::c_UTF8String> c_UTF8FileName;
			typedef c_FilePathNodeArray<c_UTF8FileName> c_UTF8FilePath;

			c_UTF8FilePath UTF8FilePath = _UTF8sz("\\Mapp1\\Mapp med ö\\Filnamn med ö.txt");
			LOG_DEVELOPMENT_TRACE(UTF8FilePath.toString());

			c_FilePath FilePath1 = u"\\Mapp1\\Mapp med ö\\Filnamn med ö.txt";
			c_FilePath FilePath2 = u"\\Mapp2\\Mapp med ö\\Filnamn med ö.txt";
			c_FileName Filename1 = c_FileName(u"Mitt filnamn 1 med ö.txt");
			c_FileName Filename2 = c_FileName(u"Mitt filnamn 2 med ö.txt");

			FilePath1 = FilePath2;
			FilePath1 += FilePath2;
			FilePath2 += Filename1;
			if (Filename1 == Filename2) {

			}
			if (FilePath1 == FilePath2) {

			}

			#ifdef COMPILE_UNALLOWED_CONSTRUCTS
			c_FileName Filename1 = u"Mitt filnamn 1 med ö.txt"; // Make to work?
			c_FileName Filename2 = u"Mitt filnamn 2 med ö.txt"; // Make to work?
			if (FilePath1 == _UTF16sz(L"\\Mapp1\\Mapp med ö\\Filnamn med ö.txt")) {
				// OK
			}
			c_UTF8FilePath sUTF8FilePath2 = "\\Mapp1\\Mapp med ö\\Filnamn med ö.txt";
			c_FilePath sPath2 = ""; // Not allowed from anonymous string
			#endif // COMPILE_UNALLOWED_CONSTRUCTS

			#else
			LOG_NOT_IMPLEMENTED;
			#endif

		}

		#undef COMPILE_UNALLOWED_CONSTRUCTS // Do NOT compile constructs that must generate compile errors
	}

};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
typedef c_FilePathNode<c_DataRepresentationFramework::c_UTF8String> c_UTF8FileName;
typedef c_FilePathNodeArray<c_UTF8FileName> c_UTF8FilePath;

typedef c_FilePathNode<c_DataRepresentationFramework::c_UTF16String> c_UTF16FileName;
typedef c_FilePathNodeArray<c_UTF16FileName> c_UTF16FilePath;

/**
  * Convenient type defs. for default types to use
  */
#if defined(__BCPLUSPLUS__)
typedef c_UTF16FileName c_FileName;
typedef c_UTF16FilePath c_FilePath;
#else
typedef c_UTF8FileName c_FileName;
typedef c_UTF8FilePath c_FilePath;
#endif
typedef c_FilePathFrameworkT<c_FilePath> c_FilePathFramework;

#endif
