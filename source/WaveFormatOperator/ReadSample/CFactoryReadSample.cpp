#include "CFactoryReadSample.h"

/**************************************************
 * WAVEファイルのサンプル値を書き込むクラスを生成する.
 **************************************************/
IReadSample* CFactoryReadSample::create(short i_shBitPerSample)
{
	IReadSample* a_iReadSample;
	
	if(i_shBitPerSample <= 8)
	{
		// 8bitで量子化されたファイルを書き込む.
		a_iReadSample = &m_CReadSample8;
	}
	else if(i_shBitPerSample > 8 && i_shBitPerSample <= 16)
	{
		// 16bitで量子化されたファイルを書き込む.
		a_iReadSample = &m_CReadSample16;
	}
	else
	{
		// 8bit,16bit以外で量子化されたファイルを書き込む.
		a_iReadSample = &m_CReadSampleOther;
	}
	

	return a_iReadSample;
}

