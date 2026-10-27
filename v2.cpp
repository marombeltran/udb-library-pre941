#include <iostream>
#include <limits>
#include <string>
#include <ctime>

using namespace std;

// Devuelve el año actual según el reloj del sistema.
int obtenerAnioActual() {
    time_t tiempoActual = time(nullptr);
    tm* fechaActual = localtime(&tiempoActual);

    return fechaActual->tm_year + 1900;
}

const int MAX_REGISTROS = 100;
const int ANIO_ACTUAL = obtenerAnioActual();

// ============================================================
// Lectura y validación de entradas
// ============================================================

// Indica si todavía se puede leer de la entrada estándar.
bool entradaDisponible() {
    return !cin.fail();
}

// Lee una linea completa para aceptar textos con espacios.
// Si la entrada ya terminó, devuelve un texto vacío sin mostrar el mensaje.
string leerTexto(const string& mensaje) {
    string texto = "";

    if (entradaDisponible()) {
        cout << mensaje;
        getline(cin, texto);
    }

    return texto;
}

// Solicita un texto hasta que el usuario no deje el campo vacio.
string leerCampoNoVacio(const string& mensaje, const string& nombreCampo) {
    string texto = "";
    bool valido = false;

    while (!valido && entradaDisponible()) {
        texto = leerTexto(mensaje);

        if (!texto.empty()) {
            valido = true;
        } else if (entradaDisponible()) {
            cout << "[Error]: " << nombreCampo << " no puede quedar vacío.\n";
        }
    }

    return texto;
}

