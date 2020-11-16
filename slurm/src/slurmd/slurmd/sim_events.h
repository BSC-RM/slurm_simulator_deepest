#ifdef SLURM_SIMULATOR
/*
 ** Definitions for simulation mode
 ** */

#define WF_API	    1
#define AFTEROK_API 0

typedef struct simulator_event_info{
    int job_id;
    int duration;
	int is_delayed_workflow;
	int api_call_time;
    struct simulator_event_info *next;
	struct simulator_event_info *prev;
}simulator_event_info_t;

typedef struct simulator_event{
    int job_id;
    uint32_t uid;
    int type;
    time_t when;
    char *nodelist;
	int pack_components;
	simulator_event_info_t *event_info_ptr;
    volatile struct simulator_event *next;
}simulator_event_t;

#endif
