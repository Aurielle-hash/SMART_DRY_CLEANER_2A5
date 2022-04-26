#include "connection.h"
#include "dombase.h"
#include <iostream>
using namespace std;

DomBase::DomBase(){
//RIEN
}
DomBase::~DomBase(){
    // RIEN
}




QVector <QString> DomBase::getListDate(QDate datedebut, QDate datefin)
{
    //"+getTableName()+"

    QVector <QString> vectDate;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT DAT FROM CAISSE WHERE DAT BETWEEN :datedebut AND :datefin");
    query.bindValue(":datedebut", datedebut);
    query.bindValue(":datefin", datefin);
    query.exec();
    int DATENo = query.record().indexOf("DAT");
    while (query.next()){

        //QString dateString= QDate::toString(query.value(DATENo).toDate());
        vectDate.push_back(query.value(DATENo).toDate().toString("dd/MM/yyyy"));
    }
    return vectDate;

}

float DomBase::getMontantTotalFraisParDate(QDate date, QString type)
{

    QSqlQuery query;
       query.prepare("SELECT SUM(MONTANT) FROM CAISSE WHERE DAT=:date AND TYPE LIKE '%' || :type || '%' ");
       query.bindValue(":date", date);
       query.bindValue(":type", type);
       query.exec();
       query.first();
       return (query.value(0).toFloat());

}

QSqlQueryModel *DomBase::getModelGlobal(){

    //QVector <QString> vectColumns;
   /* vectColumns=getColumnName();

    QString selectColumns="";
    for (int i=0;i<vectColumns.size();i++){
        selectColumns+=vectColumns[i];
        if (i!=vectColumns.size()-1){
            selectColumns+=',';
        }
    }
    qDebug()<<selectColumns;*/

    QSqlQueryModel * model= new QSqlQueryModel ();
    model->setQuery("SELECT CODE,LIBELLE,DAT,MONTANT,TYPE FROM CAISSE");
    return model;
}

QSqlQueryModel *DomBase::getModelSpecial(QString inputValue,QString filterChecked){
    QSqlQueryModel * model= new QSqlQueryModel ();
    QSqlQuery query;
   /* QVector <QString> vectColumns;
    vectColumns=getColumnName();

    QString selectColumns="";
    for (int i=0;i<vectColumns.size();i++){
        selectColumns+=vectColumns[i];
        if (i!=vectColumns.size()-1){
            selectColumns+=',';
        }
    }*/
    query.prepare("SELECT CODE,LIBELLE,DAT,MONTANT,TYPE FROM CAISSE WHERE "+filterChecked+" LIKE '%' || :inputValue || '%' ");
    query.bindValue(":inputValue",inputValue);
    query.exec();
    model->setQuery(query);
    return model;
}

bool DomBase::ajout()
{
    QSqlQuery query=queryPrepareAjout();
    return (query.exec());
}

bool DomBase::supprime(int ID)
{

    QSqlQuery query;
    query.prepare("DELETE FROM CAISSE WHERE CODE=:ID");
    query.bindValue(":ID",ID);
    return (query.exec());

}

bool DomBase::update(int ID){

    QSqlQuery query= queryPrepareUpdate(ID);
    return (query.exec());
}

void DomBase::getData(int ID)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM CAISSE WHERE CODE=:ID");
    query.bindValue(":ID",ID);

    if (query.exec()){
        query.first();
        setData(query);

    }
    else
    {
        qDebug()<<"FALSE";
    }

}

/***CLASSE CAISSE****/


DomCaisse::DomCaisse()
{
    this->code=0;
   this->libelle="";
   this->type="";
   this->montant=0;
   this->date = QDate::fromString("01/01/2000","dd/MM/yyyy");

}

DomCaisse::DomCaisse(int id,QString libelle,QString type,float montant,QDate date)
{
    this->code=id;
   this->libelle=libelle;
   this->type=type;
   this->montant=montant;
   this->date=date;

}

DomCaisse::~DomCaisse()
{
    //RIEN
}

QString DomCaisse::getTableName()
{
    return "CAISSE";
}


QString DomCaisse::getAjoutValues()
{
    return "VALUES (NULL,:libelle,:date,:montant,:type)";
}

QString DomCaisse::getUpdateValues()
{
    return "LIBELLE=:libelle,DAT=:date,MONTANT=:montant,TYPE=:type";
}

QVector <QString> DomCaisse::getColumnName()
{

    QVector <QString> vectColumns;
    QSqlQuery query;

    query.prepare("PRAGMA table_info("+getTableName()+')');
    query.exec();

    while (query.next()){
        vectColumns.push_back(query.value(1).toString());
    }
    return vectColumns;

}

