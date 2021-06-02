#include <stdio.h>
#include <sys/time.h>
#include <obliv.h>

#include "psi.h"

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

  int* result = io.output.arr;
  fprintf(stderr, "Result = ");
  for (int i = 0; i < io.input.size; i++) {
    fprintf(stderr, "%d, ", result[i]);
  }
  fprintf(stderr, "\n");


  cleanupProtocol(&pd);
  return 0;
}