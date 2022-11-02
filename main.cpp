#include <iostream>
#include <string.h>
#include <fstream>
using namespace  std;

struct Participantes
{
    string nombre;
    int cedula;
    int pago;
    int polla[100][2];
    int puntos=0;
};

struct VecParticipantes
{
    Participantes participante[100];
};

struct Resultados
{
    string equipo1;
    string equipo2;
    int golesTeam1;
    int golesTeam2;
};

struct Equipos
{
    string equipo[10];
};

Equipos lecturaEquipos();
Participantes lecturaParticipantes();
Resultados ingresarResultado(Equipos equipo);
Participantes registrarPredicciones(Participantes participante,int contPartidos );
void consultarPolla(VecParticipantes participante, Resultados resultados[], int numParticipantes, int contPartido, int cedula);
VecParticipantes calcularPuntaje(VecParticipantes participante, Resultados resultados[],int contPartidos, int contParticipantes);
void mostrarGanadores(VecParticipantes participante, int numParticipantes);
bool verificarEquipo(Equipos equipos,string verificar);

int main()
{
    Equipos equipos;
    VecParticipantes participante;
    Resultados resultados[100];
    int contPartido=0, numParticipantes=0, auxCedula=0;
    int opcion = 0;

    do
    {
        cout<<"MENU"<<std::endl;
        cout<<"Presiona 1 para registrar los equipos participantes."<<endl;
        cout<<"Presiona 2 para registrar los participantes de la polla."<<endl;
        cout<<"Presiona 3 para registrar los resultados de un partido."<<endl;
        cout<<"Presiona 4 para registrar las predicciones de los participantes."<<endl;
        cout<<"Presiona 5 para consultar la polla de un participante."<<endl;
        cout<<"Presiona 6 para calcular el puntaje de los participantes."<<endl;
        cout<<"Presiona 7 para mostrar los ganadores de la polla."<<endl;
        cout<<"Presiona 8 para salir del programa."<<endl<<endl;
        cout<<"Presiona el numero de la opcion deseada: ";
        cin>>opcion;
        cout<<endl;

        switch(opcion)
        {
        case 1:
            equipos=lecturaEquipos();
            break;

        case 2:
            cout<<"Cuantos participantes desea ingresar?"<<endl;
            cin>>numParticipantes;
            if(numParticipantes>=2 && numParticipantes<10)
            {
                for(int i=0; i<numParticipantes; i++)
                {
                    participante.participante[i]=lecturaParticipantes();
                }
            }
            else
            {
                cout<<"Ingresaste una cantidad invalidad de participantes, intentalo de nuevo"<<endl;
                opcion=2;
            }
            break;

        case 3:
            resultados[contPartido]=ingresarResultado(equipos);
            contPartido++;
            break;

        case 4:
            for(int i=0; i<numParticipantes; i++)
            {
                cout<<"Participante "<<participante.participante[i].nombre<<endl;
                participante.participante[i]=registrarPredicciones(participante.participante[i],contPartido);
            }
            break;

        case 5:
            cout<<"Ingresa el numero de cedula del participante al que le quieres consultar la polla:"<<endl;
            cin>>auxCedula;
            consultarPolla(participante, resultados, numParticipantes, contPartido, auxCedula);
            break;

        case 6:
            participante=calcularPuntaje(participante, resultados, contPartido,numParticipantes);
            break;

        case 7:
            mostrarGanadores(participante, numParticipantes);
            break;

        case 8:
            cout<<"Muchas gracias por usar el programa, vuelve pronto"<<endl;
            opcion=9;
            break;

        default:
            cout<<"Opcion inexistente, vuelve a intentarlo"<<std::endl<<endl;
            opcion=8;
        }
    }
    while(opcion<9);
}

Equipos lecturaEquipos()
{
    Equipos aux;
    int i=0;
    ifstream archivo;
    archivo.open("equipos.txt", ios::in);
    if(archivo.fail())
    {
        cout<<"Hubo un error en la lectura del arhcivo";
        exit(1);
    }
    while(!archivo.eof())
    {
        getline(archivo,aux.equipo[i]);
        i++;
    }
    cout<<"Archivo leido"<<endl<<endl;
    return aux;
}

Participantes lecturaParticipantes()
{
    Participantes part;
    int numPart=0;

    cout<<"Ingresa el nombre del participante:"<<endl;
    cin>>part.nombre;
    cout<<"Ingresa la cedula del participante:"<<endl;
    cin>>part.cedula;
    cout<<"Ingresa el costo de la inscripcion del participante:"<<endl;
    cin>>part.pago;
    cout<<endl;
    return part;
}

Resultados ingresarResultado(Equipos equipos)
{
    Resultados aux;

    bool verificar;

    cout<<"Ingrese el nombre del equipo local:"<<endl;
    //buscar que el equipo exista
    cin>>aux.equipo1;
    verificar=verificarEquipo(equipos,aux.equipo1);
    if(verificar==false)
    {
        cout<<"El equipo que ingreso no existe"<<endl;
        return aux;
    }
    cout<<"Ingrese el nombre del equipo visitante:"<<endl;
    cin>>aux.equipo2;
    verificar=verificarEquipo(equipos,aux.equipo2);
    if(verificar==false)
    {
        cout<<"El equipo que ingreso no existe"<<endl;
        return aux;
    }
    //buscar que el equipo exista
    cout<<"Ingrese el resultado del equipo local:"<<endl;
    //buscar que el equipo exista
    cin>>aux.golesTeam1;
    cout<<"Ingrese el resultado del equipo visitante:"<<endl;
    //buscar que el equipo exista
    cin>>aux.golesTeam2;
    cout<<endl;
    return aux;
}

