/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef BerTlvH
#define BerTlvH
//---------------------------------------------------------------------------
/**
 * **********************************************
 * A BerTlv API.
 */
#include <vector>
#include <map>
#include "DataRepresentationFrameWork.h"

namespace bertlv {

	/**
	  * bertlv::t_byte
	  */
	typedef c_DataRepresentationFramework::t_raw_byte t_byte;

	/**
	 * Enumeration for boolean value
	 */
	enum E_Boolean {
		ETRUE, EFALSE, ENULL
	};

	typedef c_DataRepresentationFramework::t_raw_vector c_BertlvByteVector;

	/**
	 * Miscellaneous helper methods.
	 */
	class BerTlvHelperMethods {
	public:
		/**
		 * pre-condition:
		 * ((bitindex >= 1) && (bitindex <= 8))
		 * @param byte The byte to check
		 * @param bitindex to check (range 1-8)
		 * @return true if bit at bitindex is set, otherwise false.
		 * @throw invalid_argument if precondition not fulfilled.
		 */
		static bool isSet(t_byte byte, const int bitindex);

		/**
		 * Runs sprintf and checks that the result is OK (>=0) and
		 * that no more than maxchars is written (otherwise runtime_error is thrown).
		 * @param buf buffer to write to
		 * @param format The format string
		 * @param val The value to write
		 * @param maxchars Max number of chars to write
		 */
		static void safe_sprintf(c_DataRepresentationFramework::c_ISO_8859_1_String& buf, const c_DataRepresentationFramework::c_ISO_8859_1_String& format, int val);
	};

	/**
	 * Interface for look up of tag labels by their
	 * value and vice versa.
	 */
	template <typename _Tag>
	class TagLookupIfc {
	public:
		/**
		 * @param tagvalue The tag value
		 * @return The label of the tag value
		 * @throw range_error If no label found
		 */
		virtual c_DataRepresentationFramework::c_ISO_8859_1_String lookup(const _Tag tagvalue) const = 0;

		/**
         * @param taglabel The tag label
         * @return The value of the tag label
         * @throw range_error If no value found
         */
        virtual int lookup(const c_DataRepresentationFramework::c_ISO_8859_1_String & taglabel) const = 0;

        /**
         * This method can be used when no label is found on a look up.
         * Can return "N/A" or just an empty string ("") for example.
         * @return The string representing "no label present"
         */
        virtual c_DataRepresentationFramework::c_ISO_8859_1_String getNoLabelAvailable() const = 0;
    };


    /**
     * A log interface.
     */
    class BerTlvLogIfc {
    public:
        /**
         * Writes a line to the log.
         */
        virtual void write(const c_DataRepresentationFramework::c_ISO_8859_1_String& line) = 0;

        /**
         * Writes a line followed by a newline.
         */
        virtual void writeln(const c_DataRepresentationFramework::c_ISO_8859_1_String& line) = 0;
    };


    /**
     * Common interface of all items of a TLV container.
     */
    class BerTlvItemIfc {
	public:
		/**
		 * Destructor
		 */
		virtual ~BerTlvItemIfc() {
		}

		/**
		 * @return returns current BerTlvItemIfc object
		 * as a vector of bytes
		 */
		virtual c_BertlvByteVector byteVector() const = 0;
	};


	/**
	 * The tag (type) item of a TLV container.
	 */
	template <typename _Tag>
	class BerTlvTagItem : public BerTlvItemIfc {
	public:

		/**
		 * Constructor
		 * @param value the tag value
		 */
		BerTlvTagItem(_Tag value) : value(value) {
		}

		/**
		 * Destructor
		 */
		~BerTlvTagItem() {
		}

		/**
		 * @return the tag value
		 */
		_Tag getValue() const {
			return value;
		}

		/**
		  *
		  * @see base class declaration
		  */
		c_BertlvByteVector byteVector() const {
			c_BertlvByteVector ret;
			bool done = false;
			_Tag bval = value;
			while (!done) {
				// e.g.
				// bval = 0xDDFF -> div = DD, mod = FF
				// put mod first in the vector
				t_byte div = bval / 0x100;
				t_byte mod = bval % 0x100;
				ret.insert(ret.begin(), mod);
				if (div > 0) {
					// if more bytes -> divide further on by 0x100
					bval = bval / 0x100;
				}
				else {
					// no more bytes
					done = true;
				}
			}
			return ret;
		}

