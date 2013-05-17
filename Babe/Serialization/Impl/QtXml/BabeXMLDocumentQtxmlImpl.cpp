//
// BabeXMLDocumentQtxmlImpl.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 27 19:14:13 2011 alexandre champion
// Last update Thu Dec  1 22:53:17 2011 alexandre champion
//

#include "BabeXMLDocumentQtxmlImpl.hpp"
#include "BabeLogManager.hpp"

#include <QFile>
#include <QTextStream>

namespace Babe
{

  XMLDocumentQtxmlImpl::XMLDocumentQtxmlImpl(std::string const& filePath, eOpen openType)
    : mPath(filePath),
      mOpenType(openType)
  {
    if (openType == READ)
      {
	QFile inFile(QString::fromStdString(filePath));
	if(inFile.open(QIODevice::ReadOnly | QIODevice::Text))
	  {
	    if(!mDocument.setContent(&inFile))
	      LOGE("Failed to parse the file into a DOM tree.");
	    else
	      mRootNode = mDocument.documentElement();
	    inFile.close();
	  }
	else
	  {
	    LOGE("file doesnt exist : \"" + filePath + "\"");
	    mRootNode = mDocument.createElement("document");
	    mDocument.appendChild(mRootNode);
	  }
      }
    else if (openType == CREATE)
      {
	mRootNode = mDocument.createElement("document");
	mDocument.appendChild(mRootNode);
      }
  }

  XMLDocumentQtxmlImpl::~XMLDocumentQtxmlImpl()
  {
  }

  XMLDocumentQtxmlImpl::AttributeMap XMLDocumentQtxmlImpl::getNodeAttributes(std::string const& nodeName)
  {
    XMLDocumentQtxmlImpl::AttributeMap atrMap;
    QDomNodeList elements = mDocument.elementsByTagName(QString::fromStdString(nodeName));
    if(elements.size() >= 1)
      {
	QDomElement elem = elements.item(0).toElement();
	QDomNamedNodeMap atrs = elem.attributes();
	for (int i = 0; i != atrs.size(); ++i)
	  {
	    QDomAttr atr = atrs.item(i).toAttr();
	    atrMap[atr.name().toStdString()] = atr.value().toStdString();
	  }
      }
    return atrMap;
  }

  XMLDocumentQtxmlImpl::AttributeMapVector XMLDocumentQtxmlImpl::getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName)
  {
    XMLDocumentQtxmlImpl::AttributeMapVector atrMapVector;
    QDomNodeList elemParent = mDocument.elementsByTagName(QString::fromStdString(parentNodeName));
    if (elemParent.size() >= 1)
      {
	QDomNodeList elements = mDocument.elementsByTagName(QString::fromStdString(nodeName));
	for (int i = 0; i != elements.size(); ++i)
	  {
	    XMLDocumentQtxmlImpl::AttributeMap atrMap;
	    QDomElement elem = elements.item(i).toElement();
	    QDomNamedNodeMap atrs = elem.attributes();
	    for (int i = 0; i != atrs.size(); ++i)
	      {
		QDomAttr atr = atrs.item(i).toAttr();
		atrMap[atr.name().toStdString()] = atr.value().toStdString();
	      }
	    atrMapVector.push_back(atrMap);
	  }
      }
    return atrMapVector;
  }

  XMLDocumentImpl::Element* XMLDocumentQtxmlImpl::addNodeToRoot(std::string const& nodeName)
  {
    if (!nodeName.empty())
      {
	QDomElement child = mDocument.createElement(QString::fromStdString(nodeName));
	mRootNode.appendChild(child);
	return new ElementQtxml(child);
      }
    return 0;
  }

  XMLDocumentImpl::Element* XMLDocumentQtxmlImpl::addNode(XMLDocumentImpl::Element* parentNode, std::string nodeName)
  {
    if (!parentNode)
      return addNodeToRoot(nodeName);
    ElementQtxml* parent;
    if (!(parent = dynamic_cast<ElementQtxml*>(parentNode)))
      return 0;
    QDomElement child = mDocument.createElement(QString::fromStdString(nodeName));
    parent->get().appendChild(child);
    return new ElementQtxml(child);
  }

  XMLDocumentImpl::AttributeMap XMLDocumentQtxmlImpl::getNodeAttributes(XMLDocumentImpl::Element* node)
  {
    XMLDocumentQtxmlImpl::AttributeMap atrMap;
    ElementQtxml* elem;
    if (!(elem = dynamic_cast<ElementQtxml*>(node)))
      return atrMap;
    QDomNamedNodeMap atrs = elem->get().attributes();
    for (int i = 0; i != atrs.size(); ++i)
      {
	QDomAttr atr = atrs.item(i).toAttr();
	atrMap[atr.name().toStdString()] = atr.value().toStdString();
      }
    return atrMap;
  }

  XMLDocumentImpl::Element* XMLDocumentQtxmlImpl::getNodeByAttribute(std::string const& parentNodeName, std::string const& nodeName, std::string const& attributeName, std::string const& attributeValue)
  {
    QDomNodeList elemParent = mDocument.elementsByTagName(QString::fromStdString(parentNodeName));
    if (elemParent.size() >= 1)
      {
	QDomNodeList elements = mDocument.elementsByTagName(QString::fromStdString(nodeName));
	for (int i = 0; i != elements.size(); ++i)
	  {
	    QDomElement elem = elements.item(i).toElement();
	    QDomNamedNodeMap atrs = elem.attributes();
	    for (int i = 0; i != atrs.size(); ++i)
	      {
		QDomAttr atr = atrs.item(i).toAttr();
		if (atr.name().toStdString() == attributeName && atr.value().toStdString() == attributeValue)
		  return new ElementQtxml(elem);
	      }
	  }
      }
    return 0;
  }

  void XMLDocumentQtxmlImpl::setValue(XMLDocumentImpl::Element* node, std::string const& value)
  {
    ElementQtxml* elem;
    if (!(elem = dynamic_cast<ElementQtxml*>(node)))
      return ;
    QDomText txt = mDocument.createTextNode(QString::fromStdString(value));
    elem->get().appendChild(txt);
  }
  
  void XMLDocumentQtxmlImpl::addAttribute(XMLDocumentImpl::Element* node, std::string const& attributeName, std::string const& attributeValue)
  {
    ElementQtxml* elem;
    if (!(elem = dynamic_cast<ElementQtxml*>(node)))
      return ;
    elem->get().setAttribute(QString::fromStdString(attributeName), QString::fromStdString(attributeValue));
  }

  void XMLDocumentQtxmlImpl::writeToFile()
  {
    QFile outFile(QString::fromStdString(mPath));
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
      {
	LOGE("XMLDocumentQtxmlImpl::writeToFile : Failed to open file for writing.");
	return ;
      }  
    QTextStream stream(&outFile);
    stream << mDocument.toString();
    outFile.close();
  }

} // End of namespace Babe
