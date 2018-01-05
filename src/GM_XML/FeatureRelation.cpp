#include "FeatureRelation.h"

using namespace gmml;
std::string  BoundaryRelationshipTerm = "SpatialBound";
std::string  BoundaryRelationshipSourceRoleTerm = "Internal";
std::string  BoundaryRelationshipTargetRoleTerm = "Boundary";
std::string  SpatialTopologicalAggregationRelationshipTerm = "SpatialAggregation";
std::string  SpatialTopologicalAggregationRelationshipSourceRole = "Aggregation";
std::string  SpatialTopologicalAggregationRelationshipTargetRole = "Component";

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.13
FeatureRelation::FeatureRelation(void)
{
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.13
FeatureRelation::~FeatureRelation(void)
{
}

///@brief  ��������Feature֮��Ĺ�ϵ
///@param  term �����õĹ�ϵ
///@return
///@author zhaowei
///@date   2013.11.13
void FeatureRelation::setRelationship(const std::string& term)
{
	relationshipTerm=term;
}

///@brief  ��ȡ��ϵ
///@param
///@return ���ع�ϵ
///@author zhaowei
///@date   2013.11.13
std::string FeatureRelation::getRelationship() const
{
	return relationshipTerm;
}

///@brief  ����Դ��ɫ
///@param  Դ��ɫ�ַ���
///@return
///@author zhaowei
///@date   2013.11.13
void FeatureRelation::setSourceRole(const std::string& term)
{
	source = term;
}

///@brief  ��ȡԴ��ɫ
///@param  
///@return ����Դ��ɫ�ַ���
///@author zhaowei
///@date   2013.11.13
std::string FeatureRelation::getSourceRole() const
{
	return source;
}

int FeatureRelation::GetTargetCount()
{
	return targets.size();
}

///@brief  ����Ŀ���ɫ
///@param  Ŀ���ɫ�ַ���
///@return
///@author zhaowei
///@date   2013.11.13
void FeatureRelation::addTargetRole(const std::string& term)
{
	targets.push_back(term) ;
}


///@brief  ��ȡĿ���ɫ
///@param  
///@return ����Ŀ���ɫ�ַ���
///@author zhaowei
///@date   2013.11.13

std::string FeatureRelation::getTargetRole(int i) const
{
	return targets[i];
}

///@brief  ����ڴ���������
///@param
///@return
///@author zhaowei
///@date   2013.11.13
void FeatureRelation::deleteMembers()
{
   targets.clear();
}
