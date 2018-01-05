#ifndef AbstractGML_h__
#define AbstractGML_h__

#include "export.h"
#include <string>
#include <ostream>
#include <vector>

// AbstractDataComppnent
struct AttributeValue
{
	std::string fieldType;
	std::string fieldName;
	std::string fieldValue; // id
};

struct AttributeField
{
	std::string fieldName;
	std::string fieldType;
	std::string fieldDescription;
};

namespace gml
{

	class GEOXML_EXPORT AbstractGML
	{
	public:
		AbstractGML(void);
		~AbstractGML(void);
		virtual std::string GetClassName() { return "AbstractGML"; };
	public:
		/// @name �������ȫ��ΨһID��
		//@{
		std::string getID() const;
		void setID(std::string  id);
		//@}

		long getDBID();
		void setDBID(long id);
		//@}

		/// @name ����
		//@{
		std::string getName() const;
		void setName(std::string  name);
		//@}

		/// @name ��������ļ�·��
		//@{
		std::string getIOPath() const;
		void setIOPath(std::string  value);
		//@}

		AbstractGML* getContainer() const;
		void setContainer(const AbstractGML* c);
		virtual void deleteMembers() {};
	private:
		AbstractGML *container_;
		/// �������ȫ��ΨһID��
		std::string id_;
		/// ����
		std::string name_;
		/// �ļ�·��
		std::string IOPath;

		// ���ݿ�DB ID
		long db_id;
	};

}
#endif // AbstractGML_h__