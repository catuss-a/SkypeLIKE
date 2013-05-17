//
// BabeXMLDocumentQtxmlImpl.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 27 19:14:33 2011 alexandre champion
// Last update Mon Nov 28 22:11:20 2011 alexandre champion
//

#ifndef		__BABE_XMLDOCUMENTQTXMLIMPL_HPP__
# define	__BABE_XMLDOCUMENTQTXMLIMPL_HPP__

# include <QtXml>
# include "BabeXMLDocumentImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ XMLDocumentQtxmlImpl : public XMLDocumentImpl
  {
  private:
    class ElementQtxml : public Element
    {
    public:
      ElementQtxml(QDomElement elem) : element(elem) {}
      virtual ~ElementQtxml() {}
      QDomElement get() { return element; }

    public:
      QDomElement element;
    };

  public:
    XMLDocumentQtxmlImpl(std::string const& filePath, eOpen openType = READ);
    virtual ~XMLDocumentQtxmlImpl();
    virtual AttributeMap getNodeAttributes(std::string const& nodeName);
    virtual AttributeMapVector getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName);
    virtual Element* addNodeToRoot(std::string const& nodeName);
    virtual Element* addNode(Element* parentNode, std::string nodeName);
    virtual AttributeMap getNodeAttributes(Element* node);
	virtual Element* getNodeByAttribute(std::string const& parentNodeName, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue);
    virtual void setValue(Element* node, std::string const& value);
    virtual void addAttribute(Element* node, std::string const& attributeName, std::string const& attributeValue);
    virtual void writeToFile();

  private:
    std::string		mPath;
    eOpen		mOpenType;
    QDomDocument	mDocument;
    QDomElement		mRootNode;
  };

} // End of namespace Babe


#endif		// !__BABE_XMLDOCUMENTQTXMLIMPL_HPP__
