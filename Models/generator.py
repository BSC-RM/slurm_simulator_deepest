##########################################################################################
#
#  INPUT: 
#  OUTPUT 
#  How big traces?
#  System size, deepest or bigger?
#  Load imbalance, how many points?
#  Should we extend base model with additional parameters for job size distribution, job duration distribution, etc.
# Input parameters that change the shape of distributions
# 
##########################################################################################


import subprocess
import os
from random import randint
from random import seed
from random import uniform
seed(1)

# Cirne base model was fixed so that: 
# 1) traces are in SWF format, and 
# 2) jobs are ordered from earlier to later arrival time.

base_model_path = "cirne/genworkload"

current_dir = os.getcwd()
data=[]
single_module_percent = 100


def delete_tmp_files():
    subprocess.call(["rm", current_dir+"/tmp*"])

def cut_trace_now(i,num_jobs):
    result=0
    
    if num_jobs==0:
        last_line_cm = subprocess.check_output(['tail','-1',current_dir+"/tmp.cm.swf"])
        last_line_esb = subprocess.check_output(['tail','-1',current_dir+"/tmp.esb.swf"])
        last_line_dam = subprocess.check_output(['tail','-1',current_dir+"/tmp.dam.swf"])

        last_arrival_time_cm = int(last_line_cm.split(';')[1])
        last_arrival_time_esb = int(last_line_esb.split(';')[1])
        last_arrival_time_dam = int(last_line_dam.split(';')[1])

        shortest_trace_last_arrival = min([last_arrival_time_cm, last_arrival_time_esb, last_arrival_time_dam])
    
        arrival = data[i].split(';')[1]
        if int(arrival) > shortest_trace_last_arrival:
            result=1
        else:
            result=0
    else:
        if i==num_jobs:
            result=1
        else:
            result=0

    return result

def assign_jobid(i):
    global data
    data[i]=data[i].replace(data[i].split(';')[0], str(i+1), 1)

def sort_jobs_by_arrival_time():
    data.sort(key=lambda x: int(x.split(';')[1]))

def create_template_trace(module,num_nodes,num_jobs,arr_pattern,load):
    subprocess.call([base_model_path,str(num_nodes),arr_pattern,str(num_jobs),module,"tmp."+module,str(load)])

# Label single-/multi-module is written in userid field of SWF trace
def label_single_multi_jobs(i):
    global data
    random_value = randint(0,100)
    if random_value <= single_module_percent: 
        data[i]=data[i].replace(data[i].split(';')[11], "single-module")
    else: 
        data[i]=data[i].replace(data[i].split(';')[11], "multi-module")

def add_temp_module_list_field(i):
    data[i]=data[i].replace('\n',";modlist\n")

def edit_modlist(filename,modlist):
    # if edited modlist needs to be written in file only, then:
    #filename.write(data[i].replace(data[i].split(';')[18],modlist))
    # if data list needs to be changed then:
    data[i]=data[i].replace(data[i].split(';')[18],modlist)
    # the latter might be the case if we want to pass swf trace with modlist field to creation of wf and hetero jobs file
    # only change data list if filename is basic flexibility case: modlistfile. 




##########################################################################################
#
#			TEMPLATE SWF TRACES FROM BASE WORKLOAD MODEL	
#
##########################################################################################


# Create template traces for each module with the base model.

# Cirne base model was fixed so that: 
# 1) three traces are in SWF format, and 
# 2) jobs are ordered from earlier to later arrival time.

base_model_path = "cirne/genworkload"

num_jobs=100
arrival_pattern="anl"

load_cm=0.76
load_esb=0.64
load_dam=2.5

cm_size=50
esb_size=75
dam_size=16

create_template_trace("cm",cm_size,num_jobs,arrival_pattern,load_cm)
create_template_trace("esb",esb_size,num_jobs,arrival_pattern,load_esb)
create_template_trace("dam",dam_size,num_jobs,arrival_pattern,load_dam)

##########################################################################################
#
#                       MERGE TEMPLATE TRACES IN A BASE SWF TRACE        
#
##########################################################################################

# Concatenate three trace files in tmp.swf file
filenames = [current_dir+"/tmp.cm.swf", current_dir+"/tmp.esb.swf", current_dir+"/tmp.dam.swf" ]
with open(current_dir+"/tmp.concatenated.swf",'w') as outfile:
    for fname in filenames:
        with open(fname) as infile:
            for line in infile:
                outfile.write(line)

