#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>

	
int main(int argc, char *argv[]) {
	
	//Conector para acceder al servidor de bases de datos 
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[20];
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//inicializar la conexion, indicando nuestras claves de acceso
	// al servidor de bases de datos (user,pass)
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "videojuego", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	err=mysql_query (conn, "SELECT jugadores.nombre FROM (jugadores, registro) WHERE registro.puntos=(SELECT MAX(registro.puntos) FROM registro) AND registro.idJ=jugadores.id");
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	
	}
	
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);	
	strcpy(nombre,row[0]);
	printf("El nombre del jugador con más puntos es %s", nombre);
	
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
	
		
}
