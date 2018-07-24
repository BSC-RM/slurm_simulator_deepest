This is a version of SLURM simulator's code improved and ported to SLURM 17.11 at Barcelona Supercomputing Center by Ana Jokanovic and Marco D'Amico. The reference paper on the simulator's validation is "Evaluating SLURM simulator with real-machine SLURM and vice versa" published at PMBS18 (https://ieeexplore.ieee.org/document/8641556).
The starting point for the improvements was the simulator's version by Gonzalo Rodrigo from Umea University & Berkley Lab reported in the paper https://link.springer.com/chapter/10.1007/978-3-319-77398-8\_9.

COMPILATION:
The code is tested on MareNostrum4 machine after being compiled with gcc 7.2.0 compiler.
Install and compile the code using installi\_slurm\_sim.sh script, it calls compile\_and\_install\_slurm.sh.

Simulator's source code is under slurm directory.
SLURM daemons' binaries will be installed in install/slurm\_programs/sbin.
SLURM and SLURM simulator's binaries will be installed in install/slurm\_programs/bin.

CONFIGURATION:
Before you start the simulation make sure you change in the all the files bsc33882 to your account name; the account name should appear only in install/slurm\_conf/slurm.conf.template and install/slurm\_conf/users.sim.
Configuration file template is under install/slurm\_conf/slurm.conf.template; here you should set your configuration.
Also, in slurm\_conf/user.sim file make sure all the users are set to correct ids (check: id -u username).

LAUNCHING SIMULATOR ON MARENOSTRUM:
submit\_serial\_simulation.sh is a script to submit the simulator for execution within a job on MareNostrum4 machine with SLURM job scheduler (adapt it for your machine).
The simulation is started by:

sbatch submit\_serial\_simulation.sh 0 ../trace\_name
#preferably always use full path on Marenostrum
#e.g. 	batch submit\_serial\_simulation.sh 0 /home/bsc18/bsc18997/SLURM\_SIMULATOR-master/cirne.10n.maxjob8n.anl.200.sim

INPUTS:
cirne.3456n.maxjob128n.anl.5k.1.1.sim is a big input trace example of 5000 jobs generated by CIRNE model for the system of 3456 nodes, max job size 128 nodes.
cirne.10n.maxjob8n.anl.200.arrin10min.jobcomp.sim is a small input trace example of 200 jobs generated by CIRNE model for the system of 10 nodes, max job size 8 nodes.

OUTPUTS:
Job completion log will be under simulation\_$JOBID/TRACES/trace.test.$JOBID.
SLURM daemons'logs, if enabled in slurm.conf, will be under slurm\_varios/log/.

CONFIGURING SIMULATIONS TO RUN LOCALLY ON UBUNTU MACHINES (OR VMs):
Repeat the COMPILATION and CONFIGURATION steps above plus the steps below.

REPLACE TOKENS WITH YOUR HOSTNAME:

#e.g.	$>#hostname
#$>renan-Latitude-E7450
#edit install/slurm\_conf/slurm.conf.template
#ControlMachine=renan-Latitude-E7450
#ControlAddr=renan-Latitude-E7450
#FrontendName=renan-Latitude-E7450

EDIT PORTS:

#e.g.	edit install/slurm\_conf/slurm.conf.template
#SlurmctldPort=68256
#SlurmdPort=68189

RUNNING SIMULATION LOCALLY IN UBUNTU MACHINES (OR VMs):
run\_local\_simulation.sh is a script to launch a simulation locally in your laptop or VM running Ubuntu.

#e.g.	run\_local\_simulation.sh 0 /home/renan/SLURM\_SIMULATOR-master/cirne.10n.maxjob8n.anl.200.sim
