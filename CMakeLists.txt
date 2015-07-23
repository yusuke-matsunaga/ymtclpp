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

enable_testing()


# ===================================================================
# パッケージの検査
# ===================================================================
list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include (FindDoxygen)

find_package (TCL REQUIRED)
find_package (YmTools REQUIRED)
find_package (Gperftools)
find_package (GTest)

include (ym_add_library)


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
#  ソースファイルの設定
# ===================================================================

set (SOURCES
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


# ===================================================================
#  release ターゲットの設定
# ===================================================================
ym_add_library (ym_tclpp
  SHARED
  ${SOURCES}
  )

foreach (_libname ym_tclpp ym_tclpp_p ym_tclpp_d)
  target_link_libraries(${_libname}
    ${TCL_LIBRARY}
    )
endforeach ()

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
  TARGETS ym_tclpp ym_tclpp_p ym_tclpp_d
  DESTINATION lib
  EXPORT ymtclpp-targets
  )

install(
  DIRECTORY YmTclpp
  DESTINATION include
  )

install (
  EXPORT ymtclpp-targets
  DESTINATION lib/ymtclpp-${YMTCLPP_VERSION}
  )

install (FILES
  ${PROJECT_BINARY_DIR}/YmTclppConfig.cmake
  ${PROJECT_BINARY_DIR}/YmTclppConfig-version.cmake
  DESTINATION lib/ymtclpp-${YMTCLPP_VERSION}
  )
