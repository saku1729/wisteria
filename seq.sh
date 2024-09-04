#!/bin/sh
#------ pjsub option --------#
#PJM -L rscgrp=lecture-o
#PJM -L node=6
#PJM -o ./result.txt
#PJM --mpi proc=6
#PJM -L elapse=0:15:00
#PJM -g gh67
#PJM -j
#------- Program execution -------#
mpiexec ./a.out
