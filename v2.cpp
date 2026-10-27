#include <iostream>
#include <limits>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int obtenerAnioActual() {
    time_t tiempoActual = time(nullptr);
    tm* fechaActual = localtime(&tiempoActual);

    return fechaActual->tm_year + 1900;
}

const int MAX_REGISTROS = 100;
const int ANIO_ACTUAL = obtenerAnioActual();

/*
 * <Start utils>
 */
string leerTexto(const string& mensaje)
// Lee una linea completa para aceptar textos con espacios.
{
    cout << mensaje;

    string texto;

    if (! getline(cin, texto)) {
        cout << "\n\n[Fin de entrada]: el programa ha finalizado.\n";
        exit(0);
    }

    return texto;
}

string leerCampoNoVacio(const string& mensaje, const string& nombreCampo)
// Solicita un texto hasta que el usuario no deje el campo vacio.
{
    while (true) {
        string texto = leerTexto(mensaje);

        if (! texto.empty()) {
            return texto;
        }

        cout << "[Error]: " << nombreCampo << " no puede quedar vacio.\n";
    }
}

bool convertirAEntero(const string& texto, int& numero)
// Convierte una cadena numerica a entero evitando desbordamientos.
{
    try {
        size_t caracteresLeidos = 0;
        long long valor = stoll(texto, &caracteresLeidos);

        if (caracteresLeidos != texto.length() ||
            valor < numeric_limits<int>::min() ||
            valor > numeric_limits<int>::max()) {

            return false;
        }

        numero = static_cast<int>(valor);

        return true;
    } catch (...) {
        return false;
    }
}
// <End Utils/>

bool esNumeroNatural(const string& texto)
// Verifica que la cadena no este vacia y contenga solamente digitos.
{
    bool resultado;
    size_t i; // int
    char caracter;

    resultado = true;

    if (texto.length() == 0) {
        resultado = false;
    }

    for (i = 0; i < texto.length(); i++) {
        caracter = texto[i];
        if (caracter != '0' && caracter != '1' && caracter != '2' &&
            caracter != '3' && caracter != '4' && caracter != '5' &&
            caracter != '6' && caracter != '7' && caracter != '8' &&
            caracter != '9') {
            resultado = false;
        }
    }

    return resultado;
}

int leerAnioPublicacion()
// Solicita y valida el anio de publicacion.
{
    while (true) {
        string entrada = leerTexto("Ingrese el año de publicación: ");

        if (! esNumeroNatural(entrada)) {
            cout << "[Error]: el año debe escribirse utilizando solamente números.\n";
            continue;
        }

        int anio = 0;
        if (! convertirAEntero(entrada, anio)) {
            cout << "[Error]: el año ingresado es demasiado grande.\n";
            continue;
        }

        if (anio <= 0 || anio > ANIO_ACTUAL) {
            cout << "[Error]: el año debe ser mayor que 0 y menor o igual que "
                 << ANIO_ACTUAL << ".\n";
            continue;
        }

        return anio;
    }
}

string leerCategoria()
// Solicita una categoria valida y devuelve su texto correspondiente.
{
    while (true) {
        cout << "Seleccione la categoría:\n"
             << "1. Literatura\n"
             << "2. Ciencias\n"
             << "3. Informática\n"
             << "4. Sociales\n"
             << "5. Otra\n";

        string opcion = leerTexto("Ingrese un número del 1 al 5: ");

        if (opcion == "1") return "Literatura";
        if (opcion == "2") return "Ciencias";
        if (opcion == "3") return "Informática";
        if (opcion == "4") return "Sociales";
        if (opcion == "5") return "Otra";

        cout << "[Error]: elija una categoria valida ingresando un número del 1 al 5.\n";
    }
}

