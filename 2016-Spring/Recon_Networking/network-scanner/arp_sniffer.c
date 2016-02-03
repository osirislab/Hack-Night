/* Simple ARP Sniffer.                                                   */ 
/* Author: Luis Martin Garcia. luis.martingarcia [.at.] gmail [d0t] com  */
/* To compile: gcc arpsniffer.c -o arpsniff -lpcap                       */
/* Run as root!                                                          */ 
/*                                                                       */
/* This code is distributed under the GPL License. For more info check:  */
/* http://www.gnu.org/copyleft/gpl.html                                  */

#include <pcap.h> 
#include <stdlib.h> 
#include <string.h> 

/* ARP Header, (assuming Ethernet+IPv4)            */ 
#define ARP_REQUEST 1   /* ARP Request             */ 
#define ARP_REPLY 2     /* ARP Reply               */ 
typedef struct arphdr { 
    u_int16_t htype;    /* Hardware Type           */ 
    u_int16_t ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_int16_t oper;     /* Operation Code          */ 
    u_char sha[6];      /* Sender hardware address */ 
    u_char spa[4];      /* Sender IP address       */ 
    u_char tha[6];      /* Target hardware address */ 
    u_char tpa[4];      /* Target IP address       */ 
}arphdr_t; 

#define MAXBYTES2CAPTURE 2048 



int main(int argc, char *argv[]){

 int i=0; 
 bpf_u_int32 netaddr=0, mask=0;    /* To Store network address and netmask   */ 
 struct bpf_program filter;        /* Place to store the BPF filter program  */ 
 char errbuf[PCAP_ERRBUF_SIZE];    /* Error buffer                           */ 
 pcap_t *descr = NULL;             /* Network interface handler              */ 
 struct pcap_pkthdr pkthdr;        /* Packet information (timestamp,size...) */ 
 const unsigned char *packet=NULL; /* Received raw data                      */ 
 arphdr_t *arpheader = NULL;       /* Pointer to the ARP header              */ 
 memset(errbuf,0,PCAP_ERRBUF_SIZE); 

if (argc != 2){ 
    printf("USAGE: arpsniffer <interface>\n"); 
    exit(1); 
} 
 /* Open network device for packet capture */ 
 if ((descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0,  512, errbuf))==NULL){
    fprintf(stderr, "ERROR: %s\n", errbuf);
    exit(1);
 }
    
 /* Look up info from the capture device. */ 
 if( pcap_lookupnet( argv[1] , &netaddr, &mask, errbuf) == -1){
     fprintf(stderr, "ERROR: %s\n", errbuf);
    exit(1);
 }

 /* Compiles the filter expression into a BPF filter program */ 
if ( pcap_compile(descr, &filter, "arp", 1, mask) == -1){
    fprintf(stderr, "ERROR: %s\n", pcap_geterr(descr) );
    exit(1);
 }

 /* Load the filter program into the packet capture device. */ 
 if (pcap_setfilter(descr,&filter) == -1){
    fprintf(stderr, "ERROR: %s\n", pcap_geterr(descr) );
    exit(1);
 }


 while(1){ 
 
  if ( (packet = pcap_next(descr,&pkthdr)) == NULL){  /* Get one packet */ 
    fprintf(stderr, "ERROR: Error getting the packet.\n", errbuf);
    exit(1);
 }

  arpheader = (struct arphdr *)(packet+14); /* Point to the ARP header */ 

  printf("\n\nReceived Packet Size: %d bytes\n", pkthdr.len); 
  printf("Hardware type: %s\n", (ntohs(arpheader->htype) == 1) ? "Ethernet" : "Unknown"); 
  printf("Protocol type: %s\n", (ntohs(arpheader->ptype) == 0x0800) ? "IPv4" : "Unknown"); 
  printf("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REQUEST)? "ARP Request" : "ARP Reply"); 
 
 /* If is Ethernet and IPv4, print packet contents */ 
  if (ntohs(arpheader->htype) == 1 && ntohs(arpheader->ptype) == 0x0800){ 
    printf("Sender MAC: "); 

    for(i=0; i<6;i++)
        printf("%02X:", arpheader->sha[i]); 

    printf("\nSender IP: "); 

    for(i=0; i<4;i++)
        printf("%d.", arpheader->spa[i]); 

    printf("\nTarget MAC: "); 

    for(i=0; i<6;i++)
        printf("%02X:", arpheader->tha[i]); 

    printf("\nTarget IP: "); 

    for(i=0; i<4; i++)
        printf("%d.", arpheader->tpa[i]); 
    
    printf("\n"); 

  } 

 } 

return 0; 

}
/* EOF */
