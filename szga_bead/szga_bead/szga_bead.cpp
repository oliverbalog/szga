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
 // /*  setlocale(LC_ALL, "Hun");*/
	//int elemszam = 0;
	//double atlag = 0;
	//double median = 0;
	//double szoras = 0;
	//int osszeg = 0;
	//int medianhelper = 0;
	//double szorasszamitashanyados = 0.0;
	//int* tomb;

	//printf("Kérem az tömb elemszámát: "); scanf_s("%d", &elemszam);
	//tomb = new int[elemszam];
	///*véletlen szám véletlenítése*/
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
	//
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
	//
	//	egyikkozep = kozepek-1;
	//	masikkozep = kozepek;
	//
	//	median = (tomb[egyikkozep] + tomb[masikkozep]) / 2;
	//	printf("A egyik: %d\n", egyikkozep);
	//	printf("A masik: %d\n", masikkozep);
	//}
	//printf("A medián: %f\n", median);
	//
	//
	//
	//printf("\n\n");
	//for (size_t i = 0; i < elemszam; i++)
	//{
	//	szorasszamitashanyados += (*(tomb + i) - atlag/*átlag*/) * (*(tomb + i) - atlag);
	//}
	//szoras = sqrt(szorasszamitashanyados / elemszam);
	//
	//printf("A szórás: %f\n", szoras);
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
		//átlag
		mov atlag, 0;
		mov ecx, elemszam; 
		mov esi, 0; //tömbindexhez
		mov edi, 1; //kiíráshoz
	ciklus_walk:
		mov eax, 0;
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltolás hozzáadása a pontos helyhez

		add atlag, ebx;

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
		loop ciklus_walk;

		mov eax, 0;
		mov eax, atlag;
		idiv elemszam;
		mov atlag, eax;
	}

	cout << "Átlag: " << atlag;


	_asm
	{
		mov esi, 0; //-->
						//-->Tömbváltozó és memóriacímugrás méret beállítás
		mov edi, 1; //-->

		mov saveesp, esp; //esp érték mentés
		//-----------------------------KÜLSÕ CIKLUS---------------------------------------------//
	outer_loop:						// KÜLSÕ CIKLUS
		//-----------------------------KÜLSÕ CIKLUS---------------------------------------------//
		cmp edi, tomblength1;  //edi-ben lévõ "index" és a hossz összehasonlítása		tömbhossz: elemszam - 1
		je done;  //Ha egyenlõ, akkor vége a ciklusnak 
		mov x1, 0;
		mov x2,1;		//2- mert az elsõ tömbelemet kihagyom, az lesz elõször a külsõbbik tömbben, így itt elég, ha másodiktól olvasok
		mov ebx, dword ptr[tomb];	//ebx-be bekerül a tömb kezdõ memóriacíme
										//--A külsõ tömb értékéhez
		add ebx, esi;				//a tömb kezdõ memóriacíméhez hozzáadok annyit, hogy a következõ elemre mutasson
		//-----------------------------BELSÕ CIKLUS---------------------------------------------//
			inner_loop:				// BELSÕ CIKLUS
		//-----------------------------BELSÕ CIKLUS---------------------------------------------//
				mov eax, x2;	//eax-be rakom az x2-t, ami a belsõ tömb indexedik elemének értéke
				cmp eax, tomblength2;	//tömbindexet összehasonlítom a tömbmérettel
				je inner_loop_done;		//ha egyenlõ, vége a ciklusnak
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

				add x2,1;//-->	//Hozzáadom a tömbindexhez az egyet és a 4 bájtot a memóriához
				add x1, 4;//-->		

			jmp inner_loop;	//Ha nincs csere, újra vissza a belsõ ciklus elejére

					csere:	//Ha cserélni kell
							//ebx -> ebben van a külsõ tömb érték
							//x3 -> ebben van a belsõ tömb érték

							mov ecx, dword ptr[ebx] //x4-be belerakom a külsõ ciklus tömb értéket, h elmentsem
							mov ebx, x3;	//ebx címére odateszem az x3 (belsõ tömb értékét)
							mov saveecx, ecx;
							mov x3, ecx;
							mov ecx, saveecx;

							add x2, 1;//-->
											//Hozzáadom a tömbindexhez az egyet és a 4 bájtot a memóriához, ha cserélem is
							add x1, 4;//-->		

							jmp inner_loop;

	inner_loop_done:
		add esi, 4; //int típus 4 bájtos
		add edi, 1; //következõ index kiíráshoz
		jmp outer_loop;
	done:
		mov esp, saveesp;
	}
	printf("\n\n");
	_asm {
		//ciklus létrehozása
		mov ecx, elemszam; //10 elemû a tömb
		mov esi, 0; //tömbindexhez
		mov edi, 1; //kiíráshoz
	ciklus_walk:
		mov eax, 0;
		mov ebx, dword ptr[tomb];
		add ebx, esi; //eltolás hozzáadása a pontos helyhez

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
		loop ciklus_walk;
	}

	//system("pause") meghívása
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


