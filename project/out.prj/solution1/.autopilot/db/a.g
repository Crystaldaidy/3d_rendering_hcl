#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/dnd29/3D_redering_DDY/project/out.prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}