#include <iostream>
#include <limits>
#include <string>
#include <ctime>

using namespace std;

// Devuelve el año actual según el reloj del sistema.
int obtenerAnioActual() {
    time_t tiempoActual = time(NULL);
    tm* fechaActual = localtime(&tiempoActual);

    return fechaActual->tm_year + 1900;
}

const int MAX_REGISTROS = 100;
const int MAX_EJEMPLARES = 1000;
const int ANIO_ACTUAL = obtenerAnioActual();

// ============================================================
// Lectura y validación de entradas
// ============================================================

// Indica si todavía se puede leer de la entrada estándar.
bool entradaDisponible() {
    return !cin.fail();
}

// Quita los espacios al inicio y al final de un texto.
string recortarEspacios(const string& texto) {
    string resultado = "";
    size_t inicio = texto.find_first_not_of(" \t\r\n");

    if (inicio != string::npos) {
        size_t fin = texto.find_last_not_of(" \t\r\n");
        resultado = texto.substr(inicio, fin - inicio + 1);
    }

    return resultado;
}

// Lee una línea completa para aceptar textos con espacios.
// Si la entrada ya terminó, devuelve un texto vacío sin mostrar el mensaje.
string leerTexto(const string& mensaje) {
    string texto = "";

    if (entradaDisponible()) {
        cout << mensaje;
        getline(cin, texto);
    }

    return recortarEspacios(texto);
}

// Solicita un texto hasta que el usuario no deje el campo vacío.
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

// Verifica que la cadena no esté vacía y contenga solamente dígitos.
bool esNumeroNatural(const string& texto) {
    bool resultado = !texto.empty();
    size_t i = 0;

    while (resultado && i < texto.length()) {
        if (texto[i] < '0' || texto[i] > '9') {
            resultado = false;
        }

        i++;
    }

    return resultado;
}

// Convierte una cadena de dígitos a entero evitando desbordamientos.
// Devuelve false si el texto no es un número natural o no cabe en un int.
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

// Solicita un número entero hasta que esté entre minimo y maximo.
int leerEnteroEnRango(
    const string& mensaje,
    const string& nombreCampo,
    int minimo,
    int maximo
) {
    int numero = 0;
    bool valido = false;

    while (!valido && entradaDisponible()) {
        string entrada = leerTexto(mensaje);

        if (entradaDisponible()) {
            if (!esNumeroNatural(entrada)) {
                cout << "[Error]: " << nombreCampo
                     << " debe escribirse utilizando solamente números.\n";
            } else if (!convertirAEntero(entrada, numero) ||
                       numero < minimo || numero > maximo) {
                cout << "[Error]: " << nombreCampo << " debe estar entre "
                     << minimo << " y " << maximo << ".\n";
            } else {
                valido = true;
            }
        }
    }

    return numero;
}

// Solicita una categoría válida y devuelve su texto correspondiente.
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

// Convierte la entrada de un menú en un carácter de opción.
// Solo se acepta una opción de un carácter; cualquier otra entrada es '0'.
char obtenerOpcion(const string& entrada) {
    char opcion = '0';

    if (entrada.length() == 1) {
        opcion = entrada[0];
    }

    return opcion;
}

// Pide una respuesta S/N y devuelve true si el usuario confirma.
bool leerConfirmacion(const string& mensaje) {
    bool confirmado = false;
    bool valido = false;

    while (!valido && entradaDisponible()) {
        string respuesta = leerTexto(mensaje);

        if (respuesta == "S" || respuesta == "s") {
            confirmado = true;
            valido = true;
        } else if (respuesta == "N" || respuesta == "n") {
            valido = true;
        } else if (entradaDisponible()) {
            cout << "[Error]: responda S para sí o N para no.\n";
        }
    }

    return confirmado;
}

// ============================================================
// Búsquedas
// ============================================================

