/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file is part of and is developed by the Darwinet project at https://sourceforge.net/projects/darwinet/
 */
//---------------------------------------------------------------------------

#ifndef MainFrameworkH
#define MainFrameworkH

#include <boost/shared_ptr.hpp>
#include <string>

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

namespace darwinet {

	/**
	  * Models a Drawinet MIV (Model, Instance,Value container)
	  */
	class c_DarwinetMIV {
	public:
		typedef boost::shared_ptr<c_DarwinetMIV> shared_pointer;

		// Begin c_DarwinetMIV

		/**
		  * Sets required variable to provided value
		  */
		virtual void setValue(int value) = 0;

		/**
		  * Returns the value of required variable
		  */
		virtual int getValue() = 0;

		// End c_DarwinetMIV

	};

	typedef c_DarwinetMIV::shared_pointer c_DarwinetMIVPtr;

	//-----------------------------------------------------------------------
	/**
	  * Models a View into a Darwinet Domian
	  */
	class c_DarwinetView {
	public:
		typedef boost::shared_ptr<c_DarwinetView> shared_pointer;

		// Begin c_DarwinetView

		/**
		  * Returns our MIV
		  */
		virtual c_DarwinetMIVPtr getMIV() = 0;

		// End c_DarwinetView
	};

	typedef c_DarwinetView::shared_pointer c_DarwinetViewPtr;

	//-----------------------------------------------------------------------

	/**
	  * Models a MIV history
	  */
	class c_DarwinetMIVHistory {
	public:

		typedef boost::shared_ptr<c_DarwinetMIVHistory> shared_pointer;
		typedef std::string t_sDelta;

		// Begin c_DarwinetMIVHistory

		/**
		  * Updates the MIV History with provided Delta (change)
		  */
		virtual void actOnDelta(t_sDelta sDelta) = 0;

		// End c_DarwinetMIVHistory
	};

	typedef c_DarwinetMIVHistory::shared_pointer c_DarwinetMIVHistoryPtr;
	typedef c_DarwinetMIVHistory::t_sDelta t_sDelta;

	//-----------------------------------------------------------------------

	/**
	  * Models a Darwinet Domain
	  */
	class c_DarwinetDomain {
	public:

		typedef boost::shared_ptr<c_DarwinetDomain> shared_pointer;

		// Begin c_DarwinetDomain

		/**
		  * retuns a view into the our Domain
		  */
		virtual c_DarwinetViewPtr getView() = 0;

		/**
		  * Returns access to this domains MIV history
		  */
		virtual c_DarwinetMIVHistoryPtr getMIVHistory() = 0;

		// End c_DarwinetDomain

	};

	typedef c_DarwinetDomain::shared_pointer c_DarwinetDomainPtr;
	//-----------------------------------------------------------------------
	/**
	  * Returns the default Darwinet Domain.
	  */
	c_DarwinetDomainPtr getDefaultDarwinetDomain();

}


#endif