	private:
		const _Tag value;
	};

	/**
	 * The length item of a TLV container.
	 */
	template <typename _Length = unsigned long>
	class BerTlvLengthItem : public BerTlvItemIfc {
	public:
		/**
		 * Constructor
		 * @param value the length value
		 */
		BerTlvLengthItem(const long value);

		/**
		 * Destructor
		 */
		~BerTlvLengthItem();
		/*
		*
		@see base class declaration
		*/
		c_BertlvByteVector byteVector() const;

		/**
		 * @return the length value
		 */
		_Length getValue() const;
	private:
		const _Length value;
	};

	/**
	 * Content interface (the value of a TLV container)
	 */
	class BerTlvContentItemIfc : public BerTlvItemIfc {
	public:
		virtual ~BerTlvContentItemIfc() {
		}

		/*
		*
		@see base class declaration
		*/
		virtual c_BertlvByteVector byteVector() const = 0;

		/**
		 * @return true if this is a composite
		 */
		virtual bool isComposite() const = 0;
	};


	/**
	 * Primitive content (byte contents).
	 */
	class BerTlvPrimitiveContent : public BerTlvContentItemIfc {
	public:
		/*
		*
		@see base class declaration
		*/
		c_BertlvByteVector byteVector() const;

		/**
		 * @see base class declaration
		 */
		bool isComposite() const;

		/**
		 * Constructor
		 */
		BerTlvPrimitiveContent(c_BertlvByteVector bytes);

		/**
		 * Destructor
		 */
		virtual ~BerTlvPrimitiveContent();
	private:
		const c_BertlvByteVector bytes;
	};

	// Forward
	template <typename _Tag>
	class BerTlv;

	/**
	 * Composite content (contain other BerTlv:s).
	 */
	template <typename _Tag>
	class BerTlvCompositeContent : public BerTlvContentItemIfc {
	public:
		/**
		 * Constructor
		 * @param items items included in the composite content
		 */
		BerTlvCompositeContent(std::vector < const BerTlv<_Tag>* > items);

		/**
		 * Destructor
		 */
		virtual ~BerTlvCompositeContent();
		/*
		*
		@see base class declaration
		*/
		c_BertlvByteVector byteVector() const;

		/**
		 * @see base class declaration
		 */
		bool isComposite() const;

		/**
		 * @return an iterator (the first position)
		 */
		std::vector < const BerTlv<_Tag>* >::const_iterator iterator_begin() const;

		/**
		 * @return an iterator (the last position)
		 */
		std::vector < const BerTlv<_Tag>* >::const_iterator iterator_end() const;

		/**
		  * Searches for the item with provided tag value and instance index
		  * where the first instance has index 0, or NULL
		  * if not found.
		  * Searches this item contents only. WIll not search recurivelly.
		  * @param tag tag value of item to find
		  * @instance_index the required tag instance where 0 is the first occurence.
		  * @return Item with a tag value matching the tag param.
		  */
		const BerTlv<_Tag>* findItem(const _Tag tag,int instance_index = 0) const;

	private:
		/**
		 * The items of the composite
		 */
		std::vector < const BerTlv<_Tag>* > items;

		/**
		 * @clientCardinality 1
		 * @supplierCardinality 0..*
		 * @directed
		 */
		BerTlv<_Tag>* lnkBerTlv;
	};

	/**
	 * Class containing a tag (type), length and a content (value).
	 * The user of this class can build tree structures of BerTlv:s e.g:
	 * (C=Composite, P=Primitive)
	 * C1
	 * |
	 * --P1
	 * |
	 * --P2
	 * |
	 * --C1.1
	 * |
	 * --P1.1
	 * |
	 * --P1.2
	 * IMPORTANT: The user of the class is always responsible for deleting the "root" (C1 above)
	 */
	template <typename _Tag>
	class BerTlv {
	public:
		/**
		 * Factory method creating a primitive (simple) BerTlv.
		 * IMPORTANT: If this is a "stand-alone" BerTlv (not a part of a BerTlv tree structure)
		 * the caller is responsible for deleting it (see class comment for further information).
		 * @param tagvalue the tagvalue
		 * @param bytes a list of bytes
		 * @return the BerTlv
		 */
		static const BerTlv<_Tag>* createPrimitiveBerTlv(const _Tag tagvalue, const c_BertlvByteVector bytes);

