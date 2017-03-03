/**
 * @file	COtherChunkOperator.h
 * @brief	WAVEファイルのその他Chunkクラス.
 * @note	以下のいずれかでもないChunk
 *			　・RIFF
 *			　・WAVE
 *			　・fmt 
 *			　・data
 */

#ifndef __COTHERCHUNKOPERATOR_H__
#define __COTHERCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "./BChunkOperator.h"
#endif

/**
 * @brief	WAVEファイルのその他Chunk.
 */
class COtherChunkOperator : public BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	COtherChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~COtherChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	ifstream& i_cFileStream.
	 * @param	CWaveFile& i_pcWaveFile
	 * @return	成功 / 失敗.
	 */
	bool read(ifstream& i_cFileStream, CWaveFile& i_pcWaveFile);
	
	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	ifstream& i_cFileStream.
	 * @param	CWaveFile& pcWaveFile
	 * @return	成功 / 失敗.
	 */
	bool write(ofstream& i_cFileStream, CWaveFile& i_pcWaveFile);
	
};

#endif	//__COTHERCHUNKOPERATOR_H__

