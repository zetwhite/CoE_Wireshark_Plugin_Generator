#include <stdio.h>
#include <stdlib.h>
#include "PcapFile.hpp"
int main()
{
	char fname[256 + 1] = "";
	printf(" analysis pcap file name :");
	scanf("%s", fname, sizeof(fname));
 
	FILE *fp = 0; 
    fp = fopen(fname, "rb");
	if (fp == 0)
	{
		perror("fail to open file");
		system("pause");
		return 0;
	}
 
	PFHeader pfh = { 0, };
	if (ParsePCapFile(fp, &pfh) == 0)
	{
		printf("this is not pcap file\n");
		fclose(fp);
		system("pause");
		return 0;
	}
 
	/*switch (pfh.linktype)
	{
	case LT_ETHER: ParseEther(fp); break;
	default: printf("Not Support\n"); break;
	}*/
	fclose(fp);
	system("pause");
	return 0;
}