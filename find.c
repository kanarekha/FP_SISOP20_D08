#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char *backname(char *path){
	static char buf[DIRSIZ+1];

	char *p;

	for(p = path + strlen(path);p>=path && *p != '/';p--);
	p++;

	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf,p,strlen(p));
	memset(buf+strlen(p),' ',DIRSIZ-strlen(p));
	return buf;
}

int strstr(char *needle, char *haystack){
	int m = strlen(needle);
	int n = strlen(haystack);

	int i;
	for(i=0;i<=n-m;i++){
		int j;

		for(j=0;j<m;++j){
			if(haystack[i+j] != needle[j])break;
		}

		if(j==m)return 1;
	}
	return 0;
}


void ls(char *path, char *needle){
	char buf[512];
	struct dirent de;
	struct stat st;

	int dir = open(path,0);
	if(dir < 0){
		printf(2,"ls: cannot access '%s': No such file or directory\n",path);
		return;
	}

	if(fstat(dir,&st) < 0){
		printf(2,"ls: cannot stat '%s'\n",path);
		close(dir);
		return;
	}

	if(st.type == T_FILE){
		printf(1,"%s %d %d %d\n",backname(path),st.type,st.ino,st.size);
	}
	else if(st.type == T_DIR){
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf(1,"ls: path too long\n");
			return;
		}
		strcpy(buf,path);
		char *p = buf+strlen(buf);
		*p++ = '/';
		while(read(dir,&de,sizeof (de)) == sizeof (de)){
			if(de.inum == 0)continue;
			memmove(p,de.name,DIRSIZ);
			p[DIRSIZ] = 0;
			if(stat(buf,&st) < 0){
				printf(2,"ls: cannot stat '%s'\n",buf);
				continue;
			}

			if(strstr(needle,backname(buf)))
				printf(1,"%s %d %d %d\n",backname(buf),st.type,st.ino,st.size);
		}
	}
	close(dir);
	return;
}

int main(int argc, char *argv[])
{
	if(argc == 2){
		ls(".",argv[argc-1]);
	}
	else{
		for(int i=1;i<argc-1;++i){
			printf(1,"directory: %s\n",argv[i]);
			ls(argv[i],argv[argc-1]);
			if(i!=argc-1)printf(1,"\n");
		}
	}
	exit();
}
