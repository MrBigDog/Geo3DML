#include "FeatureRelationXMLReader.h"
#include "SpatialRelationXMLReader.h"
#include "FeatureRelation.h"
#include "SpatialRelation.h"
#include "GeologicRelation.h"


#include <fstream>
#include "iconv.h"
#include <string>
FeatureRelationXMLReader::FeatureRelationXMLReader(void)
{

	gmmlObject=NULL;
}

FeatureRelationXMLReader::~FeatureRelationXMLReader(void)
{

 
}

///@brief  �����µ�FeatureRelation����
///@param 
///@return 
///@author yang hongjun
///@date   2013.11.13
void FeatureRelationXMLReader::CreateRelationship(std::string RelationType)
{
	if(RelationType == "GeologicHistory")
	gmmlObject=new gmml::GeologicHistory;

	if(RelationType == "AggregationRelation")
	gmmlObject=new gmml::AggregationRelation;

	if(RelationType == "GeologicHistory")
	gmmlObject=new gmml::FeatureRelation;

	if(RelationType == "BoundaryRelation")
	gmmlObject=new gmml::BoundaryRelation;

	if(RelationType == "DefiningStructure")
	gmmlObject=new gmml::DefiningStructure;

	if(gmmlObject==0)
		gmmlObject = new gmml::FeatureRelation;
}

