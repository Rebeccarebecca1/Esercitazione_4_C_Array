#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp" 

using namespace std;

int main()
{
	string inputFile = "data.txt";		
	
	/* Variabile che conta il numero di asset nel portafoglio */
	size_t nAsset;	

	/* Capitale iniziale investito */
	double S;
	
	/* Puntatori a memoria dinamica per i vettori dei pesi e dei rendimenti degli asset */
	double* pesi = nullptr;
	double* rendimenti  = nullptr;
	
	/* Variabili che conterranno i risultati delle elaborazioni*/
	double tot_rate;		//Valore del rendimento totale
	double S_final;			//Valore finale del portafoglio 
	
	/*Chiamo la funzione che importa i dati da file e riempio le variabili*/
	ImportData(inputFile, nAsset, S, pesi, rendimenti);
	
	/* Calcolo il rendimento portafoglio come prodotto scalare tra il vettore dei pesi e quello dei rendimenti */
	tot_rate = DotProduct( nAsset, pesi, rendimenti);
	
	/*Applico la formula per il valore finale del portafoglio: V = S * ( 1 + r) */
	S_final = tot_value(tot_rate, S);
	
	/* Esporto i risultati su file e li stampo a termianle*/
	ExportResult("result.txt", nAsset, pesi, rendimenti, S, tot_rate, S_final);
	
	/* libero la memoria dinamica allocata per i vettori così evito il problema del memory leak */

	delete [] pesi;
	delete [] rendimenti;
    return 0;
}