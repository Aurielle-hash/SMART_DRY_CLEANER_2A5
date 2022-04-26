#include "article.h"

article::article()
{

  id=0;
  type="";
  nom="";
  matiere="";
  couleur="";


}

article::article( int id, QString type, QString nom, QString matiere, QString couleur )
{
    this->id=id;
    this->type=type;
    this->nom=nom;
    this->matiere=matiere;
    this->couleur=couleur;
}


bool article::ajouter()
{
    QSqlQuery query;
    //QString id_string= QString::number(id);
    query.prepare("INSERT INTO ARTICLE (id,type,nom,matiere,couleur)" "VALUES (:id,:type,:nom,:matiere,:couleur)");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":nom", nom);
    query.bindValue(":matiere", matiere);
    query.bindValue(":couleur", couleur);

    return query.exec();
}


QSqlQueryModel* article::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();





          model->setQuery("SELECT * FROM article ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("matiere"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("couleur"));


    return model;
}
 bool article::modifier(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Update article set id = :id , type= :type , nom = :nom , matiere = :matiere , couleur = :couleur  where id = :id ");

query.bindValue(":id",res);
query.bindValue(":type",type);
query.bindValue(":nom",nom);
query.bindValue(":matiere",matiere);
query.bindValue(":couleur",couleur);



return    query.exec();
}

bool article::supprimer(int id )
{
    QSqlQuery query;

    query.prepare("DELETE FROM article where id=:id") ;

    query.bindValue(":id",id);

    return query.exec();
}



QSqlQueryModel* article::tri_type()
{
    QSqlQueryModel* model=new QSqlQueryModel();





          model->setQuery("SELECT * FROM article order by type ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("matiere"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("couleur"));

    return model;
}


QSqlQueryModel*  article::tri_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM article order by id  ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("matiere"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("couleur"));

    return model;
}

QSqlQueryModel* article::recherche_id(QString type )
{


    QSqlQueryModel * model= new QSqlQueryModel();
        QString qry="select * from article where categorie like '%"+type+"%' ";
        qDebug()<<qry;
        model->setQuery(qry);
        return model;



}


