#include "materiel.h"


stock::stock(int id_stock,int quantite,QString nom_materiel,QString categorie,float prix_materiel)
{
    this->id_stock=id_stock;
    this->quantite=quantite;
    this->nom_materiel=nom_materiel;
    this->categorie=categorie;
    this->prix_materiel=prix_materiel;
}

int stock::getID(){
   return id_stock;

}
int stock::getquantite(){
   return quantite;

}
QString stock::getNom(){
  return nom_materiel;

}
QString stock::getcategorie(){

  return categorie;
}

float stock::getPrix(){
 return prix_materiel;
}

void stock::setId(int id_stock){
    this->id_stock=id_stock;
}
void stock:: setNom(QString nom_materiel){
    this->nom_materiel=nom_materiel;
}
void stock::setPrix(float prix_materiel){
 this->prix_materiel=prix_materiel;

}
void stock::setCategorie(QString categorie){
    this->categorie=categorie;
}

bool stock::ajouter()
{
 QSqlQuery query;
query.prepare("INSERT INTO stock(id_stock,categorie,nom_materiel,quantite,prix_materiel)"
              "VALUES (:id_stock,:categorie,:nom_materiel,:quantite,:prix_materiel)");
QString id_string= QString::number(id_stock);
query.bindValue(":id_stock",id_string);
QString quantite_string= QString::number(quantite);
query.bindValue(":quantite",quantite_string);
query.bindValue(":nom_materiel",nom_materiel);
query.bindValue(":categorie",categorie);
QString e = QString::number(prix_materiel);
query.bindValue(":prix_materiel",e);
return query.exec();
}

bool stock::supprimer(int id_stock)
{
     QSqlQuery query;
    query.prepare("DELETE FROM stock where id_stock=:id_stock");

    query.bindValue(":id_stock",id_stock);

    return query.exec();
}



QSqlQueryModel * stock::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM stock");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));
return model;
}

bool stock::modifier(int id_stock,int quantite,QString nom_materiel,QString categorie,float prix_materiel)
{
    QString prix_string=QString::number(prix_materiel);
    QString id_string=QString::number(id_stock);
    QString quantite_string= QString::number(quantite);
    QSqlQuery query;
       query.prepare("update stock set id_stock=:id_stock, categorie=:categorie, nom_materiel=:nom_materiel, quantite=:quantite, prix_materiel=:prix_materiel where id_stock=:id_stock");
       query.bindValue(":id_stock",id_string);
       query.bindValue(":nom_materiel",nom_materiel);
       query.bindValue(":categorie",categorie);
       query.bindValue(":prix_materiel",prix_string);
        query.bindValue(":quantite",quantite_string);


return query.exec();
}









QSqlQueryModel * stock::tri_nom_materiel(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from stock order by nom_materiel ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));

    return model;
}



QSqlQueryModel * stock::tri_prix_materiel(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from stock order by prix_materiel ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));

    return model;
}



bool stock::rech(int x){
    QSqlQuery query;
    query.prepare("select * from stock where id_stock = :id_stock");
    query.bindValue(":id_stock", x);
    return query.exec();
}
QSqlQueryModel* stock::rechercher(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock where id_stock ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));
                return model;
            }


bool stock::rechprix(int x){
    QSqlQuery query;
    query.prepare("select * from stock where prix_materiel = :prix_materiel");
    query.bindValue(":prix_materiel", x);
    return query.exec();
}
QSqlQueryModel* stock::rechercherprix(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock where prix_materiel ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" id_stock"));
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("categorie"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom_materiel"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr(" prix_materiel"));
        return model;

}


bool stock::rechquantite(int x){
    QSqlQuery query;
    query.prepare("select * from stock where quantite = :quantite;");
    query.bindValue(":quantite", x);
    return query.exec();
}

QSqlQueryModel* stock::rechercherquantite(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock where quantite ='"+a+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_stock"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom_materiel"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("categorie"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("quantite"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("prix_materiel"));
        return model;
}

bool stock::verif()
{
    QSqlQuery query;
    bool test = false;
    query.prepare("select * from stock");
    query.exec();
    QStringList list;
    while(query.next()){
        if(query.value(3).toInt() <= 4 )
        {
            test=true;
        }
    }
    return test;

}


