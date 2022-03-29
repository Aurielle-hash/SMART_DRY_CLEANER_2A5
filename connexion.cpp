#include "connexion.h"

connexion::connexion()
{

}
bool connexion::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("DRY_CLEANER");
db.setUserName("esprit");//inserer nom de l'utilisateur
db.setPassword("lina");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

    return  test;

}

