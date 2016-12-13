
#include <iostream>
using namespace std;

#include "CReadSample8.h"
#include "../CWaveFormatOperatorUtility.h"

/****************************************
 * 8bitで量子化されたファイルを読みこむ.
 ****************************************/
double CReadSample8::read(ifstream& i_cFileStream)
{
	long max = CWaveFormatOperatorUtility::bitShift(this->m_shBitsPerSample - 1) - 1;

	char data = 0;
	i_cFileStream.read((char*)&data,sizeof(char));
	data ^= 0x80;
	
	return (double)data/max;
}
