# Establece el título de la gráfica
set title "Grafica de Energia en función del tiempo"

# Establece el nombre del eje x y el rango de valores
set xlabel "tiempo(s/c*raiz(G*M_s/c^3)"

# Establece el nombre del eje y y el rango de valores
set ylabel "Energia (J)"

# Establece el tipo de línea y el título de la leyenda
plot "energia.txt" using 1:2 with lines title "Energía"

                                        