f=(current_dir+"/tmp.concatenated.swf")
data=open(f).readlines()

# Sort lines by job's arrival time and assign jobid to each line
# Assign jobid to each line
# Cut the trace when the last job of the shortest trace has arrived
empty="-1\n"
num_jobs *= 3


with open(current_dir+"/cirne_base_"+str(num_jobs)+"_"+arrival_pattern+"_load_"+str(load_cm)+"_"+str(load_esb)+"_"+str(load_dam)+".swf",'w') as basefile:
    sort_jobs_by_arrival_time()
    for i in range(len(data)):
        if cut_trace_now(i,num_jobs):
            break  
        assign_jobid(i)
        label_single_multi_jobs(i)
        add_temp_module_list_field(i)
        #change_module_list_field
        #add_wf_dags
        #add_hetero_job_details_mwf
        #add_global_resources
        edit_modlist(basefile,empty)
#delete_tmp_files()             

##########################################################################################
#
#    	      LABEL SINGLE AND HETERO JOBS BASED ON DEEP-EST APPS PERCENT (SWF)
#
##########################################################################################

##########################################################################################
#
#   ADD MODULE-LIST FIELD ACCORDING TO INFORMATION FROM DEEP-EST APPS DEVELOPERS OR 
#                                    SCHEDULER LOGS (SWF)
#
##########################################################################################
# Parameter (preferred module (if single-module) job, percent of jobs with alternative module),
# Parameter (percent,combination)

# Percent of flexible jobs for specific preferred module
cm_flex=100
esb_flex=50
dam_flex=57

dam_flex_1=75 # prob of dam,esb occurence

modflex=-15
lowflex=-30

modlist1="cm,dam\n"
modlist2="esb,cm\n"
modlist3="dam,esb\n"
modlist4="dam,cm\n"


# TODO how would the code be organized to be able to decide whther I want lowflex and modflex to be written as well?
with open(current_dir+"/cirne_modlist_"+str(num_jobs)+"_"+arrival_pattern+"_load_"+str(load_cm)+"_"+str(load_esb)+"_"+str(load_dam)+".swf",'w') as modlistfile:
    with open(current_dir+"/cirne_modlist_"+str(num_jobs)+"_"+arrival_pattern+"_load_"+str(load_cm)+"_"+str(load_esb)+"_"+str(load_dam)+"_modflex.swf",'w') as modlist_modflex_file:
        with open(current_dir+"/cirne_modlist_"+str(num_jobs)+"_"+arrival_pattern+"_load_"+str(load_cm)+"_"+str(load_esb)+"_"+str(load_dam)+"_lowflex.swf",'w') as modlist_lowflex_file:
            for i in range(len(data)):
                job_type=data[i].split(';')[11]
                if job_type=="single-module":
                    module=data[i].split(';')[15]
                    if module=="cm":
                        edit_modlist(modlistfile,modlist1)
                        r1=randint(0,100)
                        if r1 <= cm_flex+lowflex:
                            edit_modlist(modlist_lowflex_file,modlist1)
                            edit_modlist(modlist_modflex_file,modlist1)
                        elif r1 <= cm_flex+modflex and r1 > cm_flex+lowflex:
                            edit_modlist(modlist_lowflex_file,empty)
                            edit_modlist(modlist_modflex_file,modlist1)
                        else:
                            edit_modlist(modlist_lowflex_file,empty)
                            edit_modlist(modlist_modflex_file,empty)
                    elif module=="esb":
                        r2=randint(0,100)
                        if r2 <= esb_flex+lowflex:
                            edit_modlist(modlistfile,modlist2)
                            edit_modlist(modlist_lowflex_file,modlist2)
                            edit_modlist(modlist_modflex_file,modlist2)
                        elif r2 > esb_flex+lowflex and r2 <= esb_flex+modflex:
                            edit_modlist(modlistfile,modlist2)
                            edit_modlist(modlist_lowflex_file,empty)
                            edit_modlist(modlist_modflex_file,modlist2)
                        elif r2 > esb_flex+modflex and r2 <= esb_flex:
                            edit_modlist(modlistfile,modlist2)
                            edit_modlist(modlist_lowflex_file,empty)
                            edit_modlist(modlist_modflex_file,empty)
                        else:
                            edit_modlist(modlistfile,empty)
                            edit_modlist(modlist_lowflex_file,empty)
                            edit_modlist(modlist_modflex_file,empty)
                    elif module=="dam":
                        r3=randint(0,100)    
                        r4=randint(0,100)    
                        if r3 <= dam_flex+lowflex:
                            if r4 <= dam_flex_1:
                                edit_modlist(modlistfile,modlist3)
                                edit_modlist(modlist_lowflex_file,modlist3)
                                edit_modlist(modlist_modflex_file,modlist3)
                            else:
                                edit_modlist(modlistfile,modlist4)
                                edit_modlist(modlist_lowflex_file,modlist4)
                                edit_modlist(modlist_modflex_file,modlist4)
                        elif r3 > dam_flex+lowflex and r3 <=dam_flex+modflex:
                            if r4 <= dam_flex_1:
                                edit_modlist(modlistfile,modlist3)
                                edit_modlist(modlist_lowflex_file,empty)
                                edit_modlist(modlist_modflex_file,modlist3)
                            else:
                                edit_modlist(modlistfile,modlist4)
                                edit_modlist(modlist_lowflex_file,empty)
                                edit_modlist(modlist_modflex_file,modlist4)
                        elif r3 > dam_flex+modflex and r3 <= dam_flex:
                            if r4 <= dam_flex_1:
                                edit_modlist(modlistfile,modlist3)
                                edit_modlist(modlist_lowflex_file,empty)
                                edit_modlist(modlist_modflex_file,empty)
                            else:
                                edit_modlist(modlistfile,modlist4)
                                edit_modlist(modlist_lowflex_file,empty)
                                edit_modlist(modlist_modflex_file,empty)
                        else: 
                                edit_modlist(modlistfile,empty)
                                edit_modlist(modlist_lowflex_file,empty)
                                edit_modlist(modlist_modflex_file,empty)
                elif job_type == "multi-module":
                    edit_modlist(modlistfile,empty)
                    edit_modlist(modlist_lowflex_file,empty)
                    edit_modlist(modlist_modflex_file,empty)

