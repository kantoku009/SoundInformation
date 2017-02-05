/**
 * @file	BChunkOperator.h
 * @brief	WAVEファイルのChunkクラス.
 */

#ifndef __BCHUNKOPERATOR_H__
#define __BCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __CWAVE_FORMAT_OPERATOR_H__
#include "../../CWaveFormatOperator.h"
#endif

#ifndef __CWAVEFORMATOPERATORUTILITY_H__
#include "../Utility/CWaveFormatOperatorUtility.h"
#endif

/**
 * @brief	WaveファイルのChunk構造体.
 */
typedef struct T_CHUNK
{
	char m_szID[4];
	char m_szSize[4];
}T_CHUNK;

/**
 * @brief	WAVEファイルのChunk.
 */
class BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	BChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~BChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFormatOperator& pcWaveFormatOperator
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	virtual bool read(ifstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator, T_CHUNK& i_stChunk);

	/**
	 * @brief	WAVEファイルのChunkを書き込む.
	 * @param	T_CHUNK& i_stChunk
	 * @param	CWaveFormatOperator& pcWaveFormatOperator
	 * @param	ifstream& i_cFileStream.
	 * @return	成功 / 失敗.
	 */
	virtual bool write(ofstream& i_cFileStream, CWaveFormatOperator& i_pcWaveFormatOperator);

	/**
	 * @brief	Chunk IDを取得.
	 * @param	なし.
	 * @return	成功 / 失敗.
	 */
	virtual const char* getChunkID() const
	{
		return m_szID;
	}
	
	/**
	 * @brief	Chunk sizeを取得.
	 * @param	なし.
	 * @return	成功 / 失敗.
	 */
	virtual long getChunkSize() const
	{
		return m_lSize;
	}
protected:
	/**
	 * @brief	T_CHUNKを表示.
	 * @param	char* i_pbyMessage	表示したいメッセージ.
	 * @param	T_CHUNK i_stChunk	表示したいT_CHUNK.
	 * @return	なし.
	 * @note	デバッグ用.
	 */
	void printChunk(char* i_pbyMessage, T_CHUNK& i_stChunk);

	/**
	 * @brief	Chunk ID.
	 */
	char m_szID[4];
	
	/**
	 * @brief	Chunk size.
	 */
	long m_lSize;
	
	/**
	 * @brief	デバッグフラグ.
	 */
	bool m_bIsDEBUG;
};

#endif	//__BCHUNKOPERATOR_H__

