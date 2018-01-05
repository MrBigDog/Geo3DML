#include "SpatialRelationXMLReader.h"
#include "Spatialrelation.h"
#include "FeatureClass.h"
#include "FeatureRelation.h"

#include <fstream>
#include "iconv.h"
#include <string>

SpatialRelationXMLReader::SpatialRelationXMLReader()
{
	SpatialRelation_=NULL;
}
SpatialRelationXMLReader::~SpatialRelationXMLReader()
{
	if(SpatialRelation_->getContainer()==NULL)
		delete SpatialRelation_;
}

gml::AbstractGML* SpatialRelationXMLReader::GetSpatialRelation()
{
	return SpatialRelation_;
}

///@brief �½�һ��SpatialRelationΪSpatialRelation_
///@author yang hongjun
///@date 2013.11.13
void SpatialRelationXMLReader::CreateSpatialRelation()
{
	if(!SpatialRelation_)
	SpatialRelation_=new gmml::SpatialRelation;
}


///@brief ����SpatialeRelation�ڵ�
///@param  spatialrelationNodeΪSpatialrelation�Ľڵ�
///@author yang hongjun
///@date 2013.11.13
bool SpatialRelationXMLReader::ReadSpatialRelation(xmlNode* spatialrelationNode)
{
	xmlNodePtr curNode;
	curNode=spatialrelationNode;
	xmlNodePtr NodePtr_replica=curNode;
	xmlChar* tmp_str;
	gmml::SpatialRelation* spatialrelation=NULL;
	CreateSpatialRelation();
	spatialrelation=(gmml::SpatialRelation*)SpatialRelation_;

	while (curNode!=NULL)
	{
		///@brief ��ȡSpatialRelation��id
		///@author yang hongjun
		///@date 2013.11.13
		xmlAttrPtr attrPtr=curNode->properties;
		if(!xmlStrcmp(attrPtr->name, BAD_CAST "id"))
		{
			xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "id");
			char* out = 0;
			if(std::string(mXMLCoding) == "gb2312")
			  out =  ConvertEnc("utf-8","gb2312", (char*)attr_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)tmp_str);

				spatialrelation->setID(sr);

			xmlFree(attr_str);                                             
		}	

		///@brief ��ȡ�ڵ��name
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"name"))
		{
			tmp_str=xmlNodeGetContent(curNode);
			char *out=0;
			if(std::string(mXMLCoding) == "gb2312")
			  out=ConvertEnc("utf-8","gb2312", (char*)tmp_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)tmp_str);

				spatialrelation->setName(sr);

			xmlFree(tmp_str);
		}

		///@brief ��ȡ�ڵ��relationship
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"relationship"))
		{
			tmp_str=xmlNodeGetContent(curNode);
			int left_count = TrimLeft((char*)tmp_str);
			int right_count = TrimRight((char*)tmp_str);
			int len = strlen((char*)tmp_str);
			std::string value = (char*)tmp_str;
			value = value.substr(left_count, len-left_count-right_count);
			spatialrelation->setRelationship(value);
			xmlFree(tmp_str);
		}

		///@brief ��ȡ�ڵ��sourceRole
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"sourceRole"))
		{
			tmp_str=xmlNodeGetContent(curNode);
			int left_count = TrimLeft((char*)tmp_str);
			int right_count = TrimRight((char*)tmp_str);
			int len = strlen((char*)tmp_str);
			std::string value = (char*)tmp_str;
			value = value.substr(left_count, len-left_count-right_count);
			spatialrelation->setSourceRole(value);
			xmlFree(tmp_str);
		}

		///@brief��ȡ�ڵ��targetRole
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"targetRole"))
		{
			tmp_str=xmlNodeGetContent(curNode);
			int left_count = TrimLeft((char*)tmp_str);
			int right_count = TrimRight((char*)tmp_str);
			int len = strlen((char*)tmp_str);
			std::string value = (char*)tmp_str;
			value = value.substr(left_count, len-left_count-right_count);
			//spatialrelation->addTargetRole(value);
			xmlFree(tmp_str);
		}

		/// ��ȡ�ڵ��relatedFeature
		if(!xmlStrcmp(curNode->name,(const xmlChar*)"relatedFeature"))
		{
			xmlAttrPtr attrPtr=curNode->properties;
			while(attrPtr)
			{
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "type"))
				{
					xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "type");
					xmlFree(attr_str);
				}

				/// ��relatedFeature��id��ʱ����������
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "href"))
				{
					xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "href");
					char* out = 0;
					std::string sr;
					if(std::string(mXMLCoding) == "gb2312")
						out =  ConvertEnc("utf-8","gb2312", (char*)attr_str);
					if (out)
						sr=std::string((char*)out);
					else
						sr=std::string((char*)attr_str);

					if(sr.find("#")>=0)                   ///@��ΪrelatedFeature��id�Ŀ�ͷ�Ǵ���#��
						sr = sr.substr(1,sr.size()-1);

					gmml::GeologicFeatureClass *fl = new gmml::GeologicFeatureClass;
					fl->setID(sr);
					fl->setContainer(spatialrelation);

					/*spatialrelation->SetFeatureClass(fl); */  ///@param ��SpatialRelation��δ��ȫ�����
					xmlFree(attr_str);                                             

				}			 

				attrPtr->next;
				
			 }

		 }
		curNode=curNode->next;

	 }
	 return true;

 }