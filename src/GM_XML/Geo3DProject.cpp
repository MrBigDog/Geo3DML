#include "Geo3DProject.h"
#include "Geo3DProjectMetaData.h"
#include "Geo3DMap.h"
#include "GeoModel.h"
#include "Geo3DLayer.h"
#include "GeoModel.h"
#include "featureclass.h"
#include "GeoSceneStyle.h"

using namespace gmml;

//////////////////////////////////////////////////////////////////////////////
///@brief  ���캯��
///@author zhaowei
///@date   2013.11.06
Geo3DProject::Geo3DProject(void)
{
	projectBoundary = NULL;
	pointCount = 0;
	metaData = new Geo3DProjectMetaData;
	metaData->setContainer(this);

	sceneStyle = new GeoSceneStyle;          ;
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.06
Geo3DProject::~Geo3DProject(void)
{
	if(sceneStyle)
		delete sceneStyle;
	deleteMembers();
}
 GeoSceneStyle*           Geo3DProject::GetSceneStyle()
 {
	 return sceneStyle;
 }
void Geo3DProject::setDescription(std::string d)
{
	projDescription = d;
}
std::string Geo3DProject::getDescription()
{
	return projDescription;
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void Geo3DProject::deleteMembers()
{
	delete metaData;
	metaData = NULL;
	if(projectBoundary)
		delete[] projectBoundary;
	projectBoundary = NULL;

	for(int i = 0; i < geo3DMaps.size(); i++)
		if(geo3DMaps[i]->getContainer() == this)
			delete geo3DMaps[i];

	geo3DMaps.clear();

	for(int i = 0; i < geoModels.size(); i++ )
		if(geoModels[i]->getContainer() == this)
			delete geoModels[i];

	geoModels.clear();
 
}
///@brief ��ȡGeoProject��Ӧ��Ԫ����
///@param 
///@return ����ָ��Geo3DProjectMetaData��ָ��
///@author zhaowei
///@date	 2013.11.1
Geo3DProjectMetaData* Geo3DProject::GetGeoProjectMetaData()
{
	return metaData;
}

///@brief  ����GeoProject��Ӧ��Ԫ����
///@param value �����õ�Geo3DProjectMetaDataָ��
///@return 
///@author zhaowei
///@date   2013.11.08
void Geo3DProject::SetGeoProjectMetaData(Geo3DProjectMetaData* value)
{
	value->setContainer(this);
	if(metaData)
		delete metaData;
	metaData = value;
}

/// @name �����а����ĵ���ͼ��
//@{
/// @brief  ȡ����������������ͼ����Ŀ��
/// @return ���س����е���ͼ����Ŀ��
/// @author zhaowei
/// @date   2013.11.07
int Geo3DProject::GetGeo3DMapCount()
{
	int map_count = geo3DMaps.size();
	return map_count;
}

/// @brief  ȡ�����еĵ���ͼ��
/// @param  i ��0��ʼ�ĵ���ͼ�������š�
/// @return ���س����е�i������ͼ����ָ����ŵĵ���ͼ�������򷵻�0�����ص�ָ����ָ�������ڴ��ɱ��������
/// @author zhaowei
/// @date   2013.11.07
Geo3DMap* Geo3DProject::GetGeo3DMap(const int& i)
{
	if(!(i >= 0 && i < geo3DMaps.size()))
		return NULL;		
	Geo3DMap* geo_map = geo3DMaps[i];		
	return geo_map;
}
//@}

///@brief  ��ӵ���ͼ
///@param Geo3DMap* geoMap ����ӵĵ���ͼ
///@return 
///@author zhaowei
///@date   2013.11.06
void Geo3DProject::AddGeoMap(Geo3DMap* geoMap)
{
	if(geoMap)
	{
		geoMap->setContainer(this);
		geo3DMaps.push_back(geoMap);
	}
}

///@brief  ��ȡ���е���ͼ
///@param maps ��ŵ���ͼ������
///        mapType ��ȡ�ĵ���ͼ����
///@return 
///@author zhaowei
///@date   2013.11.06
void Geo3DProject::GetAllGeoMaps(std::vector<Geo3DMap*> &maps, const std::string& mapType)
{
	int map_count = GetGeo3DMapCount();
	for(int i = 0; i < map_count; i++)
	{
		if(geo3DMaps[i]->GetType() == mapType)
		{
			maps.push_back(geo3DMaps[i]);
		}
	}
}

///@brief  ���ù����߽�����
///@param projectBoundary �����߽�ĵ�����
///        count           �����߽�ĵ���
///@return
///@author zhaowei
///@date   2013.11.06
void Geo3DProject::SetProjectBoundary(double* Boundary, const int& count)
{	
	// ���ProjectBoundary������ʱ��Ϊ�գ���ô��Ҫ��ɾ������������ڴ�ռ䣬�ٶ��丳ֵ��
	// ���������ǰ��������Ŀռ��Ϊ�����ڴ档
	if(projectBoundary)
		delete projectBoundary;
	projectBoundary = Boundary;
	pointCount = count;
}


///@brief  ��ȡ�����߽�����
///@param 
///@return ��ʾ�����߽�����������ָ��
///@author zhaowei
///@date   2013.11.06
double* Geo3DProject::GetProjectBoundary()
{
	return projectBoundary;
}

///@brief  ��ȡ�����߽����
///@param  
///@return �����߽����
///@author zhaowei
///@date   2013.11.06
int Geo3DProject::GetProjectBoundaryPointCount()
{
	return pointCount;
}

///@brief  ��ȡ������Ŀ
///@param
///@return ����������Ŀ
///@author zhaowei
///@date   2013.11.06
int Geo3DProject::GetAttributeValueCount()
{
	int attr_count = attributeValues.size();
	return attr_count;
}

///@brief  ��ȡ���Ϊi������
///@param i ���
///@return ��������
///@author zhaowei
///@date   2013.11.06
AttributeValue Geo3DProject::GetAttributeValue(const int& i)
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

///@brief  ��ȡ������Ϊfieldname������
///@param  fieldname ��������
///@return �����������Ϊ�գ������������ƺ�����ֵΪ�յĶ��󣻷��򷵻���Ӧ������
///@author zhaowei
///@date   2013.11.06
AttributeValue Geo3DProject::GetAttributeValue(const std::string& fieldname)
{	
	for(int i = 0; i < attributeValues.size(); i++)
	{
		if(attributeValues[i].fieldName == fieldname)
		{
			return attributeValues[i];
		}
	}
	/// ���û�и����ԣ��򷵻�fieldNameΪ���������fieldValueΪ�յ�AttributeValue
	AttributeValue r;
	r.fieldName = fieldname;
	r.fieldValue = "";
	return r;
}

///@brief  ��AttributeValue����������µ�Ԫ��
///@param const AttributeValue& value ����ӵ���Ԫ��
///@return 
///@author zhaowei
///@date   2013.11.05
void Geo3DProject::AddAttributeValue(const AttributeValue& value)
{
	attributeValues.push_back(value);
}

///@brief  ȡ����������������ģ�͵���Ŀ��
///@return ���س����е���ģ�͵���Ŀ��
///@author zhaowei
///@date   2013.11.06
int Geo3DProject::GetGeoModelCount()
{
	int model_count = geoModels.size();
	return model_count;
}
///@brief  ɾ��ȫ��AttributeValue����������µ�Ԫ��
///@return 
///@author xiehaifeng
///@date   2013.12.26
void Geo3DProject::DeleteAllAttributeValue()
{
	attributeValues.clear();
	
}
///@brief  ȡ�����еĵ���ģ�͡�
///@param  i ��0��ʼ�ĵ���ģ�͵������š�
///@return ���س����е�i������ģ�͡���ָ����ŵĵ���ģ�Ͳ������򷵻�0�����ص�ָ����ָ�������ڴ��ɱ��������
///@author zhaowei
///@date   2013.11.07
GeoModel* Geo3DProject::GetGeoModel(const int& i)
{
	if(!(i >= 0 && i < geoModels.size()))
		return NULL;		
	GeoModel* geo_model = geoModels[i];	
	return geo_model;
}

///@brief  ��ӵ���ģ��
///@param  geoModel ����ӵĵ���ģ��
///@return 
///@author zhaowei
///@date   2013.11.06
void Geo3DProject::AddGeoModel(GeoModel* geoModel)
{
	if(geoModel)
	{
		geoModel->setContainer(this);
		geoModels.push_back(geoModel);
	}
}

///@brief  ��ȡ���е���ģ��
///@param  models ��ŵ���ģ�͵�����
///        modelType ��ȡ�ĵ���ģ������
///@return 
///@author zhaowei
///@date   2013.11.06
void Geo3DProject::GetAllGeoModels(std::vector<GeoModel*> &models, std::string modelType)
{
	int model_count = GetGeoModelCount();
	for(int i = 0; i < model_count; i++)
	{
		if(geoModels[i]->GetType() == modelType)
		{
			models.push_back(geoModels[i]);
		}
	}
}

void Geo3DProject::UpdateRefences()
{
	for(int i = 0; i < GetGeo3DMapCount(); i++)
	{
		Geo3DMap* geomap = GetGeo3DMap(i);
		for(int j = 0; j < geomap->GetGeo3DLayerCount(); j++)
		{
			Geo3DLayer* layer = geomap->GetLayer(j);
			if(layer->GetFeatureClass() == 0)
				continue;
			std::string fcid = layer->GetFeatureClass()->getID();
			int k = fcid.find("#");
			fcid = fcid.substr(k+1,fcid.length());
			for(int m = 0; m < geoModels.size(); m++)
			{
				GeologicFeatureClass* fc =  geoModels[m]->GetGeoFeatureClass(fcid);
				if(fc)
				{
					layer->SetFeatureClass(fc);
					break;
				}
			}
		}
	}

	for(int m = 0; m < geoModels.size(); m++)
	{
		geoModels[m]-> UpdateRelations();

	}
}
 