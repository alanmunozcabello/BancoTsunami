#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//Nombre: Alan Muñoz Cabello
typedef struct Sucursal{
    int numero_sucursal; //numero sucursal
    char direccion_sucursal[50]; //direccion de la sucursal
    char administrador[50]; //adminisrador acargo de la sucursal
}Sucursal, Sucu;

typedef struct Cliente{
    int sucursal_asociada_cliente; //sucursal a la que el cleinte pertenece
    char nombres_cliente[50];   //nombres cliente
    char apellidos_cliente[50]; //apellidos cliente
    char rut_cliente[20];   // rut/id de cleinte
}Cliente;

typedef struct Cuenta{
    char tipo_cuenta[20];    //Vista, Corriente o Ahorro
    int numero_cuenta;    //id asociado a la cuenta
    char rut_cliente_asociado_cuenta[20]; //cliente al que está ligado la cuenta
    float comision_mensual_cuenta;    //comision mensual (se añade al crear la cuenta)
    float tasa_interes_cuenta;   //tasa de interes de la cuenta
    int saldo_cuenta;  //saldo disponible
    int maximo_credito_negativo; //en caso de que sea cuenta corriente
    int transacciones_gratis; //en caso de cuenta vista (comienzan siendo 4)
    char estado_cuenta[20];    //activa o inactiva (en caso que sea de ahorro)
    int meses_transcurridos_cuenta;
}Cuenta;
//funciones

int longitud_de_cadena(char cadena_1[50]){ //funcion para obtener la longitud de una cadena
    int contador=0;
    while(*(cadena_1+contador)!='\0'){
        contador++;
    }
    return contador;
}

int comparar_cadenas(char cadena_1[50], char cadena_2[50]){ //comparar dos cadenas, si nos iguales se retorna 1
    int longitud_cadena_1=longitud_de_cadena(cadena_1);
    int longitud_cadena_2=longitud_de_cadena(cadena_2);
    if(longitud_cadena_1==longitud_cadena_2){//no tiene mucha seguridad ya que no es necesaria para el proyecto

        for(int contador=0; contador<longitud_cadena_1; contador++){
            if(*(cadena_1+contador)!=*(cadena_2+contador)){
                return 0;
            }
        }
        return 1;

    }else{
        return 0;
    }
}

void juntar_cadenas(char cadena_1[50], char cadena_2[50], char cadena_3[50]){ //juntar dos cadenas separadas por un espacio
    if(cadena_1!=NULL && cadena_2!=NULL){

        int contador_cadena1=0;
        int contador_cadena2=0;
        int contador_cadena3=0;

        while(*(cadena_1+contador_cadena1)!='\0'){
            *(cadena_3+contador_cadena3)=*(cadena_1+contador_cadena1);

            contador_cadena1++;
            contador_cadena3++;
        }
        //cadena_1+contador es '\0', por lo que se añade un espacio y se añade la cadena_2 a continuacion
        *(cadena_3+contador_cadena3)=' ';
        contador_cadena3++;

        while(*(cadena_2+contador_cadena2)!='\0'){
            *(cadena_3+contador_cadena3)=*(cadena_2+contador_cadena2);
            // *(cadena_3+contador)=*(cadena_1+contador);
            contador_cadena2++;
            contador_cadena3++;
        }
        //finalizar cadena_3 con un '\0'
        *(cadena_3+contador_cadena3)='\0';

    }else{
        printf("ERROR! una de las dos cadenas no existe");
        return;
    }
}

void guardar_archivo_sucursal(Sucursal* sucursales, int cantidad_sucursales){ //guardar todas las sucursales en el arreglo al archivo
    FILE* puntero_archivo_sucursal=fopen("sucursales.txt", "w"); //abrir archivo //cambiar a w de ser necesario

    if(puntero_archivo_sucursal==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        for(int contador=0; contador<cantidad_sucursales; contador++){
            fprintf(puntero_archivo_sucursal, "%i ", (*(sucursales+contador)).numero_sucursal); //numero de sucursal
            fprintf(puntero_archivo_sucursal, "%s ", (*(sucursales+contador)).direccion_sucursal); //direccion de sucursal
            fprintf(puntero_archivo_sucursal, "%s\n", (*(sucursales+contador)).administrador); //administrador
        } //en cada iteracion se guardan los datos de las sucursales
        fclose(puntero_archivo_sucursal);
    }
}

void guardar_archivo_criente(Cliente* clientes, int cantidad_clientes){
    FILE* puntero_archivo_cliente=fopen("clientes.txt", "w"); //abrir archivo //cambiar a w de ser necesario

    if(puntero_archivo_cliente==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        for(int contador=0; contador<cantidad_clientes; contador++){
            fprintf(puntero_archivo_cliente, "%i ", (*(clientes+contador)).sucursal_asociada_cliente );
            fprintf(puntero_archivo_cliente, "%s ", (*(clientes+contador)).nombres_cliente);
            fprintf(puntero_archivo_cliente, "%s ", (*(clientes+contador)).apellidos_cliente);
            fprintf(puntero_archivo_cliente, "%s\n", (*(clientes+contador)).rut_cliente);
        } //en cada iteracion se guardan los datos de los clientes
        fclose(puntero_archivo_cliente);
    }
}

