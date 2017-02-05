
#include <iostream>
using namespace std;

#ifndef __CWAVEFORMATOPERATORUTILITY_H__
#include "../Utility/CWaveFormatOperatorUtility.h"
#endif

#ifndef __CSAMPLEOPERATOR8_H__
#include "CSampleOperator8.h"
#endif

/**
 * コンストラクタ
 */
CSampleOperator8::CSampleOperator8()
{
	m_shBitsPerSample = 8;
}

/**
 * 8bitで量子化されたファイルを読みこむ.
 */
double CSampleOperator8::read(ifstream& i_cFileStream)
{
	long max = CWaveFormatOperatorUtility::bitShift(this->m_shBitsPerSample - 1) - 1;

	char data = 0;
	i_cFileStream.read((char*)&data,sizeof(char));
	data ^= 0x80;
	
	return (double)data/max;
}

/**
 * 8bitで量子化されたファイルを書き込む.
 */
bool CSampleOperator8::write(double i_dSample, ofstream& i_cFileStream)
{
	long max = CWaveFormatOperatorUtility::bitShift(this->m_shBitsPerSample - 1) - 1;

	char data = 0;
	data = max * i_dSample;
	data ^= 0x80;
	i_cFileStream.write((char*)&data, sizeof(char));

	return true;
}

