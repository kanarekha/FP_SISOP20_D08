#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int length(char *input){
    int length = 0;
    while(input[length]!='\0')
    {
        length++;                               // menunjukkan berapa banyak character dalam input
    }
    return length;
}

int main(int argc, char *argv[]){
	int file1, file2;
	int a, b;
	char buf1[256], buf2[256], fill[512];
	int counter1 = 0, counter2 = 0, counter = 0, counters1 = 0, counters2 = 0, cs1 = 0, cs2 =0;

	if((file1 = open(argv[1], O_RDONLY)) < 0){                      // Error handling : cannot read file 1
		printf(1, "Failed to read files %s\n", argv[1]);
		exit();
	}
	if((file2 = open(argv[2], O_RDONLY)) < 0){                      // Error handling : cannot read file 2
		printf(1, "failed to read %s\n", argv[2]);
		exit();
	}

	a = read(file1, buf1, sizeof(buf1));                        // read n character from file1 and places it to  buf1
	b = read(file2, buf2, sizeof(buf2));                        // read n character from file2 and places it to  buf2
	int p1, p2;
	p1 = length(buf1);                                          // Masuk fungsi lenght dengan inout buf1
	p2 = length(buf2);                                          // Masuk fungsi lenght dengan input buf2

if(a > 0 || b > 0){

		while(p1 || p2){
		char pertama[50];
		char kedua[50];

			while(buf1[counters1] != ' '){                  // Selama ada character yg ditemukan
				pertama[cs1] = buf1[counters1];
				counters1++; cs1++;                         // Pindah ke character berikutnya dalam buf1
			}

			while(buf2[counters2] != ' '){                  // Selama ada character yg ditemukan
				kedua[counters2] = buf2[cs2];
				counters2++; cs2++;                         // Pindah ke character berikutnya dalam buf1
			}

			int pbuf1, pbuf2, i, compare = 0;
			pbuf1 = length(pertama);                        // pbuf1 = nilai return fungsi length dengan input pertama
			pbuf2 = length(kedua);                          // pbuf2 = nilai return fungsi length dengan input kedua

			if(pbuf1 != pbuf2) compare = 0;
			else{
				for(i = 0; i<pbuf1; i++){
					if(pertama[i]!=kedua[i]) compare = 0;
					else compare = 1;
				}
			}

			while(buf1[counter1] != '\n'){
				fill[counter] = buf1[counter1];             // pindah ke fill dari buf1(counter 1)
				counter++; counter1++;
			}
			fill[counter] = ' ';
			counter++;
			if(compare == 0) {
				printf(1, "WARN : The first word is not match!\n");
				while(buf2[counter2] != '\n'){
				fill[counter] = buf2[counter2];             // pindah ke fill dari buf2(counter 2 )
				counter++; counter2++;
				}
			}
			else{
				counter2 += counters2+1;
				while(buf2[counter2] != '\n'){
					fill[counter] = buf2[counter2];
					counter++; counter2++;
				}
			}
			fill[counter] = '\n';
			counter++;
			counter1++;
			counter2++;
			counters1 = counter1;
			counters2 = counter2;
			p1-=counter1;
            p2-=counter2;
		}
	}
	close(file1);
	close(file2);
	printf(1, "%s", fill);
	exit();
}