void guardar_archivo_cuenta(Cuenta* cuentas, int cantidad_cuentas){
    FILE* puntero_archivo_cuenta=fopen("cuentas.txt", "w"); //abrir archivo //cambiar a w de ser necesario

    if(puntero_archivo_cuenta==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        for(int contador=0; contador<cantidad_cuentas; contador++){                     //guardar:
            fprintf(puntero_archivo_cuenta, "%i ", (*(cuentas+contador)).numero_cuenta); //numero cuenta
            fprintf(puntero_archivo_cuenta, "%s ", (*(cuentas+contador)).tipo_cuenta); //tipo de cuenta
            fprintf(puntero_archivo_cuenta, "%s ", (*(cuentas+contador)).rut_cliente_asociado_cuenta); //rut del cleiente asociado
            fprintf(puntero_archivo_cuenta, "%f ", (*(cuentas+contador)).comision_mensual_cuenta); //comision mensual
            fprintf(puntero_archivo_cuenta, "%f ", (*(cuentas+contador)).tasa_interes_cuenta); //tasa de interes
            fprintf(puntero_archivo_cuenta, "%i ", (*(cuentas+contador)).saldo_cuenta); //saldo
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "vista")){
                fprintf(puntero_archivo_cuenta, "%i ", (*(cuentas+contador)).transacciones_gratis);
            }
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "corriente")){
                fprintf(puntero_archivo_cuenta, "%i ", (*(cuentas+contador)).maximo_credito_negativo);
            }
            fprintf(puntero_archivo_cuenta, "%s ", (*(cuentas+contador)).estado_cuenta); //estado de cuenta
            fprintf(puntero_archivo_cuenta, "%i\n", (*(cuentas+contador)).meses_transcurridos_cuenta);
        } //en cada iteracion se guardan los datos de las cuentas
        fclose(puntero_archivo_cuenta);
    }
}

//vamos a hacer funciones similares a las de arriba, pero para cargar los datos de los archivos al programa

void cargar_sucursales(Sucursal* sucursales, int* cantidad_sucursales){ //carga todas las sucursales de el archivo al programa
    fflush(stdin);
    FILE* puntero_archivo_sucursal=fopen("sucursales.txt", "r"); //abrir archivo
    if(puntero_archivo_sucursal==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        int contador=0; //en cada iteracion se guardan los datos de las sucursales
        char* nombre=(char*)malloc(sizeof(char)*25);
        char* apellido=(char*)malloc(sizeof(char)*25);

        char* direccion=(char*)malloc(sizeof(char)*50);
        char* direccion_1=(char*)malloc(sizeof(char)*25);
        char* direccion_2=(char*)malloc(sizeof(char)*25);
        while(!feof(puntero_archivo_sucursal)){                                                 //formato de escritura y lectura
            fscanf(puntero_archivo_sucursal, "%i ", &((sucursales+contador)->numero_sucursal)); //numero de sucursal
            fscanf(puntero_archivo_sucursal, "%s %s ", direccion_1, direccion_2); //direccion de sucursal
            juntar_cadenas(direccion_1, direccion_2, direccion); //se juntanlas dos aprtes de la direccion en una sola
            strcpy((sucursales+contador)->direccion_sucursal, direccion); //se copia la direccion completa en el atributo de la sucursal
            fscanf(puntero_archivo_sucursal, "%s %s\n", nombre, apellido);
            juntar_cadenas(nombre, apellido, ((sucursales+contador)->administrador));
            contador++;
            *cantidad_sucursales=*cantidad_sucursales+1;
        }
        fclose(puntero_archivo_sucursal);
    }
}

void cargar_clientes(Cliente* clientes, int* cantidad_clientes){ //carga todas las sucursales de el archivo al programa
    FILE* puntero_archivo_cliente=fopen("clientes.txt", "r"); //abrir archivo
    if(puntero_archivo_cliente==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        int contador=0; //en cada iteracion se guardan los datos de los clientes 
        while(!feof(puntero_archivo_cliente)){                                                         //formato de escritura y lectura
            fscanf(puntero_archivo_cliente, "%i ", &((clientes+contador)->sucursal_asociada_cliente)); //ESCANEAR SUCURSAL A LA QUE PERTENECE

            //escanear primer y segundo nombre, juntarlos separados por un espacio en una sola cadena
            char* primer_nombre=(char*)malloc(sizeof(char)*50); 
            char* segundo_nombre=(char*)malloc(sizeof(char)*50); 
            fscanf(puntero_archivo_cliente, "%s %s ", primer_nombre, segundo_nombre); //ESCANEAR NOMBRES
            char* nombres=(char*)malloc(sizeof(char)*50);// juntar_cadenas primer_nombre, segundo_nombre 
            juntar_cadenas(primer_nombre, segundo_nombre, nombres);
            strcpy((clientes+contador)->nombres_cliente, nombres);

            //escanear primer y segundo apellido, juntarlos separados por un espacio en una sola cadena
            char* primer_apellido=(char*)malloc(sizeof(char)*50); 
            char* segundo_apellido=(char*)malloc(sizeof(char)*50);
            fscanf(puntero_archivo_cliente, "%s %s ", primer_apellido, segundo_apellido); //ESCANEAR APELLIDOS
            char* apellidos=(char*)malloc(sizeof(char)*50); // juntar_cadenas primer_apellido, segundo_apellido 
            juntar_cadenas(primer_apellido, segundo_apellido, apellidos);
            strcpy((clientes+contador)->apellidos_cliente, apellidos);

            fscanf(puntero_archivo_cliente, "%s ", ((clientes+contador))->rut_cliente); //ESCANEAR RUT

            contador++;
            *cantidad_clientes=*cantidad_clientes+1;
        }
        fclose(puntero_archivo_cliente);
    }
}

