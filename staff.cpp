
#include "staff.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
Staff::Staff()
{
id_staff=0;nom=" ";prenom=" ";email=" ";fonction=" ";salaire=0;nb_heurs=0;
}
Staff::Staff(QString nom ,QString prenom ,int id_staff,int nb_heurs,int salaire ,QString  email,QString  fonction)
{this->nom=nom;this->prenom=prenom;this->id_staff=id_staff;this->nb_heurs=nb_heurs;this->salaire=salaire;this->email=email;this->fonction=fonction;}
QString Staff::getnom(){return nom;}
QString Staff::getprenom(){return prenom;}
QString Staff::getemail (){return email;}
QString Staff::getfonction(){return fonction;}
int Staff::getnb_heurs (){return nb_heurs;}
int Staff::getid(){return id_staff;}
int Staff::getsalaire(){return salaire; }
void Staff::setnom (QString nom){this->nom=nom;}
void Staff::setprenom (QString prenom){this->prenom=prenom;}
void Staff::setemail (QString email){this->email=email;}
void Staff::setfonction(QString fonction){this->fonction=fonction;}
void Staff::setnb_heurs(int nb_heurs){this->nb_heurs=nb_heurs;}
void Staff::setid(int id_staff){this->id_staff=id_staff;}
void Staff::setsalaire(int salaire){this->salaire=salaire;}


bool Staff::ajouter()
{
    QSqlQuery query;
  //  QString id_string=QString::number(id_staff);
   // QString nb_heurs_string=QString::number(nb_heurs);
    //QString salaire_string=QString::number(salaire);

         query.prepare("INSERT INTO STAFF (nom,prenom,id_staff,nb_heurs,salaire,email,fonction ) "
                     "VALUES (:nom, :prenom, :id_staff,:nb_heurs,  :salaire, :email, :fonction)");
         query.bindValue(":id_staff", id_staff);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":email", email);
         query.bindValue(":fonction", fonction);
         query.bindValue(":nb_heurs", nb_heurs);
         query.bindValue(":salaire", salaire);

         return query.exec();
}
bool Staff::supprimer(int id_staff )
{   QSqlQuery query;


         query.prepare("delete from STAFF where id_staff=:id_staff");
         query.bindValue(":id_staff", id_staff);


         return query.exec();




}
QSqlQueryModel* Staff::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT * FROM STAFF");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id_staff"));
    model ->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(4,Qt::Horizontal,QObject::tr("nombre d'heurs"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("salaire"));
    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("fonction"));



    return model;
}
bool Staff::modifier(int id)
{
QSqlQuery query;
QString id_string= QString::number(id);
query.prepare("Update staff set nom =:nom, prenom =:prenom , nb_heurs =:nb_heurs , salaire =:salaire  ,email  =:email,fonction=:fonction where id_staff=:id");

//query.prepare("Update staff set nom = :nom , prenom = :prenom , nb_heurs = :nb_heurs,id_staff = :id_staff , salaire = :salaire  ,email  = :email where id_staff=:id");
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":nb_heurs", nb_heurs);
query.bindValue(":salaire", salaire);
query.bindValue(":email", email);
query.bindValue(":fonction", fonction);
query.bindValue(":id", id_string);
return    query.exec();
}
