/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef PathsFrameworkH
#define PathsFrameworkH
//---------------------------------------------------------------------------
 #ifdef __BCPLUSPLUS__
// RAD Studio XE compilation
//---------------------------------------------------------------------------
#include <vector>
#include "BusinessLogUnit.h"
#include "DataRepresentationFrameWork.h"
#include <SysUtils.hpp> // Exception
# pragma warn -8072 // Disable "suspicious pointer arithmetic". Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <boost/type_traits.hpp> // boost::true_type...
# pragma warn +8072 // Disable "suspicious pointer arithmetic". Seems to be a known Issue for  boost in Borland CPP 101112/KoH
#include <limits> // std::is_integer
//---------------------------------------------------------------------------

namespace oprime4 {

	void performTests();

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

/**
  * oprime namespace
  */
namespace oprime {

	/**
	  * The Key Path framework.
	  *
	  * We use the following names and concepts.
	  *
	  * A Key path is a path of keys to be used to identify (Be a key) to an artefact.
	  * One example of a key path is the directyory path to a file in a file system.
	  * But it may also be a a path to a data field in a composite data structure.
	  *
	  * Three types of paths are defined.
	  *
	  * 1. A Key path being a vector of keys or key nodes.
	  * 2. An Indexed key path where each key or key node is accomanied with an index.
	  * 3. A typed key path where the path also has a type ascociated with the path.
	  *
	  * As mentioned a Key path is a path of keys. And the framwork distinguish between
	  * three types (classes) of key types.
	  *
	  * 1. An integral key (An int, char etc...).
	  * 2. A String key type.
	  * 3. A wrapped key node. For example an indexed kley path is a path of keys wrapped with an index.
	  *
	  * In the code below the following identifiers are used as follows:
	  *
	  * + _Key: is asumed to refer to a key type that is not wrapped. _Key may then be an integral type
	  *         or a string type.
	  * + _Node: Is used for a path node that may be a _Key or a wrapped _Key.
	  *
	  */

	//---------------------------------------------------------------------------

	template <typename _Key>
	class c_WrappedKeyNode {
	public:
		typedef _Key t_key;
		explicit c_WrappedKeyNode(const _Key& key) : m_key(key) {};
		explicit c_WrappedKeyNode(const c_WrappedKeyNode& other_instance) : m_key(other_instance.m_key) {};
		explicit c_WrappedKeyNode(c_WrappedKeyNode&& other_instance) : m_key(std::move(other_instance.m_key)) {};
		const c_WrappedKeyNode& operator=(c_WrappedKeyNode other_instance) {std::swap(m_key,other_instance.m_key);return *this;};
		bool operator==(const c_WrappedKeyNode& other_instance) const {return m_key == other_instance.m_key;};
		_Key& key() {return m_key;};
		_Key const& key() const {return m_key;};
	protected:
		_Key m_key;
	private:
	};

	namespace detail {

		template <class _StringRepresentation>
		class c_DefaultPathItemStringilizer; // forward
	}

	//---------------------------------------------------------------------------
	/**
	  * Models a Key path with nodes of type _Node.
	  * _Node may be a _Key or a c_WrappedKey<_Key>.
	  * _Key may be 1) Integral (int, enum etc) or 2) String.
	  */
	template <typename _Node>
	class c_KeyPath : public std::vector<_Node> {
	private:
		typedef std::vector<_Node> _Base;
	public:

//		typedef typename _Node t_node;
		typedef typename _Node Node;

		/**
		  * Conveniant declaration of iterator to path tags
		  */
		typedef _Base::const_iterator const_iterator;

		/**
		  * Conveniant declaration of iterator to path tags
		  */
		typedef _Base::iterator iterator;

		/**
		  * Creates an empty path
		  */
		c_KeyPath()
			: _Base()
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy constructor
		  */
		c_KeyPath(const c_KeyPath& other_instance)
			:  _Base(other_instance)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move constructor
		  */
		c_KeyPath(c_KeyPath&& other_instance)
			:  _Base(std::move(other_instance))
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move from base vector
		  */
		c_KeyPath(_Base&& base_instance)
			:  _Base(std::move(base_instance))
		{

		}

		/**
		  * Constructs a keyPathNode path with provided keyPathNode node
		  */
		explicit c_KeyPath(const _Node& keyNode1)
			: _Base(1,keyNode1)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

// 121031, Replaced by path + node
//		/**
//		  * Path extension constructor path + tag
//		  */
//		c_KeyPath(const c_KeyPath& header_path,const _Node& tail_keyNode)
//			:  _Base(header_path)
//		{
//			#ifdef _LOG_METHOD_SCOPE_
//			LOG_METHOD_SCOPE;
//			#endif
//			this->push_back(tail_keyNode);
//		}

		/**
		  * Path extension constructor tag + path
		  */
		c_KeyPath(const _Node& head_keyNode,const c_KeyPath& tail_path)
			:  _Base()
		{
			this->push_back(head_keyNode);
			this->insert(this->end(),tail_path.begin(),tail_path.end());
		}

		/**
		  * Construct from other path range.
		  * Note1: Must only be invoked with iterator, i.e c_KeyPath(iterator, iterator).
		  *       If you get a compiler error it may be that you tried c_KeyPath(type, type) where
		  *       type is NOT an iterator and there is no other match in c_KeyPath.
		  * Note2: Provided iterator must iterate over objects assignable to our objetcs.
		  *        That is _Node node = *iter must be defined for *iter.
		  */
		template <typename _Iterator>
		c_KeyPath(_Iterator _begin,_Iterator _end)
			:  _Base(_begin,_end)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Destructor
		  */
		virtual ~c_KeyPath()
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy Asignment
		  */
		c_KeyPath& operator=(c_KeyPath other_instance) {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			this->swap(other_instance);
			return *this;
		}

		/**
		  * +=node
		  */
		c_KeyPath& operator+=(const _Node& keyNode) {
			this->push_back(keyNode);
			return *this;
		}

		/**
		  * path + node
		  */
		c_KeyPath operator+(const _Node& keyNode) {
			c_KeyPath result(*this); // copy
			result += keyNode;
			return result;
		}

