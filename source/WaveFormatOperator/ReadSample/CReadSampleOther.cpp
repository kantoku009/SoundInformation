
#include <iostream>
using namespace std;

#include "CReadSampleOther.h"
#include "../CWaveFormatOperatorUtility.h"

/**************************************************
 * 8bit,16bit以外で量子化されたファイルを読みこむ.
 **************************************************/
double CReadSampleOther::read(ifstream& i_cFileStream)
{   
	long max = CWaveFormatOperatorUtility::bitShift(this->m_shBitsPerSample - 1) - 1;
	short bytesPerSample = m_shBitsPerSample/8;
	bool bigEndian = CWaveFormatOperatorUtility::isBigEndian();
    
	long data = 0;
	i_cFileStream.read((char*)&data,(long)bytesPerSample);
	if(bigEndian) CWaveFormatOperatorUtility::swapLong((char*)&data);

	return (double)data/max;
}
