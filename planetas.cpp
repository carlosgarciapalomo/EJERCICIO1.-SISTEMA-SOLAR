//EJERCICIO OBLIGATORIO 1. SISTEMA SOLAR. AUTOR: CARLOS GARCÍA PALOMO

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//DEFINIMOS LAS CONSTANTES (TODAS EN EL S.I)
#define c 1.496e11 //m
#define G 6.67e-11 //SI
#define M_s 1.989e30 //kg
#define cte 29779.30184 // Es el factor de conversion de la velocidad (ver funcion reescalar)
#define time_constant 5023623.23 //FACTOR DE CONVERSIÓN DEL TIEMPO 

//VEAMOS LAS FUNCIONES QUE NECESITAREMOS
void leerDatos(string nombreArchivo, double masa[][1], double vel[][2], double pos[][2], double excentricidad[][1]);
void reescalar(double array1[][2],double array2[][2],double array3[][1]);
double calcularEnergia(double pos[][2], double vel[][2], double masa[][1]);




int main() {

    //declaramos variables
     double pos[9][2], vel[9][2], masa[9][1], excentricidad[9][1], aceleracion[9][2];
     double a_aux[9][2],h,t,ry_anterior[9],T[9];

     //IMPORTANTE: INICIALIZAR t a cero
     t=0.0;
    // Llamar a la función leerDatos para leer los datos del archivo
    leerDatos("datos.txt", masa, vel, pos, excentricidad);

    //Pedimos por pantalla el valor del paso del tiempo
    cout << "Introduzca el valor del paso de tiempo h: ";
    cin >> h;

    //Ahora reescalamos los datos leidos para evitar errores numéricos
    reescalar(pos,vel, masa);

    //CALCULAMOS LA ACELERACION CON LA SEGUNDA LEY DE MI PRIMO NEWTON
    double r, rx, ry;
    for(int i=0; i<9; i++) {
        aceleracion[i][0] = 0.0;
        aceleracion[i][1] = 0.0;
        for(int k=0; k<9; k++) {
            if(i!=k) {
                 rx = pos[i][0] - pos[k][0];
                ry = pos[i][1] - pos[k][1];
                r = sqrt(rx*rx + ry*ry);
                aceleracion[i][0] = aceleracion[i][0] - masa[k][0] * rx * pow(r, -3);
                aceleracion[i][1] = aceleracion[i][1] - masa[k][0] * ry * pow(r, -3);
            }
        }
    }




    // Abrimos el archivo donde se escribirá la posición
    std::ofstream archivo_posicion("posicion.txt");
    archivo_posicion.precision(16); // definir la precisión del archivo de salida

    // Abrimos el archivo donde se escribirá la energía
    std::ofstream archivo_energia("energia.txt");
    archivo_energia.precision(16); // definir la precisión del archivo de salida

// Abrimos el archivo donde se escribirá  el periodo
    std::ofstream archivo_periodo("periodo.txt");
    archivo_periodo.precision(16); // definir la precisión del archivo de salida

    //Calculamos la energía inicial y la escribimos
     archivo_energia << t << " " << calcularEnergia(pos, vel, masa) << std::endl;

    //Escribimos las posiciones iniciales reescaladas

    for (int j = 0; j < 8; j++)
    {
        archivo_posicion <<pos[j][0] << ", " << pos[j][1] << ", ";
    }
    archivo_posicion << pos[8][0] << ", " << pos[8][1] << std::endl;


    //INICIALIZAMOS LOS PERIODOS A CERO y ry_anterior que almacena la posición en y anterior
     for (int i = 0; i < 9; i++){
        ry_anterior[i]=pos[i][1];
        T[i]=0.0;
     }
    // Calcularemos la posicion para 1000 iteraciones con un paso que se pide por pantalla.
    //NOTA: PARA CALCULAR LOS  PERIODOS ES CONVENIENTE AUMENTAR LAS ITERACIONES A 200000 O ASÍ.ç

    for (int i = 0; i < 10000; i++)
{
    
    // Calculamos la posicion
    for (int i = 0; i < 9; i++) {
        pos[i][0] = pos[i][0] + h * vel[i][0] + 0.5*pow(h,2) * aceleracion[i][0];
        pos[i][1] = pos[i][1] + h * vel[i][1] +0.5* pow(h,2)* aceleracion[i][1];  
    }
    
    //  CALCULAMOS LA ACELERACION AUXILIAR Y LUEGO LA ACELERACION
    for(int i=0; i<9; i++){
     
       a_aux[i][0]= aceleracion[i][0];
       a_aux[i][1]= aceleracion[i][1];
    }

    for(int i=0; i<9; i++) {
        aceleracion[i][0] = 0.0;
        aceleracion[i][1] = 0.0;
        for(int k=0; k<9; k++) {
            if(i!=k) {
                rx = pos[i][0] - pos[k][0];
                ry = pos[i][1] - pos[k][1];
                r = sqrt(rx*rx + ry*ry);
                aceleracion[i][0] = aceleracion[i][0] - masa[k][0] * rx * pow(r, -3);
                aceleracion[i][1] = aceleracion[i][1] - masa[k][0] * ry *  pow(r, -3);
            }
        }
    }

    // Calculamos la velocidad
    for (int i = 0; i < 9; i++) {
        vel[i][0] = vel[i][0]+0.5*h*a_aux[i][0]+0.5*h*aceleracion[i][0];
        vel[i][1] = vel[i][1]+0.5*h*a_aux[i][1]+0.5*h*aceleracion[i][1];
    }

    //CALCULAMOS EL PERIODO
    for (int i = 0; i < 9; i++) {
        if(T[i]==0)
        {
             if ((ry_anterior[i]<0) && (pos[i][1]>=0))
        {
            T[i]=time_constant*t; //Hacemos el reescalamiento inverso del tiempo
            archivo_periodo << T[i] << std::endl;
        }
        else

        ry_anterior[i]=pos[i][1];
        }
    }
    
    // actualizar el valor de t
    t = t + h;


 
    //Escribir la energía en el archivo de energía
     archivo_energia << t << " " << calcularEnergia(pos,vel,masa)<< std::endl;
    
    // escribir la posición en el archivo
   
    for (int j = 0; j < 8; j++)
    {
        archivo_posicion << pos[j][0] << ", " << pos[j][1] << ", ";
    }
    archivo_posicion << pos[8][0] << ", " << pos[8][1] << std::endl;
    
}

    
    // cerrar el archivo de la posicion
    archivo_posicion.close();
    //cerrar el archivo de la energía
    archivo_energia.close();
    //cerrar el archivo de los periodos
    archivo_periodo.close();



    return 0;

}
//--------------------------------------------------------------
//FUNCION QUE LEE LOS DATOS INICIALES Y LOS ALMACENA EN SUS ARRAYS
//-----------------------------------------------------------------

