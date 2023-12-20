#include <bits/stdc++.h>
using namespace std;

class MiClase {
public:
    MiClase(int valor) : valor_(valor) {}
    int getValor() const { return valor_; }
private:
    int valor_;
};

int main() {
    MiClase objeto = 123;  // Conversión implícita de int a MiClase
    std::cout << objeto.getValor() << std::endl;  // 123
    return 0;
}
