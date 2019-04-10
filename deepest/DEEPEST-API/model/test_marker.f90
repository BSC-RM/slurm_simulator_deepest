      IMPLICIT NONE

      include 'mpif.h'  

      REAL, PARAMETER :: PI        = 3.1415926

      integer, parameter :: PREC=8, LFREQ=15, NUMEVENTS=26
      integer, parameter :: M=200*1024*1024/8+17, N=M+100

      real(kind=PREC), Allocatable:: A(:),b(:),C(:),D(:)
      integer, Allocatable  :: ind(:)

      real(kind=PREC):: ALPHA 
      real(kind=PREC):: C1,C2,C3,C4,C5 
      real(kind=PREC):: C6,C7,C8,C9,C10 
      real(kind=PREC):: X, X1,X2,X3,X4,X5 
      real(kind=PREC):: Y, Y1,Y2,Y3,Y4,Y5 
      real(kind=PREC):: time, T1, T2, timemin
      real(kind=PREC):: GLoops, GFLops, GBytes, TimeLoop
      real(kind=PREC):: ALPH(4)=(/1.0,0.05,0.01,0.0/)
      real(kind=PREC):: FLOPSCOUNT, BYTESCOUNT, MEMCOUNT
      integer :: VL

      INTEGER   I, j, K, L, IERR, j1, j2, irep, iirep
      INTEGER   IT, LN, iter
      INTEGER   NPROCS, myid
      INTEGER   provided

      INTEGER(kind=PREC) :: initialdc, enddc

      character (len=20) :: ID='UNKNOWN', EXP='XXXX'
      CHARACTER(len=150) :: params

      Logical, parameter :: MPI  =.true.

      CALL MPI_INIT_THREAD(MPI_THREAD_MULTIPLE,provided, IERR)
      CALL MPI_COMM_RANK(MPI_COMM_WORLD, myid,   IERR)
      CALL MPI_COMM_SIZE(MPI_COMM_WORLD, NPROCS, IERR)

#ifdef PADDLECARD
            if (myid==0) then
               open(60,file='/sys/devices/platform/aem.0/energy1_input')
               read(60,*) InitialDC
               close(60)
            endif
#endif

      ALLOCATE(A(0:n), B(0:n), C(0:n), D(0:N), IND(0:n))
      
      CALL getarg(1, EXP)

      CALL getarg(2, params)
      read (params, *) alpha

      CALL getarg(3, params)
      read (params, *) VL

      CALL getarg(4, params)
      read (params, *) Iter

      CALL getarg(5, params)
      read (params, *) LN
      
      CALL getarg(6, params)
      read(params, *) timemin

      iter=max(iter,1)
      VL=MIN(M/2,VL)
      call random_number(A)
      call random_number(B)
      call random_number(C)
      call random_number(D)

      IND=(A**alpha)*0.5*(M-500)
      X1=1
      X2=1
      X3=1
      X3=1
      X4=1
      X5=1
      C1= A(1)
      C2= A(2)
      C3= A(3)
      C4= A(4)
      C5= A(5)
      C6= A(6)
      C7= A(7)
      C8= A(8)
      C9= A(9)
      C10=A(10)

      A(1:m:2)=-A(1:m:2)
      B=A
      C=-A
      D=A

      FLOPSCOUNT=0
      BYTESCOUNT=0
      MEMCOUNT  =0
      GLoops=0.
      GFlops=0.
      GBytes=0.

      T1=mpi_wtime()
      T2=T1+1.E6
      if (MPI) CALL MPI_barrier(MPI_COMM_WORLD,ierr)

      T1=mpi_wtime()
      if (trim('EXP') == 'OVERHEAD' ) goto 888

      SELECT CASE  (TRIM(EXP))
!     =========================================================

         CASE ('none')
            FLOPSCOUNT=1
            BYTESCOUNT=1
            MEMCOUNT  =0
            irep =1

!     =========================================================

         CASE ('A=A*scalar+scalar')
            FLOPSCOUNT=2
            BYTESCOUNT=2  *8
            MEMCOUNT  =0
            irep=1

100         continue
            do IT=1,Iter
               do I=0,LN-1
                  j=ind(I+irep)
                  j1=ind(I+100+irep)
                  do k=0,VL-1
                     a(j+k)=(a(j+k))*0.999 +1.E-9
                  enddo
               enddo
               A(j1)=D(it+3)
            enddo

            T2=mpi_wtime()
            if ((T2-T1) .lt. timemin) then
               irep=irep+1
               goto 100
            endif
    
!       =========================================================

         CASE ('A=A*B+C')
            FLOPSCOUNT=2
            BYTESCOUNT=4*8
            MEMCOUNT  =0
            irep=1

200         continue
            do IT=1,Iter
               do I=0,LN-1
                  j=ind(I+irep)
                  j1=ind(I+100+irep)
                  do k=0,VL-1
                     A(j+k)=a(j+k)*B(j+k)+C(j+k)
                  enddo
               enddo
               A(j1)=D(it+3)
            enddo

            T2=mpi_wtime()
            if ((T2-T1) .lt. timemin) then
               irep=irep+1
               goto 200
            endif

!        =========================================================

         CASE ('trigonom')  ! sqrt(sin^2(x)+cos^2(x))
            FLOPSCOUNT=4
            BYTESCOUNT=4*8
            MEMCOUNT  =0
            irep=1

300         continue
            do I=1,Iter
               A(1)=sqrt((sin(I*PI/180)*sin(I*PI/180))+(cos(I*PI/180)*cos(I*PI/180)))
            enddo

            T2=mpi_wtime()
            if ((T2-T1) .lt. timemin) then
               irep=irep+1
               goto 300
            endif
    
!        =========================================================

         CASE ('sleep')
            FLOPSCOUNT=0
            BYTESCOUNT=0
            MEMCOUNT  =0
            irep=1

400         continue
            iter=1
            CALL sleep(1)

            T2=mpi_wtime()
            if ((T2-T1) .lt. timemin) then
               irep=irep+1
               goto 400
            endif

!        =========================================================

         CASE DEFAULT
            call mpi_abort(ierr)
            write(6,*) 'Case not defined'
            stop  
      END SELECT

      CALL MPI_barrier(MPI_COMM_WORLD,ierr)

      T2=mpi_wtime()
      time=t2-t1

      GLoops=(1.D0*VL*LN*iter*irep*nprocs)/time
      GFlops=GLoops*FLOPSCOUNT
      GBytes=GLoops*BYTESCOUNT
      TimeLoop=1./GLoops

      CALL MPI_barrier(MPI_COMM_WORLD,ierr)

#ifdef PADDLECARD
      if (myid==0) then
         open(60,file='/sys/devices/platform/aem.0/energy1_input')
         read(60,*) EndDC
         close(60)
      endif
#endif

888   if (myid==0) then
!         write(6,1001) trim(EXP(1:17)), irep, VL, Alpha, TimeLoop, Gloops, GFlops, GBytes, (enddc-initialdc)/1e6, (enddc-initialdc)/(1e6*TimeLoop), time
         write(6,1001) trim(EXP(1:17)), irep, VL, Alpha, TimeLoop, Gloops, GFlops, GBytes, (enddc-initialdc)/1e6, (enddc-initialdc)/(1e6*time), time
1001     format(A17,2(I12),8(1PE12.5))           
      endif

999   CALL MPI_barrier(MPI_COMM_WORLD,ierr)
      CALL mpi_finalize(ierr)
      stop
   end !main

   subroutine errorx(i)
      write(6,*) 'ERROR:', I
      if(MPI) CALL MPI_abort(ierr)
      stop 999
   end
