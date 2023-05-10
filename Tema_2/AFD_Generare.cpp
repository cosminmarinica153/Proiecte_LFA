#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

ifstream in("AFD.txt");
int nrQ, nrE, nrF;  // nrQ este numarul starilor / nrE este numarul literelor din alfabet / nrF este numarul starilor finale
int Q[100], F[100]; // Q este multimea starilor / F este multimea starilor Finale
char E[10];         // E este alfabetul
int Delta[100][10]; // Delta este functia limbajului
bool cond;          // cond va verifica daca cuvantul este corect sau nu

void citireAutomat()
{
    in >> nrQ;                    // citim numarul de stari din automat
    in >> nrE;                    // citim numarul de litere din alfabet
    in >> nrF;                    // citim numarul de stari finale
    for (int i = 0; i < nrE; i++) // citim alfabetul
        in >> E[i];               //
    for (int i = 0; i < nrF; i++) // citim starile finale
        in >> F[i];               //
    for (int i = 0; i < nrQ; i++) // adaugam starile intr-un array
        Q[i] = i;                 //
    for (int i = 0; i < nrQ; i++) // citim functia limbajului si construim tabelul
        for (int j = 0; j < nrE; j++)
            in >> Delta[i][j];
}

void verificareCuvant(string cuvant)
{
    int l = cuvant.length(); // lungimea cuvantului
    int q = 0;               // reprezinta starea in care ne aflam
    int e;                   // index-ul alfabetului
    int p = 0;               // indexul array-ului de parcurgere
    cond = true;
    for (int k = 0; k < l; k++) // parcurgem cuvantul
    {
        for (e = 0; e < nrE; e++) // verificam daca litera cuvantului se regaseste in alfabet
        {
            if (cuvant[k] == E[e])
            {
                cond = true;
                break;
            }
            else
                cond = false;
        }
        if (cond == false)
            break;
        if (Delta[q][e] == -1)
        {
            cond = false;
            break;
        }
        q = Delta[q][e]; // mutam starea in functie de proprietatea din tabel
    }
    if (cond == true)
        for (int i = 0; i < nrF; i++) // verificam daca starea retinuta in q se regaseste in multimea starilor finale
        {
            if (q == F[i])
            {
                cond = true;
                break;
            }
            else
                cond = false;
        }
    if (cond == true)
    {
        cout << cuvant << endl;
    }
    else
        return;
}

void generare(int lungime, int stareCurenta, string cuvant)
{
    if (lungime == 0)
    {
        verificareCuvant(cuvant);
        return;
    }
    for (int i = 0; i < nrE; i++)
    {
        int stareUrmatoare = Delta[stareCurenta][i];
        string cuvantNou = cuvant + E[i];
        generare(lungime - 1, stareUrmatoare, cuvantNou);
    }
}

int main()
{
    citireAutomat();
    // afisarea tabelului functie
    cout << endl;
    cout << "   | ";
    for (int j = 0; j < nrE; j++)
        cout << E[j] << " | ";
    cout << endl;
    for (int i = 0; i < nrQ; i++)
    {
        cout << 'q' << Q[i] << " | ";
        for (int j = 0; j < nrE; j++)
            cout << Delta[i][j] << " | ";
        cout << endl;
    }
    int lungime;
    cout << "\nIntroduceti lungimea cuvintelor pe care vreti sa le afisati: ";
    cin >> lungime;
    generare(lungime, 0, "");

    in.close();
    return 0;
}