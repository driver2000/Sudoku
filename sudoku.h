#ifndef Sudoku_H
#define Sudoku_H
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Sudoku
{
    vector<short> griglia; //Griglia dove vengono memorizzati i numeri del Sudoku
public:
    //Costruttore di default:inizializza la griglia del Sudoku con tutti zeri
    Sudoku(){griglia.insert(griglia.begin(),81,0);}

    /*Costruttore parametrizzato che inizializza la griglia con un Sudoku
      predefinito, caricato da file o inserito da tastiera*/
    Sudoku(vector<short>  &v){griglia.insert(griglia.begin(),v.begin(),v.end());}

    //Costruttore di copia usato per ripristinare una partita
    Sudoku(Sudoku *s){griglia.insert( griglia.begin(),s->griglia.begin(),s->griglia.end() );}
    bool checkRules(short,short,short);  //Verifica le regole del Sudoku
    void putZero();
    //Metodo che restituisce un numero n nella griglia alla posizione (i,j)
    short getNumber(short i,short j){return griglia[i*9+j];} 
    //Metodo che inserisce un numero n (di default 0) nella griglia alla posizione (i,j)
    void setNumber(short i,short j,short n=0){ griglia[i*9+j] = n;} 
    void viewSudoku(bool s=false);   
    Sudoku* resolveSudoku(Sudoku*); //Risolve il Sudoku con la tecnica del backtracking
    void sudokuRand();
    ~Sudoku(){};  //Distruttore
};

/*Metodo che fa il check delle varie regole del sudoku,se tutte
  sono rispettate ritorna il valore TRUE, altrimenti FALSE.
  Accetta come parametri il numero n che si vuole inserire nella 
  griglia e la sua relativa posizione  (indici i e j)*/
bool Sudoku::checkRules(short n,short i,short j)
{
    //Controlla se gli indici ed il numero rientrano nel range dei possibili valori	
    if (i<0||i>8 || j<0||j>8 || n<1||n>9)  
        return false;
    //Controlla se la posizione e' occupata da un'altro numero
    if (griglia[i*9+j]!=0)
        return false;
    for (short k=0;k<9;k++)
	//Controlla se nella stessa riga o la stessa colonna e' presente lo stesso numero
        if (griglia[i*9+k]==n || griglia[k*9+j]==n)  
            return false;
     //Controlla la sotto-griglia 3x3 per verificare se il numero e' gia' presente 
    for (short k=(i/3*3);k<(i/3*3)+3;k++)  
        for (short z=(j/3*3);z<(j/3*3)+3;z++)
            if (griglia[k*9+z]==n)
                return false;
    return true; //Il numero n puo' essere inserito
}

/*Metodo che visualizza a video la griglia del Sudoku.
  Se f e' TRUE visualizza la griglia, altrimenti solo
  la scritta "SUDOKU".*/
void Sudoku::viewSudoku(bool f)
{
    system("cls");
    char s[5][30]={{" SSS U  U DDD   OO  K  K U  U"},
        {"S    U  U D  D O  O K K  U  U"},
        {" SS  U  U D  D O  O KK   U  U"},
        {"   S U  U D  D O  O K K  U  U"},
        {"SSS   UU  DDD   OO  K  K  UU "}
    };
    cout<<endl;
    for (short i=0;i<5;i++)
    {
        cout<<"\t\t      "<<s[i]<<endl;
    }
    if(!f)
    {
        cout << "\n\t\t\t  1 2 3   4 5 6   7 8 9  "<<endl;
        cout << "\n\t\t\t-------------------------"<<endl;
        for (short i=0;i<9;i++)
        {
            cout << "\t\t     "<<i+1<<"  | ";
            for (short j=0;j<9;j++)
            {
		/*Sostituisce gli zero con uno spazio vuoto 
                  per una migliore visualizzazione*/
                if (griglia[i*9+j]==0)
                    cout <<"  ";     
                else
                    cout << griglia[i*9+j] << " ";
                if ((j+1)%3 == 0)
                    cout<<"| ";
            }
            cout<<endl;
            if ((i+1)%3==0&&i<8)
                cout << "\t\t\t|-----------------------|"<<endl;
            else
                if (i==8)
                    cout << "\t\t\t-------------------------"<<endl;
        }
    }
}

