#ifndef STAFF_H
#define STAFF_H
# include <QString>
#include <QSqlQueryModel>
class Staff
{
public:
    Staff();
    Staff(QString,QString,int,int,int,QString,QString);

    QString getnom();
    QString getprenom();
    QString getemail ();
    QString getfonction ();
    int getnb_heurs ();
    int getid();
    int getsalaire();
    void setnom (QString);
    void setprenom (QString);
    void setemail (QString);
    void setfonction (QString);
    void setnb_heurs(int);
    void setid(int);
    void setsalaire(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int);
     bool modifier(int);
; private:
    QString nom , prenom , email , fonction ;
 int nb_heurs ,id_staff ,salaire ;
};

#endif // STAFF_H
