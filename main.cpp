#include "petri.hpp"

int num_monitors = 10;
int num_violations = 0;
int max_length = 0;

using namespace std;

long getVal() {
    long rss = 0L;
    	FILE* fp = NULL;
    	if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
    		return (size_t)0L;		// Can't open? */
    	if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
    	{
    		fclose( fp );
    		return (size_t)0L;		// Can't read? */
    	}
    	fclose( fp );
    	return (size_t)rss * (size_t)sysconf( _SC_PAGESIZE);
}

int main() {
    struct rusage usage;
    struct timeval start, end;
    PetriNet* monitor = new PetriNet();
    monitor->create_monitor();
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    start = usage.ru_stime;
    long mem = getVal();
    cout<<"User time : "<<end.tv_sec<<"."<<end.tv_usec<<"s"<<endl;
    cout<<"System time : "<<start.tv_sec<<"."<<start.tv_usec<<"s"<<endl;
    cout<<"Memory : "<<mem<<endl;
}