void cargar_cuentas(Cuenta* cuentas, int* cantidad_cuentas){ //carga todas las sucursales de el archivo al programa
    FILE* puntero_archivo_cuentas=fopen("cuentas.txt", "r"); //abrir archivo
    if(puntero_archivo_cuentas==NULL){ //si no se pudo abrir el archivo da error
        printf("ERROR! no se pudo abrir el archivo\n");

    }else{
        int contador=0; //en cada iteracion se guardan los datos de las cuentas
        while(!feof(puntero_archivo_cuentas)){                                            //formato de escritura y lectura
            fscanf(puntero_archivo_cuentas, "%i ", &((cuentas+contador)->numero_cuenta)); //numero de cuenta
            fscanf(puntero_archivo_cuentas, "%s ", ((cuentas+contador)->tipo_cuenta)); //tipo de cuenta
            fscanf(puntero_archivo_cuentas, "%s ", ((cuentas+contador)->rut_cliente_asociado_cuenta)); //rut del cliente asociado a la cuenta
            fscanf(puntero_archivo_cuentas, "%f ", &((cuentas+contador)->comision_mensual_cuenta)); //comision mensual de la cuenta
            fscanf(puntero_archivo_cuentas, "%f ", &((cuentas+contador)->tasa_interes_cuenta)); //tasa de interes de la cuenta
            fscanf(puntero_archivo_cuentas, "%i ", &((cuentas+contador)->saldo_cuenta)); //saldo cuenta
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "vista")){
                fscanf(puntero_archivo_cuentas, "%i", &((cuentas+contador)->transacciones_gratis));
            }
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "corriente")){
                fscanf(puntero_archivo_cuentas, "%i ", &((cuentas+contador)->maximo_credito_negativo));
            }
            fscanf(puntero_archivo_cuentas, "%s ", ((cuentas+contador)->estado_cuenta)); //estado de la cuenta
            fscanf(puntero_archivo_cuentas, "%i ", &((cuentas+contador)->meses_transcurridos_cuenta));
            contador++;
            *cantidad_cuentas=*cantidad_cuentas+1; //avanzar cuenta
        }
        fclose(puntero_archivo_cuentas);
    }
}

void imprimir_sucursales(Sucursal* sucursales, int cantidad_sucursales){//funciones de prueba. cambiar a lectura de archivo sucursal 
    for(int contador=0; contador<cantidad_sucursales; contador++){
        printf("numero sucursal: %i\n", (*(sucursales+contador)).numero_sucursal);
        printf("direccion sucursal: %s\n", (*(sucursales+contador)).direccion_sucursal);
        printf("administrador sucursal: %s\n", (*(sucursales+contador)).administrador); 
        printf("\n");
    }
}

void imprimir_clientes(Cliente* clientes, int cantidad_clientes, int numero_sucursal_perteneciente){//funcion para imprimir los clientes
    for(int contador=0; contador<cantidad_clientes; contador++){
        if((clientes+contador)->sucursal_asociada_cliente== numero_sucursal_perteneciente){
            printf("Nombre completo: %s %s\n", (*(clientes+contador)).nombres_cliente, (*(clientes+contador)).apellidos_cliente);
            printf("Rut: %s\n", (*(clientes+contador)).rut_cliente);
            printf("\n");
        }
    }
}

void imprimir_cuentas(Cuenta* cuentas, int cantidad_cuentas, char _rut_cliente_asociado[20]){
    for(int contador=0; contador<cantidad_cuentas; contador++){
        if(comparar_cadenas((cuentas+contador)->rut_cliente_asociado_cuenta, _rut_cliente_asociado)){
            printf("------------------------------\n");
            printf("Tipo de cuenta: %s\n", (cuentas+contador)->tipo_cuenta);
            printf("Numero de cuenta: %i\n", (cuentas+contador)->numero_cuenta);
            printf("Comision mensual: %f\n", (*(cuentas+contador)).comision_mensual_cuenta);
            printf("Tasa de interes mensual: %f\n", (*(cuentas+contador)).tasa_interes_cuenta);
            printf("Antiguedad de la cuenta: %i\n", (cuentas+contador)->meses_transcurridos_cuenta);
            printf("Saldo disponible: %i\n", (*(cuentas+contador)).saldo_cuenta);
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "corriente")){
                printf("Credito máximo negativo: %i\n", (cuentas+contador)->maximo_credito_negativo);
            }
            if(comparar_cadenas((cuentas+contador)->tipo_cuenta, "vista")){
                printf("Transacciones gratis restantes: %i\n", (cuentas+contador)->transacciones_gratis);
            }
            printf("Estado de la cuenta: %s\n", (cuentas+contador)->estado_cuenta);
            printf("------------------------------\n");
        }
    }
}

Cliente* buscar_cliente_en_sucursales_2(Cliente* clientes, char rut_cliente[20], int cantidad_clientes){ //funcion para saber direccion de memoria de un cliente especifico
    int contador=0;
    
    while(contador<cantidad_clientes){
        if(comparar_cadenas((clientes+contador)->rut_cliente, rut_cliente)){
            return (clientes+contador);
        }
        contador++;
    }
    return NULL; //se retorna NULL si se encuentra
}

void imprimir_cuenta(Cuenta* cuenta, Cliente* clientes, int cantidad_clientes){
    Cliente* cliente_asociado_cuenta=buscar_cliente_en_sucursales_2(clientes, cuenta->rut_cliente_asociado_cuenta, cantidad_clientes);
    if(!cliente_asociado_cuenta){
        printf("la cuenta no está asocuada a nadie mhhh...");
    }else{
        printf("Propietario de la cuenta: %s %s\n", cliente_asociado_cuenta->nombres_cliente, cliente_asociado_cuenta->apellidos_cliente);
    }
    printf("Rut cliente asociado: %s\n", cuenta->rut_cliente_asociado_cuenta);
    printf("Tipo de cuenta: %s\n", cuenta->tipo_cuenta);
    printf("Numero de cuenta: %i\n", cuenta->numero_cuenta);
    printf("Comision mensual: %f\n", (*(cuenta)).comision_mensual_cuenta);
    printf("Tasa de interes mensual: %f\n", (*(cuenta)).tasa_interes_cuenta);
    printf("Antiguedad de la cuenta: %i\n", cuenta->meses_transcurridos_cuenta);
    printf("Saldo disponible: %i\n", (*(cuenta)).saldo_cuenta);
    if(comparar_cadenas(cuenta->tipo_cuenta, "corriente")){
        printf("Credito máximo negativo: %i\n", cuenta->maximo_credito_negativo);
    }
    if(comparar_cadenas(cuenta->tipo_cuenta, "vista")){
        printf("Transacciones gratis restantes: %i\n", cuenta->transacciones_gratis);
    }
    printf("Estado de la cuenta: %s\n", cuenta->estado_cuenta);
}

