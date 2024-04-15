# tyju_LoadBalanceCluster

This program runs on top of an MPI cluster utilizing MPICH. 
To compile: make install
To run: mpirun -hosts hostsfile ./main

Be sure that the hostsfile only assigns 1 process to each physical computer,
as the program improves and scales, the single processes will thread out on each physical as needed.
This program is meant to calculate priority service values for each physical computer and with that, 
dynamically load balance a distributed program on top of a cluster of different computers with different resources.

Ex: my cluster was a laptop from 2007, a 1U server from 2012, and a desktop from 2005, all with different specs.