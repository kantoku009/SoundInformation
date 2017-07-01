#ifndef __CMPEGFRAME_H__
#define __CMPEGFRAME_H__

#include "CMpegFrame.h"

enum E_MPEG_VERSION_INDEX
{
	E_MPEG_VERSION_MIN=-1,
	E_MPEG25,			// bit 00=0:MPEG2.5.
	E_MPEG_RESERVED,	// bit 01=1:����`.
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
* Granule���
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
 * @brief	MPEG Frame�������N���X.
 */
class CMpegFrame
{
public:
	/**
	 * @brief	�R���X�g���N�^.
	 */
	CMpegFrame();

	/**
	 * @brief	�f�X�g���N�^.
	 */
	virtual ~CMpegFrame();

	/**
	 * @brief	������.
	 */
	void init();

	/**
	 * @brief	MPEG Frame Header���ۂ����m�F.
	 * @param	unsigned long i_ulHeader
	 * @return	true:MPEG Frame Header.
	 * @note	MPEG Frame Header��4[byte](32[bit])�ł���.
	 *			MPEG Frame Header�͐擪12[bit]��1���A�����Ă���.
	 *			(MPEG2.5�ɑΉ�����ꍇ��, �擪11[bit]��1���A�����Ă���)
	 */
	bool isHeader(unsigned long i_ulHeader) const;

	/**
	 * @brief	MPEG Frame Header��ݒ肷��.
	 * @param	unsigned long i_ulHeader
	 * @return	true:���� / false:���s.
	 */
	bool setHeader(unsigned long i_ulHeader);

	/**
	 * @brief	MPEG Frame Header���擾����.
	 * @param	�Ȃ�.
	 * @return	MPEG Frame Header
	 */
	unsigned long getHeader() const
	{
		return this->m_ulHeader;
	}

	/**
	 * @brief	MPEG Frame �T�C�Y���擾.
	 * @param	�Ȃ�.
	 */
	long getFrameSize() const;

	/**
	 * @brief	MPEG Main �f�[�^�T�C�Y���擾.
	 * @param	�Ȃ�.
	 */
	long getMainDataSize() const;

	/**
	 * @brief	�T���v�������擾.
	 * @param	�Ȃ�.
	 */
	long getSamples() const { return 1152; }

	/**
	 * @brief	�T���v�����O���g�����擾.
	 * @param	�Ȃ�.
	 */
	long getSampleRate() const; // Hz

	/**
	 * @brief	�r�b�g���[�g���擾.
	 * @param	�Ȃ�.
	 */
	long getBitrate() const; // Bits/Sec

	/**
	 * @brief	MPEG �o�[�W�������擾.
	 * @param	�Ȃ�.
	 * @return	0:MPEG2.5 1:MPEG2 3:MPEG1
	 */
	E_MPEG_VERSION_INDEX getVersionIndex() const { return m_eVersionIndex; }

	/**
	 * @brief	���C���[���擾.
	 * @param	�Ȃ�
	 * @return	���C���[�C���f�b�N�X.
	 */
	E_LAYER_INDEX getLayerIndex() const { return m_eLayerIndex; }

	/**
	 * @brief	�v���e�N�V�����r�b�g���擾.
	 * @param	�Ȃ�.
	 * @return	�v���e�N�V�����r�b�g.
	 */
	E_PROTECTION_BIT_INDEX getProtectionBit() const { return m_eProtectionBit; }

	/**
	 * @brief	BitRate�C���f�b�N�X���擾.
	 * @param	�Ȃ�.
	 * @return	BitRate�C���f�b�N�X.
	 */
	E_BITRATE_INDEX getBitrateIndex() const { return m_eBitrateIndex; }

	/**
	 * @brief	�T���v�����O���g���C���f�b�N�X���擾.
	 * @param	�Ȃ�.
	 * @return	�T���v�����O���g���C���f�b�N�X.
	 */
	E_SAMPLERATE_INDEX getSampleRateIndex() const { return m_eSampleRateIndex; }

