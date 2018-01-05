#include "MetaDataXMLReader.h"
#include "Geo3DProject.h"
#include "Geo3DMap.h"
#include "Geo3DProjectMetaData.h"
#include "Geo3DMapMetaData.h"
#include "GeoModelMetaData.h"
#include "GeoModel.h"
///@brief ���캯��
MetaDataXMLReader::MetaDataXMLReader(void)
{

}

///@brief ��������
MetaDataXMLReader::~MetaDataXMLReader(void)
{

}

///@brief  ��ȡGeoProject��Ԫ����
///@param  Geo3DProject* geoproject ��Ԫ���ݶ�Ӧ��Geo3DProject
///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
///@return 
///@author zhaowei
///@date   2013.11.1
void MetaDataXMLReader::ReadGeoProjectMetaData(gmml::Geo3DProject* geoproject, xmlNode* metadataNode)
{
	std::string ChildrenNodeNames[]={
		"Name",\
		"Description",\
		"Field"\
	};

	int ChildrenNodeNamesCount = 3;

	xmlNodePtr curNode;		//��ǰ���
	curNode = metadataNode;	//����ǰ��㸳ֵ
	xmlNodePtr curNode_replica = curNode;	//Ϊ��ǰ��㱣��һ�ݸ���
	xmlChar* tmp_string;	//��ʱ�ַ�������
	gmml::Geo3DProjectMetaData* metadata = geoproject->GetGeoProjectMetaData();

	if(!xmlStrcmp(curNode->name, (const xmlChar*)"Metadata"))
	{
		xmlNodePtr curChildNode = curNode->xmlChildrenNode;
		while(curChildNode && metadata)
		{
			//��ȡԪ�����еĸ����ֶΡ���ΪXML�ļ��и�����ǩ��λ��˳����Եߵ���������Ҫ����һ�������ǩ��
			for(int i = 0; i < ChildrenNodeNamesCount; i++)
			{
				if(!xmlStrcmp(curChildNode->name, (const xmlChar*)ChildrenNodeNames[i].c_str()))
				{				
					tmp_string = xmlNodeGetContent(curChildNode);
					//���ֶ������еĿհ��ַ������
					int left_count = TrimLeft((char*)tmp_string);
					int right_count = TrimRight((char*)tmp_string);
					int len = strlen((char*)tmp_string);
					std::string value = (char*)tmp_string;
					value = value.substr(left_count, len-left_count-right_count);

					AttributeValue curNodeValue;
					curNodeValue.fieldName = ChildrenNodeNames[i];
					curNodeValue.fieldValue = value; 

					metadata->AddAttributeValue(curNodeValue);
					xmlFree(tmp_string);
					
				}
			}			

			//�����ǰ������һ���Ϊtext��ǩ��������
			curChildNode = curChildNode->next;
			if ((xmlStrcmp(curChildNode->name, (const xmlChar *)"text"))) 
				curChildNode = curChildNode->next;
		}
	}
}


