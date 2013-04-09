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
//#include "FilePathFramework.h"
//#include "Sysutils.hpp" // FileExists...
//#include "BusinessLogUnit.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

///**
//  * Constructs a file path node with provided caption and type
//  */
//c_FilePathNode::c_FilePathNode(const c_DataRepresentationFramework::c_UTF16String& caption,e_FilePahNodeType type)
//	:  c_DataRepresentationFramework::c_UTF16String(caption)
//	  ,m_type(type)
//{
//
//}
//
///**
//  * Copy constructor
//  */
//c_FilePathNode::c_FilePathNode(const c_FilePathNode& other_value)
//{
//	*this = other_value; // use asignment operator
//}
//
///**
//  * Asignment operator
//  */
//c_FilePathNode& c_FilePathNode::operator=(const c_FilePathNode& other_value) {
//	static_cast<c_DataRepresentationFramework::c_UTF16String*>(this)->operator =(other_value);
//	this->m_type = other_value.m_type;
//	return *this;
//}
//
///**
//  * Returns this node caption (string contents)
//  */
//c_DataRepresentationFramework::c_UTF16String c_FilePathNode::getCaption() const {
//	return *this;
//}
//
///**
//  * Returns the file name without the extension.
//  * I.e the part of the name before '.'
//  */
//c_DataRepresentationFramework::c_UTF16String c_FilePathNode::NameWithoutExtension() const {
//	c_DataRepresentationFramework::c_UTF16String result;
//	int posOfSeparator = this->find('.',0);
//	if (posOfSeparator>0) {
//		// Process as anonymous string. The '.' is spotted correct also if string is multi-byte
//		result.anonymous() = this->anonymous().substr(0,posOfSeparator);
//	}
//	return result;
//}
//
///**
//  * Returns this node type
//  */
//e_FilePahNodeType c_FilePathNode::getType() const {
//	return this->m_type;
//}
//
///**
//  * Sets this node type
//  */
//void c_FilePathNode::setType(e_FilePahNodeType type) {
//	this->m_type = type;
//}
//
///**
//  * Returns true if the node may be a
//  * directory node. For example a drive node
//  * or a server node may NOT be a directory node.
//  * Used by directory creating method to know if
//  * the node shall be cerated as directory
//  * in the file system.
//  */
//bool c_FilePathNode::mayBeDirectoryNode() const {
//	bool result = (    (this->getType() != eFilePahNodeType_Drive)
//					&& (this->getType() != eFilePahNodeType_Server));
//	return result;
//}
//
////------------------------------------------------------------------------------
////------------------------------------------------------------------------------
///**
//  * Constructs an array of file path nodes from provided file path string.
//  */
//c_FilePathNodeArray::c_FilePathNodeArray(const c_DataRepresentationFramework::c_UTF16String& sFilePath)
//	: std::vector<c_FilePathNode>()
//{
//	this->buildArrayFromString(sFilePath);
//}
//
////------------------------------------------------------------------------------
///**
//  * Copy constructor
//  */
//c_FilePathNodeArray::c_FilePathNodeArray(const c_FilePathNodeArray& other_value)
//	: std::vector<c_FilePathNode>()
//{
//	*this = other_value; // Use asignment operator
//}
//
////------------------------------------------------------------------------------
///**
//  * Asignment operator
//  */
//c_FilePathNodeArray& c_FilePathNodeArray::operator=(const c_FilePathNodeArray& other_value) {
//	static_cast<std::vector<c_FilePathNode>*>(this)->operator =(other_value);
//	return *this;
//}
//
////------------------------------------------------------------------------------
///**
//  * Asignment to string path operator
//  */
//c_FilePathNodeArray& c_FilePathNodeArray::operator=(const c_DataRepresentationFramework::c_UTF16String& sFilePath) {
//	*this = c_FilePathNodeArray(sFilePath);
//	return *this;
//}
//
////------------------------------------------------------------------------------
///**
//  * Sum operator
//  */
//c_FilePathNodeArray c_FilePathNodeArray::operator+(const c_FilePathNodeArray& other_value) const {
//	c_FilePathNodeArray result(*this);
//	result.append(other_value);
//	return result;
//}
//
////------------------------------------------------------------------------------
///**
//  * Sum operator array + string path
//  */
//c_FilePathNodeArray c_FilePathNodeArray::operator+(const c_DataRepresentationFramework::c_UTF16String& sFilePath) const {
//	c_FilePathNodeArray result(*this);
//	result += c_FilePathNodeArray(sFilePath);
//	return result;
//}
//
////------------------------------------------------------------------------------
///**
//  * Add operator to add node
//  */
//void c_FilePathNodeArray::operator+=(const c_FilePathNode& node) {
//	this->append(node);
//}
//
////------------------------------------------------------------------------------
///**
//  * Add operator add node array
//  */
//void c_FilePathNodeArray::operator+=(const c_FilePathNodeArray& other_value) {
//	this->append(other_value);
//}
//
////------------------------------------------------------------------------------
///**
//  * Add operator to add null terminated path string
//  */
//void c_FilePathNodeArray::operator+=(const c_DataRepresentationFramework::c_UTF16String& sFilePath) {
//	this->append(c_FilePathNodeArray(sFilePath));
//}
//
////------------------------------------------------------------------------------
///**
//  * Path contents Equal test operator.
//  * Two paths are equal if all nodes match.
//  */
//bool c_FilePathNodeArray::operator==(const c_FilePathNodeArray& other_value) const {
//	bool result = false;
//	if (this->size() == other_value.size()) {
//		// May be equal contents
//		c_FilePathNodeArray::const_iterator this_iter = this->begin();
//		c_FilePathNodeArray::const_iterator other_iter = other_value.begin();
//		while (this_iter != this->end()) {
//			// Compare captions in same case as DOS does
//			c_DataRepresentationFramework::c_UTF16String sThisCaption = this_iter->getCaption();
//			c_DataRepresentationFramework::c_UTF16String sOtherCaption = other_iter->getCaption();
//			std::transform (sThisCaption.begin (), sThisCaption.end (), sThisCaption.begin (), (int(*)(int)) std::toupper);
//			std::transform (sOtherCaption.begin (), sOtherCaption.end (), sOtherCaption.begin (), (int(*)(int)) std::toupper);
//			if (!(sThisCaption == sOtherCaption)) {
//				break; // Give up
//			}
//			this_iter++;
//			other_iter++;
//		}
//		result = (this_iter == this->end()); // Came to end without break = equal
//	}
//	return result;
//}
//
//
///**
//  * Builds this array from privded file path string
//  */
//void c_FilePathNodeArray::buildArrayFromString(const c_DataRepresentationFramework::c_UTF16String& sFilePath) {
//	try {
//		// MyDirectory
//		// \MyDirectory
//		// MyFile
//		// MyFile.txt
//		// c:\MyDirectory
//		// c:\MyDirectory\MyDirectory
//		// c:\MyDirectory\MyFile.txt
//		// c:\MyDirectory\MyFile
//		// \\server\dir\dir
//
//		// Separate on ':','\','.'
//
//		c_DataRepresentationFramework::c_UTF16String::const_iterator iter = sFilePath.begin();
//		c_DataRepresentationFramework::c_UTF16String node_caption;
//
//		// Start by checking if there is a preceeding server node, one started with '\\'
//		bool thisIsAServerNode = false;
//		if (*iter == '\\') {
//			if ((iter+1) != sFilePath.end()) {
//				if (*(iter+1) == '\\') {
//					// It is \\ at the beginning
//					iter++; // skip first backslash
//					iter++; // skip second backslash
//					thisIsAServerNode = true;
//					node_caption.anonymous() = L"\\\\"; // Server node caption includes the '\\'
//				}
//			}
//		}
//		while (iter != sFilePath.end()) {
//			switch (*iter) {
//			case ':': {
//				// Drive separator
//				node_caption.anonymous() += *iter;
//				this->append(c_FilePathNode(node_caption,eFilePahNodeType_Drive));
//				node_caption.anonymous() = L"";
//			}
//			break;
//			case '\\': {
//				// Path separator.
//				if (thisIsAServerNode) {
//					this->append(c_FilePathNode(node_caption,eFilePahNodeType_Server));
//					thisIsAServerNode = false;
//				}
//				else {
//					this->append(c_FilePathNode(node_caption,eFilePahNodeType_FileOrDirectory));
//				}
//				node_caption.anonymous() = L"";
//			}
//			break;
//
//			default:
//				// Not a separator. Add to node caption
//				node_caption.anonymous() += *iter;
//				;
//			}
//			iter++;
//		}
//		// Add the tail node. Must be a file or a directory
//		if (node_caption.size() > 0) {
//			this->append(c_FilePathNode(node_caption,eFilePahNodeType_FileOrDirectory));
//		}
//	}
//	catch (...) {
//	}
//}
//
///**
//  * Appends provided node as last node in the array.
//  * Will throw an exception if the node violates current path.
//  */
//void c_FilePathNodeArray::append(const c_FilePathNode& node) {
//	if (this->size() == 0) {
//		// The array is empty. Add anything
//		this->push_back(node);
//	}
//	else {
//		// Apply node append restriction rules based
//		// on added node type
//		switch (node.getType()) {
//			case eFilePahNodeType_Drive:
//				// Failure. Drive must be first!
//				throw c_InvalidFilePathNodeAppend(this,node);
//			break;
//			case eFilePahNodeType_Undefined:
//			case eFilePahNodeType_Directory:
//			case eFilePahNodeType_File:
//			case eFilePahNodeType_FileOrDirectory:
//			case eFilePahNodeType_Unknown:
//				// Ok to append to anything but a file or an empty node.
//				// (No empty nodes allowed within the path as this will cause
//				//  mutlipple separators).
//				if (this->back().getType() != eFilePahNodeType_File) {
//					// Remove prevous node if it is empty.
//					// An empty node is only allowed as first or last node.
//					// This handles path like "\MyDir" as node("") + Node("MyDir")
//					// and "MyDir\" as node("Mydir") + node("")
//					// or "C:\" as node("C:") + node("")
//					if (this->back().getCaption().size() == 0) {
//						this->pop_back();
//					}
//					this->push_back(node);
//
//					// Update type of prevous node. We now know it has
//					// to be a drive, server or a directory as these are the only ones
//					// allowed to have preceeding nodes.
//					if (    (this->back().getType() != eFilePahNodeType_Drive)
//						 && (this->back().getType() != eFilePahNodeType_Server)) {
//						this->back().setType(eFilePahNodeType_Directory);
//					}
//				}
//				else {
//					throw c_InvalidFilePathNodeAppend(this,node);
//				}
//			break;
//
//		default:
//			;
//		}
//
//	}
//}
//
///**
//  * Appends provided array after our current nodes.
//  * Will throw an exception if the nodes violates current path.
//  */
//void c_FilePathNodeArray::append(const c_FilePathNodeArray& other_value) {
//	// APpend each node of provided array
//	c_FilePathNodeArray::const_iterator iter = other_value.begin();
//	while (iter != other_value.end()) {
//		this->append(*iter);
//		iter++;
//	}
//
//}
//
///**
//  * Returns this path with the last node removed
//  */
//c_FilePathNodeArray c_FilePathNodeArray::getParentPath() const {
//	c_FilePathNodeArray result = *this;
//	result.pop_back();
//	return result;
//}
//
///**
//  * Returns this node path as a string path
//  */
//c_DataRepresentationFramework::c_UTF16String c_FilePathNodeArray::toString() const {
//	c_DataRepresentationFramework::c_UTF16String result;
//	c_FilePathNodeArray::const_iterator iter = this->begin();
//	bool firstNode = true;
//	while (iter != this->end()) {
//		if (firstNode) {
//			firstNode = false;
//		}
//		else {
//			// Add separator from previous node
//			result.anonymous() += L"\\"; // Always between nodes of path
//		}
//		// Then add the next node caption
//		result += iter->getCaption();
//
//		iter++;
//	}
//	// Add end
//
//	return result;
//}
//
//
///**
//  * Creates an exception object about invalid node append
//  */
//c_InvalidFilePathNodeAppend::c_InvalidFilePathNodeAppend(const c_FilePathNodeArray* pArray,const c_FilePathNode& node)
//	: std::runtime_error(
//		   std::string("Failed to append \"")
//		+  c_DataRepresentationFramework::toUTF8String(pArray->toString()).anonymous()
//		+  std::string("\" with \"")
//		+  c_DataRepresentationFramework::toUTF8String(node.getCaption()).anonymous()
//		+  std::string("\""))
//		// TODO 101110, Risk of throw which is not allowed in constructor. Consider storing node and array and build string on what() call.
//{
//}
//
////------------------------------------------------------------------------------
////------------------------------------------------------------------------------
//
///**
//  * Creates provided directory path in file system.
//  * Each node in the path will be created if it does not yet exist
//  */
//bool c_FilePathFramework::directoryPathExists(const c_FilePath& directory_path) {
//	bool result = false; // default
//	result = DirectoryExists(directory_path.toString().c_str());
//	return result;
//}
//
////------------------------------------------------------------------------------
///**
//  * Creates provided directory path in file system.
//  * Each node in the path will be created if it does not yet exist
//  */
//bool c_FilePathFramework::ensureDirectoryPathExists(const c_FilePath& directory_path) {
//	bool result = false; // default
//
//	// Loop through the path and ensure that each directory node exists
//	c_FilePath::const_iterator iter = directory_path.begin();
//	c_FilePath current_path;
//	while (iter != directory_path.end()) {
//		current_path += *iter;
//		if (iter->mayBeDirectoryNode()) {
//			if (!c_FilePathFramework::directoryPathExists(current_path)) {
//				// Try to create it
//				c_DataRepresentationFramework::c_UTF8String sMessage("Creating directory=");
//				sMessage += c_DataRepresentationFramework::toUTF8String(current_path.toString());
//				LOG_BUSINESS(sMessage);
//				if (!CreateDir(current_path.toString().c_str())) {
//					// Failed to create it. Give up
//					break;
//				}
//			}
//		}
//		iter++;
//	}
//	result = (iter == directory_path.end()); // true if did not break in the process
//	return result;
//}
//
////------------------------------------------------------------------------------
///**
//  * Returns true if the file defined by provided file path exists
//  * in the file system.
//  */
//bool c_FilePathFramework::fileExists(const c_FilePath& file_path) {
//	bool result = false; // default
//	result = FileExists(AnsiString(file_path.toString().c_str()));
//	return result;
//}
//
////------------------------------------------------------------------------------
///**
//  * Deletes the file at provided path
//  */
//void c_FilePathFramework::deleteFile(const c_FilePath& file_path) {
//	DeleteFile(file_path.toString().c_str());
//}
//
///**
//  * Renames file with provided old file name in provided folder path to provided new file name.
//  */
//void c_FilePathFramework::renameFile(const c_FilePath& folderPath,const c_FileName& oldFileName,const c_FileName& newFileName) {
//	c_FilePath old_file_name_path = folderPath;
//	old_file_name_path += oldFileName;
//	c_FilePath new_file_name_path = folderPath;
//	new_file_name_path += newFileName;
//
//	// Now rename the saved live log to this name
//	RenameFile(old_file_name_path.toString().c_str(),new_file_name_path.toString().c_str());
//}
#endif // __BCPLUSPLUS__