/*Metodo che permette la generazione di Sudoku random. Genera a caso dieci numeri
   che posiziona in (i,j) anch'essi random, controlla se tali numeri possono 
   essere inseriti richiamando il metodo checkRules, poi risolve il 
   Sudoku (resolveSudoku)  ed infine  elimina  alcuni numeri (putZero).  
   Generando a caso gli indici, anche se viene posizionato un solo numero,
   abbiamo 9*81 possibili Sudoku */
void Sudoku::sudokuRand()
{
    srand((unsigned int)time(0));
    for (short k=0;k<10;k++)
    {
	//Numeri ed indici vengono generati nel loro range per rispettare le regole
        short i=rand()%9,j=rand()%9,rnum=1+rand()%9;  
        if ( checkRules(rnum,i,j) )
            setNumber(i,j,rnum);
    }
    //Il puntatore this punta all'oggetto per il quale e' stata richiamata la funzione membro
    resolveSudoku(this); 
    putZero();
}

/*Metodo che rimpiazza casualmete con degli zero i numeri della griglia,
  generando vari livelli di difficolta' in modo casuale*/
void Sudoku::putZero()
{
    srand((unsigned int)time(0));	
    short rZero=50+rand()%10; //numero di zeri
    while (rZero>0)
    {
        short rind=rand()%81; //indice del valore da azzerare
        if (griglia[rind]!=0)
        {
            griglia[rind]=0;
            rZero--;
        }
    }
}

/*Metodo che realizza la soluzione del Sudoku con la tecnica del Backtracking.
  Analizza la griglia alla ricerca di uno zero, se lo trova significa che il 
  Sudoku non e' stato ancora risolto, quindi cerca un qualsiasi numero che 
  soddisfi i vincoli descritti in checkRules, inseguito fa una chiamata 
  ricorsiva per spostarsi in un altro ramo di decisione, se restituisce un 
  valore non NULL aggiungiunge un pezzo alla soluzione, altrimeti resetta il numero
  inserito e torna indietro (Backtrack). Il metodo continua cosi' fino a che non ci 
  sono piu' zeri quindi ha trovato la soluzione, se non trova una possibile soluzione
  restituisce un puntatore NULL. Come parametro accetta un puntatore ad un' istanza
  della classe Sudoku e restituisce la soluzione oppure NULL  */
Sudoku* Sudoku::resolveSudoku(Sudoku *s)
{
    vector<short>::iterator it;
    //Se esiste un solo elemento uguale a zero il Sudoku non e' risolto
    it=find(s->griglia.begin(),s->griglia.end(),0);  
    if (it !=s->griglia.end())
    {
	//In questi cicli ricaviamo gli indici (i,j) indispensabili per i controlli
        for (short i=0;i<9;i++)       
            for (short j=0;j<9;j++)
                if (s->griglia[i*9+j] == 0)
                {
		    //Ottenuti gli indici, proviamo l'inserimeto di un numero	
                    for (short k=1;k<=9;k++) 
                    {
                        if (s->checkRules(k,i,j))
                        {
                            setNumber(i,j,k);
                         /*Trovata la pseudo-soluzione, istanziamo l'oggetto app
                           per analizzare un altro possibile percoso*/
                            Sudoku *app=resolveSudoku(s);  
                            if (app!=NULL)
                                return app;  //Ritorna un altro pezzo della soluzione
                        }
			/*Viene resettata la modifica fatta inquanto 
                          la scelta portava ad una non-soluzione*/
                        setNumber(i,j); 
                    }
		    /*La strada intrapresa non porta ad una soluzione 
                      quindi si torna indietro (Backtrack)*/
                    return NULL; 
                }
	}
 return s; //Nel Sudoku non sono presenti zeri quindi e' stato risolto
}

#endif //Sudoku_H