void leerDatos(string nombreArchivo, double masa[][1], double vel[][2], double pos[][2], double excentricidad[][1]) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    // Leer los datos y almacenarlos en arrays. Para las posiciones y velocidades la primera columna
    // corresponde con el eje x y la segunda con el eje y
    for (int i = 0; i < 9; i++) {
        if (!(archivo >> masa[i][0] >> vel[i][0] >> vel[i][1] >> pos[i][0] >> pos[i][1] >> excentricidad[i][0])) {
            cerr << "Error al leer los datos en la línea " << i + 1 << endl;
            exit(1);
        }
    }

    // Cerrar archivo
    archivo.close();
}

//--------------------------------------------------
//-----------------------------------------
//Función para reescalar
void reescalar(double array1[][2],double array2[][2],double array3[][1]) {
    for(int i=0; i<9; i++) {
       
        array1[i][0] /= c;
        array1[i][1] /= c;
        array3[i][0] /= M_s;
        array2[i][0] /= cte;
        array2[i][1] /= cte;
    }
   
}

//---------------------------------------------------
//FUNCION PARA CALCULAR LA ENERGÍA
//---------------------------------------------------
double calcularEnergia(double pos[][2], double vel[][2], double masa[][1]) {
    double energia_cinetica = 0.0;
    double energia_potencial = 0.0; 
    // Calcular la energía cinética
    for (int i = 0; i < 9; i++) {
        energia_cinetica += 0.5 * masa[i][0] * (vel[i][0]*vel[i][0] + vel[i][1]*vel[i][1]);
    }
    
    // Calcular la energía potencial
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9; j++) {
            double distancia = sqrt((pos[i][0]-pos[j][0])*(pos[i][0]-pos[j][0]) + 
                                    (pos[i][1]-pos[j][1])*(pos[i][1]-pos[j][1]));
            energia_potencial += masa[i][0] * masa[j][0] / distancia;
        }
    }
    
    // Calcular la energía total
    double energia_total = (energia_cinetica - energia_potencial)*M_s*pow(cte,2);
    //NOTA: EN LA ENERGÍA SE HA MULTIPLICADO PARA HACER EL REESCALAMIENTO INVERSO POR LO QUE ESTÁ EN JULIOS
    return energia_total;
}