// Devuelve la posición de un valor dentro de un arreglo, o -1 si no existe.
// Se usa para buscar libros por código y estudiantes por carné.
int buscarPosicion(
    const string valores[],
    int cantidad,
    const string& valorBuscado
) {
    int posicion = -1;
    int i = 0;

    while (i < cantidad && posicion == -1) {
        if (valores[i] == valorBuscado) {
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
// Registro
// ============================================================

// Pide un valor nuevo (código o carné) hasta que no esté repetido.
string leerValorUnico(
    const string valores[],
    int cantidad,
    const string& mensaje,
    const string& nombreCampo,
    const string& mensajeRepetido
) {
    string valor = "";
    bool valido = false;

    while (!valido && entradaDisponible()) {
        valor = leerCampoNoVacio(mensaje, nombreCampo);

        if (entradaDisponible()) {
            if (buscarPosicion(valores, cantidad, valor) != -1) {
                cout << "[Error]: " << mensajeRepetido << '\n';
            } else {
                valido = true;
            }
        }
    }

    return valor;
}

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
        cout << "[Error]: no hay espacio para registrar más libros.\n";
    } else {
        // En C++ el primer índice válido es 0.
        int posicion = cantidadLibros;

        cout << "\n=== REGISTRO DE NUEVO LIBRO ===\n";

        codigosLibro[posicion] = leerValorUnico(
            codigosLibro,
            cantidadLibros,
            "Ingrese el código del libro: ",
            "El código",
            "ya existe un libro con ese código."
        );
        titulosLibro[posicion] = leerCampoNoVacio("Ingrese el título: ", "El título");
        autoresLibro[posicion] = leerCampoNoVacio("Ingrese el autor: ", "El autor");

        aniosPublicacion[posicion] = leerEnteroEnRango(
            "Ingrese el año de publicación: ",
            "El año de publicación",
            1,
            ANIO_ACTUAL
        );
        categoriasLibro[posicion] = leerCategoria();
        ejemplaresLibro[posicion] = leerEnteroEnRango(
            "Ingrese la cantidad de ejemplares: ",
            "La cantidad de ejemplares",
            1,
            MAX_EJEMPLARES
        );

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
        cout << "[Error]: no hay espacio para registrar más estudiantes.\n";
    } else {
        int posicion = cantidadEstudiantes;

        cout << "\n=== REGISTRO DE NUEVO ESTUDIANTE ===\n";

        carnesEstudiante[posicion] = leerValorUnico(
            carnesEstudiante,
            cantidadEstudiantes,
            "Ingrese el carné del estudiante: ",
            "El carné",
            "ya existe un estudiante con ese carné."
        );
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
// Consultas
// ============================================================

// Muestra la información de un libro específico.
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
         << "Ejemplares disponibles: " << ejemplaresLibro[posicion] << '\n'
         << "--------------------------------\n";
}

// Muestra todos los libros o busca un libro por código.
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
                            int posicion = buscarPosicion(codigosLibro, cantidadLibros, codigoBuscado);

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
                                cout << "[Error]: no existe un libro con ese código.\n";
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

// Muestra la información de un estudiante específico.
void mostrarEstudiante(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int posicion
) {
    cout << "Estudiante número " << posicion + 1 << '\n'
         << "Carné: " << carnesEstudiante[posicion] << '\n'
         << "Nombres: " << nombresEstudiante[posicion] << '\n'
         << "Apellidos: " << apellidosEstudiante[posicion] << '\n'
         << "-----------------------------------\n";
}

// Muestra todos los estudiantes o busca un estudiante por carné.
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
                 << "2. Buscar estudiante por carné\n"
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
                            "Ingrese el carné del estudiante que desea buscar: ",
                            "El carné"
                        );

                        if (entradaDisponible()) {
                            int posicion = buscarPosicion(carnesEstudiante, cantidadEstudiantes, carneBuscado);

                            if (posicion != -1) {
                                mostrarEstudiante(
                                    carnesEstudiante,
                                    nombresEstudiante,
                                    apellidosEstudiante,
                                    posicion
                                );
                            } else {
                                cout << "[Error]: no existe un estudiante con ese carné.\n";
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

// Muestra los préstamos activos con los datos del estudiante y del libro.
void consultarPrestamos(
    const string codigosLibro[],
    const string titulosLibro[],
    int cantidadLibros,
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes,
    const string carnesPrestamo[],
    const string codigosPrestamo[],
    int cantidadPrestamos
) {
    if (cantidadPrestamos == 0) {
        cout << "No hay préstamos activos.\n";
    } else {
        cout << "\n===== PRÉSTAMOS ACTIVOS (" << cantidadPrestamos << ") =====\n";

        for (int i = 0; i < cantidadPrestamos; i++) {
            int indiceEstudiante = buscarPosicion(carnesEstudiante, cantidadEstudiantes, carnesPrestamo[i]);
            int indiceLibro = buscarPosicion(codigosLibro, cantidadLibros, codigosPrestamo[i]);

            cout << "Préstamo número " << i + 1 << '\n'
                 << "Estudiante: " << carnesPrestamo[i] << " - "
                 << nombresEstudiante[indiceEstudiante] << ' '
                 << apellidosEstudiante[indiceEstudiante] << '\n'
                 << "Libro: " << codigosPrestamo[i] << " - "
                 << titulosLibro[indiceLibro] << '\n'
                 << "--------------------------------\n";
        }
    }
}

// ============================================================
// Préstamos y devoluciones
// ============================================================

// Pide un carné, busca al estudiante y muestra su nombre.
// Devuelve su posición, o -1 si no existe o si terminó la entrada.
int seleccionarEstudiante(
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes
) {
    int posicion = -1;

    string carne = leerCampoNoVacio(
        "Ingrese el carné del estudiante: ",
        "El carné"
    );

    if (entradaDisponible()) {
        posicion = buscarPosicion(carnesEstudiante, cantidadEstudiantes, carne);

        if (posicion == -1) {
            cout << "[Error]: no existe un estudiante con ese carné.\n";
        } else {
            cout << "Estudiante: " << nombresEstudiante[posicion] << ' '
                 << apellidosEstudiante[posicion] << '\n';
        }
    }

    return posicion;
}

// Pide un código, busca el libro y muestra su título y existencias.
// Devuelve su posición, o -1 si no existe o si terminó la entrada.
int seleccionarLibro(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    const int ejemplaresLibro[],
    int cantidadLibros
) {
    int posicion = -1;

    string codigo = leerCampoNoVacio(
        "Ingrese el código del libro: ",
        "El código"
    );

    if (entradaDisponible()) {
        posicion = buscarPosicion(codigosLibro, cantidadLibros, codigo);

        if (posicion == -1) {
            cout << "[Error]: no existe un libro con ese código.\n";
        } else {
            cout << "Libro: " << titulosLibro[posicion] << " - "
                 << autoresLibro[posicion]
                 << " (ejemplares disponibles: " << ejemplaresLibro[posicion] << ")\n";
        }
    }

    return posicion;
}

// Agrega un préstamo activo al final de los arreglos de préstamos.
void agregarPrestamo(
    string carnesPrestamo[],
    string codigosPrestamo[],
    int& cantidadPrestamos,
    const string& carne,
    const string& codigo
) {
    carnesPrestamo[cantidadPrestamos] = carne;
    codigosPrestamo[cantidadPrestamos] = codigo;
    cantidadPrestamos++;
}

// Elimina un préstamo activo moviendo los registros posteriores una posición.
void eliminarPrestamo(
    string carnesPrestamo[],
    string codigosPrestamo[],
    int& cantidadPrestamos,
    int posicion
) {
    for (int i = posicion; i < cantidadPrestamos - 1; i++) {
        carnesPrestamo[i] = carnesPrestamo[i + 1];
        codigosPrestamo[i] = codigosPrestamo[i + 1];
    }

    cantidadPrestamos--;
}

// Presta un libro a un estudiante si hay ejemplares disponibles.
// Busca al estudiante y al libro, muestra sus datos y pide confirmación.
// Un estudiante no puede tener dos ejemplares del mismo libro a la vez.
void registrarPrestamo(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    int ejemplaresLibro[],
    int cantidadLibros,
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes,
    string carnesPrestamo[],
    string codigosPrestamo[],
    int& cantidadPrestamos
) {
    cout << "\n=== PRÉSTAMO DE LIBRO ===\n";

    if (cantidadEstudiantes == 0) {
        cout << "[Error]: no hay estudiantes registrados para realizar préstamos.\n";
    } else if (cantidadLibros == 0) {
        cout << "[Error]: no hay libros registrados para realizar préstamos.\n";
    } else {
        int indiceLibro = -1;
        int indiceEstudiante = seleccionarEstudiante(
            carnesEstudiante,
            nombresEstudiante,
            apellidosEstudiante,
            cantidadEstudiantes
        );

        if (indiceEstudiante != -1) {
            indiceLibro = seleccionarLibro(
                codigosLibro,
                titulosLibro,
                autoresLibro,
                ejemplaresLibro,
                cantidadLibros
            );
        }

        if (indiceLibro != -1) {
            int prestamoExistente = buscarPrestamo(
                carnesPrestamo,
                codigosPrestamo,
                cantidadPrestamos,
                carnesEstudiante[indiceEstudiante],
                codigosLibro[indiceLibro]
            );

            if (prestamoExistente != -1) {
                cout << "[Error]: el estudiante ya tiene prestado un ejemplar de este libro.\n";
            } else if (ejemplaresLibro[indiceLibro] <= 0) {
                cout << "[Error]: no es posible realizar el préstamo porque no hay ejemplares disponibles.\n";
            } else if (cantidadPrestamos >= MAX_REGISTROS) {
                cout << "[Error]: no hay espacio para registrar más préstamos activos.\n";
            } else if (leerConfirmacion("¿Confirmar el préstamo? (S/N): ")) {
                agregarPrestamo(
                    carnesPrestamo,
                    codigosPrestamo,
                    cantidadPrestamos,
                    carnesEstudiante[indiceEstudiante],
                    codigosLibro[indiceLibro]
                );
                ejemplaresLibro[indiceLibro]--;

                cout << "¡Préstamo registrado correctamente!\n";
            } else if (entradaDisponible()) {
                cout << "Préstamo cancelado.\n";
            }
        }
    }
}

// Registra la devolución de un libro prestado.
// Busca al estudiante, al libro y el préstamo activo, y pide confirmación.
void devolverLibro(
    const string codigosLibro[],
    const string titulosLibro[],
    const string autoresLibro[],
    int ejemplaresLibro[],
    int cantidadLibros,
    const string carnesEstudiante[],
    const string nombresEstudiante[],
    const string apellidosEstudiante[],
    int cantidadEstudiantes,
    string carnesPrestamo[],
    string codigosPrestamo[],
    int& cantidadPrestamos
) {
    cout << "\n=== DEVOLUCIÓN DE LIBRO ===\n";

    if (cantidadPrestamos == 0) {
        cout << "[Error]: no hay préstamos activos para devolver.\n";
    } else {
        int indiceLibro = -1;
        int indiceEstudiante = seleccionarEstudiante(
            carnesEstudiante,
            nombresEstudiante,
            apellidosEstudiante,
            cantidadEstudiantes
        );

        if (indiceEstudiante != -1) {
            indiceLibro = seleccionarLibro(
                codigosLibro,
                titulosLibro,
                autoresLibro,
                ejemplaresLibro,
                cantidadLibros
            );
        }

        if (indiceLibro != -1) {
            int indicePrestamo = buscarPrestamo(
                carnesPrestamo,
                codigosPrestamo,
                cantidadPrestamos,
                carnesEstudiante[indiceEstudiante],
                codigosLibro[indiceLibro]
            );

            if (indicePrestamo == -1) {
                cout << "[Error]: no existe un préstamo activo de ese libro para ese estudiante.\n";
            } else if (leerConfirmacion("¿Confirmar la devolución? (S/N): ")) {
                eliminarPrestamo(
                    carnesPrestamo,
                    codigosPrestamo,
                    cantidadPrestamos,
                    indicePrestamo
                );
                ejemplaresLibro[indiceLibro]++;

                cout << "¡Libro devuelto correctamente!\n";
            } else if (entradaDisponible()) {
                cout << "Devolución cancelada.\n";
            }
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
         << "7.  Ver préstamos activos\n"
         << "8.  Salir\n"
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

        opcion = obtenerOpcion(leerTexto("Seleccione una opción (1-8): "));

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
                        titulosLibro,
                        autoresLibro,
                        ejemplaresLibro,
                        cantidadLibros,
                        carnesEstudiante,
                        nombresEstudiante,
                        apellidosEstudiante,
                        cantidadEstudiantes,
                        carnesPrestamo,
                        codigosPrestamo,
                        cantidadPrestamos
                    );
                    break;

                case '6':
                    devolverLibro(
                        codigosLibro,
                        titulosLibro,
                        autoresLibro,
                        ejemplaresLibro,
                        cantidadLibros,
                        carnesEstudiante,
                        nombresEstudiante,
                        apellidosEstudiante,
                        cantidadEstudiantes,
                        carnesPrestamo,
                        codigosPrestamo,
                        cantidadPrestamos
                    );
                    break;

                case '7':
                    consultarPrestamos(
                        codigosLibro,
                        titulosLibro,
                        cantidadLibros,
                        carnesEstudiante,
                        nombresEstudiante,
                        apellidosEstudiante,
                        cantidadEstudiantes,
                        carnesPrestamo,
                        codigosPrestamo,
                        cantidadPrestamos
                    );
                    break;

                case '8':
                    cout << "Programa finalizado correctamente.\n";
                    break;

                default:
                    cout << "[Error]: elija una opción válida ingresando "
                         << "un número del 1 al 8.\n";
                    break;
            }
        }
    } while (opcion != '8' && entradaDisponible());

    if (!entradaDisponible()) {
        cout << "\n\n[Fin de entrada]: el programa ha finalizado.\n";
    }

    return 0;
}