	/**
	 * @brief	�p�f�B���O�r�b�g���擾.
	 * @param	�Ȃ�.
	 * @return	�p�f�B���O�r�b�g.
	 */
	E_PADDING_BIT_INDEX getPaddingBit() const { return m_ePaddingBit; }

	/**
	 * @brief	���g�p�r�b�g���擾.
	 * @param	�Ȃ�.
	 * @return	���g�p�r�b�g.
	 */
	E_PRIVATE_BIT_INDEX getPrivateBit() const { return m_ePrivateBit; }

	/**
	 * @brief	�`�����l�����[�h�C���f�b�N�X���擾.
	 * @param	�Ȃ�.
	 * @return	�`�����l�����[�h�C���f�b�N�X.
	 */
	E_CHANNEL_MODE_INDEX getMode() const { return m_eChannelMode; }

	/**
	 * @brief	�g�����[�h���擾.
	 * @param	�Ȃ�.
	 * @return	�g�����[�h.
	 */
	E_MODE_EXTENTION_INDEX getModeExtention() const { return m_eModeExtention; }

	/**
	 * @brief	���쌠�ی���擾.
	 * @param	�Ȃ�.
	 * @return	���쌠�ی���.
	 */
	E_COPYRIGHT_INDEX getCopyright() const { return m_eCopyright; }

	/**
	 * @brief	�I���W�i�����ۂ����擾.
	 * @param	�Ȃ�.
	 * @return	0:�R�s�[. 1:�I���W�i��. 
	 */
	E_ORIGINAL_INDEX getOriginal() const { return m_eOriginal; }

	/**
	 * @brief	�G���t�@�V�X���擾.
	 * @param	�Ȃ�.
	 * @return	�G���t�@�V�X��\���C���f�b�N�X.
	 */
	E_EMPHASIS_INDEX getEmphasis() const { return m_eEmphasis; }
	
	/**
	 * @brief	�`�����l�������擾.
	 * @param	�Ȃ�.
	 * @return	�`�����l����.
	 */
	unsigned short getChannels() const
	{
		return (E_CHANNEL_MODE3==m_eChannelMode)? 1:2;
	}

	/**
	 * @brief	CRC�����擾.
	 * @param	�Ȃ�.
	 * @return	CRC���.
	 */
	unsigned short getCRCCheck() const
	{
		return m_usCRCCheck;
	}

	/**
	 * @brief	CRC����ݒ�.
	 * @param	unsigned short i_usCRCCheck	CRC���.
	 * @return	����/���s.
	 */
	void setCRCCheck(unsigned short i_usCRCCheck)
	{
		m_usCRCCheck = i_usCRCCheck;
	}

	/**
	 * @brief	�T�C�h����ݒ�.
	 * @param	char* a_bySide
	 * @return	����/���s.
	 */
	bool setSideInfo(char* i_bySide);

	/**
	 * @brief	�T�C�h���̃T�C�Y���擾.
	 * @
	 */
	unsigned short getSideSize()
	{
		return (1==this->getChannels())? 17:32;
	}
	
	/**
	 * @brief	���C���f�[�^��ݒ�.
	 * @param	[in]char* i_pMainData
	 * @param	[in]long i_lSize
	 * @return	����/���s.
	 */
	bool setMainData(char* i_pMainData, long i_lSize);

	/**
	 * @brief	
	 * @param	�Ȃ�.
	 * @return	
	 * @note	1�r�b�g�ڂ�1�̏ꍇ,MPEG1. 1�r�b�g�ڂ�0�̏ꍇ,MPEG2 or MPEG2.5.
	 */
	unsigned short IsLSF() const
	{
		return (m_eVersionIndex&0x01);
	}

	/**
	 * @brief	
	 * @param	�Ȃ�.
	 * @return	
	 */
	unsigned short getGranules() const
	{
		return (IsLSF()==0)? 2:1;
	}

	/**
	 * @brief	MPEG Frame Header�����o��.
	 * @param	�Ȃ�.
	 * @return	�Ȃ�.
	 * @note	debug�p�ɏ����o��.
	 */
	void printHeaderInfo();

