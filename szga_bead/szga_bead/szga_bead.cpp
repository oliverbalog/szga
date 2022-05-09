// 01. Feladat: 
/*
K�sz�tsen programot, ami a felhaszn�l� �ltal megadott elemsz�m�, v�letlen sz�mokkal felt�lt�tt t�mbben
megadja a k�vetkez� statisztikai eredm�nyeket: �tlag, medi�n, sz�r�s. Az eredm�nyeket �rja ki a
k�perny�re! Az elemsz�m megad�s�t billenty�zetr�l kell bek�rni!
*/

#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

int main()
{
  /*  setlocale(LC_ALL, "Hun");*/
    

	//printf("K�rem az t�mb elemsz�m�t: "); scanf_s("%d", &elemszam);

	////v�letlen sz�m v�letlen�t�se
	//srand((unsigned)time(NULL));
	////t�mb felt�lt�se �s ki�r�sa
	//printf("A t�mb t�bl�zatos form�ban:\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	tomb[i] = rand();
	//	osszeg += tomb[i];
	//	printf("%d\t", tomb[i]);
	//}
	//printf("\n");
	//
	//atlag = (double)((double)osszeg / (double)elemszam);
	//printf("A t�mb sz�mainak �tlaga: %f\n", atlag);

	////sorbarendez�s
	//for (size_t i = 0; i < elemszam - 1; i++)
	//{
	//	for (size_t j =i+ 1; j < elemszam; j++)
	//	{
	//		if (*(tomb+i) > *(tomb+j)) {
	//			medianhelper = *(tomb + i);
	//			*(tomb + i) = *(tomb + j);
	//			*(tomb + j) = medianhelper;
	//		}
	//	}
	//}
	////p�ratlan vagy p�ros
	//if (elemszam % 2 != 0) {
	//	median = tomb[(elemszam / 2)];
	//}
	//else {
	//	int kozepek = 0;
	//	kozepek = elemszam / 2;
	//	int egyikkozep=0;
	//	int masikkozep=0;

	//	egyikkozep = kozepek-1;
	//	masikkozep = kozepek;

	//	median = (tomb[egyikkozep] + tomb[masikkozep]) / 2;
	//	printf("A egyik: %d\n", egyikkozep);
	//	printf("A masik: %d\n", masikkozep);
	//}
	//printf("A medi�n: %f\n", median);
	//

	//
	//printf("\n\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	szorasszamitashanyados += (*(tomb + i) - atlag/*�tlag*/) * (*(tomb + i) - atlag);
	//}
	//szoras = sqrt(szorasszamitashanyados / elemszam);

	//printf("A sz�r�s: %f\n", szoras);



	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	printf("%d\t", *tomb+i);
	//}

	unsigned int elemszam = 0;
	double atlag = 0;
	double median = 0;
	double szoras = 0;
	int osszeg = 0;
	int medianhelper = 0;
	double szorasszamitashanyados = 0.0;

	int saveesp;

	const char* hun = "Hun";
	const char* esz_beker = "K�rem az t�mb elemsz�m�t: ";
	const char* esz_beker_scanf = "%d";
	const char* tombelemkiir = "%d\t";
	const char* sortores = "\n";
	const char* atlagkiir = "A t�mb sz�mainak �tlaga: %f\n";
	const char* mediankiir = "A medi�n: %f\n";
	const char* szoraskiir = "A sz�r�s: %f\n";


	int* tomb;
	const char* kiir = "%d. elem: %d\n";

	//setlocale
	_asm
	{
		mov saveesp, esp;
		push hun;
		push 0;
		call setlocale;
		mov esp, saveesp;
	}

	//v�ltoz�k null�z�sa
	_asm {
		mov elemszam, 0;
		mov atlag, 0;
		mov median, 0;
		mov szoras, 0;
		mov osszeg, 0;
		mov medianhelper, 0;
		mov szorasszamitashanyados, 0;
	}

	//bek�r�s
	_asm {
		//a bek�r� ki�r�s
		mov saveesp, esp;
		push esz_beker;
		call printf;
		//a be�ll�t�s
		lea eax, elemszam;
		push eax;
		push esz_beker_scanf;
		call scanf;

		mov esp, saveesp;
	}

	tomb = new int[elemszam];

	//t�mb felt�lt�s �s ki�r�s
	_asm
	{
		//ciklus l�trehoz�sa
		mov ecx, elemszam; //10 elem� a t�mb
		mov esi, 0; //t�mbindexhez
		mov edi, 1; //ki�r�shoz
	ciklus_tombfeltolt:
		mov eax, 0;
		rdrand ax; //16 bites v�letlen sz�m gener�l�s
		//mem�riac�m kiment�se v�ltoz�ba a dinamikus t�mb el�r�s�hez:
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltol�s hozz�ad�sa a pontos helyhez
		mov dword ptr[ebx], eax; //t�mbfelt�lt�s
		push ecx; //printf miatt
		mov saveesp, ESP; //ESP ment�se v�ltoz�ba
		push dword ptr[ebx]; //�rt�k verembe helyez�se
		push edi; //index
		push kiir; //form�z� sztring
		call dword ptr printf;
		mov esp, saveesp; //ESP vissza�ll�t�s
		pop ecx;
		add esi, 4; //int t�pus 4 b�jtos
		add edi, 1; //k�vetkez� index ki�r�shoz
		loop ciklus_tombfeltolt;
	}

	int x1, x2, x3, x4, x5;
	_asm {
		mov dword ptr[x1], 0;
		mov dword ptr[x2], 0;
		mov dword ptr[x3], 0;
		mov dword ptr[x4], 0;
		mov dword ptr[x5], 0;
	}

	_asm
	{
		mov saveesp, esp;
	outer_loop:
		cmp edi, elemszam;
		je done;
		mov esi, 0;
		mov edi, 1; //
		mov ebx, dword ptr[tomb];
		add ebx, esi;
	inner_loop:
		cmp x2, elemszam;
		je inner_loop_done;

		mov x1, 1;
		mov x2, 1;
		mov x3, dword ptr[tomb];
		add x3, x1;
		cmp ebx, x3;
		cmovg x4, ebx;
		cmovg ebx, x3;
		cmovg x3, x4;
		mov dword ptr[tomb], x3;

		inc x2;
		add x1, 4;
		jmp inner_loop;
		
	inner_loop_done:
		jmp outer_loop;
		add esi, 4; //int t�pus 4 b�jtos
		add edi, 1; //k�vetkez� index ki�r�shoz
	done:
		mov esp, saveesp;
	}



	//system("pause" megh�v�sa
	const char* _pause = "pause";
	_asm
	{
		mov esi, esp; //ESP ment�s
		push _pause;
		call dword ptr system;
		mov esp, esi; //ESP vissza�ll�t�s
	}
	//dinamikus mem�ria felszabad�t�sa;
	delete[] tomb;
	return 0;

}


