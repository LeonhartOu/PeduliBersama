// FINAL PROJECT BOOTCAMP : PEDULIBERSAMA-Sedang diusahakan
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

struct Peserta{
	char name[255];
	short vac;
	int age;
	unsigned periode;
	long riwayat;
	bool isActive;
};

Peserta pesertas[200];
int totalpeserta=0;

void frontpage();
void addnewpeserta();
void hapuspeserta();
void viewpeserta();
void mainMenu();
void sortpeserta();
void searchpeserta();

int main(){
  	FILE *file = fopen ("file.txt","r");
	mainMenu();
  	fclose(file);
 	return 0;
}


void frontpage(){
	printf("\n");
	puts("Selamat Datang di PeduliBersama");
	puts("1.Tambah Peserta Baru");
	puts("2.Lihat Daftar Peserta");
	puts("3.Cari berdasarkan nama");
	puts("4.Remove Peserta");
	puts("5.Keluar");
}

void viewpeserta() {
	if(!totalpeserta){
		printf("belum ada data peserta\n");
		return;
	}
    for(int i = 0; i < totalpeserta; i++) {
        if(pesertas[i].isActive) {
			Peserta temp = pesertas[i];
			printf("- %s\n", temp.name);
			printf("  Umur : %d\n",temp.age);

			printf("  status vaksinasi : ");
			if(!temp.periode) printf("Belum vaksin\n");
			else if(temp.periode == 1) printf("vaksin pertama\n");
			else printf("vaksin kedua\n");

			if(temp.periode){ // sudah divaksin, bisa kita output jenisnya
				printf("  jenis vaksin : ");
				switch(temp.vac){
					case 1 :
						printf("Astrazeneca\n");
						break;
					case 2 :
						printf("Sinovac\n");
						break;
					case 3 :
						printf("Moderna\n");
						break;
				}
			}

			printf("  Riwayat Terjangkit : ");
			if(temp.riwayat) printf("Pernah terjangkit\n");
			else printf("Belum pernah terjangkit\n");

            printf("\n");
        }
    }
}

void addnewpeserta(){
  	FILE *file = fopen ("file.txt","a");
	printf("Masukan Nama anda dalam huruf kecil!\n");
	printf("Name: ");
	scanf("%[^\n]", pesertas[totalpeserta].name);
	do {
            printf("Age : ");
            scanf("%d",&pesertas[totalpeserta].age);
            if (pesertas[totalpeserta].age < 12 || pesertas[totalpeserta].age > 80){
            	printf("Belum masuk rentang umur penerima vaksin\n");
			}
        } while(pesertas[totalpeserta].age < 12 || pesertas[totalpeserta].age > 80);
	printf("1 : Astrazeneca\n2 : sinovac\n3 : moderna\n");
	do {
            printf("Vaksin :  ");
            scanf("%d", &pesertas[totalpeserta].vac);
        } while(pesertas[totalpeserta].vac < 1 || pesertas[totalpeserta].vac > 3);
	do {
            printf("Periode : ");
            scanf("%u",&pesertas[totalpeserta].periode);
            if (pesertas[totalpeserta].periode == 3){
            	printf("Vaksin ketiga hanya untuk tenaga kesehatan\n");
			}
        } while(pesertas[totalpeserta].periode < 1 || pesertas[totalpeserta].periode > 2);
	printf("Riwayat, \n");
	do {
            printf("1 untuk pernah, 0 untuk belum pernah :  ");
            scanf("%ld",&pesertas[totalpeserta].riwayat);
        } while(pesertas[totalpeserta].riwayat < 0 || pesertas[totalpeserta].riwayat > 1);
	pesertas[totalpeserta].isActive = true;
	totalpeserta++;
	sortpeserta(); 
  	fprintf(file,"%s %d %d %u %ld",pesertas[totalpeserta].name, pesertas[totalpeserta].age, pesertas[totalpeserta].vac, pesertas[totalpeserta].periode, pesertas[totalpeserta].riwayat);
  // sort data everytime new data input
}

void hapuspeserta(){
    char hapus[255];
    printf("Masukan Nama Peserta yang anda ingin hapus dalam huruf kecil!\n");
    printf("Nama : ");
    scanf("%[^\n]", hapus); getchar();
    for(int i = 0; i < totalpeserta; i++) {
        if(strcmp(pesertas[i].name, hapus) == 0) {
            pesertas[i].isActive = false;
        }
    }
}

void mainMenu() {
    bool onApp = true;

    while(onApp) {
        
        frontpage();
        int choice = -1;

        do {
            printf(">> ");
            scanf("%d", &choice); getchar();
        } 
		while(choice < 1 || choice > 5);
         	if(choice == 1) {
                addnewpeserta();
    		}else if(choice ==2){
    			viewpeserta();
    		}else if(choice ==3){
    			searchpeserta();
			}else if(choice == 4){
				hapuspeserta();
              // else if for filter in coming!!! - mujak
			}else if(choice == 5) {
           		printf("Bye bye!");
            	onApp = false;
        }
	}
}

void mergesort(int start, int end){
	int mid = (start + end)/2;
	int left = start;
	int right = mid + 1;
	Peserta temp[200];
	int index = start;
	for(; left <= mid && right <= end ;){
		if(strcmp(pesertas[left].name,pesertas[right].name)<=0){
			temp[index] = pesertas[left];
			left++;
		} else {
			temp[index] = pesertas[right];
			right++;
		}
		index++;
	}
	for(; left <= mid;){
		temp[index] = pesertas[left];
		left++;
		index++;
	}
	for(; right <= end ;){
		temp[index] = pesertas[right];
		right++;
		index++;
	}
	for(int i = start; i <= end; i++){
		pesertas[i] = temp[i];
	}
}

void splitmergesort(int start, int end){
	if(start >= end) return;
	int mid = (start + end)/2;
	splitmergesort(start, mid);
	splitmergesort(mid+1, end);
	mergesort(start,end);
}

void sortpeserta(){
	splitmergesort(0,totalpeserta-1);
}

void searchpeserta(){
  	// binary search implementation
	int start = 0;
	int end = totalpeserta-1;
	char c[200];
	printf("Masukkan nama yang anda cari dan pastikan identik : ");
	scanf("%[^\n]", c);
	int res = -1;
	for(; start <=  end; ){
		int mid = (start+end) / 2;
		int temp = strcmp(c,pesertas[mid].name);
		if(temp == 0){
			res = mid;
			break;
		} else if(temp < 0){ // current string is smaller, then we will check the half after it
			start = mid+1;
		} else {
			end = mid-1;
		}
	}
	if(res == -1) printf("nama %s tidak ditemukan di daftar\n",c);
	else {
		Peserta temp = pesertas[res];
		printf("Ditemukan!\n- %s\n", temp.name);
		printf("  Umur : %d\n",temp.age);

		printf("  status vaksinasi : ");
		if(!temp.periode) printf("Belum vaksin\n");
		else if(temp.periode == 1) printf("vaksin pertama\n");
		else printf("vaksin pertama\n");

		if(temp.periode){ // sudah divaksin, bisa kita output jenisnya
			printf("  jenis vaksin : ");
			switch(temp.vac){
				case 1 :
					printf("Astrazeneca\n");
					break;
				case 2 :
					printf("Sinovac\n");
					break;
				case 3 :
					printf("Moderna\n");
					break;
			}
		}

		printf("  Riwayat Terjangkit : ");
		if(temp.riwayat) printf("Pernah terjangkit\n");
		else printf("Belum pernah terjangkit\n");
	}
}
