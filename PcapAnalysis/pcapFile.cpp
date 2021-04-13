#include "PcapFile.hpp"
 
char buffer[0x100000];
void ViewPCapFile(PFHeader *pfh);
void ViewPacketHeaderInfo(PackHeader *ph,int pno);
 
void ParseEther(FILE *fp)
{
	PackHeader ph = { 0 };
	int pno=0;
	while (fread(&ph,sizeof(PackHeader),1,fp)==1)
	{
		pno++;
		ViewPacketHeaderInfo(&ph, pno);
		fread(buffer, sizeof(uchar), ph.caplen, fp);
	}
}
 
int ParsePCapFile(FILE *fp, PFHeader *pfh)
{
	fread(pfh, sizeof(PFHeader), 1, fp);
	if (pfh->magic != PF_MAGIC)
	{
		return 0;
	}
	ViewPCapFile(pfh);
	return 1;
}
void ViewPCapFile(PFHeader *pfh)
{
	printf("=========== PCAP File Infomation ============\n");
	printf("\tVersion : %d.%d\n", pfh->major, pfh->minor);
	printf("\tMax Length Packet:%d bytes\n", pfh->max_caplen);
}
void ViewPacketHeaderInfo(PackHeader *ph, int pno)
{
	printf("!!! <%4d th> 프레임 !!!\n", pno);
	printf("패킷:%6d bytes 캡쳐:%6d\n", ph->packlen, ph->caplen);
}