		/**
		  * Returns true if all our nodes matches corresponding nodes in other path.
		  * _Node must implement the operator!=
		  */
		bool isEqualPath(const c_KeyPath& other_instance) const {
			bool result = true; // Default;
			if (this->size() == other_instance.size()) {
				const_iterator this_iter = this->begin();
				const_iterator other_iter = other_instance.begin();

				while (this_iter != this->end()) {
					if (*this_iter != *other_iter) {
						result = false;
						break;
					}
					this_iter++;
					other_iter++;
				}
			}
			else {
				// Not of equal length! Can't be equal
				result = false;
			}

			#ifdef _LOG_METHOD_SCOPE_
			// Debug trace
			c_LogString sMessage(__FUNCTION__" ");
			sMessage += this->toDottedHexValueString();
			if (result == true) {
				sMessage += _UTF8sz(" == ");
			}
			else {
				sMessage += _UTF8sz(" <> ");
			}
			sMessage += other_instance.toDottedHexValueString();
			LOG_DEVELOPMENT_TRACE(sMessage);
			// End Debug trace
			#endif

			return result;
		}

		/**
		  * Returns the parent path to this tag path.
		  * It is this path with the last tag removed.
		  */
		c_KeyPath getParentPath() const {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			return c_KeyPath<_Node>(this->begin(),this->end()-1); // Will throw if we are empty
		}

		/**
		  * Returns the path with the first tag (header tag) omitted
		  */
		c_KeyPath getTailPath() const {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			return c_KeyPath<_Node>(this->begin()+1,this->end()); // Will throw if we are empty
		}

		template <typename _StringRepresentation>
		_StringRepresentation toString() const {
			detail::c_DefaultPathToStringVisitor<_StringRepresentation> toStringVisitor;
			this->visitAll(toStringVisitor);
			return toStringVisitor.toString();
		}

		template <typename _StringRepresentation, class _Stringilizer>
		_StringRepresentation toString(const _Stringilizer& stringilizer) const {
			detail::c_DefaultPathToStringVisitor<_StringRepresentation,_Stringilizer> toStringVisitor(stringilizer);
			this->visitAll(toStringVisitor);
			return toStringVisitor.toString();
		}

		/**
		  * Note: _StringRepresentation has to provide
		  *       _StringRepresentation::const_iterator.
		  *       Providing char* or simmilar causes compiler error.
		  */
		template <typename _StringRepresentation>
		static c_KeyPath fromString(const _StringRepresentation& sPath) {
			/**
			  * Check if we are calling with a too simple string type.
			  * We expect a string class. We do not accept char* or char* wrapper.
			  * boost::has_trivial_destructor seems like a good chice.
			  * NOTE: If you get a compiler error here you are probably not providing
			  * a string class for _StringRepresentation;
			  */
			BOOST_STATIC_ASSERT(! boost::has_trivial_destructor<_StringRepresentation>::value );
			return c_KeyPath<_Node>(tokeyPath<c_KeyPath,_StringRepresentation>(sPath));
		}

		template <typename _Visitor>
		void visitAll(_Visitor& visitor) const {
			for (const_iterator iter = this->begin(); iter != this->end(); ++iter) {
				visitor.visitNode(*iter);
			}
        }

	protected:
		/**
		  * STL swap
		  */
		void swap(c_KeyPath& other_instance) {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			_Base::swap(other_instance);
		}

	private:
	};

	//---------------------------------------------------------------------------
	/**
	  * Models an indexed key of type _Key.
	  * c_IndexedKeyNode is a wrapped Key with an index.
	  */
	template <typename _Key>
	class c_IndexedKeyNode : public c_WrappedKeyNode<_Key> {
	private:
		typedef c_WrappedKeyNode<_Key> _Base;
	public:

		/**
		  * Creates an indexed tag node using provided tag value, cardinality and start index.
		  * Not explicit = allow implicit cast to c_IndexedKeyNode from key.
		  */
		c_IndexedKeyNode(const _Key& key,unsigned int index = 0)
			:  _Base(key)
			  ,m_index(index)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy constructor
		  */
		explicit c_IndexedKeyNode(const c_IndexedKeyNode& other_instance)
			:  _Base(other_instance.m_key)
			  ,m_index(other_instance.m_index)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move constructor
		  */
		explicit c_IndexedKeyNode(c_IndexedKeyNode&& other_instance)
			:  _Base(std::move(other_instance.m_key))
			  ,m_index(std::move(other_instance.m_index))
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Asignment operator
		  */
		c_IndexedKeyNode& operator=(c_IndexedKeyNode other_instance) {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			this->swap(other_instance);
			return *this;
		}

		/**
		  * Asignment operator to base key. Will set default index
		  */
		c_IndexedKeyNode& operator=(const _Key& key) {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			this->key() = key;
			return *this;
		}

		/**
		  * Returns our keyPathNode node index
		  */
		const unsigned int& index() const {
			return this->m_index;
		}

		/**
		  * Returns our keyPathNode node index
		  */
		unsigned int& index() {
			return this->m_index;
		}

		/**
		  * Sets the index of this keyNode
		  */
		void setIndex(unsigned int index) {
			this->m_index = index;
		}

		/**
		  * Returns true of we equeal to other instance both in keyPathNode and index
		  */
		bool operator==(const c_IndexedKeyNode& other_instance) const {
			bool result = (     (this->key() == other_instance.key())
							 && (this->index() == other_instance.index()));
			return result;
		}

		bool operator!=(const c_IndexedKeyNode& other_instance) const {
			return !(*this==other_instance);
		}

		template <typename _StringRepresentation>
		_StringRepresentation toString() const {
			_StringRepresentation result(detail::nodeToString<_Key,_StringRepresentation>(this->key()));
			result += _Asciic(':');
			result += DataRepresentationFramework::toOtherString<_StringRepresentation>(c_DataRepresentationFramework::intToDecimalString(this->index()));
			return result;
		}

		template <typename _StringRepresentation>
		static c_IndexedKeyNode fromString(const _StringRepresentation& sNode) {
			// Split on ":"
			_StringRepresentation::const_iterator startIter = sNode.begin();
			_StringRepresentation::const_iterator endIter = std::find(startIter,sNode.end(),':');
			_StringRepresentation sKey(startIter,endIter);
			_Key key = c_DataRepresentationFramework::intValueOfHexString(sKey);
			_StringRepresentation sIndex(endIter+1,sNode.end());
			int index = c_DataRepresentationFramework::intValueOfDecimalString(sIndex);
			c_IndexedKeyNode result(key,index);
			return result;
		}

		template <class _Visitor>
		void accept(_Visitor& visitor) const {
			visitor.visitNode(this->key());
			visitor.visitIndex(this->index());
		}

