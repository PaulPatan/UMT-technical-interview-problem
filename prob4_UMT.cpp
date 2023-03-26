#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int minimum_password_changes(string s) {
    int length = s.length();
    int nr = 0;
    bool has_lower = false, has_upper = false, has_digit = false, has_repeating = false;
    //parcurgem sirul cu un for loop

    for (int i = 0; i < length; ) {
            //daca caracterul curent e o litera mica, mare sau o cifra atunci
            //setam variabilele de mai jos cu 1 pentru a putea incrementa sau nu counter-ul
            //de schimbari necesare pentru a obtine o parola puternica
        if (s[i] >= 'a' && s[i] <= 'z')
            has_lower = true;
        else if (s[i] >= 'A' && s[i] <= 'Z')
            has_upper = true;
        else if (s[i] >= '0' && s[i] <= '9')
            has_digit = true;

        //cu un while loop, verificam daca literele de DUPA cea curenta sunt egale cu aceasta
        //astfel ca While-ul se opreste atunci cand o litera din sir NU mai este egala cu cea
        //de pe pozitia curenta(i)
        //lungimea subsecventei de caractere egale este egale cu length

        int j = i;
        while (j < length && s[j] == s[i])
            j++;

        //daca subsecventa de caractere egale are o dimensiune de cel putin 3
        //incrementam de asemenea counter-ul. daca NU am face lung/3 counter-ul s-ar incrementa de 3 ori mai mult(de lungimea subsecventei ori) decat ar fi nevoie

        int len = j - i;
        if (len >= 3) {
            has_repeating = true;
            nr += len / 3;
        }

        i = j;
    }

    //Daca nu avem NICIO litera mica, sau NICIUNA mare, sau NICIO cifra, incrementam counter-ul nou(missing_conditions)
    int missing_conditions = 0;
    if (!has_lower) missing_conditions++;
    if (!has_upper) missing_conditions++;
    if (!has_digit) missing_conditions++;
    if (has_repeating) missing_conditions++;


    /*
    Calculam diferenta dintre lungimea sirului si intervalul de lungime permis al parolei puternice, care este intre 6 și 20
    Daca sirul este mai scurt de 6 caractere, trebuie sa adaugam caractere la parola
    Daca sirul de intrare este mai lung de 20 de caractere, trebuie sa eliminam caracterele din parola
    Cu max() ne asiguram ca diferenta este intotdeauna pozitiva, deoarece nu putem avea modificari negative.
    */
    int length_diff = max(0, 6 - length) + max(0, length - 20);

    return max(missing_conditions, length_diff);
    /*
    Daca sirul indeplineste deja toate conditiile parolei, atat missing_conditions, cat și length_diff vor fi zero,deci funcția va returna zero.
    Altfel, va returna maximul dintre cele doua valori,
    deoarece trebuie sa facem cel putin atatea modificari pentru a face parola puternica.
    */
}

int main() {
    string password;
    getline(cin, password);
    int changes_required = minimum_password_changes(password);
    cout << changes_required << endl;
    return 0;
}
