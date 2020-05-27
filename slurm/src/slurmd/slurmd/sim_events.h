#ifdef SLURM_SIMULATOR
/*
 ** Definitions for simulation mode
 ** */

#define WF_API	    1
#define AFERTOK_API 0

typedef struct simulator_event{
    int job_id;
    uint32_t uid;
    int type;
    time_t when;
    char *nodelist;
    volatile struct simulator_event *next;
}simulator_event_t;

typedef struct simulator_event_info{
    int job_id;
    int duration;
    int wf_type;
    struct simulator_event_info *next;
}simulator_event_info_t;
#endif