int leerCantidadEjemplares()
// Solicita y valida la cantidad de ejemplares.
{
    while (true) {
        string entrada = leerTexto("Ingrese la cantidad de ejemplares: ");

        if (! esNumeroNatural(entrada)) {
            cout << "[Error]: la cantidad debe escribirse utilizando solamente números.\n";
            continue;
        }

        int ejemplares = 0;
        if (! convertirAEntero(entrada, ejemplares)) {
            cout << "[Error]: la cantidad ingresada es demasiado grande.\n";
            continue;
        }

        if (ejemplares <= 0) {
            cout << "[Error]: la cantidad de ejemplares debe ser mayor que 0.\n";
            continue;
        }

        return ejemplares;
    }
}

void registrarLibro(
    string codigosLibro[],
    string titulosLibro[],
    string autoresLibro[],
    int aniosPublicacion[],
    string categoriasLibro[],
    int ejemplaresLibro[],
    int& cantidadLibros
)
// Registra un libro en los arreglos paralelos.
{
    if (cantidadLibros >= MAX_REGISTROS) {
        cout << "No hay espacio para registrar más libros.\n";
        return;
    }

    // En C++ el primer indice valido es 0.
    int posicion = cantidadLibros;

    cout << "\n=== REGISTRO DE NUEVO LIBRO ===\n";

    codigosLibro[posicion] = leerCampoNoVacio("Ingrese el código del libro: ", "El código");
    titulosLibro[posicion] = leerCampoNoVacio("Ingrese el título: ", "El título");
    autoresLibro[posicion] = leerCampoNoVacio("Ingrese el autor: ", "El autor");

    aniosPublicacion[posicion] = leerAnioPublicacion();
    categoriasLibro[posicion] = leerCategoria();
    ejemplaresLibro[posicion] = leerCantidadEjemplares();

    cantidadLibros++;
    cout << "\nLibro registrado correctamente!!.\n";
}

void registrarEstudiante(
    string carnesEstudiante[],
    string nombresEstudiante[],
    string apellidosEstudiante[],
    int& cantidadEstudiantes
)
// Registra un estudiante en los arreglos paralelos.
{
    if (cantidadEstudiantes >= MAX_REGISTROS) {
        cout << "No hay espacio para registrar más estudiantes.\n";
        return;
    }

    int posicion = cantidadEstudiantes;

    cout << "\n=== REGISTRO DE NUEVO ESTUDIANTE ===\n";

    carnesEstudiante[posicion] = leerCampoNoVacio("Ingrese el carnet del estudiante: ", "El carnet");
    nombresEstudiante[posicion] = leerCampoNoVacio("Ingrese los nombres: ", "Los nombres");
    apellidosEstudiante[posicion] = leerCampoNoVacio("Ingrese los apellidos: ", "Los apellidos");

    cantidadEstudiantes++;
    cout << "\nEstudiante registrado correctamente!!.\n";
}

void mostrarLibro(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    const int aniosPublicacion[],
    const string categoriasLibro[],
    const int ejemplaresLibro[],
    int posicion
)
// Muestra la informacion de un libro especifico.
{
    cout << "Libro número " << posicion + 1 << '\n'
         << "Código: " << codigosLibro[posicion] << '\n'
         << "Título: " << titulosLibro[posicion] << '\n'
         << "Autor: " << autoresLibro[posicion] << '\n'
         << "Año de publicación: " << aniosPublicacion[posicion] << '\n'
         << "Categoría: " << categoriasLibro[posicion] << '\n'
         << "Ejemplares: " << ejemplaresLibro[posicion] << '\n'
         << "--------------------------------\n";
}

