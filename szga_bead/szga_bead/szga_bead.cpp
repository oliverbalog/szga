// 01. Feladat: 
/*
Készítsen programot, ami a felhasználó által megadott elemszámú, véletlen számokkal feltöltött tömbben
megadja a következõ statisztikai eredményeket: átlag, medián, szórás. Az eredményeket írja ki a
képernyõre! Az elemszám megadását billentyûzetrõl kell bekérni!
*/

#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;

int main()
{
  /*  setlocale(LC_ALL, "Hun");*/
    

	//printf("Kérem az tömb elemszámát: "); scanf_s("%d", &elemszam);

	////véletlen szám véletlenítése
	//srand((unsigned)time(NULL));
	////tömb feltöltése és kiírása
	//printf("A tömb táblázatos formában:\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	tomb[i] = rand();
	//	osszeg += tomb[i];
	//	printf("%d\t", tomb[i]);
	//}
	//printf("\n");
	//
	//atlag = (double)((double)osszeg / (double)elemszam);
	//printf("A tömb számainak átlaga: %f\n", atlag);

	////sorbarendezés
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
	////páratlan vagy páros
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
	//printf("A medián: %f\n", median);
	//

	//
	//printf("\n\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	szorasszamitashanyados += (*(tomb + i) - atlag/*átlag*/) * (*(tomb + i) - atlag);
	//}
	//szoras = sqrt(szorasszamitashanyados / elemszam);

	//printf("A szórás: %f\n", szoras);



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
	const char* esz_beker = "Kérem az tömb elemszámát: ";
	const char* esz_beker_scanf = "%d";
	const char* tombelemkiir = "%d\t";
	const char* sortores = "\n";
	const char* atlagkiir = "A tömb számainak átlaga: %f\n";
	const char* mediankiir = "A medián: %f\n";
	const char* szoraskiir = "A szórás: %f\n";


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

	//változók nullázása
	_asm {
		mov elemszam, 0;
		mov atlag, 0;
		mov median, 0;
		mov szoras, 0;
		mov osszeg, 0;
		mov medianhelper, 0;
		mov szorasszamitashanyados, 0;
	}

	//bekérés
	_asm {
		//a bekérõ kiírás
		mov saveesp, esp;
		push esz_beker;
		call printf;
		//a beállítás
		lea eax, elemszam;
		push eax;
		push esz_beker_scanf;
		call scanf;

		mov esp, saveesp;
	}

	tomb = new int[elemszam];

	//tömb feltöltés és kiírás
	_asm
	{
		//ciklus létrehozása
		mov ecx, elemszam; //10 elemû a tömb
		mov esi, 0; //tömbindexhez
		mov edi, 1; //kiíráshoz
	ciklus_tombfeltolt:
		mov eax, 0;
		rdrand ax; //16 bites véletlen szám generálás
		//memóriacím kimentése változóba a dinamikus tömb eléréséhez:
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltolás hozzáadása a pontos helyhez
		mov dword ptr[ebx], eax; //tömbfeltöltés
		push ecx; //printf miatt
		mov saveesp, ESP; //ESP mentése változóba
		push dword ptr[ebx]; //érték verembe helyezése
		push edi; //index
		push kiir; //formázó sztring
		call dword ptr printf;
		mov esp, saveesp; //ESP visszaállítás
		pop ecx;
		add esi, 4; //int típus 4 bájtos
		add edi, 1; //következõ index kiíráshoz
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
		add esi, 4; //int típus 4 bájtos
		add edi, 1; //következõ index kiíráshoz
	done:
		mov esp, saveesp;
	}



	//system("pause" meghívása
	const char* _pause = "pause";
	_asm
	{
		mov esi, esp; //ESP mentés
		push _pause;
		call dword ptr system;
		mov esp, esi; //ESP visszaállítás
	}
	//dinamikus memória felszabadítása;
	delete[] tomb;
	return 0;

}


