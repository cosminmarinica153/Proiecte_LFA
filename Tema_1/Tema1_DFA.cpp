#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

ifstream in("input.txt");
int nrQ, nrE, nrF;  // nrQ este numarul starilor / nrE este numarul literelor din alfabet / nrF este numarul starilor finale
int Q[100], F[100]; // Q este multimea starilor / F este multimea starilor Finale
char E[10];         // E este alfabetul
int Delta[100][10]; // Delta este functia limbajului
bool cond;          // cond va verifica daca cuvantul este corect sau nu
string Parcurgere[200];

void citireAutomat()
{
    in >> nrQ;                    // citim numarul de stari din automat
    in >> nrE;                    // citim numarul de litere din alfabet
    in >> nrF;                    // citim numarul de stari finale
    for (int i = 0; i < nrE; i++) // citim alfabetul
        in >> E[i];               //
    for (int i = 0; i < nrF; i++) // citim starile finale
    {                             //
        in >> F[i];               //
    }                             //
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
    if (cuvant == "vid")
    {
        cout << "Cuvant vid";
        return;
    }
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
        Parcurgere[p] = to_string(q);
        p++;
        Parcurgere[p] = E[e];
        p++;
        if (Delta[q][e] == -1)
        {
            cond = false;
            break;
        }
        q = Delta[q][e]; // mutam starea in functie de proprietatea din tabel
    }
    Parcurgere[p] = to_string(q);
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
        cout << "Cuvantul este corect!" << endl;
        int i;
        for (i = 0; i < p; i++)
        {
            if (i % 2 == 0)
                cout << 'q';
            cout << Parcurgere[i] << " -> ";
        }
        cout << 'q' << Parcurgere[i];
    }
    else
        cout << "Cuvantul nu este corect!";
}

int main()
{
    string cuvant;
    citireAutomat();
    cout << "Introduceti cuvantul pe care doriti sa il verificati" << endl;
    cin >> cuvant;
    verificareCuvant(cuvant);

    // cout << endl; // afisarea tabelului functie pentru testare
    // cout << "  ";
    // for (int j = 0; j < nrE; j++)
    //     cout << E[j] << ' ';
    // cout << endl;
    // for (int i = 0; i < nrQ; i++)
    // {
    //     cout << Q[i] << ' ';
    //     for (int j = 0; j < nrE; j++)
    //         cout << Delta[i][j] << ' ';
    //     cout << endl;
    // }

    in.close();
    return 0;
}