#include <iostream>
#include <ctime>
using namespace std;

int main() 
{
	/*
		K�sz�tsen egy 10 elem�, eg�sz t�pus� t�mb�t.
		K�rjen be billenty�zetr�l k�t sz�mot, (A,B, ahol A<B), majd t�ltse fel A �s B k�z�tti 
			v�letlen sz�mokkal a t�mb�t.
		Ezut�n hat�rozza meg, h�ny darab p�ros sz�m tal�lhat� a t�mbben, �s adja meg a p�ros sz�mok �sszeg�t!
		A t�bl�zatot, az eredm�nyeket �rjuk ki a k�perny�re.
	*/
	int A=0, B=0, tomb[10], parosdb=0, parososszeg = 0;
	setlocale(0, "Hun");
	printf("K�rem az A �rt�k�t: "); scanf_s("%d", &A);
	printf("K�rem az B �rt�k�t: "); scanf_s("%d", &B);
	//v�letlen sz�m v�letlen�t�se
	srand((unsigned)time(NULL));
	//t�mb felt�lt�se �s ki�r�sa
	printf("A t�mb t�bl�zatos form�ban:\n");
	for (size_t i = 0; i < 10; i++)
	{
		tomb[i] = rand() % (B - A + 1) + A;
		printf("%d\t", tomb[i]);
	}
	printf("\n");
	//p�ros sz�mos r�sz
	for (size_t i = 0; i < 10; i++)
	{
		if (tomb[i] % 2 == 0) {
			parosdb++;
			parososszeg += tomb[i];
		}
	}

	printf("A t�mbben %d p�ros sz�m van, �sszege: %d\n", parosdb, parososszeg);
	//#####################################################################################################
	//plusz v�ltoz�k l�trehoz�sa
	int saveesp;

	const char* A_beker = "K�rem az A �rt�k�t: ";
	const char* B_beker = "K�rem az B �rt�k�t: ";
	const char* beker_format = "%d";
	const char* hun = "Hun";
	const char* tombfejlec = "A t�mb t�bl�zatos form�ban:\n";
	const char* tombelem = "%d\t";
	const char* ujsor = "\n";
	const char* eredmeny = "A t�mbben %d p�ros sz�m van, �sszege: %d\n";

	//setlocale
	_asm
	{
		mov saveesp, esp;
		push hun;
		push 0;
		call setlocale;
		mov esp, saveesp;
	}
	
	//v�ltoz�k kinull�z�sa
	_asm {
		mov A, 0;
		mov B, 0;
		mov parosdb, 0;
		mov parososszeg, 0;
	}

	//bek�r�s
	_asm {
		//a bek�r� ki�r�s
		mov saveesp, esp;
		push A_beker;
		call printf;
		//a be�ll�t�s
		lea eax, A;
		push eax;
		push beker_format;
		call scanf;
		//b bek�r� ki�r�s
		push B_beker;
		call printf;
		//b be�ll�t�s
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
		call time; //eax-ben az eredm�ny
		push eax;
		call srand;
		mov esp, saveesp;
	}

	//t�mb felt�lt�s �s ki�r�s
	_asm {
		//bevezet� printf
		mov saveesp, esp;
		push tombfejlec;
		call printf;
		mov esp, saveesp;
		//ciklus kezdet
		mov ecx, 10; //mivel 10 elem� a t�mb, ha N elem� lenne, N lenne itt
		mov esi, 0; //t�mbindex, amely megmondja, h�ny b�jtra van a k�vetkez� t�mbelem
	ciklus_feltolt:
		push ecx;
		//v�letlen sz�m gener�l�s
		call rand; //eredm�ny eax-ben, de az ebx, ecx, edx regiszer is m�dosul
		//rand()%(B-A+1)+A
		mov ebx, B;
		sub ebx, A;
		inc ebx; //B-A+1
		//oszt�s
		mov edx, 0; //div m�velet: az eax-ben l�v� elemet osztja a div ut�n l�v� �rt�kkel. az edx-et �s eax-et el�tte 0-�zni kell.
		div ebx; //eax/ebx
		//hozz�ad�s
		add edx, A;
		//t�mbfelt�lt�s:
		mov tomb[esi], edx; //tomb[i] = rand()%(B-A+1)+A;
		//k�perny�re ki�r�s
		mov saveesp, esp;
		push tomb[esi];
		push tombelem;
		call printf;
		mov esp, saveesp;
		//ciklus v�ge
		pop ecx; //kivessz�k a ciklusv�ltoz�t
		add esi, 4; //k�vetkez� t�mbelem 4 b�jtra van
		loop ciklus_feltolt;
		//�jsor ki�r�sa
		mov saveesp, esp;
		push ujsor;
		call printf;
		mov esp, saveesp;
	}

	//vizsg�latos ciklus
	_asm {
		mov ecx, 10;
		mov esi, 0;
	ciklus_vizsgal:
		//p�ros sz�m vizsg�lata:
		mov eax, tomb[esi];
		mov ebx, 2;
		mov edx, 0; 
		div ebx;	//eax/ebx  marad�k az edx-ben van
		
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

	//eredm�ny ki�r�sa
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
