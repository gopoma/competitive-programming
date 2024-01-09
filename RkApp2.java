

public class RkApp2 {
    public static void main(String[] args) {
        double h=0.5;       //paso
//Situación inicial
        double x0=5000;
        Estado es=new Estado(0, x0, 0);
        double t=20.0;      //resolver la e. d. hasta este instante

        new Funcion().resolver(t, es, h);
        System.out.println("valor aprox. de x "+(int)es.x);
        System.out.println("valor aprox. de y "+(int)es.y);
// valor exacto
        double x=(int)(x0*Math.exp(-0.1*t));
        double y=(int)(0.1*x0*(Math.exp(-0.1*t)-Math.exp(-0.2*t))/0.1);
        System.out.println("valor exacto de x "+(int)x);
        System.out.println("valor exacto de y "+(int)y);

        try  {
//espera la pulsación de una tecla y luego RETORNO
            System.in.read();
        }catch (Exception ex) {  }
    }
}

