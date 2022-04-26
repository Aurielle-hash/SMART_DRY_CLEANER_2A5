#ifndef ARTICLE_H
#define ARTICLE_H
#include "defs.h"


class article
{
    int id;
    QString type,nom,matiere,couleur;
    //constructors
public:
    article();
    article(int,QString,QString,QString,QString);

//getters
int getid(){return id; }
QString get_type(){return type;}
QString getnom(){return nom ;}
QString getmatiere(){return matiere;}
QString getcouluer(){return couleur;}

//setters
void setid(int id){this->id=id;}
void settype(QString type ){this->type=type;}
void setnom(QString nom ){this->nom=nom;}
void setmatiere(QString matiere){this->matiere=matiere;}
void setcouleur(QString couleur){this->couleur=couleur;}
//functions of depot class

bool ajouter();
QSqlQueryModel* afficher();
bool supprimer ( int id);
bool modifier(int id);
QSqlQueryModel* tri_id();
QSqlQueryModel* tri_type();
QSqlQueryModel* recherche_id(QString type );
















};

#endif // ARTICLE_H
