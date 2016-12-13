
#include <iostream>
using namespace std;

#include "CWriteSample16.h"
#include "../CWaveFormatOperatorUtility.h"

/**************************************************
 * 16bitで量子化されたファイルを書き込む.
 **************************************************/
bool CWriteSample16::write(double i_dSample, ofstream& i_cFileStream)
{
	bool bigEndian = CWaveFormatOperatorUtility::isBigEndian();
	long max = CWaveFormatOperatorUtility::bitShift(m_shBitsPerSample - 1) - 1;

	short data = 0;
	data = max * i_dSample;
	if(bigEndian) data = CWaveFormatOperatorUtility::swapShort((char*)&data);
	i_cFileStream.write((char*)&data, sizeof(short));

	return true;
}
