#ifndef __DB_HPP__
# define __DB_HPP__

# include "NinaCppUtils.hpp"
# include "Babe.hpp"

class DB : NINA::NonCopyable
{
	public:
		DB(std::string const& path);
		~DB();

	public:
		std::string getContacts(std::string const& login);
		void setContacts(std::string const& login, std::string const& contacts);
		bool isMatching(std::string const& login, std::string const& passwd);
		bool exists(std::string const& login);
	private:
		Babe::ApplicationManager* mAppMgr;
		Babe::XMLDocument mDB;
};

#endif /* !__DB_HPP__ */
