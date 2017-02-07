
#include <iostream>
using namespace std;

#ifndef __CWAVEFILEUTILITY_H__
#include "../Utility/CWaveFileUtility.h"
#endif

#ifndef __CSAMPLEOPERATOR16_H__
#include "CSampleOperator16.h"
#endif

/**
 * コンストラクタ
 */
CSampleOperator16::CSampleOperator16()
{
	m_shBitsPerSample = 16;
}

/**
 * 16bitで量子化されたファイルを読みこむ.
 */
double CSampleOperator16::read(ifstream& i_cFileStream)
{
	long max = CWaveFileUtility::bitShift(this->m_shBitsPerSample - 1) - 1;
	bool bigEndian = CWaveFileUtility::isBigEndian();

	short data = 0;
	i_cFileStream.read((char*)&data, sizeof(short));
	if(bigEndian) CWaveFileUtility::swapShort((char*)&data);

	return (double)data/max;
}

/**
 * 16bitで量子化されたファイルを書き込む.
 */
bool CSampleOperator16::write(double i_dSample, ofstream& i_cFileStream)
{
	bool bigEndian = CWaveFileUtility::isBigEndian();
	long max = CWaveFileUtility::bitShift(this->m_shBitsPerSample - 1) - 1;

	short data = 0;
	data = max * i_dSample;
	if(bigEndian) data = CWaveFileUtility::swapShort((char*)&data);
	i_cFileStream.write((char*)&data, sizeof(short));

	return true;
}
