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
#include "PathsFramework.h"
#include <map>

//---------------------------------------------------------------------------

#pragma package(smart_init)

namespace oprime4 {

	typedef unsigned long t_key;
	typedef int t_index;
	typedef std::vector<t_key> t_keys;
	typedef std::vector<t_index> t_indexes;
	typedef t_keys::iterator t_keys_iterator;
	typedef t_indexes::iterator t_indexes_iterator;
	typedef t_keys::const_iterator t_keys_const_iterator;
	typedef t_indexes::const_iterator t_indexes_const_iterator;

	class c_IndexedKeyPath; // forward

	class c_IndexedKey {
	public:
		c_IndexedKey(const t_key& key, const t_index& index) : m_key(key),m_index(index) {};
		c_IndexedKeyPath operator+(const c_IndexedKey& other_instance);
		t_key& key() {return m_key;};
		const t_key& key() const {return m_key;};
		t_index& index() {return m_index;};
		const t_index& index() const {return m_index;};
	private:
		t_key m_key;
		t_index m_index;
	};

	/**
	  * Acts like a c_IndexedKey.
	  * A const c_IndexedKeyProxy does not allow modification (may not be used a lvalue).
	  * A non-const c_IndexedKeyProxy allows read (rvalue use) and write (lvalue use).
	  * When used as rvalue it is implicitally converted to c_IndexedKey.
	  * When used as lvalue the operator= is used.
	  * All read and write access defers to referenced real values.
	  */
	class c_IndexedKeyProxy {
	public:
		typedef c_IndexedKey value_type;
		// Create proxy taking non-const references to the real objects.
		c_IndexedKeyProxy(t_key& key_ref, t_index& index_ref): m_key_ref(key_ref), m_index_ref(index_ref) {};
		// Assign to us by really assigning to the real objects
		c_IndexedKeyProxy& operator=(const c_IndexedKey& indexed_key) {m_key_ref = indexed_key.key();m_index_ref = indexed_key.index();return *this;};
		// Implicit cast ourself to real object rvalue.
		operator value_type() const {return c_IndexedKey(m_key_ref,m_index_ref);} // rvalue use

		// begin c_IndexedKey
		t_key& key() {return m_key_ref;};
		const t_key& key() const {return m_key_ref;};
		t_index& index() {return m_index_ref;};
		const t_index& index() const {return m_index_ref;};
		// End c_IndexedKey

	private:
		t_key& m_key_ref;
		t_index& m_index_ref;
	};

	class c_IndexedKeyPathIterator {
	public:
		typedef c_IndexedKeyProxy reference;
		typedef boost::shared_ptr<reference> pointer;

		c_IndexedKeyPathIterator(const t_keys_iterator& keys_iterator,const t_indexes_iterator& indexes_iterator) : m_keys_iterator(keys_iterator),m_indexes_iterator(indexes_iterator) {};
		reference operator*() const {return reference(*m_keys_iterator,*m_indexes_iterator);};
		pointer operator->() const {return pointer(new reference(*m_keys_iterator,*m_indexes_iterator));};
		bool operator==(const c_IndexedKeyPathIterator& other_instance) {return (m_keys_iterator==other_instance.m_keys_iterator) && (m_indexes_iterator==other_instance.m_indexes_iterator);};
		bool operator!=(const c_IndexedKeyPathIterator& other_instance) {return !(*this == other_instance);};

		c_IndexedKeyPathIterator& operator++() {++m_keys_iterator; ++m_indexes_iterator; return *this;}; // pre-fix. increment and return.
		const c_IndexedKeyPathIterator operator++(int) {c_IndexedKeyPathIterator pre_incremented_value(*this); ++(*this); return pre_incremented_value;}; // post-fix. Copy to temp, increment and return const temp = (prohibit (iter++)++).
	private:
		t_keys_iterator m_keys_iterator;
		t_indexes_iterator m_indexes_iterator;
	};

	class c_IndexedKeyPathConstIterator {
	public:
		typedef const c_IndexedKeyProxy reference; // a const proxy may not be used as lvalue.
		typedef boost::shared_ptr<reference> pointer;