		/**
		 * Factory method creating a BerTlv with composite content (contains other BerTlv:s which can be
		 * primitives and/or other composites)
		 * IMPORTANT: If this is a "root" BerTlv (doesn't have any other BerTlv node above it in a tree structure)
		 * the caller is responsible for deleting it (see class comment for further information).
		 * @param tagvalue the tagvalue
		 * @param items a list of other BerTlv:s
		 */
		static const BerTlv<_Tag>* createCompositeBerTlv(const _Tag tagvalue, std::vector < const BerTlv<_Tag>* > items);
		/*
		*
		@see base class declaration
		*/
		c_BertlvByteVector byteVector() const;

		/**
		 * Destructor
		 */
		virtual ~BerTlv();

		/**
		 * @return value of tag
		 */
		_Tag getTagValue() const;

		/**
		 * @return value of length
		 */
		int getLengthValue() const;

		/**
		 * @return content
		 */
		const BerTlvContentItemIfc * const getContent() const;

	private:
		/**
		 * Constructor
		 * @param tagvalue tag value
		 * @content content
		 */
		BerTlv(const _Tag tagvalue, const BerTlvContentItemIfc * const pContent);

		/**
		 * tag object
		 */
		const BerTlvTagItem<_Tag> m_tag;

		/**
		 * length object
		 */
		const BerTlvLengthItem<> m_length;

		/**
		 * pointer to content
		 */
		const BerTlvContentItemIfc * const m_pContent;
	};


	/**
	 * Parses a byte vector to a BerTlv object.
	 */
	template <typename _Tag>
	class BerTlvParser {
	public:
		/**
		 * Parses byte vector parameter to BerTlv object
		 * @param bytes byte vector
		 * @return pointer to BerTlv object
		 */
		static const BerTlv<_Tag>* parseBerTlv(const c_BertlvByteVector& bytes);

	private:
		/**
		 * Parses byte vector parameter to BerTlv object
		 * @param bytes byte vector
		 * @param offset position to start parsing (included since recursive method)
		 * @return vector of pointers to BerTlv objects
		 */
		static std::vector < const BerTlv<_Tag>* > parseBerTlv(const c_BertlvByteVector& bytes, const size_t length,
		   const size_t offset);

		/**
		 * Reads tag from byte vector parameter
		 * @param bytes byte vector
		 * @param offset position to start reading
		 * @param bytesReadReference call by ref param. Returns number of bytes of the tag.
		 * @return tag value
		 */
		static _Tag readTag(const c_BertlvByteVector& bytes, const size_t offset, int & bytesReadReference);

		/**
		 * Reads length from byte vector parameter
		 * @param bytes byte vector
		 * @param offset position to start reading
		 * @param bytesReadReference call by ref param. Returns number of bytes of the length.
		 * @return length value
		 */
		static int readLength(const c_BertlvByteVector& bytes, const size_t offset, int& bytesReadReference);
	};
	// ============================ BerTlvParser =================================
	/**
	 * Parses byte vector parameter to BerTlv object
	 * @param bytes byte vector
	 * @param offset position to start parsing (included since recursive method)
	 * @return vector of pointers to BerTlv objects
	 */
	template <typename _Tag>
	const BerTlv<_Tag>* BerTlvParser<_Tag>::parseBerTlv(const c_BertlvByteVector& bytes) {
		BerTlv<_Tag>* result = NULL;
		std::vector <const BerTlv<_Tag>*> ret = parseBerTlv(bytes, bytes.size(), 0);
		// return the first and only element since one root element
		if (ret.size() == 1) {

			result = const_cast<BerTlv<_Tag>*>(*ret.begin());
		}
		else {
			// Failed! No items or more than 1 item!
		}
		return result;
	}

