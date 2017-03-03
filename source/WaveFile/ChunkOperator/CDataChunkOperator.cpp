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

#define DEF_CHUNK_ID_DATA	"data"

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
bool  CDataChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	bool a_bIsSuccess = true;

	a_bIsSuccess = BChunkOperator::read(i_cFileStream, i_pcWaveFile);
	if(!a_bIsSuccess)
	{
		if(m_bIsDEBUG) printf("failed:data do not read.\n");
		return false;
	}

	// 自分自身のChunk IDと比較.
	if( 0 != strncmp(this->m_szID, DEF_CHUNK_ID_DATA, sizeof(this->m_szID)) )
	{
		if(m_bIsDEBUG) printf("failed:RIFF read. not chunk.\n");
		this->m_lSize = 0;
		return false;
	}

	i_pcWaveFile.setSamplesPerChannel(this->m_lSize/i_pcWaveFile.getBlockAlign());

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
	
	if(m_bIsPrintChunkInfo) printChunk((char*)"Read Chunk");
	return true;
}

/**
 * data chunkをファイルへ書き込み.
 */
bool CDataChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	// "data" Chunk IDをコピー.
	memcpy(this->m_szID, DEF_CHUNK_ID_DATA, sizeof(this->m_szID));

	// "data"のサイズを計算.
	this->m_lSize = i_pcWaveFile.getSamplesPerChannel() * i_pcWaveFile.getBlockAlign();
	
	// 量子化ビットを取得.
	short a_BitsPerSample = i_pcWaveFile.getBitsPerSample();
	
	// サンプル値の読み込む方法を生成. (1サンプル 8bit, 16bit...のどれで読み込むかを決定).
	CFactorySampleOperator a_CFactorySampleOperator;
	ISampleOperator* a_piSampleOperator;
	a_piSampleOperator = a_CFactorySampleOperator.create(a_BitsPerSample);
	
	// Chunk ID および Chunk Sizeをファイルへ書き込み.
	BChunkOperator::write(i_cFileStream, i_pcWaveFile);

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

	if(m_bIsPrintChunkInfo) printChunk((char*)"Write Sample Chunk");
	return true;
}

