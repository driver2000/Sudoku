#include <iostream>
#include <fstream>
#include <string>
#include "sudoku.h"
//Contiene la function per l'animazione della progressbar
#include "progressbar.h"

using namespace std;

void print();
short menu();
void menu1(Sudoku **);
void inputSudoku(Sudoku **);
void insertNum(Sudoku **);
void delNum(Sudoku **);
void loadSudoku(vector<short> &, bool flag=false);
void saveSudoku(Sudoku **);

int main()
{
    vector<short> vec;
    //Creazione di un' istanza di Sudoku
    Sudoku *sudoku=NULL;
    short m;
    //Cambia il colore della console di Windows
    system("color F");
    print();
    do
    {
        m=menu();
        switch (m)
        {
        case 1: //l'opzione 1 carica dal file "sudoku.su" il Suduku predefinito
            loadSudoku(vec);
            try //Gestione delle eccezzioni per l'allocazione dinamica della memoria
            {
                sudoku=new Sudoku(vec);
            }
            catch (bad_alloc xa)
            {
                cout<<"Errore allocazione memoria!"<<endl;
                exit(1);
            }
            sudoku->viewSudoku();
            menu1(&sudoku);
            break;
        case 2: //l'opzione 2 fa generare un Suduku in modo random
            try
            {
                sudoku=new Sudoku();
            }
            catch (bad_alloc xa)
            {
                cout<<"Errore allocazione memoria!"<<endl;
                exit(1);
            }
            sudoku->sudokuRand();
            sudoku->viewSudoku();
            menu1(&sudoku);
            break;
        case 3: //l'opzione 3 permette di creare un Suduku
            try
            {
                sudoku=new Sudoku();
            }
            catch (bad_alloc xa)
            {
                cout<<"Errore allocazione memoria!"<<endl;
                exit(1);
            }
            inputSudoku(&sudoku);
            sudoku->viewSudoku();
            menu1(&sudoku);
            break;
        case 4: //l'opzione 4 permette di caricare un Suduku  da file
            loadSudoku(vec,true);
            try
            {
                sudoku=new Sudoku(vec);
            }
            catch (bad_alloc xa)
            {
                cout<<"Errore allocazione memoria!"<<endl;
                exit(1);
            }
            sudoku->viewSudoku();
            menu1(&sudoku);
            break;
        case 0: //l'opzione 0 termina il programma
            system("cls");
            cout<<"Grazie per aver giocato !!! ;-)"<<endl;
            Sleep(2000);
            delete sudoku;
        }
    }
    while (m>=1&&m<=4);
    return 0;
}

//Function che visualizza a video l'animazione d'apertura
void print()
{
    char s[7][37]={ {" SSSS U   U DDD    OOO  K    K U   U"},
                    {"S     U   U D  D  O   O K   K  U   U"},
                    {"S     U   U D   D O   O K  K   U   U"},
                    {" SSS  U   U D   D O   O KKK    U   U"},
                    {"    S U   U D   D O   O K  K   U   U"},
                    {"    S U   U D  D  O   O K   K  U   U"},
                    {"SSSS   UUU  DDD    OOO  K    K  UUU "}};
    cout<<endl;
    for(int i=0;i<7;i++)
        cout<<"\t\t"<<s[i]<<endl;
    Sleep(750);
    system("cls");
    for(int k=0;k<37;k++)
    {
        cout<<endl;
        for(int i=0;i<7;i++)
        {
            cout<<"\t\t";
            int x=0;
            while(x<k)
            {
                cout<<" ";
                x++;
            }
            for(int j=k;j<37;j++)
                cout<<s[i][j];
            cout<<endl;
        }
        system("cls");
    }

}
//Function che visualizza a video il menu' principale e restitusce la scelta fatta dall'utente
short menu()
{
    short scelta ;
    bool f; /*flag di controllo utlizzato per verificare
              la corretta digitazione delle opzioni*/
    do
    {
        f=false;
        Sudoku s;
        s.viewSudoku(true);
        cout<<"\n\n\n\t        * * * * * * * M * E * N * U * * * * * * *   "<<endl;
        cout<<"\t       *   1 - Gioca con Sudoku predefinito      *  "<<endl;
        cout<<"\t      *   2 - Gioca Sudoku generato casualmente   * "<<endl;
        cout<<"\t     *   3 - Gioca con un Sudoku creato da te      *"<<endl;
        cout<<"\t      *   4 - Carica Sudoku salvato               * "<<endl;
        cout<<"\t       *   0 - Alla prossima :-)                 *  "<<endl;
        cout<<"\t        * * * * * * * * * * * * * * * * * * * * *   "<<endl;
        cout<<"\t                     Scegli : ";
        cin>>scelta;
        if (scelta<0||scelta>4)
        {
            cout<<"Rivedi il menu', hai effettuato una scelta errata"<<endl;
            Sleep(2000);
            system("cls");
            f=true;
        }
    }while (f);
    return scelta;
}

