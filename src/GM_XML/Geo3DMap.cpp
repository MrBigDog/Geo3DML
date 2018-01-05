#include "Geo3DMap.h"
#include "Geo3DMapMetaData.h"
#include "Geo3DLayer.h"

using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.07
Geo3DMap::Geo3DMap(void)
{
	metaData = new Geo3DMapMetaData;
}

///@brief ��������
///@author zhaowei
///@date   2013.11.07
Geo3DMap::~Geo3DMap(void)
{
	deleteMembers();

}

///@brief ��ȡGeoMap��Ӧ��Ԫ����
///@param 
///@return ����ָ��Geo3DMapMetaData��ָ��
///@author zhaowei
///@date   2013.11.01
Geo3DMapMetaData* Geo3DMap::GetGeoMapMetaData()
{
	return metaData;
}


///@brief  ����GeoMap��Ӧ��Ԫ����
///@param  value �����õ�Ԫ����
///@return
///@author zhaowei
///@date   2013.11.08
void Geo3DMap::SetGeoMapMetaData(Geo3DMapMetaData* value)
{
	value->setContainer(this);
	metaData = value;
}

///@name ����ͼ�е�ͼ�㡣
//@{
///@brief  ȡ����ͼ����������ͼ�����Ŀ��
///@return ���ص���ͼ��������ͼ�����Ŀ��
///@author zhaowei
///@date   2013.11.07
int Geo3DMap::GetGeo3DLayerCount()
{
	int layer_count = geo3DLayers.size();
	return layer_count;
}

///@brief  ȡ����ͼ�е�ͼ�㡣
///@param i ͼ���ڵ���ͼ�е������ţ���0��ʼ����
///@return ָ����ͼ�㡣������ָ����ָ�������ڴ��ɱ�������������ָ����ͼ�㲻���ڣ��򷵻�0.
///@author zhaowei
///@date   2013.11.07
Geo3DLayer* Geo3DMap::GetLayer(int i)
{
	if(i < 0 || i >= geo3DLayers.size())
		return NULL;
	Geo3DLayer* geo_layer = geo3DLayers[i];
	return geo_layer;
}
//@}

///@brief  ��ȡȫ���ĵ���ͼ��
///@param  geo_layers ��Ϊ���ò���������ȡ����ȫ������ͼ��
///@return 
///@author zhaowei
///@date   2013.11.08
void Geo3DMap::GetAllGeoLayer(std::vector<Geo3DLayer*>& geo_layers)
{
	geo_layers = geo3DLayers;
}

///@brief  ȡ����ͼ��������Ϣ��
///@return ���ص���ͼ�����͡�
///@author zhaowei
///@date   2013.11.07
std::string Geo3DMap::GetType()
{
	return geoMapType;
}

///@brief  ���õ���ͼ����
///@param  mapType ����ͼ����ֵ
///@return
///@author zhaowei
///@date   2013.11.07
void Geo3DMap::SetType(const std::string& mapType)
{
	geoMapType = mapType;
}

///@brief  ��ӵ���ͼ��
///@param  value ����ӵĵ���ͼ��
///@return
///@author zhaowei
///@date   2013.11.07
void Geo3DMap::AddGeoLayer(Geo3DLayer* value)
{
	value->setContainer(this);
	geo3DLayers.push_back(value);
}

///@brief  ��ȡGeoMap��������Ŀ
///@param  
///@return ����GeoMap��������Ŀ
///@author zhaowei
///@date   2013.11.07
int Geo3DMap::GetAttributeValueCount()
{
	int attribute_count = attributeValues.size();
	return attribute_count;
}

///@brief  ��ȡ����ͼ�е�i������
///@param  i ���i����0��ʼ������
///@return ������i��Ч�����ص�i�����ԣ����򷵻��������ƺ�����ֵ��Ϊ�յ�����
///@author zhaowei
///@date   2013.11.07
AttributeValue Geo3DMap::GetAttributeValue(const int& i)
{
	if(i < 0 || i >= attributeValues.size())
	{
		AttributeValue v;
		v.fieldName = "";
		v.fieldValue = "";
		return v;
	}
	AttributeValue attr_value = attributeValues[i];
	return attr_value;
}

///@brief  ��ȡ��������Ϊfieldname�������ֶ�
///@param  fieldname ��������
///@return �������������Ч���򷵻ض�Ӧ�����ԣ����򷵻��������ƺ�����ֵ��Ϊ�յ�����
///@author zhaowei
///@date   2013.11.07
AttributeValue Geo3DMap::GetAttributeValue(const std::string& fieldname)
{
	AttributeValue v;
	if(fieldname.empty())
	{
		v.fieldName = "";
		v.fieldValue = "";
	}
	else
	{
		for(int i = 0; i < attributeValues.size(); i++)
		{
			if(attributeValues[i].fieldName == fieldname)
			{
				v = attributeValues[i];
				break;
			}
		}
	}
	return v;
}

///@brief  ��AttributeValue����������µ�Ԫ��
///@param const AttributeValue& value ����ӵ���Ԫ��
///@return 
///@author zhaowei
///@date   2013.11.05
void Geo3DMap::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void Geo3DMap::deleteMembers()
{
	if(metaData)
		delete metaData;
	metaData = NULL;

	for(std::vector<Geo3DLayer*>::size_type i = 0; i < geo3DLayers.size(); i++)
	{
		if(geo3DLayers[i]->getContainer() == this)
		{
			delete geo3DLayers[i];
		}
	}
	geo3DLayers.clear();
}