##########################################################################################
#
#                            ADD WORKFLOW JOBS TO THE TRACE (SWF)
#
##########################################################################################
# Only single module jobs belong to WF. (Depends what approach Zia takes.)
# Parameter (module DAG, percent of occurence)
# How do I create random DAGs based on this information?

#parameters
max_wf_jobs = 3
perc_wf_jobs = 20
is_het = [0] * len(data)
is_first_het = [0] * len(data)
use_het=1

#much easier to mange data as a list
ldata=[]
#extend data format to include real delay, use 17th field for the req_delay
for i in range(len(data)):
    data[i] = data[i].replace('\n',";-1\n")
    ldata.append(data[i].split(';'))
i = 0
while i < len(data):
    job_type = data[i].split(';')[11]
    if job_type == "single-module":
        r1 = randint(0,100)
        ncomp = 1
        iprec = i
        inext = i + 1
        #extend SWF with two fields
        while r1 <= perc_wf_jobs and ncomp < max_wf_jobs and inext < len(data):
            #calculate delay from requested time
            req_delay = round(uniform(0.5,0.9) * float(ldata[iprec][8]))
            #calculate actual delay from duration
            api_call = round(uniform(0.5,0.9) * float(ldata[iprec][3]))
            if req_delay < api_call:
                api_call = -1
            ldata[inext][16] = ldata[iprec][0]
            ldata[inext][17] = str(req_delay)
            ldata[iprec][19] = str(api_call)+'\n'
            
            #If hetjob set same arrival time of precedent job (initially also for jobs with deps)
            ldata[inext][1] = ldata[iprec][1]
            ldata[inext][1] = ldata[iprec][1]
            r1 = randint(0,100)
            ncomp += 1
            iprec = inext
            inext += 1
        sum_req_time = 0
        if use_het:
            #set is_het to the number of components
            if ncomp > 1:
                for j in range(i,i+ncomp):
                    is_het[j] = ncomp
                    sum_req_time += int(ldata[j][8])

                #set requested time to the total
                for j in range(i,i+ncomp):
                    ldata[j][8] = str(sum_req_time)
            is_first_het[i] = is_het[i]
        i += ncomp