void crear_sucursal(Sucursal* sucursal ,int numero_sucursal, char direccion_sucursal[50], char administrador[50]){ //crear sucursal. recibe numero y direccion
    sucursal->numero_sucursal=numero_sucursal;   //añade numero
    strcpy(sucursal->direccion_sucursal, direccion_sucursal); //añade direccion
    strcpy(sucursal->administrador, administrador); //añade administrador
}

void crear_cliente(Cliente* cliente, int sucursal_asociada, char nombres[50], char apellidos[50], char rut[20]){ //crear cliente. recibe nombres, apellidos, rut y sucursal asociada al cluente
    cliente->sucursal_asociada_cliente=sucursal_asociada; //añade sucursal asociada
    strcpy(cliente->nombres_cliente, nombres);   //añade nombres
    strcpy(cliente->apellidos_cliente, apellidos);   //añade apellidos
    strcpy(cliente->rut_cliente, rut);   //añade rut/identificador
}

void crear_cuenta(Cuenta* cuenta, char tipo_cuenta[20], int numero_cuenta, float comision_mensual, float tasa_interes, int saldo, char estado[20], char rut_cliente_asociado[20], int maximo_credito_negativo){ //crear cuenta. recibe tipo de cuenta, numero de cuenta, comision mensual, tasa de interes, saldo, estado y rut cliente asociado
    strcpy(cuenta->tipo_cuenta, tipo_cuenta);
    cuenta->numero_cuenta=numero_cuenta;
    cuenta->comision_mensual_cuenta=comision_mensual;
    cuenta->tasa_interes_cuenta=tasa_interes;
    cuenta->saldo_cuenta=saldo;
    strcpy(cuenta->estado_cuenta, estado);
    strcpy(cuenta->rut_cliente_asociado_cuenta, rut_cliente_asociado);
    cuenta->transacciones_gratis=4;
    cuenta->maximo_credito_negativo=maximo_credito_negativo;
}

Cuenta* buscar_cuenta_en_arreglo(Cuenta* cuentas, int numero_cuenta, int cantidad_cuentas){ //buscar una cuenta en una coleccion de cuentas
    int bandera=1;
    for(int contador=0; contador<cantidad_cuentas && bandera; contador++){ //buscar la cuenta solicitada
        if((*(cuentas+contador)).numero_cuenta==numero_cuenta){
            return cuentas+contador;
        }
    }
    return NULL; //si no se encuentra se retorna NULL
}

int verificar_restricciones_cuenta(Cuenta* cuenta, int monto, char tipo[10]){ //funcion para mejor legibilidad de la funcion "transferir_dinero" 
        int bandera=1; //se realizan las comprovaciones respecto a las restricciones de cada tipo de cuenta para efectuar o no la tranferencia
        //cuenta CORRIENTE
        if(comparar_cadenas(tipo, "origen")){
            if(comparar_cadenas(cuenta->tipo_cuenta, "corriente") && cuenta->saldo_cuenta-monto < cuenta->maximo_credito_negativo){ //-100k estandar (maximo de credito negativo)
                bandera=0; //no se puede realizar la transaccion por saldo insuficiente
            }
            else{
            //cuenta AHORRO 
                // char inactiva[50]; strcpy(inactiva, "inactiva"); && comparar_cadenas(cuenta_origen->estado_cuenta, inactiva)
                if(comparar_cadenas(cuenta->tipo_cuenta, "ahorro") && cuenta->saldo_cuenta-monto<50000){
                    bandera=0;
                }
                else{
            //cuenta VISTA
                    if(comparar_cadenas(cuenta->tipo_cuenta, "vista") && cuenta->saldo_cuenta-monto<0){ //cuenta vista no puede tener saldo negativo
                        bandera=0;
                    }
                }
            }
        }else{
            if(comparar_cadenas(tipo, "destino")){
                if(comparar_cadenas(cuenta->tipo_cuenta, "ahorro") && cuenta->saldo_cuenta+monto<100000 && comparar_cadenas(cuenta->estado_cuenta, "inactiva")){ //cuenta inactiva
                    bandera=0;
                }else{
            //cuenta VISTA
                if(comparar_cadenas(cuenta->tipo_cuenta, "vista") && cuenta->saldo_cuenta+monto>2500000){//saldo maximo en cuenta vista es de 2.5 millones
                    bandera=0;
                }
            }
                }
        }
        return bandera;
}

