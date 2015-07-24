#! /bin/sh

# mk_builddir.sh
#
# コンパイル用のディレクトリを作るシェルスクリプト
#
# Copyright (C) 2015 Yusuke Matsunaga
# All rights reserved


# このファイルのあるディレクトリを srcdir にセットする．
basedir=`dirname $0`
srcdir=`cd $basedir; pwd`

while [ $# -ge 4 ] ; do
    if [ $1 = "--ymtools_dir" ]; then
	ymtoolsdir=$2
	shift; shift
    fi
done

if [ $# -ne 2 ]; then
    echo "USAGE mk_builddir.sh [--ymtools_dir <ymtools-dir>] <compiledir> <installdir>"
    exit 1
fi

# ビルド用のディレクトリ名
builddir=$1

# インストール先のディレクトリ名
installdir=$2

echo "****"
echo "source  directory: $srcdir"
echo "build   directory: $builddir"
echo "install directory: $installdir"
if [ "x$ymtoolsdir" != x ]; then
    echo "ymtools directory: $ymtoolsdir"
fi
echo "****"
echo -n "continue ? (yes/no)"
while read confirmation; do
    case $confirmation in
	"yes")
	    break;;
	"no")
	    exit 0;;
	*)
	    echo "please answer 'yes' or 'no'"
	    echo -n "continue ? (yes/no)"
	    ;;
    esac
done

# ビルドディレクトリはなければ作る．
test -d $builddir || mkdir -p $builddir

# do_cmake ファイルを作る．
do_cmake="do_cmake.sh"
sed "-e s!___SRC_DIR___!$srcdir!" \
    "-e s!___INSTALL_DIR___!$installdir!" \
    "-e s!___YMTOOLS_DIR___!$ymtoolsdir!" \
    ${srcdir}/etc/${do_cmake}.in > ${builddir}/${do_cmake}
chmod +x $builddir/${do_cmake}

# do_cmake.sh を実行する．
echo "running cmake"
(cd $builddir && ./${do_cmake})

echo "done"