first_het_id = -1
with open(current_dir+"/cirne_base_"+str(num_jobs)+"_"+arrival_pattern+"_load_"+str(load_cm)+"_"+str(load_esb)+"_"+str(load_dam)+".mwf",'w') as mwffile:
    for i in range(len(data)):
        mwf = [""] * 42
        if is_het[i]:
            if is_first_het[i]:
                mwf[0] = ldata[i][0]
                first_het_id = mwf[0]
            else:
                mwf[0] = first_het_id
        else:
            mwf[0] = ldata[i][0]
        if is_het[i] == 0:
            mwf[1] = "1"
        else:
            mwf[1] = str(is_het[i])
        mwf[2] = "job"+ldata[i][0]
        mwf[3] = ldata[i][1]
        mwf[4] = "-1"
        mwf[5] = ldata[i][8]
        #number of components submitted at submit time (do we need this?)
        mwf[6] = "-1"
        mwf[7] = str(i+1)
        mwf[8] = "job"+str(i)
        mwf[9] = "-1"
        mwf[10] = ldata[i][3]
        mwf[11] = "0"
        mwf[12] = "-1"
        mwf[13] = ldata[i][15]
        mwf[14] = ldata[i][7]
        mwf[15] = "-1"
        mwf[16] = "-1"
        mwf[17] = "-1"
        mwf[18] = "-1"
        mwf[19] = "-1"
        #NAM
        mwf[21] = "-1"
        mwf[21] = "-1"
        mwf[22] = "-1"
        mwf[23] = "-1"
        mwf[24] = "-1"
        mwf[25] = "-1"
        mwf[26] = "-1"
        mwf[27] = "-1"
        mwf[28] = "-1"
        mwf[29] = "-1"
        mwf[30] = "-1"
        mwf[31] = "-1"
        mwf[32] = "-1"
        mwf[33] = "-1"
        mwf[34] = "-1"
        mwf[35] = "-1"
        mwf[36] = "-1"
        mwf[37] = "-1"
        mwf[38] = "-1"
        mwf[39] = "NA"
        if is_het[i]:
            #dependency with prec job
            if not is_first_het[i]:
                #precedent job has id == i
                mwf[38] = str(i)
                if use_het:
                    mwf[39] = "DYNAMIC"
                else:
                    mwf[39] = "AFTEROK"
        mwf[40] = ldata[i][17]
        mwf[41] = ldata[i][19]
        
        mwffile.write(';'.join(mwf))

#Loop between single jobs and assign a dependency with the following job. If a dependency is created the following job arrival time is modified to current job arrival time.


##########################################################################################
#
#                            ADD HETEROGENEOUS JOBS TO THE TRACE (MWF)
#
##########################################################################################
# Parameter (first module in hetero job, percent of hetero jobs)
# Parameter (percent, combination)
# Add new lines to MWF trace with subjobs definition
# SHould I first create hetero jobs then module-list?


#If Zia considers wf as heterogeneous then percent single/multi should change; part of single jobs that are wfs should become multi

hetero1=["cm","esb"]
hetero2=["cm","dam"]
hetero3=["cm","esb","dam"]
hetero4=["esb","dam"]
# Do I add additional job for subjobs, or I try to match jobs? 
with open(current_dir+"/cirne_anl_30_multi-module.mwf",'w') as multimodfile:
    for i in range(len(data)):
        #copy_swf_data_to_vars_to_later_build_mwf_job_string
        #number of lines per job will depend on the module combination
        job_type=data[i].split(';')[11]
        if job_type=="single-module":
            module=data[i].split(';')[15]
            if module=="cm":
                break
##########################################################################################
#
#                   ADD JOBS WITH GLOBAL RESOURCES REQUESTS TO THE TRACE (MWF)
#
##########################################################################################
# What type of jobs request global resources, how many single, how many hetero, how many wf, using what modules, and what are the percentages, then devise paramters values, choose jobs and assign the value to the field.
# Still, simulator does not support this part. 



## Final output should be:
# 1) base SWF trace 
#	a) balanced
#	b) imbalanced (several traces need to be created, with more or less imbalance) 
# 2) SWF trace with module-list field
# 3) SWF trace with partition-list field (for modlist policy validation)
# 4) SWF/MWF trace with workflows
# 5) MWF trace with heterogeneous
# 6) MWF trace with all types of jobs.  
