
package ejercicio2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Ejercicio2 {

    public static void generarTrianguloPascal(int n, List<Integer> coeficientes) {
        coeficientes.clear();
        for (int k = 0; k <= n; k++) {
            // Se inicializa la lista con el tamaño necesario
            coeficientes.add(0); 
        }

        if (n >= 0) {
            coeficientes.set(0, 1);
        }

        // C(i, k) = C(i-1, k-1) + C(i-1, k)
        for (int i = 1; i <= n; i++) {
            coeficientes.set(i, 1);
            for (int j = i - 1; j > 0; j--) {
                // Cálculo basado en la fila anterior (va hacia atrás)
                int nuevoCoeficiente = coeficientes.get(j) + coeficientes.get(j - 1);
                coeficientes.set(j, nuevoCoeficiente);
            }
        }
    }
    
    public static void mostrarPolinomio(int n, List<Integer> coeficientes) {
        System.out.print("(x+1)^" + n + " = ");
        for (int i = n; i >= 0; i--) {
            int coeficiente = coeficientes.get(i);
            if (coeficiente != 0) {
                if (i != n) {
                    System.out.print(" + ");
                }
                if (coeficiente != 1 || i == 0) {
                    System.out.print(coeficiente);
                }
                if (i > 0) {
                    System.out.print("x");
                    if (i > 1) {
                        System.out.print("^" + i);
                    }
                }
            }
        }
        System.out.println();
    }

   
    public static long calcularPolinomio(int n, int x, List<Integer> coeficientes, Appendable outputStream) throws IOException {
        long resultado = 0;
        
        // Escribe el encabezado del cálculo
        if (outputStream instanceof FileWriter) {
            outputStream.append("Cálculo para x = ").append(String.valueOf(x)).append(":\n");
        } else {
            System.out.println("Cálculo para x = " + x + ":");
        }
        
        StringBuilder calculoStr = new StringBuilder();

        for (int i = n; i >= 0; i--) {
            int coeficiente = coeficientes.get(i);
            if (coeficiente != 0) {
                long termino = (long) coeficiente;
                
                // Calcular x^i
                for (int j = 0; j < i; j++) {
                    termino *= x;
                }
                
                resultado += termino;

                // Construir la representación textual del término
                if (i < n) {
                    calculoStr.append(" + ");
                }
                if (coeficiente != 1 || i == 0) {
                    calculoStr.append(coeficiente);
                }
                if (i > 0) {
                    calculoStr.append("x");
                    if (i > 1) {
                        calculoStr.append("^").append(i);
                    }
                }
            }
        }
        
        // Escribe el resultado final
        calculoStr.append(" = ").append(resultado);
        
        if (outputStream instanceof FileWriter) {
            outputStream.append(calculoStr).append("\n");
        } else {
            System.out.println(calculoStr.toString());
        }
        
        return resultado;
    }


    
    private static void guardarResultados(int n, List<Integer> coeficientes, double tiempoEjecucionSegundos) {
        
        try (FileWriter archivo = new FileWriter("resultado.txt")) {
            
            archivo.write("Tiempo de ejecución: " + tiempoEjecucionSegundos + " segundos\n\n");
            
            // 1. Polinomio (x+1)^n
            archivo.write("Polinomio (x+1)^" + n + ":\n");
            StringBuilder polinomioStr = new StringBuilder();
            polinomioStr.append("(x+1)^").append(n).append(" = ");
            for (int i = n; i >= 0; i--) {
                int coeficiente = coeficientes.get(i);
                if (coeficiente != 0) {
                    if (i != n) {
                        polinomioStr.append(" + ");
                    }
                    if (coeficiente != 1 || i == 0) {
                        polinomioStr.append(coeficiente);
                    }
                    if (i > 0) {
                        polinomioStr.append("x");
                        if (i > 1) {
                            polinomioStr.append("^").append(i);
                        }
                    }
                }
            }
            archivo.write(polinomioStr.toString() + "\n");

            // 2. Resultado para x = 2
            archivo.write("\nResultado para x = 2:\n");
            // Llamamos a calcularPolinomio, pasando el FileWriter como destino
            calcularPolinomio(n, 2, coeficientes, archivo);

            System.out.println("\nResultados guardados en 'resultado.txt'");
            
        } catch (IOException e) {
            System.out.println("No se pudo abrir o escribir en el archivo 'resultado.txt': " + e.getMessage());
        }
    }
    
    public static void main(String[] args) {
        int n = 100; 
        List<Integer> coeficientes = new ArrayList<>();
        
        // --- 1. Generación y Medición de Tiempo ---
        long inicio = System.nanoTime();
        generarTrianguloPascal(n, coeficientes);
        long fin = System.nanoTime();
        
        double tiempoEjecucionSegundos = (fin - inicio) / 1_000_000_000.0;
        
        // --- 2. Mostrar Resultados en Consola ---
        System.out.println("--- Polinomio Binomial ---");
        mostrarPolinomio(n, coeficientes);
        
        try {
            // Usamos System.out como un Appendable para imprimir en la consola
            calcularPolinomio(n, 2, coeficientes, System.out);
        } catch (IOException e) {
            // Esto solo ocurriría si System.out fallara (caso muy raro)
            System.err.println("Error al imprimir el cálculo del polinomio: " + e.getMessage());
        }
        
        System.out.println("\nTiempo de ejecución: " + tiempoEjecucionSegundos + " segundos");

        // --- 3. Guardar en Archivo ---
        guardarResultados(n, coeficientes, tiempoEjecucionSegundos);
    }
  
    
}
