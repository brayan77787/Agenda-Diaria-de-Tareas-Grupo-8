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
cin.get();
getline(cin, nuevaTarea.fecha);

cout <<" \n\tDescripcion de la tarea : "<< endl;;
getline(cin, nuevaTarea.descripcion);

nuevaTarea.completada = false;
idActual++;

// Ahora guardo la tarea en el archivo de tareas
ofstream escribir;
escribir.open("tareas.txt", ios::app);
escribir <<" \n " << idActual;
escribir <<" \n " << nuevaTarea.fecha;
escribir <<" \n " << nuevaTarea.completada;
escribir <<" \n " << nuevaTarea.descripcion;
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