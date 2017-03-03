Wave File Format
====================
# はじめに

WAVEファイルのFormatを解説する。

# Chunk

WAVEファイルはChunkという構成要素からなる。  
WAVEファイルは以下のChunkを必ず含む。  

+ RIFF
+ fmt
+ data

他にもChunkはあるがオプションの為、省略する。  

## RIFF Chunk

WAVEファイルの先頭には必ずRIFF Chunkがある。  
WAVEファイルは、RIFFファイルの一種。  
RIFFファイルはコンテナである為、WAVEファイル以外にも種類はあるらしいが省略。  

RIFF Chunkの構造を以下に示す。  

|フィールド名	|サイズ		|説明				|  
|:-				|:-			|:-					|  
|Chunk ID		|4[Byte]	|'RIFF'				|  
|Chunk Size		|4[Byte]	|ファイルサイズ-8	|  
|RIFF Type		|4[Byte]	|'WAVE'				|  

C言語の構造体で表すと以下のように定義される。

```C
struct
{
  char 	m_szID[4];		// 'RIFF'
  long	m_lSize;		// ファイルサイズ-8[byte]. リトルエンディアン.
  char	m_szType[4];	// 'WAVE'
}；
```

## fmt  Chunk

WAVEファイルの種々の情報が格納されているChunk。  
拡張されたFMTEXもあるようだが、省略。  

fmt Chunkの構造を以下に示す。  

|フィールド名	|サイズ		|説明								|  
|:-				|:-			|:-									|  
|Chunk ID		|4[Byte]	|'fmt '(最後は空白). 	|  
|Chunk Size		|4[Byte]	|FMTチャンクのサイズ				|  
|FMT Chunk		|n[Byte]	|FMT Chunkを参照. ※				|  

※FMT ChunkとFMTEX Chunkでサイズが異なる。  

FMT Chunk.

|フィールド名	|サイズ		|説明							|  
|:-				|:-			|:-								|  
|FormatTag		|2[Byte]	|フォーマットタグ. PCMならば1.	|  
|Channels		|2[Byte]	|チャンネル数					|  
|SamplesPerSec	|4[Byte]	|サンプリング周波数				|  
|AvgBytesPerSec	|4[Byte]	|単位時間当たりのサイズ			|  
|BlockAlign		|2[Byte]	|1ブロックのサイズ				|  
|BitsPerSample	|2[Byte]	|量子化ビット					|  

C言語の構造体で表すと以下のように定義される。

```C
struct
{
  char			m_szID[4];	// 'fmt '
  long			m_lSize;	// struct T_FMTのサイズ. リトルエンディアン.
  struct T_FMT	m_stFmt;	// fmt Chunk.
};

struct T_FMT
{
	short m_wFormatTag;		// フォーマットタグ. PCMならば1.
	short m_nChannels;		// チャンネル数.
	long m_nSamplesPerSec;	// サンプリング周波数.
	long m_nAvgBytesPerSec;	// 単位時間あたりのサイズ.
	short m_nBlockAlign;	// 1ブロックのサイズ.
	short m_wBitsPerSample;	// 量子化ビット.
};
```

## data Chunk

波形データ(サンプル値)が格納されたChunk。  

data Chunkの構造を以下に示す。  

|フィールド名	|サイズ		|説明						|  
|:-				|:-			|:-							|  
|Chunk ID		|4[Byte]	|'data'						|  
|Chunk Size		|4[Byte]	|data Chunkのサイズ			|  
|Sample			|n[Byte]	|波形データ(サンプル値) ※	|  

※(量子化ビット/8) \* サンプリング周波数 \* チャンネル数 \* 時間[秒]のバイト数となる.

C言語の構造体で表すと以下のように定義される。

```C
struct
{
  char				m_szID[4];	// 'data'
  long				m_lSize;	// 全サンプルのサイズ[byte]. リトルエンディアン.
  unsigned char*	m_pSample;	// 波形データ(サンプル値).
};
```
