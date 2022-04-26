#ifndef MATERIEL_H
#define MATERIEL_H
#include "defs.h"


class stock
{
    QString nom_materiel,categorie;
    int id_stock,quantite;
    float prix_materiel;
public:
    //constructeurs

    stock(){}
    ~stock(){}

    stock(int,int,QString,QString,float);

    //getters


    QString getNom();
    QString getcategorie();
    int getID();
     int getquantite();
    float getPrix();

// setters
    void setNom(QString );
    void setCategorie(QString);
    void setId(int);
     void setquantite(int);
    void setPrix(float);


// fonctionnalites de base relatives a lentite materiel
    bool ajouter();
    bool supprimer(int);
    bool modifier(int id_stock,int quantite,QString nom_materiel,QString categorie ,float prix_materiel);
QSqlQueryModel* afficher();
QSqlQueryModel * tri_prix_materiel();
QSqlQueryModel * tri_nom_materiel();

bool rech(int );
QSqlQueryModel* rechercher(QString );
bool rechprix(int );
QSqlQueryModel* rechercherprix(QString );
bool rechquantite(int );
QSqlQueryModel* rechercherquantite(QString );
bool verif();
};

#endif // MATERIEL_H