// Verifica que la cadena no este vacia y contenga solamente digitos.
bool esNumeroNatural(const string& texto) {
    bool resultado;
    size_t i;
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

// Convierte una cadena de digitos a entero evitando desbordamientos.
// Devuelve false si el texto no es un numero natural o no cabe en un int.
bool convertirAEntero(const string& texto, int& numero) {
    bool valido = esNumeroNatural(texto);
    long long valor = 0;
    size_t i = 0;

    while (valido && i < texto.length()) {
        valor = valor * 10 + (texto[i] - '0');

        if (valor > numeric_limits<int>::max()) {
            valido = false;
        }

        i++;
    }

    if (valido) {
        numero = static_cast<int>(valor);
    }

    return valido;
}

// Solicita y valida el anio de publicacion.
int leerAnioPublicacion() {
    int anio = 0;
    bool valido = false;

    while (!valido && entradaDisponible()) {
        string entrada = leerTexto("Ingrese el año de publicación: ");

        if (entradaDisponible()) {
            if (!esNumeroNatural(entrada)) {
                cout << "[Error]: el año debe escribirse utilizando solamente números.\n";
            } else if (!convertirAEntero(entrada, anio)) {
                cout << "[Error]: el año ingresado es demasiado grande.\n";
            } else if (anio <= 0 || anio > ANIO_ACTUAL) {
                cout << "[Error]: el año debe ser mayor que 0 y menor o igual que "
                     << ANIO_ACTUAL << ".\n";
            } else {
                valido = true;
            }
        }
    }

    return anio;
}

// Solicita una categoria valida y devuelve su texto correspondiente.
string leerCategoria() {
    string categoria = "";

    while (categoria.empty() && entradaDisponible()) {
        cout << "Seleccione la categoría:\n"
             << "1. Literatura\n"
             << "2. Ciencias\n"
             << "3. Informática\n"
             << "4. Sociales\n"
             << "5. Otra\n";

        string opcion = leerTexto("Ingrese un número del 1 al 5: ");

        if (opcion == "1") {
            categoria = "Literatura";
        } else if (opcion == "2") {
            categoria = "Ciencias";
        } else if (opcion == "3") {
            categoria = "Informática";
        } else if (opcion == "4") {
            categoria = "Sociales";
        } else if (opcion == "5") {
            categoria = "Otra";
        } else if (entradaDisponible()) {
            cout << "[Error]: elija una categoría válida ingresando un número del 1 al 5.\n";
        }
    }

    return categoria;
}

// Solicita y valida la cantidad de ejemplares.
int leerCantidadEjemplares() {
    int ejemplares = 0;
    bool valido = false;

    while (!valido && entradaDisponible()) {
        string entrada = leerTexto("Ingrese la cantidad de ejemplares: ");

        if (entradaDisponible()) {
            if (!esNumeroNatural(entrada)) {
                cout << "[Error]: la cantidad debe escribirse utilizando solamente números.\n";
            } else if (!convertirAEntero(entrada, ejemplares)) {
                cout << "[Error]: la cantidad ingresada es demasiado grande.\n";
            } else if (ejemplares <= 0) {
                cout << "[Error]: la cantidad de ejemplares debe ser mayor que 0.\n";
            } else {
                valido = true;
            }
        }
    }

    return ejemplares;
}

// Convierte la entrada de un menú en un carácter de opción.
// Solo se acepta una opción de un carácter; cualquier otra entrada es '0'.
char obtenerOpcion(const string& entrada) {
    char opcion = '0';

    if (entrada.length() == 1) {
        opcion = entrada[0];
    }

    return opcion;
}

// ============================================================
// Registro
// ============================================================

// Registra un libro en los arreglos paralelos.
void registrarLibro(
    string codigosLibro[],
    string titulosLibro[],
    string autoresLibro[],
    int aniosPublicacion[],
    string categoriasLibro[],
    int ejemplaresLibro[],
    int& cantidadLibros
) {
    if (cantidadLibros >= MAX_REGISTROS) {
        cout << "No hay espacio para registrar más libros.\n";
    } else {
        // En C++ el primer indice valido es 0.
        int posicion = cantidadLibros;

        cout << "\n=== REGISTRO DE NUEVO LIBRO ===\n";

        codigosLibro[posicion] = leerCampoNoVacio("Ingrese el código del libro: ", "El código");
        titulosLibro[posicion] = leerCampoNoVacio("Ingrese el título: ", "El título");
        autoresLibro[posicion] = leerCampoNoVacio("Ingrese el autor: ", "El autor");

        aniosPublicacion[posicion] = leerAnioPublicacion();
        categoriasLibro[posicion] = leerCategoria();
        ejemplaresLibro[posicion] = leerCantidadEjemplares();

        // Solo se confirma el registro si se completaron todos los datos.
        if (entradaDisponible()) {
            cantidadLibros++;
            cout << "\n¡Libro registrado correctamente!\n";
        }
    }
}

// Registra un estudiante en los arreglos paralelos.
void registrarEstudiante(
    string carnesEstudiante[],
    string nombresEstudiante[],
    string apellidosEstudiante[],
    int& cantidadEstudiantes
) {
    if (cantidadEstudiantes >= MAX_REGISTROS) {
        cout << "No hay espacio para registrar más estudiantes.\n";
    } else {
        int posicion = cantidadEstudiantes;

        cout << "\n=== REGISTRO DE NUEVO ESTUDIANTE ===\n";

        carnesEstudiante[posicion] = leerCampoNoVacio("Ingrese el carnet del estudiante: ", "El carnet");
        nombresEstudiante[posicion] = leerCampoNoVacio("Ingrese los nombres: ", "Los nombres");
        apellidosEstudiante[posicion] = leerCampoNoVacio("Ingrese los apellidos: ", "Los apellidos");

        // Solo se confirma el registro si se completaron todos los datos.
        if (entradaDisponible()) {
            cantidadEstudiantes++;
            cout << "\n¡Estudiante registrado correctamente!\n";
        }
    }
}

// ============================================================
// Búsquedas
// ============================================================

// Devuelve la posición del libro con ese código, o -1 si no existe.
int buscarLibro(
    const string codigosLibro[],
    int cantidadLibros,
    const string& codigo
) {
    int posicion = -1;
    int i = 0;

    while (i < cantidadLibros && posicion == -1) {
        if (codigosLibro[i] == codigo) {
            posicion = i;
        }

        i++;
    }

    return posicion;
}

// Devuelve la posición del estudiante con ese carnet, o -1 si no existe.
int buscarEstudiante(
    const string carnesEstudiante[],
    int cantidadEstudiantes,
    const string& carne
) {
    int posicion = -1;
    int i = 0;

    while (i < cantidadEstudiantes && posicion == -1) {
        if (carnesEstudiante[i] == carne) {
            posicion = i;
        }

        i++;
    }

    return posicion;
}

// Devuelve la posición del préstamo activo de ese estudiante y libro, o -1.
int buscarPrestamo(
    const string carnesPrestamo[],
    const string codigosPrestamo[],
    int cantidadPrestamos,
    const string& carne,
    const string& codigo
) {
    int posicion = -1;
    int i = 0;

    while (i < cantidadPrestamos && posicion == -1) {
        if (carnesPrestamo[i] == carne &&
            codigosPrestamo[i] == codigo) {
            posicion = i;
        }

        i++;
    }

    return posicion;
}

// ============================================================
// Consultas
// ============================================================

// Muestra la informacion de un libro especifico.
void mostrarLibro(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    const int aniosPublicacion[],
    const string categoriasLibro[],
    const int ejemplaresLibro[],
    int posicion
) {
    cout << "Libro número " << posicion + 1 << '\n'
         << "Código: " << codigosLibro[posicion] << '\n'
         << "Título: " << titulosLibro[posicion] << '\n'
         << "Autor: " << autoresLibro[posicion] << '\n'
         << "Año de publicación: " << aniosPublicacion[posicion] << '\n'
         << "Categoría: " << categoriasLibro[posicion] << '\n'
         << "Ejemplares: " << ejemplaresLibro[posicion] << '\n'
         << "--------------------------------\n";
}

// Muestra todos los libros o busca un libro por codigo.
void consultarLibros(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    const int aniosPublicacion[],
    const string categoriasLibro[],
    const int ejemplaresLibro[],
    int cantidadLibros
) {
    if (cantidadLibros == 0) {
        cout << "No hay libros registrados.\n";
    } else {
        char opcionConsulta;

        do {
            cout << "\n=== CONSULTA DE LIBROS ===\n"
                 << "1. Ver todos los libros\n"
                 << "2. Buscar libro por código\n"
                 << "3. Regresar al menú principal\n";

            opcionConsulta = obtenerOpcion(leerTexto("Ingrese una opción: "));

            if (entradaDisponible()) {
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

                        if (entradaDisponible()) {
                            int posicion = buscarLibro(codigosLibro, cantidadLibros, codigoBuscado);

                            if (posicion != -1) {
                                mostrarLibro(
                                    codigosLibro,
                                    titulosLibro,
                                    autoresLibro,
                                    aniosPublicacion,
                                    categoriasLibro,
                                    ejemplaresLibro,
                                    posicion
                                );
                            } else {
                                cout << "No se encontró un libro con ese código.\n";
                            }
                        }
                        break;
                    }

                    case '3':
                        break;

                    default:
                        cout << "[Error]: elija una opción válida del 1 al 3.\n";
                        break;
                }
            }
        } while (opcionConsulta != '3' && entradaDisponible());
    }
}

