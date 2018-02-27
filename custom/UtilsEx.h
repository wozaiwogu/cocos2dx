#ifndef __CONFIG_UTILS_H__
#define __CONFIG_UTILS_H__

#include "cocos2d.h"

NS_CC_BEGIN
class CC_DLL UtilsEx {
public:
	static bool	saveServerConfig(const char * fileName, const char * data, int dataCount);
	static char* decrypt(const char* fileName);
};

NS_CC_END

#endif // !__CONFIG_UTILS_H__
