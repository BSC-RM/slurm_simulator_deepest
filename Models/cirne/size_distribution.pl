
my @job_sizes=(0)*10000;
$j=0;

while(<>){
     if(/.*fixed\t\d+\t(\d+).*/){
         $job_sizes[$1]=$job_sizes[$1]+1;
     }
}

while($j<=10000){
     print "$job_sizes[$j]\n";
     $j=$j+1;
}

#*       *       synthetic       fixed   198691  64      7512    198691  203398  completed
#*       *       synthetic       fixed   198676  512     23613   198676  212538  completed

