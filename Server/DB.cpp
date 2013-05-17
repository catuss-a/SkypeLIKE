#include <iostream>
#include <string>
#include "DB.hpp"

DB::DB(std::string const& path)
	: mAppMgr(new Babe::ApplicationManager("BabelServer")),
	mDB(path)
{
}

DB::~DB()
{
	delete mAppMgr;
}

std::string
DB::getContacts(std::string const& login)
{
	Babe::XMLDocumentImpl::Element* elem;
	Babe::XMLDocument::AttributeMap	atrMap;

	elem = mDB.getNodeByAttribute("users", "user", "login", login);
	atrMap = mDB.getNodeAttributes(elem);
	return atrMap["contacts"];
}

void
DB::setContacts(std::string const& login, std::string const& contacts)
{
	Babe::XMLDocumentImpl::Element* elem;

	elem = mDB.getNodeByAttribute("users", "user", "login", login);
	mDB.addAttribute(elem, "contacts", contacts);
	mDB.writeToFile();
}

bool
DB::isMatching(std::string const& login, std::string const& passwd)
{
	Babe::XMLDocumentImpl::Element* elem;
	Babe::XMLDocument::AttributeMap	atrMap;

	elem = mDB.getNodeByAttribute("users", "user", "login", login);
	atrMap = mDB.getNodeAttributes(elem);
	return (atrMap["password"] == passwd);
}

bool
DB::exists(std::string const& login)
{
	return (mDB.getNodeByAttribute("users", "user", "login", login) != 0);
}
