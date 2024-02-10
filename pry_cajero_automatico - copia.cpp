#include <iostream> //Biblioteca estandar para la entrada/salida
#include <vector> //Biblioteca de los vectores para almacenar los datos
#include <string> //Para la manipulacion de cadenas de texto

#ifdef _WIN32 //Con esto se comprueba si se esta compilando en windows, por eso la condicional de este tipo
    #include <conio.h> // Incluye la biblioteca conio.h para lectura de caracteres sin esperar una pulsación de tecla
    #define CLEAR_COMMAND "cls" //Se define una instruccion para limpiar la consola
#endif


using namespace std; // Utiliza las entidades estándar de la biblioteca de C++

//Clase usuario
class class_usuario {
public:
    string atr_nom_titular; // Atributo para almacenar el nombre del titular
    string atr_num_documento; // Atributo para almacenar el número de documento
    int atr_edad; // Atributo para almacenar la edad
    int atr_num_cuenta; // Atributo para almacenar el número de cuenta
    double atr_saldo; // Atributo para almacenar el saldo
    vector<string> atr_movimientos; // Atributo para almacenar los movimientos

    //Constructor
    class_usuario(string var_nombre, string var_documento, int var_edad, int var_cuenta, double var_saldo) {
        atr_nom_titular = var_nombre; // Inicializa el atributo del nombre del titular con el valor proporcionado
        atr_num_documento = var_documento; // Inicializa el atributo del número de documento con el valor proporcionado
        atr_edad = var_edad; // Inicializa el atributo de la edad con el valor proporcionado
        atr_num_cuenta = var_cuenta; // Inicializa el atributo del número de cuenta con el valor proporcionado
        atr_saldo = var_saldo; // Inicializa el atributo del saldo con el valor proporcionado
    }
};

//Clase usuario
class class_cuenta {
private:
    vector<class_usuario> atr_usuarios; // Atributo privado para almacenar los usuarios de la cuenta

public:
    //Metodo para consultar el saldo
    void met_saldo_consultar(int var_cuenta) {
            //const = No se permiten modificaciones durante el bucle
            //auto = Deduce automaticamente el tipo de cada elemento del vector
            //& = indica que estamos utilizando una referencia en cada elemento en lugar de copiarlos
        for (const auto& obj_usuario : atr_usuarios) { //el const auto& lo que nos permite es recorrer el vector y acceder a los elementos sin que se modifiquen los datos en el proceso
            if (obj_usuario.atr_num_cuenta == var_cuenta) {
                // Imprimir saldo actual
                cout << "--------------------------" << endl;
                cout << "Su saldo actual es $" << obj_usuario.atr_saldo << endl;
                cout << "--------------------------" << endl;
                return;
            }
        }
         // La cuenta no se encontró
        cout << "--------------------------" << endl;
        cout << "Cuenta no encontrada. Por favor, verifique el numero de cuenta." << endl;
        cout << "--------------------------" << endl;
    }

    //Metodo para depositar
    void met_depositar(int var_cuenta, double var_cantidad) {
        for (auto& obj_usuario : atr_usuarios) { //el auto& nos permite trabajar con cada elemento del vector sin necesidad de que se copeen.
            if (obj_usuario.atr_num_cuenta == var_cuenta) {
                if (var_cantidad > 0) {
                // Actualizar saldo y agregar movimiento de depósito
                    obj_usuario.atr_saldo += var_cantidad;
                    obj_usuario.atr_movimientos.push_back("Deposito de $" + to_string(var_cantidad)); //con el to string convertimos el valor en una cadena de caracteres para concatenarlo.
                    cout << "--------------------------" << endl;                                       //Esto se hace para para poder almacenar el movimiento en el vector atr_movimientos como una cadena completa.
                    cout << "Deposito realizado con exito." << endl;
                    cout << "--------------------------" << endl;
                } else {
                // Cantidad de depósito inválida
                    cout << "--------------------------" << endl;
                    cout << "Cantidad invalida. Por favor, intente nuevamente." << endl;
                    cout << "--------------------------" << endl;
                }
                return;
            }
        }
        // La cuenta no se encontró
        cout << "--------------------------" << endl;
        cout << "Cuenta no encontrada. Por favor, verifique el numero de cuenta." << endl;
        cout << "--------------------------" << endl;
    }

