// Clase principal
public class G1 {
    public static void main(String[] args) {
        Pajaro miPajaro = new Pajaro();
        miPajaro.volar();  // Salida: El pájaro vuela alto en el cielo.
    }
}

// Definición de la interfaz
interface Volador {
    void volar();
}

// Clase que implementa la interfaz
class Pajaro implements Volador {
    @Override
    public void volar() {
        System.out.println("El pájaro vuela alto en el cielo.");
    }
}
