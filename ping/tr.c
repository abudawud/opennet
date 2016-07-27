#include <stdio.h>
#define LUAS(x)	    (22/7*x*x)
int main(){
    struct{
	int umur;
	char nim[5];
	char nama[5];
    }mahasiswa;
    mahasiswa data={20,"E321","QWER"};
    data.umur=20;
    printf("%d %d",data.umur,LUAS(7));
    return 0;
}
