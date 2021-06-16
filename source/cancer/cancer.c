#include <stdio.h>
#include <sys/time.h>
#include <obliv.h>

#include "cancer.h"

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
    if(protocolAcceptTcp2PProfiled(&pd, argv[1])){
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
  
  if (currentParty == 1) {
    io.UniformityofCellSize = 3;
    io.UniformityofCellShape = 3;
    io.BareNuclei = 3;
    io.BlandChromatin = 3;
    io.SingleEpithelialCellSize = 3;
    io.ClumpThickness = 3;
    io.NormalNucleoli = 3;
    io.MarginalAdhesion = 3;
    io.Mitoses = 3;
  }
  
  execYaoProtocol(&pd, analyze, &io); 
  fprintf(stderr, "CommunicationSend: %zu\n", tcp2PBytesSent(&pd));
  fprintf(stderr, "CommunicationFlush: %zu\n", tcp2PFlushCount(&pd));

  cleanupProtocol(&pd);
  return 0;
}