	/**
	 * Reads tag from byte vector parameter
	 * @param bytes byte vector
	 * @param offset position to start reading
	 * @param bytesReadReference call by ref param. Returns number of bytes of the tag.
	 * @return tag value
	 */
	template <typename _Tag>
	_Tag BerTlvParser<_Tag>::readTag(const c_BertlvByteVector& bytes, const size_t offset, int & bytesReadReference) {
		_Tag tot;
		_Tag first = static_cast<_Tag>(bytes[offset + 0]);
		bytesReadReference = 1;
		int bit5to1 = first & 0x1F;
		// Check if bit 5 -> bit 1 is in <= 30 or > 30
		if (bit5to1 <= 30) {
			// it's a tag included in a single octet
			tot = first;
		}
		else {
			// it's a tag included in more than one octet
			bool done = false;
			// initialize tot to the value of the first byte,
			// start the loop at the second byte
			tot = first;
			int index = 1;
			// Read until bit 8 is 0
			while (!done) {
				_Tag val = static_cast<_Tag>(bytes[offset + index]);
				tot = static_cast<_Tag>(tot * 0x100 + val);
				if (BerTlvHelperMethods::isSet(val, 8)) {
					// continue with next byte
					index++;
				}
				else {
					// the last byte
					done = true;
				}
			}
			bytesReadReference += index;
		}
		return tot;
	}

	template <typename _Tag>
	int BerTlvParser<_Tag>::readLength(const c_BertlvByteVector& bytes, const size_t offset, int & bytesReadReference) {
		int first = bytes[offset];
		int tot = 0;
		if (first <= 127) {
			bytesReadReference = 1;
			tot = first;
		}
		else {
			int nbrOfBytes = first & 0x7F;
			bytesReadReference = nbrOfBytes + 1;
			for (int i = 1; i <= nbrOfBytes; i++) {
				tot = tot * 0x100 + bytes[offset + i];
				//int v = bytes[offset + i] << ((nbrOfBytes-i) * 8);
				//tot += v;
			}
		}
		return tot;
	}

	/**
	 * Parses byte vector parameter to BerTlv object
	 * @param bytes byte vector
	 * @param offset position to start parsing (included since recursive method)
	 * @return vector of pointers to BerTlv objects
	 */
	template <typename _Tag>
	std::vector < const BerTlv<_Tag>* > BerTlvParser<_Tag>::parseBerTlv(const c_BertlvByteVector& bytes, const size_t length,const size_t offset) {
		std::vector<const BerTlv<_Tag>*> items;
		// check arguments
		if (offset <= bytes.size()) {
			// Ok to proceed
			// current position in bytes vector
			size_t localoffset = offset;

			bool done = (length == 0);

			while (!done) {
				// called method will write nbr of read bytes
				// in this reference (call by reference)
				int bytesReadReference;
				// read tag
				const _Tag tag = readTag(bytes, localoffset, bytesReadReference);
				// check if bit 6 is set (-> it's a composite)
				const bool isComposite = BerTlvHelperMethods::isSet(bytes[0 + localoffset], 6);
				// increment by nbr of tag bytes
				localoffset += bytesReadReference;
				// read length field
				const int len = readLength(bytes, localoffset, bytesReadReference);
				// increment offset by nr of bytes in length field
				localoffset += bytesReadReference;
				const BerTlv<_Tag>* tlv;
				if (isComposite) {
					// A composite
					// parse composite contents
					std::vector < const BerTlv<_Tag>* > children = parseBerTlv(bytes, len, localoffset);
					tlv = BerTlv<_Tag>::createCompositeBerTlv(tag, children);
				}
				else {
					// A leaf
					c_BertlvByteVector value;
					for (int i = 0; i < len; i++) {
						value.push_back(bytes[localoffset + i]);
					}
					tlv = BerTlv<_Tag>::createPrimitiveBerTlv(tag, value);
				}
				items.push_back(tlv);
				// increase local offset by content length
				localoffset += len;
				// check if we've read all bytes we're supposed to read
				if (localoffset - offset >= length) {
					done = true;
				}
			}
		}
		else {
			c_DataRepresentationFramework::c_ISO_8859_1_String sMessage("BerTlvParser<_Tag>::parseBerTlv failed. Called with offset outside bytes array");
			throw std::runtime_error(sMessage);
		}

		return items;
	}
	// ============================ (END) BerTlvParser =================================
	// ==========================================================================


	/**
	 * Interface to formatter of primitive BerTlv contents.
	 * The client implements a formatter for type or tag specific
	 * contents and provides them in a BerTlv formatter and provides it
	 * to the Log output formatter (printToStr).
	 */
	class BerTlvPrimitiveContentsFormatterIfc {
	public:
		/**
		 * Returns a formatted string of provided primitive content
		 */
		virtual c_DataRepresentationFramework::c_ISO_8859_1_String toString(const BerTlvPrimitiveContent * const pContent,const c_DataRepresentationFramework::c_ISO_8859_1_String& sIndent) = 0;
	};


