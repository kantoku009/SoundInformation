/**
 * @file	CDataChunkOperator.cpp
 * @brief	WAVEファイルのdata Chunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CDATACHUNKOPERATOR_H__
#include "CDataChunkOperator.h"
#endif

#ifndef __CFACTORYSAMPLEOPERATOR_H__
#include "../SampleOperator/CFactorySampleOperator.h"
#endif

#ifndef __IREADSAMPLEOPERATOR_H__
#include "../SampleOperator/ISampleOperator.h"
#endif

/**
 * コンストラクタ.
 */
CDataChunkOperator::CDataChunkOperator()
{
	strncpy(m_szID, "data", 4);
	m_lSize = 0;
}

/**
 * data chunkをファイルから読み込み.
 */
bool  CDataChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk)
{
	long lDataSize = CWaveFileUtility::convert4ByteDataToLong(i_stChunk.m_szSize);
	i_pcWaveFile.setSamplesPerChannel(lDataSize/i_pcWaveFile.getBlockAlign());

	// 量子化ビットを取得.
	short a_BitsPerSample = i_pcWaveFile.getBitsPerSample();
	
	// サンプル値の読み込む方法を生成. (1サンプル 8bit, 16bit...のどれで読み込むかを決定).
	CFactorySampleOperator a_CFactorySampleOperator;
	ISampleOperator* a_piSampleOperator;
	a_piSampleOperator = a_CFactorySampleOperator.create(a_BitsPerSample);
	
	// read sample.
	for(long index=0;index<i_pcWaveFile.getSamplesPerChannel();index++)
	{
		for(short channel=0;channel<i_pcWaveFile.getNumChannels();channel++)
		{
			double a_dSample = a_piSampleOperator->read(i_cFileStream);
			i_pcWaveFile.setSample(a_dSample, index, channel);
		}
	}
	
	if(m_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	return true;
}

/**
 * data chunkをファイルへ書き込み.
 */
bool CDataChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	T_CHUNK a_stChunk;
	memset((char*)&a_stChunk, 0x00, sizeof(a_stChunk));

	// "data"をコピー.
	strncpy(a_stChunk.m_szID, this->m_szID, sizeof(a_stChunk.m_szID));
	
	// "data"のサイズを計算.
	long lDataSize = i_pcWaveFile.getSamplesPerChannel() * i_pcWaveFile.getBlockAlign();
	CWaveFileUtility::convertLongTo4ByteData(lDataSize, a_stChunk.m_szSize);
	
	// chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&a_stChunk, sizeof(a_stChunk));
    
	// 量子化ビットを取得.
	short a_BitsPerSample = i_pcWaveFile.getBitsPerSample();
	
	// サンプル値の読み込む方法を生成. (1サンプル 8bit, 16bit...のどれで読み込むかを決定).
	CFactorySampleOperator a_CFactorySampleOperator;
	ISampleOperator* a_piSampleOperator;
	a_piSampleOperator = a_CFactorySampleOperator.create(a_BitsPerSample);
	
	// write sample.
	bool a_bIsWriteSuccess = true;
	for(long index=0;index<i_pcWaveFile.getSamplesPerChannel();index++)
	{
		for(short channel=0;channel<i_pcWaveFile.getNumChannels();channel++)
		{
			double a_Sample = i_pcWaveFile.getSample(index,channel);
			a_bIsWriteSuccess = a_piSampleOperator->write(a_Sample, i_cFileStream);
			if(a_bIsWriteSuccess) break;
			
		}
	}

	if(m_bIsDEBUG) printChunk((char*)"Write Sample Chunk", a_stChunk);
	return true;
}

