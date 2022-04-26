#include "client.h"

client::client()
{
    id_clt = 0; id = 0; nom =" "; prenom =" "; adresse=" "; mail=" "; numtel =0;
}

client::client(int idc, int ia, QString n, QString p, QString a, QString m, int nu)
{this->id_clt=idc; this->id=ia; this->nom=n; this->prenom=p; this->adresse=a; this->mail=m; this->numtel=nu;}

int client::getid_clt(){return id_clt;}
int client::getid(){return id;}
QString client::getnom(){return nom;}
QString client::getprenom(){return prenom;}
QString client::getadresse(){return adresse;}
QString client::getmail(){return mail;}
int client::getnumtel(){return numtel;}
float client::getacompte(){return acompte;}
float client::getremise(){return remise;}

void client::setid_clt(int idc){this->id_clt=idc;}
void client::setid(int ia){this->id=ia;}
void client::setnom(QString n){this->nom=n;}
void client::setprenom(QString p){this->prenom=p;}
void client::setadresse(QString a){this->adresse=a;}
void client::setmail(QString m){this->mail=m;}
void client::setnumtel(int nu){this->numtel=nu;}
void client::setacompte(float acmt){this->acompte=acmt;}
void client::setremise(float r){this->remise=r;}

bool client::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id_clt);
    QString id_string2= QString::number(id);
    QString num_string= QString::number(numtel);

        query.prepare("INSERT INTO CLIENT(ID_CLT, ID, NOM, PRENOM, ADRESSE, MAIL, NUMTEL)"
                      "values(:id_clt, :id, :nom, :prenom, :adresse, :mail, :numtel)");

        query.bindValue(":id_clt", id_string);
        query.bindValue(":id",id_string2);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":adresse", adresse);
        query.bindValue(":mail", mail);
        query.bindValue(":numtel", num_string);
        return query.exec();

}

bool client::supprimer(int id_clt)
{
    QSqlQuery query;
    QString id_string= QString::number(id_clt);
    query.prepare("Delete from CLIENT where ID_CLT =:id_clt");
    query.bindValue(":id_clt",id_string);
    return query.exec();

}

QSqlQueryModel* client::afficher()
{

    QSqlQueryModel* model= new QSqlQueryModel();
    model->setQuery("SELECT* FROM CLIENT");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID_Client"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("ID_Article"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("Num_tel"));

    return model;
}

bool client::modifier(int id_clt)
{
    QSqlQuery query;
    QString id_string= QString::number(id_clt);
    QString id_string2= QString::number(id);
    QString num_string= QString::number(numtel);

    query.prepare("UPDATE CLIENT SET ID_CLT=:id_clt, ID=:id, NOM=:nom, PRENOM=:prenom, ADRESSE=:adresse, MAIL=:mail, NUMTEL=:numtel where ID_CLT =:id_clt");
    query.bindValue(":id_clt", id_string);
    query.bindValue(":id",id_string2);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail", mail);
    query.bindValue(":numtel", num_string);
    return query.exec();


}

QSqlQueryModel * client::afficherValeur(QString valeur)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString ch1="select ";
    QString query=" from client";
    query=ch1+valeur+query;


    model->setQuery(query);

    return model;
}

QSqlQueryModel * client::afficherValeurArticle(QString valeur)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString ch1="select ";
    QString query=" from article";
    query=ch1+valeur+query;


    model->setQuery(query);

    return model;
}

QSqlQueryModel * client::trierA(QString valeur)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString query="select * from client ORDER by "+valeur+" asc";

    model->setQuery(query);

    return model;
}

QSqlQueryModel * client::trierD(QString valeur)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString query="select * from client ORDER by "+valeur+" desc";

    model->setQuery(query);

    return model;
}

QSqlQueryModel* client::rechercher(QString valeur){

   QSqlQueryModel * model =new QSqlQueryModel();
   QString query="select * from client where ID_CLT like '%"+valeur+"%' or NOM like '%"+valeur+"%' or PRENOM like '%"+valeur+"%'";

   model->setQuery(query);
   return model;

}