/*Function che visualizza a video il menu' di gioco.
  Riceve e restituisce un'istanza della classe Sudoku*/
void menu1(Sudoku **s)
{
    //Salva lo stato del Sudoku,per poterlo resettare su richiesta dell'utente
    Sudoku *save=new Sudoku(*s);
    short scelta;
    bool f;
    do
    {
        do
        {
            f=false;
            cout<<"\t\t   **** P * A * R * T * I * T * A **** "<<endl;
            cout<<"\t\t  *   1 - Inserisci numero            *"<<endl;
            cout<<"\t\t  *   2 - Cancella numero             *"<<endl;
            cout<<"\t\t  *   3 - Riavvia Sudoku              *"<<endl;
            cout<<"\t\t  *   4 - Soluzione                   *"<<endl;
            cout<<"\t\t  *   5 - Salva Sudoku                *"<<endl;
            cout<<"\t\t  *   0 - ..torna al menu' principale *"<<endl;
            cout<<"\t\t   *********************************** "<<endl;
            cout<<"\t\t              Scegli : ";
            cin>>scelta;
            if (scelta<0||scelta>5)
            {
                cout<<"Rivedi il menu', hai effettuato una scelta errata"<<endl;
                f=true;
            }
        }while (f);
        switch (scelta)
        {
        case 1:  //l'opzione 1 permette l'inserimeto di un numero
            insertNum(s);
            break;
        case 2: //l'opzione 2 permette la cancellazione di un numero
            delNum(s);
            break;
        case 3: //l'opzione 3 permette di resettare il Sudoku
            delete *s; //Dealloca *s
            *s=new Sudoku(save); //Ripristina lo stato iniziale del Sudoku
            break;
        case 4: //l'opzione 4 permette di trovare una soluzione se esiste
            if ((*s)->resolveSudoku(*s)==NULL)
            {
                cout<<"\nSoluzione non trovata!"<<endl;
                system("pause");
            }
            break;
        case 5: //l'opzione 5 permette di salvare il Sudoku su un file scelto dall'utente
            saveSudoku(s);
            break;
        }
        system("cls");
        if (scelta!=0)
            (*s)->viewSudoku();
        else
            delete save;

    }while (scelta>=1&&scelta<=5);
}

/*Function che permette di inizializzare un Sudoku da tastiera.
  Riceve e restituisce un'istanza della classe Sudoku*/
void inputSudoku(Sudoku **s)
{
    short num;
    cout<<"Digita le righe del Sudoku(0 per le caselle vuote)"<<endl;
    for (short i=0;i<9;i++)
    {
        for (short j=0;j<9;j++)
        {
            cin>>num;
	    /*Controlla il renge di numeri (da 0 a 9)
              possibili da inserire,0 per una posizione vuota*/
            if ((num>=0)&&(num<10))
                (*s)->setNumber(i,j,num);
            else
            {
                cout<<"Attento, devi inserire un numero fra 0 e 9"<<endl;
                j--;
            }
        }
        cout<<"la  riga "<<i+1 <<" e' stata completata"<<endl;
    }

}

