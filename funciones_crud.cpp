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
            archivoTemporal << "\n" << t.id;
            archivoTemporal << "\n" << t.fecha;
            archivoTemporal << "\n" << t.completada;
            archivoTemporal << "\n" << t.descripcion;
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
                archivoTemporal << "\n" << t.id;
                archivoTemporal << "\n" << t.fecha;
                archivoTemporal << "\n" << t.completada;
                archivoTemporal << "\n" << t.descripcion;
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
