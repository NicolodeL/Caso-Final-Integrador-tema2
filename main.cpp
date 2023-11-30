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
    FILE* f = nullptr;

    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "Error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

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
        if (f)
            fclose(f);
    }
}

int main()
{
    // Utiliza la función load_script() para cargar el archivo "Ejemplo.txt" y mostrar su contenido
    load_script("Ejemplo.txt", true);

    // Utiliza la función load_script() para cargar un script mediante la entrada del usuario
    

    return 0;
}