	//Side���@�idebug�p�Ɏ擾�ł���悤�ɂ���j
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
	 * @brief	MPEG Frame Header�̐ݒ�i�������j.
	 * @param	[in ] const unsigned long i_ulHeader,
	 * @param	[in ] const unsigned long i_ulMask,
	 * @param	[in ] const unsigned long i_ulShift,
	 * @param	[in ] const long i_ulMin,
	 * @param	[in ] const long i_ulMax,
	 * @param	[out] long& i_ulValue
	 * @return	����/���s.
	 */
	bool setHeaderValueImp(
			const unsigned long i_ulHeader,
			const unsigned long i_ulMask,
			const unsigned long i_ulShift,
			const long i_ulMin,
			const long i_ulMax,
			long* i_ulValue);

	/**
	 * @brief	Version��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return ����/���s.
	 */
	bool setVersionIndex(unsigned long i_ulHeader);

	/**
	 * @brief	Layer��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setLayerIndex(unsigned long i_ulHeader);

	/**
	 * @brief	�v���e�N�V�����r�b�g��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setProtectionBit(unsigned long i_ulHeader);

	/**
	 * @brief	�r�b�g���[�g�C���f�b�N�X��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setBitrateIndex(unsigned long i_ulHeader);

	/**
	 * @brief	�T���v�����O���g���C���f�b�N�X��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setSampleRateIndex(unsigned long i_ulHeader);

	/**
	 * @brief	�p�f�B���O�r�b�g��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setPaddingBit(unsigned long i_ulHeader);

	/**
	 * @brief	���g�p�r�b�g��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setPrivateBit(unsigned long i_ulHeader);

	/**
	 * @brief	�`�����l�����[�h��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setChannelMode(unsigned long i_ulHeader);

	/**
	 * @brief	�g�����[�h��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setMoedExtention(unsigned long i_ulHeader);

	/**
	 * @brief	���쌠����ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setCopyright(unsigned long i_ulHeader);

	/**
	 * @brief	�I���W�i�����ۂ���ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setOriginal(unsigned long i_ulHeader);

	/**
	 * @brief	�G���t�@�V�X��ݒ�.
	 * @param	unsigned long i_ulHeader
	 * @return	����/���s.
	 */
	bool setEmphasis(unsigned long i_ulHeader);


	/**
	 * @brief	Mpeg Frame Header.
	 */
	unsigned long	m_ulHeader;

