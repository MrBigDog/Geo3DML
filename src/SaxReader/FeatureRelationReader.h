#pragma once

#include "global.h"

SAXREADER_EXPORT int ReadFeatureRelation(void* pData,xmlTextReaderPtr reader);
SAXREADER_EXPORT int ReadTargets(void* pData,xmlTextReaderPtr reader);
SAXREADER_EXPORT int ReadSource(void* pData,xmlTextReaderPtr reader);