// Muestra la informacion de un estudiante especifico.
void mostrarEstudiante(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int posicion
) {
    cout << "Estudiante número " << posicion + 1 << '\n'
         << "Carnet: " << carnesEstudiante[posicion] << '\n'
         << "Nombres: " << nombresEstudiante[posicion] << '\n'
         << "Apellidos: " << apellidosEstudiante[posicion] << '\n'
         << "-----------------------------------\n";
}

// Muestra todos los estudiantes o busca un estudiante por carnet.
void consultarEstudiantes(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes
) {
    if (cantidadEstudiantes == 0) {
        cout << "No hay estudiantes registrados.\n";
    } else {
        char opcionConsulta;

        do {
            cout << "\n=== CONSULTA DE ESTUDIANTES ===\n"
                 << "1. Ver todos los estudiantes\n"
                 << "2. Buscar estudiante por carnet\n"
                 << "3. Regresar al menú principal\n";

            opcionConsulta = obtenerOpcion(leerTexto("Ingrese una opción: "));

            if (entradaDisponible()) {
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

                        if (entradaDisponible()) {
                            int posicion = buscarEstudiante(carnesEstudiante, cantidadEstudiantes, carneBuscado);

                            if (posicion != -1) {
                                mostrarEstudiante(
                                    carnesEstudiante,
                                    nombresEstudiante,
                                    apellidosEstudiante,
                                    posicion
                                );
                            } else {
                                cout << "No se encontró un estudiante con ese carnet.\n";
                            }
                        }
                        break;
                    }

                    case '3':
                        break;

                    default:
                        cout << "[Error]: elija una opción válida del 1 al 3.\n";
                        break;
                }
            }
        } while (opcionConsulta != '3' && entradaDisponible());
    }
}

// ============================================================
// Préstamos y devoluciones
// ============================================================

