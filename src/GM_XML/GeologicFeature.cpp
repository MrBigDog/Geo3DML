#include "GeologicFeature.h"
#include "MappedFeature.h"

using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.13
GeologicFeature::GeologicFeature(void)
{
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.13
GeologicFeature::~GeologicFeature(void)
{
} 

///@brief  ȡҪ�ص���������
///@param  
///@return Ҫ�ص���������
///@author zhaowei
///@date   2013.11.13
std::string GeologicFeature::GetFeatureType()
{
	return featureType;
}

///@brief  ����Ҫ�ص�������
///@param  value �����õ�Ҫ������
///@return 
///@author zhaowei
///@date   2013.11.13
void GeologicFeature::SetFeatureType(const std::string& value)
{
	featureType = value;
}

///@brief  ��ȡGeologicFeature������MappedFeature��Ŀ
///@param  
///@return ����MappedFeature��Ŀ
///@author zhaowei
///@date   2013.11.13
int GeologicFeature::GetMappedFeatureCount()
{
	int mapped_feature_count = mappedFeatures.size();
	return mapped_feature_count;
}

///@brief  ��ȡָ����ŵ�MappedFeature
///@param  i ���
///@return ָ��MappedFeature��ָ��
///@author zhaowei
///@date   2013.11.13
MappedFeature* GeologicFeature::GetMappedFeature(const int& i)
{
	if(!(i >= 0 && i < mappedFeatures.size()))
		return NULL;		
	MappedFeature* mapped_feature = mappedFeatures[i];		
	return mapped_feature;
}

///@brief  ��ȡȫ����MappedFeature
///@param  mapped_features ��Ϊ���ò��������ڱ���ȫ����mappedFeature
///@return 
///@author zhaowei
///@date   2013.11.13
void GeologicFeature::GetAllMappedFeature(std::vector<MappedFeature*>& mapped_features)
{
	mapped_features = mappedFeatures;
}

///@brief  ����µ�MappedFeature
///@param  value ����ӵ�MappedFeature
///@return 
///@author zhaowei
///@date   2013.11.08
void GeologicFeature::AddMappedFeature(MappedFeature* value)
{
	value->setContainer(this);
	mappedFeatures.push_back(value);
}

void  GeologicFeature::AddBoundaryFeature(GeologicFeature* f)
{
	boundaryFeatures.push_back(f);
}

int  GeologicFeature::GetBoundaryFeatureCount()
{
	return boundaryFeatures.size();
}

GeologicFeature* GeologicFeature::GetBoundaryFeature(int i)
{
	return boundaryFeatures[i];
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void GeologicFeature::deleteMembers()
{
	for(std::vector<MappedFeature*>::size_type i = 0; i < mappedFeatures.size(); i++)
	{
		if(mappedFeatures[i]->getContainer() == this)
		{
			delete mappedFeatures[i];
		}
	}
	boundaryFeatures.clear();
	mappedFeatures.clear();
}