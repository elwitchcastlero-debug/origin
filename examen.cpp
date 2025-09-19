#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

struct Point { // Define la estructura de un Point
    double x, y;
};


double calcularMagnitud(const Point& p1) { // Función para calcular la magnitud asociada al punto i
    return sqrt(pow(p1.x, 2) + pow(p1.y, 2));
}

void leerPuntos(Point puntos[], int n) {  // Función para leer las coordenadas de varios puntos
    char respuesta;
    std::cout << "\n ¿Desea ingresar los puntos manualmente? (s/n): ";
    std::cin >> respuesta;
    std::cin.ignore(); // Ignorar el salto de línea

    if (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N'){ // Caso en el que el comando no sea sí o no
      while (respuesta != 's' && respuesta != 'S' && respuesta != 'n' && respuesta != 'N') {
         std::cout << "\n Respuesta inválida, ingrese s para sí o n para no: ";
         std::cin >> respuesta;
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer
      }

    }

    if (respuesta == 's' || respuesta == 'S') { // Caso en el que el comando sea sí
        for (int i = 0; i < n; i++) {
            std::string input;
            std::cout << "\n Ingrese las coordenadas del punto " << i + 1 << " (x, y): ";
            std::getline(std::cin, input);

            std::stringstream ss(input);
            char paren1, comma, paren2;
            ss >> paren1 >> puntos[i].x >> comma >> puntos[i].y >> paren2;

            if (paren1 != '(' || comma != ',' || paren2 != ')') {
                std::cout << "\n Error: El formato debe ser (x, y). Intente de nuevo.\n";
                i--; // Repetir la iteración
                continue;
            }
        }
    } if (respuesta == 'n' || respuesta == 'N') { // Caso en el que el comando sea no
        std::cout << "\n Usando puntos predeterminados...\n";
        Point predeterminados[] = {{0, 0}, {3, 4}, {6, 8}, {9, 12}};
        for (int i = 0; i < n && i < 4; i++) {
            puntos[i] = predeterminados[i]; //Asignando los valores de predeterminado en puntos
        }
    }
}


double calcularMayorMagnitud(Point puntos[], int n, int& indiceMayorMagnitud) {  // Función para calcular la mayor magnitud y su índice
    double m_my = calcularMagnitud(puntos[0]);
    indiceMayorMagnitud = 0;

    for (int i = 1; i < n; i++) {
        double m = calcularMagnitud(puntos[i]); // Calcula la magnitud del i - elemento de puntos
        if (m > m_my) {
            m_my = m; // Compara la magnitud con la mayor magnitud registrada
            indiceMayorMagnitud = i; // Asigna el valor i a la posición del punto con mayor magnitud registrada
        }
    }
    return m_my;
}

void mostrarResultado(Point puntos[], int indiceMayorMagnitud, double m_my) { // Función para mostrar el punto con mayor magnitud, sus coordenadas y su magnitud

    std::cout << "\n El punto de mayor magnitud es el " << indiceMayorMagnitud + 1 << ", con coordenadas: ("<< puntos[indiceMayorMagnitud].x << ", "
              << puntos[indiceMayorMagnitud].y << "), el valor de la magnitud es: " << m_my << std::endl;
}

int main() {
    int n;

    do {
        std::cout << "Ingrese el número de puntos (mínimo 2): "; // Inicia el programa
        if (!(std::cin >> n)) { // Caso en el que el comando no sea un entero positivo
            std::cout << "\n Comando inválido, debe ser un número entero positivo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            n = -1; // Forzar que el bucle continúe
        } else if (n <= 1) {  // Caso en el que el comando no sea mayor a 1 elemento
            std::cout << "\n Se necesitan al menos 2 puntos para calcular las magnitudes (recuerde que son enteros positivos).\n";
        }
    } while (n <= 1);

    Point* puntos = new Point[n];

    leerPuntos(puntos, n);

    int indiceMayorMagnitud;
    double m = calcularMayorMagnitud(puntos, n, indiceMayorMagnitud);

    mostrarResultado(puntos, indiceMayorMagnitud, m);

    delete[] puntos;
    return 0;
}
