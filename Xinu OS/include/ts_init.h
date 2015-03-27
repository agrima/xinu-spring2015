
#define SIZE 60

struct ts_ent {
	int ts_tqexp;         // new priority: CPU-intensive (time quantum expired)
	int ts_slpret;        // new priority: I/O-intensive (sleep return)
	int ts_quantum;       // new time slice
};
extern struct ts_ent tstab[];
