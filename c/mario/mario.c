#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Hacemos la pregunta de la altura
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8); // Condición de la pregunta

    int espacios = h;
    // For que recorre las filas
    for (int i = 0; i < h; i++)
    {
        // for que recorre las columnas
        for (int j = 1; j <= h; j++)
        {
            // Si el valor de la columna es menor a n - 1, printea un espacio.
            if (j < espacios)
            {
                printf(" ");
            }
            // Si no printea un #.
            else
            {
                printf("#");
            }
        }
        // print 2 espacios
        printf("  ");
        // Segundo bloque para la piramide simetrica.
        for (int y = 1; y <= h; y++)
        {
            if (y >= espacios)
            {
                printf("#");
            }
        }
        // Espacio en blanco y restamos n.
        printf("\n");
        espacios = espacios - 1;
    }
}
