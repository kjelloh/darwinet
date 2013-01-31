//---------------------------------------------------------------------------

#pragma hdrstop

#include "MainFramework.h"
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace darwinet {
	class c_DarwinetMIVImpl; // forward
	typedef boost::shared_ptr<c_DarwinetMIVImpl> c_DarwinetMIVImplPtr;
	class c_DarwinetMIVHistoryImpl; // forward
	typedef boost::shared_ptr<c_DarwinetMIVHistoryImpl> c_DarwinetMIVHistoryImplPtr;
	class c_DarwinetViewImpl; // forward
	typedef boost::shared_ptr<c_DarwinetViewImpl> c_DarwinetViewImplPtr;
	class c_DarwinetDomainImpl; // forward
	typedef boost::shared_ptr<c_DarwinetDomainImpl> c_DarwinetDomainImplPtr;

	//-----------------------------------------------------------------------
	/**
	  * Implements the c_DarwinetMIV interface
	  */
	class c_DarwinetMIVImpl : public c_DarwinetMIV {
	public:
		// Begin c_DarwinetMIV

		/**
		  * Sets required variable to provided value
		  */
		virtual void setValue(int value);

		/**
		  * Returns the value of required variable
		  */
		virtual int getValue();

		// End c_DarwinetMIV

		/**
		  * Constructor
		  */
		c_DarwinetMIVImpl(c_DarwinetViewImplPtr pViewImpl);

		/**
		  * returns our parent View implementation
		  */
		c_DarwinetViewImplPtr getViewImpl();

	private:

		/**
		  * Private storage of our parent view
		  */
		c_DarwinetViewImplPtr m_pViewImpl;

		/**
		  * Private storage of our cashed value
		  */
		int m_cashedValue;

		/**
		  * Private pointer of a shared pointer to our instance
		  */
		c_DarwinetMIVImplPtr m_pShared_This;

	};

	//-----------------------------------------------------------------------

	/**
	  * Models a View into a Darwinet Domian
	  */
	class c_DarwinetViewImpl : public  c_DarwinetView {
	public:

		// Begin c_DarwinetView

		/**
		  * Returns our MIV
		  */
		virtual c_DarwinetMIVPtr getMIV();

		// End c_DarwinetView

		/**
		  * Constructor
		  */
		c_DarwinetViewImpl(c_DarwinetDomainImplPtr pDomainImpl);

		/**
		  * Returns our parent Domain implementation
		  */
		c_DarwinetDomainImplPtr getDomainImpl();

		/**
		  * Returns our MIV implementation
		  */
		c_DarwinetMIVImplPtr getMIVImpl();

	private:

		/**
		  * Private storage of our parent Domain implementation
		  */
		c_DarwinetDomainImplPtr m_pDomainImpl;

		/**
		  * Private styorage of our MIV implementation
		  */
		c_DarwinetMIVImplPtr m_pMIVImpl;

		/**
		  * Private pointer of a shared pointer to our instance
		  */
		c_DarwinetViewImplPtr m_pShared_This;

	};
	//-----------------------------------------------------------------------

	/**
	  * Models a MIV history
	  */
	class c_DarwinetMIVHistoryImpl : public c_DarwinetMIVHistory {
	public:

		// Begin c_DarwinetMIVHistory

		/**
		  * Updates the MIV History with provided Delta (change)
		  */
		virtual void actOnDelta(t_sDelta sDelta);

		// End c_DarwinetMIVHistory

		/**
		  * Constructor
		  */
		c_DarwinetMIVHistoryImpl(c_DarwinetDomainImplPtr pDomainImpl);

	private:

		/**
		  * Private storage of our parent Domain implementation
		  */
		c_DarwinetDomainImplPtr m_pDomainImpl;

		/**
		  * private storage of current delta sequence
		  */
		std::vector<t_sDelta> m_deltas;

		/**
		  * Private pointer of a shared pointer to our instance
		  */
		c_DarwinetMIVHistoryImplPtr m_pShared_This;

	};

	//-----------------------------------------------------------------------

	/**
	  * Implements a Darwinet Domain
	  */
	class c_DarwinetDomainImpl : public c_DarwinetDomain {
	public:
		// Begin c_DarwinetDomain

		/**
		  * retuns a view into the our Domain
		  */
		virtual c_DarwinetViewPtr getView();

		/**
		  * Returns access to this domains MIV history
		  */
		virtual c_DarwinetMIVHistoryPtr getMIVHistory();

		// End c_DarwinetDomain

		/**
		  * Constructor
		  */
		c_DarwinetDomainImpl();

		/**
		  * Returns our parent MIV history implementation
		  */
		c_DarwinetMIVHistoryImplPtr getMIVHistoryImpl();

		/**
		  * Returns our view implementation
		  */
		c_DarwinetViewImplPtr getDarwinetViewImpl();

	private:

		/**
		  * Private storage of our MIV history implementation
		  */
		c_DarwinetMIVHistoryImplPtr m_pDarwinetMIVHistoryImpl;

		/**
		  * Private storage of our View implementation
		  */
		c_DarwinetViewImplPtr m_pDarwinetViewImpl;

		/**
		  * Private pointer of a shared pointer to our instance
		  */
		c_DarwinetDomainImplPtr m_pShared_This;

	};

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	// Begin c_DarwinetMIV

	/**
	  * Sets required variable to provided value
	  */
	void c_DarwinetMIVImpl::setValue(int value) {
		// Detect the change
		int delta_value = value - this->getValue();
		if (delta_value > 0) {
			// Add value
			std::string sDelta = "delta_v add HelloWorld ";
			sDelta += delta_value;
			this->getViewImpl()->getDomainImpl()->getMIVHistoryImpl()->actOnDelta(sDelta);
		}
		else {
			// subtract value
			std::string sDelta = "delta_v subtract HelloWorld ";
			sDelta += delta_value;
			this->getViewImpl()->getDomainImpl()->getMIVHistoryImpl()->actOnDelta(sDelta);
		}

	}

	//-----------------------------------------------------------------------
	/**
	  * Returns the value of required variable
	  */
	int c_DarwinetMIVImpl::getValue() {
		return m_cashedValue;
	}

	// End c_DarwinetMIV

	/**
	  * Constructor
	  */
	c_DarwinetMIVImpl::c_DarwinetMIVImpl(c_DarwinetViewImplPtr pViewImpl)
		:   m_pShared_This(this)
		   ,m_pViewImpl(pViewImpl)
	{
	}

	//-----------------------------------------------------------------------
	/**
	  * returns our parent View implementation
	  */
	c_DarwinetViewImplPtr c_DarwinetMIVImpl::getViewImpl() {
		return this->m_pViewImpl;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	// Begin c_DarwinetView

	/**
	  * Returns our MIV
	  */
	c_DarwinetMIVPtr c_DarwinetViewImpl::getMIV() {
		return this->getMIVImpl();
	}

	// End c_DarwinetView

	/**
	  * Constructor
	  */
	c_DarwinetViewImpl::c_DarwinetViewImpl(c_DarwinetDomainImplPtr pDomainImpl)
		:   m_pShared_This(this)
		   ,m_pDomainImpl(pDomainImpl)
	{

	}

	/**
	  * Returns our parent Domain implementation
	  */
	c_DarwinetDomainImplPtr c_DarwinetViewImpl::getDomainImpl() {
		return this->m_pDomainImpl;
	}

	/**
	  * Returns our MIV implementation
	  */
	c_DarwinetMIVImplPtr c_DarwinetViewImpl::getMIVImpl() {
		if (!this->m_pMIVImpl) {
			this->m_pMIVImpl.reset(new c_DarwinetMIVImpl(this->m_pShared_This));
		}
		return this->m_pMIVImpl;
    }

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	// Begin c_DarwinetMIVHistory

	/**
	  * Updates the MIV History with provided Delta (change)
	  */
	void c_DarwinetMIVHistoryImpl::actOnDelta(t_sDelta sDelta) {
		this->m_deltas.push_back(sDelta);
		// TODO - Distribute the delta to the other nodes of the network
	}

	// End c_DarwinetMIVHistory

	/**
	  * Constructor
	  */
	c_DarwinetMIVHistoryImpl::c_DarwinetMIVHistoryImpl(c_DarwinetDomainImplPtr pDomainImpl)
		:  m_pShared_This(this)
		  ,m_pDomainImpl(pDomainImpl)
	{
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------

	// Begin c_DarwinetDomain

	/**
	  * retuns a view into the our Domain
	  */
	c_DarwinetViewPtr c_DarwinetDomainImpl::getView() {
		return this->getDarwinetViewImpl();
	}

	//-----------------------------------------------------------------------
	/**
	  * Returns access to this domains MIV history
	  */
	c_DarwinetMIVHistoryPtr c_DarwinetDomainImpl::getMIVHistory() {
		return this->getMIVHistoryImpl();
	}

	// End c_DarwinetDomain

	/**
	  * Constructor
	  */
	c_DarwinetDomainImpl::c_DarwinetDomainImpl()
		: m_pShared_This(this)
	{
	}


	/**
	  * Returns our parent MIV history implementation
	  */
	c_DarwinetMIVHistoryImplPtr c_DarwinetDomainImpl::getMIVHistoryImpl() {
		if (!this->m_pDarwinetMIVHistoryImpl) {
			this->m_pDarwinetMIVHistoryImpl.reset(new c_DarwinetMIVHistoryImpl(this->m_pShared_This));
		}
		return this->m_pDarwinetMIVHistoryImpl;
	}

	/**
	  * Returns our view implementation
	  */
	c_DarwinetViewImplPtr c_DarwinetDomainImpl::getDarwinetViewImpl() {
		if (!this->m_pDarwinetViewImpl) {
			this->m_pDarwinetViewImpl.reset(new c_DarwinetViewImpl(this->m_pShared_This));
		}
		return this->m_pDarwinetViewImpl;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	/**
	  * Returns the default Darwinet Domain.
	  */
	c_DarwinetDomainPtr getDefaultDarwinetDomain() {
		static c_DarwinetDomainImplPtr m_pInstance;

		if (!m_pInstance) {
			m_pInstance.reset(new c_DarwinetDomainImpl());
		}

		return m_pInstance;
	}

}

