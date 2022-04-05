#ifndef DOMBASE_H
#define DOMBASE_H
#include "defs.h"
#include "connection.h"


class DomBase
{

public :
    DomBase();
    ~DomBase();

    bool ajout();
    bool supprime(int);
    bool update(int);
    void getData(int);

    QVector <QString> getListDate(QDate,QDate);
    QSqlQueryModel *getModelGlobal();
    QSqlQueryModel *getModelSpecial(QString,QString);
    virtual QString getTableName() = 0;
    virtual QString getAjoutValues() = 0;
    virtual QString getUpdateValues() = 0;
    virtual QVector <QString> getColumnName() = 0;// Elle peut être déclarer seulement dans DomBase
    virtual QSqlQuery queryPrepareAjout() = 0;
    virtual QSqlQuery queryPrepareUpdate(int) = 0;
    virtual void setData(QSqlQuery) = 0;

    float getMontantTotalFraisParDate(QDate,QString);
    };

class DomCaisse : public DomBase {

private :

    int code;
    QString libelle;
    QString type;
    float montant;
    QDate date;

public:
    DomCaisse();
       DomCaisse(int,QString,QString,float,QDate);
       ~DomCaisse();

       QString getTableName();
       QString getAjoutValues();
       QString getUpdateValues();
       QVector <QString>  getColumnName();
       QSqlQuery queryPrepareAjout();
       int found(QString,QString);
       QSqlQuery queryPrepareUpdate(int);
       void setData(QSqlQuery);
       void getHistoryFromDB();
       void getBilanFromDB(QDate,QDate);

    //Getters
    int getID(){return this->code;}
    QString getLibelle(){return libelle;}
    QString getType(){return type;}
   float getMontant(){return montant;}
   QDate getDate(){return this->date;}

    //Setters
   void setID( int ID){this->code = ID;}
    void setLibelle(QString l){libelle=l;}
    void setType(QString t){type=t;}
    void setMontant(float m){montant=m;}
    void setDate(QDate date){this->date = date;}


};
#endif // DOMBASE_H
