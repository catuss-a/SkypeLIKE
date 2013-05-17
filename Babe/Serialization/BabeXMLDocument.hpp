
#ifndef		__BABE_XMLDOCUMENT_HPP__
# define	__BABE_XMLDOCUMENT_HPP__

# include <map>
# include <vector>
# include <string>
# include "BabeDef.hpp"
# include "BabeXMLDocumentImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ XMLDocument
  {
  public:
    typedef std::map<std::string, std::string> AttributeMap;
    typedef std::vector<AttributeMap> AttributeMapVector;

  public:
    XMLDocument(std::string const& filePath, XMLDocumentImpl::eOpen openType = XMLDocumentImpl::READ);
    ~XMLDocument();

    /*
    ** Intended for fast use... Dont use this function if there is more than
    ** one node named the same : will return the first one found !!!
    */
    AttributeMap getNodeAttributes(std::string const& nodeName);

    /*
    ** Intended for fast use... Get the attributes of each element named nodeName
    ** that have a parent node named parentNodeName
    */
    AttributeMapVector getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName);

    /*
    ** Create child node to the root node
    */
    XMLDocumentImpl::Element* addNodeToRoot(std::string const& nodeName);

    /*
    ** Create child node to the specified node
    */
    XMLDocumentImpl::Element* addNode(XMLDocumentImpl::Element* parentNode, std::string nodeName);

    AttributeMap getNodeAttributes(XMLDocumentImpl::Element* node);
	XMLDocumentImpl::Element* getNodeByAttribute(std::string const& parentNode, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue);

    /*
    ** Set the value of the specified node
    */
    void setValue(XMLDocumentImpl::Element* node, std::string const& value);

    /*
    ** Add a new attribute to the specified node
    */
    void addAttribute(XMLDocumentImpl::Element* node, std::string const& attributeName, std::string const& attributeValue);

    /*
    ** Output xml file
    */
    void writeToFile();

  private:
    XMLDocumentImpl* mImpl;
  };

} // End of namespace Babe

#endif		// ! __BABE_XMLDOCUMENT_HPP__
