#include "connection.h"
connection::connection(){}

bool connection::connection_db()
{

 db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;

db.setDatabaseName("Source_Projet2A");
QFileInfo info_database("Source_Projet2A");
db.setUserName("Aurielle");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur
         if (db.open()) test=true;
             return test;
}

void connection::closeConnection(){db.close();}
