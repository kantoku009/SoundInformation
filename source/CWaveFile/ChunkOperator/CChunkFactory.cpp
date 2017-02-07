/**
 * @file	CChunkFactory.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CCHUNKFACTORY_H__
#include "CChunkFactory.h"
#endif

/**
 * コンストラクタ.
 */
CChunkFactory::CChunkFactory()
{
	//m_mapChunk[m_cRIFFChunkOperator.getChunkID()] = m_cRIFFChunkOperator;
	//m_mapChunk[m_cWAVEChunkOperator.getChunkID()] = m_cWAVEChunkOperator;
	//m_mapChunk[m_cFmtChunkOperator.getChunkID()] = m_cFmtChunkOperator;
	//m_mapChunk[m_cDataChunkOperator.getChunkID()] = m_cDataChunkOperator;
	//m_mapChunk[m_cOtherChunkOperator.getChunkID()] = m_cOtherChunkOperator;
}

/**
 * WAVE chunkをファイルから読み込み.
 */
BChunkOperator*  CChunkFactory::create(const char* i_szID)
{
	//return &m_mapChunk[i_szID];
	BChunkOperator* rgbChunkOperator[] =
	{
		&m_cRIFFChunkOperator,
		&m_cWAVEChunkOperator,
		&m_cFmtChunkOperator,
		&m_cDataChunkOperator,
		&m_cOtherChunkOperator,
	};
	short a_shLoopMax = sizeof(rgbChunkOperator) / sizeof(rgbChunkOperator[0]);
	for(short a_shIndex=0; a_shIndex<a_shLoopMax; a_shIndex++)
	{
		if(0 == memcmp(rgbChunkOperator[a_shIndex]->getChunkID(), i_szID, 4) )
		{
			return rgbChunkOperator[a_shIndex];
		}
	}
	return &m_cOtherChunkOperator;
}
