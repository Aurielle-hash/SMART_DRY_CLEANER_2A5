#ifndef STAFF_H
#define STAFF_H
# include "defs.h"
class Staff
{
public:
    Staff();
    Staff(int,QString,QString,QString,int,int,QString,QString,QString);

    QString getnom();
    QString getprenom();
    QString getemail ();
    QString getfonction ();
    QString getuid_c ();
    QString getdate_emp ();
    bool getpresent ();
    int getnb_heurs ();
    int getid();
    int getsalaire();
    void setnom (QString);
    void setprenom (QString);
    void setemail (QString);
    void setfonction (QString);
    void setdate_emp (QString);
    void setuid_c (QString);
    void setnb_heurs(int);
    void setid(int);
    void setsalaire(int);
     void setpresent (bool);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherValeur(QString);
    bool supprimer (int);
     bool modifier(int);
; private:
    QString nom , prenom , email , fonction,date_emp , uid_c ;
 int nb_heurs ,id_staff ,salaire ;
  bool present;
};

#endif // STAFF_H
