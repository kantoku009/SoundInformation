/**
 * @file	CRIFFChunkOperator.cpp
 * @brief	WAVEファイルのRIFF Chunkクラス.
 */

#include <cstring>
#include <cstdio>
using namespace std;

#ifndef __CFMTCHUNKOPERATOR_H__
#include "CFmtChunkOperator.h"
#endif

#ifndef __CRIFFCHUNKOPERATOR_H__
#include "CRIFFChunkOperator.h"
#endif

#define DEF_CHUNK_ID_RIFF	"RIFF"
#define DEF_CHUNK_TYPE_WAVE	"WAVE"

/**
 * コンストラクタ.
 */
CRIFFChunkOperator::CRIFFChunkOperator()
{
	strncpy(m_szID, DEF_CHUNK_ID_RIFF, 4);
	m_lSize = 0;
	strncpy(m_szType, DEF_CHUNK_TYPE_WAVE, 4);
	m_szChunkInfo = &m_szType[0];
}

/**
 * RIFF chunkをファイルから読み込み.
 */
bool  CRIFFChunkOperator::read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	bool a_bIsSuccess = true;
	size_t a_uReaded = 0;
	char a_szType[4] = "";
	memset(a_szType, 0x00, sizeof(a_szType));

	a_bIsSuccess = BChunkOperator::read(i_cFileStream, i_pcWaveFile);
	if(!a_bIsSuccess)
	{
		if(m_bIsDEBUG) printf("failed:fmt  chunk do not read.\n");
		return false;
	}

	// 自分自身のChunk IDと比較.
	if( 0 != strncmp(this->m_szID, DEF_CHUNK_ID_RIFF, sizeof(this->m_szID)) )
	{
		if(m_bIsDEBUG) printf("failed:RIFF read. not chunk.\n");
		this->m_lSize = 0;
		return false;
	}

	// typeをファイルから読み込み.
	a_uReaded = i_cFileStream.readsome( a_szType, sizeof(a_szType) );
	if(sizeof(a_szType) != a_uReaded)
	{
		if(m_bIsDEBUG) printf("failed:RIFF TYPE read.\n");
		return false;
	}

	// 自分自身のRIFF Typeと比較.
	if( 0 != strncmp(this->m_szType, DEF_CHUNK_TYPE_WAVE ,sizeof(a_szType) ) )
	{
		if(m_bIsDEBUG) printf("failed:RIFF read. not \"WAVE\" Type.\n");
		return false;
	}

	if(m_bIsPrintChunkInfo) printChunk((char*)"Read Chunk");
	return true;
}

/**
 * RIFF chunkをファイルへ書き込み.
 */
bool CRIFFChunkOperator::write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile)
{
	// "RIFF" Chunk IDをコピー.
	memcpy(this->m_szID, DEF_CHUNK_ID_RIFF, sizeof(this->m_szID));

	// Chunk Sizeを計算.
	long dataSize = i_pcWaveFile.getSamplesPerChannel() * i_pcWaveFile.getBlockAlign();
	this->m_lSize = 4						//'WAVE'
					+ 4						//'fmt '
					+ sizeof(T_FMT_CHUNK)	//FMT Chunk
					+ 4						//'data'
					+ dataSize;				//全サンプルのサイズ.

	// "WAVE" Chunk Typeをコピー.
	memcpy(this->m_szType, DEF_CHUNK_TYPE_WAVE, sizeof(this->m_szType));

	// Chunk ID および Chunk Sizeをファイルへ書き込む.
	BChunkOperator::write(i_cFileStream, i_pcWaveFile);

	// RIFF Typeを書き込む.
	i_cFileStream.write(this->m_szType, sizeof(this->m_szType) );
	
	if(m_bIsPrintChunkInfo) printChunk((char*)"Write Chunk");
	return true;
}

