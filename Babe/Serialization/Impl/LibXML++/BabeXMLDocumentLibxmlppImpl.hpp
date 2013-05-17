//
// BabeXMLDocumentLibxmlppImpl.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 27 18:18:07 2011 alexandre champion
// Last update Mon Nov 28 22:31:49 2011 alexandre champion
//

#ifndef		__BABE_XMLDOCUMENTLIBXMLPPIMPL_HPP__
# define	__BABE_XMLDOCUMENTLIBXMLPPIMPL_HPP__

# include <vector>
# include <libxml++/libxml++.h>
# include "BabeXMLDocumentImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ XMLDocumentLibxmlppImpl : public XMLDocumentImpl
  {
  private:
    class ElementLibxmlpp : public Element
    {
    public:
      ElementLibxmlpp(xmlpp::Element* elem) : element(elem) {}
      virtual ~ElementLibxmlpp() {}
      xmlpp::Element* get() { return element; }

    public:
      xmlpp::Element* element;
    };

  private:
    typedef std::vector<xmlpp::Element*> ElemVector;

  public:
    XMLDocumentLibxmlppImpl(std::string const& filePath, eOpen openType = READ);
    virtual ~XMLDocumentLibxmlppImpl();
    virtual AttributeMap getNodeAttributes(std::string const& nodeName);
    virtual AttributeMapVector getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName);
    virtual Element* addNodeToRoot(std::string const& nodeName);
    virtual Element* addNode(Element* parentNode, std::string nodeName);
    virtual AttributeMap getNodeAttributes(Element* node) = 0;
	virtual Element* getNodeByAttribute(std::string const& parentNodeName, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue) = 0;
    virtual void setValue(Element* node, std::string const& value);
    virtual void addAttribute(Element* node, std::string const& attributeName, std::string const& attributeValue);
    virtual void writeToFile();

  private:
    xmlpp::Node* getNodeByName(std::string const& nodeName);
    xmlpp::Element* getNodeElemByName(std::string const& nodeName);
    ElemVector getNodeListByName(std::string const& parentNodeName, std::string const& nodeName);
    AttributeMap getAttributes(xmlpp::Element* element);
    AttributeMap childrenToAttributeMap(xmlpp::Element* element);
    std::string const& getPath() const;
    xmlpp::Node* getNodeByNameTR(xmlpp::Node* node, std::string const& searchedNode);

  private:
    std::string		mPath;
    eOpen		mOpenType;
    xmlpp::DomParser*	mParser;
    xmlpp::Node*	mRootNode;
    xmlpp::Document*	mDocument;
  };

} // End of namespace Babe


#endif		// !__BABE_XMLDOCUMENTLIBXMLPPIMPL_HPP__
