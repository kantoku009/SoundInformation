/**
 * @file	COtherChunkOperator.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __COTHERCHUNKOPERATOR_H__
#include "COtherChunkOperator.h"
#endif

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
bool  COtherChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk)
{
	return BChunkOperator::read(i_cFileStream, i_pcWaveFile, i_stChunk);
}

/**
 * chunkをファイルへ書き込み.
 */
bool COtherChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	return BChunkOperator::write(i_cFileStream, i_pcWaveFile);
}

