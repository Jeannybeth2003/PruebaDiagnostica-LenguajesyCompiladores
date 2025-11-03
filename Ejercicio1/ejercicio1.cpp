#include <iostream>
#include <string>
#include <vector>

class ValidadorFEN {
private:
    // Función auxiliar para validar el formato del tablero
    bool validarTablero(const std::string& tablero) const {
        std::string copia = tablero;  // Crear una copia modificable
        size_t pos = 0;
        int filasValidadas = 0;
        
        while ((pos = copia.find('/')) != std::string::npos) {
            std::string fila = copia.substr(0, pos);
            copia.erase(0, pos + 1);
            
            if (!validarFila(fila)) return false;
            filasValidadas++;
        }
        
        return filasValidadas == 7 && validarFila(copia);
    }

    // Función auxiliar para validar una fila individual
    bool validarFila(const std::string& fila) const {
        int cuadradosVacios = 0;
        for (size_t i = 0; i < fila.length(); ++i) {
            if (std::isdigit(fila[i])) {
                cuadradosVacios += (fila[i] - '0');
            } else if (esPiezaValida(fila[i])) {
                continue;
            } else {
                return false;
            }
        }
        return cuadradosVacios <= 8;
    }

    // Función auxiliar para verificar si un carácter es una pieza válida
    bool esPiezaValida(char c) const {
        return (c >= 'r' && c <= 'k') ||  // Piezas negras
               (c >= 'R' && c <= 'K') ||  // Piezas blancas
               (c == 'p' || c == 'P');    // Peones
    }

public:
    // Constructor por defecto
    ValidadorFEN() {}

    // Función principal para validar una cadena FEN
    bool validar(const std::string& fen) const {
        // Verificar longitud mínima
        if (fen.length() < 30) return false;

        // Dividir la cadena en sus componentes
        std::vector<std::string> campos;
        size_t inicio = 0;
        size_t fin = fen.find(' ');
        
        while (fin != std::string::npos) {
            campos.push_back(fen.substr(inicio, fin - inicio));
            inicio = fin + 1;
            fin = fen.find(' ', inicio);
        }
        campos.push_back(fen.substr(inicio));

        // Debe haber exactamente 6 campos
        if (campos.size() != 6) return false;

        // Validar cada campo según su posición
        return validarTablero(campos[0]) &&
               validarTurno(campos[1]) &&
               validarEnroque(campos[2]) &&
               validarEnPassant(campos[3]) &&
               validarContadorMedioMovimiento(campos[4]) &&
               validarNumeroMovimientoCompleto(campos[5]);
    }

    // Funciones de validación específicas para cada campo
    bool validarTurno(const std::string& turno) const {
        return (turno == "w" || turno == "b");
    }

    bool validarEnroque(const std::string& enroque) const {
        if (enroque == "-") return true;
        
        std::string permisosValidos = "KQkq";
        for (size_t i = 0; i < enroque.length(); ++i) {
            if (permisosValidos.find(enroque[i]) == std::string::npos) return false;
        }
        return true;
    }

    bool validarEnPassant(const std::string& enpassant) const {
        if (enpassant == "-") return true;
        
        if (enpassant.length() != 2) return false;
        
        char columna = enpassant[0];
        char fila = enpassant[1];
        
        return (columna >= 'a' && columna <= 'h') &&
               (fila == '3' || fila == '6');
    }

    bool validarContadorMedioMovimiento(const std::string& contador) const {
        for (size_t i = 0; i < contador.length(); ++i) {
            if (!std::isdigit(contador[i])) return false;
        }
        return true;
    }

    bool validarNumeroMovimientoCompleto(const std::string& numero) const {
        for (size_t i = 0; i < numero.length(); ++i) {
            if (!std::isdigit(numero[i])) return false;
        }
        return true;
    }
};

// Función principal para demostrar el uso
int main() {
    ValidadorFEN validador;
    
    // Ejemplos de cadenas FEN válidas
    std::string fenInicial = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string fenDespuesMovimiento = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1";
    
    // Ejemplos de cadenas FEN inválidas
    std::string fenInvalido1 = "rnbqkbnr/ppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";  // Falta peón
    std::string fenInvalido2 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR x KQkq - 0 1";  // Turno inválido
    
    std::cout << "FEN inicial valida: " << (validador.validar(fenInicial) ? "SÍ" : "NO") << std::endl;
    std::cout << "FEN despues de movimiento valida: " << (validador.validar(fenDespuesMovimiento) ? "SÍ" : "NO") << std::endl;
    std::cout << "FEN invalida (falta peon): " << (validador.validar(fenInvalido1) ? "SÍ" : "NO") << std::endl;
    std::cout << "FEN invalida (turno incorrecto): " << (validador.validar(fenInvalido2) ? "SÍ" : "NO") << std::endl;
    
    return 0;
}
