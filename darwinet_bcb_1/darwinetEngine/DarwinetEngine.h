//---------------------------------------------------------------------------

#ifndef DarwinetEngineH
#define DarwinetEngineH
//---------------------------------------------------------------------------

/*

The actors of a darwinet domian are:
* The user
* The Application
* The Domain node
* The Domain

Each actor may play one or many a roles
* The user may be
	* Domain creator
	* Domain adimistrator
	* Application user
	* ...

Each actor may be:
* Authenticated for identity
* Authorised to perform operation
* Accounted for operations


The mechanisms of the darwinet engine are:

<View>
* Application View - A subset of the user View defined for an application
					 in the domain.
* User View - A subset of the Role view as defined for a user in the Domain.
* Role View - A subset of the Domain View as defined by a role.
* Domian View - Assemble Model, instance, Value state fo the Domain data as
				defined by a View. The View defines a time in history of
				the domain data state. Through the Domian view applications
				of the domian gets access to the domian file system and database
				as defined by the time in history.

<Authentication>
* User authentication
* Domian node Authentication

<Authorisation>
* User Auhorisation
* Domian Authorisation

<Accounting>
* User accounting - A user may receive or be debited for services
* Application accounting - An application vendor may receive or be debited for services
* Role accounting?
* Domain node accounting?
* Domain accounint?

<Representation>
* Role protection - Encrypt/Decrypt data on a per-Role level
* User protection - Encrypt/Decrypt data on a per-User level within the domain
* Domain Node Protection - Encrypt/Decrypt data on a per-node level
* Domain protection + Encrypt/Decrypt data on a per-domian level

<Transport>
* Messaging - Perform communication with other nodes in the domain

* Routing - Find the other operating nodes of the domain and roure messages
			to them
* Transport - Perform the actual transaction of messages between domian nodes
				and routing nodes of the domian.

*/



#endif