	/**
	 * Interface to Formatter of primitive BerTlv contents.
	 * Client implements a formatter with this interface and provides
	 * it to logger funktion to control formatting of contents in Log.
	 */
	template <typename _Tag>
	class BerTlvContentsFormatterIfc {
	public:
		/**
		 * Returns true if there is a formatter for provided tag
		 */
		virtual bool tagSpecificFormatterExists(_Tag tagval) = 0;

        /**
         * Returns a formatter for provided tag id or null if none registered
         */
        virtual BerTlvPrimitiveContentsFormatterIfc * getTagSpecificFormatter(_Tag tagval) = 0;
    };


    /**
     * Formatter of primitive BerTlv contents.
     * Client implements a formatter with this interface and provides
     * it to logger funktion to control formatting of contents in Log.
     */
	template <typename _Tag>
	class BerTlvContentsFormatter : public BerTlvContentsFormatterIfc<_Tag> {
	public:
		/**
		 * Registers a formatter for a tag id.
		 */
		void addTagSpecificFormatter(_Tag tagvalue, BerTlvPrimitiveContentsFormatterIfc * formatter);
		// --------------------------------------------------------------
		// Implementation of BerTlvContentsFormatterIfc<_Tag>

		/**
		 * Returns true if there is a formatter for provided tag
		 */
		bool tagSpecificFormatterExists(_Tag tagval);

		/**
		 * Returns a formatter for provided tag id or null if none registered
		 */
		BerTlvPrimitiveContentsFormatterIfc * getTagSpecificFormatter(_Tag tagval);
		// End of Implementation of BerTlvContentsFormatterIfc<_Tag>
		// --------------------------------------------------------------

	private:
		/**
		 * Private storage of formatters for specific tag ids
		 */
		std::map < _Tag, BerTlvPrimitiveContentsFormatterIfc * > m_TagSpecificFormatters;

		/**
		 * Private storage of formatters for specific tag types
		 */
		std::map < _Tag, BerTlvPrimitiveContentsFormatterIfc * > m_TypeSpecificFormatters;

	};
	// ==========================================================================


	/**
	 * Prints a BerTlv object or raw byte data.
	 * Used in tracing/debugging.
	 */
	template <typename _Tag>
	class BerTlvPrinter {
	public:
		/**
		 * Formats provided BerTlv to provided string using provided formatters and TagLookup
		 */
		static void printToStr(const BerTlv<_Tag>* tlv, c_DataRepresentationFramework::c_ISO_8859_1_String & str, int level, const TagLookupIfc<_Tag> * tagLookup,
		   BerTlvContentsFormatterIfc<_Tag> * pContentsFormatter = NULL);

		/**
		 * Prints BerTlv object to the log object
		 * @param tlv the BerTlv object
		 * @param log c_BerTlvLogIfc object to log to
		 */
		static void print(const BerTlv<_Tag>* tlv, BerTlvLogIfc & log, const TagLookupIfc<_Tag> * tagLookup,
		   BerTlvContentsFormatterIfc<_Tag> * pContentsFormatter = NULL);

		/**
		 * Prints bytes to the log object
		 * @param bytes the bytes to write
		 * @param log c_BerTlvLogIfc object to log to
		 */
		static void printBytes(const c_BertlvByteVector bytes, BerTlvLogIfc & log);
	};

	// ============================ BerTlvCompositeContent =================================
	template <typename _Tag>
	std::vector < const BerTlv<_Tag>* >::const_iterator BerTlvCompositeContent<_Tag>::iterator_begin() const {
		return items.begin();
	}

	template <typename _Tag>
	std::vector < const BerTlv<_Tag>* >::const_iterator BerTlvCompositeContent<_Tag>::iterator_end() const {
		return items.end();
	}