    //Metodo para retirar dinero
  void met_retirar(int var_cuenta, double var_cantidad) {
    for (auto& obj_usuario : atr_usuarios) { //el auto& nos permite trabajar con cada elemento del vector sin necesidad de que se copeen.
        if (obj_usuario.atr_num_cuenta == var_cuenta) {
            if (var_cantidad > 0 && var_cantidad <= obj_usuario.atr_saldo) {
            // Actualizar saldo y agregar movimiento de retiro
                obj_usuario.atr_saldo -= var_cantidad;
                obj_usuario.atr_movimientos.push_back("Retiro de $" + to_string(var_cantidad));//con el to string convertimos el valor en una cadena de caracteres para concatenarlo.
                cout << "--------------------------" << endl;
                cout << "Retiro realizado con exito." << endl;
                cout << "Saldo restante: $" << obj_usuario.atr_saldo << endl;
                cout << "--------------------------" << endl;

            // Verificar si se debe imprimir el recibo
                char var_imprimir; //El char nos permite representar caracteres individuales en este caso s o S 
                cout << "¿Desea imprimir un recibo? (S/N): ";
                cin >> var_imprimir;
                if (var_imprimir == 'S' || var_imprimir == 's') {
                    // Lógica para imprimir el recibo
                    cout << "Imprimiendo recibo..." << endl;
                    cout << "Nombre del titular: " << obj_usuario.atr_nom_titular << endl;
                    cout << "Numero de cuenta: " << obj_usuario.atr_num_cuenta << endl;
                    cout << "Cantidad retirada: $" << var_cantidad << endl;
                }
            } else {
                // Cantidad de retiro inválida o saldo insuficiente
                cout << "--------------------------" << endl;
                cout << "Cantidad invalida o saldo insuficiente. Por favor, intente nuevamente." << endl;
                cout << "--------------------------" << endl;
            }
            return;
        }
    }
    // La cuenta no se encontró
    cout << "--------------------------" << endl;
    cout << "Cuenta no encontrada. Por favor, verifique el numero de cuenta." << endl;
    cout << "--------------------------" << endl;
}


    //Metodo para transferir dinero
    void met_transferir(int var_cuenta_origen, int var_cuenta_destino, double var_cantidad) {
    //Aqui se crea un puntero * para señalar la ubicacion del objeto en la memoria es como una referencia
    class_usuario* obj_usuario_origen = nullptr; //Junto a esto se encuentra el puntero nulo
    class_usuario* obj_usuario_destino = nullptr;//Estos nulos no apuntan a ningun espacio de la memoria como si estuvieran vacios


    for (auto& obj_usuario : atr_usuarios) {
        if (obj_usuario.atr_num_cuenta == var_cuenta_origen) {
            obj_usuario_origen = &obj_usuario;
        } else if (obj_usuario.atr_num_cuenta == var_cuenta_destino) {
            obj_usuario_destino = &obj_usuario;
        }

        if (obj_usuario_origen != nullptr && obj_usuario_destino != nullptr) { //Aqui es donde se verifica si el puntero sigue siendo nulo
            break; //O si ya tiene asignado algun lugar en la memoria para continuar con el codigo y hacer sus respectivos calculos
        }
    }

    if (obj_usuario_origen != nullptr && obj_usuario_destino != nullptr) {
        if (var_cantidad > 0 && var_cantidad <= obj_usuario_origen->atr_saldo) {
        // Actualizar saldos y agregar movimientos de transferencia
            obj_usuario_origen->atr_saldo -= var_cantidad;
            obj_usuario_destino->atr_saldo += var_cantidad;
            obj_usuario_origen->atr_movimientos.push_back("Transferencia de $" + to_string(var_cantidad) + " a cuenta " + to_string(var_cuenta_destino));
            obj_usuario_destino->atr_movimientos.push_back("Transferencia recibida de $" + to_string(var_cantidad) + " de cuenta " + to_string(var_cuenta_origen));
            cout << "--------------------------" << endl;
            cout << "Transferencia realizada con exito." << endl;
            cout << "Saldo restante en cuenta origen: $" << obj_usuario_origen->atr_saldo << endl;
            cout << "--------------------------" << endl;

            // Verificar si se debe imprimir el recibo
            char var_imprimir; //El char nos permite representar caracteres individuales en este caso s o S
            cout << "¿Desea imprimir un recibo? (S/N): ";
            cin >> var_imprimir;
            if (var_imprimir == 'S' || var_imprimir == 's') {
                    cout << "Imprimiendo recibo..." << endl;
                    cout << "Nombre del titular: " << obj_usuario_origen->atr_nom_titular << endl;
                    cout << "Numero de cuenta: " << obj_usuario_origen->atr_num_cuenta << endl;
                    cout << "Cantidad transferida: $" << var_cantidad << endl;
                
                    // Imprimir el recibo en la cuenta de destino
                    cout << "¡Tranferencia con exito!" << endl;
                    cout << "Nombre del titular: " << obj_usuario_destino->atr_nom_titular << endl;
                    cout << "Número de cuenta: " << obj_usuario_destino->atr_num_cuenta << endl;
                    cout << "Cantidad recibida: $" << var_cantidad << endl;
            }
        } else {
            // Saldo insuficiente para transferencia
            cout << "--------------------------" << endl;
            cout << "Saldo insuficiente. No es posible realizar la transferencia." << endl;
            cout << "--------------------------" << endl;
        }
    } else {
        // Una o ambas cuentas no se encontraron
        cout << "--------------------------" << endl;
        cout << "Una o ambas cuentas no encontradas. Por favor, verifique los numeros de cuenta." << endl;
        cout << "--------------------------" << endl;
    }
}

