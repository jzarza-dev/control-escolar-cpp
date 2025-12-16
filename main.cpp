/* UVM - Programacion orientada a objetos Proyecto integrador etapa 3 */ 
/* Joshua Zarza Sanchez – Matricula: 940073114 */ 
/* Profesor Saul Santiago Rivera */ 

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// --------------------
// Clase base Persona
// --------------------
class Persona {
public:
    int id;
    string nombre;
    string apellido;
    string sexo;
    int edad;

    Persona() : id(0), edad(0) {}
    virtual ~Persona() = default;
};

// --------------------
// Profesor (hereda Persona)
// --------------------
class Profesor : public Persona {
public:
    string titulo;
    string noCedula;

    void mostrar() const {
        cout << "\n--- PROFESOR ---\n";
        cout << "ID: " << id << "\n";
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "Sexo: " << sexo << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Titulo: " << titulo << "\n";
        cout << "Cedula: " << noCedula << "\n";
    }
};

// --------------------
// Materia
// --------------------
class Materia {
public:
    int id;
    string nombre;
    int creditos;
    int profesorId; // referencia por ID

    Materia() : id(0), creditos(0), profesorId(0) {}

    // Mostrar requiere lista de profesores para resolver el nombre
    void mostrar(const vector<Profesor>& profesores) const {
        cout << "\n--- MATERIA ---\n";
        cout << "ID: " << id << "\n";
        cout << "Nombre: " << nombre << "\n";
        cout << "Creditos: " << creditos << "\n";

        // buscar profesor por ID
        bool found = false;
        for (const auto& p : profesores) {
            if (p.id == profesorId) {
                cout << "Profesor asignado: " << p.nombre << " " << p.apellido << "\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "Profesor asignado: (No encontrado)\n";
    }
};

// --------------------
// Alumno (hereda Persona)
// --------------------
class Alumno : public Persona {
public:
    int semestre;
    vector<int> materiaIds; // IDs de materias

    Alumno() : semestre(0) {}

    void mostrar(const vector<Materia>& materias, const vector<Profesor>& profesores) const {
        cout << "\n--- ALUMNO ---\n";
        cout << "ID: " << id << "\n";
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "Sexo: " << sexo << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Semestre: " << semestre << "\n";

        cout << "\nMaterias inscritas:\n";
        if (materiaIds.empty()) {
            cout << "(Sin materias)\n";
        } else {
            for (int mid : materiaIds) {
                // buscar materia
                bool found = false;
                for (const auto& m : materias) {
                    if (m.id == mid) {
                        // mostrar nombre materia y profesor asignado
                        cout << "- " << m.nombre << " (Profesor: ";
                        bool pfound = false;
                        for (const auto& p : profesores) {
                            if (p.id == m.profesorId) {
                                cout << p.nombre << " " << p.apellido;
                                pfound = true;
                                break;
                            }
                        }
                        if (!pfound) cout << "No encontrado";
                        cout << ")\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "- Materia ID " << mid << " (No encontrada)\n";
            }
        }
    }
};

// --------------------
// Funciones auxiliares de búsqueda
// --------------------
Profesor* buscarProfesor(vector<Profesor>& profesores, int id) {
    for (auto &p : profesores) if (p.id == id) return &p;
    return nullptr;
}

Materia* buscarMateria(vector<Materia>& materias, int id) {
    for (auto &m : materias) if (m.id == id) return &m;
    return nullptr;
}

Alumno* buscarAlumno(vector<Alumno>& alumnos, int id) {
    for (auto &a : alumnos) if (a.id == id) return &a;
    return nullptr;
}

// --------------------
// Lectura segura de int (evita problemas con getline)
// --------------------
int leerEntero(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Entrada invalida. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string leerLinea(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

// --------------------
// MAIN
// --------------------
int main() {
    vector<Profesor> profesores;
    vector<Materia> materias;
    vector<Alumno> alumnos;

    cout << "=== CAPTURA DE 3 PROFESORES ===\n";
    for (int i = 0; i < 3; ++i) {
        Profesor p;
        p.id = i + 1;
        p.nombre = leerLinea("Nombre: ");
        p.apellido = leerLinea("Apellido: ");
        p.sexo = leerLinea("Sexo: ");
        p.edad = leerEntero("Edad: ");
        p.titulo = leerLinea("Titulo/Profesion: ");
        p.noCedula = leerLinea("No. de Cedula: ");
        profesores.push_back(p);
    }

    cout << "\n=== CAPTURA DE 4 MATERIAS ===\n";
    for (int i = 0; i < 4; ++i) {
        Materia m;
        m.id = i + 1;
        m.nombre = leerLinea("Nombre de la materia: ");
        m.creditos = leerEntero("Creditos: ");

        // Mostrar profesores disponibles
        cout << "Profesores disponibles:\n";
        for (const auto& p : profesores) {
            cout << "  ID " << p.id << " -> " << p.nombre << " " << p.apellido << "\n";
        }
        m.profesorId = leerEntero("ID del profesor que imparte la materia: ");

        materias.push_back(m);
    }

    cout << "\n=== CAPTURA DE 3 ALUMNOS (cada uno con 2 materias) ===\n";
    for (int i = 0; i < 3; ++i) {
        Alumno a;
        a.id = i + 1;
        a.nombre = leerLinea("Nombre: ");
        a.apellido = leerLinea("Apellido: ");
        a.sexo = leerLinea("Sexo: ");
        a.edad = leerEntero("Edad: ");
        a.semestre = leerEntero("Semestre: ");

        cout << "Materias disponibles:\n";
        for (const auto& m : materias) {
            cout << "  ID " << m.id << " -> " << m.nombre << "\n";
        }

        int asignadas = 0;
        while (asignadas < 2) {
            int mid = leerEntero("Ingrese ID de materia a asignar (2 materias por alumno): ");
            // validar existencia
            if (buscarMateria(materias, mid)) {
                a.materiaIds.push_back(mid);
                asignadas++;
            } else {
                cout << "ID de materia no valido, intente de nuevo.\n";
            }
        }
        alumnos.push_back(a);
    }

    // Menu de visualización
    cout << "\n=== MENU DE VISUALIZACION ===\n";
    cout << "Desea visualizar: 1. Profesor  2. Materia  3. Alumno\n";
    int opcion = leerEntero("Opcion: ");
    int id = leerEntero("Ingrese ID: ");

    switch (opcion) {
        case 1: {
            Profesor* p = buscarProfesor(profesores, id);
            if (p) p->mostrar();
            else cout << "Profesor no encontrado.\n";
            break;
        }
        case 2: {
            Materia* m = buscarMateria(materias, id);
            if (m) m->mostrar(profesores);
            else cout << "Materia no encontrada.\n";
            break;
        }
        case 3: {
            Alumno* a = buscarAlumno(alumnos, id);
            if (a) a->mostrar(materias, profesores);
            else cout << "Alumno no encontrado.\n";
            break;
        }
        default:
            cout << "Opcion invalida.\n";
    }

    cout << "\nFin del programa.\n";
    return 0;
}
