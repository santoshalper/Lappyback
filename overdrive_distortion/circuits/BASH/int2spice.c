#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define BUF 501
int spice2int(char*);
void int2spice(int,char*);
int main(int argc, char* argv[]) {
    int min = spice2int(argv[1]);
    int NoS = atoi(argv[2]);
    int max = spice2int(argv[3]);
    int ssize;
    int outInt[BUF];
    char outStr[BUF][50];
    if(min < 0) {
      printf("min input error\n");
      return -1;
    }
    else if(max < 0) {
      printf("max input error\n");
      return -1;
    }
    else if(NoS > BUF) {
      printf("data input max\n");
      return -1;
    }
    else{
      ssize=(max-min);
      ssize=ssize/NoS;
	for(int i=0;i<NoS;i++)
	  outInt[i] = min+(ssize*i);
        if(NoS<BUF && outInt[NoS-1] != max)
	  outInt[NoS] = max;
	for(int i=0;i<(NoS+1);i++) {
	 int2spice(outInt[i],outStr[i]);
 	 printf("out[%d]=%d %s\n", i, outInt[i], outStr[i]);
	}
      return 0;
    }
}
void int2spice(int val, char *outSp) {
     int i=0;
     int l=2;
     int up=val/1000;
     int lo=val%1000;
     int nudig = floor(log10(up));
     int nldig=0;
     char dig; 
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
