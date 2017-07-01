#ifndef __CMPEGFRAME_H__
#define __CMPEGFRAME_H__

#include "CMpegFrame.h"

enum E_MPEG_VERSION_INDEX
{
	E_MPEG_VERSION_MIN=-1,
	E_MPEG25,			// bit 00=0:MPEG2.5.
	E_MPEG_RESERVED,	// bit 01=1:未定義.
	E_MPEG2,			// bit 10=2:MPEG2.
	E_MPEG1,			// bit 11=3:MPEG1.
	E_MPEG_VERSION_MAX
};

enum E_LAYER_INDEX
{
	E_LAYER_MIN=-1,
	E_LAYER_RESERVED,
	E_LAYER_3,
	E_LAYER_2,
	E_LAYER_1,
	E_LAYER_MAX
};

enum E_PROTECTION_BIT_INDEX
{
	E_PROTECTION_BIT_MIN=-1,
	E_PROTECTION_BIT_TRUE,
	E_PROTECTION_BIT_FALSE,
	E_PROTECTION_BIT_MAX
};

enum E_BITRATE_INDEX
{
	E_BITRATE_MIN=-1,
	E_BITRATE_0,
	E_BITRATE_1,
	E_BITRATE_2,
	E_BITRATE_3,
	E_BITRATE_4,
	E_BITRATE_5,
	E_BITRATE_6,
	E_BITRATE_7,
	E_BITRATE_8,
	E_BITRATE_9,
	E_BITRATE_10,
	E_BITRATE_11,
	E_BITRATE_12,
	E_BITRATE_13,
	E_BITRATE_14,
	E_BITRATE_INVALID,
	E_BITRATE_MAX
};

enum E_SAMPLERATE_INDEX
{
	E_SAMPLERATE_MIN=-1,
	E_SAMPLERATE_0,
	E_SAMPLERATE_1,
	E_SAMPLERATE_2,
	E_SAMPLERATE_RESERVED,
	E_SAMPLERATE_MAX,
};

enum E_PADDING_BIT_INDEX
{
	E_PADDING_BIT_MIN=-1,
	E_PADDING_BIT_FALSE,
	E_PADDING_BIT_TRUE,
	E_PADDING_BIT_MAX
};

enum E_PRIVATE_BIT_INDEX
{
	E_PRIVATE_BIT_MIN=-1,
	E_PRIVATE_BIT_FALSE,
	E_PRIVATE_BIT_TRUE,
	E_PRIVATE_BIT_MAX
};

enum E_CHANNEL_MODE_INDEX
{
	E_CHANNEL_MODE_MIN=-1,
	E_CHANNEL_MODE0,
	E_CHANNEL_MODE1,
	E_CHANNEL_MODE2,
	E_CHANNEL_MODE3,
	E_CHANNEL_MODE_MAX
};

enum E_MODE_EXTENTION_INDEX
{
	E_MODE_EXTENTION_MIN=-1,
	E_MODE_EXTENTION0,
	E_MODE_EXTENTION1,
	E_MODE_EXTENTION2,
	E_MODE_EXTENTION3,
	E_MODE_EXTENTION_MAX
};

enum E_COPYRIGHT_INDEX
{
	E_COPYRIGHT_MIN=-1,
	E_COPYRIGHT_FALSE,
	E_COPYRIGHT_TRUE,
	E_COPYRIGHT_MAX
};

enum E_ORIGINAL_INDEX
{
	E_ORIGINAL_MIN=-1,
	E_ORIGINAL_FALSE,
	E_ORIGINAL_TRUE,
	E_ORIGINAL_MAX
};

enum E_EMPHASIS_INDEX
{
	E_EMPHASIS_MIN=-1,
	E_EMPHASIS_ON,
	E_EMPHASIS_50_15MS,
	E_EMPHASIS_RESERVED,
	E_EMPHASIS_CCIT_J17,
	E_EMPHASIS_MAX
};

