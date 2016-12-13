
#include <iostream>
using namespace std;

#include "CWriteSampleOther.h"
#include "../CWaveFormatOperatorUtility.h"

/**************************************************
 * 8bit,16bit以外で量子化されたファイルを書き込む.
 **************************************************/
bool CWriteSampleOther::write(double i_dSample, ofstream& i_cFileStream)
{
	bool bigEndian = CWaveFormatOperatorUtility::isBigEndian();
	long max = CWaveFormatOperatorUtility::bitShift(m_shBitsPerSample - 1) - 1;
	short bytesPerSample = m_shBitsPerSample / 8;

	long data = 0;
	data = max * i_dSample;
	if(bigEndian) data = CWaveFormatOperatorUtility::swapLong((char*)&data);
	i_cFileStream.write((char*)&data, bytesPerSample);

	return true;
}
