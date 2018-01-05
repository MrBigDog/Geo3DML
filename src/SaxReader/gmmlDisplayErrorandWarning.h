#ifndef __gmmlDisplayErrorandWarning_INFO_H__
#define __gmmlDisplayErrorandWarning_INFO_H__

#include "Export.h"

class SAXREADER_EXPORT gmmlDisplayErrorandWarning
{
public:
	gmmlDisplayErrorandWarning(void);
	~gmmlDisplayErrorandWarning(void);

	virtual void DisplayText(const char* textStr)=0;
};

#endif