	/////////////////////////////////////////////////////////////////////////////
	//�t���[���w�b�_�[����.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	ID.
	 * @param	�Ȃ�.
	 * @return	0:MPEG2.5 1:MPEG2 2:����` 3:MPEG1.
	 * @note	MPEG Frame Header 12-13�r�b�g��. MPEG2.5���l�����Ă���.
	 */
	E_MPEG_VERSION_INDEX m_eVersionIndex;			// MPEG Frame Header 2 bit

	/**
	 * @brief	���C���[.
	 * @param	�Ȃ�.
	 * @return	0:�\��ς�. 1:���C���[III 2:���C���[II 3:���C���[I.
	 */
	E_LAYER_INDEX m_eLayerIndex;						// MPEG Frame Header 2 bits

	/**
	 * @brief	�ی�r�b�g.
	 * @return	0:CRC�ی삠��. 1:CRC�ی�Ȃ�.
	 */
	E_PROTECTION_BIT_INDEX m_eProtectionBit;				// MPEG Frame Header 1 bit

	/**
	 * @brief	�r�b�g���[�g.
	 * @note	�r�b�g���[�g�������C���f�b�N�X.<br>
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
	 *			<tr> <td>15		</td> <td>�s���l	</td> <td>�s���l	</td> <td>�s���l	</td> </tr>
	 */
	E_BITRATE_INDEX m_eBitrateIndex;				// MPEG Frame Header 4 bits

	/**
	 * @brief	�T���v�����O���g��.
	 * @note	�T���v�����O���g���������C���f�b�N�X.<br>
	 *			<tr> <th>Index	</th> <th>�T���v�����O���g��[Hz]</th> </tr>
	 *			<tr> <td>0		</td> <td>44100					</td> </tr>
	 *			<tr> <td>1		</td> <td>48000					</td> </tr>
	 *			<tr> <td>3		</td> <td>�\��ς�				</td> </tr>
	 */
	E_SAMPLERATE_INDEX m_eSampleRateIndex;			// MPEG Frame Header 2 bits

	/**
	 * @brief	�p�f�B���O�r�b�g.
	 * @note	0:�p�f�B���O�r�b�g�Ȃ�. 1:�p�f�B���O�r�b�g����.
	 */
	E_PADDING_BIT_INDEX m_ePaddingBit;					// MPEG Frame Header 1 bit

	/**
	 * @brief	���g�p�r�b�g.
	 */
	E_PRIVATE_BIT_INDEX m_ePrivateBit;						// MPEG Frame Header 1 bit

	/**
	 * @brief	�`���l�����[�h.
	 * @note	�`���l���������C���f�b�N�X.<br>
	 *			<tr> <th>Index	</th> <th>�`���l����</th> <th>����	</th> </tr>
	 *			<tr> <td>0		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>1		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>2		</td> <td>2			</td> <td>		</td> </tr>
	 *			<tr> <td>3		</td> <td>1			</td> <td>		</td> </tr>
	 */
	E_CHANNEL_MODE_INDEX m_eChannelMode;						// MPEG Frame Header 2 bits

	/**
	 * @brief	�g�����[�h.
	 *			<tr> <th>Index	</th> <th>I�X�e���I	</th> <th>M/S�X�e���I	</th> </tr>
	 *			<tr> <td>0		</td> <td>			</td> <td>				</td> </tr>
	 *			<tr> <td>1		</td> <td>			</td> <td>		<		/td> </tr>
	 *			<tr> <td>2		</td> <td>			</td> <td>				</td> </tr>
	 *			<tr> <td>3		</td> <td>			</td> <td>				</td> </tr>
	 */
	E_MODE_EXTENTION_INDEX m_eModeExtention;				// MPEG Frame Header 2 bits

	/**
	 * @brief	���쌠�ی�.
	 * @note	0:���쌠�ی�Ȃ�. 1:���쌠�ی삠��.
	 */
	E_COPYRIGHT_INDEX m_eCopyright;					// MPEG Frame Header 1 bit

	/**
	 * @brief	�I���W�i��.
	 * @note	0:�R�s�[. 1:�I���W�i��.
	 */
	E_ORIGINAL_INDEX m_eOriginal;					// MPEG Frame Header 1 bit

	/**
	 * @brief	����.
	 * @note	0:����. 1:50/15ms 2:�\��ς�. 3:CCIT J.17.
	 */
	E_EMPHASIS_INDEX m_eEmphasis;					// MPEG Frame Header 2 bits

	/////////////////////////////////////////////////////////////////////////////
	// �T�C�h��񍀖�.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	CRC.
	 */
	unsigned short m_usCRCCheck;

	/**
	 * @brief	���C���f�[�^�̊J�n�ʒu.
	 */
	unsigned short m_usMainDataBegin;

	/**
	 * @brief	�X�P�[���t�@�N�^�[.
	 */
	unsigned short m_pusScfSi[2][4];		// [Channel][] 1Bit.

	/**
	 * @brief	�O���j���[�����.
	 */
	T_GRANULE_INFO m_pGranuleInfo[2][2];		// [Channel][Granule].

	/////////////////////////////////////////////////////////////////////////////
	// ���C����񍀖�.
	/////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief	���C�����.
	 */
	unsigned char m_pbyMainData[2048];

	/**
	 * @brief	���C����� �f�[�^�T�C�Y.
	 */
	long	m_lMainDataSize;

	// debug�p�t���O.
	bool	m_bIsDebug;
};

#endif

