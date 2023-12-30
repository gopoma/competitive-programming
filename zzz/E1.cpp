#include <bits/stdc++.h>
using namespace std;

class Receta {
public:
    virtual void juntarIngredientes() = 0;
    virtual void prepararIngredientes() = 0;
    virtual void cocinarIngredientes() = 0;
    virtual void adornar() = 0;
};

class Ceviche: public Receta {
public:
    virtual void juntarIngredientes() {cout<<"Juntando Ingredientes de Ceviche\n";}
    virtual void prepararIngredientes() {cout<<"Preparando Ingredientes de Ceviche\n";}
    virtual void cocinarIngredientes() {cout<<"Cocinando Ingredientes de Ceviche\n";}
    virtual void adornar() {cout<<"Adornando al Ceviche\n";}
};

class TallarinRojo: public Receta {
public:
    virtual void juntarIngredientes() {cout<<"Juntando Ingredientes de TallarinRojo\n";}
    virtual void prepararIngredientes() {cout<<"Preparando Ingredientes de TallarinRojo\n";}
    virtual void cocinarIngredientes() {cout<<"Cocinando Ingredientes de TallarinRojo\n";}
    virtual void adornar() {cout<<"Adornando al TallarinRojo\n";}
};

class Aeropuerto: public Receta {
public:
    virtual void juntarIngredientes() {cout<<"Juntando Ingredientes de Aeropuerto\n";}
    virtual void prepararIngredientes() {cout<<"Preparando Ingredientes de Aeropuerto\n";}
    virtual void cocinarIngredientes() {cout<<"Cocinando Ingredientes de Aeropuerto\n";}
    virtual void adornar() {cout<<"Adornando al Aeropuerto\n";}
};

class Tipakay: public Receta {
public:
    virtual void juntarIngredientes() {cout<<"Juntando Ingredientes de Tipakay\n";}
    virtual void prepararIngredientes() {cout<<"Preparando Ingredientes de Tipakay\n";}
    virtual void cocinarIngredientes() {cout<<"Cocinando Ingredientes de Tipakay\n";}
    virtual void adornar() {cout<<"Adornando al Tipakay\n";}
};

class RecetaFactory {
public:
    static Receta* createReceta(int type) {
        Receta* res = NULL;

        switch(type) {
            case 1: { res = new Ceviche(); break; }
            case 2: { res = new TallarinRojo(); break; }
            case 3: { res = new Aeropuerto(); break; }
            case 4: { res = new Tipakay(); break; }
            default: {
                cout << "invalido RECIPE type, ingresa otra opcion" << "\n";
                return NULL;
            }
        }

        res->juntarIngredientes();
        res->prepararIngredientes();
        res->cocinarIngredientes();
        res->adornar();

        return res;
    }
};

signed main() {
    Receta* cv = RecetaFactory::createReceta(1); cout<<"\n";
    Receta* tl = RecetaFactory::createReceta(2); cout<<"\n";
    Receta* ar = RecetaFactory::createReceta(3); cout<<"\n";
    Receta* tk = RecetaFactory::createReceta(4); cout<<"\n";
}