/******************************
* Granule情報
*******************************/
typedef struct T_GRANULE_INFO
{
	unsigned short    nPart23Length;          // 12 Bits
	unsigned short    nBigValues;             // 9 Bits
	unsigned short    nGlobalGain;            // 8 Bits
	unsigned short    nScalefacCompress;      // 4 Bits
	unsigned short    nWindowSwitchingFlag;   // 1 Bit
	unsigned short    nBlockType;             // 2 Bits 
	unsigned short    nMixedBlockFlag;        // 1 Bit
	unsigned short    nTableSelect[3];        // 5 Bits * 3
	unsigned short    nSubblockGain[3];       // 3 Bits * 3
	unsigned short    nRegion0Count;          // 4 Bits
	unsigned short    nRegion1Count;          // 3 Bits
	unsigned short    nPreFlag;               // 1 Bit 
	unsigned short    nScalefacScale;         // 1 Bit
	unsigned short    nCount1TableSelect;     // 1 Bit 0:QUAD_A 1:QUAD_B

	bool IsMixedBlock() const { return nBlockType==2 && nMixedBlockFlag; }
	bool IsLongBlock() const { return nBlockType!=2; }
	bool IsShortBlock() const { return nBlockType==2 && !nMixedBlockFlag; }
}T_GRANULE_INFO;


/**
 * @brief	MPEG Frameを扱うクラス.
 */