/*Function che permette di giocare inserendo i numeri nel Sudoku.
  Riceve e restituisce un'istanza della classe Sudoku*/
void insertNum(Sudoku **s)
{
    short num,i,j;
    bool f;
    do
    {
        cout<<"NUMERO : ";
        cin>> num;
        cout<<"RIGA : ";
        cin>>i;
        cout<<"COLONNA : ";
        cin>>j;
        f=false;
        if ((*s)->getNumber(i-1,j-1)!=0)
        {
            f=true;
            cout<<"Posizione occupata\n";
        }
    /*Controlla se gli indici ed il numero rientrano nel range
      dei possibili valori e se la posizione sia libera*/
    }while (num<1||num>9||i<1||i>9||j<1||j>9||f);
    (*s)->setNumber(i-1,j-1,num);
}

/*Function che permette di giocare rimuovendo un numero del Sudoku.
  Riceve e restituisce un'istanza della classe Sudoku*/
void delNum(Sudoku **s)
{
    short i,j;
    do
    {
        cout<<"RIGA : ";
        cin>>i;
        cout<<"COLONNA : ";
        cin>>j;
    //Controlla se gli indici rientrano nel range dei possibili valori
    }while (i<1||i>9||j<1||j>9);
    //Se non viene specificato il numero setNumber inserisce uno 0
    (*s)->setNumber(i-1,j-1);
}

/*Function che carica da file una partita salvata o il Sudoku predefinito
  salvato nel file "sudoku.su". Riceve come parametri il vettore che conterra'
  i numeri del Sudoku ed un flag di controllo, quest'ultimo e' di default
  FALSE e indica che si vuole caricare una partita salvata dall'utente,
  se viene impostato a TRUE viene caricato il file "sudoku.su" */
void loadSudoku(vector<short> &vec, bool flag)
{
    string name;
    vec.erase(vec.begin(),vec.end());//Elimina tutti gli elementi dal vettore
    if (flag) //Si vuole caricare una partita salvata dall'utente
    {
        cout<<"Nome della partita da caricare : ";
        cin>>name;
        name+=".su";//Concatena e assegna l' estensione
    }
    else  //Si vuole caricare il Sudoku predefinito
        name="sudoku.su";
    const char *p=name.c_str(); //Crea una stringa costante
    ifstream file(p);
    if (!file.is_open())
    {
        cout<<"Impossibile aprire il file"<<endl;
        system("pause");
        exit(1);
    }
    else
    {
	//Se non si vuole caricare "sudoku.su" visualizza l'animazione
        if (name!="sudoku.su")
        {
            cout<<endl;
            progressBar();
            cout<<"\n\n\t\t\tPartita Caricata!\a"<<endl;
            Sleep(2000);
            system("cls");
        }
        char c;
        while (!file.eof())
        {
            c=file.get();
            vec.push_back(short(c-48)); //Conversione da carattere ASCII a short
        }
    }
    file.close();
}

/*Function che permette il salvataggio di una partita su file.
  Riceve un'istanza della classe Sudoku*/
void saveSudoku(Sudoku **s)
{
    string name;
    cout<<"Inserisci il nome della partita da salvare"<<endl;
    cin>>name;
    name+=".su";  //Concatena e assegna l' estensione
    const char *p=name.c_str(); //Crea una stringa costante
    ofstream file;
    file.open(p,ios::trunc|ios::out);
    if (!file.is_open())
    {
        cout<<"Impossibile aprire il file"<<endl;
        system("pause");
        exit(1);
    }
    else
    {
        cout<<endl;
        progressBar();
        cout<<"\n\n\t\t\tPartita Salvata!\a"<<endl;
        Sleep(2000);
        system("cls");
        for (short i=0;i<9;i++)
            for (short j=0;j<9;j++)
                file.put(char((*s)->getNumber(i,j)+48));//Conversione da short a carattere ASCII
        file.close();
    }
}
