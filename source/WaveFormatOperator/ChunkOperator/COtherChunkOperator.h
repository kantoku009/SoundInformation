/**
 * @file	COtherChunkOperator.h
 * @brief	WAVEファイルのChunkクラス.
 */

#ifndef __COTHERCHUNKOPERATOR_H__
#define __COTHERCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "./BChunkOperator.h"
#endif

/**
 * @brief	WAVEファイルのChunk.
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
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFormatOperator& i_pcWaveFormatOperator
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool read(ifstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator, T_CHUNK& i_stChunk);
	
	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFormatOperator& pcWaveFormatOperator
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	bool write(ofstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator);
	
};

#endif	//__COTHERCHUNKOPERATOR_H__

