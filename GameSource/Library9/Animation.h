#pragma once

#include "Function.h"


//アニメーションクラス
class Animation
{
public:

	Animation();
	~Animation();

	//キーフレームの生成
	void	CreateKey(int numkey);

	//生成した配列に値を設定
	void	SetKeyValue(int index,float key,float value);

	//アニメーション全体の継続時間の設定
	void	SetDuration(DWORD duration);

	//アニメーションをループするかどうかの設定
	void	SetLoopFlag(DWORD isLoop);

	//アニメーションの開始時刻の設定
	void	SetStartTime(DWORD start);


	//時刻に対応する値を取得
	bool	GetValue(DWORD time, float* value, bool* isEnd);

	//時刻を割合に変換
	float	GetFraction(DWORD time);

	//割合に対応するインデックスを取得
	int		GetBeginIndex(float fraction);



private:
	int		m_numKey;		//キーの数
	float*	m_keys;			//キーを格納する配列のポインタ
	float*	m_values;		//キーに対する値を格納する配列のポインタ
	DWORD	m_duration;		//継続時間
	DWORD	m_isLoop;		//ループさせるかのフラグ
	DWORD	m_startTime;	//スタート時刻
};