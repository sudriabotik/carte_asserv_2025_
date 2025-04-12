// serialusM2M.c

#include "serialusM2M.h"
#include "Uart.h" // Include your UART code here
#include "system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

SerialusM2M serialusM2M = {
    .head = 0,
    .tail = 0,
    .carriageReturnReceived = false};

void serialusM2M_init()
{
    InitUART(UART_XBEE, 1000000);
    serialusM2M.clignotement_en_cours = false;
}

void serialusM2M_receive()
{
    // Code to read incoming serial data and place it in the circular buffer
    // You can use your UART functions here to read characters.
    // For example:

    while (U1STAbits.URXDA == 1)
    {                                         // U1STAbits.URXDA checks if data is available
        volatile char receivedChar = U1RXREG; // Read a character from UART1
        PutcUART(UART_XBEE, receivedChar);

        serialusM2M.buffer[serialusM2M.head] = receivedChar;
        serialusM2M.head = (serialusM2M.head + 1) % BUFFER_SIZE;

        // Check for '\r' (carriage return) to mark the end of a command
        if (receivedChar == '\r')
        {
            // putchar('\r');
            putchar('\n');
            serialusM2M.carriageReturnReceived = true;
        }
    }
}

void reset_rx_Buffer()
{
    while (U1STAbits.URXDA)
    {
        (void)U1RXREG; // Read and discard the character
    }
}

