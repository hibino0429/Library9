#pragma once
#pragma comment(lib,"dsound.lib")

//#include <mmsystem.h>
#include "../Function.h"
//#include <mmiscapi.h>
#include <windows.h>
#include <mmiscapi2.h>



//’è‹`-------------------------------------------------------------
#define WAVEFILE_READ	1

#define DELETE_SAFE_ARRAY(me) {if(me){delete[] (me); (me) = NULL;}}
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = NULL;} }
#define SAFE_DELETE_ARRAY(p) { if(p){delete[] (p); (p) = NULL;} }
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = NULL;} }

//-----------------------------------------------------------------
//WaveFile‚ÉŠÖ‚·‚éƒNƒ‰ƒX
//-----------------------------------------------------------------
class CWaveFile
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
	HMMIO         m_hmmio;       // MM I/O handle for the WAVE
	MMCKINFO      m_ck;          // Multimedia RIFF chunk
	MMCKINFO      m_ckRiff;      // Use in opening a WAVE file
	DWORD         m_dwSize;      // The size of the wave file
	MMIOINFO      m_mmioinfoOut;
	DWORD         m_dwFlags;
	BOOL          m_bIsReadingFromMemory;
	BYTE*         m_pbData;
	BYTE*         m_pbDataCur;
	ULONG         m_ulDataSize;
	CHAR*         m_pResourceBuffer;

protected:
	HRESULT ReadMMIO();
	HRESULT WriteMMIO(WAVEFORMATEX *pwfxDest);

public:
	CWaveFile();
	~CWaveFile();

	HRESULT Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
	HRESULT OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags);
	HRESULT Close();

	HRESULT Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
	HRESULT Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);

	DWORD   GetSize();
	HRESULT ResetFile();
	WAVEFORMATEX* GetFormat() { return m_pwfx; };
};