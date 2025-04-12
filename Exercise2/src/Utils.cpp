#include <iostream>
#include <fstream>
#include <sstream>
#include<iomanip>
#include<string>
#include "Utils.hpp"

using namespace std;

/* Funzione che legge da file i dati relativi a un portafoglio finanziario:
   - capitale iniziale S,
   - numero di asset n,
   - due vettori w e r(relativi ai pesi e ai rendimenti)
   I puntatori vengono passati per riferimento per poter essere modificati all'interno della funzione e poter vedere queste modifiche all'esterno della funzione
   Infatti non sto lavorando su una copia, ma direttamente sulla variabile originale.
   n e S invece sono scalari quindi vengono passati solo tramite riferimento*/

bool ImportData(const string& inputFilePath, size_t& n, double& S, double*& w, double*& r) 
{	
	ifstream file(inputFilePath);
	if(file.fail())						//Verifico che il file si possa leggere
	{
		cout<<"File not found"<<endl;
		return false;
	}
	
	/* Ignoro la parte testuale prima di ';' */
	
	std::string tmp; 
	getline( file, tmp,';');
	
	/* Memorizzo il valore del capitale iniziale(S) */
	
	file >> S;
	file.ignore();		//Ignoro il carattere di newline
	
	/* Procedura analoga per leggere il numero di asset */
	
	getline(file, tmp,';');
	file >> n;
	file.ignore();
	getline(file, tmp);		//Pulisco la riga successiva
	
	/* Allocazione dinamica dei vettori perchè non ne conosco la dimensione. 
	La dimensione può essere determinata durante l'esecuzione del programma e questo 
	mi permette di allocare esattamente la memoria necessaria in base al valore letto da file. */
	
	w = new double[n];
	r = new double[n];
	double posizione;
	for(unsigned int i = 0; i < n; i++)
	{
		getline(file, tmp);
		
		/* Trovo la posizione di ; nella riga */
		 
		posizione = tmp.find(';');
		
		/* Estrazione della sottostinga prima di ;*/
		// Estraggo da tmp i caratteri da 0 fino al carattere prima di posizione
		w[i] = stod(tmp.substr(0, posizione));
		
		/* Estrazione della sottostinga sotto di ;*/
		// Estraggo da carattere poszione + 1 fin oalla fine della stringa
		r[i] = stod(tmp.substr(posizione + 1));
	} 
	file.close();
    return true;
}

/* Calcolo il prodotto scalare tra i vettori w e r di dimensione n.*/

double DotProduct(const size_t& n, const double* const& w, const double* const& r)		
//I vettori sono passati per riferimento costante perchè non devono essere modificati
{
	double DotProduct = 0;
	for(unsigned int i = 0; i < n; i++)
    {
		DotProduct = DotProduct + (w[i] * r[i]);
    }
   return DotProduct;
}
 /* Valore totale del portafoglio: V = (1 + r_tot) * S */
 
double tot_value(const double &r_tot, const double &S)
{
	// r_tot è il valore che mi ritorna dalla funzione DotProduct
	return (1 + r_tot) * S;
}

/* Converte un array di double in una stringa formattata */
/* double* indica un puntatore a double, ovvero una variabile che può puntare a un array dinamico di numeri decimali. 
Quando aggiungiamo const davanti, come in const double*, stiamo dicendo che i valori puntati non possono essere modificati: 
si può cambiare dove punta il puntatore, ma non si possono cambiare i dati a cui punta.
Se scriviamo invece const double* const, stiamo aggiungendo un secondo const alla fine, e questo significa che anche il 
puntatore stesso non può cambiare, oltre ai dati: non si possono modificare né i valori contenuti nell’array, né far puntare il puntatore a un’altra zona di memoria.
Infine, quando usiamo const double* const&, stiamo passando per riferimento questo puntatore “bloccato”, evitando che venga fatta una copia. */

string ArrayToString(const size_t& n, const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}

/* Questa funzione scrive i risultati su file. */
/* Questa funzione scrive i risultatu su termianle. */

bool ExportResult(const string& outputFilePath, const size_t& n, const double* const& w, const double* const& r, const double& S, const double& rate, const double& V)		
//Tutti i parametri vengono passati per riferimento costante perchè non vengono modificati ovviamente
{
    ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr<< "File open failed"<< endl;
        return false;
    }
	
	/* Scrittura su file */
    file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	
	//Ripristino il formato predefinito prima di scrivere rate
	file.unsetf(ios::fixed);		//Disattivo la notazione decimale forzata
	file << setprecision(4);		//Imposto la precisione totale significativa
	
	// I vettori w e r vengono convertiti in stringhe tramite la funzione ArrayToString definita prima di questa 
    file << "w = " << ArrayToString(n,w) << endl;		
	file << "r = " << ArrayToString(n,r) <<endl;
    file << "Rate of return of the portfolio: " << rate << endl;
	file << "V: " << fixed << setprecision(2) << V << endl;  	
	
	/* Stampa sul terminale*/
	cout << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	
	//Ripristino anche sul cout
	cout.unsetf(ios::fixed);		
	cout << setprecision(4);		
	
    cout << "w = " << ArrayToString(n,w ) << endl;
	cout << "r = " << ArrayToString(n,r) << endl;
    cout << "Rate of return of the portfolio: " << rate << endl;
	// Devo stampare il valore finale con due cifre decimali
	cout << "V: " << fixed << setprecision(2) << V << endl;  		
    file.close();
    return true;
}