    //Metodo para ver los movimientos de la cuenta
    void met_movimientos_ver(int var_cuenta) {
        for (const auto& obj_usuario: atr_usuarios) {
            if (obj_usuario.atr_num_cuenta == var_cuenta) {
                // Imprimir movimientos de la cuenta
                cout << "--------------------------" << endl;
                cout << "Movimientos de la cuenta " << obj_usuario.atr_num_cuenta << endl;
                for (const auto& atr_movimientos : obj_usuario.atr_movimientos) {
                    cout << atr_movimientos << endl;
                }
                cout << "--------------------------" << endl;
                return;
            }
        }
        // La cuenta no se encontró
        cout << "--------------------------" << endl;
        cout << "Cuenta no encontrada. Por favor, verifique el numero de cuenta." << endl;
        cout << "--------------------------" << endl;
    }

    //Metodo para crear la cuenta
    void met_cuenta_crear(string var_nombre, string var_documento, int var_edad, int var_cuenta, double var_saldo) {
        for (const auto& obj_usuario : atr_usuarios) {
            if (obj_usuario.atr_num_cuenta == var_cuenta) {
                // El numero de cuenta ya existe
                cout << "El numero de cuenta ya existe. Por favor, intente con otro numero." << endl;
                return;
            }
        }
        // Crear nueva cuenta y agregarla a la lista de usuarios
        atr_usuarios.push_back(class_usuario(var_nombre, var_documento, var_edad, var_cuenta, var_saldo));
        cout << "--------------------------" << endl;
        cout << "Cuenta creada exitosamente." << endl;
        cout << "--------------------------" << endl;
    }
};

//Clase cajero
class class_cajero {
private:
    class_cuenta obj_cuenta; // Objeto de la clase 'class_cuenta' para interactuar con las cuentas bancarias

public:

//Metodo para limpiar consola
void met_limpiar() {
        #ifdef _WIN32
            system(CLEAR_COMMAND); // Limpia la consola en Windows
        #endif
    }
    //Metodo para mostrar menu
    void met_menu_mostrar() {
        int atr_opcion;
        do {
            // Mostrar menú del cajero automático y solicitar una opción al usuario
            cout << "==========================" << endl;
            cout << "   CAJERO AUTOMATICO" << endl;
            cout << "==========================" << endl;
            cout << "1. Crear cuenta" << endl;
            cout << "2. Consultar saldo" << endl;
            cout << "3. Depositar dinero" << endl;
            cout << "4. Retirar dinero" << endl;
            cout << "5. Transferir dinero" << endl;
            cout << "6. Ver movimientos" << endl;
            cout << "7. Limpiar consola" << endl;
            cout << "8. Salir" << endl;
            cout << "--------------------------" << endl;
            cout << "Ingrese una opcion: ";
            cin >> atr_opcion;

            switch (atr_opcion) {
                case 1:
                    met_cuenta_crear(); // Llamar al método para crear una cuenta
                    break;
                case 2:
                    met_saldo_consultar(); // Llamar al método para consultar el saldo
                    break;
                case 3:
                    met_depositar(); // Llamar al método para depositar dinero
                    break;
                case 4:
                    met_retirar(); // Llamar al método para retirar dinero
                    break;
                case 5:
                    met_transferir(); // Llamar al método para transferir dinero
                    break;
                case 6:
                    met_movimientos_ver(); // Llamar al método para ver los movimientos de una cuenta
                    break;
                case 7:
                    met_limpiar(); // Llamar al método para limpiar la consola
                    break;
                case 8: //Para salir del programa
                    cout << "Gracias por utilizar el cajero automatico. ¡Hasta luego!" << endl;
                break;
                default:
                    cout << "Opcion invalida. Por favor, intente nuevamente." << endl;
                    break;
            }
            cout << "--------------------------" << endl;
        } while (atr_opcion != 8);
    }

//Metodo crear cuenta
    void met_cuenta_crear() {
        string var_nombre, var_documento;
        int var_edad, var_cuenta;
        double var_saldo;
        
        // Solicitar datos para crear una cuenta
        cout << "==========================" << endl;
        cout << "   CREAR CUENTA" << endl;
        cout << "==========================" << endl;
        cout << "Ingrese el nombre del titular: ";
        cin.ignore();
        getline(cin, var_nombre);

        cout << "Ingrese el numero de documento: ";
        getline(cin, var_documento);

        cout << "Ingrese la edad del titular: ";
        cin >> var_edad;

        // Verificar la edad del titular
        if (var_edad < 18) {
            cout << "El titular debe ser mayor de 18 años. No se puede crear la cuenta." << endl;
            return;
        }

        cout << "Ingrese el numero de cuenta: ";
        cin >> var_cuenta;

        cout << "Ingrese el saldo inicial: $";
        cin >> var_saldo;

        obj_cuenta.met_cuenta_crear(var_nombre, var_documento, var_edad, var_cuenta, var_saldo);
    }
    

//Metodo para consultar saldo