void consultarLibros(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    const int aniosPublicacion[],
    const string categoriasLibro[],
    const int ejemplaresLibro[],
    int cantidadLibros
)
// Muestra todos los libros o busca un libro por codigo.
{
    if (cantidadLibros == 0) {
        cout << "No hay libros registrados.\n";
        return;
    }

    char opcionConsulta;

    do {
        cout << "\n=== CONSULTA DE LIBROS ===\n"
             << "1. Ver todos los libros\n"
             << "2. Buscar libro por código\n"
             << "3. Regresar al menú principal\n";

        string entrada = leerTexto("Ingrese una opción: ");

        if (entrada.length() == 1) {
            opcionConsulta = entrada[0];
        } else {
            opcionConsulta = '0';
        }

        switch (opcionConsulta) {
            case '1':
                cout << "===== LIBROS REGISTRADOS =====\n";

                for (int i = 0; i < cantidadLibros; i++) {
                    mostrarLibro(
                        codigosLibro,
                        titulosLibro,
                        autoresLibro,
                        aniosPublicacion,
                        categoriasLibro,
                        ejemplaresLibro,
                        i
                    );
                }
                break;

            case '2': {
                string codigoBuscado = leerCampoNoVacio(
                    "Ingrese el código del libro que desea buscar: ",
                    "El código"
                );
                bool encontrado = false;

                for (int i = 0; i < cantidadLibros; i++) {
                    if (codigosLibro[i] == codigoBuscado) {
                        mostrarLibro(
                            codigosLibro,
                            titulosLibro,
                            autoresLibro,
                            aniosPublicacion,
                            categoriasLibro,
                            ejemplaresLibro,
                            i
                        );

                        encontrado = true;
                        break;
                    }
                }

                if (! encontrado) {
                    cout << "No se encontro un libro con ese código.\n";
                }

                break;
            }

            case '3':
                break;

            default:
                cout << "[Error]: elija una opcion valida del 1 al 3.\n";
                break;
        }
    } while (opcionConsulta != '3');
}

void mostrarEstudiante(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int posicion
)
// Muestra la informacion de un estudiante especifico.
{
    cout << "Estudiante número " << posicion + 1 << '\n'
         << "Carnet: " << carnesEstudiante[posicion] << '\n'
         << "Nombres: " << nombresEstudiante[posicion] << '\n'
         << "Apellidos: " << apellidosEstudiante[posicion] << '\n'
         << "-----------------------------------\n";
}

void consultarEstudiantes(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes
)
// Muestra todos los estudiantes o busca un estudiante por carnet.
{
    if (cantidadEstudiantes == 0) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    char opcionConsulta;

    do {
        cout << "\n=== CONSULTA DE ESTUDIANTES ===\n"
             << "1. Ver todos los estudiantes\n"
             << "2. Buscar estudiante por carnet\n"
             << "3. Regresar al menú principal\n";

        string entrada = leerTexto("Ingrese una opción: ");

        if (entrada.length() == 1) {
            opcionConsulta = entrada[0];
        } else {
            opcionConsulta = '0';
        }

        switch (opcionConsulta) {
            case '1':
                cout << "===== ESTUDIANTES REGISTRADOS =====\n";

                for (int i = 0; i < cantidadEstudiantes; i++) {
                    mostrarEstudiante(
                        carnesEstudiante,
                        nombresEstudiante,
                        apellidosEstudiante,
                        i
                    );
                }
                break;

            case '2': {
                string carneBuscado = leerCampoNoVacio(
                    "Ingrese el carnet del estudiante que desea buscar: ",
                    "El carnet"
                );
                bool encontrado = false;

                for (int i = 0; i < cantidadEstudiantes; i++) {
                    if (carnesEstudiante[i] == carneBuscado) {
                        mostrarEstudiante(
                            carnesEstudiante,
                            nombresEstudiante,
                            apellidosEstudiante,
                            i
                        );
                        encontrado = true;
                        break;
                    }
                }

                if (! encontrado) {
                    cout << "No se encontro un estudiante con ese carnet.\n";
                }
                break;
            }

            case '3':
                break;

            default:
                cout << "[Error]: elija una opción valida del 1 al 3.\n";
                break;
        }
    } while (opcionConsulta != '3');
}

