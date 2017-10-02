#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define BUF 501
int spice2int(char*);
void int2spice(int,char*);
int potSweep(int,int,int);
int main(int argc, char* argv[]) {
   if(argc < 4) {
      printf("too few arguements\n");
      return -1;
    }
    else if(strlen(argv[1])>1) {
      printf("single char flags\n");
      return 0;
    }
    else {
      char flag = *argv[1];
      int ret;
      int min;
      int max;
      int NoS;
      FILE *outf;
      outf = fopen("./out/resSweep/res.out","w+");
      if (flag == 'w') {
	min = spice2int(argv[2]);
        NoS = atoi(argv[3]);
        max = spice2int(argv[4]);
        int ssize;
        int outInt[BUF];
        char outStr[BUF][50];
        if(min < 0) {
          printf("min input error\n");
          ret = -1;
        }
        else if(max < 0) {
          printf("max input error\n");
          ret = -1;
        }
        else if(NoS > BUF) {
          printf("data input max\n");
          ret = -1;
        }
        else{
          max=max-min;
          ssize=max/(NoS-1);
	  for(int i=1;i<NoS;i++)
	    outInt[i] = (min/2)+(ssize*(i-1));
	    outInt[1] = min; 
          if(NoS<BUF && outInt[NoS] != max)
	    outInt[NoS] = max;
	  for(int i=1;i<(NoS+1);i++) {
	    int2spice(outInt[i],outStr[i]);
	    fprintf(outf,"r%d %s\n",i,outStr[i]);
	  }
          ret = 0; 
        }  	
      }
      else if (flag == 's') {
        max = spice2int(argv[2]);
	min = spice2int(argv[3]);
	char outS[15];
        int2spice((max-min),outS);
        printf("%s\n", outS);
        ret = 0;
      }
      else {
        printf("incorrect flag\n");
        ret = -1;
      }
    fclose(outf); 
    return ret;
    }
}

void int2spice(int val, char *outSp) {
     int i=0;
     int l=2;
     int up=val/1000;
     int lo=val%1000;
     int nudig=0;
     int nldig=0;
     char dig; 
     if(up!=0) {
     nudig = floor(log10(up));
     while(i<nudig+1){
	dig = (char) ((up/((int) pow(10,i)))%10);
	dig += '0';
	*(outSp+(nudig-i))=dig;
	i++;
     }
     *(outSp+nudig+1)='k'; 
     i=0;
     if(lo!=0) {
      nldig = floor(log10(lo));
      while(i<l+1) { 
	dig = (char) ((lo/((int) pow(10,i)))%10);
	dig += '0';
	*((outSp+nudig+2)+(l-i))=dig;
	i++;
      }
     } 
     else *(outSp+nudig+2) = ' ';  	
     *(outSp+nudig+5)='\0';
     }
     else {
      nldig = floor(log10(lo));
      while(i<nldig+1){
	dig = (char) ((lo/((int) pow(10,i)))%10);
	dig += '0';
	*(outSp+(nldig-i))=dig;
	i++;
     }
     *(outSp+nldig+1)='\0'; 
    }
}
	
int spice2int(char* inpSp) {
	int out=0;
	int tmp=0;
	int len=0;
	int lef=0;
	int i=0;
	int fact=0;
	int t=0;
	int l=0; 
	len=strlen(inpSp);
	while(i<len){
           tmp=0;
	   if(isdigit(*(inpSp+i))){
	     out*=10;
	     tmp=(int)(*(inpSp+i)-'0');
	     out+=tmp;
             i++;
	    }
           else {
             if((i==0) || (*(inpSp+i) != 'k')){
              out=-1;
	      i=len;
	     }
	     else {
	      out*=1000;
              lef=len-i;
	      i++; 
              while(l<lef){
		if(isdigit(*(inpSp+i))){
		  t=(int)(*(inpSp+i)-'0');
		  fact = (int)pow(10.0,l);
		  fact = 100/fact;
		  t*=fact;
		  tmp+=t;
                  l++;
		  i++;
		}
		else{
		  i=len;
                  l=lef;
		}
	       }
         	out+=tmp;
	     }
           }                  
	}
        return out;
}