bool verificarEquipo(Equipos equipos,string verificar)
{
    for(int i=0; i<10; i++)
    {
        if(equipos.equipo[i]==verificar)
        {
            return true;
        }
    }
    return false;
}

Participantes registrarPredicciones(Participantes participante,int contPartidos )
{
    for(int i=0; i<contPartidos; i++)
    {
        cout<<"Ingrese la prediccion del partido "<<i+1<<" para el local:"<<endl;
        cin>>participante.polla[i][0];
        cout<<"Ingrese la prediccion del partido "<<i+1<<" para el visitante:"<<endl;
        cin>>participante.polla[i][1];
        cout<<endl;
    }
    return participante;
}

void consultarPolla(VecParticipantes participante, Resultados resultados[], int numParticipantes, int contPartidos, int cedula)
{
    for(int i=0; i<numParticipantes; i++)
    {
        if(participante.participante[i].cedula==cedula)
        {
            cout<<"Nombre: "<<participante.participante[i].nombre<<endl;
            cout<<"Cedula: "<<participante.participante[i].cedula<<endl;
            for(int j=0; j<contPartidos; j++)
            {
                cout<<"Partido "<<resultados[j].equipo1<<" VS "<<resultados[j].equipo2<<":"<<endl;
                cout<<"Polla del participante:"<<endl;
                cout<<"Local (Equipo #1): "<<participante.participante[i].polla[j][0]<<endl;
                cout<<"Visitante (Equipo #2): "<<participante.participante[i].polla[j][1]<<endl<<endl;
            }
        }
    }
}

VecParticipantes calcularPuntaje(VecParticipantes participante, Resultados resultados[1000],int contPartidos,int contParticipantes)
{
    for(int i=0; i<=contParticipantes; i++)
    {
        for(int j=0; i<=contPartidos; i++)
        {
            if(resultados[j].golesTeam1 > resultados[j].golesTeam2)//en caso de que el team 1 gane
            {
                if(participante.participante[i].polla[j][0]==resultados[j].golesTeam1 && participante.participante[i].polla[j][1]==resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=3;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 3 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else if(participante.participante[i].polla[j][0] > resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=1;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 1 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else
                {
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 0 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
            }
            else if(resultados[j].golesTeam1 == resultados[j].golesTeam2)// en caso de empate
            {
                if(participante.participante[i].polla[j][0]==resultados[j].golesTeam1 && participante.participante[i].polla[j][1]==resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=3;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 3 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else if(participante.participante[i].polla[j][0] == resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=1;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 1 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else
                {
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 0 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
            }
            else if(resultados[j].golesTeam1 < resultados[j].golesTeam2) //en caso de que el team2 gane
            {
                if(participante.participante[i].polla[j][0]==resultados[j].golesTeam1 && participante.participante[i].polla[j][1]==resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=3;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 3 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else if(participante.participante[i].polla[j][0] < resultados[j].golesTeam2)
                {
                    participante.participante[i].puntos+=1;
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 1 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
                else
                {
                    cout<<"El participante "<<participante.participante[i].nombre<<" obtuvo 0 puntos y su puntaje actual es de "<<participante.participante[i].puntos<<endl<<endl;
                }
            }
        }
    }
    return participante;
}

void mostrarGanadores(VecParticipantes participante, int numParticipantes)
{
    Participantes aux;
    int mayor=0, auxUbicacion1=0, auxUbicacion2=0, auxUbicacion3=0, auxPremio=0;
    ofstream archivo;
    archivo.open("resultados.txt", ios::out);
    if(archivo.fail())
    {
        cout<<"Hubo un error en la lectura del arhcivo";
        exit(1);
    }
    else
    {
        for(int i=0; i<numParticipantes; i++)
        {
            for(int j=0; j<numParticipantes; j++)
            {
                if(participante.participante[j].puntos<participante.participante[j+1].puntos)
                {
                    aux=participante.participante[j];
                    participante.participante[j]=participante.participante[j+1];
                    participante.participante[j+1]=aux;
                }
            }
            auxPremio+=participante.participante[i].pago;
        }
        cout<<"El primer ganador de la polla es: "<<participante.participante[0].nombre<<" con una ganancia del 50% de las apuestas equivalente al "<<(auxPremio*0.5)<<endl;
        archivo<<"El primer ganador de la polla es: "<<participante.participante[0].nombre<<" con una ganancia del 50% de las apuestas equivalente al "<<(auxPremio*0.5)<<endl<<endl;

        cout<<"El segundo ganador de la polla es: "<<participante.participante[1].nombre<<" con una ganancia del 30% de las apuestas equivalente al "<<(auxPremio*0.3)<<endl;
        archivo<<"El segundo ganador de la polla es: "<<participante.participante[1].nombre<<" con una ganancia del 30% de las apuestas equivalente al "<<(auxPremio*0.3)<<endl<<endl;
        if(numParticipantes> 2)
        {
            cout<<"El tercer ganador de la polla es: "<<participante.participante[2].nombre<<" con una ganancia del 10% de las apuestas equivalente al "<<(auxPremio*0.2)<<endl;
            archivo<<"El tercer ganador de la polla es: "<<participante.participante[2].nombre<<" con una ganancia del 30% de las apuestas equivalente al "<<(auxPremio*0.2)<<endl<<endl;
        }
    }
}
