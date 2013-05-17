
#include <stdexcept>
#include "BabeXMLDocument.hpp"
#include "BabeLogManager.hpp"
#if defined (BABE_XML_QT)
# include "BabeXMLDocumentQtxmlImpl.hpp"
#else
# include "BabeXMLDocumentLibxmlppImpl.hpp"
#endif // !BABE_XML_QT

namespace Babe
{

  XMLDocument::XMLDocument(std::string const& filePath, XMLDocumentImpl::eOpen openType)
  {
#if defined (BABE_XML_QT)
    mImpl = new XMLDocumentQtxmlImpl(filePath, openType);
    LOG("--Using QtXml for serialization (set define in \"Babe/BabeDef.hpp\")--");
#else
    mImpl = new XMLDocumentLibxmlppImpl(filePath, openType);
    LOG("--Using LibXML++ for serialization (set define in \"Babe/BabeDef.hpp\")--");
#endif // !BABE_XML_QT
  }

  XMLDocument::~XMLDocument()
  {
    delete mImpl;
  }

  XMLDocument::AttributeMap XMLDocument::getNodeAttributes(std::string const& nodeName)
  {
    return mImpl->getNodeAttributes(nodeName);
  }

  XMLDocument::AttributeMapVector XMLDocument::getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName)
  {
    return mImpl->getNodeListAttributes(parentNodeName, nodeName);
  }

  XMLDocumentImpl::Element* XMLDocument::addNodeToRoot(std::string const& nodeName)
  {
    return mImpl->addNodeToRoot(nodeName);
  }

  XMLDocumentImpl::Element* XMLDocument::addNode(XMLDocumentImpl::Element* parentNode, std::string nodeName)
  {
    return mImpl->addNode(parentNode, nodeName);
  }

  XMLDocument::AttributeMap XMLDocument::getNodeAttributes(XMLDocumentImpl::Element* node)
  {
	return mImpl->getNodeAttributes(node);
  }

  XMLDocumentImpl::Element* XMLDocument::getNodeByAttribute(std::string const& parentNodeName, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue)
  {
	return mImpl->getNodeByAttribute(parentNodeName, nodeName, attributeName, attributeValue);
  }

  void XMLDocument::setValue(XMLDocumentImpl::Element* node, std::string const& value)
  {
    mImpl->setValue(node, value);
  }

  void XMLDocument::addAttribute(XMLDocumentImpl::Element* node, std::string const& attributeName, std::string const& attributeValue)
  {
    mImpl->addAttribute(node, attributeName, attributeValue);
  }

  void XMLDocument::writeToFile()
  {
    mImpl->writeToFile();
  }

} // End of namespace Babe
