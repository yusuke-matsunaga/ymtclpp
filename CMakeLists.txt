# ===================================================================
# CMAKE のおまじない
# ===================================================================
cmake_minimum_required (VERSION 3.2)


# ===================================================================
# プロジェクト名，バージョンの設定
# ===================================================================
project (ymtclpp)
set (YMTCLPP_VERSION_MAJOR 1)
set (YMTCLPP_VERSION_MINOR 0)
set (YMTCLPP_VERSION "${YMTCLPP_VERSION_MAJOR}.${YMTCLPP_VERSION_MINOR}")


# ===================================================================
# CTest モジュールの読み込み
# ===================================================================
include (CTest)


# ===================================================================
# パッケージの検査
# ===================================================================

include (FindDoxygen)

find_package(TCL REQUIRED)

find_package (YmTools REQUIRED)

find_package (GTest)


# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${YmTools_INCLUDE_DIRS}
  ${TCL_INCLUDE_PATH}
  )


# ===================================================================
#  ターゲットの設定
# ===================================================================
add_library(ym_tclpp
  src/StrBuf.h
  src/TclBase.cc
  src/TclCmd.cc
  src/TclHandler.cc
  src/TclObj.cc
  src/TclObjMsgHandler.cc
  src/TclPopt.cc
  src/TclPoptGroup.h
  src/TclVarTrace.cc
  )

target_link_libraries(ym_tclpp
  ${TCL_LIBRARY}
  )


# ===================================================================
# パッケージコンフィグレーションファイルの生成
# ===================================================================

configure_file(
  ${PROJECT_SOURCE_DIR}/etc/YmTclppConfig.cmake.in
  ${PROJECT_BINARY_DIR}/YmTclppConfig.cmake
  @ONLY
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/etc/YmTclppConfig-version.cmake.in
  ${PROJECT_BINARY_DIR}/YmTclppConfig-version.cmake
  @ONLY
  )


# ===================================================================
#  インストールターゲットの設定
# ===================================================================

install(
  TARGETS ym_tclpp
  DESTINATION lib
  EXPORT ymtclpp-targets
  )

install(
  DIRECTORY YmTclpp
  DESTINATION include
  )

install (
  EXPORT ymtclpp-targets
  DESTINATION lib/ymtclpp-${YMTOOLS_VERSION}
  )

install (FILES
  ${PROJECT_BINARY_DIR}/YmTclppConfig.cmake
  ${PROJECT_BINARY_DIR}/YmTclppConfig-version.cmake
  DESTINATION lib/ymtclpp-${YMTCLPP_VERSION}
  )