int buscarLibro(
    const string codigosLibro[],
    int cantidadLibros,
    const string& codigo
)
{
    for (int i = 0; i < cantidadLibros; i++) {
        if (codigosLibro[i] == codigo) {
            return i;
        }
    }

    return -1;
}

int buscarEstudiante(
    const string carnesEstudiante[],
    int cantidadEstudiantes,
    const string& carne
)
{
    for (int i = 0; i < cantidadEstudiantes; i++) {
        if (carnesEstudiante[i] == carne) {
            return i;
        }
    }

    return -1;
}

int buscarPrestamo(
    const string carnesPrestamo[],
    const string codigosPrestamo[],
    int cantidadPrestamos,
    const string& carne,
    const string& codigo
)
{
    for (int i = 0; i < cantidadPrestamos; i++) {
        if (carnesPrestamo[i] == carne &&
            codigosPrestamo[i] == codigo) {
            return i;
        }
    }

    return -1;
}

void registrarPrestamo(
    const string codigosLibro[],
    const string carnesEstudiante[],
    int ejemplaresLibro[],
    string carnesPrestamo[],
    string codigosPrestamo[],
    int cantidadLibros,
    int cantidadEstudiantes,
    int& cantidadPrestamos
)
{
    cout << "\n=== PRÉSTAMO DE LIBRO ===\n";

    string carne = leerCampoNoVacio(
        "Ingrese el carnet del estudiante: ",
        "El carnet"
    );

    string codigo = leerCampoNoVacio(
        "Ingrese el código del libro: ",
        "El código"
    );

    int indiceEstudiante = buscarEstudiante(
        carnesEstudiante,
        cantidadEstudiantes,
        carne
    );

    if (indiceEstudiante == -1) {
        cout << "No existe un estudiante con ese carnet.\n";
        return;
    }

    int indiceLibro = buscarLibro(
        codigosLibro,
        cantidadLibros,
        codigo
    );

    if (indiceLibro == -1) {
        cout << "No existe un libro con ese código.\n";
        return;
    }

    if (ejemplaresLibro[indiceLibro] <= 0) {
        cout << "No es posible realizar el préstamo porque no hay ejemplares disponibles.\n";
        return;
    }

    if (cantidadPrestamos >= MAX_REGISTROS) {
        cout << "No hay espacio para registrar más préstamos activos.\n";
        return;
    }

    carnesPrestamo[cantidadPrestamos] = carne;
    codigosPrestamo[cantidadPrestamos] = codigo;
    cantidadPrestamos++;

    ejemplaresLibro[indiceLibro]--;

    cout << "Préstamo registrado correctamente.\n";
}

void devolverLibro(
    const string codigosLibro[],
    const string carnesEstudiante[],
    int ejemplaresLibro[],
    string carnesPrestamo[],
    string codigosPrestamo[],
    int cantidadLibros,
    int cantidadEstudiantes,
    int& cantidadPrestamos
)
{
    cout << "\n=== DEVOLUCIÓN DE LIBRO ===\n";

    string carne = leerCampoNoVacio(
        "Ingrese el carnet del estudiante: ",
        "El carnet"
    );

    string codigo = leerCampoNoVacio(
        "Ingrese el código del libro: ",
        "El código"
    );

    int indiceEstudiante = buscarEstudiante(
        carnesEstudiante,
        cantidadEstudiantes,
        carne
    );

    if (indiceEstudiante == -1) {
        cout << "No existe un estudiante con ese carnet.\n";
        return;
    }

    int indiceLibro = buscarLibro(
        codigosLibro,
        cantidadLibros,
        codigo
    );

    if (indiceLibro == -1) {
        cout << "No existe un libro con ese código.\n";
        return;
    }

    int indicePrestamo = buscarPrestamo(
        carnesPrestamo,
        codigosPrestamo,
        cantidadPrestamos,
        carne,
        codigo
    );

    if (indicePrestamo == -1) {
        cout << "No existe un préstamo activo de ese libro para ese estudiante.\n";
        return;
    }

    ejemplaresLibro[indiceLibro]++;

    // Elimina el préstamo moviendo los registros posteriores una posición.
    for (int i = indicePrestamo; i < cantidadPrestamos - 1; i++) {
        carnesPrestamo[i] = carnesPrestamo[i + 1];
        codigosPrestamo[i] = codigosPrestamo[i + 1];
    }

    cantidadPrestamos--;

    cout << "Libro devuelto correctamente.\n";
}

