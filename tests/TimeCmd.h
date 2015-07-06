﻿#ifndef TIMECMD_H
#define TIMECMD_H

/// @file TimeCmd.h
/// @brief TimeCmd のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011 Yusuke Matsunaga
/// All rights reserved.

// 時間計測を行うパッケージ


#include "tclpp/TclCmd.h"
#include "utils/StopWatch.h"


BEGIN_NAMESPACE_YM_TCLPP

//////////////////////////////////////////////////////////////////////
// ストップウォッチ操作を行うコマンド用のクラス
//////////////////////////////////////////////////////////////////////
class StpwatchObj :
  public TclCmd
{
public:

  // コンストラクタ
  StpwatchObj();

  // デストラクタ
  virtual
  ~StpwatchObj();


protected:

  // usage を出力する関数
  virtual
  void
  usage();

  // コマンドを実行する仮想関数
  virtual
  int
  cmd_proc(TclObjVector& objv);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 本当のストップウォッチオブジェクト
  StopWatch mStopWatch;

};


//////////////////////////////////////////////////////////////////////
// タイマーオブジェクトを生成するコマンドクラス
//////////////////////////////////////////////////////////////////////
class StpwatchCls :
  public TclCmdCls
{
protected:

  // StpwatchObjのオブジェクトを生成する仮想関数
  virtual
  TclCmd*
  create_obj() const;

};


//////////////////////////////////////////////////////////////////////
// 時間計測コマンド
//////////////////////////////////////////////////////////////////////
class TimeCmd :
  public TclCmd
{
public:

  // コンストラクタ
  TimeCmd();

  // デストラクタ
  virtual
  ~TimeCmd();


protected:

  // コマンド処理関数
  virtual
  int
  cmd_proc(TclObjVector& objv);


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // 時間計測を行うオブジェクト
  StopWatch mStopWatch;

  // 今までの経過時間
  USTime mTotalTime;
};

END_NAMESPACE_YM_TCLPP

#endif // TIMECMD_H
