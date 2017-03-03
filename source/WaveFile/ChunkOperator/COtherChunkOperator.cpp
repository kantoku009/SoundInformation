/**
 * @file	COtherChunkOperator.cpp
 * @brief	WAVEファイルのその他Chunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __COTHERCHUNKOPERATOR_H__
#include "COtherChunkOperator.h"
#endif

#define DEF_CHUNK_ID_OTHER	""

/**
 * コンストラクタ.
 */
COtherChunkOperator::COtherChunkOperator()
{
	strncpy(m_szID, "", 4);
	m_lSize = 0;
}

/**
 * chunkをファイルから読み込み.
 */
bool  COtherChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	bool a_bIsSuccess = true;

	a_bIsSuccess = BChunkOperator::read(i_cFileStream, i_pcWaveFile);
	if(!a_bIsSuccess)
	{
		return false;
	}

	// Chunkサイズ分だけ読み飛ばす.
	i_cFileStream.seekg(this->m_lSize,ios::cur);
	
	if(m_bIsPrintChunkInfo) printChunk((char*)"Read Chunk");
	return true;
}

/**
 * chunkをファイルへ書き込み.
 */
bool COtherChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	return BChunkOperator::write(i_cFileStream, i_pcWaveFile);
}

