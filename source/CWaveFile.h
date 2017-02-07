/**
 * @file	CWaveFile.h
 * @brief	WAVEファイルを操作するクラス.
 */

#ifndef __CWAVEFILE_H__
#define __CWAVEFILE_H__

#include <fstream>
using namespace std;

#ifndef __BWAVEFORM_H__
#include "BWaveForm.h"
#endif

/**
 * @brief	WAVEファイルを扱うクラス.
 */
class CWaveFile : public BWaveForm
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CWaveFile(
						long  sampleRate=44100,
						short bitsPerSample=16,
						short numChannels=2,
						long  numSamples=44100)
			:BWaveForm(
							sampleRate, 
							bitsPerSample, 
							numChannels, 
							numSamples)
	{
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CWaveFile(){ }

	/**
	 * @brief	WAVEファイルから読みこみ.
	 * @param	const string i_strFilename
	 * @return	成功/失敗.
	 */
	bool read(const string i_strFileName);

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(const string i_strFileName);

};

#endif	//__CWAVEFILE_H__