///@brief  ��ȡGeoMap��Ԫ����
///@param  Geo3DMap* geomap ��Ԫ���ݶ�Ӧ��Geo3DMap
///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
///@return 
///@author zhaowei
///@date   2013.11.1
void MetaDataXMLReader::ReadGeoMapMetaData(gmml::Geo3DMap* geomap, xmlNode* metadataNode)
{
	std::string ChildrenNodeNames[]={
		"Name",\
		"Description",\
		"Owner",\
		"Date",\
		"ToolName",\
		"ToolVersion"
	};

	int ChildrenNodeNamesCount = 6;

	xmlNodePtr curNode;		//��ǰ���
	curNode = metadataNode;	//����ǰ��㸳ֵ
	xmlNodePtr curNode_replica = curNode;	//Ϊ��ǰ��㱣��һ�ݸ���
	xmlChar* tmp_string;	//��ʱ�ַ�������
	gmml::Geo3DMapMetaData* metadata = geomap->GetGeoMapMetaData();

	if(!xmlStrcmp(curNode->name, (const xmlChar*)"Metadata"))
	{
		xmlNodePtr curChildNode = curNode->xmlChildrenNode;
		while(curChildNode && metadata)
		{
			//��ȡԪ�����еĸ����ֶΡ���ΪXML�ļ��и�����ǩ��λ��˳����Եߵ���������Ҫ����һ�������ǩ��
			for(int i = 0; i < ChildrenNodeNamesCount; i++)
			{
				if(!xmlStrcmp(curChildNode->name, (const xmlChar*)ChildrenNodeNames[i].c_str()))
				{				
					tmp_string = xmlNodeGetContent(curChildNode);
					//���ֶ������еĿհ��ַ������
					int left_count = TrimLeft((char*)tmp_string);
					int right_count = TrimRight((char*)tmp_string);
					int len = strlen((char*)tmp_string);
					std::string value = (char*)tmp_string;
					value = value.substr(left_count, len-left_count-right_count);

					AttributeValue curNodeValue;
					curNodeValue.fieldName = ChildrenNodeNames[i];
					curNodeValue.fieldValue = value; 

					metadata->AddAttributeValue(curNodeValue);
					xmlFree(tmp_string);

					
				}
			}			

			//�����ǰ������һ���Ϊtext��ǩ��������
			curChildNode = curChildNode->next;
			if ((xmlStrcmp(curChildNode->name, (const xmlChar *)"text"))) 
				curChildNode = curChildNode->next;
		
		}
	}
}

///@brief  ��ȡGeoModel��Ԫ����
///@param GeoModel* geomodel ��Ԫ���ݶ�Ӧ��GeoModel
///@param xmlNode* metadataNode ��Ԫ�������ڵ�XML���
///@return 
///@author yang hongjun zhaowei
///@date   2013.11.10	2013.11.20
void MetaDataXMLReader::ReadGeoModelMetaData(gmml::GeoModel* geomodel, xmlNode* metadataNode)
{
	/*
	std::string ChildrenNodeNames[]={
		"Contact",\
		"dateStamp",\
		"identificationInfo",\
		"Description",\
		"ToolName",\
		"ToolVersion"
	};

	int ChildrenNodeNamesCount = 6;
	*/
	xmlNodePtr curNode;		//��ǰ���
	curNode = metadataNode;	//����ǰ��㸳ֵ
	xmlNodePtr curNode_replica = curNode;	//Ϊ��ǰ��㱣��һ�ݸ���
	xmlChar* tmp_str;	//��ʱ�ַ�������
	gmml::GeoModelMetaData* metadata = geomodel->GetGeoModelMetaData();

	if(!xmlStrcmp(curNode->name, (const xmlChar*)"Metadata"))
	{
		xmlNodePtr curChildNode = curNode->xmlChildrenNode;
		while(curChildNode && metadata)
		{
			int n = 0;
			if(curChildNode->name)
				n = strlen((char*)curChildNode->name);
			if(n && xmlStrcmp( curChildNode->name, (const xmlChar *)"text"))
			{
				std::string value = "";
				
				tmp_str = xmlNodeGetContent(curChildNode);
				char* out = NULL;

				int left_count, right_count, len;
				if(std::string(mXMLCoding) == "UTF-8")
					out = ConvertEnc("UTF-8","GB2312", (char*)tmp_str);
				if(out)
				{
					left_count = TrimLeft(out);
					right_count = TrimRight(out);
					len = strlen(out);
					value = (std::string)out;
				}
				else
				{
					left_count = TrimLeft((char*)tmp_str);
					right_count = TrimRight((char*)tmp_str);
					len = strlen((char*)tmp_str);
					value = (std::string)((char*)tmp_str);
				}					

				value = value.substr(left_count, len-left_count-right_count);
				
				AttributeValue curNodeValue;
				curNodeValue.fieldName = (std::string)((char*)curChildNode->name);
				curNodeValue.fieldValue = value; 
				metadata->AddAttributeValue(curNodeValue);
			
				xmlFree(tmp_str);
			} 
		   curChildNode = curChildNode->next;
		}
	}

}
