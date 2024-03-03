//
//  main.cpp
//  sifravimas
//
//  Created by juli on 03/03/2024.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Funkcija, kuri šifruoja arba dešifruoja tekstą naudojant Vigenere šifravimo algoritmą
string vigenere_encrypt_decrypt(const string& text, const string& key, bool encrypt = true) {
    //Susikuriame vektorių, kuris saugos pagrindinius simbolius (ASCII 32-126)
    vector<char> base_symbols;
    for (int i = 32; i < 127; ++i) {
        base_symbols.push_back(static_cast<char>(i));
    }
    // Išplėčiame raktą, kad jis būtų tokio pat ilgio kaip ir tekstas
    string expanded_key = key;
    while (expanded_key.length() < text.length()) {
        expanded_key += key;
    }
    expanded_key = expanded_key.substr(0, text.length());

    // Sukuriame vektorių, kuris saugos indeksus, kuriuos reikės naudoti su raktu
    vector<int> key_indices;
    for (char k : expanded_key) {
        key_indices.push_back(distance(base_symbols.begin(), find(base_symbols.begin(), base_symbols.end(), k)));
    }

    // Inicializuojame rezultatą ir pradinius kintamuosius
    string result = "";
    int key_index = 0;

    // Einame per visus tekstui priklausančius simbolius
    for (char c : text) {
        // Randame simbolio indeksą pagal pagrindinių simbolių vektorių
        int char_index = std::distance(base_symbols.begin(), find(base_symbols.begin(), base_symbols.end(), c));
        // Apskaičiuojame poslinkį pagal dabartinį rakto simbolį
        int key_shift = key_indices[key_index];
        // Atnaujiname rakto indeksą
        key_index = (key_index + 1) % key_indices.size();

        // Apskaičiuojame naują simbolio indeksą, priklausomai ar šifruojame ar dešifruojame
        int new_char_index;
        if (encrypt) {
            new_char_index = (char_index + key_shift) % base_symbols.size();
        } else {
            new_char_index = (char_index - key_shift + base_symbols.size()) % base_symbols.size();
        }

        // Gautą naują simbolį pridedame prie rezultato
        char new_char = base_symbols[new_char_index];
        result += new_char;
    }

    // Grąžiname rezultatą
    return result;
}

// Main funkcija, kuri vykdo šifravimą arba dešifravimą pagal vartotojo pasirinkimą
int main() {
    char action;
    string text, key;

    // Vartotojo įvesties gavimas
    cout << "Choose action (encrypt - 'e', decrypt - 'd'): ";
    cin >> action;
    cin.ignore(); // Išvalome įvesties buferį
    cout << "Enter text: ";
    getline(std::cin, text);
    cout << "Enter key: ";
    getline(std::cin, key);

    // Pagal vartotojo pasirinkimą šifruojame arba dešifruojame tekstą
    if (action == 'e' || action == 'E') {
        string encrypted_text = vigenere_encrypt_decrypt(text, key);
        cout << "Encrypted text: " << encrypted_text << endl;
    } else if (action == 'd' || action == 'D') {
        string decrypted_text = vigenere_encrypt_decrypt(text, key, false);
        cout << "Decrypted text: " << decrypted_text << endl;
    } else {
        cout << "Invalid action. Enter 'e' to encrypt or 'd' to decrypt." << endl;
    }

    return 0;
}
