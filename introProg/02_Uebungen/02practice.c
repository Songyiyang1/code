/*
Willkommen zum zweiten Übungsblatt vom Programmierkurs. Alles funktioniert wie auch beim ersten Aufgabenblatt.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 02practice_test.c -o 02practice_test.o -lm && ./02practice_test.o

Auf diesem Blatt geht es unter anderem um:

- if, else und else-if
- logisches und und logisches oder (`&&` und `||`)
- verschachtelte while und for loops
*/

#include <stdio.h>

int is_prime(int n)
{
    int result = 0;
    /*
    Eine Primzahl ist eine natürliche Zahl größer gleich 2, deren einzigen ganzzahligen Teiler die eins und die Zahl selbst sind.
    Die ersten Primzahlen sind 2, 3, 5, 7, 11, 13, ...

    Weisen Sie der Variable `result` den Wert `1` zu, falls `n` eine Primzahl ist, und ansonsten `0`.
    */
    /* BEGIN CHANGES */
    {
        for (int i = 2; i <= n / 2; i++)
        {
            if (n % i == 0)
            {
                result = 1;
                break;
            }
        }
    }
    if (result || n == 1 || n == 0)
        result = 0;
    else
        result = 1;

    /* END CHANGES */
    return result;
}

int sum_first_primes(int n)
{
    int result = 0;
    /*
    Weisen Sie der Variable `result` die Summe der ersten `n` Primzahlen zu zu.
    Beispiel für `n = 4`: `2 + 3 + 5 + 7 = 17`.
    */
    /* BEGIN CHANGES */
    int sum = 0;
    int i = 0;
    while (sum < n)
    {
        if (is_prime(i))
        {
            result += i;
            sum++;
        }
        i++;
    }

    /* END CHANGES */
    return result;
}

int sum_first_powers(int n)
{
    int result = 0;
    /*
    Sum First Powers:
    Weisen Sie der Variable `result` die Summe `n^0 + n^1 + n^2 + n^3 + ... + n^n` zu.
    Beispiel für `n = 4`: `4^0 + 4^1 + 4^2 + 4^3 + 4^4 = 1 + 4 + 16 + 64 + 256 = 341`.
    */
    /* BEGIN CHANGES */
    int potenz = 1;
    for (int i = 0; i <= n; i++)
    {
        result += potenz;
        potenz *= n;
    }
    /* END CHANGES */
    return result;
}

/*
Schreiben Sie ein paar nette Muster ins Terminal.


Muster 1: k-square (im Beispiel unten ist k := 8)

########
########
########
########
########
########
########
########

Muster 2: k-diagonal (im Beispiel unten ist k := 8)

#
##
###
####
#####
######
#######
########

Muster 3: k-arrow (im Beispiel unten ist k := 8)

#
##
###
####
####
###
##
#

Muster 4: k-chessboard (im Beispiel unten ist k := 8)

 # # # #
# # # #
 # # # #
# # # #
 # # # #
# # # #
 # # # #
# # # #

Muster 5: k-pyramid (im Beispiel unten ist k := 8)

   ##
  ####
 ######
########

Muster 6: k-spiral (im Beispiel unten ist k := 16)

################
               #
############## #
#            # #
# ########## # #
# #        # # #
# # ###### # # #
# # # ## # # # #
# # # #  # # # #
# # # #### # # #
# # #      # # #
# # ######## # #
# #          # #
# ############ #
#              #
################



*/