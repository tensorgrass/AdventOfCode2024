#include <iostream>     // std::cout
#include <vector>       // std::vector
#include <string>
#include <chrono>       // std::chrono
#include <cstdlib>      // std::strtoull


using namespace std;

#define LOG_OPERACIONES_BASICAS
#define LOG_ERROR_ENCONTRADO
#define LOG_INTERMEDIO
#define LOG_CHECK

//input
#define PATH_FICHERO "input.txt"
// #define PATH_FICHERO "testA1.txt"
// #define PATH_FICHERO "testA2.txt"
// #define PATH_FICHERO "testA3.txt"
// #define PATH_FICHERO "testA4.txt"
// #define PATH_FICHERO "testA5.txt"
// #define PATH_FICHERO "testA6.txt"
// #define PATH_FICHERO "testA9.txt"


int main()
{
    auto start = std::chrono::steady_clock::now();
    freopen(PATH_FICHERO, "r", stdin);
    string line;
    unsigned long long total = 0;
    int num_lineas = 0;
    int num_columnas = 0;
    unsigned long long a_int = 0;
    string a_string = "";
    unsigned long long b_int = 0;
    string b_string = "";
    unsigned long long c_int = 0;
    string c_string = "";
    vector<int> p_int;
    vector<string> p_string;
    

    while(getline(cin, line))  {
        num_lineas++;
        #ifdef LOG_OPERACIONES_BASICAS
            printf("Linea %i: %s\n", num_lineas, line.c_str());
        #endif
        vector<string> numeros;
        int num_numero = -1;
        bool is_numero = false;
        for (char c : line){
            if (c == '-' || (c >= '0' && c <= '9')){
                if (!is_numero) {
                    numeros.push_back("");
                    num_numero++;
                }
                numeros[num_numero] += c;
                is_numero = true;
            } else {
                if (is_numero){
                    is_numero = false;
                }
            }
        }
        #ifdef LOG_OPERACIONES_BASICAS
            std::cout << "Numero de lineas: " << num_lineas << std::endl;
            std::cout << "Numeros: ";
            for (const auto& num : numeros) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        #endif
        switch (num_lineas) {
            case 1:
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "Caso 1 " << numeros[0] << std::endl;
                #endif
                a_string = numeros[0];
                a_int = std::stoull(a_string);
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "a_int: " << a_int << std::endl;
                    std::cout << "a_string: " << a_string << std::endl;
                #endif
            break;
            case 2:
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "Caso 2 " << numeros[0] << std::endl;
                #endif
                b_string = numeros[0];
                b_int = std::stoull(b_string);
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "b_int: " << b_int << std::endl;
                    std::cout << "b_string: " << b_string << std::endl;
                #endif 
            break;
            case 3:
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "Caso 3 " << numeros[0] << std::endl;
                #endif
                c_string = numeros[0];
                c_int = std::stoull(c_string);
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "c_int: " << c_int << std::endl;
                    std::cout << "c_string: " << c_string << std::endl;
                #endif 
            break;
            case 5:
                #ifdef LOG_OPERACIONES_BASICAS
                    std::cout << "Caso 4 " << numeros[0] << std::endl;
                #endif
                for (string s : numeros) {
                    p_string.push_back(s);
                    p_int.push_back(std::stoull(s));
                }
            break;
        };
        
    }
    // cerrar el fichero
    fclose(stdin);
    std::cout << "Lectura fichero: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    #ifdef LOG_OPERACIONES_BASICAS
        std::cout << "a_int: " << a_int << std::endl;
        std::cout << "a_string: " << a_string << std::endl;

        std::cout << "b_int: " << b_int << std::endl;
        std::cout << "b_string: " << b_string << std::endl;

        std::cout << "c_int: " << c_int << std::endl;
        std::cout << "c_string: " << c_string << std::endl;

        std::cout << "p_int: " ;
        for (int i : p_int) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;

        std::cout << "p_string: " ;
        for (string s : p_string) {
            std::cout << s << ", ";
        }
        std::cout << std::endl; 
    #endif

    vector<int> resultado;
    for (int i = 0; i < p_int.size(); i+=2) {
        if (p_int[i] == 0) {//adv
            unsigned long long numerador = a_int;
            unsigned long long denominador = 0;
            unsigned long long resultado_div = 0;
            if (p_int[i+1] <= 3) {
                denominador = p_int[i+1];
            }
            else if (p_int[i+1] == 4) {
                denominador = a_int;
            }
            else if (p_int[i+1] == 5) {
                denominador = b_int;
            }
            else if (p_int[i+1] == 6) {
                denominador = c_int;
            }
            else if (p_int[i+1] == 7) {
                // denominador = c_int;
            }
            denominador = pow(2, denominador);
            resultado_div = numerador / denominador;
            a_int = resultado_div;
        }
        else if (p_int[i] == 1) {//bxl
            unsigned long long valor_xor = p_int[i+1];
            unsigned long long resultado_xor = 0;
            resultado_xor = b_int ^ valor_xor;
            b_int = resultado_xor;
        }
        else if (p_int[i] == 2) {//bst
            unsigned long long valor_mod = 0;
            unsigned long long resultado_mod = 0;
            if (p_int[i+1] <= 3) {
                valor_mod = p_int[i+1];
            }
            else if (p_int[i+1] == 4) {
                valor_mod = a_int;
            }
            else if (p_int[i+1] == 5) {
                valor_mod = b_int;
            }
            else if (p_int[i+1] == 6) {
                valor_mod = c_int;
            }
            else if (p_int[i+1] == 7) {
                // denominador = c_int;
            }
            resultado_mod = valor_mod % 8;
            resultado_mod = resultado_mod % 1000;
            b_int = resultado_mod;
        }
        else if (p_int[i] == 3) {//jnz
            if (a_int != 0) {
                unsigned long long valor_jump = p_int[i+1];
                i = valor_jump - 2;
            }
        }
        else if (p_int[i] == 4) {//bxl
            unsigned long long resultado_xor = 0;
            resultado_xor = b_int ^ c_int;
            b_int = resultado_xor;
        }
        else if (p_int[i] == 5) {//mod
            unsigned long long valor_mod = 0;
            unsigned long long resultado_mod = 0;
            if (p_int[i+1] <= 3) {
                valor_mod = p_int[i+1];
            }
            else if (p_int[i+1] == 4) {
                valor_mod = a_int;
            }
            else if (p_int[i+1] == 5) {
                valor_mod = b_int;
            }
            else if (p_int[i+1] == 6) {
                valor_mod = c_int;
            }
            else if (p_int[i+1] == 7) {
                // denominador = c_int;
            }
            resultado_mod = valor_mod % 8;
            resultado.push_back(resultado_mod);
        }
        if (p_int[i] == 6) {//adv
                       unsigned long long numerador = a_int;
            unsigned long long denominador = 0;
            unsigned long long resultado_div = 0;
            if (p_int[i+1] <= 3) {
                denominador = p_int[i+1];
            }
            else if (p_int[i+1] == 4) {
                denominador = a_int;
            }
            else if (p_int[i+1] == 5) {
                denominador = b_int;
            }
            else if (p_int[i+1] == 6) {
                denominador = c_int;
            }
            else if (p_int[i+1] == 7) {
                // denominador = c_int;
            }
            denominador = pow(2, denominador);
            resultado_div = numerador / denominador;
            b_int = resultado_div;
        }
        if (p_int[i] == 7) {//adv
                       unsigned long long numerador = a_int;
            unsigned long long denominador = 0;
            unsigned long long resultado_div = 0;
            if (p_int[i+1] <= 3) {
                denominador = p_int[i+1];
            }
            else if (p_int[i+1] == 4) {
                denominador = a_int;
            }
            else if (p_int[i+1] == 5) {
                denominador = b_int;
            }
            else if (p_int[i+1] == 6) {
                denominador = c_int;
            }
            else if (p_int[i+1] == 7) {
                // denominador = c_int;
            }
            denominador = pow(2, denominador);
            resultado_div = numerador / denominador;
            c_int = resultado_div;
        }
    }

    std::cout << "Resultado: ";
    for (int res : resultado) {
        std::cout << res << ",";
    }
    std::cout << std::endl;


    std::cout << "Total: " << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;
    cout << "Total robots: " << total << endl;
    //SOLUCION: 1,7,6,5,1,0,5,0,7
}