void transferir_dinero(Cuenta* cuentas, int cantidad_cuentas, int numero_cuenta_origen, int numero_cuenta_destino){ //tranferir dinero de una cuenta a otra
    Cuenta* cuenta_origen=buscar_cuenta_en_arreglo(cuentas, numero_cuenta_origen, cantidad_cuentas); //sirve para la condicion de la bandera
    Cuenta* cuenta_destino=buscar_cuenta_en_arreglo(cuentas, numero_cuenta_destino, cantidad_cuentas); //sirve para la condicion de la bandera

    if(cuenta_origen==NULL || cuenta_destino==NULL){ //si no se encuentra alguna de las dos se emite mensaje de error
        printf("ERROR! una de las cuentas no existe");
    }else{ //sino se pregunta por el monto y se transfiere si se cumplen los requisitos (saldo o restricciones de cuenta)

        printf("\n------------------------------------------\n");
        printf("tipo de cuenta de origen: %s\n", cuenta_origen->tipo_cuenta);
        printf("Saldo cuenta origen: %i\n", cuenta_origen->saldo_cuenta); //borrar despues
        printf("Estado de cuenta de origen: %s\n", cuenta_origen->estado_cuenta);
        printf("------------------------------------------\n");
        printf("tipo de cuenta de destino: %s\n", cuenta_destino->tipo_cuenta);
        printf("Saldo cuenta destinatario: %i\n", cuenta_destino->saldo_cuenta); //borrar despues
        printf("Estado de cuenta destino: %s\n", cuenta_destino->estado_cuenta);
        printf("------------------------------------------\n");

        int monto;
        printf("Ingrese el monto a transferir: ");
        scanf("%i", &monto); printf("\n");

        //esta parte es para verificar si las restricciones de las cuentas permiten la transacción
        int bandera_transaccion_origen=1;
        int bandera_transaccion_destino=1;

        char* corriente=(char*)malloc(sizeof(char)*10); strcpy(corriente, "corriente");
        char* vista=(char*)malloc(sizeof(char)*6); strcpy(vista, "vista");
        char* ahorro=(char*)malloc(sizeof(char)*7); strcpy(ahorro, "ahorro");
        char* origen=(char*)malloc(sizeof(char)*10); strcpy(origen, "origen");
        char* destino=(char*)malloc(sizeof(char)*10); strcpy(destino, "destino");

        //comprovaciones cuenta de origen
        bandera_transaccion_origen=verificar_restricciones_cuenta(cuenta_origen,monto, origen);
        //comprovaciones cuenta de destino
        bandera_transaccion_destino=verificar_restricciones_cuenta(cuenta_destino,monto, destino);

    //transfer si los requisitos se cumplen
    if(bandera_transaccion_origen && bandera_transaccion_destino){
        cuenta_origen->saldo_cuenta=cuenta_origen->saldo_cuenta-monto;
        cuenta_destino->saldo_cuenta=cuenta_destino->saldo_cuenta+monto;
        
        if(comparar_cadenas(cuenta_origen->tipo_cuenta, vista)){ //ver transacciones gratis de la cuenta vista
            if(cuenta_origen->transacciones_gratis>0){
                cuenta_origen->transacciones_gratis=cuenta_origen->transacciones_gratis-1;
            }else{
                if(cuenta_origen->saldo_cuenta-400>0){
                    cuenta_origen->saldo_cuenta=cuenta_origen->saldo_cuenta-400;
                }else{
                    cuenta_origen->saldo_cuenta=0;
                }
            }
        }
        printf("Saldo cuenta origen: %i\n", cuenta_origen->saldo_cuenta);
        printf("Saldo cuenta destinatario: %i\n", cuenta_destino->saldo_cuenta);
        printf("Transferencia realizada con exito\n");
    }else{
        printf("La transaccion no se pudo realizar\n");
    }
    }
}

void depositar(Cuenta* cuentas, int numero_cuenta, int cantidad_cuentas){
    Cuenta* cuenta_a_depositar=buscar_cuenta_en_arreglo(cuentas, numero_cuenta, cantidad_cuentas);
    int bandera=0;
    if(cuenta_a_depositar==NULL){ //si la cuenta no existe da error
        printf("ERROR! la cuenta no existe");
    }else{ //sino, se hacen las verificaciones de deposito
        printf("tipo de cuenta: %s\n", cuenta_a_depositar->tipo_cuenta);
        printf("cantidad de dinero en cuenta: %i\n", cuenta_a_depositar->saldo_cuenta);

        int monto;
        printf("ingrese monto a depositar:"); //se pregunta por el monto
        scanf("%i", &monto);
        
        //depositar si se cumplen los requerimientos segun sea el tipo de cuenta
        if(comparar_cadenas(cuenta_a_depositar->tipo_cuenta, "ahorro") && comparar_cadenas(cuenta_a_depositar->estado_cuenta, "activa")){
            bandera=1;
            cuenta_a_depositar->saldo_cuenta=cuenta_a_depositar->saldo_cuenta+monto;
        }else{
            if(comparar_cadenas(cuenta_a_depositar->tipo_cuenta, "vista") && cuenta_a_depositar->saldo_cuenta+monto<=2500000){
                bandera=1;
                cuenta_a_depositar->saldo_cuenta=cuenta_a_depositar->saldo_cuenta+monto;
            }else{
                bandera=1;
                cuenta_a_depositar->saldo_cuenta=cuenta_a_depositar->saldo_cuenta+monto;
            }
        }
    }
    if(!bandera){ //si la bandera es 0 es que por restricciones no se pudo realizar el deposito
        printf("El deposito no se pudo realizar");
    }else{ //sino es que si se pudo realizar con exito
        printf("Deposito realizado con exito\n");
        printf("Cantidad de dinero en cuenta: %i\n", cuenta_a_depositar->saldo_cuenta);
    }
}

