// Autores: Ana Argüello, Camila Caicedo, Laura Olivero
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Definimos el tamaño de la memoria principal
const int MEM_SIZE = 1000;

// Estructura para representar los registros de la CPU
struct RegistrosCPU {
    int ACC = 0;  // Acumulador
    int ICR = 0;  // Instruction Counter Register
    int MAR = 0;  // Memory Address Register
    int MDR = 0;  // Memory Data Register
};

// Memoria principal implementada como un arreglo
struct Memoria {
    int data[MEM_SIZE] = {0};  // Inicializa toda la memoria con ceros
};

// Unidad de control
struct UnidadControl {
    bool ejecutando = true;  // Controla si el procesador sigue ejecutando instrucciones
};

// Instancias de los componentes
RegistrosCPU registros;
Memoria memoria;
UnidadControl control;

// Función para obtener el índice de la memoria
int obtenerIndice(const string& direccion) {
    if (direccion[0] == 'D' && direccion.length() > 1) {
        return stoi(direccion.substr(1));  // Mira el número después de la "D"
    }
    return -1;  // Dirección inválida
}

// Función para ejecutar instrucciones
void ejecutarInstruccion(const string& instr, const string& op1, const string& op2, const string& op3) {
    int idx1 = obtenerIndice(op1);
    int idx2 = obtenerIndice(op2);
    int idx3 = obtenerIndice(op3);

    if (instr == "SET" && idx1 >= 0) {
        memoria.data[idx1] = stoi(op2);  // Almacena valor en memoria
    } 
    else if (instr == "LDR" && idx1 >= 0) {
        registros.ACC = memoria.data[idx1];  // Carga valor en el acumulador
    } 
    else if (instr == "ADD") {
        if (idx1 >= 0 && op2 == "NULL") {
            registros.ACC += memoria.data[idx1];  // Suma al acumulador
        } 
        else if (idx1 >= 0 && idx2 >= 0 && op3 == "NULL") {
            registros.ACC = memoria.data[idx1] + memoria.data[idx2];  // Suma dos valores y almacena en ACC
        } 
        else if (idx1 >= 0 && idx2 >= 0 && idx3 >= 0) {
            memoria.data[idx3] = memoria.data[idx1] + memoria.data[idx2];  // Suma y almacena en idx3
        }
    } 
    else if (instr == "INC" && idx1 >= 0) {
        memoria.data[idx1]++;  // Incrementa valor en memoria
    } 
    else if (instr == "DEC" && idx1 >= 0) {
        memoria.data[idx1]--;  // Decrementa valor en memoria
    } 
    else if (instr == "STR" && idx1 >= 0) {
        memoria.data[idx1] = registros.ACC;  // Guarda valor del acumulador en memoria
    } 
    else if (instr == "SHW") {
        if (op1 == "ACC") {
            cout << "ACC: " << registros.ACC << endl;
        } 
        else if (op1 == "ICR") {
            cout << "ICR: " << registros.ICR << endl;
        } 
        else if (op1 == "MAR") {
            cout << "MAR: " << registros.MAR << endl;
        } 
        else if (op1 == "MDR") {
            cout << "MDR: " << registros.MDR << endl;
        } 
        else if (idx1 >= 0) {
            cout << op1 << ": " << memoria.data[idx1] << endl;
        }
    } 
    else if (instr == "PAUSE") {
        cout << "Ejecución pausada. Presiona Enter para continuar...";
        cin.ignore();
        cin.get();
    } 
    else if (instr == "END") {
        control.ejecutando = false;  // Finaliza la ejecución
    }
}

// Función para leer y ejecutar un archivo de instrucciones
void leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    string linea, instr, op1, op2, op3;
    while (getline(archivo, linea) && control.ejecutando) {
        registros.ICR++;  // Incrementa el contador de instrucciones

        stringstream ss(linea);
        ss >> instr >> op1 >> op2 >> op3;

        ejecutarInstruccion(instr, op1, op2, op3);
    }

    archivo.close();
}




int main() {
    leerArchivo("programa2.txt");
    return 0;
}
