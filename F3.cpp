#include <bits/stdc++.h>
using namespace std;

class MiClase {
public:
    explicit MiClase(int valor) : valor_(valor) {}
    operator int() const { return valor_; }  // Operador de conversión a int
private:
    int valor_;
};

int main() {
    MiClase objeto(456);
    int valor = objeto;  // Uso del operador de conversión
    std::cout << valor << std::endl;  // 456

    return 0;
}
