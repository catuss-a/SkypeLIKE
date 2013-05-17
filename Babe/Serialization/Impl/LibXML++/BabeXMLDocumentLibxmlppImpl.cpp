//
// BabeXMLDocumentLibxmlppImpl.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 27 18:17:58 2011 alexandre champion
// Last update Mon Nov 28 22:17:42 2011 alexandre champion
//

#include "BabeXMLDocumentLibxmlppImpl.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{

  XMLDocumentLibxmlppImpl::XMLDocumentLibxmlppImpl(std::string const& filePath, eOpen openType)
    : mPath(filePath),
      mOpenType(openType),
      mParser(0),
      mRootNode(0),
      mDocument(0)
  {
    if (openType == READ)
      {
	mParser = new xmlpp::DomParser;
	mParser->set_substitute_entities();
	try
	  {
	    mParser->parse_file(filePath);
	    mDocument = mParser->get_document();
	    mRootNode = mDocument->get_root_node();
	  }
	catch (xmlpp::internal_error const&)
	  {
	    mDocument = new xmlpp::Document;
	    mRootNode = mDocument->create_root_node("document");
	  }
      }
    else if (openType == CREATE)
      {
	mDocument = new xmlpp::Document;
	mRootNode = mDocument->create_root_node("document");
      }
  }

  XMLDocumentLibxmlppImpl::~XMLDocumentLibxmlppImpl()
  {
    delete mParser;
    delete mDocument;
  }

  XMLDocumentLibxmlppImpl::AttributeMap XMLDocumentLibxmlppImpl::getNodeAttributes(std::string const& nodeName)
  {
    xmlpp::Element* elem = dynamic_cast<xmlpp::Element*>(getNodeByName(nodeName));
    XMLDocumentLibxmlppImpl::AttributeMap attr;
    if (!elem)
      return attr;
    return getAttributes(elem);
  }

  XMLDocumentLibxmlppImpl::AttributeMapVector XMLDocumentLibxmlppImpl::getNodeListAttributes(std::string const& parentNodeName, std::string const& nodeName)
  {
    AttributeMapVector Attributes;
    ElemVector elemVector = getNodeListByName(parentNodeName, nodeName);
    for (ElemVector::iterator i = elemVector.begin(); i != elemVector.end(); ++i)
      Attributes.push_back(getAttributes(*i));
    return Attributes;
  }

  XMLDocumentImpl::Element* XMLDocumentLibxmlppImpl::addNodeToRoot(std::string const& nodeName)
  {
    if (!nodeName.empty())
      return new ElementLibxmlpp(mRootNode->add_child(nodeName));
    return 0;
  }

  XMLDocumentImpl::Element* XMLDocumentLibxmlppImpl::addNode(XMLDocumentImpl::Element* parentNode, std::string nodeName)
  {
    if (!parentNode)
      return addNodeToRoot(nodeName);
    ElementLibxmlpp* parent;
    if (!(parent = dynamic_cast<ElementLibxmlpp*>(parentNode)))
      return 0;
    xmlpp::Element* child = parent->get()->add_child(nodeName);
    return new ElementLibxmlpp(child);
  }

  XMLDocumentLibxmlppImpl::AttributeMap XMLDocumentLibxmlppImpl::getNodeAttributes(XMLDocumentImpl::Element* node)
  {
	  XMLDocumentLibxmlppImpl::AttributeMap attr;
	  ElementLibxmlpp* elem;
	  if (!(elem = dynamic_cast<ElementLibxmlpp*>(node)))
		  return attr;
	  return getAttributes(elem->get());
  }

  XMLDocumentLibxmlppImpl::Element* XMLDocumentLibxmlppImpl::getNodeByAttribute(std::string const&, std::string const&, std::string const&, std::string const&)
  {
	  LOGE("XMLDocumentLibxmlppImpl::getNodeByAttribute not implemented !");
	  return 0; 
  }

  void XMLDocumentLibxmlppImpl::setValue(XMLDocumentImpl::Element* node, std::string const& value)
  { 
    ElementLibxmlpp* elem;
    if (!(elem = dynamic_cast<ElementLibxmlpp*>(node)))
      return ;
    elem->get()->add_child_text(value);
  }

  void XMLDocumentLibxmlppImpl::addAttribute(XMLDocumentImpl::Element* node, std::string const& attributeName, std::string const& attributeValue)
  {
    ElementLibxmlpp* elem;
    if (!(elem = dynamic_cast<ElementLibxmlpp*>(node)))
      return ;
    elem->get()->set_attribute(attributeName, attributeValue);    
  }

  void XMLDocumentLibxmlppImpl::writeToFile()
  {
    mDocument->write_to_file(mPath);
  }

  xmlpp::Node* XMLDocumentLibxmlppImpl::getNodeByNameTR(xmlpp::Node* node, std::string const& searchedNode)
  {
    const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
    const std::string nodeName = node->get_name();
    if (nodeName == searchedNode)
      return node;
    if(!nodeContent)
      {
	xmlpp::Node::NodeList list = node->get_children();
	for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
	  {
	    xmlpp::Node* foundNode = getNodeByNameTR(*iter, searchedNode);
	    if (foundNode)
	      return foundNode;
	  }
      }
    return 0;
  }

  xmlpp::Node* XMLDocumentLibxmlppImpl::getNodeByName(std::string const& nodeName)
  {
    return getNodeByNameTR(mRootNode, nodeName);
  }
  
  xmlpp::Element* XMLDocumentLibxmlppImpl::getNodeElemByName(std::string const& nodeName)
  {
    if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(getNodeByName(nodeName)))
      return nodeElement;
    else
      return 0;
  }
  
  XMLDocumentLibxmlppImpl::ElemVector XMLDocumentLibxmlppImpl::getNodeListByName(std::string const& parentNodeName, std::string const& searchedNode)
  {
    xmlpp::Node* node = getNodeByName(parentNodeName);
    ElemVector elementVector;
    if (node)
      {
	xmlpp::Node::NodeList list = node->get_children();
	for(xmlpp::Node::NodeList::iterator i = list.begin(); i != list.end(); ++i)
	  {
	    const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(*i);
	    const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(*i);
	    const Glib::ustring nodeName = (*i)->get_name();
	    if(!nodeText && !nodeComment && !nodeName.empty())
	      {
		if (nodeName == searchedNode)
		  {
		    if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(*i))
		      elementVector.push_back(nodeElement);
		  }
	      }
	  }
      }
    else
      {
	//throw std::runtime_error("XMLDocumentLibxmlppImpl::getNodeListByName : No such node \"" + parentNodeName + "\" in file " + mPath);
	LOGE("XMLDocumentLibxmlppImpl::getNodeListByName : No such node \"" + parentNodeName + "\" in file " + mPath);
      }
    return elementVector;
  }

  XMLDocumentLibxmlppImpl::AttributeMap XMLDocumentLibxmlppImpl::getAttributes(xmlpp::Element* element)
  {
    AttributeMap	attributeMap;
    const xmlpp::Element::AttributeList& attributes = element->get_attributes();
    for(xmlpp::Element::AttributeList::const_iterator i = attributes.begin(); i != attributes.end(); ++i)
      {
	const xmlpp::Attribute* curAtr = *i;
	attributeMap[curAtr->get_name()] = curAtr->get_value();
      }
    return attributeMap;
  }

  XMLDocumentLibxmlppImpl::AttributeMap XMLDocumentLibxmlppImpl::childrenToAttributeMap(xmlpp::Element* element)
  {
    AttributeMap	attributeMap;
    if (element)
      {
	xmlpp::Node::NodeList list = element->get_children();
	for(xmlpp::Node::NodeList::iterator i = list.begin(); i != list.end(); ++i)
	  {
	    const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(*i);
	    const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(*i);
	    const Glib::ustring nodeName = (*i)->get_name();
	    if(!nodeText && !nodeComment && !nodeName.empty())
	      {
		if(xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(*i))
		  attributeMap[nodeElement->get_name()] = nodeElement->get_child_text()->get_content();
	      }
	  }
      }
    return attributeMap;
  }

  std::string const& XMLDocumentLibxmlppImpl::getPath() const
  {
    return mPath;
  }
  
} // End of namespace Babe
