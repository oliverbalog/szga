#include <iostream>
#include <ctime>
using namespace std;

int main() 
{
	/*
		Készítsen egy 10 elemû, egész típusú tömböt.
		Kérjen be billentyûzetrõl két számot, (A,B, ahol A<B), majd töltse fel A és B közötti 
			véletlen számokkal a tömböt.
		Ezután határozza meg, hány darab páros szám található a tömbben, és adja meg a páros számok összegét!
		A táblázatot, az eredményeket írjuk ki a képernyõre.
	*/
	int A=0, B=0, tomb[10], parosdb=0, parososszeg = 0;
	setlocale(0, "Hun");
	printf("Kérem az A értékét: "); scanf_s("%d", &A);
	printf("Kérem az B értékét: "); scanf_s("%d", &B);
	//véletlen szám véletlenítése
	srand((unsigned)time(NULL));
	//tömb feltöltése és kiírása
	printf("A tömb táblázatos formában:\n");
	for (size_t i = 0; i < 10; i++)
	{
		tomb[i] = rand() % (B - A + 1) + A;
		printf("%d\t", tomb[i]);
	}
	printf("\n");
	//páros számos rész
	for (size_t i = 0; i < 10; i++)
	{
		if (tomb[i] % 2 == 0) {
			parosdb++;
			parososszeg += tomb[i];
		}
	}

	printf("A tömbben %d páros szám van, összege: %d\n", parosdb, parososszeg);
	//#####################################################################################################
	//plusz változók létrehozása
	int saveesp;

	const char* A_beker = "Kérem az A értékét: ";
	const char* B_beker = "Kérem az B értékét: ";
	const char* beker_format = "%d";
	const char* hun = "Hun";
	const char* tombfejlec = "A tömb táblázatos formában:\n";
	const char* tombelem = "%d\t";
	const char* ujsor = "\n";
	const char* eredmeny = "A tömbben %d páros szám van, összege: %d\n";

	//setlocale
	_asm
	{
		mov saveesp, esp;
		push hun;
		push 0;
		call setlocale;
		mov esp, saveesp;
	}
	
	//változók kinullázása
	_asm {
		mov A, 0;
		mov B, 0;
		mov parosdb, 0;
		mov parososszeg, 0;
	}

	//bekérés
	_asm {
		//a bekérõ kiírás
		mov saveesp, esp;
		push A_beker;
		call printf;
		//a beállítás
		lea eax, A;
		push eax;
		push beker_format;
		call scanf;
		//b bekérõ kiírás
		push B_beker;
		call printf;
		//b beállítás
		lea eax, B;
		push eax;
		push beker_format;
		call scanf;

		mov esp, saveesp;
	}

	//srand(time(0))
	_asm
	{
		mov saveesp, esp;
		push 0;
		call time; //eax-ben az eredmény
		push eax;
		call srand;
		mov esp, saveesp;
	}

	//tömb feltöltés és kiírás
	_asm {
		//bevezetõ printf
		mov saveesp, esp;
		push tombfejlec;
		call printf;
		mov esp, saveesp;
		//ciklus kezdet
		mov ecx, 10; //mivel 10 elemû a tömb, ha N elemû lenne, N lenne itt
		mov esi, 0; //tömbindex, amely megmondja, hány bájtra van a következõ tömbelem
	ciklus_feltolt:
		push ecx;
		//véletlen szám generálás
		call rand; //eredmény eax-ben, de az ebx, ecx, edx regiszer is módosul
		//rand()%(B-A+1)+A
		mov ebx, B;
		sub ebx, A;
		inc ebx; //B-A+1
		//osztás
		mov edx, 0; //div mûvelet: az eax-ben lévõ elemet osztja a div után lévõ értékkel. az edx-et és eax-et elõtte 0-ázni kell.
		div ebx; //eax/ebx
		//hozzáadás
		add edx, A;
		//tömbfeltöltés:
		mov tomb[esi], edx; //tomb[i] = rand()%(B-A+1)+A;
		//képernyõre kiírás
		mov saveesp, esp;
		push tomb[esi];
		push tombelem;
		call printf;
		mov esp, saveesp;
		//ciklus vége
		pop ecx; //kivesszük a ciklusváltozót
		add esi, 4; //következõ tömbelem 4 bájtra van
		loop ciklus_feltolt;
		//újsor kiírása
		mov saveesp, esp;
		push ujsor;
		call printf;
		mov esp, saveesp;
	}

	//vizsgálatos ciklus
	_asm {
		mov ecx, 10;
		mov esi, 0;
	ciklus_vizsgal:
		//páros szám vizsgálata:
		mov eax, tomb[esi];
		mov ebx, 2;
		mov edx, 0; 
		div ebx;	//eax/ebx  maradék az edx-ben van
		
		cmp edx, 0;
		je paros;
		jne tovabb;
	paros:
		inc parosdb;
		mov eax, tomb[esi];
		add parososszeg, eax;
	tovabb:
		add esi, 4;

		loop ciklus_vizsgal;
	}

	//eredmény kiírása
	_asm
	{
		mov saveesp, esp;
		push parososszeg;
		push parosdb;
		push eredmeny;
		call printf;
		mov esp, saveesp;
	}

	system("pause");
	return 0;
}
