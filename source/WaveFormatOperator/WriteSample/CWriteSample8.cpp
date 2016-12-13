
#include <iostream>
using namespace std;

#include "CWriteSample8.h"
#include "../CWaveFormatOperatorUtility.h"

/**************************************************
 * 8bitで量子化されたファイルを書き込む.
 **************************************************/
bool CWriteSample8::write(double i_dSample, ofstream& i_cFileStream)
{
	long max = CWaveFormatOperatorUtility::bitShift(m_shBitsPerSample - 1) - 1;

	char data = 0;
	data = max * i_dSample;
	data ^= 0x80;
	i_cFileStream.write((char*)&data, sizeof(char));

	return true;
}

