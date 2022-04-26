
#include "staff.h"


Staff::Staff()
{
id_staff=0;nom=" ";prenom=" ";email=" ";fonction=" ";salaire=0;nb_heurs=0;date_emp="";uid_c=""; present =false;
}
Staff::Staff(int id_staff, QString nom ,QString prenom,QString  email, int nb_heurs,int salaire ,QString  fonction,QString date_emp,QString uid_c )
{this->nom=nom;this->prenom=prenom;this->id_staff=id_staff;this->nb_heurs=nb_heurs;this->salaire=salaire;this->email=email;this->fonction=fonction;
    this->date_emp=date_emp;this->uid_c=uid_c;}
QString Staff::getprenom(){return prenom;}
QString Staff::getemail (){return email;}
QString Staff::getfonction(){return fonction;}
int Staff::getnb_heurs (){return nb_heurs;}
int Staff::getid(){return id_staff;}
int Staff::getsalaire(){return salaire; }
QString Staff::getdate_emp(){return date_emp;}
QString Staff::getuid_c(){return uid_c;}
bool Staff::getpresent(){return present;}
void Staff::setnom (QString nom){this->nom=nom;}
void Staff::setprenom (QString prenom){this->prenom=prenom;}
void Staff::setemail (QString email){this->email=email;}
void Staff::setfonction(QString fonction){this->fonction=fonction;}
void Staff::setnb_heurs(int nb_heurs){this->nb_heurs=nb_heurs;}
void Staff::setid(int id_staff){this->id_staff=id_staff;}
void Staff::setsalaire(int salaire){this->salaire=salaire;}
void Staff::setpresent(bool present){this->present=present;}
void Staff::setuid_c(QString uid_c){this->uid_c=uid_c;}
void Staff::setdate_emp(QString date_emp){this->date_emp=date_emp;}

bool Staff::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id_staff);
    QString nb_heurs_string=QString::number(nb_heurs);
    QString salaire_string=QString::number(salaire);

         query.prepare("INSERT INTO STAFF (nom,prenom,id_staff,nb_heurs,salaire,email,fonction ) "
                     "VALUES (:nom, :prenom, :id_staff,:nb_heurs, :salaire, :email, :fonction)");
         query.bindValue(":id_staff", id_string);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":email", email);
         query.bindValue(":fonction", fonction);
         query.bindValue(":nb_heurs", nb_heurs_string);
         query.bindValue(":salaire", salaire_string);

         return query.exec();
}
bool Staff::supprimer(int id_staff )
{   QSqlQuery query;

    QString id_string= QString::number(id_staff);
    query.prepare("Delete from CLIENT where ID_CLT =:id_clt");
         query.prepare("delete from STAFF where id_staff=:id_staff");
         query.bindValue(":id_staff", id_string);


         return query.exec();


}
QSqlQueryModel* Staff::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model ->setQuery("SELECT ID_STAFF NOM PRENOM EMAIL NB_HEURS SALAIRE FONCTION DATE_EMP PRESENT UID_C  FROM STAFF");
    model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("id_staff"));
    model ->setHeaderData(5,Qt::Horizontal,QObject::tr("nom"));
    model ->setHeaderData(6,Qt::Horizontal,QObject::tr("prenom"));
    model ->setHeaderData(7,Qt::Horizontal,QObject::tr("email"));
    model ->setHeaderData(8,Qt::Horizontal,QObject::tr("nombre d'heurs"));
    model ->setHeaderData(9,Qt::Horizontal,QObject::tr("salaire"));
    model ->setHeaderData(10,Qt::Horizontal,QObject::tr("fonction"));
    model ->setHeaderData(11,Qt::Horizontal,QObject::tr("Date_emploie"));
    model ->setHeaderData(12,Qt::Horizontal,QObject::tr("present"));
    model ->setHeaderData(13,Qt::Horizontal,QObject::tr("uid_c"));



    return model;
}
bool Staff::modifier(int id)
{
QSqlQuery query;
QString id_string= QString::number(id);
QString nb_heurs_string=QString::number(nb_heurs);
QString salaire_string=QString::number(salaire);

query.prepare("Update staff set nom=:nom, prenom=:prenom , nb_heurs=:nb_heurs , salaire=:salaire  ,email =:email, fonction =:fonction, date_emp=:date_emp, uid_c=:uid_c where id_staff=:id");

//query.prepare("Update staff set nom=:nom , prenom=:prenom , nb_heurs = :nb_heurs,id_staff = :id_staff , salaire = :salaire  ,email  = :email where id_staff=:id");
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":nb_heurs", nb_heurs_string);
query.bindValue(":salaire", salaire_string);
query.bindValue(":email", email);
query.bindValue(":fonction", fonction);
query.bindValue(":date_emp", date_emp);
query.bindValue(":uid_c", uid_c);
query.bindValue(":id", id_string);
return    query.exec();
}

QSqlQueryModel * Staff::afficherValeur(QString valeur)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString ch1="select ";
    QString query=" from staff";
    query=ch1+valeur+query;


    model->setQuery(query);

    return model;
}

