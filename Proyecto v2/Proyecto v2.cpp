
#include <iostream>
#include <string>
using namespace std;

struct Alumno {
    string nombre;
    string matricula;
    float calif[3];
    int grupo;
};

struct Maestro {
    string nombre;
    string materia;
};

struct Grupo {
    string nombre;
    string carrera;
};

float calcularPromedio(float calif[]) {
    return (calif[0] + calif[1] + calif[2]) / 3.0;
}

int main() {
    Alumno alumnos[100];
    Maestro maestros[100];
    Grupo grupos[100];

    int numAlumnos = 0;
    int numMaestros = 0;
    int numGrupos = 0;
    int opcion;

    do {
        cout << "\n===== SISTEMA DE ALUMNOS V2 =====" << endl;
        cout << "1. Capturar alumnos" << endl;
        cout << "2. Capturar grupos y carreras" << endl;
        cout << "3. Capturar maestros" << endl;
        cout << "4. Mostrar reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (numGrupos == 0) {
                cout << "Primero registra los grupos (opcion 2)." << endl;
                break;
            }

            int cantidad;
            cout << "Cuantos alumnos deseas registrar (1-100)? ";
            cin >> cantidad;

            if (cin.fail() || cantidad < 1 || cantidad > 100) {
                cout << "Cantidad no valida." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            numAlumnos = cantidad;

            for (int i = 0; i < numAlumnos; i++) {
                cout << "\nAlumno " << i + 1 << endl;

                cout << "Nombre completo: ";
                cin >> ws;
                getline(cin, alumnos[i].nombre);

                cout << "Matricula: ";
                getline(cin, alumnos[i].matricula);

                for (int j = 0; j < 3; j++) {
                    cout << "Calificacion " << j + 1 << ": ";
                    cin >> alumnos[i].calif[j];

                    if (cin.fail()) {
                        cout << "Calificacion no valida." << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        alumnos[i].calif[j] = 0;
                    }
                }

                cout << "Grupos disponibles:" << endl;
                for (int j = 0; j < numGrupos; j++) {
                    cout << j + 1 << ". " << grupos[j].nombre << endl;
                }

                cout << "Numero de grupo: ";
                cin >> alumnos[i].grupo;

                if (cin.fail() || alumnos[i].grupo < 1 ||
                    alumnos[i].grupo > numGrupos) {
                    cout << "Grupo no valido. Se asignara el grupo 1." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    alumnos[i].grupo = 1;
                }
            }
            break;
        }

        case 2: {
            int cantidad;
            cout << "Cuantos grupos deseas registrar (1-100)? ";
            cin >> cantidad;

            if (cin.fail() || cantidad < 1 || cantidad > 100) {
                cout << "Cantidad no valida." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            numGrupos = cantidad;

            for (int i = 0; i < numGrupos; i++) {
                cout << "\nGrupo " << i + 1 << endl;

                cout << "Nombre del grupo: ";
                cin >> ws;
                getline(cin, grupos[i].nombre);

                cout << "Carrera: ";
                getline(cin, grupos[i].carrera);
            }
            break;
        }

        case 3: {
            int cantidad;
            cout << "Cuantos maestros deseas registrar (1-100)? ";
            cin >> cantidad;

            if (cin.fail() || cantidad < 1 || cantidad > 100) {
                cout << "Cantidad no valida." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            numMaestros = cantidad;

            for (int i = 0; i < numMaestros; i++) {
                cout << "\nMaestro " << i + 1 << endl;

                cout << "Nombre completo: ";
                cin >> ws;
                getline(cin, maestros[i].nombre);

                cout << "Materia: ";
                getline(cin, maestros[i].materia);
            }
            break;
        }

        case 4: {
            if (numAlumnos == 0) {
                cout << "Primero registra alumnos (opcion 1)." << endl;
                break;
            }

            cout << "\n===== PROMEDIOS =====" << endl;
            for (int i = 0; i < numAlumnos; i++) {
                cout << alumnos[i].nombre << " - Promedio: "
                    << calcularPromedio(alumnos[i].calif) << endl;
            }

            cout << "\n===== MEJOR ALUMNO POR GRUPO =====" << endl;
            for (int g = 1; g <= numGrupos; g++) {
                int mejor = -1;

                for (int i = 0; i < numAlumnos; i++) {
                    if (alumnos[i].grupo == g) {
                        if (mejor == -1 ||
                            calcularPromedio(alumnos[i].calif) >
                            calcularPromedio(alumnos[mejor].calif)) {
                            mejor = i;
                        }
                    }
                }

                cout << grupos[g - 1].nombre << ": ";
                if (mejor == -1) {
                    cout << "Sin alumnos registrados." << endl;
                }
                else {
                    cout << alumnos[mejor].nombre
                        << " - Promedio: "
                        << calcularPromedio(alumnos[mejor].calif)
                        << endl;
                }
            }

            cout << "\n===== ALUMNOS POR CARRERA =====" << endl;
            for (int g = 0; g < numGrupos; g++) {
                bool repetida = false;

                for (int j = 0; j < g; j++) {
                    if (grupos[g].carrera == grupos[j].carrera) {
                        repetida = true;
                    }
                }

                if (!repetida) {
                    int total = 0;

                    for (int i = 0; i < numAlumnos; i++) {
                        int indice = alumnos[i].grupo - 1;

                        if (indice >= 0 && indice < numGrupos &&
                            grupos[indice].carrera == grupos[g].carrera) {
                            total++;
                        }
                    }

                    cout << grupos[g].carrera << ": "
                        << total << " alumnos" << endl;
                }
            }
            break;
        }

        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }

    } while (opcion != 5);

    return 0;
}
