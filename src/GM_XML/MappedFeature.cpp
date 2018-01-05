#include "MappedFeature.h"
using namespace gmml;

///@brief  ���캯��
///@author zhaowei
///@date   2013.11.13
MappedFeature::MappedFeature(void)
{
	shape = NULL;
}

///@brief  ��������
///@author zhaowei
///@date   2013.11.13
MappedFeature::~MappedFeature(void)
{
}

///@brief  �ͷŹ�����ڴ�
///@param  
///@return
///@author zhaowei
///@date   2013.11.13
void MappedFeature::deleteMembers()
{
	if(shape)
		delete shape;
	shape = NULL;
}

///@brief  ��ȡ��������
///@param
///@return ָ�򼸺����ݵ�ָ��
///@author zhaowei
///@date   2013.11.13
vtkObject* MappedFeature::GetShape()
{
	return shape;
}

///@brief  ���ü�������
///@param  value �����õļ�������
///@return 
///@author zhaowei
///@date   2013.11.13
void MappedFeature::SetShape(vtkObject* value)
{
	shape = value;
}

bool MappedFeature::isShaped()
{
	return shape;
}

