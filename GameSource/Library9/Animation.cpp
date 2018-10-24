#include "Animation.h"


//コンストラクタ
Animation::Animation() : m_numKey(0),m_keys(0),m_values(0),m_isLoop(TRUE),
m_startTime(0),m_duration(0)
{

}

//デストラクタ
Animation::~Animation()
{
	if (m_keys != 0) { delete[] m_keys; }
	if (m_values != 0) { delete[] m_values; }
}


//キーフレームの生成
void	Animation::CreateKey(int numberKey)
{
	//キーフレーム数をメンバ変数に保存
	m_numKey = numberKey;

	//既存の古いデータを削除
	if (m_keys != 0)
	{
		delete[] m_keys;
	}
	if (m_values != 0)
	{
		delete[] m_values;
	}

	//新しい配列の生成
	m_keys	= new float[numberKey];
	m_values	= new float[numberKey];
}



//生成した配列に値を設定
void	Animation::SetKeyValue(int index, float key, float value)
{
	//インデックスが0より小さい、または現在のキーの数以上なら何もしない
	if ((index < 0) || (index >= m_numKey))
	{
		return;
	}

	m_keys[index]		= key;
	m_values[index]	= value;
}


//アニメーション全体の継続時間の設定
void	Animation::SetDuration(DWORD duration)
{
	//アニメーション全体の継続時間をメンバ変数に保存
	m_duration = duration;
}



//アニメーションをループさせるかの設定
void	Animation::SetLoopFlag(DWORD isLoop)
{
	m_isLoop = isLoop;
}


//アニメーションの開始時刻の設定
void	Animation::SetStartTime(DWORD start)
{
	m_startTime = start;
}


//時刻に対応する値を取得
bool	Animation::GetValue(DWORD time, float* value, bool* isEnd)
{
	//不正の場合の処理
	if (value == 0) { return false; }
	if (isEnd == 0) { return false; }
	if (m_numKey <= 0) { return false; }

	//アニメーションが終了していた時の処理
	DWORD	endTime = m_startTime + m_duration;

	if (!m_isLoop)
	{
		if (time < m_startTime)
		{
			//時刻が開始時刻よりも小さいなら最初の値を返す
			*value = m_values[0];
			*isEnd = true;
			return true;
		}
		else if (time > endTime)
		{
			//時刻が終了時刻よりも大きいなら最後の値を返す
			*value = m_values[m_numKey - 1];
			*isEnd = true;
			return true;
		}
	}

	//アニメーションの計算
	int		beginIndex;
	int		endIndex;
	float	fraction;
	float	slope;

	//現在時刻を割合に変換
	fraction = GetFraction(time);
	//現在時刻に最も近い直前のキーフレーム取得
	beginIndex = GetBeginIndex(fraction);
	//現在時刻に最も近い直後のキーフレーム取得
	endIndex = beginIndex + 1;

	//値の計算
	if (beginIndex < 0)		//アニメーションの開始前
	{
		*value = m_values[0];	//最初のキーフレームの値を返す
	}
	else if (beginIndex >= m_numKey - 1)	//アニメーション終了後
	{
		*value = m_values[m_numKey - 1];	//最後のキーフレームの値を返す
	}
	else
	{
		//傾きの計算
		float	diffValue = m_values[endIndex] - m_values[beginIndex];	//キーフレーム間の値の差
		float	diffTime = m_keys[endIndex] - m_keys[beginIndex];		//キーフレーム間の継続時間
		slope = diffValue / diffTime;	//傾き

		//現在値を求める
		float	fPastFromPrev = fraction - m_keys[beginIndex];	//直前のキーフレームからの継続時間
		*value = slope * fPastFromPrev + m_values[beginIndex];	//現在値の計算
	}

	*isEnd = false;
	return true;
}



//時刻を割合に変換
float	Animation::GetFraction(DWORD time)
{
	DWORD	diffTime;
	float	fraction;

	//時刻から割合を求める
	if (m_duration == 0)
	{
		fraction = 1.0f;
	}
	else
	{
		if (time > m_startTime)
		{
			//現在時刻からスタート時刻を引く
			diffTime = time - m_startTime;
			//ループ対応
			diffTime = diffTime % m_duration;
			//割合の計算
			fraction = (float)diffTime / (float)m_duration;
			//小数部分だけ使用
			fraction = fraction - (int)fraction;
		}
		else
		{
			//現在時刻が、スタート時刻より小さいとき
			//タイマーが一周してしまったとき発生
			diffTime = m_startTime - time;
			diffTime = diffTime % m_duration;
			fraction = (float)diffTime / (float)m_duration;
			fraction = 1.0f - (fraction - (int)fraction);
		}
	}

	return fraction;
}



//割合に対応するインデックスを取得
int		Animation::GetBeginIndex(float fraction)
{
	if (fraction < m_keys[0]) { return -1; }

	//引数に指定された割合とキーフレームの割合を比較
	int	index = 0;
	for (int i = 0; i < m_numKey; i++)
	{
		//キーフレームより大きくなったら発見
		if (m_keys[i] <= fraction)
		{
			index = i;
		}
		else
		{
			break;
		}
	}
	return index;
}