///@brief ��ȡFeatureRelation
///@param featurerelationNodeΪ��ǰFeatureRelation�ڵ�
///@return ����ɹ�����true ���򷵻�false
///@author yang hongjun
///@date 2013.11.14
bool FeatureRelationXMLReader::ReadNode  (xmlNode* curRelationNode)
{
	if(curRelationNode)
		if(!xmlStrcmp(curRelationNode->name,(const xmlChar*)"Relation"))
		{
			xmlNodePtr curcurRelationNodeChildNode=curRelationNode->xmlChildrenNode;
			while(curcurRelationNodeChildNode)
			{
				if(!xmlStrcmp(curcurRelationNodeChildNode->name,(const xmlChar*)"BoundaryRelationship"))
				{
					CreateRelationship("BoundaryRelation");
					

					gmml::FeatureRelation* boundaryrelationship=NULL;
					boundaryrelationship=(gmml::FeatureRelation*)gmmlObject;
					boundaryrelationship->setRelationship("BoundaryRelationship");

					ReadRelation(curcurRelationNodeChildNode);
				}
				else
				if(!xmlStrcmp(curcurRelationNodeChildNode->name,(const xmlChar*)"AggregationRelation"))
				{
					CreateRelationship("AggregationRelation");
					

					gmml::FeatureRelation* boundaryrelationship=NULL;
					boundaryrelationship=(gmml::FeatureRelation*)gmmlObject;
					boundaryrelationship->setRelationship("AggregationRelation");
					ReadRelation(curcurRelationNodeChildNode);
				}
				else
                if(!xmlStrcmp(curcurRelationNodeChildNode->name,(const xmlChar*)"GeologicHistory"))
				{
					CreateRelationship("GeologicHistory");
					

					gmml::FeatureRelation* boundaryrelationship=NULL;
					boundaryrelationship=(gmml::FeatureRelation*)gmmlObject;
					boundaryrelationship->setRelationship("GeologicHistory");
					ReadRelation(curcurRelationNodeChildNode);
				}
						else
                if(!xmlStrcmp(curcurRelationNodeChildNode->name,(const xmlChar*)"DefiningStructure"))
				{
					CreateRelationship("DefiningStructure");
					

					gmml::FeatureRelation* boundaryrelationship=NULL;
					boundaryrelationship=(gmml::FeatureRelation*)gmmlObject;
					boundaryrelationship->setRelationship("DefiningStructure");
					ReadRelation(curcurRelationNodeChildNode);
				}
				curcurRelationNodeChildNode=curcurRelationNodeChildNode->next;
			}

		}

	return true;
}
bool FeatureRelationXMLReader::ReadRelation(xmlNode* boundaryrelationshipNode)
{
	xmlNodePtr curNode=boundaryrelationshipNode;
	xmlNodePtr NodePtr_replica=curNode;
	xmlChar *tmp_str;
	
	gmml::FeatureRelation* boundaryrelationship=NULL;
	boundaryrelationship=(gmml::FeatureRelation*)gmmlObject;
	xmlAttrPtr attrPtr=curNode->properties;
	while(attrPtr)
	{
		if(!xmlStrcmp(attrPtr->name, BAD_CAST "id"))
		{
			xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "id");
			char* out = 0;
			if(std::string(mXMLCoding) == "UTF-8")
			   out =  ConvertEnc("UTF-8","GB2312", (char*)attr_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)attr_str);

				boundaryrelationship->setID(sr);

			xmlFree(attr_str);                                             
		}			 
		attrPtr=attrPtr->next;
	}
	

	curNode=curNode->xmlChildrenNode;
	while(curNode!=NULL)
	{
		//boundaryrelationship->setRelationship("AggregationRelation");
	
		if (!xmlStrcmp(curNode->name,(const xmlChar*)"Relationship"))
		{
          
			tmp_str=xmlNodeGetContent(curNode);
			char* out = 0;
			if(std::string(mXMLCoding) == "UTF-8")
				out = ConvertEnc("UTF-8","GB2312", (char*)tmp_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)tmp_str);
				boundaryrelationship->setRelationship(sr);
			
			xmlFree(tmp_str);

		}
		else
		if (!xmlStrcmp(curNode->name,(const xmlChar*)"name"))
		{
          
			tmp_str=xmlNodeGetContent(curNode);
			char* out = 0;
			if(std::string(mXMLCoding) == "UTF-8")
				out = ConvertEnc("UTF-8","GB2312", (char*)tmp_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)tmp_str);
				boundaryrelationship->setName(sr);
			
			xmlFree(tmp_str);

		}
		else
		///����Source�ڵ������
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"Source"))
		{
			xmlNodePtr SourceNode=curNode->xmlChildrenNode;
			while(SourceNode)
			{
				if(!xmlStrcmp(SourceNode->name,(const xmlChar*)"Feature"))
				{
					xmlAttrPtr attrPtr=SourceNode->properties; 
					while(attrPtr)
					{

						///��ȡ����type����
						if(!xmlStrcmp(attrPtr->name, BAD_CAST "type"))
						{
							xmlChar*attr_str = xmlGetProp(SourceNode, BAD_CAST "type");
							xmlFree(attr_str);
						}
						else
						///��ȡ����href����
						if(!xmlStrcmp(attrPtr->name, BAD_CAST "href"))
						{
							xmlChar*attr_str = xmlGetProp(SourceNode, BAD_CAST "href");
							char* out = 0;
							if(std::string(mXMLCoding) == "UTF-8")
								out = ConvertEnc("UTF-8","GB2312", (char*)attr_str);
							std::string sr;
							if (out)
								sr=std::string((char*)out);
							else
								sr=std::string((char*)attr_str);

								boundaryrelationship->setSourceRole(sr);

							xmlFree(attr_str);                                             
						}		
						attrPtr=attrPtr->next;
					}
				}
				SourceNode=SourceNode->next;
			}
			
		}	

		else
		///����Targets�ڵ������
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"Targets"))
		{
			xmlNodePtr TargetsNode=curNode->xmlChildrenNode;
			while(TargetsNode)
			{
				if(!xmlStrcmp(TargetsNode->name,(const xmlChar*)"Feature"))
				{
					xmlAttrPtr attrPtr=TargetsNode->properties;
					while(attrPtr)
					{
						///��ȡ����type����
						if(!xmlStrcmp(attrPtr->name, BAD_CAST "type"))
						{
							xmlChar* attr_str = xmlGetProp(TargetsNode, BAD_CAST "type");
							char* out = 0;
							if(std::string(mXMLCoding) == "UTF-8")
								out = ConvertEnc("UTF-8","GB2312", (char*)attr_str);
							xmlFree(attr_str);
						}
						else
						///��ȡ����href����
						if(!xmlStrcmp(attrPtr->name, BAD_CAST "href"))
						{
							 xmlChar* attr_str = xmlGetProp(TargetsNode, BAD_CAST "href");
							char* out = 0;
							if(std::string(mXMLCoding) == "UTF-8")
								out = ConvertEnc("UTF-8","GB2312", (char*)attr_str);
							std::string sr;
							if (out)
								sr=std::string((char*)out);
							else
								sr=std::string((char*)attr_str);

							if(sr.find("#")>=0)                   ///@��ΪTargets��id�Ŀ�ͷ�Ǵ���#��
								sr = sr.substr(1,sr.size()-1);
								boundaryrelationship->addTargetRole(sr);///��Ϊһ��Targets�����ж��Feature���ǲ���Ӧ����ջ�洢����
							xmlFree(attr_str);                                             
						}		
						attrPtr=attrPtr->next;
					}
				}
				TargetsNode=TargetsNode->next;
			}
		}
		curNode=curNode->next;
	}
	return true;
}
