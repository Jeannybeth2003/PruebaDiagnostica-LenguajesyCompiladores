#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>

// Funcion para validar notacion cientifica
bool validarNotacionCientifica(const std::string& cadena) {
    int posE = cadena.find('e');
    if (posE == std::string::npos) return false;
    
    std::string parteNumerica = cadena.substr(0, posE);
    std::string parteExponente = cadena.substr(posE + 1);
    
    // Validar parte numerica
    bool tienePunto = false;
    bool tieneNumero = false;
    
    for (size_t i = 0; i < parteNumerica.length(); i++) {
        char c = parteNumerica[i];
        if (c == '.') {
            if (tienePunto) return false;
            tienePunto = true;
        } else if (std::isdigit(c)) {
            tieneNumero = true;
        } else if (c == '+' || c == '-') {
            if (i != 0) return false;
        } else {
            return false;
        }
    }
    
    if (!tieneNumero) return false;
    
    // Validar parte exponencial
    for (size_t i = 0; i < parteExponente.length(); i++) {
        if (!std::isdigit(parteExponente[i])) return false;
    }
    
    return true;
}

// Funcion para validar direccion IP
bool validarIP(const std::string& ip) {
    size_t pos = 0;
    int octetos = 0;
    int valorActual = 0;
    
    while (pos < ip.length()) {
        valorActual = 0;
        while (pos < ip.length() && std::isdigit(ip[pos])) {
            valorActual = valorActual * 10 + (ip[pos++] - '0');
        }
        
        if (valorActual < 0 || valorActual > 255) return false;
        if (pos < ip.length() && ip[pos] != '.') return false;
        
        octetos++;
        pos++;
    }
    
    return octetos == 4;
}

// Funcion para validar correo electronico
bool validarEmail(const std::string& email) {
    if (email.empty() || email.length() > 254) return false;
    
    size_t posArroba = email.find('@');
    if (posArroba == std::string::npos || posArroba == 0 || posArroba == email.length() - 1) {
        return false;
    }
    
    // Validar parte local (antes del @)
    for (size_t i = 0; i < posArroba; i++) {
        char c = email[i];
        if (!std::isalnum(c) && c != '.' && c != '_' && c != '-') return false;
    }
    
    // Validar dominio
    size_t posPunto = email.find('.', posArroba);
    if (posPunto == std::string::npos) return false;
    
    // Validar parte del dominio despues del @ y antes del punto
    for (size_t i = posArroba + 1; i < posPunto; i++) {
        char c = email[i];
        if (!std::isalnum(c) && c != '-' && c != '.') return false;
    }
    
    // Validar extension
    std::string extension = email.substr(posPunto + 1);
    if (extension.length() < 2 || extension.length() > 6) return false;
    for (size_t i = 0; i < extension.length(); i++) {
        if (!std::isalpha(extension[i])) return false;
    }
    
    return true;
}

int main() {
    clock_t inicio, fin;
    
    std::cout << "Validador de Cadenas\n";
    std::cout << "1. Notacion Cientifica\n";
    std::cout << "2. Direccion IP\n";
    std::cout << "3. Correo Electronico\n";
    std::cout << "Seleccione el tipo de validacion: ";
    
    int opcion;
    std::cin >> opcion;
    
    std::string cadena;
    bool resultado;
    
    inicio = clock();
    
    switch(opcion) {
        case 1:
            std::cout << "Ingrese una cadena en notacion cientifica (ej: 1.23e-4): ";
            std::cin >> cadena;
            resultado = validarNotacionCientifica(cadena);
            std::cout << "¿Es valida? " << (resultado ? "Si" : "No") << std::endl;
            break;
            
        case 2:
            std::cout << "Ingrese una direccion IP (ej: 192.168.1.1): ";
            std::cin >> cadena;
            resultado = validarIP(cadena);
            std::cout << "¿Es valida? " << (resultado ? "Si" : "No") << std::endl;
            break;
            
        case 3:
            std::cout << "Ingrese un correo electronico (ej: ejemplo@dominio.com): ";
            std::cin >> cadena;
            resultado = validarEmail(cadena);
            std::cout << "¿Es valida? " << (resultado ? "Si" : "No") << std::endl;
            break;
            
        default:
            std::cout << "Opcion no valida" << std::endl;
            break;
    }
    
    fin = clock();
    std::cout << "\nTiempo de ejecucion: " << (fin - inicio) / (double)CLOCKS_PER_SEC << " segundos" << std::endl;
    
    return 0;
}