void serialusM2M_process()
{
    // Process the data in the circular buffer

    while (serialusM2M.head != serialusM2M.tail)
    {
        volatile char currentChar = serialusM2M.buffer[serialusM2M.tail];
        serialusM2M.tail = (serialusM2M.tail + 1) % BUFFER_SIZE;

        // Check for '\r' (carriage return) to mark the end of a command
        if (currentChar == '\r')
        {
            // Process the complete command here or set a flag to indicate a complete command
            if (serialusM2M.carriageReturnReceived)
            {
                // printf(serialusM2M.buffer);
                //  Complete command received, process it
                char id0 = serialusM2M.buffer[0];
                char id1;
                char id2;
                int taille_buffer = serialusM2M.tail;

                switch (id0)
                {
                case '0': // pos
                    id1 = serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '0': // get rob
                        print_pos();
                        break;
                    case '1': // set rob
                        if ((taille_buffer) != 15)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        else
                        {
                            InitPosM2M();
                            break;
                        }
                    default:
                        printf("err char 2 \n");
                        break;
                    }
                    break;
                case '1': // ca
                    id1 = serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '0': // ca X
                        if ((taille_buffer) != 15)
                        {
                            printf("erreur taille chat %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        calageX();
                        break;
                    case '1': // ca Y
                        if ((taille_buffer) != 15)
                        {
                            printf("erreur taille chat %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        calageY();
                        break;
                    case '2': // ca All
                        if ((taille_buffer) != 4)
                        {
                            printf("erreur taille chat %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        calageALL();
                        break;

                    default:
                        printf("error");
                        break;
                    }
                    break;
                case '2': // de
                    id1 = serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '1': // ori
                        if ((taille_buffer) != 10)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        ori();
                        break;
                    case '2': // cib
                        if ((taille_buffer) != 15)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        cib();
                        break;
                    case '3': // av
                        if ((taille_buffer) != 11)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        av();
                        break;
                    case '4': // rec
                        if ((taille_buffer) != 11)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        rec();
                        break;
                    case '5': // rej
                        if ((taille_buffer) != 16)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        rej();
                        break;

                    case '6': // passe_par
                        if ((taille_buffer) != 17)
                        {
                            printf("erreur taille char %d \n", taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        passe_par();
                        break;
                        
                     case '7': // break
                        set_Break();
                        break;
                        
                    default:
                        printf("non reconu char2 deplacement");
                        break;
                    }
                    break;

                case '3': // asserv
                    id1 = serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '0': ////reset
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0':
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_asserve();
                            break;
                        case '1':
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_VITESSE_CONSIGNE_MAX_MM();
                            break;
                        case '2': // reset_VITESSE_DISTANCE_MIN()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_VITESSE_DISTANCE_MIN();
                            break;
                        case '3': // reset_VITESSE_MAX_MM_TENSION()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_VITESSE_MAX_MM_TENSION();
                            break;
                        case '4': // reset_DISTANCE_CONSIGNE_MM()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_DISTANCE_CONSIGNE_MM();
                            break;
                        case '5': // reset_VITESSE_ANGLE_MAX()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_VITESSE_ANGLE_MAX();
                            break;
                        case '6': // reset_VITESSE_ANGLE_MIN()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_VITESSE_ANGLE_MIN();
                            break;
                        case '7': // reset_ORIENTATION_CONSIGNE_DEG()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_ORIENTATION_CONSIGNE_DEG();
                            break;
                        case '8': // reset_PID_Vitesse()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_PID_Vitesse();
                            break;
                        case '9': // reset_PID_Break()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_PID_Break();
                            break;

                        default:
                            printf("non reconu char3 asserv PID RESET");
                            break;
                        }
                        break;
                    case '1': // ODOM
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0': // reset_ENTRAXE_MM()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_ENTRAXE_MM();
                            break;
                        case '1': // reset_DIAMETRE_ROUE_CODEUSE()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_DIAMETRE_ROUE_CODEUSE();
                            break;
                        case '2': // reset_PERIMETRE_ROUE_MM()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_PERIMETRE_ROUE_MM();
                            break;
                        case '3': // reset_coef_D()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_coef_D();
                            break;
                        case '4': // reset_coef_G()
                            if ((taille_buffer) != 4)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            reset_coef_G();
                            break;
                        case '5': // set_ENTRAXE_MM()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ENTRAXE_MM(serialusM2M.buffer[3]);
                            break;
                        case '6': // set_DIAMETRE_ROUE_CODEUSE()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DIAMETRE_ROUE_CODEUSE(serialusM2M.buffer[3]);
                            break;
                        case '7': // set_PERIMETRE_ROUE_MM()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_PERIMETRE_ROUE_MM(serialusM2M.buffer[3]);
                            break;
                        case '8': // set_coef_D()
                            if ((taille_buffer) != 9)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_coef_D(serialusM2M.buffer[3]);
                            break;
                        default:
                            printf("non reconu char2 odom");
                            break;
                        case '9': // set_coef_G()
                            if ((taille_buffer) != 9)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_coef_G();
                            break;
                        }
                        break;

                    case '2': // PID Numerique setter
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0': // set_PID_Vitesse()
                            if ((taille_buffer) != 19)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_PID_Vitesse();
                            break;
                        case '1': // set_PID_Break()
                            if ((taille_buffer) != 19)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_PID_Break();
                            break;
                        case '2': // set_MAX_ERREUR_INTEGRALLE_V()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_MAX_ERREUR_INTEGRALLE_V();
                            break;
                        case '3': // set_MAX_E_INTEGRALLE_BRAKE()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_MAX_E_INTEGRALLE_BRAKE();
                            break;
                        case '4': // set_SEUIL_IMMOBILITE()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_SEUIL_IMMOBILITE();
                            break;
                        default:
                            printf("non reconu char3 asserv PID Numerique setter");
                            break;
                        }
                        break;

                    case '3': // PID vitesse-distance setters
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0': // set_VITESSE_CONSIGNE_MAX_MM()
                            if ((taille_buffer) != 6)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_VITESSE_CONSIGNE_MAX_MM();
                            break;
                        case '1': // set_VITESSE_DISTANCE_MIN()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_VITESSE_DISTANCE_MIN();
                            break;
                        case '2': // set_VITESSE_MAX_MM_TENSION()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_VITESSE_MAX_MM_TENSION();
                            break;
                        case '3': // set_DISTANCE_CONSIGNE_MM()
                            if ((taille_buffer) != 10)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DISTANCE_CONSIGNE_MM();
                            break;
                        case '4': // set_VITESSE_ANGLE_MAX()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_VITESSE_ANGLE_MAX();
                            break;
                        case '5': // set_VITESSE_ANGLE_MIN()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_VITESSE_ANGLE_MIN();
                            break;
                        case '6': // set_ORIENTATION_CONSIGNE_DEG()
                            if ((taille_buffer) != 9)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ORIENTATION_CONSIGNE_DEG();
                            break;
                        default:
                            printf("non reconu char2 PID vitesse-distance setters\n");
                            break;
                        }
                        break;

                    case '4': // PID ACCEL-DECCEL setters
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0': // set_ACC_ORIENTATION_CONSIGNE()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ACC_ORIENTATION_CONSIGNE();
                            break;
                        case '1': // set_DCC_ORIENTATION_CONSIGNE()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DCC_ORIENTATION_CONSIGNE();
                            break;
                        case '2': // set_ACC_ORIENTATION_MIN()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ACC_ORIENTATION_MIN();
                            break;
                        case '3': // set_DCC_ORIENTATION_MIN()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DCC_ORIENTATION_MIN();
                            break;
                        case '4': // set_ACC_POSITION_CONSIGNE()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ACC_POSITION_CONSIGNE();
                            break;
                        case '5': // set_DCC_POSITION_CONSIGNE()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DCC_POSITION_CONSIGNE();
                            break;
                        case '6': // set_ACC_POSITION_MIN()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_ACC_POSITION_MIN();
                            break;
                        case '7': // set_DCC_POSITION_MIN()
                            if ((taille_buffer) != 8)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            set_DCC_POSITION_MIN();
                            break;
                        default:
                            printf("non reconu char2 PID ACCEL-DECCEL setters \n");
                            break;
                        }
                        break;
                    case '5': // debug off/on
                        id2 = serialusM2M.buffer[2];
                        switch (id2){
                            case '0':
                                DEBUG_OFF();
                                break;
                            case '1':
                                DEBUG_ON();
                                break;
                            default:
                                printf("non reconu char2 debug off on \n");
                                break;
                        }
                        break;
                    default:
                        printf("non reconu char2 asserv \n");
                        break;
                    }
                    break;

                case '4': // AX
                    id1 = serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '0': ////AX_set
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0':
                            if ((taille_buffer) != 13)
                            {
                                printf("erreur taille char AX %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_set_ang();
                            break;
                        case '1':
                            if ((taille_buffer) != 14)
                            {
                                printf("erreur taille char AX %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_set_pos();
                            break;
                        case '2': 
                            if ((taille_buffer) != 7)
                            {
                                printf("erreur taille char AX %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_set_led();
                            break;
                        case '3': // 
                            if ((taille_buffer) != 7)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_set_torque();
                            break;
                        case '4': // ()
                            if ((taille_buffer) != 5)
                            {
                                printf("erreur taille char %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_set_alim();
                            break;

                        default:
                            printf("non reconu char3 AXset");
                            break;
                        }
                        break;

                    case '1': ////AX_get
                        id2 = serialusM2M.buffer[2];
                        switch (id2)
                        {
                        case '0':
                            if ((taille_buffer) != 6)
                            {
                                printf("erreur taille char AX %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_get_pos();
                            break;
                        case '1':
                            if ((taille_buffer) != 6)
                            {
                                printf("erreur taille char AX %d \n", taille_buffer);
                                break;
                            }
                            else if (!sontdesdigits(serialusM2M.buffer))
                            {
                                printf("erreur Sont des digits \n");
                                break;
                            }
                            AX_get_ping();
                            break;


                        default:
                            printf("non reconu char3 AXget");
                            break;

                        }
                        break;

                    default:
                            printf("non reconu char2 AX \n");
                            break;
                    }
                    break;
                case '5':
                    //printf("you are here \n");
                        id1 = serialusM2M.buffer[1];
                    switch (id1)
                    { case '0':
                        get_couleur();
                        break;
                        case '1':
                        set_couleur();
                        break;

                        default  :
                            printf ("Mauvais id1 couleur /n");
                            break;
                            }
                        
                        break; //break case 5 
                    
                    case '6'://evitemnt
                        //printf("you are here \n");
                         id1 = serialusM2M.buffer[1];
                        switch (id1)
                        { case '0':
                                Evitement_on_off();
                            break;
                            
                         case '1':
                            set_evitment();
                            break;
                        
                         case '2':
                             Check_evitement();
                             break;
                                
                            case '9':
                                start_match();
                                 break;
                                 
                            default  :
                                printf ("Mauvais id1 evitement /n");
                                break;
                                }
                                
                                      
                                
                        
                        break; //break 6
                case '7': // Strategie
                    id1= serialusM2M.buffer[1];
                    switch (id1)
                    {
                    case '0':
                        if ((taille_buffer) != 5)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        recup_plante();
                        break;

                    case '1':
                        if ((taille_buffer) != 17)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        recup_plante_alt();
                        break;

                    case '2': 
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        depose_zone_depart();
                        break;

                    case '3': 
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        depose_zone_reserv();
                        break;

                    case '4': 
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        depose_zone_reserv_alt();
                        break;

                    case '5':
                        if ((taille_buffer) != 5)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        depose_jardiniere();
                        break;

                    case '6':
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        activ_panneaux_solaires();
                        break;

                    case '7':
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        zone_recharge();
                        break;

                    case '8':
                        if ((taille_buffer) != 4)
                        {
                            printf("[Strategie] Code %d%d - Erreur taille buffer %d \n", id0, id1, taille_buffer);
                            break;
                        }
                        else if (!sontdesdigits(serialusM2M.buffer))
                        {
                            printf("erreur Sont des digits \n");
                            break;
                        }
                        calage_dep();
                        break;

                    default:
                        printf("[Strategie] Code %d%d - Code non reconnu\n", id0, id1);
                        break;
                    }
                    break;

                               
                            
                default:
                    printf("connais pas \n");
                    break;
                }

                // Clear the flag
                serialusM2M.carriageReturnReceived = false;

                // Reset the circular buffer
                serialusM2M.head = 0;
                serialusM2M.tail = 0;
                reset_rx_Buffer();
            }
        }
    }
}



void print_pos()
{
    printf("%f_%f_%f\n", (float)get_X(), (float)get_Y(), (float)get_orientation());
}
void calageX()
{
    double d = 0.0;
    double t = 0.0;
    int8_t s = 0;
    double v = 0.0;

    char charD[5];
    char charT[4];
    char charS[2];
    char charV[4];

    strncpy(charD, serialusM2M.buffer + 3, 4);
    strncpy(charT, serialusM2M.buffer + 7, 3);
    strncpy(charS, serialusM2M.buffer + 10, 1);
    strncpy(charV, serialusM2M.buffer + 11, 3);

    charD[4] = '\0';
    charT[3] = '\0';
    charV[3] = '\0';
    charS[1] = '\0';

    // Convert the substrings to double
    d = (double)atof(charD);
    t = (double)atof(charT);
    v = (double)atof(charV);
    s = (int8_t)atoi(charS);
    
    if (s==0){
        s=-1; 
    }
    if (t>180)
    {
        t=(360-t)*(-1);
    }          

    if (abs(d) > 3000 || abs(t) > 180 || abs(v) > 200 || abs(s) != 1)
    {
        printf("data inchoerante d: %f,t: %f ,V %f , s%d \n ", (float)d, (float)t, (float)v, s);
    }
    else
    {
        calage_X(d, t, s, v);
        print_pos();
    }
}

void calageY()
{
    double d = 0.0;
    double t = 0.0;
    int8_t s = 0;
    double v = 0.0;

    char charD[5];
    char charT[4];
    char charS[2];
    char charV[4];

    strncpy(charD, serialusM2M.buffer + 3, 4);
    strncpy(charT, serialusM2M.buffer + 7, 3);
    strncpy(charS, serialusM2M.buffer + 10, 1);
    strncpy(charV, serialusM2M.buffer + 11, 3);

    charD[4] = '\0';
    charT[3] = '\0';
    charV[3] = '\0';
    charS[1] = '\0';

    // Convert the substrings to double
    d = (double)atof(charD);
    t = (double)atof(charT);
    v = (double)atof(charV);
    s = (int8_t)atoi(charS);
    
    if (s==0){
        s=-1; 
    }
    if (t>180)
    {
        t=(360-t)*(-1);
    }          

    if (abs(d) > 3000 || abs(t) > 180 || abs(v) > 200 || abs(s) != 1)
    {
        printf("data inchoerante d: %f,t: %f ,V %f , s%d \n ", (float)d, (float)t, (float)v, s);
    }
    else
    {
        calage_Y(d, t, s, v);
        print_pos();
    }
}

void get_couleur(){
    if (COULEUR==BLEU){
        printf("0 \n");
    }
    else{
        if (COULEUR==JAUNE){
        printf("1 \n");}
        else{
            printf("no Coulor debug couleur=%d \n",COULEUR);
       
        }
     
    }
   
    
 
         
}

void set_couleur(){
    int8_t coul=0;
    char charc[2];
    strncpy(charc, serialusM2M.buffer + 3, 1);
    charc[1]='\0';
    coul= (int8_t) atoi(charc);
    if (coul==BLEU){
        COULEUR=BLEU;
        printf("bleu set \n");
    }
    if (coul==JAUNE){
        COULEUR=JAUNE;
        printf("jaune set \n");
    }
    
           
    
}

void calageALL()
{
    calage_depart(STRAT1);
    print_pos();
    // print_pos();
}
void reset_overflow_error()
{
    U1STAbits.OERR = 0;
    printf("overflow error");
}
void InitPosM2M()
{
    double x_ = 0.0;
    double y_ = 0.0;
    double t_ = 0.0;

    char charX[5];
    char charY[5];
    char charTheta[4];

    // Extract x, y, and theta substrings from the buffer
    strncpy(charX, serialusM2M.buffer + 3, 4);
    strncpy(charY, serialusM2M.buffer + 7, 4);
    strncpy(charTheta, serialusM2M.buffer + 11, 3);

    // Null-terminate the substrings
    charX[4] = '\0';
    charY[4] = '\0';
    charTheta[3] = '\0';
    // Convert the substrings to double
    x_ = (double)atof(charX);
    y_ = (double)atof(charY);
    t_ = (double)atof(charTheta);
     if (t_>180)
    {
        t_=(360-t_)*(-1);
    }
    if (abs(x_) > 3000 || abs(y_) > 2000 || abs(t_) > 180)
    {
        printf("data inchoerante x: %f,y: %f ,theta %f \n ", (float)x_, (float)y_, (float)t_);
    }
    else
    {
        printf("Init X : %f, Y : %f, Teta : %f \n", (float)x_, (float)y_, (float)t_);
        init_position_robot(x_, y_, t_);
    }
}

void ori()
{
    double a = 0.0;
    double v = 0.0;

    char chara[4];
    char charv[4];

    // Extract x, y, and theta substrings from the buffer
    strncpy(chara, serialusM2M.buffer + 3, 3);
    strncpy(charv, serialusM2M.buffer + 6, 3);

    // Null-terminate the substrings
    chara[3] = '\0';
    charv[3] = '\0';
    // Convert the substrings to double
    a = (double)atof(chara);
    v = (double)atof(charv);
    if (a>180)
    {
        a=(360-a)*(-1);
    }
      if (abs(a) > 180 || abs(v) > 200)
    {
        printf("data inchoerante a : %f, v : %f\n ", (float)a, (float)v);
    }
    else
    {
        init_clignotement();
        print_erreur_deplacementM2M(_orienter(a, v));
    }
}

void cib()
{
    double x = 0.0;
    double y = 0.0;
    double v = 0.0;

    char charX[5];
    char charY[5];
    char charV[4];

    // Extract x, y, and theta substrings from the buffer
    strncpy(charX, serialusM2M.buffer + 3, 4);
    strncpy(charY, serialusM2M.buffer + 7, 4);
    strncpy(charV, serialusM2M.buffer + 11, 3);

    // Null-terminate the substrings
    charX[4] = '\0';
    charY[4] = '\0';
    charV[3] = '\0';
    // Convert the substrings to double
    x = (double)atof(charX);
    y = (double)atof(charY);
    v = (double)atof(charV);
    if (abs(x) > 4000 || abs(y) > 4000 || abs(v) > 200)
    {
        printf("data inchoerante x: %f,y: %f ,V %f \n ", (float)x, (float)y, (float)v);
    }
    else
    {
        init_clignotement();
        print_erreur_deplacementM2M(_cibler(x, y, v));
    }
}

void av()
{
    double d = 0.0;
    double v = 0.0;

    char chard[5];
    char charv[4];

    // Extract x, y, and theta substrings from the buffer
    strncpy(chard, serialusM2M.buffer + 3, 4);
    strncpy(charv, serialusM2M.buffer + 7, 3);

    // Null-terminate the substrings
    chard[4] = '\0';
    charv[3] = '\0';
    // Convert the substrings to double
    d = (double)atof(chard);
    v = (double)atof(charv);
    if (d > 3000 || abs(v) > 200 || d < 0)
    {
        printf("data inchoerante av d : %f, v : %f\n ", (float)d, (float)v);
    }
    else
    {
        init_clignotement();
        print_erreur_deplacementM2M(_avancer_reculer(d, v));
    }
}

void rec()
{
    double d = 0.0;
    double v = 0.0;

    char chard[5];
    char charv[4];

    // Extract x, y, and theta substrings from the buffer
    strncpy(chard, serialusM2M.buffer + 3, 4);
    strncpy(charv, serialusM2M.buffer + 7, 3);

    // Null-terminate the substrings
    chard[4] = '\0';
    charv[3] = '\0';
    // Convert the substrings to double
    d = (double)atof(chard);
    v = (double)atof(charv);
    if (d > 3000 || abs(v) > 200 || d < 0)
    {
        printf("data inchoerante rec d : %f, v : %f\n ", (float)d, (float)v);
    }
    else
    {
        init_clignotement();
        print_erreur_deplacementM2M(_avancer_reculer(-d, v));
    }
}

void rej()
{
    double x = 0.0;
    double y = 0.0;
    int8_t s = 0;
    double v = 0.0;

    char charX[5];
    char charY[5];
    char charS[2];
    char charV[4];

    strncpy(charX, serialusM2M.buffer + 3, 4);
    strncpy(charY, serialusM2M.buffer + 7, 4);
    strncpy(charS, serialusM2M.buffer + 11, 1);
    strncpy(charV, serialusM2M.buffer + 12, 3);

    charX[4] = '\0';
    charY[4] = '\0';
    charV[3] = '\0';
    charS[1] = '\0';

    // Convert the substrings to double
    x = (double)atof(charX);
    y = (double)atof(charY);
    v = (double)atof(charV);
    s = (int8_t)atoi(charS);
    
    if (s==0){
        s=-1; 
    }
                  

    if (abs(x) > 3000 || abs(y) > 2000 || abs(v) > 200 || abs(s) != 1)
    {
        printf("data inchoerante x: %f,y: %f ,V %f , s%d \n ", (float)x, (float)y, (float)v, s);
    }
    else
    {
        init_clignotement();
        
        print_erreur_deplacementM2M(_rejoindre(x, y, s, v));
    }
}

void passe_par()
{

    double x = 0.0;
    double y = 0.0;
    int8_t s = 0;
    double v = 0.0;
    int8_t l = 0;

    char charX[5];
    char charY[5];
    char charS[2];
    char charV[4];
    char charl[2];
    char last;

    strncpy(charX, serialusM2M.buffer + 3, 4);
    strncpy(charY, serialusM2M.buffer + 7, 4);
    strncpy(charS, serialusM2M.buffer + 11, 1);
    strncpy(charV, serialusM2M.buffer + 12, 3);
    strncpy(charl, serialusM2M.buffer + 15, 1);

    charX[4] = '\0';
    charY[4] = '\0';
    charS[1] = '\0';
    charV[3] = '\0';
    charl[1] = '\0';

    // Convert the substrings to double
    x = (double)atof(charX);
    y = (double)atof(charY);
    v = (double)atof(charV);
    s = (int8_t)atoi(charS);
    l = (int8_t)atoi(charl);

    switch (l)
    {
    case 0:
        last = DEBUT_TRAJECTOIRE;
        break;
    case 1:
        last = MILIEU_TRAJECTOIRE;
        break;
    case 2:
        last = FIN_TRAJECTOIRE;
        break;
    default:
        last = FIN_TRAJECTOIRE;
        break;
    }

    if (abs(x) > 3000 || abs(y) > 2000 || abs(v) > 200 || abs(s) != 1)
    {
        printf("data inchoerante x: %f,y: %f ,V %f , s%d \n ", (float)x, (float)y, (float)v, s);
    }
    else
    {
        init_clignotement();
        print_erreur_deplacementM2M(_passe_part(x, y, s, v, last));
    }
}

void set_Break(){
    brake();
    printf("brake\n");
}

void set_PID_Vitesse()
{
    double _KP = 0.0;
    double _KI = 0.0;
    double _KD = 0.0;

    char charX[6];
    char charY[6];
    char charV[6];

    // Extract x, y, and theta substrings from the buffer
    strncpy(charX, serialusM2M.buffer + 3, 5);
    strncpy(charY, serialusM2M.buffer + 8, 5);
    strncpy(charV, serialusM2M.buffer + 13, 5);

    // Null-terminate the substrings
    charX[5] = '\0';
    charY[5] = '\0';
    charV[5] = '\0';
    // Convert the substrings to double
    _KP = ((double)atof(charX)) / 10000;
    _KI = (double)atof(charY) / 100000;
    _KD = (double)atof(charV) / 10000;
    if (_KP > 1 || _KI > 1 || _KD > 1)
    {
        printf("data inchoerante kp: %f,ki: %f ,kd %f \n ", (float)_KP, (float)_KI, (float)_KD);
    }
    else
    {
        // PID VITESSE DISTANCE
        PID.VITESSE_DIS.KP = _KP;
        PID.VITESSE_DIS.KI = _KI;
        PID.VITESSE_DIS.KD = _KD;
        printf("VITESSE_DIST kp: %f,ki: %f ,kd %f \n ", (float)PID.VITESSE_DIS.KP, (float)PID.VITESSE_DIS.KI, (float)PID.VITESSE_DIS.KD);
    }
}
void set_PID_Break()
{

    double _KP = 0.0;
    double _KI = 0.0;
    double _KD = 0.0;

    char charX[6];
    char charY[6];
    char charV[6];

    // Extract x, y, and theta substrings from the buffer
    strncpy(charX, serialusM2M.buffer + 3, 5);
    strncpy(charY, serialusM2M.buffer + 8, 5);
    strncpy(charV, serialusM2M.buffer + 13, 5);

    // Null-terminate the substrings
    charX[5] = '\0';
    charY[5] = '\0';
    charV[5] = '\0';
    // Convert the substrings to double
    _KP = ((double)atof(charX)) / 100000;
    _KI = (double)atof(charY) / 100000;
    _KD = (double)atof(charV) / 100000;
    if (_KP > 1 || _KI > 1 || _KD > 1)
    {
        printf("data inchoerante kp: %f,ki: %f ,kd %f \n ", (float)_KP, (float)_KI, (float)_KD);
    }
    else
    {
        // PID BRAKE
        PID.BRAKE.KP = _KP;
        PID.BRAKE.KI = _KI;
        PID.BRAKE.KD = _KD;
        printf("BREAK kp: %f,ki: %f ,kd %f \n ", (float)PID.BRAKE.KP, (float)PID.BRAKE.KI, (float)PID.BRAKE.KD);
    }
}

void set_ENTRAXE_MM()
{
    double EM = 0.0;
    char charEM[7];
    strncpy(charEM, serialusM2M.buffer + 3, 6);

    charEM[6] = '\0';

    EM = ((double)atof(charEM)) / 100;
    ENTRAXE_MM = EM;
    calcul_var_odom_asserv();

    printf("ENTRAXE_MM = %f \n , ENTRAXE_TICKS= %f", ENTRAXE_MM, ENTRAXE_TICKS);
}

void set_DIAMETRE_ROUE_CODEUSE()
{
    double DRC = 0.0;
    char charDRC[7];
    strncpy(charDRC, serialusM2M.buffer + 3, 6);

    charDRC[6] = '\0';

    DRC = ((double)atof(charDRC)) / 100;
    DIAMETRE_ROUE_CODEUSE = DRC;
    calcul_var_odom_asserv();
    printf("DIAMETRE_ROUE_CODEUSE = %f \n ", DIAMETRE_ROUE_CODEUSE);
}

void set_PERIMETRE_ROUE_MM()
{
    double PR = 0.0;
    char charPR[7];
    strncpy(charPR, serialusM2M.buffer + 3, 6);

    charPR[6] = '\0';

    PR = ((double)atof(charPR)) / 100;
    PERIMETRE_ROUE_MM = PR;
    calcul_var_odom_asserv();

    printf("PERIMETRE_ROUE_MM = %f ; MM_PAR_TICKS = %f\n ", PERIMETRE_ROUE_MM, MM_PAR_TICKS);
}

void set_coef_D()
{

    double CD = 0.0;
    char charCD[6];
    strncpy(charCD, serialusM2M.buffer + 3, 5);

    charCD[5] = '\0';

    CD = ((double)atof(charCD)) / 10000;
    COEF_D = CD;

    printf("COEF_D = %f \n ", COEF_D);
}

void set_coef_G()
{

    double CG = 0.0;
    char charCG[6];
    strncpy(charCG, serialusM2M.buffer + 3, 5);

    charCG[5] = '\0';

    CG = ((double)atof(charCG)) / 10000;
    COEF_G = CG;

    printf("COEF_G = %f \n ", COEF_G);
}

void set_MAX_ERREUR_INTEGRALLE_V()
{
    double MEV = 0.0;
    char charMEV[7];
    strncpy(charMEV, serialusM2M.buffer + 3, 6);

    charMEV[6] = '\0';

    MEV = ((double)atof(charMEV));
    MAX_ERREUR_INTEGRALLE_V = MEV;
    PID.VITESSE_DIS.max_I = MAX_ERREUR_INTEGRALLE_V;

    printf("MAX_ERREUR_INTEGRALLE_V = %f \n", MAX_ERREUR_INTEGRALLE_V);
}

// Set MAX_E_INTEGRALLE_BRAKE
void set_MAX_E_INTEGRALLE_BRAKE()
{
    double MEB = 0.0;
    char charMEB[7];
    strncpy(charMEB, serialusM2M.buffer + 3, 6);

    charMEB[6] = '\0';

    MEB = ((double)atof(charMEB));
    MAX_E_INTEGRALLE_BRAKE = MEB;
    PID.BRAKE.max_I = MAX_E_INTEGRALLE_BRAKE;

    printf("MAX_E_INTEGRALLE_BRAKE = %f \n", MAX_E_INTEGRALLE_BRAKE);
}

// Set SEUIL_IMMOBILITE
void set_SEUIL_IMMOBILITE()
{
    double SI = 0.0;
    char charSI[7];
    strncpy(charSI, serialusM2M.buffer + 3, 6);

    charSI[6] = '\0';

    SI = ((double)atof(charSI)) / 100;
    SEUIL_IMMOBILITE = SI;
    PID.VITESSE_DIS.seuil_immobilite = SEUIL_IMMOBILITE;
    printf("SEUIL_IMMOBILITE = %f \n", SEUIL_IMMOBILITE);
}

void set_VITESSE_CONSIGNE_MAX_MM()
{
    double VCMM = 0.0;
    char charVCMM[3];
    strncpy(charVCMM, serialusM2M.buffer + 3, 2);

    charVCMM[2] = '\0';

    VCMM = ((double)atof(charVCMM)) / 10;
    VITESSE_CONSIGNE_MAX_MM = VCMM;
    calcul_var_odom_asserv();

    printf("VITESSE_CONSIGNE_MAX_MM = %f \n", VITESSE_CONSIGNE_MAX_MM);
}

void set_VITESSE_DISTANCE_MIN()
{
    double VDM = 0.0;
    char charVDM[7];
    strncpy(charVDM, serialusM2M.buffer + 3, 6);

    charVDM[6] = '\0';

    VDM = ((double)atof(charVDM)) / 1000;
    VITESSE_DISTANCE_MIN = VDM;
    calcul_var_odom_asserv();

    printf("VITESSE_DISTANCE_MIN = %f \n", VITESSE_DISTANCE_MIN);
}

void set_VITESSE_MAX_MM_TENSION()
{
    double VMMT = 0.0;
    char charVMMT[5];
    strncpy(charVMMT, serialusM2M.buffer + 3, 4);

    charVMMT[4] = '\0';

    VMMT = ((double)atof(charVMMT)) / 100;
    VITESSE_MAX_MM_TENSION = VMMT;
    calcul_var_odom_asserv();

    printf("VITESSE_MAX_MM_TENSION = %f \n", VITESSE_MAX_MM_TENSION);
}

void set_DISTANCE_CONSIGNE_MM()
{
    double DCM = 0.0;
    char charDCM[7];
    strncpy(charDCM, serialusM2M.buffer + 3, 6);

    charDCM[6] = '\0';

    DCM = ((double)atof(charDCM)) / 1000;
    DISTANCE_CONSIGNE_MM = DCM;
    calcul_var_odom_asserv();

    printf("%f \n", DISTANCE_CONSIGNE_MM);
}

void set_ACC_POSITION_CONSIGNE()
{
    double APC = 0.0;
    char charAPC[5];
    strncpy(charAPC, serialusM2M.buffer + 3, 4);

    charAPC[4] = '\0';

    APC = ((double)atof(charAPC)) / 1000;
    ACC_POSITION_CONSIGNE = APC;
    acc.acceleration.position.max = ACC_POSITION_CONSIGNE;
    printf("%f \n", ACC_POSITION_CONSIGNE);
}

void set_DCC_POSITION_CONSIGNE()
{
    double DPC = 0.0;
    char charDPC[5];
    strncpy(charDPC, serialusM2M.buffer + 3, 4);

    charDPC[4] = '\0';
    DPC = ((double)atof(charDPC)) / 1000;
    DCC_POSITION_CONSIGNE = DPC;
    acc.deceleration.position.max = DCC_POSITION_CONSIGNE;

    printf(" %f \n", DCC_POSITION_CONSIGNE);
}

void set_ACC_POSITION_MIN()
{
    double APM = 0.0;
    char charAPM[5];
    strncpy(charAPM, serialusM2M.buffer + 3, 4);

    charAPM[4] = '\0';

    APM = ((double)atof(charAPM)) / 1000;
    ACC_POSITION_MIN = APM;
    acc.acceleration.position.min = ACC_POSITION_MIN;

    printf(" %f \n", ACC_POSITION_MIN);
}

void set_DCC_POSITION_MIN()
{
    double DPM = 0.0;
    char charDPM[5];
    strncpy(charDPM, serialusM2M.buffer + 3, 4);

    charDPM[4] = '\0';

    DPM = ((double)atof(charDPM)) / 1000;
    DCC_POSITION_MIN = DPM;
    acc.deceleration.position.min = DCC_POSITION_MIN;

    printf(" %f \n", DCC_POSITION_MIN);
}

void set_VITESSE_ANGLE_MAX()
{
    double VAM = 0.0;
    char charVAM[5];
    strncpy(charVAM, serialusM2M.buffer + 3, 4);

    charVAM[4] = '\0';

    VAM = ((double)atof(charVAM)) / 1000;
    VITESSE_ANGLE_MAX = VAM;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_ANGLE_MAX);
}

void set_VITESSE_ANGLE_MIN()
{
    double VAMI = 0.0;
    char charVAMI[5];
    strncpy(charVAMI, serialusM2M.buffer + 3, 4);

    charVAMI[4] = '\0';

    VAMI = ((double)atof(charVAMI)) / 1000;
    VITESSE_ANGLE_MIN = VAMI;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_ANGLE_MIN);
}

void set_ORIENTATION_CONSIGNE_DEG()
{
    double OCD = 0.0;
    char charOCD[6];
    strncpy(charOCD, serialusM2M.buffer + 3, 5);

    charOCD[5] = '\0';

    OCD = ((double)atof(charOCD)) / 100;
    ORIENTATION_CONSIGNE_DEG = OCD;
    calcul_var_odom_asserv();

    printf(" %f \n", ORIENTATION_CONSIGNE_DEG);
}

void set_ACC_ORIENTATION_CONSIGNE()
{
    double AOC = 0.0;
    char charAOC[5];
    strncpy(charAOC, serialusM2M.buffer + 3, 4);

    charAOC[4] = '\0';

    AOC = ((double)atof(charAOC)) / 100;
    ACC_ORIENTATION_CONSIGNE = AOC;
    acc.acceleration.orientation.max = ACC_ORIENTATION_CONSIGNE;

    printf("ACC_ORIENTATION_CONSIGNE = %f \n", ACC_ORIENTATION_CONSIGNE);
}

void set_DCC_ORIENTATION_CONSIGNE()
{
    double DOC = 0.0;
    char charDOC[5];
    strncpy(charDOC, serialusM2M.buffer + 3, 4);

    charDOC[4] = '\0';

    DOC = ((double)atof(charDOC)) / 100;
    DCC_ORIENTATION_CONSIGNE = DOC;
    acc.deceleration.orientation.max = DCC_ORIENTATION_CONSIGNE;

    printf(" %f \n", DCC_ORIENTATION_CONSIGNE);
}

void set_ACC_ORIENTATION_MIN()
{
    double AOM = 0.0;
    char charAOM[5];
    strncpy(charAOM, serialusM2M.buffer + 3, 4);

    charAOM[4] = '\0';

    AOM = ((double)atof(charAOM)) / 100;
    ACC_ORIENTATION_MIN = AOM;
    acc.acceleration.orientation.min = ACC_ORIENTATION_MIN;

    printf(" %f \n", ACC_ORIENTATION_MIN);
}

void set_DCC_ORIENTATION_MIN()
{
    double DOM = 0.0;
    char charDOM[5];
    strncpy(charDOM, serialusM2M.buffer + 3, 4);

    charDOM[4] = '\0';

    DOM = ((double)atof(charDOM)) / 100;
    DCC_ORIENTATION_MIN = DOM;
    acc.deceleration.orientation.min = DCC_ORIENTATION_MIN;

    printf(" %f \n", DCC_ORIENTATION_MIN);
}

void reset_PID_Vitesse()
{

    // PID VITESSE DISTANCE
    PID.VITESSE_DIS.KP = VITESSE_DIS_KP;
    PID.VITESSE_DIS.KI = VITESSE_DIS_KI;
    PID.VITESSE_DIS.KD = VITESSE_DIS_KD;
    printf("%f_%f_%f\n ", (float)PID.VITESSE_DIS.KP, (float)PID.VITESSE_DIS.KI, (float)PID.VITESSE_DIS.KD);
}
void reset_PID_Break()
{

    // PID BRAKE
    PID.BRAKE.KP = KP_BRAKE;
    PID.BRAKE.KI = KI_BRAKE;
    PID.BRAKE.KD = KD_BRAKE;
    printf("%f_%f_%f\n ", (float)PID.BRAKE.KP, (float)PID.BRAKE.KI, (float)PID.BRAKE.KD);
}

void reset_ENTRAXE_MM()
{
    ENTRAXE_MM = _ENTRAXE_MM;
    calcul_var_odom_asserv();
    printf("entraxe mm : %f  , ENTRAXE_TICKS= %f \n", ENTRAXE_MM, ENTRAXE_TICKS);
}

void reset_DIAMETRE_ROUE_CODEUSE()
{
    DIAMETRE_ROUE_CODEUSE = _DIAMETRE_ROUE_CODEUSE;
    calcul_var_odom_asserv();
    printf(" %f \n ", DIAMETRE_ROUE_CODEUSE);
}

void reset_PERIMETRE_ROUE_MM()
{
    PERIMETRE_ROUE_MM = _PERIMETRE_ROUE_MM;
    calcul_var_odom_asserv();
    printf("%f _ %f\n ", PERIMETRE_ROUE_MM, MM_PAR_TICKS);
}

void reset_coef_D()
{
    COEF_D = _COEF_D;
    calcul_var_odom_asserv();
    printf("%f \n ", COEF_D);
}

void reset_coef_G()
{
    COEF_G = _COEF_G;
    calcul_var_odom_asserv();
    printf("%f \n ", COEF_G);
}

void reset_asserve()
{
    reinit_asserv();
    printf("asserve reset \n ");
}

void reset_VITESSE_CONSIGNE_MAX_MM()
{
    VITESSE_CONSIGNE_MAX_MM = _VITESSE_CONSIGNE_MAX_MM;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_CONSIGNE_MAX_MM);
}

void reset_VITESSE_DISTANCE_MIN()
{
    VITESSE_DISTANCE_MIN = _VITESSE_DISTANCE_MIN;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_DISTANCE_MIN);
}

void reset_VITESSE_MAX_MM_TENSION()
{
    VITESSE_MAX_MM_TENSION = _VITESSE_MAX_MM_TENSION;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_MAX_MM_TENSION);
}

void reset_DISTANCE_CONSIGNE_MM()
{
    DISTANCE_CONSIGNE_MM = _DISTANCE_CONSIGNE_MM;
    calcul_var_odom_asserv();

    printf(" %f \n", DISTANCE_CONSIGNE_MM);
}

void reset_VITESSE_ANGLE_MAX()
{
    VITESSE_ANGLE_MAX = _VITESSE_ANGLE_MAX;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_ANGLE_MAX);
}

void reset_VITESSE_ANGLE_MIN()
{
    VITESSE_ANGLE_MIN = _VITESSE_ANGLE_MIN;
    calcul_var_odom_asserv();

    printf(" %f \n", VITESSE_ANGLE_MIN);
}

// Reset ORIENTATION_CONSIGNE_DEG
void reset_ORIENTATION_CONSIGNE_DEG()
{
    ORIENTATION_CONSIGNE_DEG = _ORIENTATION_CONSIGNE_DEG;
    calcul_var_odom_asserv();

    printf(" %f \n", ORIENTATION_CONSIGNE_DEG);
}

bool sontdesdigits(const char *str)
{

    for (int i = 0; str[i] != '\r'; i++)
    {
        if (!isdigit(str[i]))
        {
            printf("error::");
            PutcUART(UART_XBEE, str[i]);
            return false;
        }
    }
    return true;
}

void print_erreur_deplacementM2M(_enum_erreur_asserv erreur)
{
    
    serialusM2M.clignotement_en_cours = false;
    switch (erreur)
    {
    case EVITEMENT:
        printf("1\n");
        break;
    case BLOCAGE:
        printf("2\n");
        break;
    case DEPLACEMENT_NORMAL:
        print_pos();
        break;
    }
}

void init_clignotement()
{
    printf("clignotement\r");
    serialusM2M.clignotement_en_cours = true;
}

void calcul_var_odom_asserv()
{
    PERIMETRE_ROUE_MM=DIAMETRE_ROUE_CODEUSE*_Pi;
    MM_PAR_TICKS = PERIMETRE_ROUE_MM / CODEUR_D_NB_IMP_LOG;
    TICKS_PAR_MM = CODEUR_D_NB_IMP_LOG / PERIMETRE_ROUE_MM;

    ENTRAXE_TICKS = CODEUR_D_NB_IMP_LOG * ENTRAXE_MM / PERIMETRE_ROUE_MM;

    VITESSE_CONSIGNE_MAX_PAS = VITESSE_CONSIGNE_MAX_MM * TICKS_PAR_MM;
    VITESSE_DISTANCE_MIN_PAS = (VITESSE_DISTANCE_MIN * TICKS_PAR_MM);
    VITESSE_MAX_TENSION = (VITESSE_MAX_MM_TENSION * TICKS_PAR_MM);

    DISTANCE_CONSIGNE_PAS = (DISTANCE_CONSIGNE_MM * TICKS_PAR_MM);

    VITESSE_ANGLE_PAS = (VITESSE_ANGLE_MAX * (ENTRAXE_TICKS / 2.));
    VITESSE_ANGLE_MIN_PAS = (VITESSE_ANGLE_MIN * (ENTRAXE_TICKS / 2.));

    ORIENTATION_CONSIGNE_PAS = (ORIENTATION_CONSIGNE_DEG * Pi / 180. * (ENTRAXE_TICKS / 2.));
}

void DEBUG_ON(){
#ifndef DEBUG_ACTIF 
    #define DEBUG_ACTIF 
#endif
printf("Debug ON\n");
}

void DEBUG_OFF(){

#ifdef DEBUG_ACTIF    
    #undef DEBUG_ACTIF 
#endif
    printf("Debug OFF\n");
}


void AX_set_ang(){
    uint8_t id = 0;
    int16_t angle =0;
    uint16_t v = 0;

    char charID[3];
    char charAngle[4];
    char charV[5];

    // Extract id, angle, and v substrings from the buffer
    strncpy(charID, serialusM2M.buffer + 3, 2);
    strncpy(charAngle, serialusM2M.buffer + 5, 3);
    strncpy(charV, serialusM2M.buffer + 8, 4);

    // Null-terminate the substrings
    charID[2] = '\0';
    charAngle[3] = '\0';
    charV[4] = '\0';

    // Convert the substrings to double

    id = (uint8_t) atoi(charID);
    angle = (int16_t) atoi(charAngle);
    v = (uint16_t) atoi(charV);

    if (!(id >= 0 && id <= ID_MAX_AX12 && abs(angle) <= 270 && v >= 0 && v <= 1023))
    {
        printf("data inchoerante ID: %i, angle: %i , v: %i \n ", (uint8_t)id, (int16_t)angle, (uint16_t)v);
    }
    else
    {

        synchro_AX12(id, (float)angle, v, SANS_ATTENTE);
        print_erreur_ax12();

    }

}

void AX_set_pos(){

    uint8_t id = 0;
    int16_t position =0;
    uint16_t v = 0;

    char charID[3];
    char charPosition[5];
    char charV[5];

    // Extract id, angle, and v substrings from the buffer
    strncpy(charID, serialusM2M.buffer + 3, 2);
    strncpy(charPosition, serialusM2M.buffer + 5, 4);
    strncpy(charV, serialusM2M.buffer + 9, 4);

    // Null-terminate the substrings
    charID[2] = '\0';
    charPosition[4] = '\0';
    charV[4] = '\0';

    // Convert the substrings to double

    id = (uint8_t) atoi(charID);
    position = (int16_t) atoi(charPosition);
    v = (uint16_t) atoi(charV);

    if (!((id >= 0 && id <= ID_MAX_AX12 && position>=0 && position <= 1023 && v >= 0 && v <= 1023)))
    {
        printf("data inchoerante ID: %d, position: %d , v: %d \n ", id, position, v);
    }
    else
    {

        angle_AX12(id, position, v, SANS_ATTENTE);
        print_erreur_ax12();

    }


}

void AX_set_led(){
    uint8_t id = 0;
    uint8_t state = 0;

    char charID[3];
    char charState[2];

    strncpy(charID, serialusM2M.buffer + 3, 2);
    strncpy(charState, serialusM2M.buffer + 5, 1);

    id = (uint8_t) atoi(charID);
    state = (uint8_t) atoi(charState);

    if (state){

        allumer_LED_AX12((uint8_t)id);
        print_erreur_ax12();
    }
    else if (!state){

        eteindre_LED_AX12((uint8_t) id);
        print_erreur_ax12();
    }

    else {
        printf("on//off AX Led error\n");
    }
}

void AX_set_torque(){
    uint8_t id = 0;
    uint8_t state = 0;

    char charID[3];
    char charState[2];

    strncpy(charID, serialusM2M.buffer + 3, 2);
    strncpy(charState, serialusM2M.buffer + 5, 1);

    id = (uint8_t) atoi(charID);
    state = (uint8_t) atoi(charState);

    if (state){

        torque_enable_ax12((uint8_t)id, true);
        print_erreur_ax12();
    }
    else if (!state){

        torque_enable_ax12((uint8_t)id, false);
        print_erreur_ax12();
    }

    else {
        printf("on//off AX torque Error \n");
    }

}

void AX_set_alim(){

    uint8_t state = 0;

    char charState[2];

    strncpy(charState, serialusM2M.buffer + 3, 1);

    state = (uint8_t) atoi(charState);

    if (state){
        printf("iAX -> on \n");
        INHIBIT_AX12 = ALLUME;
    }
    else if (!state){
        printf("AX->  off \n");
        INHIBIT_AX12 = ETEINT;
    }

    else {
        printf("on//off AX alim Error \n");
    }

}

void AX_get_pos(){
    int16_t id = 0;

    char charID[3];

    strncpy(charID, serialusM2M.buffer + 3, 2);

    id = (int16_t) atoi(charID);
    
    print_position_ax12(id, read_data(id, LIRE_POSITION_ACTU));
     
    id = check_id_ax12_m2m(id);
    if (id == TOUS_LES_AX12)
    {
        uint8_t id = 0, index = 0;
        uint8_t tab[ID_MAX_AX12];
        for (id = 0 ; id < ID_MAX_AX12 ; id++)
        {
            if (Ping(id) == REPONSE_OK)
            {
                tab[index++] = id;
            }
        }

        
            //printf("\r");
            for (id = 0 ; id < index ; id++)
            {
                print_position_ax12(tab[id], read_data(tab[id], LIRE_POSITION_ACTU));
            }
            printf("\n");
        
    }
    else
    {
        if (Ping(id) == REPONSE_OK)
        {
            
            print_position_ax12(id, read_data(id, LIRE_POSITION_ACTU));
            printf("\n");
        }
        else 
            printf("PAS DE REPONSE \n");
    }


}

void AX_get_ping(){
    int16_t id = 0;

    char charID[3];

    strncpy(charID, serialusM2M.buffer + 3, 2);

    id = (int16_t) atoi(charID);

     // si c'est un id
    id = check_id_ax12_m2m(id);
    if (id == TOUS_LES_AX12)
    {
        uint8_t id = 0;
        for (id = 0 ; id < ID_MAX_AX12 ; id++)
        {
            if (Ping(id) == REPONSE_OK)
            {
                print_ping(id);
            }
            
        }
    printf("\n");
    }
    else if (id != -1)
    {
        if (Ping(id) == REPONSE_OK)
        {
            print_ping(id);
            printf("\n");
        }
        else 
            printf("NC");//Not Conected
            printf("\n");
    }
} 


void print_erreur_ax12()
{
    switch(ax12.erreur)
    {
        case PAS_D_ERREUR :  
            printf("0\n");
            break;
        case TIME_OUT :
            printf("1\n");
            break;
        case ERREUR_CS :
            printf("2\n");
            break;
        case LIMITATION_DE_COURANT :
            printf("3\n");
            break;
        case AUTRE_ERREUR :
            printf("5\n");
        default :
            break;
    }  
}

void print_position_ax12(uint8_t id, int16_t position)
{
    printf(" ID : %d =%d \r", id, position);
}

void print_ping(uint8_t id)
{
    printf("ID : %d \r", id);
}

int16_t check_id_ax12_m2m(int16_t id)
{
    if (!(id >= 0 && id <= ID_MAX_AX12))
            id = -1;
    
    else if (id==99)
    {
        id = TOUS_LES_AX12;
    }
    else 
        id =-1;
    
    if (id == -1)
        print_abort("4\n ");
    
    return id;
}

void Check_evitement() {
    int8_t sens=0;
    char chars[2];
    strncpy(chars, serialusM2M.buffer + 2, 1);
    chars[1]='\0';
    sens= (int8_t) atoi(chars);
    if (sens == 0) { // Arrière
        
        int8_t gauche=0;
        int8_t droite=0;
        int8_t centre=0;
        int robot_evit = 0;
        
        robot_evit = EVITEMENT_ADV.sens == MARCHE_ARRIERE && check_evitement_arriere();
        
        if ( ((EVITEMENT_ADV.cote & EV_CENTRE) != 0) && (CAPT_ADV_ARRIERE_C == ETAT_ADV_ARRIERE_C))
            centre = 1;
        else if ( ((EVITEMENT_ADV.cote & EV_GAUCHE) != 0) && (CAPT_ADV_ARRIERE_G == ETAT_ADV_ARRIERE_G))
            gauche = 1;
        else if ( ((EVITEMENT_ADV.cote & EV_DROIT) != 0) && (CAPT_ADV_ARRIERE_D == ETAT_ADV_ARRIERE_D))
            droite = 1;
        
        printf("Evitement arriere = %d / %d / %d / robot = %d\n ", gauche , centre, droite, robot_evit);
    }

    if (sens == 1) { // Avant
        int8_t gauche = 0;
        int8_t droite = 0;
        int8_t centre = 0;
        int robot_evit = 0;
        
        robot_evit = EVITEMENT_ADV.sens == MARCHE_AVANT && check_evitement_avant();
        
        if ( ((EVITEMENT_ADV.cote & EV_CENTRE) != 0) && (CAPT_ADV_AVANT_C == ETAT_ADV_AVANT_C))
            centre = 1;
        if ( ((EVITEMENT_ADV.cote & EV_GAUCHE) != 0) && (CAPT_ADV_AVANT_G == ETAT_ADV_AVANT_G))
            gauche = 1;
        if ( ((EVITEMENT_ADV.cote & EV_DROIT) != 0) && (CAPT_ADV_AVANT_D == ETAT_ADV_AVANT_D))
            droite = 1;
        
        printf("Evitement avant = %d / %d / %d / robot = %d\n ", gauche , centre, droite, robot_evit);
    }
}

void Evitement_on_off() {
    int8_t state=0;
    char chars[2];
    strncpy(chars, serialusM2M.buffer + 2, 1);
    chars[1]='\0';
    state= (int8_t) atoi(chars);
    if (state==1){
          EVITEMENT_ADV.actif = ON;
          printf("on \n");
    }
    else{
          EVITEMENT_ADV.actif = OFF; 
          printf("off \n");
    }            
}

void set_evitment() {
    int8_t state=0;
    char chars[2];
    strncpy(chars, serialusM2M.buffer + 2, 1);
    chars[1]='\0';
    state= (int8_t) atoi(chars);
    if (state==1){
         EVITEMENT_ADV.mode = EVITEMENT_NORMAL;
          printf("evitement normale \n");
    }
    else{
        EVITEMENT_ADV.mode = STOP;
        printf("evitement stop \n");
    }            
}

void start_match() {
     CPT_TEMPS_MATCH.actif = ON;
     printf("here we go again \n");
}

void recup_plante() {
    uint8_t strat = 0;
    uint8_t id = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    strncpy(char_val, serialusM2M.buffer + 3, 1);
    id = (uint8_t) atoi(char_val);

         if ((id == 1) && (strat == 1)) recup_plante4_ou_1(false, strat);
    else if ((id == 2) && (strat == 1)) recup_plante5_ou_2(false, strat);
    else if  (id == 3)                  recup_plante3     (false, true, strat);
    else if ((id == 4) && (strat == 0)) recup_plante4_ou_1(false, strat);
    else if ((id == 5) && (strat == 0)) recup_plante5_ou_2(false, strat);
    else printf("[%s] Bad ID %d for strat %d\n", __func__, id, strat);
}

void recup_plante_alt() {
    uint8_t strat = 0;
    uint8_t id = 0;
    double x_target = 0.0;
    double y_target = 0.0;
    double x_evitement = 0.0;
    char char_val[2];
    char char_val5[5];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    strncpy(char_val, serialusM2M.buffer + 3, 1);
    id = (uint8_t) atoi(char_val);

    strncpy(char_val5, serialusM2M.buffer + 4, 4);
    char_val5[4] = '\0';
    x_target = (double) atof(char_val5);

    strncpy(char_val5, serialusM2M.buffer + 8, 4);
    char_val5[4] = '\0';
    y_target = (double) atof(char_val5);

    strncpy(char_val5, serialusM2M.buffer + 12, 4);
    char_val5[4] = '\0';
    x_evitement = (double) atof(char_val5);

    if ((x_target > 3000    && x_target < 0   ) ||
        (y_target > 3000    && y_target < 0   ) ||
        (x_evitement > 3000 && x_evitement < 0)) {
        printf("[%s] Incoherent data: x_target = %f, y_target = %f, x_evitement = %f\n", __func__, x_target, y_target, x_evitement);
        return;
    }

         if ((id == 2) && (strat == 1)) recup_plante5_ou_2_alt(true, strat, x_target, y_target, x_target);
    else if ((id == 5) && (strat == 0)) recup_plante5_ou_2_alt(true, strat, x_target, y_target, x_target);
    else printf("[%s] Bad ID %d for strat %d\n", __func__, id, strat);

}

void depose_zone_depart() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    if (strat == 0) depose_zone_depart_strat1(true);
    else if (strat == 1) depose_zone_depart_strat2(true);
    else printf("[%s] Bad Strat %d\n", __func__, strat);
}

void depose_zone_reserv() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }

    depose_zone_reservee(true, strat);
}

void depose_zone_reserv_alt() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }

    depose_zone_reservee_alt(true, strat);
}

void depose_jardiniere() {
    uint8_t strat = 0;
    uint8_t id = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    strncpy(char_val, serialusM2M.buffer + 3, 1);
    id = (uint8_t) atoi(char_val);

    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }
         if (id == 0) depose_jardiniere1(true, strat);
    else if (id == 1) depose_jardiniere2(true, strat);
    else if (id == 2) depose_jardiniere3(true, strat);
    else printf("[%s] Bad ID %d for strat %d\n", __func__, id, strat);
}

void activ_panneaux_solaires() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);


    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }
    activation_panneaux_solaires(false, strat);
}

void zone_recharge() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }
    retour_zone_recharge(true, strat);
}

void calage_dep() {
    uint8_t strat = 0;
    char char_val[2];

    strncpy(char_val, serialusM2M.buffer + 2, 1);
    strat = (uint8_t) atoi(char_val);

    if ((strat != 0) && (strat != 1)) {
        printf("[%s] Incoherent data: strat = %d\n", __func__, strat);
        return;
    }
    calage_depart(strat);
}
