#include "Geo3DLayerXMLReader.h"
#include "Geo3DLayer.h"
#include "FeatureClass.h"
#include "Geo3DStyleXMLReader.h"

#include <fstream>
#include "iconv.h"
#include <string>

Geo3DLayerXMLReader::Geo3DLayerXMLReader(void)
{
	GeoLayer_=0;
}
Geo3DLayerXMLReader::~Geo3DLayerXMLReader(void)
{
	if(GeoLayer_->getContainer() == NULL)
	   delete GeoLayer_;
}
///@brief ��ȡGeoLayer
///@retun ����GeoLayer ��ָ��
///@author yang hongjun
///@data 2013.11.07
gml::AbstractGML* Geo3DLayerXMLReader::GetGeoLayer()
{
	return GeoLayer_;
}
///@ brief ������GeoLayer
///@ author yang hongjun
///@data 2013.11.07
void Geo3DLayerXMLReader::CreateGeoLayer()
{
	GeoLayer_=new gmml::Geo3DLayer;
}

bool Geo3DLayerXMLReader::ReadGeoLayer(xmlNode* geolayerNode)
{

	xmlNodePtr curNode;      //������ָ��(����Ҫ��Ϊ���ڸ��������ƶ�)      
	curNode=geolayerNode;      //����Project�̳�����Geo3DMap��ָ�븳��curNode
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr NodePtr_replica = curNode;
	gmml::Geo3DLayer* layer = NULL;
	CreateGeoLayer();
	layer=(gmml::Geo3DLayer*)GeoLayer_;


	xmlAttrPtr attrPtr = curNode->properties;
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
				sr=std::string(out);
			else
				sr=std::string((char*)attr_str);
			layer->setID(sr);
			xmlFree(attr_str);                                             
		}			 
		attrPtr=attrPtr->next;			
	}



	while(curNode != NULL) 
	{		
		if ((!xmlStrcmp(curNode->name, (const xmlChar *)"name"))) 
		{
			xmlChar * tmp_str = xmlNodeGetContent(curNode);
			char* out =0; 
			if(std::string(mXMLCoding) == "UTF-8")
				out =  ConvertEnc("UTF-8","GB2312", (char*)tmp_str);
			std::string sr;
			if (out)
				sr=std::string((char*)out);
			else
				sr=std::string((char*)tmp_str);
			layer->setName(sr);

			xmlFree(tmp_str); 
		} 
		else
		//ȡ��Geo3DMap�ڵ��е�����
		if ((!xmlStrcmp(curNode->name, (const xmlChar *)"FeatureClass"))) 
		{	
			///@brief ȡ���������Խڵ������
			///@paramas type��hrefΪGeologicFeatureClass����������
			///@author yang hongjun
			///@data 2013.11.07
			NodePtr_replica = curNode;
			xmlAttrPtr attrPtr = NodePtr_replica->properties;
			while(attrPtr)
			{
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "type"))
				{
					xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "type");
					xmlFree(attr_str);
				}
				/// ��GeologicFeatureClass��id��ʱ����������
				/// yang hongjun
				/// 2013.11.10
				else
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "href"))
				{
					xmlChar* attr_str = xmlGetProp(NodePtr_replica, BAD_CAST "href");
					char* out = 0;
				
					if(std::string(mXMLCoding) == "UTF-8")
						out =  ConvertEnc("UTF-8","GB2312", (char*)attr_str);

					std::string sr;
					if (out)
						sr=std::string((char*)out);
					else
						sr=std::string((char*)attr_str);

					if(sr.find("#")>=0)                   ///@��ΪGeologicFeatureClass��id�Ŀ�ͷ�Ǵ���#��
						sr = sr.substr(sr.find("#")+1,sr.size()-1);

					gmml::GeologicFeatureClass *fl = new gmml::GeologicFeatureClass;
					fl->setID(sr);
					fl->setContainer(layer);

					layer->SetFeatureClass(fl);   
					xmlFree(attr_str);                                             
					
				 }			 

               attrPtr= attrPtr->next;
		    }	
		}

		///@brief ��ȡGeo3DStyle������
		///@param
		///@author yang hongjun
		///@date 2013.11.08
		else
		if((!xmlStrcmp(curNode->name, (const xmlChar *)"Styles"))) 
		{
			xmlNodePtr  StyleNode = curNode->xmlChildrenNode;
			while(StyleNode)
			{
				if((!xmlStrcmp(StyleNode->name, (const xmlChar *)"Style"))) 
				{
					xmlNodePtr  geo3dStyleNode = StyleNode->xmlChildrenNode;
					while(geo3dStyleNode)
					{
						if((!xmlStrcmp(geo3dStyleNode->name, (const xmlChar *)"Geo3DStyle"))) 
						{
							Geo3DStyleXMLReader Geo3DStyleReader;
							if(layer)
								Geo3DStyleReader.ReadGeo3DStyle(geo3dStyleNode);
							///@brief ��GeoLayer���뵽��GeoLayer��


							layer->SetStyle((gmml::Geo3DStyle*)Geo3DStyleReader.GetGeo3DStyle());//@param  ��֮ǰ�Ľڵ�����ж�����Add������غ�����
						}

						geo3dStyleNode = geo3dStyleNode->next;
					}
				}
				StyleNode = StyleNode->next;
			}		
		} 
		curNode = curNode->next; 
	} 
	return true;

}