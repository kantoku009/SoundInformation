
#include <iostream>
using namespace std;

#include "CReadSample16.h"
#include "../CWaveFormatOperatorUtility.h"

/****************************************
 * 16bitで量子化されたファイルを読みこむ.
 ****************************************/
double CReadSample16::read(ifstream& i_cFileStream)
{
	long max = CWaveFormatOperatorUtility::bitShift(this->m_shBitsPerSample - 1) - 1;
	bool bigEndian = CWaveFormatOperatorUtility::isBigEndian();

	short data = 0;
	i_cFileStream.read((char*)&data, sizeof(short));
	if(bigEndian) CWaveFormatOperatorUtility::swapShort((char*)&data);

	return (double)data/max;
}
