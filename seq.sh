#!/bin/sh
#------ pjsub option --------#
#PJM -L rscgrp=lecture-o
#PJM -L node=12
#PJM --mpi proc=576
#PJM -L elapse=0:01:00
#PJM -o b.out
#PJM -g gh67
#PJM -j
#------- Program execution -------#
mpiexec ./a.out
