
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>
#include<time.h>
long long int d1,d2,d3;
static int long count=4294967296;

static void *A_count(){
	long long int diff;
	struct timespec start,end;
	clock_gettime(CLOCK_MONOTONIC,&start);
	for(long long int i=0;i<count;i++){
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	d1=diff;
	printf("elpased time FIFO +%llu nanoseconds\n", diff);
	return NULL;
}

static void *B_count(){
	long long int diff;
	struct timespec start,end;
	clock_gettime(CLOCK_MONOTONIC,&start);
	for(long long int i=0;i<count;i++){
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	d2=diff;
	printf("elpased time RR  +%llu nanoseconds\n", diff);
	return NULL;
}

static void *C_count(){
	long long int diff;
	struct timespec start,end;
	clock_gettime(CLOCK_MONOTONIC,&start);
	for(long long int i=0;i<count;i++){
	}
	clock_gettime(CLOCK_MONOTONIC,&end);
	diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	d3=diff;
	printf("elpased time other +%llu nanoseconds\n", diff);
	return NULL;
}

int main(int argc,char *argv[]){
	int p=1;
	for(int i=0;i<5;i++){
	FILE *f;
	f=fopen("plot.data","a");
		pthread_t thr,thr1,thr2;
		pthread_attr_t attr,attr1,attr2;
		pthread_attr_t *attrp,*attrp1,*attrp2;
		int s;

		attrp=NULL;
		attrp1=NULL;
		attrp2=NULL;
		attrp=&attr;
		attrp1=&attr1;
		attrp2=&attr2;

		s=pthread_attr_init(&attr);
		s=pthread_attr_init(&attr1);
		s=pthread_attr_init(&attr2);
	

		s=pthread_attr_setschedpolicy(&attr,SCHED_FIFO);
		s=pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamFIFO;
		schedParamFIFO.sched_priority=p;
		s=pthread_attr_setschedparam(&attr,&schedParamFIFO);
		s=pthread_create(&thr,attrp,&A_count, NULL);
		
	
		s=pthread_attr_setschedpolicy(&attr,SCHED_RR);
		s=pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamRR;
		schedParamRR.sched_priority=p;
		s=pthread_attr_setschedparam(&attr,&schedParamRR);
		s=pthread_create(&thr1,attrp,&B_count,NULL);
	
		s=pthread_attr_setschedpolicy(&attr,SCHED_OTHER);
		s=pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamOTHER;
		schedParamOTHER.sched_priority=0;
		s=pthread_attr_setschedparam(&attr,&schedParamOTHER);
		s=pthread_create(&thr2,attrp,&C_count,NULL);

		p=p+15;

		if(attrp!=NULL){
			s=pthread_attr_destroy(attrp);
		}	
		if(attrp1!=NULL){
			s=pthread_attr_destroy(attrp);
		}
		if(attrp2!=NULL){
			s=pthread_attr_destroy(attrp);
		}

		pthread_join(thr,NULL);
		pthread_join(thr1,NULL);
		pthread_join(thr2,NULL);

		fprintf(f,"%d %llu %llu %llu\n",p,d1,d2,d3);

		printf("\n");
		fclose(f);
	}
	return 0;
}	


