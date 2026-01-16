//---------------------------------------------------------------------------

#ifndef DarwinetEngineProxyFrameworkH
#define DarwinetEngineProxyFrameworkH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------

/**
  * base interface of a Darwinet Domain Proxy
  */
class c_DarwinetDomainProxy {
public:

	typedef boost::shared_ptr<c_DarwinetDomainProxy> shared_ptr;

	// Begin c_DarwinetDomainProxy

	// End c_DarwinetDomainProxy
};
/**
  * Base interface of a Darwinet Engine Proxy
  */
class c_DarwinetEngineProxy {
public:

	typedef boost::shared_ptr<c_DarwinetEngineProxy> shared_ptr;

	// begin c_DarwinetEngineProxy

	/**
	  * Returns a Domain hosted by the Engine
	  */
	virtual c_DarwinetDomainProxy::shared_ptr getDomain(/* TODO: Provide path of the domain to return */) = 0;

	// End c_DarwinetEngineProxy
};

class c_DarwinetEngineFactory {
public:

	/**
	  * Factory Method that creates the Darwinet Engine to be used by the Client.
	  */
	static c_DarwinetEngineProxy::shared_ptr createDarwinetEngine();

};

#endif