    void met_saldo_consultar() {
        int var_cuenta;
        // Solicitar el número de cuenta para consultar el saldo
        cout << "==========================" << endl;
        cout << "   CONSULTAR SALDO" << endl;
        cout << "==========================" << endl;
        cout << "Ingrese el numero de cuenta: ";
        cin >> var_cuenta;

        obj_cuenta.met_saldo_consultar(var_cuenta); // Llamar al método 'met_saldo_consultar' de la clase 'class_cuenta' para consultar el saldo
    }

//Metodo para depositar
    void met_depositar() {
        int var_cuenta;
        double var_cantidad;
        // Solicitar el número de cuenta y la cantidad a depositar
        cout << "==========================" << endl;
        cout << "   DEPOSITAR DINERO" << endl;
        cout << "==========================" << endl;
        cout << "Ingrese el numero de cuenta: ";
        cin >> var_cuenta;
        cout << "Ingrese la cantidad a depositar: $";
        cin >> var_cantidad;

        obj_cuenta.met_depositar(var_cuenta, var_cantidad); // Llamar al método 'met_depositar' de la clase 'class_cuenta' para depositar dinero
    }

//Metodo para retirar
    void met_retirar() {
    int var_cuenta;
    double var_cantidad;
    char var_imprimir;
    // Solicitar el número de cuenta y la cantidad a retirar
    cout << "==========================" << endl;
    cout << "   RETIRAR DINERO" << endl;
    cout << "==========================" << endl;
    cout << "Ingrese el numero de cuenta: ";
    cin >> var_cuenta;
    cout << "Ingrese la cantidad a retirar: $";
    cin >> var_cantidad;

    obj_cuenta.met_retirar(var_cuenta, var_cantidad); // Llamar al método 'met_retirar' de la clase 'class_cuenta' para retirar dinero
}

//Metodo para transferir
    void met_transferir() {
        int var_cuenta_origen, var_cuenta_destino;
        double var_cantidad;
        char var_imprimir;
        // Solicitar el número de cuenta de origen, el número de cuenta de destino y la cantidad a transferir
        cout << "==========================" << endl;
        cout << "   TRANSFERIR DINERO" << endl;
        cout << "==========================" << endl;
        cout << "Ingrese el numero de cuenta de origen: ";
        cin >> var_cuenta_origen;
        cout << "Ingrese el numero de cuenta de destino: ";
        cin >> var_cuenta_destino;
        cout << "Ingrese la cantidad a transferir: $";
        cin >> var_cantidad;

        obj_cuenta.met_transferir(var_cuenta_origen, var_cuenta_destino, var_cantidad); // Llamar al método 'met_transferir' de la clase 'class_cuenta' para transferir dinero
    }

//Metodo para ver movimientos
    void met_movimientos_ver() {
        int var_cuenta;
        // Solicitar el número de cuenta para ver los movimientos
        cout << "==========================" << endl;
        cout << "   VER MOVIMIENTOS" << endl;
        cout << "==========================" << endl;
        cout << "Ingrese el numero de cuenta: ";
        cin >> var_cuenta;

        obj_cuenta.met_movimientos_ver(var_cuenta); // Llamar al método 'met_movimientos_ver' de la clase 'class_cuenta' para ver los movimientos de una cuenta
    }
};

int main() {
    class_cajero obj_cajero; // Crear un objeto de la clase 'class_cajero'
    obj_cajero.met_menu_mostrar(); // Llamar al método 'met_menu_mostrar' del objeto 'obj_cajero' para mostrar el menú del cajero automático y permitir al usuario interactuar con las opciones

    return 0;
}