		// const interator creatabale from borth const and un-const iterators
		c_IndexedKeyPathConstIterator(const t_keys_iterator& keys_iterator,const t_indexes_iterator& indexes_iterator) : m_keys_iterator(keys_iterator),m_indexes_iterator(indexes_iterator) {};
		c_IndexedKeyPathConstIterator(const t_keys_const_iterator& keys_iterator,const t_indexes_const_iterator& indexes_iterator) : m_keys_iterator(keys_iterator),m_indexes_iterator(indexes_iterator) {};
		reference operator*() const {return reference(const_cast<t_key&>(*m_keys_iterator),const_cast<t_index&>(*m_indexes_iterator));}; // proxy needs to be cerated with non-const refs as input. But write is still prohobited as proxy itself is const
		pointer operator->() const {return pointer(new reference(const_cast<t_key&>(*m_keys_iterator),const_cast<t_index&>(*m_indexes_iterator)));}; // proxy needs to be cerated with non-const refs as input. But write is still prohobited as proxy itself is const
		bool operator==(const c_IndexedKeyPathConstIterator& other_instance) {return (m_keys_iterator==other_instance.m_keys_iterator) && (m_indexes_iterator==other_instance.m_indexes_iterator);};
		bool operator!=(const c_IndexedKeyPathConstIterator& other_instance) {return !(*this == other_instance);};

		c_IndexedKeyPathConstIterator& operator++() {++m_keys_iterator; ++m_indexes_iterator; return *this;}; // pre-fix. increment and return.
		const c_IndexedKeyPathConstIterator operator++(int) {c_IndexedKeyPathConstIterator pre_incremented_value(*this); ++(*this); return pre_incremented_value;}; // post-fix. Copy to temp, increment and return const temp = (prohibit (iter++)++).

	private:
		t_keys_const_iterator m_keys_iterator;
		t_indexes_const_iterator m_indexes_iterator;
	};

	class c_IndexedKeyPath {
	public:
		c_IndexedKeyPath() : m_keys(),m_indexes() {};
		c_IndexedKeyPath operator+(const c_IndexedKey& node) {c_IndexedKeyPath result(*this);result.m_keys.push_back(node.key());result.m_indexes.push_back(node.index());return result;};
		void operator+=(const c_IndexedKey& node) {m_keys.push_back(node.key()); m_indexes.push_back(node.index());};

		bool operator<(const c_IndexedKeyPath& other_instance) const {return ((m_keys < other_instance.m_keys) || ((m_keys == other_instance.m_keys) && (m_indexes < other_instance.m_indexes)));};
		bool operator==(const c_IndexedKeyPath& other_instance) const {return ((m_keys == other_instance.m_keys) && (m_indexes == other_instance.m_indexes));};

		typedef c_IndexedKeyPathIterator iterator;
		iterator begin() {return iterator(m_keys.begin(),m_indexes.begin());};
		iterator end() {return iterator(m_keys.end(),m_indexes.end());};
		iterator::reference front() {return *begin();};

		typedef c_IndexedKeyPathConstIterator const_iterator;
		const_iterator begin() const {return const_iterator(m_keys.begin(),m_indexes.begin());};
		const_iterator end() const {return const_iterator(m_keys.end(),m_indexes.end());};
		const_iterator::reference front() const {return *begin();};

	private:
		std::vector<t_key> m_keys;
		std::vector<t_index> m_indexes;
	};


	c_IndexedKeyPath c_IndexedKey::operator+(const c_IndexedKey& other_instance) {
		c_IndexedKeyPath result;
		result += *this;
		result += other_instance;
		return result;
	}

	c_LogString toLogString(const c_IndexedKeyPath& path) {
		c_LogString result;
		bool isFirstLap = true;
		for (c_IndexedKeyPath::const_iterator iter = path.begin(); iter != path.end(); iter++) {
			if (isFirstLap) {
				isFirstLap = false;
			}
			else {
				result += _Asciic('.');
			}
			result += c_DataRepresentationFramework::intToHexString(iter->key());
			result += _Asciic(':');
			result += c_DataRepresentationFramework::intToDecimalString(iter->index());
		}
		return result;
	}

	void performTests() {
		// 0. Basic operations
		{
			c_IndexedKeyPath path; // default
			path += c_IndexedKey(0x01,0); // append node
			path = path + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0); // path+node = path
			LOG_DEVELOPMENT_TRACE(toLogString(path)); // "1:0.2:0.3:0.4:0"
			c_IndexedKeyPath path2 = c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0); // node + node = path

