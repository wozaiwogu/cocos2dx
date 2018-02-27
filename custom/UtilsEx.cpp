#include <memory>
#include <string>
#include "cocos2d.h"
#include "UtilsEx.h"
#include "xxtea/xxtea.h"
 
NS_CC_BEGIN

static std::string signString = std::string("HuNanQiPai--Sign");

bool UtilsEx::saveServerConfig(const char * fileName, const char * data, int dataCount)
{
	FILE* file;
	file = fopen(fileName, "wb");
	if (fwrite(data, sizeof(char), dataCount, file) != dataCount) {
		printf("write error");
		fclose(file);
		return false;
	}
	fclose(file);

	return true;
}

char* UtilsEx::decrypt( const char* fileName)
{
	FILE* fileOpen;
	fileOpen = fopen(fileName, "rb");
	fseek(fileOpen, 0, SEEK_END);
	int count = ftell(fileOpen);
	unsigned char* dataBuf = new unsigned char[count];
	memset(dataBuf, 0, count);
	fseek(fileOpen, 0, SEEK_SET);
	if (fread(dataBuf, sizeof(char), count, fileOpen) != count) {
		CCLOG("open encode file fail");
		return nullptr;
	}

	fclose(fileOpen);

	char* outBuf = nullptr;
	int outLen = base64Decode(dataBuf, count, (unsigned char**)&outBuf);
	delete[] dataBuf;

    int signIndex = 0;
    int signeLen = signString.size();
    if (outLen < signeLen) {
        CCLOG("sign compare failure");
        return nullptr;
    }
    
	const char* signStr = signString.c_str();
	for (int signIndex = 0; signIndex < signeLen && signIndex < outLen; ++signIndex) {
		if (signStr[signIndex] != outBuf[signIndex]) {
			CCLOG("sign compare failure");
			return nullptr;
		}
	}

	for (long index = signeLen; index < outLen; ++index)
	{
		 char value = outBuf[index];
		outBuf[index] = ((value & 0xf0) >> 4) | ((value & 0x0f) << 4);
	}

	xxtea_long len = 0;
	std::string b = std::string("#$JKD)#$#!NJRE_)$%NFDK");
	unsigned char* result = xxtea_decrypt((unsigned char*)outBuf + signeLen,
		(xxtea_long)outLen - signeLen,
		(unsigned char*)b.c_str(),
		(xxtea_long)b.size(),
		&len);

	delete[] outBuf;

	char* buf = new char[len + 1];
	memcpy(buf, result, len);
	buf[len] = '\0';
	
	return buf;
}


NS_CC_END