class CMpegFrame
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CMpegFrame();

	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CMpegFrame();

	/**
	 * @brief	初期化.
	 */
	void init();

	/**
	 * @brief	MPEG Frame Headerか否かを確認.
	 * @param	unsigned long i_ulHeader
	 * @return	true:MPEG Frame Header.
	 * @note	MPEG Frame Headerは4[byte](32[bit])である.
	 *			MPEG Frame Headerは先頭12[bit]は1が連続している.
	 *			(MPEG2.5に対応する場合は, 先頭11[bit]は1が連続している)
	 */
	bool isHeader(unsigned long i_ulHeader) const;

	/**
	 * @brief	MPEG Frame Headerを設定する.
	 * @param	unsigned long i_ulHeader
	 * @return	true:成功 / false:失敗.
	 */
	bool setHeader(unsigned long i_ulHeader);

	/**
	 * @brief	MPEG Frame Headerを取得する.
	 * @param	なし.
	 * @return	MPEG Frame Header
	 */
	unsigned long getHeader() const
	{
		return this->m_ulHeader;
	}

	/**
	 * @brief	MPEG Frame サイズを取得.
	 * @param	なし.
	 */
	long getFrameSize() const;

	/**
	 * @brief	MPEG Main データサイズを取得.
	 * @param	なし.
	 */
	long getMainDataSize() const;

	/**
	 * @brief	サンプル数を取得.
	 * @param	なし.
	 */
	long getSamples() const { return 1152; }

	/**
	 * @brief	サンプリング周波数を取得.
	 * @param	なし.
	 */
	long getSampleRate() const; // Hz

	/**
	 * @brief	ビットレートを取得.
	 * @param	なし.
	 */
	long getBitrate() const; // Bits/Sec

	/**
	 * @brief	MPEG バージョンを取得.
	 * @param	なし.
	 * @return	0:MPEG2.5 1:MPEG2 3:MPEG1
	 */
	E_MPEG_VERSION_INDEX getVersionIndex() const { return m_eVersionIndex; }

	/**
	 * @brief	レイヤーを取得.
	 * @param	なし
	 * @return	レイヤーインデックス.
	 */
	E_LAYER_INDEX getLayerIndex() const { return m_eLayerIndex; }

	/**
	 * @brief	プロテクションビットを取得.
	 * @param	なし.
	 * @return	プロテクションビット.
	 */
	E_PROTECTION_BIT_INDEX getProtectionBit() const { return m_eProtectionBit; }

	/**
	 * @brief	BitRateインデックスを取得.
	 * @param	なし.
	 * @return	BitRateインデックス.
	 */
	E_BITRATE_INDEX getBitrateIndex() const { return m_eBitrateIndex; }

	/**
	 * @brief	サンプリング周波数インデックスを取得.
	 * @param	なし.
	 * @return	サンプリング周波数インデックス.
	 */
	E_SAMPLERATE_INDEX getSampleRateIndex() const { return m_eSampleRateIndex; }

	/**
	 * @brief	パディングビットを取得.
	 * @param	なし.
	 * @return	パディングビット.
	 */
	E_PADDING_BIT_INDEX getPaddingBit() const { return m_ePaddingBit; }

	/**
	 * @brief	未使用ビットを取得.
	 * @param	なし.
	 * @return	未使用ビット.
	 */
	E_PRIVATE_BIT_INDEX getPrivateBit() const { return m_ePrivateBit; }

	/**
	 * @brief	チャンネルモードインデックスを取得.
	 * @param	なし.
	 * @return	チャンネルモードインデックス.
	 */
	E_CHANNEL_MODE_INDEX getMode() const { return m_eChannelMode; }

	/**
	 * @brief	拡張モードを取得.
	 * @param	なし.
	 * @return	拡張モード.
	 */
	E_MODE_EXTENTION_INDEX getModeExtention() const { return m_eModeExtention; }

	/**
	 * @brief	著作権保護情報取得.
	 * @param	なし.
	 * @return	著作権保護情報.
	 */
	E_COPYRIGHT_INDEX getCopyright() const { return m_eCopyright; }

	/**
	 * @brief	オリジナルか否かを取得.
	 * @param	なし.
	 * @return	0:コピー. 1:オリジナル. 
	 */
	E_ORIGINAL_INDEX getOriginal() const { return m_eOriginal; }

	/**
	 * @brief	エンファシスを取得.
	 * @param	なし.
	 * @return	エンファシスを表すインデックス.
	 */
	E_EMPHASIS_INDEX getEmphasis() const { return m_eEmphasis; }
	
	/**
	 * @brief	チャンネル数を取得.
	 * @param	なし.
	 * @return	チャンネル数.
	 */
	unsigned short getChannels() const
	{
		return (E_CHANNEL_MODE3==m_eChannelMode)? 1:2;
	}

	/**
	 * @brief	CRC情報を取得.
	 * @param	なし.
	 * @return	CRC情報.
	 */
	unsigned short getCRCCheck() const
	{
		return m_usCRCCheck;
	}

	/**
	 * @brief	CRC情報を設定.
	 * @param	unsigned short i_usCRCCheck	CRC情報.
	 * @return	成功/失敗.
	 */
	void setCRCCheck(unsigned short i_usCRCCheck)
	{
		m_usCRCCheck = i_usCRCCheck;
	}

	/**
	 * @brief	サイド情報を設定.
	 * @param	char* a_bySide
	 * @return	成功/失敗.
	 */
	bool setSideInfo(char* i_bySide);

	/**
	 * @brief	サイド情報のサイズを取得.
	 * @
	 */
	unsigned short getSideSize()
	{
		return (1==this->getChannels())? 17:32;
	}
	
	/**
	 * @brief	メインデータを設定.
	 * @param	[in]char* i_pMainData
	 * @param	[in]long i_lSize
	 * @return	成功/失敗.
	 */
	bool setMainData(char* i_pMainData, long i_lSize);

	/**
	 * @brief	
	 * @param	なし.
	 * @return	
	 * @note	1ビット目が1の場合,MPEG1. 1ビット目が0の場合,MPEG2 or MPEG2.5.
	 */
	unsigned short IsLSF() const
	{
		return (m_eVersionIndex&0x01);
	}

	/**
	 * @brief	
	 * @param	なし.
	 * @return	
	 */
	unsigned short getGranules() const
	{
		return (IsLSF()==0)? 2:1;
	}

	/**
	 * @brief	MPEG Frame Header情報を出力.
	 * @param	なし.
	 * @return	なし.
	 * @note	debug用に情報を出力.
	 */
	void printHeaderInfo();

	//Side情報　（debug用に取得できるようにする）
	unsigned short getMainDataBegin() const
	{
		return m_usMainDataBegin;
	}
	unsigned short getScfSI(unsigned short i_usChannel, unsigned short i_usIndex) const
	{
		return m_pusScfSi[i_usChannel][i_usIndex];
	}
	const T_GRANULE_INFO* getGranuleInfo(unsigned short i_usChannel, unsigned short i_usGranuleIndex) const
	{
		return &m_pGranuleInfo[i_usChannel][i_usGranuleIndex];
	}