	/**
	 * Returns the item with a tag value matching the tag param.
	 * Note: Doesn't search recursively. The finder is only for
	 * items one level below current (i.e. the children not the grand children).
	 * If no item found -> NULL is returned.
	 * @param tag tag value of item to find
	 * @return Item with a tag value matching the tag param.
	 * instance_no = 0 requests the first occurenec of the tag, 1 the second and so on.
	 */
	template <typename _Tag>
	const BerTlv<_Tag>* BerTlvCompositeContent<_Tag>::findItem(const _Tag tag,int instance_index) const {
		const BerTlv<_Tag>* result = NULL; // default
		std::vector < const BerTlv<_Tag>* >::const_iterator iterator = this->iterator_begin();
		std::vector < const BerTlv<_Tag>* >::const_iterator end = this->iterator_end();
		int instanceCount = 0;
		while (iterator != end) {
			if (((*iterator))->getTagValue() == tag) {
				instanceCount++;
				if ((instanceCount-1) == instance_index) {
					result = (*iterator);
				}
			}
			iterator++;
		}
		// if no match -> return NULL
		return result;
	}

	template <typename _Tag>
	bool BerTlvCompositeContent<_Tag>::isComposite() const {
		return true;
	}

	template <typename _Tag>
	BerTlvCompositeContent<_Tag>::BerTlvCompositeContent(std::vector < const BerTlv<_Tag>* > items) : items(items) {
	}

	template <typename _Tag>
	BerTlvCompositeContent<_Tag>::~BerTlvCompositeContent() {
		// delete all content of the composite
		std::vector < const BerTlv<_Tag>* >::const_iterator iter = iterator_begin();
		std::vector < const BerTlv<_Tag>* >::const_iterator end = iterator_end();
		while (iter != end) {
			delete * iter;
			iter++;
		}
	}

	template <typename _Tag>
	c_BertlvByteVector BerTlvCompositeContent<_Tag>::byteVector() const {
		c_BertlvByteVector ret;
		std::vector < const BerTlv<_Tag>* >::const_iterator i;
		// Loop through all BerTlv items and append their
		// bytes to the result ret
		for (i = items.begin(); i != items.end(); i++) {
			const BerTlv<_Tag>* b = * i;
			c_BertlvByteVector thisPart = b->byteVector();
			ret.insert(ret.end(), thisPart.begin(), thisPart.end());
		}
		return ret;
	}

	// ============================ (END) BerTlvCompositeContent =================================

	// ============================ BerTlv =================================
	template <typename _Tag>
	const BerTlv<_Tag>* BerTlv<_Tag>::createPrimitiveBerTlv(const _Tag tagvalue, const c_BertlvByteVector bytes) {
		BerTlvPrimitiveContent * pContent = new BerTlvPrimitiveContent(bytes);
		const BerTlv<_Tag>* primitive = new BerTlv(tagvalue, pContent);
		return primitive;
	}

	template <typename _Tag>
	const BerTlv<_Tag>* BerTlv<_Tag>::createCompositeBerTlv(const _Tag tagvalue, std::vector < const BerTlv<_Tag>* > items) {
		BerTlvCompositeContent<_Tag> * pContent = new BerTlvCompositeContent<_Tag>(items);
		const BerTlv<_Tag>* composite = new BerTlv<_Tag>(tagvalue, pContent);
		return composite;
	}

	template <typename _Tag>
	BerTlv<_Tag>::BerTlv(const _Tag tagvalue, const BerTlvContentItemIfc * const pContent)
		:  m_tag(BerTlvTagItem<_Tag>(tagvalue))
		  ,m_length(BerTlvLengthItem<>(pContent->byteVector().size())), m_pContent(pContent) {
	}

	template <typename _Tag>
	BerTlv<_Tag>::~BerTlv() {
		delete m_pContent;
	}

	template <typename _Tag>
	c_BertlvByteVector BerTlv<_Tag>::byteVector() const {
		c_BertlvByteVector ret;
		c_BertlvByteVector::iterator iter;
		c_BertlvByteVector src = m_tag.byteVector();
		ret.insert(ret.end(), src.begin(), src.end());
		src = m_length.byteVector();
		ret.insert(ret.end(), src.begin(), src.end());
		src = m_pContent->byteVector();
		ret.insert(ret.end(), src.begin(), src.end());
		return ret;
	}

	template <typename _Tag>
	_Tag BerTlv<_Tag>::getTagValue() const {
		return m_tag.getValue();
	}

	template <typename _Tag>
	int BerTlv<_Tag>::getLengthValue() const {
		return m_length.getValue();
	}

	template <typename _Tag>
	const BerTlvContentItemIfc * const BerTlv<_Tag>::getContent() const {
		return m_pContent;
	}

	// ============================ (END) BerTlv =================================

