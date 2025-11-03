#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    const char *ingles;
    const char *espanol;
    int contador; 
} PalabraReservada;


PalabraReservada palabras_reservadas[] = {
    {"auto", "Automático", 0}, {"break", "Romper", 0}, {"case", "Caso", 0},
    {"char", "Carácter", 0}, {"const", "Constante", 0}, {"continue", "Continuar", 0},
    {"default", "Predeterminado", 0}, {"do", "Hacer", 0}, {"double", "Doble", 0},
    {"else", "Si no", 0}, {"enum", "Enumeración", 0}, {"extern", "Externo", 0},
    {"float", "Flotante", 0}, {"for", "Para", 0}, {"goto", "Ir a", 0},
    {"if", "Si (condición)", 0}, {"int", "Entero", 0}, {"long", "Largo", 0},
    {"register", "Registro", 0}, {"return", "Retornar", 0}, {"short", "Corto", 0},
    {"signed", "Con signo", 0}, {"sizeof", "Tamaño de", 0}, {"static", "Estático", 0},
    {"struct", "Estructura", 0}, {"switch", "Interruptor", 0}, {"typedef", "Definir tipo", 0},
    {"union", "Unión", 0}, {"unsigned", "Sin signo", 0}, {"void", "Vacío", 0},
    {"volatile", "Volátil", 0}, {"while", "Mientras", 0},
    {NULL, NULL, 0}
};



// Verifica si un carácter es un delimitador de token
int es_delimitador(char c) {
    return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

// Carga el código de un archivo en memoria dinámica
char *cargar_programa_desde_archivo(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    rewind(archivo);
    
    if (tamano <= 0) {
        fclose(archivo);
        fprintf(stderr, "Error: El archivo está vacío o no se pudo determinar su tamaño.\n");
        return NULL;
    }
    
    char *programa = (char *)malloc(tamano + 1);
    if (programa == NULL) {
        fclose(archivo);
        perror("Error al asignar memoria dinámica");
        return NULL;
    }

    size_t leido = fread(programa, 1, tamano, archivo);
    fclose(archivo);
    
    if (leido != tamano) {
        free(programa);
        perror("Error al leer el archivo completamente");
        return NULL;
    }
    programa[tamano] = '\0'; 

    return programa;
}

// Función principal de verificación y conteo 
void verificar_palabras_reservadas(char *programa) {
    PalabraReservada *pr = palabras_reservadas;

    printf("\nIniciando verificación y conteo...\n");

    // Iterar sobre todas las palabras reservadas
    while (pr->ingles != NULL) {
        const char *palabra = pr->ingles;
        size_t len_palabra = strlen(palabra);
        
        
        char *ptr_programa = programa; 
        
        // Bucle para buscar todas las ocurrencias de la palabra actual
        while ((ptr_programa = strstr(ptr_programa, palabra)) != NULL) {
            
            // --- VERIFICACIÓN DE TOKEN COMPLETO ---
            
            // 1. Comprueba el inicio: debe ser el inicio de la cadena o un delimitador
            int inicio_valido = (ptr_programa == programa) || es_delimitador(*(ptr_programa - 1));
            
            // 2. Comprueba el final: debe ser el final de la cadena o un delimitador
            int fin_valido = (*(ptr_programa + len_palabra) == '\0') || es_delimitador(*(ptr_programa + len_palabra));

            if (inicio_valido && fin_valido) {
            
                pr->contador++;
            }
            
            
            ptr_programa += len_palabra;
        }
        
    
        pr++; 
    }
    
    printf("Conteo completado.\n");
}


// Función para generar el reporte de resultados
void generar_reporte() {
    PalabraReservada *pr = palabras_reservadas;
    int total_palabras_encontradas = 0;

    printf("\n=============================================\n");
    printf("          REPORTE DE PALABRAS RESERVADAS     \n");
    printf("=============================================\n");
    printf("Palabra C | Ocurrencias | Equivalente en Español\n");
    printf("----------|-------------|-----------------------\n");
    
    while (pr->ingles != NULL) {
        if (pr->contador > 0) {
            printf("%-9s | %-11d | %s\n", pr->ingles, pr->contador, pr->espanol);
            total_palabras_encontradas += pr->contador;
        }
        pr++;
    }
    
    printf("----------|-------------|-----------------------\n");
    printf("TOTAL ENCONTRADAS: %d\n", total_palabras_encontradas);
    printf("=============================================\n");
    
    if (total_palabras_encontradas == 0) {
        printf("No se encontraron palabras reservadas de C en el código.\n");
    }
}


int main() {
    char nombre_archivo[256];
    
    printf("Ingrese la ruta del archivo C a cargar (ej: codigo.c): ");
    if (scanf("%255s", nombre_archivo) != 1) {
        fprintf(stderr, "Error en la lectura de la entrada.\n");
        return 1;
    }
    
    // 1. Cargar el código en memoria dinámica desde el archivo
    char *programa_cargado = cargar_programa_desde_archivo(nombre_archivo);

    if (programa_cargado == NULL) {
        return 1;
    }

    printf("\n## Código C Original (Cargado en memoria dinámica):\n");
    printf("--------------------------------------------------\n");
    printf("%s\n", programa_cargado);
    printf("--------------------------------------------------\n");

    // 2. Procesar: Verificar y contar las palabras reservadas
    verificar_palabras_reservadas(programa_cargado);

    // 3. Generar el reporte (muestra la lista y el conteo traducido)
    generar_reporte();

    // 4. Liberar la memoria dinámica
    printf("\nLiberando memoria dinámica...\n");
    free(programa_cargado);

    return 0;
}