private:
	/**
	 * @brief	MPEG Frame Headerの設定（実処理）.
	 * @param	[in ] const unsigned long i_ulHeader,
	 * @param	[in ] const unsigned long i_ulMask,
	 * @param	[in ] const unsigned long i_ulShift,
	 * @param	[in ] const long i_ulMin,
	 * @param	[in ] const long i_ulMax,
	 * @param	[out] long& i_ulValue
	 * @return	成功/失敗.
	 */
	bool setHeaderValueImp(
			const unsigned long i_ulHeader,
			const unsigned long i_ulMask,
			const unsigned long i_ulShift,
			const long i_ulMin,
			const long i_ulMax,
			long* i_ulValue);

	/**
	 * @brief	Versionを設定.
	 * @param	unsigned long i_ulHeader
	 * @return 成功/失敗.
	 */
	bool setVersionIndex(unsigned long i_ulHeader);

	/**
	 * @brief	Layerを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setLayerIndex(unsigned long i_ulHeader);

	/**
	 * @brief	プロテクションビットを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setProtectionBit(unsigned long i_ulHeader);

	/**
	 * @brief	ビットレートインデックスを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setBitrateIndex(unsigned long i_ulHeader);

	/**
	 * @brief	サンプリング周波数インデックスを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setSampleRateIndex(unsigned long i_ulHeader);

	/**
	 * @brief	パディングビットを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setPaddingBit(unsigned long i_ulHeader);

	/**
	 * @brief	未使用ビットを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setPrivateBit(unsigned long i_ulHeader);

	/**
	 * @brief	チャンネルモードを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setChannelMode(unsigned long i_ulHeader);

	/**
	 * @brief	拡張モードを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setMoedExtention(unsigned long i_ulHeader);

	/**
	 * @brief	著作権情報を設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setCopyright(unsigned long i_ulHeader);

	/**
	 * @brief	オリジナルか否かを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setOriginal(unsigned long i_ulHeader);

	/**
	 * @brief	エンファシスを設定.
	 * @param	unsigned long i_ulHeader
	 * @return	成功/失敗.
	 */
	bool setEmphasis(unsigned long i_ulHeader);


	/**
	 * @brief	Mpeg Frame Header.
	 */
	unsigned long	m_ulHeader;

	/////////////////////////////////////////////////////////////////////////////
	//フレームヘッダー項目.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	ID.
	 * @param	なし.
	 * @return	0:MPEG2.5 1:MPEG2 2:未定義 3:MPEG1.
	 * @note	MPEG Frame Header 12-13ビット目. MPEG2.5を考慮している.
	 */
	E_MPEG_VERSION_INDEX m_eVersionIndex;			// MPEG Frame Header 2 bit

	/**
	 * @brief	レイヤー.
	 * @param	なし.
	 * @return	0:予約済み. 1:レイヤーIII 2:レイヤーII 3:レイヤーI.
	 */
	E_LAYER_INDEX m_eLayerIndex;						// MPEG Frame Header 2 bits

	/**
	 * @brief	保護ビット.
	 * @return	0:CRC保護あり. 1:CRC保護なし.
	 */
	E_PROTECTION_BIT_INDEX m_eProtectionBit;				// MPEG Frame Header 1 bit

	/**
	 * @brief	ビットレート.
	 * @note	ビットレートを示すインデックス.<br>
	 *			<tr> <th>Index	</th> <th>Layer I	</th> <th>Layer II	</th> <th>Layer III	</th> </tr>
	 *			<tr> <td>0		</td> <td>free bit	</td> <td>free bit	</td> <td>free bit	</td> </tr>
	 *			<tr> <td>1		</td> <td>32		</td> <td>32		</td> <td>32		</td> </tr>
	 *			<tr> <td>2		</td> <td>64		</td> <td>48		</td> <td>40		</td> </tr>
	 *			<tr> <td>3		</td> <td>96		</td> <td>56		</td> <td>48		</td> </tr>
	 *			<tr> <td>4		</td> <td>128		</td> <td>64		</td> <td>56		</td> </tr>
	 *			<tr> <td>5		</td> <td>160		</td> <td>80		</td> <td>64		</td> </tr>
	 *			<tr> <td>6		</td> <td>192		</td> <td>96		</td> <td>80		</td> </tr>
	 *			<tr> <td>7		</td> <td>224		</td> <td>112		</td> <td>96		</td> </tr>
	 *			<tr> <td>8		</td> <td>256		</td> <td>128		</td> <td>112		</td> </tr>
	 *			<tr> <td>9		</td> <td>288		</td> <td>160		</td> <td>128		</td> </tr>
	 *			<tr> <td>10		</td> <td>320		</td> <td>192		</td> <td>160		</td> </tr>
	 *			<tr> <td>11		</td> <td>352		</td> <td>224		</td> <td>192		</td> </tr>
	 *			<tr> <td>12		</td> <td>384		</td> <td>256		</td> <td>224		</td> </tr>
	 *			<tr> <td>13		</td> <td>416		</td> <td>320		</td> <td>256		</td> </tr>
	 *			<tr> <td>14		</td> <td>448		</td> <td>384		</td> <td>320		</td> </tr>
	 *			<tr> <td>15		</td> <td>不正値	</td> <td>不正値	</td> <td>不正値	</td> </tr>
	 */
	E_BITRATE_INDEX m_eBitrateIndex;				// MPEG Frame Header 4 bits

	/**
	 * @brief	サンプリング周波数.
	 * @note	サンプリング周波数を示すインデックス.<br>
	 *			<tr> <th>Index	</th> <th>サンプリング周波数[Hz]</th> </tr>
	 *			<tr> <td>0		</td> <td>44100					</td> </tr>
	 *			<tr> <td>1		</td> <td>48000					</td> </tr>
	 *			<tr> <td>3		</td> <td>予約済み				</td> </tr>
	 */
	E_SAMPLERATE_INDEX m_eSampleRateIndex;			// MPEG Frame Header 2 bits

	/**
	 * @brief	パディングビット.
	 * @note	0:パディングビットなし. 1:パディングビットあり.
	 */
	E_PADDING_BIT_INDEX m_ePaddingBit;					// MPEG Frame Header 1 bit

	/**
	 * @brief	未使用ビット.
	 */
	E_PRIVATE_BIT_INDEX m_ePrivateBit;						// MPEG Frame Header 1 bit

	/**
	 * @brief	チャネルモード.
	 * @note	チャネルを示すインデックス.<br>
	 *			<tr> <th>Index	</th> <th>チャネル数</th> <th>説明	</th> </tr>
	 *			<tr> <td>0		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>1		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>2		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>3		</td> <td>1			</td> <td>		</td> </tr>
	 */
	E_CHANNEL_MODE_INDEX m_eChannelMode;						// MPEG Frame Header 2 bits

	/**
	 * @brief	拡張モード.
	 *			<tr> <th>Index	</th> <th>Iステレオ	</th> <th>M/Sステレオ	</th> </tr>
	 *			<tr> <td>0		</td> <td>			</td> <td>				</td> </tr>
	 *			<tr> <td>1		</td> <td>			</td> <td>		<		/td> </tr>
	 *			<tr> <td>2		</td> <td>			</td> <td>				</td> </tr>
	 *			<tr> <td>3		</td> <td>			</td> <td>				</td> </tr>
	 */
	E_MODE_EXTENTION_INDEX m_eModeExtention;				// MPEG Frame Header 2 bits

	/**
	 * @brief	著作権保護.
	 * @note	0:著作権保護なし. 1:著作権保護あり.
	 */
	E_COPYRIGHT_INDEX m_eCopyright;					// MPEG Frame Header 1 bit

	/**
	 * @brief	オリジナル.
	 * @note	0:コピー. 1:オリジナル.
	 */
	E_ORIGINAL_INDEX m_eOriginal;					// MPEG Frame Header 1 bit

	/**
	 * @brief	強調.
	 * @note	0:強調. 1:50/15ms 2:予約済み. 3:CCIT J.17.
	 */
	E_EMPHASIS_INDEX m_eEmphasis;					// MPEG Frame Header 2 bits

	/////////////////////////////////////////////////////////////////////////////
	// サイド情報項目.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	CRC.
	 */
	unsigned short m_usCRCCheck;

	/**
	 * @brief	メインデータの開始位置.
	 */
	unsigned short m_usMainDataBegin;

	/**
	 * @brief	スケールファクター.
	 */
	unsigned short m_pusScfSi[2][4];		// [Channel][] 1Bit.

	/**
	 * @brief	グラニュール情報.
	 */
	T_GRANULE_INFO m_pGranuleInfo[2][2];		// [Channel][Granule].

	/////////////////////////////////////////////////////////////////////////////
	// メイン情報項目.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	メイン情報.
	 */
	unsigned char m_pbyMainData[2048];

	/**
	 * @brief	メイン情報 データサイズ.
	 */
	long	m_lMainDataSize;

	// debug用フラグ.
	bool	m_bIsDebug;
};

#endif