	// ============================ BerTlvLengthItem =================================
	template <typename _Length>
	BerTlvLengthItem<_Length>::BerTlvLengthItem(const long value) : value(value) {
	}

	template <typename _Length>
	BerTlvLengthItem<_Length>::~BerTlvLengthItem() {
	}

	template <typename _Length>
	_Length BerTlvLengthItem<_Length>::getValue() const {
		return value;
	}

	template <typename _Length>
	c_BertlvByteVector BerTlvLengthItem<_Length>::byteVector() const {
		c_BertlvByteVector ret;
		if (value <= 127) {
			// a single octet length
			// just return the value in one byte
			ret.push_back((t_byte)value);
		}
		else {
			// the first byte
			// bit 8 = 1
			// following bits represent number of subsequent length bytes
			int first = ((value / 0xFF) + 1) + 0x80;
			bool done = false;
			int bval = value;
			while (!done) {
				// e.g.
				// bval = 0xDDFF -> div = DD, mod = FF
				// put mod first in the vector
				int div = bval / 0x100;
				int mod = bval % 0x100;
				ret.insert(ret.begin(), mod);
				if (div > 0) {
					// if more bytes -> divide further on by 0x100
					bval = bval / 0x100;
				}
				else {
					// no more bytes
					done = true;
				}
			}
			// set the first "length" byte as leading
			ret.insert(ret.begin(), first);
		}
		return ret;
	}

	// ============================ (END) BerTlvLengthItem =================================

	// ============================ BerTlvPrinter =================================

	/**
	 * Prints BerTlv object to a string
	 * @param tlv the BerTlv object
	 * @param str the string to print to
	 * @param level current level of the bertlv structures. This parameter
	 * @param tagLookup A tag lookup object
	 * controls the indentation of the output
	 */
	template <typename _Tag>
	void BerTlvPrinter<_Tag>::printToStr(const BerTlv<_Tag>* tlv, c_DataRepresentationFramework::c_ISO_8859_1_String & str, int level, const TagLookupIfc<_Tag> * tagLookup,
	   BerTlvContentsFormatterIfc<_Tag> * pContentsFormatter) {
		   // set indentation of current level in the bertlv structure
		   c_DataRepresentationFramework::c_ISO_8859_1_String indent("  ");
		   for (int i = 0; i < level; i++) {
			   indent += _Literalsz("   ");
		   }
		   const _Tag tagval = tlv->getTagValue();
		   // get label (e.g. cdoOPInit) of current tag value
		   // if no TagLookupIfc<_Tag> instance -> write empty string ("")
		   // if label not found -> write value returned from getNoLabelAvailable
		   c_DataRepresentationFramework::c_ISO_8859_1_String taglabel;
		   if (tagLookup == NULL) {
			   taglabel = _Literalsz("");
		   }
		   else {
			   try {
				   taglabel = tagLookup->lookup(tagval);
			   }
			   catch (...) {
				   taglabel = _Literalsz("#failed#");
			   }
		   }
		   const int lenval = tlv->getLengthValue();
		   c_DataRepresentationFramework::c_ISO_8859_1_String tagvalbuf;
		   BerTlvHelperMethods::safe_sprintf(tagvalbuf, _Literalsz("%x"), tagval);
		   c_DataRepresentationFramework::c_ISO_8859_1_String lenvalbuf;
		   BerTlvHelperMethods::safe_sprintf(lenvalbuf, _Literalsz("%d"), lenval);
		   str.append(indent);
		   str.append(taglabel);
		   str.append("\t");
		   str.append(tagvalbuf);
		   str.append("(");
		   str.append(lenvalbuf);
		   str.append(")");
		   const BerTlvContentItemIfc * const pContents = tlv->getContent();
		   if (pContents->isComposite()) {
			   str.append("\n");
			   const BerTlvCompositeContent<_Tag>* composite = dynamic_cast<const BerTlvCompositeContent<_Tag>*>(pContents);
			   std::vector < const BerTlv<_Tag>* >::const_iterator end = composite->iterator_end();
			   std::vector < const BerTlv<_Tag>* >::const_iterator iter = composite->iterator_begin();
			   while (iter != end) {
				   const BerTlv<_Tag>* tlv = * iter;
				   // recursive call to print
				   // print the items of the composite
				   printToStr(tlv, str, level + 1, tagLookup, pContentsFormatter);
				   iter++;
			   }
		   }
		   else {
			   str.append(" = ");
			   const BerTlvPrimitiveContent * primitiveItem = (BerTlvPrimitiveContent *) pContents;
			   bool contentsFormatted = false; // Flag to signal if content is formatted
			   // Check if there is a tag specific rule
			   if (pContentsFormatter != NULL) {
				   if (pContentsFormatter->tagSpecificFormatterExists(tagval)) {
					   BerTlvPrimitiveContentsFormatterIfc * lf = pContentsFormatter->getTagSpecificFormatter(tagval);
					   str.append(lf->toString(dynamic_cast < const BerTlvPrimitiveContent * const > (pContents),indent));
					   contentsFormatted = true;
				   }
				   // Else Check if there is a registered type dependent rule
				   // Todo: Write code here
				   /*
				   if (pContentsFormatter != NULL) {
				   if (pContentsFormatter->typeSpecificFormatterExists(tagval)) {
				   BerTlvPrimitiveContentsFormatterIfc* lf = pContentsFormatter->getTypeSpecificFormatter(tagval);
				   str.append(lf->toString(dynamic_cast<const BerTlvPrimitiveContent* const>(contents)));
				   contentsFormatted = true;
				   }
				   */
			   }
			   if (!contentsFormatted) {
				   // Append as string
				   str.append("\"");
				   str += c_DataRepresentationFramework::createBracketedHexValueISO8859_1String(primitiveItem->byteVector());
				   str.append("\"");
			   }
			   str.append("\n");
		   }
	}

