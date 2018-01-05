#ifndef AbstractGML1_h__
#define AbstractGML1_h__

#include <string>
#include <ostream>
#include "export.h"

class GMLFEATURE_EXPORT AbstractGML
{
public:
	AbstractGML(void);
	~AbstractGML(void);

public:
	/// @name �������ȫ��ΨһID��
	//@{
	std::string getID() const;
	void setID(const std::string& id);
	//@}

	/// @name ���֡�
	//@{
	std::string getName() const;
	void setName(const std::string& name);
	//@}

public:
	virtual void write(std::ostream& xmlStream) const;

protected:
	virtual std::string getXmlNodeName() const = 0;
	virtual void writeExt(std::ostream& xmlStream) const = 0;

private:
	/// �������ȫ��ΨһID��
	std::string id_;
	/// ����
	std::string name_;
};

 
#endif // AbstractGML1_h__