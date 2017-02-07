
#include <iostream>
using namespace std;

#ifndef __CWAVEFILEUTILITY_H__
#include "../Utility/CWaveFileUtility.h"
#endif

#ifndef __CSAMPLEOPERATOROTHER_H__
#include "CSampleOperatorOther.h"
#endif

/**
 * コンストラクタ
 */
CSampleOperatorOther::CSampleOperatorOther()
{
		m_shBitsPerSample = 24;
}

/**
 * 8bit,16bit以外で量子化されたファイルを読みこむ.
 */
double CSampleOperatorOther::read(ifstream& i_cFileStream)
{   
	long max = CWaveFileUtility::bitShift(this->m_shBitsPerSample - 1) - 1;
	short bytesPerSample = this->m_shBitsPerSample/8;
	bool bigEndian = CWaveFileUtility::isBigEndian();
    
	long data = 0;
	i_cFileStream.read((char*)&data,(long)bytesPerSample);
	if(bigEndian) CWaveFileUtility::swapLong((char*)&data);

	return (double)data/max;
}

/**
 * 8bit,16bit以外で量子化されたファイルを書き込む.
 */
bool CSampleOperatorOther::write(double i_dSample, ofstream& i_cFileStream)
{
	bool bigEndian = CWaveFileUtility::isBigEndian();
	long max = CWaveFileUtility::bitShift(this->m_shBitsPerSample - 1) - 1;
	short bytesPerSample = this->m_shBitsPerSample / 8;

	long data = 0;
	data = max * i_dSample;
	if(bigEndian) data = CWaveFileUtility::swapLong((char*)&data);
	i_cFileStream.write((char*)&data, bytesPerSample);

	return true;
}