// Presta un libro a un estudiante si hay ejemplares disponibles.
void registrarPrestamo(
    const string codigosLibro[],
    const string carnesEstudiante[],
    int ejemplaresLibro[],
    string carnesPrestamo[],
    string codigosPrestamo[],
    int cantidadLibros,
    int cantidadEstudiantes,
    int& cantidadPrestamos
) {
    cout << "\n=== PRÉSTAMO DE LIBRO ===\n";

    string carne = leerCampoNoVacio(
        "Ingrese el carnet del estudiante: ",
        "El carnet"
    );

    string codigo = leerCampoNoVacio(
        "Ingrese el código del libro: ",
        "El código"
    );

    if (entradaDisponible()) {
        int indiceEstudiante = buscarEstudiante(
            carnesEstudiante,
            cantidadEstudiantes,
            carne
        );

        int indiceLibro = buscarLibro(
            codigosLibro,
            cantidadLibros,
            codigo
        );

        if (indiceEstudiante == -1) {
            cout << "No existe un estudiante con ese carnet.\n";
        } else if (indiceLibro == -1) {
            cout << "No existe un libro con ese código.\n";
        } else if (ejemplaresLibro[indiceLibro] <= 0) {
            cout << "No es posible realizar el préstamo porque no hay ejemplares disponibles.\n";
        } else if (cantidadPrestamos >= MAX_REGISTROS) {
            cout << "No hay espacio para registrar más préstamos activos.\n";
        } else {
            carnesPrestamo[cantidadPrestamos] = carne;
            codigosPrestamo[cantidadPrestamos] = codigo;
            cantidadPrestamos++;

            ejemplaresLibro[indiceLibro]--;

            cout << "Préstamo registrado correctamente.\n";
        }
    }
}

// Registra la devolución de un libro prestado.
void devolverLibro(
    const string codigosLibro[],
    const string carnesEstudiante[],
    int ejemplaresLibro[],
    string carnesPrestamo[],
    string codigosPrestamo[],
    int cantidadLibros,
    int cantidadEstudiantes,
    int& cantidadPrestamos
) {
    cout << "\n=== DEVOLUCIÓN DE LIBRO ===\n";

    string carne = leerCampoNoVacio(
        "Ingrese el carnet del estudiante: ",
        "El carnet"
    );

    string codigo = leerCampoNoVacio(
        "Ingrese el código del libro: ",
        "El código"
    );

    if (entradaDisponible()) {
        int indiceEstudiante = buscarEstudiante(
            carnesEstudiante,
            cantidadEstudiantes,
            carne
        );

        int indiceLibro = buscarLibro(
            codigosLibro,
            cantidadLibros,
            codigo
        );

        int indicePrestamo = buscarPrestamo(
            carnesPrestamo,
            codigosPrestamo,
            cantidadPrestamos,
            carne,
            codigo
        );

        if (indiceEstudiante == -1) {
            cout << "No existe un estudiante con ese carnet.\n";
        } else if (indiceLibro == -1) {
            cout << "No existe un libro con ese código.\n";
        } else if (indicePrestamo == -1) {
            cout << "No existe un préstamo activo de ese libro para ese estudiante.\n";
        } else {
            ejemplaresLibro[indiceLibro]++;

            // Elimina el préstamo moviendo los registros posteriores una posición.
            for (int i = indicePrestamo; i < cantidadPrestamos - 1; i++) {
                carnesPrestamo[i] = carnesPrestamo[i + 1];
                codigosPrestamo[i] = codigosPrestamo[i + 1];
            }

            cantidadPrestamos--;

            cout << "Libro devuelto correctamente.\n";
        }
    }
}

// ============================================================
// Menú y programa principal
// ============================================================

// Muestra las opciones del menú principal.
void mostrarMenu() {
    cout << "\n================================================================================\n"
         << "              SISTEMA DE GESTIÓN BIBLIOTECARIA\n"
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

// Sistema de biblioteca
int main() {
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

        opcion = obtenerOpcion(leerTexto("Seleccione una opción (1-7): "));

        if (entradaDisponible()) {
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
                    cout << "[Error]: elija una opción válida ingresando "
                         << "un número del 1 al 7.\n";
                    break;
            }
        }
    } while (opcion != '7' && entradaDisponible());

    if (!entradaDisponible()) {
        cout << "\n\n[Fin de entrada]: el programa ha finalizado.\n";
    }

    return 0;
}
