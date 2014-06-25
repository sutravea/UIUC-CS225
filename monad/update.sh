#!/usr/bin/env bash
# Clean monad_dev
mkdir -p source

# Monad Binary
cp ../monad_dev/monad .
cp ../monad_dev/source/memcheck.h source
cp ../monad_dev/source/Makefile.proxy source
cp ../monad_dev/source/config.ini source
cp ../monad_dev/source/memcheck.h source
cp ../monad_dev/source/monad_shared.cpp source
cp ../monad_dev/source/monad_shared.h source
cp ../monad_dev/source/pipestream.cpp source
cp ../monad_dev/source/pipestream.h source
cp ../monad_dev/source/proxy.cpp source
cp ../monad_dev/source/proxy.h source
cp ../monad_dev/source/util.cpp source
cp ../monad_dev/source/util.h source
cp ../monad_dev/source/filemap.h source
cp ../monad_dev/source/filemap.cpp source
cp ../monad_dev/source/valgrind.h source

# Monad Source
cp ../monad_dev/source/Makefile source
cp ../monad_dev/source/LICENSE.txt source
cp ../monad_dev/source/monad.h source
cp ../monad_dev/source/monad.cpp source
cp ../monad_dev/source/quotes.txt source
cp ../monad_dev/source/random.h source
cp ../monad_dev/source/README.txt source
cp ../monad_dev/source/README_config.txt source
cp ../monad_dev/source/README_tests.txt source
cp ../monad_dev/source/help.cpp source
cp ../monad_dev/source/ccmonad.cpp source