void mostrarMenu() {
    cout << "\n================================================================================\n"
         << "              SISTEMA DE GESTION BIBLIOTECARIA\n"
         << "================================================================================\n"
         << "1.  Registrar libros\n"
         << "2.  Registrar estudiantes\n"
         << "3.  Consultar libros\n"
         << "4.  Consultar estudiantes\n"
         << "5.  Prestar libro\n"
         << "6.  Devolver libro\n"
         << "7.  Salir\n"
         << "================================================================================\n";
}

int main()
// Sistema de biblioteca
{
    string codigosLibro[MAX_REGISTROS];
    string titulosLibro[MAX_REGISTROS];
    string autoresLibro[MAX_REGISTROS];
    int aniosPublicacion[MAX_REGISTROS];
    string categoriasLibro[MAX_REGISTROS];
    int ejemplaresLibro[MAX_REGISTROS];

    string carnesEstudiante[MAX_REGISTROS];
    string nombresEstudiante[MAX_REGISTROS];
    string apellidosEstudiante[MAX_REGISTROS];

    string carnesPrestamo[MAX_REGISTROS];
    string codigosPrestamo[MAX_REGISTROS];

    int cantidadLibros = 0;
    int cantidadEstudiantes = 0;
    int cantidadPrestamos = 0;
    char opcion;

    do {
        mostrarMenu();

        string entrada = leerTexto("Seleccione una opción (1-7): ");

        // Solo se acepta una opción de un carácter.
        if (entrada.length() == 1) {
            opcion = entrada[0];
        } else {
            opcion = '0';
        }

        switch (opcion) {
            case '1':
                registrarLibro(
                    codigosLibro,
                    titulosLibro,
                    autoresLibro,
                    aniosPublicacion,
                    categoriasLibro,
                    ejemplaresLibro,
                    cantidadLibros
                );
                break;

            case '2':
                registrarEstudiante(
                    carnesEstudiante,
                    nombresEstudiante,
                    apellidosEstudiante,
                    cantidadEstudiantes
                );
                break;

            case '3':
                consultarLibros(
                    codigosLibro,
                    titulosLibro,
                    autoresLibro,
                    aniosPublicacion,
                    categoriasLibro,
                    ejemplaresLibro,
                    cantidadLibros
                );
                break;

            case '4':
                consultarEstudiantes(
                    carnesEstudiante,
                    nombresEstudiante,
                    apellidosEstudiante,
                    cantidadEstudiantes
                );
                break;

            case '5':
                registrarPrestamo(
                    codigosLibro,
                    carnesEstudiante,
                    ejemplaresLibro,
                    carnesPrestamo,
                    codigosPrestamo,
                    cantidadLibros,
                    cantidadEstudiantes,
                    cantidadPrestamos
                );
                break;

            case '6':
                devolverLibro(
                    codigosLibro,
                    carnesEstudiante,
                    ejemplaresLibro,
                    carnesPrestamo,
                    codigosPrestamo,
                    cantidadLibros,
                    cantidadEstudiantes,
                    cantidadPrestamos
                );
                break;

            case '7':
                cout << "Programa finalizado correctamente.\n";
                break;

            default:
                cout << "[Error]: elija una opción valida ingresando "
                     << "un numero del 1 al 7.\n";
                break;
        }

    } while (opcion != '7');

    return 0;
}