	template <typename _Tag>
	void BerTlvPrinter<_Tag>::print(const BerTlv<_Tag>* tlv, BerTlvLogIfc & log, const TagLookupIfc<_Tag> * tagLookup, BerTlvContentsFormatterIfc<_Tag> * pContentsFormatter) {
		   c_DataRepresentationFramework::c_ISO_8859_1_String str;
		   printToStr(tlv, str, 0, tagLookup, pContentsFormatter);
		   log.write(str);
	}

	template <typename _Tag>
	void BerTlvPrinter<_Tag>::printBytes(const c_BertlvByteVector bytes, BerTlvLogIfc & log) {
		c_DataRepresentationFramework::c_ISO_8859_1_String str;
		c_BertlvByteVector::const_iterator iter;
		int index = 0;
		for (iter = bytes.begin(); iter != bytes.end(); iter++) {
			int uc = (int) * iter;
			str.append("|");
			if (uc <= 15) {
				str.append("0");
			}
			c_DataRepresentationFramework::c_ISO_8859_1_String hexbuf;
			BerTlvHelperMethods::safe_sprintf(hexbuf, _Literalsz("%x"), uc);
			// write in 8 byte row length
			if ((++index % 8) == 0) {
				str.append("|");
			}
		}
		log.write(str);
	}
	// ============================ (END) BerTlvPrinter =================================
	// ============================ BerTlvContentsFormatter =================================

	/**
	 * Returns true if there is a formatter for provided tag
	 */
	template <typename _Tag>
	bool BerTlvContentsFormatter<_Tag>::tagSpecificFormatterExists(_Tag tagval) {
		return (getTagSpecificFormatter(tagval) != NULL);
	};

	/**
	 * Returns a formatter for provided tag id or null if none registered
	 */
	template <typename _Tag>
	BerTlvPrimitiveContentsFormatterIfc * BerTlvContentsFormatter<_Tag>::getTagSpecificFormatter(_Tag tagval) {
		BerTlvPrimitiveContentsFormatterIfc * result = NULL;
		std::map < _Tag, BerTlvPrimitiveContentsFormatterIfc * >::iterator iter;
		iter = m_TagSpecificFormatters.find(tagval);
		if (iter != m_TagSpecificFormatters.end()) {
			// Found one!
			result = iter->second;
		}
		return result;
	};

	/**
	 * Registers a formatter for a tag id.
	 */
	template <typename _Tag>
	void BerTlvContentsFormatter<_Tag>::addTagSpecificFormatter(_Tag tagvalue, BerTlvPrimitiveContentsFormatterIfc * formatter) {
		m_TagSpecificFormatters[tagvalue] = formatter;
	};
	// ============================ (END) BerTlvContentsFormatter =================================


}; // namespace bertlv

#endif
