#pragma once

struct Coordenadas
{
    int fila;
    int columna;
};

void busca_camino(int direccion, int i, int num_lines, int j, int num_columns, std::vector<std::vector<int>> &mapa, int altura, long &total, std::vector<Coordenadas> &mapa_origen);
