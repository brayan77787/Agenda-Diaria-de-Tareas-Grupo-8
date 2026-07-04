#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int idActual; // Guarda el ID de la próxima tarea que voy a crear

// Estructura para organizar los datos de cada tarea
struct Tarea {
int id; // ID de la tarea
string fecha;
bool completada;
string descripcion;
};

// Función para limpiar la pantalla (sirve en Windows y Linux)
void limpiarPantalla() {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

// Pausa el programa hasta que presionás Enter
void pausarPrograma() {
cout << "\n\t Presiona Enter para continuar...";
cin.ignore();
cin.get();
}

// Función para agregar una nueva tarea
void agregarTarea() {
limpiarPantalla();

cout <<" \t\t\t*********************************************************************** "<< endl;
cout <<" \t\t\t "<<endl;
cout <<" \t\t\t BIENVENIDO A Tu Lista de Tareas " <<endl;
cout <<" \t\t\t " <<endl;
cout <<" \t\t\t*********************************************************************** "<< endl;

Tarea nuevaTarea; // Creo la estructura para la tarea nueva
cout <<" \n\tIntroduce la fecha (Ej: 24/06/2026) : "<< endl;
cin.ignore();
getline(cin, nuevaTarea.fecha);

cout <<" \n\tDescripcion de la tarea : "<< endl;;
getline(cin, nuevaTarea.descripcion);

nuevaTarea.completada = false;
idActual++;

// Ahora guardo la tarea en el archivo de tareas
// Ahora guardo la tarea en el archivo de tareas
ofstream escribir;
escribir.open("tareas.txt", ios::app);
escribir << idActual << "\n";
escribir << nuevaTarea.fecha << "\n";
escribir << nuevaTarea.completada << "\n";
escribir << nuevaTarea.descripcion << "\n";
escribir.close();

// Guardo el ID actual en un archivo aparte
escribir.open("id.txt");
escribir << idActual;
escribir.close();

char opcion;
cout <<" \n\tDeseas agregar otra tarea? s o n : "; cin>> opcion;

if(opcion == 's'|| opcion == 'S'){
agregarTarea();
} else{
   cout <<" \n\tLa tarea ha sido agregada con exito \n";

   return;
}

}


// Función para imprimir una tarea
void imprimir(Tarea t) {
    string estado = (t.completada) ? "Completada" : "Pendiente";
    cout << "\tID: " << t.id << " | Fecha: " << t.fecha << " | Estado: [" << estado << "]" << endl;
    cout << "\tTarea: " << t.descripcion << endl;
    cout << "\t-----------------------------------------------------------------------" << endl;
}

// Lee todas las tareas del archivo y las muestra
void leerDatos() {
    limpiarPantalla();
    cout<<"\t\t\t***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t                       BIENVENIDO A Tu Lista de Tareas                 "<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t***********************************************************************"<<endl<<endl<<endl;
    
    Tarea t;  // Variable auxiliar para leer cada tarea
    ifstream leer;
    leer.open("tareas.txt");  // Abre el archivo en modo lectura
    cout << "\n\t\t\t------------------Tus tareas actuales en la lista--------------------" << endl; 
    
    // Va leyendo línea por línea y armando las tareas
    while (leer >> t.id) {
        leer.ignore();
        getline(leer, t.fecha); 
        leer >> t.completada;
        leer.ignore(); 
        getline(leer, t.descripcion);
        imprimir(t);
    }
    leer.close();  // Cierra el archivo
    cout << "\n"; 
}


// Busca una tarea por ID y la retorna (o retorna -1 si no existe)
int buscarDatos() {
    limpiarPantalla();
    cout<<"\t\t\t***********************************************************************"<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t                       BIENVENIDO A Tu Lista de Tareas                 "<<endl;
    cout<<"\t\t\t                                                                       "<<endl;
    cout<<"\t\t\t***********************************************************************"<<endl<<endl<<endl;

    int idBuscado;
    cout << "\n\tIntroduce el ID de la tarea : ";     
    cin >> idBuscado;
    
    Tarea t;
    ifstream leer;
    leer.open("tareas.txt");
    
    // Recorre todas las tareas hasta encontrar la que coincide
    while (leer >> t.id) {
        leer.ignore();
        getline(leer, t.fecha);
        leer >> t.completada;
        leer.ignore();
        getline(leer, t.descripcion);
        
        if (t.id == idBuscado) {  // La encontro
            cout << "\n\t--- Tarea Encontrada ---" << endl;
            imprimir(t);
            leer.close(); 
            return idBuscado;  // Retorna el ID
        }
    }
    leer.close();
    
    // Si llegó aquí es porque no encontró nada
    cout << "\n\tNo se encontro ninguna tarea con el ID " << idBuscado << ".\n" << endl;
    return -1;  // Retorna -1 para indicar error
}

// Marca una tarea como completada
void completarTarea() {
    limpiarPantalla();

    // Primero busca la tarea por ID
    int idBuscado = buscarDatos();
    
    if (idBuscado == -1) {  // Si no existe, sale
        return;
    }

    cout << "\n\tDeseas marcar esta tarea como completada? s o n : ";
    char eleccion;
    cin >> eleccion;
    
    if (eleccion == 's' || eleccion == 'S') {
        Tarea t;
        // Crea un archivo temporal para guardar todo
        ofstream archivoTemporal("temporal.txt");
        ifstream leer("tareas.txt");
        
        // Lee todas las tareas y reescribe el archivo
        while (leer >> t.id) {
            leer.ignore();
            getline(leer, t.fecha);
            leer >> t.completada;
            leer.ignore();
            getline(leer, t.descripcion);
            
            // Si es la tarea que buscamos, la marca como completada
            if (t.id == idBuscado) {
                t.completada = true; 
            }
            
            // Reescribe en el archivo temporal
            archivoTemporal << t.id << "\n";
            archivoTemporal << t.fecha << "\n";
            archivoTemporal << t.completada << "\n";
            archivoTemporal << t.descripcion << "\n";
        }
        leer.close();
        archivoTemporal.close();
        
        // Borra el archivo viejo y renombra el temporal
        remove("tareas.txt");
        rename("temporal.txt", "tareas.txt");
        cout << "\n\tEstado de la tarea actualizado con exito!\n";
    }
}

// Elimina una tarea del archivo
void eliminarDatos() {
    limpiarPantalla();

    // Busca la tarea para confirmar que existe
    int idBuscado = buscarDatos();
    
    if (idBuscado == -1) {  // No existe
        return;
    }

    cout << "\n\tDeseas eliminar esta tarea? s o n : ";
    char eleccion;
    cin >> eleccion;
    
    if (eleccion == 's' || eleccion == 'S') {
        Tarea t;
        // Crea un archivo temporal
        ofstream archivoTemporal("temporal.txt");
        ifstream leer("tareas.txt");
        
        // Lee todas las tareas pero solo copia las que NO son la buscada
        while (leer >> t.id) {
            leer.ignore();
            getline(leer, t.fecha);
            leer >> t.completada;
            leer.ignore();
            getline(leer, t.descripcion);
            
            // Solo copia si el ID es diferente (así se "elimina")
            if (t.id != idBuscado) {
                archivoTemporal << t.id << "\n";
                archivoTemporal << t.fecha << "\n";
                archivoTemporal << t.completada << "\n";
                archivoTemporal << t.descripcion << "\n";
            }
        }
        leer.close();
        archivoTemporal.close();
        
        // Reemplaza el archivo original con el temporal
        remove("tareas.txt");
        rename("temporal.txt", "tareas.txt");
        cout << "\n\tTarea eliminada con exito\n";
    }
    else {
        cout << "\n\tRegistro no eliminado\n";
    }
}

// El programa principal
int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    // Intenta leer el ID guardado (para mantener el contador entre ejecuciones)
    ifstream leer;
    leer.open("id.txt");
    if (!leer.fail()) {
        leer >> idActual;  // Si existe el archivo, lee el último ID
    }
    else {
        idActual = 0;  // Si no existe, empieza de 0
    }
    leer.close();

    // Loop principal que siempre está corriendo hasta que sales
    while (true) {

        limpiarPantalla(); 
        
        // Menú principal
        cout<<"\n\n\t\t\t***********************************************************************"<<endl;
        cout<<"\t\t\t* *"<<endl;
        cout<<"\t\t\t* BIENVENIDO A Tu Lista de Tareas                     *"<<endl;
        cout<<"\t\t\t* *"<<endl;
        cout<<"\t\t\t***********************************************************************"<<endl;
        
        cout << "\n\t1. Agregar tarea";
        cout << "\n\t2. Ver tareas";
        cout << "\n\t3. Buscar tarea";
        cout << "\n\t4. Marcar tarea como completada"; 
        cout << "\n\t5. Eliminar tarea";
        cout << "\n\t6. Salir del programa";

        int seleccion;
        cout << "\n\n\tIntroduce una opcion : ";
        cin >> seleccion;
        
        // Switch para ejecutar lo que el usuario selecciona
        switch (seleccion) {
        case 1:
            agregarTarea();
            cout << "\n\t"; pausarPrograma();
            break;
        case 2:
            leerDatos();
            cout << "\n\t"; pausarPrograma();
            break;
        case 3:
            buscarDatos();
            cout << "\n\t"; pausarPrograma();
            break;
        case 4:
            completarTarea();
            cout << "\n\t"; pausarPrograma();
            break;
        case 5:
            eliminarDatos();
            cout << "\n\t"; pausarPrograma();
            break;
        case 6:
            cout << "\n\tSaliendo del programa... Hasta luego!\n";
            return 0;
        default: 
            cout<<"\n\tIntroduce una opcion valida entre 1 y 6";
            cout << "\n\t"; pausarPrograma();
        }
    }
}
