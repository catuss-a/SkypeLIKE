
#ifndef		__BABE_XMLDOCUMENTIMPL_HPP__
# define	__BABE_XMLDOCUMENTIMPL_HPP__

# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ XMLDocumentImpl
  {
  public:
    class Element
    {
    public:
      virtual ~Element() {}
    };
    enum eOpen
      {
	READ,
	CREATE
      };
    typedef std::map<std::string, std::string> AttributeMap;
    typedef std::vector<AttributeMap> AttributeMapVector;

  public:
    virtual ~XMLDocumentImpl() {}
    virtual AttributeMap getNodeAttributes(std::string const& nodeName) = 0;
    virtual AttributeMapVector getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName) = 0;
    virtual Element* addNodeToRoot(std::string const& nodeName) = 0;
    virtual Element* addNode(Element* parentNode, std::string nodeName) = 0;
    virtual AttributeMap getNodeAttributes(Element* node) = 0;
	virtual Element* getNodeByAttribute(std::string const& parentNodeName, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue) = 0;
    virtual void setValue(Element* node, std::string const& value) = 0;
    virtual void addAttribute(Element* node, std::string const& attributeName, std::string const& attributeValue) = 0;
    virtual void writeToFile() = 0;
  };

} // End of namespace Babe


#endif		// !__BABE_XMLDOCUMENTIMPL_HPP__
