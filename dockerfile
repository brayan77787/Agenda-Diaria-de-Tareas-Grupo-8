# 1. IMAGEN BASE: Descargamos un entorno linux que ya incluye el compilador de c/c++

FROM gcc:latest

# 2. DIRECTORIO DE TRABAJO: Creamos una carpeta llamada /app dentro del contenedor

WORKDIR /app

# 3. COPIA DE ARCHIVOS: Copiamos nuestro main.cpp (y todo lo demás) a la carpeta /app del contenedor

COPY . .

# 4. COMPILACIÓN: Compilamos los archivos .cpp y generamos un ejecutable llamado "gestor_de_tareas"

RUN g++ -o gestor_de_tareas *.cpp