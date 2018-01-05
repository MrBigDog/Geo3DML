#include "GeoStyleXMLReader.h"
#include "Geo3DStyle.h"
#include <libxml/parser.h>//"parser.h"//  [1/5/2018 BigDog]
#include <fstream>
#include "iconv.h"
#include <string>

GeoStyleXMLReader::GeoStyleXMLReader(void)
{
	GeoStyle_=0;
}


GeoStyleXMLReader::~GeoStyleXMLReader(void)
{
	if(GeoStyle_)
		delete GeoStyle_;
}

///@brief ��ȡGeoStyle����
///@params 
///@author yang hongjun
///data 2013.11.09
gml::AbstractGML* GeoStyleXMLReader::GetGeoStyle()
{
	return GeoStyle_;
}

///@brief ����һ���µ�GeoStyle����
///@params
///@author yang hongjun
///@data 2013.11.09
void GeoStyleXMLReader::CreateGeoStyle()
{
	
	GeoStyle_=new gmml::Geo3DStyle;
}

///@brief ����GeoStyle
///@params geolayer�����ϲ��layer,geostyleNode�����ϲ��Geo3DLayer�е�GeoStyle�Ľڵ�ָ�� 
        ///�����ɹ�����true�����򷵻�false
///@author yang hongjun
///@data 2013.11.09
bool GeoStyleXMLReader::ReadGeoStyle(xmlNode* geostyleNode)
{
	xmlNodePtr curNode=geostyleNode;
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr NodePtr_replica = curNode;
	xmlChar* tmp_str;
	CreateGeoStyle();
	gmml::Geo3DStyle* style=(gmml::Geo3DStyle*)GeoStyle_;

	while(curNode!=NULL)
	{
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))///@brief GeoStyle�а���name�ڵ㣬
			                                                 ///��������ȡ���洢��GeoStyle��Ӧ��λ��
		{
			    tmp_str=xmlNodeGetContent(curNode);
				char* out=ConvertEnc("utf-8","gb2312", (char*)tmp_str);
				if(out)
					style->setName(out);
				else
				    style->setName((char*)tmp_str);
				     
			
			xmlFree(tmp_str);
		}

		///@brief ��ȡFeatureTypeStyle
		///@params ��Ϊͷ�ļ���û��FeatureTypeStyle���������Ͷ��壬���Ըöδ���ֻ����ʱ��
		///@author yang hongjun
		///@data 2013.11.09
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"FeatureTypeStyle"))
		{
			
			/*FeatureTypeStyleXMLReader FeatureTypeStyleReader;*////@params ��ʱ�Ե�FeatureTypeStyleXMLReader�ࣨδ����δ������
			/*if(style)
				FeatureTypeStyleReader.ReadFile(style,curNode);
				style->AddFeatureTypeStyle(FeatureTypeStyleReader.GetFeatureTypeStyle());*////@params ��ʱ�Ե�AddFeatureTypeStyle������δ����δ������
		}


		curNode=curNode->next;
	}

	return true;

}