
#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <algorithm>    // std::sort
#include <cstdlib>      // std::strtoull
#include <assert.h>
#include <unordered_map>
#include <stack>

using namespace std;


// #define LOG_OPERACIONES_BASICAS
// #define LOG_INTERMEDIO

#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"

struct Conexion {
    string nodo1;
    string nodo2;
};

struct StackSet {
    vector<string> r;
    vector<string> p;
    vector<string> x;
};

vector<vector<string>> busca_max_cliques(unordered_map<string, vector<string>> &grafo, vector<string> &nodos) {
    // Algoritmo de Bron-Kerbosch con pivote para encontrar todas las clique máximas en un grafo no dirigido.
    // https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm#With_pivoting
    vector<vector<string>> cliques;
    std::stack<StackSet> pila;
    vector<string> nodos_tmp(nodos);
    StackSet s = { {}, nodos_tmp, {} };
    pila.push(s);
    
    while (pila.size() > 0) {
        StackSet valor_pila = pila.top();
        pila.pop();
        if (valor_pila.p.size() == 0 && valor_pila.x.size() == 0) {
            cliques.push_back(valor_pila.r);
        }
        else {
            string u = "";  //pivot
            for(string v : valor_pila.p) {
                if (u == ""  || grafo[v].size() > grafo[u].size()) {
                    u = v;
                }
            }
            vector<string> pp;
            for (string v : valor_pila.p) {
                bool encontrado = false;
                for (string nodo_v : grafo[u]) {
                    if (v == nodo_v) {
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    pp.push_back(v);
                }
            }
 
            for (string v : pp) {
                //union
                vector<string> r_tmp(valor_pila.r);
                bool encontrado = false;
                for (string nodo_r : r_tmp) {
                    if (nodo_r == v) {
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    r_tmp.push_back(v);
                }

                //interseccion
                vector<string> p_tmp;
                vector<string> v_tmp = grafo[v];
                for (string nodo_p : valor_pila.p) {
                    for (string nodo_v : v_tmp) {
                        if (nodo_p == nodo_v) {
                            p_tmp.push_back(nodo_p);
                            break;
                        }
                    }
                }

                //interseccion
                vector<string> x_tmp;
                v_tmp = grafo[v];
                for (string nodo_x : valor_pila.x) {
                    for (string nodo_v : v_tmp) {
                        if (nodo_x == nodo_v) {
                            p_tmp.push_back(nodo_x);
                            break;
                        }
                    }
                }

                StackSet nodo_pila_tmp = { r_tmp, p_tmp, x_tmp };
                pila.push(nodo_pila_tmp);

            }
        }
    }
    return cliques;
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;

    vector<Conexion> graph;
    int num_filas = 0;

    while(getline(cin, line))  {
        num_filas++;
        #ifdef LOG_OPERACIONES_BASICAS
            cout << "Linea " << num_filas << ": " << line << endl;
        #endif
        Conexion c = {line.substr(0, 2), line.substr(3, 2)};
        
        graph.push_back(c);
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    #ifdef LOG_OPERACIONES_BASICAS
        for (const auto& conexion : graph) {
            cout << "Conexion: " << conexion.nodo1 << " - " << conexion.nodo2 << endl;
        }
    #endif

    vector<string> nodos;
    unordered_map<string, vector<string>> grafo;

    for (Conexion c : graph) {
        string nodo1 = c.nodo1;
        string nodo2 = c.nodo2;
        bool encontrado = false;
        for (int i = 0; i < nodos.size(); i++) {
            if (nodos[i] == c.nodo1) {
                encontrado = true;
                grafo[nodo1].push_back(nodo2);
                break;
            }
        }
        if (!encontrado) {
            nodos.push_back(c.nodo1);
            grafo[nodo1] = {nodo2};
        }
        encontrado = false;
        for (int i = 0; i < nodos.size(); i++) {
            if (nodos[i] == c.nodo2) {
                encontrado = true;
                grafo[nodo2].push_back(nodo1);
                break;
            }
        }
        if (!encontrado) {
            nodos.push_back(c.nodo2);
            grafo[nodo2] = {nodo1};
        }
    }

    #ifdef LOG_INTERMEDIO
        for (int i = 0; i < nodos.size(); i++) {
            cout << "Nodo: " << nodos[i] << endl;
        }
    #endif

    vector<string> max_clique = {};
    vector<vector<string>> cliques = busca_max_cliques(grafo, nodos);
    for (vector<string> clique : cliques) {
        if (clique.size() > max_clique.size()) {
            max_clique = clique;
        }
    }   

    std::cout << "Max clique: ";
    for (const auto& nodo : max_clique) {
        std::cout << nodo << " ";
    }
    std::cout << std::endl;

    sort(max_clique.begin(), max_clique.end());

    std::cout << "Max clique sorted: ";
    for (size_t i = 0; i < max_clique.size(); ++i) {
        std::cout << max_clique[i];
        if (i < max_clique.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;

    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Numero grupos jugadores: " << total << endl;
    //SOLUCION: da,do,gx,ly,mb,ns,nt,pz,sc,si,tp,ul,vl
}


