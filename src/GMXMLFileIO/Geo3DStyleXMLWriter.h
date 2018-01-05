#pragma once
#include "xmlwriter.h"
#include "Geo3DStyle.h"
#include <fstream>

namespace se
{
	class GeoSymbolizer;
	class FeatureStyleRule;
	class CoverageStyleRule;
}
namespace gmml
{
	class Geo3DStyle;
}
class GMXMLFILEIO_EXPORT Geo3DStyleXMLWriter :
	public XMLWriter
{
public:
	///@brief ���캯��
	///@author zhaowei
	///@date 2014.03.18
	Geo3DStyleXMLWriter(void);

	///@brief ��������
	///@author zhaowei
	///@date 2014.03.18
	~Geo3DStyleXMLWriter(void);

	///@brief ��Style��Ϣд���ļ�
	///@param style ָ���д��Style��ָ��
	///@param xml_stream д���ļ���ָ��
	///@author zhaowei
	///@date 2014.03.18
	void WriteStyle(gmml::Geo3DStyle* style, std::ofstream& xml_stream);

	///@brief ��Symbolizer��Ϣд���ļ�
	///@param rule ����Symbolizer���ݵ�ָ��rule��ָ��
	///@param xml_stream д���ļ���
	///@author zhaowei
	///@date 2014.03.18
	void WirteSymbolizer(se::FeatureStyleRule* rule, std::ofstream& xml_stream);
	void WirteCoverageSymbolizer(se::CoverageStyleRule* rule, std::ofstream& xml_stream);
};

