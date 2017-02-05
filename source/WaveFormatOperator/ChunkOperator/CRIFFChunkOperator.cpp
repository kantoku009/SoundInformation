/**
 * @file	CRIFFChunkOperator.cpp
 * @brief	WAVEファイルのChunkクラス.
 */

#include <cstring>
using namespace std;

#ifndef __CFMTCHUNKOPERATOR_H__
#include "CFmtChunkOperator.h"
#endif

#ifndef __CRIFFCHUNKOPERATOR_H__
#include "CRIFFChunkOperator.h"
#endif

/**
 * コンストラクタ.
 */
CRIFFChunkOperator::CRIFFChunkOperator()
{
	strncpy(m_szID, "RIFF", 4);
	m_lSize = 0;
}

/**
 * RIFF chunkをファイルから読み込み.
 */
bool  CRIFFChunkOperator::read(ifstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator, T_CHUNK& i_stChunk)
{
	memset((char*)&i_stChunk, 0x00, sizeof(i_stChunk));
	
	// ファイルから読み込み.
	i_cFileStream.read((char*)&i_stChunk,sizeof(i_stChunk));
	
	// 自分自身のChunk IDと比較.
	if( 0 != strncmp(i_stChunk.m_szID, this->m_szID, sizeof(i_stChunk.m_szID) ) )
	{
		this->m_lSize = 0;
		return false;
	}

	// Chunk sizeを設定.
	this->m_lSize = CWaveFormatOperatorUtility::convert4ByteDataToLong(i_stChunk.m_szSize);
	
	if(m_bIsDEBUG) printChunk((char*)"Read Chunk", i_stChunk);
	return true;
}

/**
 * RIFF chunkをファイルへ書き込み.
 */
bool CRIFFChunkOperator::write(ofstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator)
{
	T_CHUNK a_stChunk;
	memset((char*)&a_stChunk, 0x00, sizeof(a_stChunk));
	
	// Chunk IDを書き込む
	strncpy(a_stChunk.m_szID, this->m_szID, sizeof(a_stChunk.m_szID));

	// Chunk Sizeを書き込む.
	long dataSize = i_pcWaveFormatOperator.getSamplesPerChannel() * i_pcWaveFormatOperator.getBlockAlign();
	long lRIFFSize = 0;
	lRIFFSize = 4						//'WAVE'
				+ sizeof(T_CHUNK)		//'fmt '
				+ sizeof(T_FMT_CHUNK)	//FMT Chunk
				+ sizeof(T_CHUNK)		//'data'
				+ dataSize;				//全サンプルのサイズ.
	CWaveFormatOperatorUtility::convertLongTo4ByteData(lRIFFSize, a_stChunk.m_szSize);

	// Chunkをファイルへ書き込み.
	i_cFileStream.write((char*)&a_stChunk, sizeof(a_stChunk));

	if(m_bIsDEBUG) printChunk((char*)"Write Chunk", a_stChunk);
	return true;
}

