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
 // /*  setlocale(LC_ALL, "Hun");*/
	//int elemszam = 0;
	//double atlag = 0;
	//double median = 0;
	//double szoras = 0;
	//int osszeg = 0;
	//int medianhelper = 0;
	//double szorasszamitashanyados = 0.0;
	//int* tomb;

	//printf("K�rem az t�mb elemsz�m�t: "); scanf_s("%d", &elemszam);
	//tomb = new int[elemszam];
	///*v�letlen sz�m v�letlen�t�se*/
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
	//
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
	//
	//	egyikkozep = kozepek-1;
	//	masikkozep = kozepek;
	//
	//	median = (tomb[egyikkozep] + tomb[masikkozep]) / 2;
	//	printf("A egyik: %d\n", egyikkozep);
	//	printf("A masik: %d\n", masikkozep);
	//}
	//printf("A medi�n: %f\n", median);
	//
	//
	//
	//printf("\n\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	szorasszamitashanyados += (*(tomb + i) - atlag/*�tlag*/) * (*(tomb + i) - atlag);
	//}
	//szoras = sqrt(szorasszamitashanyados / elemszam);
	//
	//printf("A sz�r�s: %f\n", szoras);
	//
	//
	//
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	printf("%d\t", *tomb+i);
	//}

	int elemszam ;
	double atlag ;
	double median ;
	double szoras ;
	int osszeg ;
	int medianhelper ;
	double szorasszamitashanyados;

	int saveesp;
	int saveeax;
	int saveecx;

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
	int tomblength1, tomblength2;
	_asm {
		mov x1, 0;
		mov x2, 0;
		mov x3, 0;
		mov x4, 0;
		mov x5, 0;
		mov tomblength1, 0;
		mov tomblength2, 0;

		mov saveesp, esp;
		mov esp, elemszam;

		mov tomblength1, esp;
		sub tomblength1, 1;
		mov tomblength2, esp;

		mov esp, saveesp;
	}


	_asm {
		//�tlag
		mov atlag, 0;
		mov ecx, elemszam; 
		mov esi, 0; //t�mbindexhez
		mov edi, 1; //ki�r�shoz
	ciklus_walk:
		mov eax, 0;
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltol�s hozz�ad�sa a pontos helyhez

		add atlag, ebx;

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
		loop ciklus_walk;

		mov eax, 0;
		mov eax, atlag;
		idiv elemszam;
		mov atlag, eax;
	}

	cout << "�tlag: " << atlag;


	_asm
	{
		mov esi, 0; //-->
						//-->T�mbv�ltoz� �s mem�riac�mugr�s m�ret be�ll�t�s
		mov edi, 1; //-->

		mov saveesp, esp; //esp �rt�k ment�s
		//-----------------------------K�LS� CIKLUS---------------------------------------------//
	outer_loop:						// K�LS� CIKLUS
		//-----------------------------K�LS� CIKLUS---------------------------------------------//
		cmp edi, tomblength1;  //edi-ben l�v� "index" �s a hossz �sszehasonl�t�sa		t�mbhossz: elemszam - 1
		je done;  //Ha egyenl�, akkor v�ge a ciklusnak 
		mov x1, 0;
		mov x2,1;		//2- mert az els� t�mbelemet kihagyom, az lesz el�sz�r a k�ls�bbik t�mbben, �gy itt el�g, ha m�sodikt�l olvasok
		mov ebx, dword ptr[tomb];	//ebx-be beker�l a t�mb kezd� mem�riac�me
										//--A k�ls� t�mb �rt�k�hez
		add ebx, esi;				//a t�mb kezd� mem�riac�m�hez hozz�adok annyit, hogy a k�vetkez� elemre mutasson
		//-----------------------------BELS� CIKLUS---------------------------------------------//
			inner_loop:				// BELS� CIKLUS
		//-----------------------------BELS� CIKLUS---------------------------------------------//
				mov eax, x2;	//eax-be rakom az x2-t, ami a bels� t�mb indexedik elem�nek �rt�ke
				cmp eax, tomblength2;	//t�mbindexet �sszehasonl�tom a t�mbm�rettel
				je inner_loop_done;		//ha egyenl�, v�ge a ciklusnak
				mov x2, eax;

				mov saveeax, eax;
				mov eax, dword ptr[tomb];
				mov x3, eax;
				mov eax, saveeax;
				mov saveecx, ecx;
				mov ecx, x1;
				add x3, ecx;
				mov ecx, saveecx;

				cmp ebx, x3;
				jg csere;

				add x2,1;//-->	//Hozz�adom a t�mbindexhez az egyet �s a 4 b�jtot a mem�ri�hoz
				add x1, 4;//-->		

			jmp inner_loop;	//Ha nincs csere, �jra vissza a bels� ciklus elej�re

					csere:	//Ha cser�lni kell
							//ebx -> ebben van a k�ls� t�mb �rt�k
							//x3 -> ebben van a bels� t�mb �rt�k

							mov ecx, dword ptr[ebx] //x4-be belerakom a k�ls� ciklus t�mb �rt�ket, h elmentsem
							mov ebx, x3;	//ebx c�m�re odateszem az x3 (bels� t�mb �rt�k�t)
							mov saveecx, ecx;
							mov x3, ecx;
							mov ecx, saveecx;

							add x2, 1;//-->
											//Hozz�adom a t�mbindexhez az egyet �s a 4 b�jtot a mem�ri�hoz, ha cser�lem is
							add x1, 4;//-->		

							jmp inner_loop;

	inner_loop_done:
		add esi, 4; //int t�pus 4 b�jtos
		add edi, 1; //k�vetkez� index ki�r�shoz
		jmp outer_loop;
	done:
		mov esp, saveesp;
	}
	printf("\n\n");
	_asm {
		//ciklus l�trehoz�sa
		mov ecx, elemszam; //10 elem� a t�mb
		mov esi, 0; //t�mbindexhez
		mov edi, 1; //ki�r�shoz
	ciklus_walk:
		mov eax, 0;
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltol�s hozz�ad�sa a pontos helyhez

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
		loop ciklus_walk;
	}

	//system("pause") megh�v�sa
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


