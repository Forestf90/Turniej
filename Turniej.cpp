#include <iostream>
#include <windows.h>
#include <string>
#include <math.h>
#include <fstream>
#include <conio.h>

#include <algorithm>0
#include <functional>

using namespace std;

//https://github.com/nlohmann/json/blob/develop/src/json.hpp

class zawodnik
{
	public:
string imie;
//bool pusty=true;
bool zwyciezca=false;
bool przegrany=false;
bool zaznaczenie=false;
int punkty=0;	
int numer=0;
int rzad=0;
zawodnik *galaz_gora=NULL;
zawodnik *galaz_dol=NULL;
zawodnik *potomek=NULL;


void wypisz()
{
	if(imie=="") cout<<"####";
	int x=15;
	if(zwyciezca) x=10;
	else if(przegrany) x=12;
	else if(numer==14) x=14;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	
	if(zaznaczenie) SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY  | x );
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	
 if(!zwyciezca)cout<<imie<<" :"<<punkty;
 else cout<<imie;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

};

void gotoxy(int x, int y)
{
  COORD c;
  c.X=x-1;
  c.Y=y-1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


class drzewo
{

public:
zawodnik * tabela = new zawodnik[15];	

	
	
	
	void wypisz_drzewo()
	{
		double x=1;
		double y=1;
		double zmiana=0;
		double kiedy=8;
		double potega=2;
		double poczatek=2;
		zawodnik *uczestnik;
		double temp_y;
		bool co_dwa=true;
		
//		freopen ("drzewo.txt","w",stdout);
 		for(int i=0; i<15 ;i++)
 		{
 		temp_y=y;	
 		uczestnik=&tabela[i];
 		gotoxy(x,y);
		tabela[i].wypisz();
//		cout<<endl;
		y +=pow(2,potega);
		zmiana+=1;



		if(zmiana!=kiedy && co_dwa)
		{
			int srednia =(temp_y+y)/2;
			for(int i=temp_y+1; i<y ;i++)
			{
				gotoxy(x,i);
				cout<<"|";
				if(i==srednia)
				{
					for(int j=x+1; j<x+15 ;j++)
					{
						gotoxy(j,i);
						cout<<"-";
					}
					
				}
			
		//	cout<<endl;
			}	
			co_dwa=false;	
		}
		else co_dwa=true;
		
		
		
		 if(zmiana==kiedy)
		 {

		
		 	kiedy=kiedy/2;
		 	zmiana=0;
		 	x+=15;
			potega+=1;
			y=pow(2,poczatek) -1;
			poczatek++;
		 }

		}
//	fclose (stdout);
	}
/*	
	void zapisz_drzewo(zawodnik * zwyciezca)
	{
		zawodnik *drugi;
		
		if(zwyciezca->galaz_gora->przegrany) drugi = zwyciezca->galaz_gora;
		else drugi= zwyciezca->galaz_dol;
		
		
		freopen ("drzewo.txt","a+b",stdout);
		
			cout<<"Zwyciezca turnieju zosta³ : ";zwyciezca->wypisz();
			cout<<endl<<"Drugie miejsce zaja³ : ";drugi->wypisz();
			cout<<endl<<"Pozostale miejsca to jakies randomy";
		
		
		
		fclose (stdout);
		system("exit");
		
	}
	*/
	void wczytaj()
	{

		fstream plik;
		plik.open( "zawodnicy.txt", ios::in | ios::out );
		string line;  
		int i=0;  
		while(plik.good())
		{
		    getline(plik, line);
			tabela[i].imie=line;
			tabela[i].numer=i;
			tabela[i].rzad=1;
		    i++;
		}

	}
	
	void punkty(zawodnik * przegrany)
	{
		
	
		
		zawodnik *przegryw = new zawodnik;
		
		przegryw=przegrany;
		int punkciki;
		while(true)
		{
	//	cout<<przegryw->imie;
		gotoxy(30,1);
		cout<<"Ile rund (0,1) wygral "<<przegryw->imie<<" :";
		
		punkciki=getche();
		gotoxy(30,1);
		cout<<"                                          ";
		if(punkciki==48 || punkciki==49) break;
		}
		przegryw->punkty=punkciki-48+przegryw->punkty;
	}
	
	
	void dodaj(zawodnik * wygrany)
	{
		
		int numer=wygrany->numer;
		int pozycja=8- (numer/2);
		
		zawodnik * wygryw=new zawodnik;
	//	wygrany->potomek=wygryw;
			wygryw->imie=wygrany->imie;
			wygryw->rzad=wygrany->rzad+1;

			if(numer%2==0) 
			{
				wygryw->galaz_gora=wygrany;
				wygryw->galaz_dol=wygrany+1;
				wygryw->punkty=wygrany->punkty+2;
				wygryw->numer=numer+pozycja;
				(tabela[numer+pozycja])=*wygryw;
				wygrany->potomek=&tabela[numer+pozycja];
				(wygrany+1)->potomek=&tabela[numer+pozycja];
				
				
			}
			else
			{
				wygryw->galaz_dol=wygrany;
				wygryw->galaz_gora=wygrany-1;
				
				wygryw->punkty=wygrany->punkty+2;
				
				wygryw->numer=numer+pozycja-1;
				tabela[numer+pozycja-1]=*wygryw;
				wygrany->potomek=&tabela[numer+pozycja-1];
				(wygrany-1)->potomek=&tabela[numer+pozycja-1];	
			}
			
	//	delete wygryw;
	}
};




void ranking(drzewo turniej)
{
zawodnik wynik[8];
int j=0;





for(int i=0 ; i<=14 ; i++)	
	{
		gotoxy(50,j+1);
	//	cout<<"tutaj";
		if(turniej.tabela[i].przegrany==true || turniej.tabela[i].numer==14)
		{
		//	cout<<turniej->tabela[i].imie;
			wynik[j].punkty =turniej.tabela[i].punkty;
		//	cout<<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		//	wynik[j]=j;
			wynik[j].imie=turniej.tabela[i].imie ;
	//		cout<<j<<".";
	//		wynik[j].wypisz();
		//	cout<<"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
			j++;
		}
	//	cout<<"czy tam";
	}
	
j=0;
int x,k;


//freopen ("drzewo.txt","w",stdout);
	
 fstream plik( "drzewo.txt", ios::out );
   if( plik.good() )
{
	
		

int p=1;
int miejsce=1;


for(int g=7 ; g>0 ; g--)
{
	gotoxy(50,p);
	if(g==7 || wynik[g].punkty<wynik[g+1].punkty)
	{
		plik <<miejsce<<". ";
		miejsce++;
		
	}
	else plik<<"   ";
	plik <<wynik[g].imie <<": " <<wynik[g].punkty<< endl;
	p++;
}

plik.close();

}

//fclose (stdout);

/*
	std::fstream score;
	score.open("scores.txt", ios::out | ios::app);
	if (score.good() == true)
	{
		std::string napis;
		getline(std::cin, napis);
		score << napis << "\t" << global_scorer << "\t" << "Points" << endl;
		score.close();
	}
	else
	{
		SetConsoleTextAttribute(hOut, 14);
		printf("\n\n\n\t\t\t\t\t The file is missing :( \n");
	}
	*/
	
	
}



int main()
{
ShowConsoleCursor(false);
 
 drzewo turniej;

turniej.wczytaj();


zawodnik *zaznaczony=&turniej.tabela[0];
//zaznaczony=turniej.tabela[0];
int pozycja;
int ster;

do	
{
	system("CLS");
	zaznaczony->zaznaczenie=true;
	turniej.wypisz_drzewo();

if(zaznaczony->numer==14) 
{
	gotoxy(50,1);
cout<<"Aby zapisac ranking "<<endl;
gotoxy(50,2);
cout<<"do pliku wcisnij ENTER";
}
	ster= getch();

	switch(ster)
	{
	case 72:
		if(zaznaczony->rzad==(zaznaczony-1)->rzad)
		{
			zaznaczony->zaznaczenie=false;
			if((zaznaczony-1) !=0)zaznaczony=zaznaczony-1;
		}
		break;

	case 80:
		if(zaznaczony->rzad==(zaznaczony+1)->rzad)
		{
			zaznaczony->zaznaczenie=false;
			if((zaznaczony+1) !=0)zaznaczony=zaznaczony+1;
		}
		break;

	case 75:
		if(zaznaczony->galaz_gora!=0)
		{
			zaznaczony->zaznaczenie=false;
			zaznaczony=zaznaczony->galaz_gora;	
		}
		break;

	case 77:
		if(zaznaczony->potomek!=NULL)
		{
			zaznaczony->zaznaczenie=false;
			zaznaczony=zaznaczony->potomek;
		}
		break;
	
	
	case 13:
			if(zaznaczony->numer==14) ranking(turniej);
		
		if(zaznaczony->numer%2==0 && (zaznaczony+1)->zwyciezca==false && (zaznaczony+1)->numer==zaznaczony->numer+1)
		 {
		 	zawodnik * przegrany =zaznaczony+1;
		 	(zaznaczony+1)->przegrany=true;
		 	zaznaczony->zwyciezca=true;
		 	turniej.dodaj(zaznaczony);
		 	turniej.punkty(przegrany);
		 }
		else if(zaznaczony->numer%2==1 && (zaznaczony-1)->zwyciezca==false && (zaznaczony-1)->numer==zaznaczony->numer-1) 
		{
			zawodnik * przegrany =zaznaczony-1;
			(zaznaczony-1)->przegrany=true;
			zaznaczony->zwyciezca=true;
			turniej.dodaj(zaznaczony);
			turniej.punkty(przegrany);
		//	zaznaczony->potomek->wypisz();
		}
//	if(zaznaczony->numer==14) turniej.zapisz_drzewo(zaznaczony);

		break;
	
	}
	

//	gotoxy(40,1);
//	if(zaznaczony->potomek!=0)zaznaczony->potomek->wypisz();
//	cout<<endl<<zaznaczony->numer<<zaznaczony->rzad;
}while(ster!=27);
	

    return 0;
}
