#include<stdio.h>
#include <sys/time.h>
#include<obliv.h>

#include"median4.h"

int main(int argc, char** argv){

  if(argc != 4){
    fprintf(stderr, "Usage: %s <port> <--|localhost> <inputFIle>\n", argv[0]);
    return 2;
  }

  ProtocolDesc pd;
  protocolIO io;

  // Read inputs from file
  FILE* file;
  file = fopen(argv[3], "r");

  char* errorMsg = "Input file must me in format:\nOPERAND_1\nOPERAND_2\n";
  if(fscanf(file, "%d\n", &io.smaller) == EOF){
    fprintf(stderr, errorMsg);
    return 2;
  } if (fscanf(file, "%d\n", &io.larger) == EOF){
    fprintf(stderr, errorMsg);
    return 2;
  }

  fclose(file);

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

  struct timeval start,end;  
  gettimeofday(&start, NULL);  
  execYaoProtocol(&pd, median4, &io);
  gettimeofday(&end, NULL);  
  printf("time=%d ms\n",((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec - start.tv_usec))/1000);  

  fprintf(stderr, "Median4: result = %d\n", io.median);

  cleanupProtocol(&pd);
  return 0;
}