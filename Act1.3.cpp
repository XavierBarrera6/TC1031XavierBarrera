/*
Act-Integradora-1 Conceptos básicos y algoritmos fundamentales
Equipo 6:
Xavier Barrera A01702869
Jorge Emiliano Pomar A01709338

Este programa lee el archivo bitacora.txt que contiene registros y los ordena.
Posteriormente permite al usuario buscar un rango de fechas dados los limites de
busqueda.
*/

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// clase registro para los arreglos en el archivo
class Registro {
public:
  std::string mes;
  int dia;
  int hora;
  int minuto;
  int segundo;
  std::string espacio;
  std::string puntos;
  std::string direccion_ip;
  std::string mensaje;
};

// Funcion que compara tamano de cada elemnto de fecha

bool comparar_fechas(Registro r1, Registro r2) {
  if (r1.mes != r2.mes) {
    return r1.mes < r2.mes;
  } else if (r1.espacio != r2.espacio) {
    return r1.espacio < r2.espacio;
  } else if (r1.dia != r2.dia) {
    return r1.dia < r2.dia;
  } else if (r1.espacio != r2.espacio) {
    return r1.espacio < r2.espacio;
  } else if (r1.hora != r2.hora) {
    return r1.hora < r2.hora;
  } else if (r1.puntos != r2.puntos) {
    return r1.puntos < r2.puntos;
  } else if (r1.minuto != r2.minuto) {
    return r1.minuto < r2.minuto;
  } else if (r1.puntos != r2.puntos) {
    return r1.puntos < r2.puntos;
  } else {
    return r1.segundo < r2.segundo;
  }
}

// insertion sort para ordenar el arreglo
void insertion_sort(std::vector<Registro> &registros) {
  int n = registros.size();
  for (int i = 1; i < n; ++i) {
    Registro key = registros[i];
    int j = i - 1;
    while (j >= 0 && comparar_fechas(registros[j], key)) {
      registros[j + 1] = registros[j];
      j--;
    }
    registros[j + 1] = key;
  }
} // complejidad O(n^2); menos eficiente

// funcion merge que
void merge(std::vector<Registro> &registros, int low, int m, int high) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;

  std::vector<Registro> L(n1), H(n2);

  for (i = 0; i < n1; i++) {
    L[i] = registros[low + i];
  }
  for (j = 0; j < n2; j++) {
    H[j] = registros[m + 1 + j];
  }

  i = 0;
  j = 0;
  k = low;

  while (i < n1 && j < n2) {
    if (comparar_fechas(L[i], H[j])) {
      registros[k] = L[i];
      i++;
    } else {
      registros[k] = H[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    registros[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    registros[k] = H[j];
    j++;
    k++;
  }
}

// merge sort es una funcion recursiva que parte a la mitad y al final llama a
// la funcion merge para unir las dos partes
void merge_sort(std::vector<Registro> &registros, int low, int high) {
  if (low < high) {
    int m = low + (high - low) / 2;
    merge_sort(registros, low, m);
    merge_sort(registros, m + 1, high);
    merge(registros, low, m, high);
  }
}

// Busca que la fecha solicitada coincida, si no es asi regresa -1
int buscar_fecha(const std::vector<Registro> &registros,
                 std::string fechainicio, std::string fechafin) {
  int n = registros.size();
  for (int i = 0; i < n; ++i) {
    if (registros[i].mes + std::to_string(registros[i].dia) == fechainicio) {
      return i;
    }
  }
  return -1;
}

int main() {

  std::ifstream archivo("bitacora.txt"); // abrir y leer archivo

  std::vector<Registro> registros;
  std::string mes, espacio, direccion_ip, puntos, mensaje;
  int dia, hora, minuto, segundo;
  while (archivo >> mes >> espacio >> dia >> espacio >> hora >> puntos >>
         minuto >> puntos >> segundo >> espacio >> direccion_ip >> mensaje) {
    Registro registro;
    registro.mes = mes;
    registro.espacio = " ";
    registro.dia = dia;
    registro.espacio = " ";
    registro.hora = hora;
    registro.puntos = puntos;
    registro.minuto = minuto;
    registro.puntos = puntos;
    registro.segundo = segundo;
    registro.espacio = " ";
    registro.direccion_ip = direccion_ip;
    registro.espacio = " ";
    registro.mensaje = mensaje;
    registros.push_back(registro);
  }

  auto inicio1 = std::chrono::high_resolution_clock::now(); // tiempo merge sort
  merge_sort(registros, 0, registros.size() - 1);
  auto fin1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> tiempom = fin1 - inicio1;
  std::cout << "Tiempo de ordenamiento por merge sort: " << tiempom.count()
            << " segundos" << std::endl;

  auto inicio2 =
      std::chrono::high_resolution_clock::now(); // tiempo insertion sort
  insertion_sort(registros);
  auto fin2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> tiempoin = fin2 - inicio2;
  std::cout << "Tiempo de ordenamiento por insertion sort: " << tiempoin.count()
            << " segundos" << std::endl;

  std::string fechainicio; // ingresar fecha de inicio
  std::cout
      << "Ingrese una fecha inicio en formato Mes-dia-hora-minutos-segundos: ";
  std::cin >> fechainicio;

  std::string fechafin; // ingresar la fecha del final
  std::cout
      << "Ingrese una fecha fin en formato Mes-dia-hora-minutos-segundos: ";
  std::cin >> fechafin;

  int indx =
      buscar_fecha(registros, fechainicio,
                   fechafin); // buscar si la fecha corresponde a inicio o fin
  if (indx == -1) {
    std::cout << "No se encontraron registros para la fecha " << fechainicio
              << std::endl;
  } else if (indx >= 16809) {
    std::cout << "No se encontraron registros para la fecha " << fechainicio
              << std::endl;
  }

  else { // en caso de encontrar, se despliega informacion del rango de fechas
    std::cout << "Registros encontrados entre las fechas " << fechainicio
              << "----" << fechafin << ":" << std::endl;

    while (indx < registros.size() &&
           registros[indx].mes + std::to_string(registros[indx].dia) ==
               fechainicio) {
      std::cout << registros[indx].mes << " " << registros[indx].dia << " "
                << registros[indx].hora << ":" << registros[indx].minuto << ":"
                << registros[indx].segundo << " "
                << registros[indx].direccion_ip << " "
                << registros[indx].mensaje << std::endl;
      indx++;
    }
  }
  return 0;
}