void retirar(Cuenta* cuentas, int numero_cuenta, int cantidad_cuentas){ //funcion para hacer un retiro de dinero
    int bandera=0;
    Cuenta* cuenta_de_retiro=buscar_cuenta_en_arreglo(cuentas, numero_cuenta, cantidad_cuentas);
    if(cuenta_de_retiro==NULL){ //si la cuenta no existe se da el error
        printf("ERROR! la cuenta no existe");
    }else{
        //sino se pregunta por los datos de la cuenta
        printf("tipo de cuenta: %s\n", cuenta_de_retiro->tipo_cuenta);
        printf("cantidad de dinero en cuenta: %i\n", cuenta_de_retiro->saldo_cuenta);

        int monto;
        printf("ingrese monto a retirar:"); //se pregunta por el monto
        scanf("%i", &monto);
        //dependiendo del tipo de cuenta y las restricciones asociadas se efectuará o no el movimiento
        if(comparar_cadenas(cuenta_de_retiro->tipo_cuenta, "vista") && (cuenta_de_retiro->saldo_cuenta-monto)>=0){
            bandera=1;
            cuenta_de_retiro->saldo_cuenta=cuenta_de_retiro->saldo_cuenta-monto;
            printf("cantidad de dinero en cuenta: %i\n", cuenta_de_retiro->saldo_cuenta);
        }else{
            if(comparar_cadenas(cuenta_de_retiro->tipo_cuenta, "ahorro") && comparar_cadenas(cuenta_de_retiro->estado_cuenta, "activa") && (cuenta_de_retiro->saldo_cuenta-monto)>=0){
                bandera=1;
                cuenta_de_retiro->saldo_cuenta=cuenta_de_retiro->saldo_cuenta-monto;
                printf("cantidad de dinero en cuenta: %i\n", cuenta_de_retiro->saldo_cuenta);
                if(cuenta_de_retiro->saldo_cuenta<50000){
                    strcpy(cuenta_de_retiro->estado_cuenta, "inactiva");
                    printf("ahora su cuenta esta inactiva");
                }
            }else{
                if(comparar_cadenas(cuenta_de_retiro->tipo_cuenta, "corriente") && (cuenta_de_retiro->saldo_cuenta-monto)>=(cuenta_de_retiro->maximo_credito_negativo)){
                    bandera=1;
                    cuenta_de_retiro->saldo_cuenta=cuenta_de_retiro->saldo_cuenta-monto;
                    printf("cantidad de dinero en cuenta: %i\n", cuenta_de_retiro->saldo_cuenta);
                }
            }
        }
    }
    if(!bandera){ //si la bandera es 0 significa que por restriccion no se pudo realizar el retiro
        printf("La transaccion no se pudo realizar");
    }else{ //sino es que se pudo realizar con exito
        printf("Retiro realizado con exito");
    }
}

void extracto_mesual(Cuenta* cuentas, int cantidad_cuentas, int numero_cuenta){ //se calcula el extracto mensual (cada que se hace es como si pasara un mes)
    Cuenta* cuenta_extracto=buscar_cuenta_en_arreglo(cuentas, numero_cuenta, cantidad_cuentas);
    if(cuenta_extracto==NULL){ //si la cuenta no existe se da el error
        printf("ERROR! la cuenta no existe\n");
    }else{
        //sino se calcula
        int interes_generado=(cuenta_extracto->saldo_cuenta)*(cuenta_extracto->tasa_interes_cuenta);
        int saldo_final=(cuenta_extracto->saldo_cuenta)+interes_generado-(cuenta_extracto->comision_mensual_cuenta);
        printf("\nSaldo en cuenta: %i\n", cuenta_extracto->saldo_cuenta);
        printf("Intereses generados: %i\n", interes_generado);
        printf("Comision mensual: %f\n", cuenta_extracto->comision_mensual_cuenta);
        cuenta_extracto->saldo_cuenta=saldo_final;
        cuenta_extracto->meses_transcurridos_cuenta=cuenta_extracto->meses_transcurridos_cuenta+1;
        printf("Saldo final: %i", cuenta_extracto->saldo_cuenta);

        //si despues de calcular la cuenta es de ahorro y su nuevo monto es menor a 50k, la cuenta queda inactiva
        if(comparar_cadenas(cuenta_extracto->tipo_cuenta, "ahorro") && cuenta_extracto->saldo_cuenta<50000){
            strcpy(cuenta_extracto->estado_cuenta, "inactiva");
            printf("La cuenta ahora se encuentra inactiva");
        }
    }
}

void avanzar_mes(Cuenta *cuenta){
    // aplica interes
    cuenta->saldo_cuenta = cuenta->saldo_cuenta + cuenta->saldo_cuenta * cuenta->tasa_interes_cuenta;
    // aplica comisiones
    cuenta->saldo_cuenta = cuenta->saldo_cuenta - cuenta->comision_mensual_cuenta;
    // evitar saldos negativos por comisiones
    if (cuenta->saldo_cuenta < 0) {
        if(comparar_cadenas(cuenta->tipo_cuenta, "corriente") && cuenta->saldo_cuenta<cuenta->maximo_credito_negativo){
            cuenta->saldo_cuenta = cuenta->maximo_credito_negativo; //como la cuenta corriente es la unica que puede tener saldo negativo de algun tipo, se comprueba
        }else{
            cuenta->saldo_cuenta=0; //como es paso del tiempo y no transacciones se llega al limite minimo de dinero de la cuenta sin mas
        }
        
    }
}

void avanzar_tiempo(Cuenta* cuentas, int cantidad_cuentas, int meses){
    int contador=0;
    while(contador<cantidad_cuentas){
        int contador_2=0;
        while(contador_2<meses){
            ((cuentas+contador)->meses_transcurridos_cuenta)=((cuentas+contador)->meses_transcurridos_cuenta)+1;
            avanzar_mes(cuentas+contador); //se avanza mes a mes en cada cuenta haciendo los calculos necesarios
            contador_2=contador_2+1;
        }
        contador=contador+1;
    }
}

int buscar_cliente_en_sucursales(Cliente* clientes, char rut_cliente[20], int sucursal_asociada, int cantidad_cuentas){ //funcion para confirmar que al crear un usuario no exista en la misma sucursal
    int bandera=1;
    int contador=0;
    
    while(contador<cantidad_cuentas && bandera){
        if((*(clientes+contador)).sucursal_asociada_cliente==sucursal_asociada){
            if(comparar_cadenas((clientes+contador)->rut_cliente, rut_cliente)){
                bandera=0; //si se encuentra que está en la misma sucursal se cambia la bandera, cerrando el ciclo
            }
        }
        contador++;
    }
    if(bandera){
        return 1; //se retorna 1 (True) si no se encuentra
    }else{
        return 0; //se retorna 0 (False) si se encuentra
    }
}

