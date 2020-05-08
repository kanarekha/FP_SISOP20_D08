#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

unsigned char charkey[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

unsigned char revchar(char ch)
{
   if (ch >= 'A' && ch <= 'Z')
      ch -= 'A';
   else if (ch >= 'a' && ch <='z')
      ch = ch - 'a' + 26;
   else if (ch >= '0' && ch <='9')
      ch = ch - '0' + 52;
   else if (ch == '+')
      ch = 62;
   else if (ch == '/')
      ch = 63;
   return(ch);
}

int encode(unsigned char in[], unsigned char out[], int panjang, int newline_flag, int separator)
{
   int index,index2,blks,left_over;

   blks = (panjang / 3) * 3;
   for (index=0,index2=0; index < blks; index += 3,index2 += 4) {
      out[index2] = charkey[in[index] >> 2];
      out[index2+1] = charkey[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
      out[index2+2] = charkey[((in[index+1] & 0x0f) << 2) + (in[index+2] >> 6)];
      out[index2+3] = charkey[in[index+2] & 0x3F];
      
      if (!(index2 % (separator+1)) && newline_flag) {
         out[index2+4] = '\n';
         index2++;
      }
   }
   left_over = panjang % 3;
   if (left_over == 1) {
      out[index2] = charkey[in[index] >> 2];
      out[index2+1] = charkey[(in[index] & 0x03) << 4];
      out[index2+2] = '=';
      out[index2+3] = '=';
      index2 += 4;
   }
   else if (left_over == 2) {
      out[index2] = charkey[in[index] >> 2];
      out[index2+1] = charkey[((in[index] & 0x03) << 4) + (in[index+1] >> 4)];
      out[index2+2] = charkey[(in[index+1] & 0x0F) << 2];
      out[index2+3] = '=';
      index2 += 4;
   }
   out[index2] = '\0';
   return(index2);
}

int decode(unsigned char in[], unsigned char out[], int panjang, int newline_flag, int separator)
{
   int index,index2,blks,left_over;

   if (in[panjang-1] == '=')
      panjang--;
   if (in[panjang-1] == '=')
      panjang--;

   blks = (panjang / 4) * 4;
   for (index=0,index2=0; index2 < blks; index += 3,index2 += 4) {
      out[index] = (revchar(in[index2]) << 2) + ((revchar(in[index2+1]) & 0x30) >> 4);
      out[index+1] = (revchar(in[index2+1]) << 4) + (revchar(in[index2+2]) >> 2);
      out[index+2] = (revchar(in[index2+2]) << 6) + revchar(in[index2+3]);

      if (!(index2 % (separator+1)) && newline_flag) {
         out[index2+4] = '\n';
         index2++;
      }
   }
   left_over = panjang % 4;
   if (left_over == 2) {
      out[index] = (revchar(in[index2]) << 2) + ((revchar(in[index2+1]) & 0x30) >> 4);
      out[index+1] = (revchar(in[index2+1]) << 4);
      index += 2;
   }
   else if (left_over == 3) {
      out[index] = (revchar(in[index2]) << 2) + ((revchar(in[index2+1]) & 0x30) >> 4);
      out[index+1] = (revchar(in[index2+1]) << 4) + (revchar(in[index2+2]) >> 2);
      out[index+2] = revchar(in[index2+2]) << 6;
      index += 3;
   }
   out[index] = '\0';
   return(index);
}


int main(int argc, char *argv[]){

   if(argc==2){
      int inputfile;
      if((inputfile = open(argv[1],O_RDONLY)) < 0){
         close(inputfile);
         exit();
      }
      int buff_len;
      unsigned char output[1024],data[1024];
      while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
      encode(data, output, strlen((char*)data),0,76);
      printf(1,"%s\n",output);
      close(inputfile);
      exit();
   }
   else if(argc==3){
      if((strcmp(argv[1],"-d"))==0){
         int inputfile;
         if((inputfile = open(argv[2],O_RDONLY)) < 0){
            close(inputfile);
            exit();
         }
         int buff_len;
         unsigned char output[1024],data[1024];
         while ((buff_len = read(inputfile,data,sizeof(data))) > 0);
         decode(data, output, strlen((char*)data),0,76);
         printf(1,"%s\n",output);
         close(inputfile);
         exit();
      }
}
}