			const c_IndexedKeyPath path3(c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			const c_IndexedKeyPath path4(c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			if (path3 == path4) {
				c_LogString sMessage("Path ");
				sMessage += toLogString(path3);
				sMessage += _Asciisz(" IS EQUAL TO ");
				sMessage += toLogString(path4);
				LOG_DEVELOPMENT_TRACE(sMessage); // "17:0.2:0.3:0.4:0"
			}
		}

		// 1. non-const iterator
		{
			c_IndexedKeyPath path;
			path += c_IndexedKey(0x01,0);
			path = path + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0);
			LOG_DEVELOPMENT_TRACE(toLogString(path)); // "1:0.2:0.3:0.4:0"
			c_IndexedKey iKey(path.front());
			path.front() = c_IndexedKey(0x17,0);
			LOG_DEVELOPMENT_TRACE(toLogString(path)); // "17:0.2:0.3:0.4:0"

			iKey.key() = path.front().key();
			path.front().key() = ++iKey.key();
			LOG_DEVELOPMENT_TRACE(toLogString(path)); // "18:0.2:0.3:0.4:0"
		}

		// 2. const iterator
		{
			const c_IndexedKeyPath path(c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			LOG_DEVELOPMENT_TRACE(toLogString(path)); // "1:0.2:0.3:0.4:0"
			c_IndexedKey iKey(path.front());
//			path.front() = c_IndexedKey(0x17,0); // Not allowed. Const path
			iKey.key() = path.front().key();
//			path.front().key() = ++iKey.key(); // Not allowed. Const path
		}

		// Use with stl
		{
			const c_IndexedKeyPath path1(c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			const c_IndexedKeyPath path2(c_IndexedKey(0x01,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			std::map<c_IndexedKeyPath,std::string> key_map;
			key_map.insert(std::make_pair(path1,"The first key"));
			std::map<c_IndexedKeyPath,std::string>::iterator m_iter = key_map.find(path2);
			if ( m_iter != key_map.end()) { // Map uses only operator< (i.e equal if !(a<b) &&(b<a)))
				LOG_DEVELOPMENT_TRACE(toLogString(m_iter->first));
			}

			std::vector<c_IndexedKeyPath> path_vector;
			const c_IndexedKeyPath path3(c_IndexedKey(0x10,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			const c_IndexedKeyPath path4(c_IndexedKey(0x10,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,1));
			const c_IndexedKeyPath path5(c_IndexedKey(0x11,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));
			const c_IndexedKeyPath path6(c_IndexedKey(0x11,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,1));
			const c_IndexedKeyPath path7(c_IndexedKey(0x11,0) + c_IndexedKey(0x02,0) + c_IndexedKey(0x03,0) + c_IndexedKey(0x04,0));

			path_vector.push_back(path3);
			path_vector.push_back(path4);
			path_vector.push_back(path5);
			path_vector.push_back(path6);
			std::vector<c_IndexedKeyPath>::iterator v_iter = std::find(path_vector.begin(),path_vector.end(),path7);
			if (v_iter != path_vector.end()) {
				LOG_DEVELOPMENT_TRACE(toLogString(*v_iter));
			}
		}

		// 4. templetaized on key and index

	};

}

namespace oprime {

	enum e_NodeId {
		 eNodeId_Undefined
		 ,eNodeId_IceCream
		 ,eNodeId_Popstickle
		,eNodeId_Unknown
	};

	enum e_PathType {
		 ePathType_Undefined
		,ePathType_Unknown
	};

	template <class _StringRepresentation>
	class c_TestPathItemStringilizer {
	public:

		_StringRepresentation keyToString(const e_NodeId& key) {
			_StringRepresentation result;
			switch (key) {
			case eNodeId_Undefined:
				result += _Asciisz("Undefined");
			break;
			case eNodeId_IceCream:
				result += _Asciisz("IceCream");
			break;
			case eNodeId_Popstickle:
				result += _Asciisz("Popstickle");
			break;

			case eNodeId_Unknown:
				result += _Asciisz("Unknown");
			break;
			default:
				result += _Asciisz("??");
			}
			return result;
		}

		_StringRepresentation keyToString(const c_LogString& key) {
			return DataRepresentationFramework::toOtherString<_StringRepresentation>(key); // key is String type. Convert to required return string
		}

		_StringRepresentation indexToString(int index) {
			return c_DataRepresentationFramework::intToDecimalString(index);
		}

		_StringRepresentation typeToString(const e_PathType& type) {
			e_PathType result;
			switch (type) {
			case ePathType_Undefined:
				result = _Asciisz("Undefined");
			break;
			case ePathType_Unknown:
				result = _Asciisz("Unknown");
			break;
			default:
				result = _Asciisz("??");
			}
			return result;
		}
	};

//	template <class _StringRepresentation>
//	class c_TypedPathToStringVisitor {
//	public:
//		void visitType(const e_PathType& type) {
//			m_String += _Asciisz("[");
//			switch (type) {
//			case ePathType_Undefined:
//				m_String += _Asciisz("Undefined");
//			break;
//			case ePathType_Unknown:
//				m_String += _Asciisz("Unknown");
//			break;
//			default:
//				m_String += _Asciisz("??");
//				;
//			}
//			m_String += _Asciisz("]");
//		}
//
//		void visitNode(const e_NodeId& node) {
//			if (m_String.size() > 0) {
//				m_String += _Asciisz(".");
//			}
//			switch (node) {
//			case eNodeId_Undefined:
//				m_String += _Asciisz("Undefined");
//			break;
//			case eNodeId_IceCream:
//				m_String += _Asciisz("IceCream");
//			break;
//			case eNodeId_Popstickle:
//				m_String += _Asciisz("Popstickle");
//			break;
//
//			case eNodeId_Unknown:
//				m_String += _Asciisz("Unknown");
//			break;
//			default:
//				m_String += _Asciisz("??");
//				;
//			}
//		}
//
//		void visitNode(const c_IndexedKeyNode<e_NodeId>& node) {
//			this->visitNode(node.key());
//			m_String += _Asciisz(":");
//			m_String += c_DataRepresentationFramework::intToHexString(node.index());
//		}
//
//		_StringRepresentation toString() {return m_String;};
//
//	private:
//		_StringRepresentation m_String;
//	};

	template <class _Path>
	void performPathTests(const typename _Path::Node& node1,const typename _Path::Node& node2,const typename _Path::Node& node3,const typename _Path::Node& node4) {
		typedef _Path::Node _Node;

		typedef c_TestPathItemStringilizer<c_LogString> c_Stringilizer;
		c_Stringilizer testPathItemStringilizer;

		_Path path1;
		path1 += node1;
		path1 += node2;
		path1 += node3;
		path1 += node4;
		c_LogString sPath = path1.toString<c_LogString>();
		LOG_DEVELOPMENT_TRACE(path1.toString<c_LogString>());
		LOG_DEVELOPMENT_TRACE(path1.toString<c_LogString>(testPathItemStringilizer));
		_Path path2(_Path::fromString(sPath));
		LOG_DEVELOPMENT_TRACE(path2.toString<c_LogString>());

//		c_TypedPathToStringVisitor<c_LogString> pathToStringVisitor;
//		path1.visitAll(pathToStringVisitor);
//		LOG_DEVELOPMENT_TRACE(pathToStringVisitor.toString());

	}

	/**
	  * Performs test of path templates
	  */
	void testPaths() {
		typedef e_NodeId t_key;
//		typedef unsigned long t_key;
		typedef e_PathType t_type;

		typedef c_KeyPath<t_key> t_plain_path;
//		typedef c_IndexedKeyPath<t_key> t_indexed_path;
		typedef c_TypedKeyPath<t_plain_path,t_type> t_typed_plain_path;
//		typedef c_TypedKeyPath<t_indexed_path,t_type> t_typed_indexed_path;

		performPathTests<t_plain_path>(eNodeId_IceCream,eNodeId_Popstickle,eNodeId_Popstickle,eNodeId_IceCream);
//		performPathTests<t_typed_indexed_path>(eNodeId_IceCream,eNodeId_Popstickle,eNodeId_Popstickle,eNodeId_IceCream);

		typedef c_LogString t_sKey;
		typedef c_KeyPath<t_sKey> t_plain_string_path;
//		typedef c_IndexedKeyPath<t_sKey> t_indexed_string_path;
		typedef c_TypedKeyPath<t_plain_string_path,t_type> t_typed_plain_string_path;
//		typedef c_TypedKeyPath<t_indexed_string_path,t_type> t_typed_indexed_string_path;

		performPathTests<t_plain_string_path>(_Asciisz("IceCream"),_Asciisz("Popstickle"),_Asciisz("Popstickle"),_Asciisz("IceCream"));
//		performPathTests<t_typed_indexed_string_path>(_Asciisz("IceCream"),_Asciisz("Popstickle"),_Asciisz("Popstickle"),_Asciisz("IceCream"));

//		t_typed_indexed_path typed_path(ePathType_Undefined);
//		typed_path += 1;
//		typed_path += 2;
//		typed_path += 3;
//		typed_path += 4;
//		c_LogString sPath = typed_path.toString<c_LogString>();
//		LOG_DEVELOPMENT_TRACE(typed_path.toString<c_LogString>());
//		c_TypedKeyPath<t_indexed_path,int> typed_path2(c_TypedKeyPath<t_indexed_path,int>::fromString(sPath));
//		LOG_DEVELOPMENT_TRACE(typed_path2.toString<c_LogString>());
	}

}
#endif // __BCPLUSPLUS__