void menu_recursivo(){ //basicamente el segundo main
    Sucursal* sucursales=(Sucursal*)malloc(sizeof(Sucursal)*5); //arreglo de sucursales (maximo 5)
    Cliente* clientes=(Cliente*)malloc(sizeof(Cliente)*50); //arreglo de cleintes (maximo 50)
    Cuenta* cuentas=(Cuenta*)malloc(sizeof(Cuenta)*150); //arreglo cuentas (maximo 150)
    int cantidad_sucursales=0;
    int cantidad_clientes=0;
    int cantidad_cuentas=0;

    cargar_sucursales(sucursales, &cantidad_sucursales);
    cargar_clientes(clientes, &cantidad_clientes);
    cargar_cuentas(cuentas, &cantidad_cuentas);

    int opcion=0;
    while(opcion!=13){ //mientras la opcion sea distinta de salir se va a mostrar el menu
        printf("\n--- Menu Banco Tusunami ---\n");
        printf("1. Crear Sucursal\n");
        printf("2. Crear Cliente\n");
        printf("3. Crear Cuenta\n");
        printf("4. Transferir Dinero\n");
        printf("5. Depositar Dinero\n");
        printf("6. Retirar Dinero\n");
        printf("7. Listado de sucursales\n");
        printf("8. Listado de Clientes\n");
        printf("9. Listado de Cuentas de Cliente\n");
        printf("10. Estado de cuenta\n");
        printf("11. Extracto mensual\n");
        printf("12. Avanzar tiempo\n");
        printf("13. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%i", &opcion);
        printf("----------------------------\n");

        switch(opcion){
            case 1: //crear sucursal
                printf("\nCrear sucursal\n");
                if(cantidad_sucursales<7){ //cantidad maxima de sucursales
                    int numero_sucursal;
                    char* direccion=(char*)malloc(sizeof(char)*50);
                    char* direccion_1=(char*)malloc(sizeof(char)*25);
                    char* direccion_2=(char*)malloc(sizeof(char)*25);
                
                    char* administrador=(char*)malloc(sizeof(char)*50);
                    char* nombre_administrador=(char*)malloc(sizeof(char)*25);
                    char* apellido_administrador=(char*)malloc(sizeof(char)*25);
                
                    int bandera=1;
                    printf("Ingrese numero de la sucursal: "); //recopilar datos de la sucursal
                    scanf("%i", &numero_sucursal);
                    for(int contador=0; contador<cantidad_sucursales && bandera; contador++){
                        if(numero_sucursal==((sucursales+contador)->numero_sucursal)){
                            printf("ERROR! ya existe esta sucursal");
                            bandera=0;
                        }
                    }
                    if(bandera){
                        printf("Ingrese direccion de la sucursal [FORMATO: ALGO ALGO]: ");
                        scanf("%s %s", direccion_1, direccion_2);
                        printf("Ingrese nombre y apellido del administrador de la sucursal: ");
                        scanf("%s %s", nombre_administrador, apellido_administrador);
                        juntar_cadenas(nombre_administrador, apellido_administrador, administrador);
                        juntar_cadenas(direccion_1, direccion_2, direccion);
                        crear_sucursal(((sucursales+cantidad_sucursales)), numero_sucursal, direccion, administrador); //crear el sucursal
                        cantidad_sucursales++; //aumentar la cantidad de sucursales
                        printf("Sucursal creada exitosamente.\n");
                    }
                    
                }else{
                    printf("No se pueden agregar más sucursales.\n");
                }
                break;
            case 2: //crear cliente
                printf("\nCrear cliente\n");
                if(cantidad_clientes<50){ //cantidad maxima de clientes
                    int sucursal_asociada;
                    char* nombres=(char*)malloc(sizeof(char)*50);
                    char* nombres_1=(char*)malloc(sizeof(char)*25);
                    char* nombres_2=(char*)malloc(sizeof(char)*25);

                    char* apellidos=(char*)malloc(sizeof(char)*50);
                    char* apellidos_1=(char*)malloc(sizeof(char)*25);
                    char* apellidos_2=(char*)malloc(sizeof(char)*25);

                    char* rut=(char*)malloc(sizeof(char)*20);
                    printf("Ingrese sucursal asociada: "); //recopilar datos del cliente
                    scanf("%i", &sucursal_asociada);
                    printf("Ingrese nombres del cliente: ");
                    scanf("%s %s", nombres_1, nombres_2);
                    printf("Ingrese apellidos del cliente: ");
                    scanf("%s %s", apellidos_1, apellidos_2);
                    printf("Ingrese RUT del cliente: ");
                    scanf("%s", rut);
                    if(buscar_cliente_en_sucursales(clientes, rut, sucursal_asociada, cantidad_clientes)){
                        juntar_cadenas(nombres_1, nombres_2, nombres);
                        juntar_cadenas(apellidos_1, apellidos_2, apellidos);
                        crear_cliente((clientes+cantidad_clientes), sucursal_asociada, nombres, apellidos, rut); //crear el cliente
                        cantidad_clientes++; //aumentar cantidad de clientes
                        printf("Cliente creado exitosamente.\n");
                    }else{
                        printf("Error al anadir el cliente: ya existe en la sucursal %i", sucursal_asociada);
                    }
                }else{
                    printf("No se pueden agregar más clientes.\n");
                }
                break;
            case 3: //crear cuenta
                printf("\nCrear cuenta\n");
                if(cantidad_cuentas<150){ //cantidad maximo de cuentas
                    char* tipo_cuenta=(char*)malloc(sizeof(char)*20);
                    char* estado=(char*)malloc(sizeof(char)*20);
                    char* rut_cliente=(char*)malloc(sizeof(char)*20); //se crean los contenedores necesarios
                    int numero_cuenta, saldo;
                    float comision, tasa_interes;
                    printf("Ingrese tipo de cuenta (vista, corriente, ahorro): "); //recopilar datos de la cuenta
                    scanf("%s", tipo_cuenta);
                    fflush(stdin);
                    printf("Ingrese número de cuenta: ");
                    scanf("%i", &numero_cuenta);
                    printf("Ingrese comision mensual: ");
                    scanf("%f", &comision);
                    printf("Ingrese tasa de interés: ");
                    scanf("%f", &tasa_interes);
                    printf("Ingrese saldo inicial: ");
                    scanf("%i", &saldo);
                    if(comparar_cadenas(tipo_cuenta, "ahorro")){
                        if(saldo<100000){
                            printf("la cuenta no se a podido crear: fondos insuficientes");
                            break;
                        }else{
                            strcpy(estado, "activa"); //o el saldo es mayor que 100k
                        }
                    }else{
                        strcpy(estado, "activa"); //o el saldo es mayor que 100k, o la cuenta no es de ahorro
                    }
                    int maximo_credito_negativo=0;
                    if(comparar_cadenas(tipo_cuenta, "corriente")){
                        printf("ingrese monto maximo que puede deber la cuenta: ");
                        scanf("%i", &maximo_credito_negativo);
                        maximo_credito_negativo=maximo_credito_negativo*-1;
                    }
                    printf("Ingrese RUT del cliente asociado: ");
                    scanf("%s", rut_cliente);
                    fflush(stdin);
                    crear_cuenta((cuentas+cantidad_cuentas), tipo_cuenta, numero_cuenta, comision, tasa_interes, saldo, estado, rut_cliente, maximo_credito_negativo);
                    cantidad_cuentas++; //aumentar cantidad de cuentas
                    printf("Cuenta creada exitosamente.\n");
                }else{
                    printf("No se pueden agregar más cuentas.\n");
                }
                break;
            case 4: //transferir dinero
                printf("\nTransferencia de Dinero.\n"); //seleccionar cuenta de origen y resive
                int numero_cuenta_origen, numero_cuenta_destino;

                printf("ingrese cuenta de origen: ");
                scanf("%i", &numero_cuenta_origen);
                printf("ingrese cuenta destinataria: ");
                scanf("%i", &numero_cuenta_destino);
                transferir_dinero(cuentas, cantidad_cuentas, numero_cuenta_origen, numero_cuenta_destino);
                break;
            case 5: //depositar dinero
                printf("\nDepósito de Dinero.\n");
                char rut_usuario[20];
                printf("ingrese su rut: ");
                scanf("%s", rut_usuario);
                int numero_cuenta_deposito;
                printf("ingrese cuenta para depositar: ");
                scanf("%i", &numero_cuenta_deposito);
                //buscar si la cuenta pertenece al usuario
                Cuenta* cuenta_deposito=buscar_cuenta_en_arreglo(cuentas, numero_cuenta_deposito, cantidad_cuentas);
                if(comparar_cadenas(((cuenta_deposito)->rut_cliente_asociado_cuenta), rut_usuario)){
                    printf("No se puede realizar el deposito.\n");
                }else{
                    depositar(cuentas, numero_cuenta_deposito, cantidad_cuentas);
                }
                break;
            case 6: //retirar dinero
                printf("\nRetiro de Dinero.\n");
                int numero_cuenta_retiro;
                printf("ingrese cuenta para retirar: ");
                scanf("%i", &numero_cuenta_retiro);
                retirar(cuentas, numero_cuenta_retiro, cantidad_cuentas);
                break;
            case 7: //ver listado de sucursales
                printf("\nListado de Sucursales.\n");
                imprimir_sucursales(sucursales, cantidad_sucursales); //imprimir cada sucursal
                break;
            case 8: //ver listado general de clientes en todas las sucursales
                printf("\nListado de Clientes:\n");
                int numero_sucursal_perteneciente;
                printf("ingrese numero de sucursal que desea imprimir: ");
                scanf("%i", &numero_sucursal_perteneciente);
                imprimir_clientes(clientes, cantidad_clientes, numero_sucursal_perteneciente); //imprimir cada cliente
                break;
            case 9: //Listado de Cuentas de Cliente
                printf("\nListado de Cuentas de Cliente:\n");
                char _rut_cliente_asociado[20];
                printf("ingrese rut cliente asociado que desea imprimir: ");
                scanf("%s", _rut_cliente_asociado);
                imprimir_cuentas(cuentas, cantidad_cuentas, _rut_cliente_asociado); //imprimir cada cliente
                break;
            case 10: //imprimir una cuenta especifica
                printf("\nEstado de cuenta\n");
                int numero_cuenta_estado;
                printf("que cuenta desea revisar?: ");
                scanf("%i", &numero_cuenta_estado);
                Cuenta* cuenta_imprimir=buscar_cuenta_en_arreglo(cuentas, numero_cuenta_estado, cantidad_cuentas);
                if(cuenta_imprimir){
                    imprimir_cuenta(cuenta_imprimir, clientes, cantidad_clientes);
                }else{
                    printf("la cuenta no existe");
                }

                break;
            case 11://extracto mensual
                printf("\nExtracto mensual\n");
                int numero_cuenta_extracto;
                printf("ingrese numero de cuenta: "); scanf("%i", &numero_cuenta_extracto);
                extracto_mesual(cuentas, cantidad_cuentas, numero_cuenta_extracto);
                break;
            case 12: //avanzar el tiempo
                printf("\nAvanzar tiempo\n");
                int meses;
                printf("cuantos meses desea avanzar?: ");
                scanf("%i", &meses);
                while(meses<=0){
                    printf("\nCantidad de meses fuera de rango: [debe ser mayor que 0 meses]\n");
                    printf("cuantos meses desea avanzar?: ");
                    scanf("%i", &meses);
                }
                avanzar_tiempo(cuentas, cantidad_cuentas, meses);
                break;
            case 13: //salir del programa
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
        }
    } 

    guardar_archivo_sucursal(sucursales, cantidad_sucursales);
    guardar_archivo_criente(clientes, cantidad_clientes);
    guardar_archivo_cuenta(cuentas, cantidad_cuentas);
    }

int main(){
    printf("------------BIENVENIDO A BANCO TSUNAMI------------");
    menu_recursivo();
    printf("--MUCHAS GRACIAS POR NO PREFERIR BANCO ESTADO :)--");
    return 1;
}