#include<stdio.h>
#include<obliv.h>
#include<../common/util.h>
#include "psi.h"

int testSorterMain(int argc,char* argv[])
{
  ProtocolDesc pd;
  extern void testSorter(void*);
  extern bool testSorterResult;
  protocolUseStdio(&pd);
  setCurrentParty(&pd,argv[1][0]=='1'?1:2);
  execDebugProtocol(&pd,testSorter,NULL);
  cleanupProtocol(&pd);
  if(testSorterResult) fprintf(stderr,"Sorted!\n");
  else fprintf(stderr,"Unsorted mess!\n");
  return 0;
}

double lap;
int testPsiMain(int argc,char* argv[])
{
  // Usage:
  //   ./a.out -- 1234 &
  //   ./a.out localhost 1234
  // The first command starts out a background server listening on port 1234.
  // The second command connects to this server, which is localhost at port 1234
  extern void randomPsi(void*);
  ProtocolDesc pd;
  //protocolUseStdio(&pd);
  const char* remote_host = (strcmp(argv[2],"--")?argv[2]:NULL);
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);
  lap = wallClock();
  setCurrentParty(&pd,remote_host?2:1);
  execYaoProtocol(&pd,randomPsi,NULL);
  fprintf(stderr,"Total time: %lf s\n",wallClock()-lap);
  cleanupProtocol(&pd);
  return 0;
}

int main(int argc, char** argv){

  if(argc != 4){
    fprintf(stderr, "Usage: %s <port> <--|localhost> <inputFIle>\n", argv[0]);
    return 2;
  }

  ProtocolDesc pd;
  protocolIO io;

  const char* remote_host = (strcmp(argv[2], "--")==0?NULL:argv[2]);
 // ocTestUtilTcpOrDie(&pd, remote_host, argv[1]);
  if(!remote_host){
    if(protocolAcceptTcp2P(&pd, argv[1])){
      fprintf(stderr, "TCP accept failed\n");
      exit(1);
    }
  }
  else{
    if(protocolConnectTcp2P(&pd,remote_host,argv[1])!=0){
      fprintf(stderr,"TCP connect failed\n");
      exit(1);
    }
  }

  int currentParty = remote_host?2:1;
  setCurrentParty(&pd, currentParty); 

  vector v;
  FILE* file = fopen(argv[3], "r");
  if(fscanf(file, "%d\n", &(v.size)) == EOF){
    fprintf(stderr, "Invalid input file\n");
    return 2;
  }
  

  v.arr = malloc(sizeof(int) * v.size);

  for(int i=0; i<v.size; i++){
    if(fscanf(file, "%d\n", &(v.arr[i])) == EOF){
      return 2;
    }
  }
  fprintf(stderr, "Exec Yao");
  io.input = v;

  vector r;
  r.size = v.size;
  r.arr = malloc(sizeof(int) * r.size);
  io.output = r;
  
  struct timeval start,end;  
  gettimeofday(&start, NULL);  
  execYaoProtocol(&pd, psi, &io);
  gettimeofday(&end, NULL);  

  printf("time=%d ms\n",((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000);  

  int* result = io.output.arr;
  fprintf(stderr, "Median4: result = ");
  for (int i = 0; i < io.input.size; i++) {
    fprintf(stderr, "%d, ", result[i]);
  }
  fprintf(stderr, "\n");


  cleanupProtocol(&pd);
  return 0;
}