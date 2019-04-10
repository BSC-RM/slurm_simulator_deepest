#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

#define M 200*1024*1024/8 //+17
#define N (M+100)
#define LFREQ 15
#define NUMEVENTS 26

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

double Rand01(){return (double)rand() / (double)RAND_MAX;}

int main (int argc, char *argv[])
{
	double alpha;
	double c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
	double x, x1, x2, x3, x4, x5;
	double y, y1, y2, y3, y4, y5; 
	double eTime, t1, t2, minTime;
	double GLoops, GFlops, GBytes, TimeLoop, flopsCount, bytesCount, memCount;
	
//	double A[N], B[N], C[N], D[N], IND[N];
	double *A=NULL, *B=NULL, *C=NULL, *D=NULL, *IND=NULL;

	int error;
	int vl, i, j, k, j1, irep, it, ln, iter;
	int nprocs, myid, provided;

	int initialDC, endDC;

    char experiment[20], params[150];

	FILE *fEnergy=NULL;

	if (argc != 7)
	{
		printf ("Error on the number of input parameters\n");
		return -1;
	}

	//MPI_Init_thread(MPI_THREAD_MULTIPLE, &provided);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	#ifdef PADDLECARD
	if (myid==0)
	{
		fEnergy=fopen("/sys/devices/platform/aem.0/energy1_input", O_RW);
		fread(fEnergy, "%d", &initialDC);
		fclose(fEnergy);
	}
	#endif

	A = (double *) malloc (N*sizeof(double));
	if (!A)
	{
		perror("A");
		return -1;
	}

	B = (double *) malloc (N*sizeof(double));
	if (!B)
	{
		perror("B");
		free (A);
		return -1;
	}

	C = (double *) malloc (N*sizeof(double));
	if (!C)
	{
		perror("C");
		free (B);
		free (A);
		return -1;
	}

	D = (double *) malloc (N*sizeof(double));
	if (!D)
	{
		perror("D");
		free (C);
		free (B);
		free (A);
		return -1;
	}

	IND = (double *) malloc (N*sizeof(double));
	if (!IND)
	{
		perror("IND");
		free (D);
		free (C);
		free (B);
		free (A);
		return -1;
	}

	srand(time(NULL));

	strncpy(experiment, argv[1], strlen(argv[1]));
	alpha = atof(argv[2]);
	vl = atoi(argv[3]);
	iter = atoi(argv[4]);
	ln = atoi(argv[5]);
	minTime = atof(argv[6]);

	iter = MAX(iter,1);
	vl = MIN(M/2,vl);

	for(i=0; i<N; i++)
	{
		A[i]=Rand01();
		B[i]=Rand01();
		C[i]=Rand01();
		D[i]=Rand01();
		IND[i]=pow(A[i],alpha)*0.5*(M-500);
	}

	x1=x2=x3=x4=x5=1;
	y1=y2=y3=y4=y5=1;
	c1=A[0]; c2=A[1]; c3=A[2]; c4=A[3]; c5=A[4];
	c6=A[5]; c7=A[6]; c8=A[7]; c9=A[8]; c10=A[9];

	for (i=10; i<M; i++)
	{
		A[i]*=pow(-1, i);
		B[i]=A[i];
		C[i]=-1*A[i];
		D[i]=A[i];
	}

	flopsCount=0;
	bytesCount=0;
	memCount=0;
	GLoops=0.;
	GFlops=0.;
	GBytes=0.;

	t1=MPI_Wtime();
	t2=t1+1.E6;
	
	MPI_Barrier(MPI_COMM_WORLD);
	t1=MPI_Wtime();
	
	if (!strncmp("none", experiment, strlen("none")))
	{
		flopsCount=1;
		bytesCount=1;
		memCount=0;
		irep=1;
	}

	else if (!strncmp("A=A*scalar+scalar", experiment, strlen("A=A*scalar+scalar")))
	{
		flopsCount=2;
		bytesCount=2*8;
		memCount=0;
		irep=0;

		if (t2-t1 < minTime)
		{
			for (it=0; it<iter; it++)
			{
				for(i=0; i<ln; i++)
				{
					j=IND[i+irep];
					j1=IND[j+100+irep];
					for(k=0; k<vl; k++)
						A[j+k]=A[j+k]*0.999+1.E-9;
				}//i

				A[j1]=D[it+3];
			} //it

			t2=MPI_Wtime();
			irep++;
		} //if t2-t1
	} //else if

	else if (!strncmp("A=A*B+C", experiment, strlen("A=A*B+C")))
	{
		flopsCount=2;
		bytesCount=4*8;
		memCount=0;
		irep=0;

		if (t2-t1 < minTime)
		{
			for (it=0; it<iter; it++)
			{
				for(i=0; i<ln; i++)
				{
					j=IND[i+irep];
					j1=IND[j+100+irep];
					for(k=0; k<vl; k++)
						A[j+k]=A[j+k]*B[j+k]+C[j+k];
				}//i

				A[j1]=D[it+3];
			} //it

			t2=MPI_Wtime();
			irep++;
		} //if t2-t1
	} //else if

	else if (!strncmp("trigonom", experiment, strlen("trigonom"))) //sqrt(sin^2(x)+cos^2(x))
	{
		flopsCount=5;
		bytesCount=2*8;
		memCount=0;
		irep=0;

		if (t2-t1 < minTime)
		{
			for (it=0; it<iter; it++)
			{
				for(i=0; i<ln; i++)
				{
					j=IND[i+irep];
					j1=IND[j+100+irep];
					for(k=0; k<vl; k++)
						A[j+k]=sqrt((sin(A[j+k])*sin(A[j+k]))+(cos(A[j+k])*cos(A[j+k])));
				}//i

				A[j1]=D[it+3];
			} //it

			t2=MPI_Wtime();
			irep++;
		} //if t2-t1
	} //else if

	else if (!strncmp("sleep", experiment, strlen("sleep")))
	{
		flopsCount=0;
		bytesCount=0;
		memCount=0;
		irep=0;

		if (t2-t1 < minTime)
		{
            sleep(1);
            t2=MPI_Wtime();
            irep=irep+1;
		} //if t2-t1
	} //else if

	else
	{
		printf ("Error. Undefined experiment\n");
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
		return -1;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	t2=MPI_Wtime();
	eTime=t2-t1;
	GLoops=(1.0*vl*ln*iter*irep*nprocs)/eTime;
	GFlops=GLoops*flopsCount;
	GBytes=GLoops*bytesCount;
	TimeLoop=1./GLoops;

	MPI_Barrier(MPI_COMM_WORLD);

	#ifdef PADDLECARD
	if (myid==0)
	{
		fEnergy=fopen("/sys/devices/platform/aem.0/energy1_input", O_RW);
		fread(fEnergy, "%d", &endDC);
		fclose(fEnergy);
	}
	#endif

	printf ("Final %d\n", myid);

	if (!myid)
		printf ("%s %d %d %1.5e %1.5e %1.5e %1.5e %1.5e %1.5e %1.5e %1.5e \n", experiment, irep, vl, alpha, TimeLoop, GLoops, GFlops, GBytes, (endDC-initialDC)/1e6, (endDC-initialDC)/(1e6*eTime), eTime);

	free ((void*) A);
	free ((void*) B);
	free ((void*) C);
	free ((void*) D);
	free ((void*) IND);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();

	return 0;
}
