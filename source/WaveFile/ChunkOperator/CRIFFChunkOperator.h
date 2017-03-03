/**
 * @file	CRIFFChunkOperator.h
 * @brief	WAVEファイルのRIFF Chunkクラス.
 */

#ifndef __CRIFFCHUNKOPERATOR_H__
#define __CRIFFCHUNKOPERATOR_H__

#include <fstream>
using namespace std;

#ifndef __BCHUNKOPERATOR_H__
#include "./BChunkOperator.h"
#endif

/**
 * @brief	WAVEファイルのRIFF Chunk.
 */
class CRIFFChunkOperator : public BChunkOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CRIFFChunkOperator();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CRIFFChunkOperator(){ }

	/**
	 * @brief	WAVEファイルのChunkを読み込む.
	 * @param	ifstream& i_cFileStream.
	* @param	CWaveFile& pcWaveFile
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

private:
	char m_szType[4];

	static char m_szConstID[5];
	
};

#endif	//__CRIFFCHUNKOPERATOR_H__