QSqlQuery DomCaisse::queryPrepareAjout()
{

    QSqlQuery query;
    QString montant= QString::number(this->montant);

    query.prepare("INSERT INTO  CAISSE (LIBELLE,DAT,MONTANT,TYPE)" "VALUES(:libelle, :date, :montant, :type)");


    query.bindValue(":libelle", this->libelle);
    query.bindValue(":date", this->date);
    query.bindValue(":montant", montant);
    query.bindValue(":type", this->type);



    return query;
}

QSqlQuery DomCaisse::queryPrepareUpdate(int id)
{
   QSqlQuery query;
   QString montant= QString::number(this->montant);

       query.prepare("UPDATE CAISSE SET LIBELLE=:libelle, DAT=:date, MONTANT=:montant, TYPE=:type WHERE CODE=:id");

       query.bindValue(":libelle", this->libelle);
       query.bindValue(":date", this->date);
       query.bindValue(":montant", montant);
       query.bindValue(":type", this->type);
       query.bindValue(":id", id);

     return query;

}

void DomCaisse::setData(QSqlQuery query)
{
    int codeNo = query.record().indexOf("CODE");
        int libelleNo= query.record().indexOf("LIBELLE");
        int dateNo = query.record().indexOf("DAT");
        int montantNo = query.record().indexOf("MONTANT");
        int typeNo = query.record().indexOf("TYPE");

        this->code = query.value(codeNo).toInt();
        this->libelle= query.value(libelleNo).toString();
        this->date = query.value(dateNo).toDate();
        this->montant = query.value(montantNo).toFloat();
        this->type = query.value(typeNo).toString();

}

int DomCaisse::found(QString type, QString libelle)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CAISSE WHERE LIBELLE=:libelle AND TYPE=:type");
    query.bindValue(":libelle",libelle);
    query.bindValue(":type",type);
    query.exec();
    query.next();
    qDebug()<<query.value(0).toInt();
    return query.value(0).toInt();
}

void DomCaisse::getHistoryFromDB()
{
    QSqlQuery query;

       QString fileName="historique.txt";
       QFile file(fileName);
       file.open(QIODevice::WriteOnly|QIODevice::Text);
       QTextStream out(&file);


       query.prepare("SELECT * FROM CAISSE");
       query.exec();

       int dateNo = query.record().indexOf("DAT");
       int montantNo = query.record().indexOf("MONTANT");
       int typeNo = query.record().indexOf("TYPE");


       while (query.next()){
           if (query.value(typeNo).toString()=="depense")
           {
               out<<"La somme de "+query.value(montantNo).toString()+" a été prélevée de la caisse le "+query.value(dateNo).toString() <<endl;
           }

           else if (query.value(typeNo).toString()=="versement")
           {
               out<<"La somme de "+query.value(montantNo).toString()+" a été ajoutée à la caisse le "+query.value(dateNo).toString() <<endl;
           }

       }
       out<<"  " <<endl;
       file.close();
}

void DomCaisse::getBilanFromDB(QDate D1, QDate D2)
{

    QSqlQuery query;

       QString fileName="bilan.txt";
       QFile file(fileName);
       file.open(QIODevice::WriteOnly|QIODevice::Text);
       QTextStream out(&file);


       query.prepare("SELECT * FROM CAISSE WHERE DAT BETWEEN :date1 AND :date2");
       query.bindValue(":date1", D1);
       query.bindValue(":date2", D2);
       query.exec();

       int codeNo = query.record().indexOf("CODE");
       int dateNo = query.record().indexOf("DAT");
       int typeNo = query.record().indexOf("TYPE");

      // float montantDap= getMontantTotalFraisParDate(D1,"depense");
       //out<<"Montant total des ESSAIS : "<< montantDap<<endl;


       while (query.next()){

           int a= query.value(codeNo).toInt();

               out<<"Date : "+query.value(dateNo).toString()+"         référence de la caisse : "+QString::number(a) <<endl;

               if (query.value(typeNo).toString()=="versement")
               {
                   float montantVer= getMontantTotalFraisParDate(query.value(dateNo).toDate(),"versement");
                   //QString mtnver= QString::number(montantVer);
                   out<<"Montant Total des entrees : "<< montantVer<<endl;

               }

               else if (query.value(typeNo).toString()=="depense")
               {
                   float montantDep= getMontantTotalFraisParDate(query.value(dateNo).toDate(),"depense");
                  // QString mtndep= QString::number(montantDep);
                   out<<"Montant total des sorties : "<< montantDep<<endl;
               }

          out<<"  " <<endl;
          out<<"  " <<endl;

       }
       file.close();
}































