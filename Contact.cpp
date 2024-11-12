#ifndef CONTATO_H
#define CONTATO_H
#include <string>
using namespace std;

class Contato {
public:
    string nome;
    string telefone;
    string email;
    bool favorito;

    Contato(string x, string y, string z, bool w)
        : nome(x), telefone(y), email(z), favorito(w) {}


void setNome(string x) {
    nome = x;
}

void setTelefone(string y) {
    telefone = y;
}

void setEmail(string z) {
    email = z;
}
void setFavorito(bool fav) {
    favorito = fav;
}

string getNome() const { return nome; }
};


#endif // CONTATO_H