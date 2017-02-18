/**
 * @file	CDataChunkOperator.h
 * @brief	WAVEファイルのdata Chunkクラス.
 */

#ifndef __CDATACHUNKOPERATOR_H__
#define __CDATACHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "BChunkOperator.h"
#endif

/**
 * @brief	WAVEファイルのdata Chunk.
 */
class CDataChunkOperator : public BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CDataChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CDataChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFile& pcWaveFile
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile, T_CHUNK& i_stChunk);
	
	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFile& pcWaveFile
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile);
	
};

#endif	//__CDATACHUNKOPERATOR_H__

