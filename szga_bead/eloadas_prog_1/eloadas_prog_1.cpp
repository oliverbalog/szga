#include <iostream>
using namespace std;

int main()
{
	/* 
	*	Másodfokú egyenlet megoldása megoldóképlet alapján.
	*	Kérje be az a,b,c értékeket a felhasználótól.
	*	Számítsa ki a diszkrimináns értékét és oldja meg a megoldóképlet segítségével az egyenletet.
	*		a valós számok halmazán. 
	*	Ha D<0, akkor nincs megoldás a valós számok halmazán
	*	Ha D=0, akkor egy megoldása van.
	*	Ha D>0, akkor 2 megoldás.
	*	Írja ki az eredményeket a képernyõre.
	*/
	double a, b, c, D, x1, x2;

	
	setlocale(LC_ALL, "Hun");
	
	//bekérés
	printf("Kérem az a értékét: "); scanf_s("%lf", &a);
	printf("Kérem az b értékét: "); scanf_s("%lf", &b);
	printf("Kérem az c értékét: "); scanf_s("%lf", &c);

	//diszkrimináns
	D = b * b - 4 * a * c;

	//felételes elágazás és kiírás
	if (D < 0) 
	{
		printf("Nincs valós megoldás!\n");
		//return 0;
	}
	if(D==0) {
		x1 = -b / (2 * a);
		printf("Az egyenletnek egy megoldása van: %lf\n", x1);
		//return 0;
	}
	if (D > 0) {
		x1 = (-b + sqrt(D)) / (2 * a);
		x2 = (-b - sqrt(D)) / (2 * a);
		printf("Az egyenletnek két megoldása van: %lf és %lf\n", x1, x2);;
		//return 0;
	}

	//########################################################################################
	//változók létrehozása
	int saveesp; //hagyományos veremhez tartozó veremmutatót mentjük vele

	const char* a_beker = "Kérem az a értékét : ";
	const char* b_beker = "Kérem az b értékét : ";
	const char* c_beker = "Kérem az c értékét : ";

	const char* beker_f = "%lf"; //scanf-hez
	
	const char* NMO = "Nincs valós megoldás!\n";
	const char* _1MO = "Az egyenletnek egy megoldása van: %lf\n";
	const char* _2MO = "Az egyenletnek két megoldása van: %lf és %lf\n";

	const char* hun = "Hun"; //setlocalehoz

	const char* _pause = "pause"; //system("pause")-hoz

	//##############################################################################################

	//setlocale(LC_ALL, "Hun");

	_asm 
	{
		mov saveesp, esp; //saveesp = esp;
		push hun;
		push LC_ALL; //0
		call dword ptr setlocale;
		mov esp, saveesp;
	}

	//a bekérése
	_asm
	{
		//bevezetõ printf
		mov saveesp, esp;
		push a_beker;
		call printf;
		//scanf
		lea eax, a; //a változó memóriacíme a regiszterbe kerül.  Az eax egy tetszõleges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//b bekérése
	_asm
	{
		//bevezetõ printf
		mov saveesp, esp;
		push b_beker;
		call printf;
		//scanf
		lea eax, b; //b változó memóriacíme a regiszterbe kerül.  Az eax egy tetszõleges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//c bekérése
	_asm
	{
		//bevezetõ printf
		mov saveesp, esp;
		push c_beker;
		call printf;
		//scanf
		lea eax, c; //c változó memóriacíme a regiszterbe kerül.  Az eax egy tetszõleges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//printf("%lf, %lf, %lf\n", a, b, c);

	//Diszkrimináns
	int negy = 4;
	_asm {
		//b*b-4*a*c
		fld b;
		fmul b;
		fild negy;
		fmul a;
		fmul c;
		fsubp st(1), st(0); //b*b-4*a*c
		fstp D;
	}

	//feltételvizsgálat
	_asm 
	{
		fldz; //+0.0  --a verem tetejére rakja a 0-t
		fld D; //st(0) = D, st(1) = 0
		fcomi st(0), st(1);
		jz egymegoldas;
		jc nincsmegoldas;
		jnc ketmegoldas;
	}

	//nincs megoldás
	_asm
	{
	nincsmegoldas:
		mov saveesp, esp;
		push NMO;
		call printf;
		mov esp, saveesp;
		jmp kilep;
	}

	//egy megoldás
	_asm
	{
	egymegoldas:
		//x1=-b/2a
		fldz;
		fsub b; //-b
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti értéket osztom a verem tetején lévõvel?
		fstp x1;
		//képernyõre írás
		mov saveesp, esp;
		fld x1;
		sub esp, 8; //8 bájtnyi helyet foglalok le
		fstp qword ptr[esp];
		push _1MO;
		call printf;
		mov esp, saveesp;
		jmp kilep;
	}

	//kétmegoldás
	_asm
	{
		ketmegoldas:
		//x1 kiszámítása: -b + sqrt
		fldz;
		fsub b; //-b
		fld D;
		fsqrt;
		faddp st(1), st(0); //-b + sqrt(D)
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti értéket osztom a verem tetején lévõvel?
		fstp x1;

		//x2 kiszámítása: -b + sqrt
		fldz;
		fsub b; //-b
		fld D;
		fsqrt;
		fsubp st(1), st(0); //-b + sqrt(D)
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti értéket osztom a verem tetején lévõvel?
		fstp x2;

		//képernyõre írás
		mov saveesp, esp;
		fld x2;
		sub esp, 8; //8 bájtnyi helyet foglalok le
		fstp qword ptr[esp];
		fld x1;
		sub esp, 8; //8 bájtnyi helyet foglalok le
		fstp qword ptr[esp];
		push _2MO;
		call printf;
		mov esp, saveesp;
		jmp kilep;
	}

	_asm 
	{
		kilep:
	}

	system("pause");
}
