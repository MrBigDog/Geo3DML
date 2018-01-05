#include "XMLMetaDataReader.h"
#include "Geo3DProject.h"
#include "Geo3DMap.h"
#include "Geo3DProjectMetaData.h"
#include "Geo3DMapMetaData.h"

///@brief ���캯��
XMLMetaDataReader::XMLMetaDataReader(void)
{

}

///@brief ��������
XMLMetaDataReader::~XMLMetaDataReader(void)
{

}

///@brief  ��ȡGeoProject��Ԫ����
///@params Geo3DProject* geoproject ��Ԫ���ݶ�Ӧ��Geo3DProject
///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
///@return 
///@author zhaowei
///@date   2013.11.1
void XMLMetaDataReader::ReadGeoProjectMetaData(gmml::Geo3DProject* geoproject, xmlNode* metadataNode)
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

					break;
				}
			}			

			//�����ǰ������һ���Ϊtext��ǩ��������
			curNode = curNode->next;
			if ((xmlStrcmp(curNode->name, (const xmlChar *)"text"))) 
				curNode = curNode->next;
		}
	}
}


///@brief  ��ȡGeoMap��Ԫ����
///@params Geo3DMap* geomap ��Ԫ���ݶ�Ӧ��Geo3DMap
///        xmlNode* metadataNode ��Ԫ�������ڵ�XML���
///@return 
///@author zhaowei
///@date   2013.11.1
void XMLMetaDataReader::ReadGeoMapMetaData(gmml::Geo3DMap* geomap, xmlNode* metadataNode)
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

					break;
				}
			}			

			//�����ǰ������һ���Ϊtext��ǩ��������
			curNode = curNode->next;
			if ((xmlStrcmp(curNode->name, (const xmlChar *)"text"))) 
				curNode = curNode->next;
		}
	}
}
