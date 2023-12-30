#include <iostream>
#include <string>

using namespace std;

class Button {
public:
    virtual void paint() = 0;
};

class WinButton: public Button {
public:
    void paint() {
        cout << "Dibujando Button Windows\n";
    }
};

class MacButton: public Button {
public:
    void paint() {
        cout << "Dibujando Button Mac\n";
    }
};

class LinuxButton: public Button {
public:
    void paint() {
        cout << "Dibujando Button Linux\n";
    }
};

class CheckBox {
public:
    virtual void paint() = 0;
};

class WinCheckBox: public CheckBox {
public:
    void paint() {
        cout << "Dibujando CheckBox Windows\n";
    }
};

class MacCheckBox: public CheckBox {
public:
    void paint() {
        cout << "Dibujando CheckBox Mac\n";
    }
};

class LinuxCheckBox: public CheckBox {
public:
    void paint() {
        cout << "Dibujando CheckBox Linux\n";
    }
};

class GUIFactory {
public:
    virtual string getName() = 0;

    virtual Button* createButton() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

class WinFactory: public GUIFactory {
public:
    string getName() { return "Windows"; }

    Button* createButton() {
        return new WinButton();
    }

    CheckBox* createCheckBox() {
        return new WinCheckBox();
    }
};

class MacFactory: public GUIFactory {
public:
    string getName() { return "Mac"; }

    Button* createButton() {
        return new MacButton();
    }

    CheckBox* createCheckBox() {
        return new MacCheckBox();
    }
};

class LinuxFactory: public GUIFactory {
public:
    string getName() { return "Linux"; }

    Button* createButton() {
        return new LinuxButton();
    }

    CheckBox* createCheckBox() {
        return new LinuxCheckBox();
    }
};

class Application {
private:
    GUIFactory* factory;

    Button* btn;
public:
    Application(GUIFactory* f) {
        cout << "Cliente: " << f->getName() << "\n";

        factory = f;
    }

    void init() {
        createUI();
        paint(); cout << "\n";
    }

    void createUI() {
        btn = factory->createButton();
    }

    void paint() {
        btn->paint();
    }
};


GUIFactory* getGUIFactory(int os) {
    // 1-Windows
    // 2-Mac
    // 3-Linux

    switch(os) {
        case 1: {
            return new WinFactory();
        }
        case 2: {
            return new MacFactory();
        }
        case 3: {
            return new LinuxFactory();
        }
        default: {
            cout << "Error! Unknown operating system.\n";
            exit(1);
        }
    }
}

signed main() {
    Application* app = new Application(getGUIFactory(1));
    app->init();

    Application* app2 = new Application(getGUIFactory(2));
    app2->init();

    Application* app3 = new Application(getGUIFactory(3));
    app3->init();
}
