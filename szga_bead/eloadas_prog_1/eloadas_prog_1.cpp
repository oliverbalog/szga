#include <iostream>
using namespace std;

int main()
{
	/* 
	*	M�sodfok� egyenlet megold�sa megold�k�plet alapj�n.
	*	K�rje be az a,b,c �rt�keket a felhaszn�l�t�l.
	*	Sz�m�tsa ki a diszkrimin�ns �rt�k�t �s oldja meg a megold�k�plet seg�ts�g�vel az egyenletet.
	*		a val�s sz�mok halmaz�n. 
	*	Ha D<0, akkor nincs megold�s a val�s sz�mok halmaz�n
	*	Ha D=0, akkor egy megold�sa van.
	*	Ha D>0, akkor 2 megold�s.
	*	�rja ki az eredm�nyeket a k�perny�re.
	*/
	double a, b, c, D, x1, x2;

	
	setlocale(LC_ALL, "Hun");
	
	//bek�r�s
	printf("K�rem az a �rt�k�t: "); scanf_s("%lf", &a);
	printf("K�rem az b �rt�k�t: "); scanf_s("%lf", &b);
	printf("K�rem az c �rt�k�t: "); scanf_s("%lf", &c);

	//diszkrimin�ns
	D = b * b - 4 * a * c;

	//fel�teles el�gaz�s �s ki�r�s
	if (D < 0) 
	{
		printf("Nincs val�s megold�s!\n");
		//return 0;
	}
	if(D==0) {
		x1 = -b / (2 * a);
		printf("Az egyenletnek egy megold�sa van: %lf\n", x1);
		//return 0;
	}
	if (D > 0) {
		x1 = (-b + sqrt(D)) / (2 * a);
		x2 = (-b - sqrt(D)) / (2 * a);
		printf("Az egyenletnek k�t megold�sa van: %lf �s %lf\n", x1, x2);;
		//return 0;
	}

	//########################################################################################
	//v�ltoz�k l�trehoz�sa
	int saveesp; //hagyom�nyos veremhez tartoz� veremmutat�t mentj�k vele

	const char* a_beker = "K�rem az a �rt�k�t : ";
	const char* b_beker = "K�rem az b �rt�k�t : ";
	const char* c_beker = "K�rem az c �rt�k�t : ";

	const char* beker_f = "%lf"; //scanf-hez
	
	const char* NMO = "Nincs val�s megold�s!\n";
	const char* _1MO = "Az egyenletnek egy megold�sa van: %lf\n";
	const char* _2MO = "Az egyenletnek k�t megold�sa van: %lf �s %lf\n";

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

	//a bek�r�se
	_asm
	{
		//bevezet� printf
		mov saveesp, esp;
		push a_beker;
		call printf;
		//scanf
		lea eax, a; //a v�ltoz� mem�riac�me a regiszterbe ker�l.  Az eax egy tetsz�leges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//b bek�r�se
	_asm
	{
		//bevezet� printf
		mov saveesp, esp;
		push b_beker;
		call printf;
		//scanf
		lea eax, b; //b v�ltoz� mem�riac�me a regiszterbe ker�l.  Az eax egy tetsz�leges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//c bek�r�se
	_asm
	{
		//bevezet� printf
		mov saveesp, esp;
		push c_beker;
		call printf;
		//scanf
		lea eax, c; //c v�ltoz� mem�riac�me a regiszterbe ker�l.  Az eax egy tetsz�leges 32 bites regiszter
		push eax;
		push beker_f;
		call scanf;
		mov esp, saveesp;
	}

	//printf("%lf, %lf, %lf\n", a, b, c);

	//Diszkrimin�ns
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

	//felt�telvizsg�lat
	_asm 
	{
		fldz; //+0.0  --a verem tetej�re rakja a 0-t
		fld D; //st(0) = D, st(1) = 0
		fcomi st(0), st(1);
		jz egymegoldas;
		jc nincsmegoldas;
		jnc ketmegoldas;
	}

	//nincs megold�s
	_asm
	{
	nincsmegoldas:
		mov saveesp, esp;
		push NMO;
		call printf;
		mov esp, saveesp;
		jmp kilep;
	}

	//egy megold�s
	_asm
	{
	egymegoldas:
		//x1=-b/2a
		fldz;
		fsub b; //-b
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti �rt�ket osztom a verem tetej�n l�v�vel?
		fstp x1;
		//k�perny�re �r�s
		mov saveesp, esp;
		fld x1;
		sub esp, 8; //8 b�jtnyi helyet foglalok le
		fstp qword ptr[esp];
		push _1MO;
		call printf;
		mov esp, saveesp;
		jmp kilep;
	}

	//k�tmegold�s
	_asm
	{
		ketmegoldas:
		//x1 kisz�m�t�sa: -b + sqrt
		fldz;
		fsub b; //-b
		fld D;
		fsqrt;
		faddp st(1), st(0); //-b + sqrt(D)
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti �rt�ket osztom a verem tetej�n l�v�vel?
		fstp x1;

		//x2 kisz�m�t�sa: -b + sqrt
		fldz;
		fsub b; //-b
		fld D;
		fsqrt;
		fsubp st(1), st(0); //-b + sqrt(D)
		fld a;
		fadd a; //2*a
		fdivp st(1), st(0); //a verem legteteje alatti �rt�ket osztom a verem tetej�n l�v�vel?
		fstp x2;

		//k�perny�re �r�s
		mov saveesp, esp;
		fld x2;
		sub esp, 8; //8 b�jtnyi helyet foglalok le
		fstp qword ptr[esp];
		fld x1;
		sub esp, 8; //8 b�jtnyi helyet foglalok le
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
