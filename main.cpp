#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
    static constexpr auto reset = "\033[0m";
};

struct ConsoleBox
{
    void new_text() { /*...*/ }
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    ifstream file;

    try
    {
        file.open(filename);
        if (!file.is_open())
        {
            cerr << "Error de apertura de " << filename << endl;
            return;
        }

        char buf[4001];
        while (file.read(buf, sizeof(buf)))
        {
            buf[file.gcount()] = '\0'; // Agregamos el carácter nulo al final del buffer leído
            script.append(buf);
        }

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << ColorConsole::reset << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const exception& e)
    {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
    }
}

void load_script()
{
    string filename;
    cout << "Archivo: ";
    cin >> filename;
    load_script(filename.c_str(), true);
}
// C:\Users\nicol\OneDrive\Documents\GitHub\Caso-Final-Integrador-tema2\Ejemplo.txt ruta hasta el archivod de ejemplo
int main()
{
    load_script("Ejemplo.txt", true);

    load_script();

    return 0;
}

