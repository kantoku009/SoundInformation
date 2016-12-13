#include "CFactoryWriteSample.h"

/**************************************************
 * WAVEファイルのサンプル値を書き込むクラスを生成する.
 **************************************************/
IWriteSample* CFactoryWriteSample::create(short i_shBitPerSample)
{
	IWriteSample* a_IWriteSample;
	
	if(i_shBitPerSample <= 8)
	{
		// 8bitで量子化されたファイルを書き込む.
		a_IWriteSample = &m_CWriteSample8;
	}
	else if(i_shBitPerSample > 8 && i_shBitPerSample <= 16)
	{
		// 16bitで量子化されたファイルを書き込む.
		a_IWriteSample = &m_CWriteSample16;
	}
	else
	{
		// 8bit,16bit以外で量子化されたファイルを書き込む.
		a_IWriteSample = &m_CWriteSampleOther;
	}
	
	return a_IWriteSample;
}

