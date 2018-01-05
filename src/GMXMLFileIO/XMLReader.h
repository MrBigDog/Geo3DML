#pragma once
#include "export.h"

#include <libxml/parser.h>
#include <string>
namespace gml
{
	class AbstractGML;
}

class GMXMLFILEIO_EXPORT XMLReader
{
public:
	///@brief  ���캯��
	///@author zhaowei
	///@date   2013.11.04
	XMLReader(void);

	///@brief  ��������
	///@author zhaowei
	///@date   2013.11.04
	~XMLReader(void);
	
	///@brief  ���ļ�
	///@param  docName �ļ�·��������
	///@param  charSet ���ļ�ʱѡ����ַ�����ʽ
	///@return �����ȡ�ɹ�������true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.04
	virtual bool ReadFile(const char *docName, const std::string charSet = "UTF-8");

	///@brief  ��ȡXML�ļ��е�ָ���ڵ�
	///@param  curNode XML�ļ��б�ǩ���ڽڵ��ָ��
	///@return �����ȡ�ɹ�������true�����򷵻�false
	///@author zhaowei
	///@date   2013.11.06
	virtual bool ReadNode(xmlNodePtr curNode){return 0;};

	int InitCharSet(const char* pFileName);

    gml::AbstractGML* GetReadObject();

protected:
	///@brief  �ַ���ת��
	///@param  encFrom ��ת������
	///@param  encTo   ת����ı���
	///@param  in      ��ת���ַ���
	///@return ת������ַ���
	///@author zhaowei
	///@date   2013.11.04
	char* ConvertEnc(char* encFrom, char* encTo, char* in);

	///@brief  �����β�DocName����ߵĿհ��ַ���Ŀ
	///@param  DocName ��������ļ�����
	///@return �����ļ��������Ŀհ��ַ���
	///@author zhaowei
	///@date   2013.11.04
	int TrimLeft(char* DocName);

	///@brief  �����β�DocName���ұߵĿհ��ַ���Ŀ
	///@param  DocName ��������ļ�����
	///@return �����ļ������Ҳ�Ŀհ��ַ���
	///@author zhaowei
	///@date   2013.11.04
	int TrimRight(char* DocName);

	///@brief  ����β�DocName�еĿհ��ַ�
	///@param  DocName ��������ļ�����
	///@return ���ش������ַ���
	///@author zhaowei
	///@date   2013.11.04
	const char* TrimAll(char* DocName);

 
protected:	
	char FilePath[256];		//�ļ�·��
	char mXMLCoding[256];	//XML������
	char gCharSet[256];

	gml::AbstractGML* gmmlObject;
};