	protected:
		/**
		  * STL Swap
		  */
		void swap(c_IndexedKeyNode& other_instance) {
			std::swap(this->m_key,other_instance.m_key);
			std::swap(this->m_index,other_instance.m_index);
		}

	private:

		/**
		  * Private storage of current keyPathNode index
		  */
		unsigned int m_index;

	};

	/**
	  * Models a typed keypath that extends path _Base
	  * with Type _PathType
	  */
	template <class _Base,class _Type>
	class c_TypedKeyPath
		: public _Base
	{
	private:
//		typedef typename _Base::Key _Key;
		typedef typename _Base::Node _Node;

	public:

		typedef typename _Base::Node Node;

		/**
		  * Constructs an empty instance tag path of provided type
		  */
		explicit c_TypedKeyPath(const _Type& composite_type = _Type(0))
			:  _Base()
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

// 121031, replaced with c_TypedKeyPath(type,node). Works for all nodes
//         thta may be implicit constructed from key.
//		/**
//		  * Constructs an instance tag path of provided type and node with provided key.
//		  */
//		explicit c_TypedKeyPath(const _Type& composite_type,const _Key& key1)
//			:  _Base(_Node(key1))
//			  ,m_composite_type(composite_type)
//		{
//			#ifdef _LOG_METHOD_SCOPE_
//			LOG_METHOD_SCOPE;
//			#endif
//		}

		/**
		  * Constructs an instance tag path of provided type and node with provided node.
		  */
		c_TypedKeyPath(const _Type& composite_type,const _Node& node)
			:  _Base(node)
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy constructor
		  */
		explicit c_TypedKeyPath(const c_TypedKeyPath& other_instance)
			:  _Base(other_instance)
			  ,m_composite_type(other_instance.m_composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move constructor
		  */
		explicit c_TypedKeyPath(c_TypedKeyPath&& other_instance)
			:  _Base(std::move(other_instance))
			  ,m_composite_type(other_instance.m_composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy construct from base class instance
		  */
		explicit c_TypedKeyPath(const _Type& composite_type,const _Base& base)
			:  _Base(base)
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move construct from base class instance
		  */
		explicit c_TypedKeyPath(const _Type& composite_type,_Base&& base)
			:  _Base(std::move(base))
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Copy construct but change type
		  */
		explicit c_TypedKeyPath(const _Type& composite_type,const c_TypedKeyPath& other_instance)
			:  _Base(other_instance)
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Move construct + change type
		  */
		explicit c_TypedKeyPath(const _Type& composite_type,c_TypedKeyPath&& other_instance)
			:  _Base(std::move(other_instance))
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Construct from other path range.
		  * Note1: Must only be invoked with iterator, i.e c_TypedKeyPath(iterator, iterator).
		  *       If you get a compiler error it may be that you tried c_TypedKeyPath(type, type) where
		  *       type is NOT an iterator and there is no other match in c_TypedKeyPath.
		  * Note2: Provided iterator must iterate over objects assignable to our path nodes.
		  *        That is _Node node = *iter must be defined for _Node.
		  */
		template <typename _Iterator>
		c_TypedKeyPath(const _Type& composite_type, _Iterator _begin,_Iterator _end)
			:  _Base(_begin,_end)
			  ,m_composite_type(composite_type)
		{
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
		}

		/**
		  * Assignment to same
		  */
		c_TypedKeyPath& operator=(c_TypedKeyPath other_instance) {
			#ifdef _LOG_METHOD_SCOPE_
			LOG_METHOD_SCOPE;
			#endif
			this->swap(other_instance);
			return *this;
		}

		/**
		  * Append node operator
		  */
		c_TypedKeyPath& operator+=(const _Node& keyNode) {
			this->push_back(keyNode);
			return *this;
		}

		/**
		  * Path + node operator
		  */
		c_TypedKeyPath operator+(const _Node& keyNode) const {
			c_TypedKeyPath result(*this);
			result += keyNode;
			return result;
		}

		/**
		  * Returns the path to parent node
		  */
		c_TypedKeyPath getParentPath() const {
			c_TypedKeyPath result(this->m_composite_type,_Base::getParentPath());
			return result;
		}

		/**
		  * Returns the path with the first tag (header tag) omitted
		  */
		c_TypedKeyPath getTailPath() const {
			c_TypedKeyPath result(this->m_composite_type,_Base::getTailPath());
			return result;
		}

		/**
		  * c_TypedKeyPath<T> == T
		  * That is, type disregarded
		  */
		bool isEquealToUntypedPath(const _Base& untyped_path) const {
			bool result = (_Base::isEqualPath(untyped_path));
			return result;
		}

		/**
		  * c_TypedKeyPath<T> == c_TypedKeyPath<T>
		  * That is equal in path and type
		  */
		bool isEquealToPathAndType(const c_TypedKeyPath& other_instance) const {
			bool result = false;
			if (this->m_composite_type == other_instance.m_composite_type) {
				result = isEquealToUntypedPath(other_instance);
			}
			return result;
		}

		/**
		  * Returns a string describing this instance path of the form
		  * <node caption>.<node caption>
		  * where node caption is <hex value>:<decimal index>
		  */
		c_DataRepresentationFramework::c_AsciiString toDottedHexValueString() const {
			return this->toString<c_DataRepresentationFramework::c_AsciiString>();
		}

		template <typename _StringRepresentation>
		_StringRepresentation toString() const {
			detail::c_DefaultPathToStringVisitor<_StringRepresentation> toStringVisitor;
			this->visitAll(toStringVisitor);
			return toStringVisitor.toString();
		}

		/**
		  * Note: _StringRepresentation has to provide
		  *       _StringRepresentation::const_iterator.
		  *       Providing char* or simmilar causes compiler error.
		  */
		template <typename _StringRepresentation>
		static c_TypedKeyPath fromString(const _StringRepresentation& sPath) {
			// 1.Get hold of our type
			_StringRepresentation::const_iterator startIter = sPath.begin()+1; // past '['
			_StringRepresentation::const_iterator endIter = std::find(startIter,sPath.end(),']');
			_StringRepresentation sType(startIter,endIter);
			_Type type = c_DataRepresentationFramework::intValueOfHexString(sType);
			// 2. Create path from string nodes
			c_TypedKeyPath result(type,_Base::fromString(_StringRepresentation(endIter+1,sPath.end())));
			return result;
		}

		/**
		  * Returns the composite type of which this is a path.
		  */
		const _Type& compositeType() const {
			return this->m_composite_type;
		}

		/**
		  * Sets the composite type of this path
		  */
		void setcompositeType(const _Type& composite_type) {
			this->m_composite_type = composite_type;
		}

		template <typename _Visitor>
		void visitAll(_Visitor& visitor) const {
			visitor.visitType(this->compositeType());
			_Base::visitAll(visitor);
		}

	protected:

		/**
		  * STL swap
		  */
		void swap(c_TypedKeyPath& other_instance) {
			_Base::swap(other_instance);
			std::swap(this->m_composite_type,other_instance.m_composite_type);
		}

		/**
		  * Move swap
		  */
		void swap(c_TypedKeyPath&& other_instance) {
			_Base::swap(std::move(other_instance));
			this->m_composite_type = std::move(other_instance.m_composite_type);
		}

	private:
		/**
		  * Private storage of message type this may be a path into
		  */
		_Type m_composite_type;

	};

	//---------------------------------------------------------------------------
	// Path to string section
	//---------------------------------------------------------------------------

	/**
	  * Detail namespace to hide template overloads based on provided type
	  */
	namespace detail {

//		//---------------------------------------------------------------------------
//		/**
//		  * General NodeToStringTrait template. Only specialized templates
//		  * is exptected to be used. This one is needed for the compiler to have
//		  * something to specialize.
//		  */
//		template <typename _Node, typename _StringRepresentation,bool, bool>
//		struct NodeToStringTrait {}; // An error if instanciated
//
//		//---------------------------------------------------------------------------
//		/**
//		  * Specialized NodeToStringTrait template for _Node
//		  * asumed to be a key of integral type
//		  */
//		template <typename _Node,typename _StringRepresentation>
//		struct NodeToStringTrait<_Node,_StringRepresentation,true,false> {
//			static _StringRepresentation nodeToString(const _Node& node) {
//				// Interpret the integral type as an hex digit string
//				return DataRepresentationFramework::toOtherString<_StringRepresentation>(c_DataRepresentationFramework::intToHexString(node));
//			}
//		};
//
//		//---------------------------------------------------------------------------
//		/**
//		  * Specialized NodeToStringTrait template for _Node
//		  * asumed to be a string class
//		  */
//		template <typename _Node,typename _StringRepresentation>
//		struct NodeToStringTrait<_Node,_StringRepresentation, false, true> {
//			static _StringRepresentation nodeToString(const _Node& node) {
//				/**
//				  * Return the string node converted to the required return string type
//				  */
//				return DataRepresentationFramework::toOtherString<_StringRepresentation>(node);
//			}
//		};
//
//		//---------------------------------------------------------------------------
//		/**
//		  * Specialized NodeToStringTrait template for _Node
//		  * asumed to be a wrapped key node.
//		  * The wrapped key must be defined by member type _Node::t_key
//		  * and the value of the wrapped key must be _Node::key()
//		  */
//		template <typename _Node,typename _StringRepresentation>
//		struct NodeToStringTrait<_Node,_StringRepresentation, false, false> {
//			static _StringRepresentation nodeToString(const _Node& node) {
//				// The node is asumed to be a wrapped node. Use the
//				// toString method defined by the wrapper.
//				// Note: If you get a compiler error here it may be because
//				// the wrapper you are providing does not have a const toString method defined.
//				return node.toString<_StringRepresentation>();
//			}
//		};
//
//		template <typename _Node,typename _StringRepresentation>
//		_StringRepresentation nodeToString(const _Node& node) {
//			// delegate to specilization that is appropriate for provided _KeyPathNode.
//			/**
//			  * so what happens here? Well, we use the template matching mechanism to find a
//			  * match for template NodeToStringTrait struct. Then we use the matched struct
//			  * member method to convert the node to required string.
//			  * The template has four parameters. The first and second are the the type of the node
//			  * and the required returned string type.
//			  * Then follows two boolean value parameters. They are used to specialize on two aspects
//			  * of the provided node type. The first boolean is set to true or false depending
//			  * on if provided node type is integral type or not. (An integral type is an int, enum, long etc...)
//			  * The second boolean is used to determine if the provided node type is a string class or not.
//			  * We use pre-defined templates in the boost namespace to map these aspects
//			  * to a booelan value type.
//			  */
//			return detail::NodeToStringTrait<
//				 _Node
//				,_StringRepresentation
//				,boost::is_integral<_Node>::value || boost::is_enum<_Node>::value
//				,(     (boost::is_base_of<std::basic_string<char>,_Node>::value)
//					|| (boost::is_base_of<std::basic_string<wchar_t>,_Node>::value)
//					|| (boost::is_base_of<std::basic_string<char32_t>,_Node>::value))>::nodeToString(node);
//		}
	}

	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------


	namespace detail {

		struct is_integral_type {};
		struct is_string_type {};

		template <bool,bool>
		struct KeyTypeTrait {}; // General trait never used. See specialized below.

		template <>
		struct KeyTypeTrait<true,false> {
			typedef is_integral_type type;
			static type value() {return type();}; // returns is_integral_type
		};

		template <>
		struct KeyTypeTrait<false,true> {
			typedef is_string_type type;
			static type value() {return type();}; // returns is_string_type
		};

		template <typename _Key>
		struct KeyType : public KeyTypeTrait< // Inherit from KeyTypeTrait<true,false> or KeyTypeTrait<false,true>
			 boost::is_integral<_Key>::value || boost::is_enum<_Key>::value
			,(     (boost::is_base_of<std::basic_string<char>,_Key>::value)
				|| (boost::is_base_of<std::basic_string<wchar_t>,_Key>::value)
				|| (boost::is_base_of<std::basic_string<char32_t>,_Key>::value))>
		{}; // Base class value() will return is_integral_type or is_string_type depending on matched trait.

		/**
		  * Convert
		  * + ints and enums key nodes ==> hex-string
		  * + String node ==> String
		  */
		template <class _StringRepresentation>
		class c_DefaultPathItemStringilizer {
		public:

			template <typename _Key>
			_StringRepresentation keyToString(const _Key& key) {
//				return detail::nodeToString<_Key,_StringRepresentation>(key);
				return this->keyToString(key,KeyType<_Key>::value()); // Call keyToString(key,is_integral_type) or keyToString(key,is_string_type)
			}

			_StringRepresentation indexToString(int index) {
				return c_DataRepresentationFramework::intToDecimalString(index);
			}

			template <typename _Type>
			_StringRepresentation typeToString(const _Type& type) {
				return c_DataRepresentationFramework::intToHexString(type);
			}
		private:

			template <typename _Key>
			_StringRepresentation keyToString(const _Key& key,is_integral_type dummy) {
				return c_DataRepresentationFramework::intToHexString(key); // Key is integral type, return hex-string
			}

			template <typename _Key>
			_StringRepresentation keyToString(const _Key& key,is_string_type dummy) {
				return DataRepresentationFramework::toOtherString<_StringRepresentation>(key); // key is String type. Convert to required return string
			}

		};

//		template <class _StringRepresentation,class _PathItemStringilizer = c_DefaultPathItemStringilizer<_StringRepresentation> >
//		class c_DefaultPathToStringVisitor {
//		public:
//
//			c_DefaultPathToStringVisitor(const _PathItemStringilizer& pathItemStringilizer = _PathItemStringilizer()) : m_pathItemStringilizer(pathItemStringilizer) {};
//
//			void reset() {m_String.clear();}
//
//			template <typename _Node>
//			void visitNode(const _Node& node) {
//				if (m_String.size() > 0) {
//					m_String += _Asciic('.');
//				}
//				m_String += m_pathItemStringilizer.nodeToString(node);
//			}
//
//			template <typename _Type>
//			void visitType(const _Type& type) {
//				m_String += _Asciic('[');
//				m_String += m_pathItemStringilizer.typeToString(type);
//				m_String += _Asciic(']');
//			}
//
//			_StringRepresentation toString() {return m_String;}
//
//		private:
//			_StringRepresentation m_String;
//			_PathItemStringilizer m_pathItemStringilizer;
//		};

		struct is_unwrapped_type {}; // type used to identify unwrapped node
		struct is_wrapped_type {}; // Type used to identify wrapped node

		// Is unwrapped trait
		template <bool>
		struct is_unwrapped_trait {};

		// Is unwrapped
		template <>
		struct is_unwrapped_trait<true> {
			typedef is_unwrapped_type type;
			static type value() {return type();};
		};

		// Is not unwrapped
		template <>
		struct is_unwrapped_trait<false> {
			typedef is_wrapped_type type;
			static type value() {return type();};
		};

		template <typename _Node>
		struct is_unwrapped : public is_unwrapped_trait<
			 (    (boost::is_integral<_Node>::value)
			   || (boost::is_enum<_Node>::value)
			   || (    (boost::is_base_of<std::basic_string<char>,_Node>::value)
					|| (boost::is_base_of<std::basic_string<wchar_t>,_Node>::value)
					|| (boost::is_base_of<std::basic_string<char32_t>,_Node>::value)))
		> {
		};

		/**
		  * Path visitor that creates a string representation of the path using provided "stringilizer".
		  * If not stringilizer is provided a default one is used.
		  */
		template <class _StringRepresentation,class _PathItemStringilizer = c_DefaultPathItemStringilizer<_StringRepresentation> >
		class c_DefaultPathToStringVisitor {
		private:
		public:

			c_DefaultPathToStringVisitor(const _PathItemStringilizer& pathItemStringilizer = _PathItemStringilizer()) : m_pathItemStringilizer(pathItemStringilizer) {};

			void reset() {m_String.clear();}

			template <typename _Node>
			void visitNode(const _Node& node) {
				this->visit(node,is_unwrapped<_Node>::value());
			}

			void visitIndex(int index) {
				m_String += _Asciic(':');
				m_String += m_pathItemStringilizer.indexToString(index);
			}

			template <typename _Type>
			void visitType(const _Type& type) {
				m_String += _Asciic('[');
				m_String += m_pathItemStringilizer.typeToString(type);
				m_String += _Asciic(']');
			}

			_StringRepresentation toString() {return m_String;}

		private:
			_StringRepresentation m_String;
			_PathItemStringilizer m_pathItemStringilizer;

			/**
			  * Visit an unwrapped node.
			  */

			template <typename _Key>
			void visit(const _Key& key, is_unwrapped_type dummy) {
				if (m_String.size() > 0) {
					m_String += _Asciic('.');
				}
				m_String += m_pathItemStringilizer.keyToString(key);
			}

			/**
			  * Visit a wrapped node.
			  */
			template <typename _Node>
			void visit(const _Node& node, is_wrapped_type dummy) {
				node.accept(*this);
			}

		};

	}

	//---------------------------------------------------------------------------
	// String to path section
	//---------------------------------------------------------------------------

	/**
	  * Detail namespace to hide template overloads based on provided type
	  */
	namespace detail {

		//---------------------------------------------------------------------------
		/**
		  * General NodeToStringTrait template
		  */
		template <typename _Node, typename _StringRepresentation,bool, bool>
		struct StringToNodeTrait {}; // An error if instanciated

		/**
		  * Specialized NodeToStringTrait template for _Node
		  * asumed to be a key of integral type
		  */
		template <typename _Node,typename _StringRepresentation>
		struct StringToNodeTrait<_Node,_StringRepresentation,true,false> {
			static _Node stringToNode(const _StringRepresentation& sNode) {
				// Interpret the integral type as an hex digit string
				return c_DataRepresentationFramework::intValueOfHexString(sNode);
			}
		};

		//---------------------------------------------------------------------------
		/**
		  * Specialized NodeToStringTrait template for _Node
		  * asumed to be a string class
		  */
		template <typename _Node,typename _StringRepresentation>
		struct StringToNodeTrait<_Node,_StringRepresentation, false, true> {
			static _Node stringToNode(const _StringRepresentation& sNode) {
				/**
				  * Return the string node converted to the required return string type.
				  * Note: _Node is the type of the String node so we
				  * convert to string type _Node.
				  */
				return DataRepresentationFramework::toOtherString<_Node>(sNode);
			}
		};

		//---------------------------------------------------------------------------
		/**
		  * Specialized NodeToStringTrait template for _Node
		  * asumed to be a wrapped key node.
		  * The wrapped key must be defined by member type _Node::t_key
		  * and the value of the wrapped key must be _Node::key()
		  */
		template <typename _Node,typename _StringRepresentation>
		struct StringToNodeTrait<_Node,_StringRepresentation,false, false> {
			static _Node stringToNode(const _StringRepresentation& sNode) {
				/**
				  * We are to create a wrapped key node. Use the fromString
				  * template defined by the wrapper class.
				  * Note: If you get a compiler error here it is because the _Node
				  * provided here does not have a static fromString<> defined.
				  */
				return _Node::fromString<_StringRepresentation>(sNode);
			}
		};

	}

	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------

	template <typename _Node,typename _StringRepresentation>
	_Node stringToNode(const _StringRepresentation& sNode) {
		// delegate to specilization that is appropriate for provided _Node.
		/**
		  * so what happens here? Well, we use the template matching mechanism to find a
		  * match for template StringToNodeTrait struct. Then we use the matched struct
		  * member method to convert the provided string to required node.
		  * The template has four parameters. The first and second are the the type of the node
		  * and the type of the string.
		  * Then follows two boolean value parameters. They are used to specialize on two aspects
		  * of the provided node type. The first boolean is set to true or false depending
		  * on if provided node type is integral type or not. (An integral type is an int, enum, long etc...)
		  * The second boolean is used to determine if the provided node type is a string class os not.
		  * We use pre-defined templates in the boost namespace to map the aspects
		  * to a booelan value type.
		  */
		return detail::StringToNodeTrait<
			 _Node
			,_StringRepresentation
			,boost::is_integral<_Node>::value || boost::is_enum<_Node>::value
			,(     (boost::is_base_of<std::basic_string<char>,_Node>::value)
				|| (boost::is_base_of<std::basic_string<wchar_t>,_Node>::value)
				|| (boost::is_base_of<std::basic_string<char32_t>,_Node>::value))>::stringToNode(sNode);
	}

	//---------------------------------------------------------------------------
	/**
	  * Template toKeyPath that takes a path in provided string of type _StringRepresentation
	  * and returns a std::vector<T>.
	  * Note: _StringRepresentation has to provide
	  *       _StringRepresentation::const_iterator.
	  *       _StringRepresentation = char* or simmilar causes compiler error.
	  */
	template <class _Node,class _StringRepresentation>
	std::vector<_Node> stringToNodeVector(const _StringRepresentation& sPath) {
		std::vector<_Node> result;

		try {
			// Find the string up to the next '.' or end of string
			// Note: If you get a compiler error here it is because the _StringRepresentation
			// you have provided does not have an iterator defined. See above.
			_StringRepresentation::const_iterator startIter = sPath.begin();
			_StringRepresentation::const_iterator endIter = std::find(startIter,sPath.end(),'.');
			while (startIter != endIter) {
				_StringRepresentation sNode(startIter,endIter);

				// Convert to keyPathNode and push into path
				// Note: If you get a comiler error here it may be that your keyPathNode type T
				// has no mathing stringToNode() method that creates a T from a string S.
				result.push_back(stringToNode<_Node,_StringRepresentation>(sNode));

				// Move start to end
				if (endIter != sPath.end()) {
					startIter = endIter+1;
				}
				else {
					startIter = endIter;
				}
				endIter = std::find(startIter,sPath.end(),'.');
			}
		}
		catch (std::exception& e) {
			c_LogString sMessage(__FUNCTION__"  failed. sPath = ");
			sMessage += sPath;
			sMessage += _UTF8sz(". Exception=");
			sMessage += _UTF8sz(e.what());
			LOG_DESIGN_INSUFFICIENCY(sMessage);
		}
		catch (Exception& e) {
			c_LogString sMessage(__FUNCTION__"  failed. sPath = ");
			sMessage += sPath;
			sMessage += _UTF8sz(". Exception=");
			sMessage += toLogString(e.Message.c_str());
			LOG_DESIGN_INSUFFICIENCY(sMessage);
		}
		catch (...) {
			c_LogString sMessage(__FUNCTION__"  failed. sPath = ");
			sMessage += sPath;
			sMessage += _UTF8sz(". Anonymous excpetion cought.");
			LOG_DESIGN_INSUFFICIENCY(sMessage);
		}

		return result;
	}

	//---------------------------------------------------------------------------
	template <typename _Path,typename _StringRepresentation>
	_Path tokeyPath(const _StringRepresentation& sPath) {
		return _Path(stringToNodeVector<_Path::Node,_StringRepresentation>(sPath));
	}

	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------

	/**
	  * Performs test of path templates
	  */
	void testPaths();

}

/**
  * Deprecated path classes. To be replaced by
  * opath classes
  */
namespace deprecated {

	/**
	  * Template class that models a path of nodes
	  */
	template<class T>
	class c_NodePath2 : public std::vector<T> {
	public:
		/**
		  * Default constructor.
		  * Needed to participtate as values in stl containers.
		  */
		explicit c_NodePath2(const c_DataRepresentationFramework::c_AsciiString& sDottedNodePath=_Asciisz(""))
			: std::vector<T>()
		{
			this->buildNodesFromPathString(sDottedNodePath);
		}

		/**
		  * Constructor of path of one to five tags of specified type
		  * and supplied root tag as the first tag in the path.
		  * The message type may be used by user of path if
		  * action depends on into what type of message the path referrs
		  */
		explicit c_NodePath2(const T& node1)
			: std::vector<T>()
		{
			this->push_back(node1);
		}

		explicit c_NodePath2(unsigned long node_value1)
			: std::vector<T>()
		{
			// Create an instance of T from unsigned long value.
			// T must support a constructor taking an unsigned long.
			// If you get a compiler error here it is because the T yous are using does not :-).
			this->push_back(T(node_value1));
		}

		c_NodePath2(const T& node1,const T& node2)
			: std::vector<T>()
		{
			this->push_back(node1);
			this->push_back(node2);

		}

		c_NodePath2(const T& node1,const T& node2,const T& node3)
			: std::vector<T>()
		{
			this->push_back(node1);
			this->push_back(node2);
			this->push_back(node3);
		}

		c_NodePath2(const T& node1,const T& node2,const T& node3,const T& node4)
			: std::vector<T>()
		{
			this->push_back(node1);
			this->push_back(node2);
			this->push_back(node3);
			this->push_back(node4);
		}

		c_NodePath2(const T& node1,const T& node2,const T& node3,const T& node4,const T& node5)
			: std::vector<T>()
		{
			this->push_back(node1);
			this->push_back(node2);
			this->push_back(node3);
			this->push_back(node4);
			this->push_back(node5);
		}

		/**
		  * Copy constructor
		  */
		c_NodePath2(const c_NodePath2& other_path)
			: std::vector<T>()
		{
			*this = other_path; // Use asignment operator
		}

		/**
		  * Path extension constructor path + tag
		  */
		c_NodePath2(const c_NodePath2& other_path,const T& node)
			: std::vector<T>()
		{
			*this = other_path; // Use asignment operator
			this->puch_back(node);
		}

		/**
		  * Path extension constructor tag + path
		  */
		c_NodePath2(const T& node,const c_NodePath2& node_path)
			: std::vector<T>()
		{
			this->puch_back(node);
			iterator iter = node_path.begin();
			while (iter != node_path.end()) {
				this->puch_back(*iter);
				iter++;
			}
		}

		/**
		  * Destructor
		  */
		virtual ~c_NodePath2() {

		}

		c_NodePath2& operator=(const c_NodePath2& node_path) {
			static_cast<std::vector<T>*>(this)->operator=(node_path);
		}

		c_NodePath2& operator=(const c_DataRepresentationFramework::c_AsciiString& sDottedNodePath) {
			*this = c_NodePath2<T>(sDottedNodePath); // use asignment operator
		}

		/**
		  * Returns true if provided path is equal to us,
		  * i.e all nodes in the path are the same values
		  * and the path is a path into the same message type.
		  */
		bool isEqualTo(const c_NodePath2& other_path) const {
			bool result=true; // default
			if (this->size() == other_path.size()) {
				// Could be equal. Is at least the same size
				for (int i = 0; i < this->size(); i++) {
					// Type T has to implement operator==().
					// If you get compiler error here it is because your
					// type T does not.
					if (this[i] == other_path[i]) {
						// Equal OK
					}
					else {
						result = false;
						break;
					}
				}
			}
			else {
				result = false;
			}
			return result;
		}

		/**
		  * Returns the parent path to this tag path.
		  * It is this path with the last tag removed.
		  */
		c_NodePath2 getParentPath() const {
			c_NodePath2 result = *this;
			if (this->size()>0) {
				result.insert(result.begin(),this->begin(),this->end()-1);
			}
			return result;
		}

		/**
		  * Returns the path with the first tag (header tag) omitted
		  */
		c_NodePath2 getTailPath() const {
			c_NodePath2 result = *this;
			if (this->size()>0) {
				result.insert(result.begin(),this->begin()+1,this->end());
			}
			return result;
		}

		/**
		  * Returns access to last node of this path
		  */
		T& getLastNode() {
			return this->back();
		}

		/**
		  * Returns const access to last node of this path
		  */
		const T& getLastNode() const {
			return this->back();
		}

		/**
		  * Creates atring of each node T string representation separated by '.'
		  */
		c_DataRepresentationFramework::c_AsciiString toDottedStringPath() const {
			c_DataRepresentationFramework::c_AsciiString result;
			iterator iter = this->begin();
			int count = 0;
			while (iter != this->end()) {
				if (count>0) {
					result += _Asciic('.'); // Add separator
				}
				// T has to implement a toString() method.
				// If you get a compiler error here it may be because
				// your type T does not.
				result +=  c_DataRepresentationFramework::toAsciiString(iter->toString());
				count++;
				iter++;
			}
			return result;
		}

		/**
		  * Returns the composite type of which this is a path.
		  * Also see the isEqueal... methods about when composite type
		  * is applied.
		  */
		unsigned long compositeType() const {
			return m_composite_type;
		}

		/**
		  * Sets the composite type of this path
		  */
		void setcompositeType(unsigned long composite_type) {
			m_composite_type = composite_type;
		}

		/**
		  * Conveniant declaration of iterator to path tags
		  */
		typedef std::vector<T>::const_iterator iterator;

	private:

		/**
		  * Private storage of message type this may be a path into
		  */
		unsigned long m_composite_type;

		/**
		  * Parses provided string path and creates nodes
		  * from the node values.
		  */
		void buildNodesFromPathString(const c_DataRepresentationFramework::c_AsciiString& sDottedNodePath) {
			try {
				// Find the string up to the next '.' or end of string
				// int startIndex = 0;
				// int endIndex = sDottedNodePath.find('.',startIndex)
				c_DataRepresentationFramework::c_AsciiString::const_iterator startIter = sDottedNodePath.begin();
				c_DataRepresentationFramework::c_AsciiString::const_iterator endIter = std::find(startIter,sDottedNodePath.end(),'.');
				while (startIter != endIter) {
					c_DataRepresentationFramework::c_AsciiString sNode(startIter,endIter);

					// Create a new node T from provided caption.
					// Node that the type T has to have a constructor tacing a c_DataRepresentationFramework::c_AsciiString as parameter.
					// If you get a compiler error here it is because the T you uses does not.
					this->push_back(T(sNode));

					// Move start to end
					if (endIter != sDottedNodePath.end()) {
						startIter = endIter+1;
					}
					else {
						startIter = endIter;
					}
					endIter = std::find(startIter,sDottedNodePath.end(),'.');
				}
			}
			catch (std::exception& e) {
				c_LogString sMessage = _UTF8sz("c_DefinitionTagPath::c_DefinitionTagPath(sDottedNodePath) failed. sDottedNodePath = ");
				sMessage += _Asciis(sDottedNodePath);
				sMessage += _UTF8sz(". Exception=");
				sMessage += _UTF8s(e.what());
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
			catch (Exception& e) {
				c_LogString sMessage = _UTF8sz("c_DefinitionTagPath::c_DefinitionTagPath(sDottedNodePath) failed. sDottedNodePath = ");
				sMessage += _Asciis(sDottedNodePath);
				sMessage += _UTF8sz(". Exception=");
				sMessage += toLogString(_UTF16sz(e.Message.c_str()));
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
			catch (...) {
				c_LogString sMessage = _UTF8sz("c_DefinitionTagPath::c_DefinitionTagPath failed. catch (...) clause activated. parameter sDottedNodePath = ");
				sMessage += _Asciis(sDottedNodePath);
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

	};

	/**
	  * Models a path node of type unsigned long
	  */
	class c_UnsignedLongNode2 {
	public:
		/**
		  * Creates an unsigned long node with provided value
		  */
		c_UnsignedLongNode2(unsigned long value=0)
			: m_value(value) {};

		/**
		  *
		  */
		explicit c_UnsignedLongNode2(const c_DataRepresentationFramework::c_AsciiString sValue)
			: m_value(LONG_MAX) {
			try {
				m_value = c_DataRepresentationFramework::intValueOfHexString(sValue);
				if (m_value == LONG_MAX) {
					// Failed. No allowed! Reserved for invalid node.
					c_LogString sMessage = _UTF8sz("Warning: constructor c_UnsignedLongNode2(");
					sMessage += sValue;
					sMessage += _UTF8sz(") invalid. Provided node value to large and reserved for invalid node value.");
					LOG_DESIGN_INSUFFICIENCY(sMessage);
				}
			} catch (...) {
				c_LogString sMessage = _UTF8sz("creator c_UnsignedLongNode2(");
				sMessage += sValue;
				sMessage += _UTF8sz(") failed. Will set this node to LONG_MAX");
				LOG_DESIGN_INSUFFICIENCY(sMessage);
			}
		}

		/**
		  * Equal operator
		  */
		bool operator==(const c_UnsignedLongNode2& other_node) const {
			return (this->m_value == other_node.m_value);
		}

		c_DataRepresentationFramework::c_AsciiString toString() const {
			return c_DataRepresentationFramework::intToHexString(m_value);
		}

		/**
		  * Returns the tag value of this node
		  */
		const unsigned long& getTagValue() const {
			return m_value;
		}

		/**
		  * Type used by user of T to know type of contained value
		  */
		typedef unsigned long node_value_type;

	private:
		unsigned long m_value;
	};

	/**
	  * Models a node with a string value
	  */
	template <class S>
	class c_StringNode2 : public S {
	public:
		/**
		  * Creates a string node with provided value
		  */
		c_StringNode2(const S& sCaption=_Asciisz(""))
			: S(sCaption)
		{

		}

		/**
		  * Equal operator
		  */
		bool operator==(const c_StringNode2& other_node) const {
			return (this->compare(other_node)==0);
		}

		S toString() const {
			return *this;
		}

		/**
		  * Returns the tag value of this node
		  */
		const S& getTagValue() const {
			return *this;
		}

		/**
		  * Type used by user of T to know type of contained value
		  */
		typedef S node_value_type;

	};


	typedef c_StringNode2<c_DataRepresentationFramework::c_UTF8String> c_CaptionNode2;
	typedef c_NodePath2<c_CaptionNode2> c_CaptionNodePath2;

	/**
	  * Helper class to describe cardinality of an instance
	  */
	class c_NodeCardinality {
	public:

		/**
		  * Constructor of helper class to describe cardinality of an instance
		  */
		c_NodeCardinality(int minNoInstances=1,int maxNrOfInstances=1);

		/**
		  * Returns the min number of instances of this cardinality
		  * In cardinality x..y this is the x value.
		  */
		int getMaxNrOfInstances() const;
		/**
		  * Returns the max number of instances of this cardinality
		  * In cardinality x..y this is the y value.
		  */
		int getMinNoInstances() const;

		/**
		  * Returns a readable caption describing this instance values.
		  */
		c_DataRepresentationFramework::c_AsciiString caption();

	private:
		/**
		  * Private storage of min number of instances of described value
		  * In cardinality x..y this is the x value.
		  */
		int m_minNoInstances;

		/**
		  * Private storage of max number of instances of described value.
		  * In cardinality x..y this is the y value.
		  */
		int m_maxNrOfInstances;
	};

	/**
	  * Models a tag value that also has an index to represent
	  * multipple occurenece of this node in a tag path.
	  */
	template <class T> class c_InstanceCountNode2 {
	public:

		/**
		  * Creates an indexed tag node using provided tag value, cardinality and start index
		  */
		c_InstanceCountNode2(const T& node_value,const c_NodeCardinality& cardinality = c_NodeCardinality(1,1),unsigned int startIndex = 0);

		/**
		  * Copy constructor
		  */
		c_InstanceCountNode2(const c_InstanceCountNode2& other_value);

		/**
		  * Asignment operator
		  */
		c_InstanceCountNode2& operator=(const c_InstanceCountNode2& other_value);

		/**
		  * Returns the tag value of this node
		  */
		const T& getTagValue() const;

		/**
		  * Returns the index of this node
		  */
		unsigned int getIndex() const;

		/**
		  * Sets the index of this node
		  */
		void setIndex(unsigned int index);

		/**
		  * Returns the cardinality of this indexed node
		  */
		c_NodeCardinality getCardinality() const;

		/**
		  * Increments the index if this node
		  */
		c_InstanceCountNode2& operator++();

		/**
		  * Returns true of this node is equeal to other node both in value and index
		  */
		bool operator==(const c_InstanceCountNode2& other_value) const;

		/**
		  * Returns true of this node is equeal to other tag value
		  */
		bool operator==(unsigned long tag_value) const;

		/**
		  * Will return a string dscribing this node value and index
		  * to be used for example in node tag path strings
		  */
		c_DataRepresentationFramework::c_AsciiString toNodeValueAndIndexString() const;

		/**
		  * Type used by user of T to know type of contained value
		  */
		typedef T node_value_type;

	private:
		/**
		  * Private storage of this node tag value
		  */
		unsigned long m_tagValue;

		/**
		  * Private storage of current index of this tag node
		  */
		unsigned int m_index;

		/**
		  * Private storage of the valid cardinality of this node
		  */
		c_NodeCardinality m_cardinality;
	};

	typedef c_NodePath2<c_UnsignedLongNode2> c_UnsignedLongNodePath2;
	typedef c_NodePath2<c_InstanceCountNode2<c_UnsignedLongNode2> > c_UnsignedLongNodeInstancePath2;

	/**
	  * Deprecated types split on different types to enable
	  * refactoring in smaller scopes until the type may be
	  * totally removed
	  */
//	typedef deprecated::c_NodePath2<deprecated::c_CaptionNode2> c_01_CaptionNodePath; // To be refactored
	typedef oprime::c_KeyPath<c_DataRepresentationFramework::c_UTF8String> c_01_CaptionNodePath; // To be refactored
//	typedef oprime::c_KeyPath<oprime::c_WrappedKeyNode<c_DataRepresentationFramework::c_UTF8String> > c_01_CaptionNodePath; // To be refactored
	typedef deprecated::c_NodePath2<deprecated::c_CaptionNode2> c_02_CaptionNodePath; // To be refactored
	typedef deprecated::c_NodePath2<deprecated::c_CaptionNode2> c_03_CaptionNodePath; // To be refactored

}


#endif // __BCPLUSPLUS__
#endif
