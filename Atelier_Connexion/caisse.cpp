#include "caisse.h"
#include "ui_Caisse.h"


Caisse::Caisse(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Caisse)
{
    ui->setupUi(this);
    this->Blocked=true;
    this->ajout=false;

    this->setWindowTitle("Fiche Caisse");
       this->PixTrueIcon=QPixmap("images/True_icon.jpeg");
       this->PixFalseIcon=QPixmap("images/False_icon.jpeg");

}

void Caisse::verifAjout()
{
    if (this->ajout){
           this->setWindowTitle("Nouvelle fiche Caisse");
          ui->pushButton_bloquedCaisse->setEnabled(false);
          ui->pushButton_supprimerCaisse->setEnabled(false);
          ui->dateEdit_date->setDate(QDate::currentDate());
     }

}

void Caisse::setCaisse()
{
    domcaisse.getData(IDtoDisplay);

       ui->lineEdit_montant->setText(QString::number(domcaisse.getMontant()));
       ui->dateEdit_date->setDate(domcaisse.getDate());
       ui->plainTextEdit_description->setPlainText(domcaisse.getLibelle());

       ui->comboBox_type->setCurrentIndex(ui->comboBox_type->findData(domcaisse.getType(), Qt::DisplayRole));
        cleanControlFiche();

}

void Caisse::cleanControlFiche()
{
    ui->label_dateControl->clear();
    ui->label_typeControl->clear();
    ui->label_descriptionControl->clear();
    ui->label_montantControl->clear();

}

Caisse::~Caisse()
{
    delete ui;
}

bool Caisse::VerifDate()
{

    if (ui->dateEdit_date->date()==QDate::fromString("01/01/1000","dd/MM/yyyy"))
       {
           ui->label_dateControl->setPixmap(PixFalseIcon);
           return false;
       }
       else
       {

        ui->label_dateControl->setPixmap(PixTrueIcon);
           return true;
       }
}

bool Caisse::VerifType()
{

    if (ui->comboBox_type->currentIndex()>-1)
    {
         ui->label_typeControl->setPixmap(PixTrueIcon);
        return true;
    }
    else
    {
         ui->label_typeControl->setPixmap(PixFalseIcon);
        return false;
    }
}

bool Caisse::VerifMontant()
{

    if (ui->lineEdit_montant->text().isEmpty() || ui->lineEdit_montant->text().contains(QRegExp("[^.0-9]")) || ui->lineEdit_montant->text().length()<3 || ui->lineEdit_montant->text().length()>8)
    {
        ui->label_montantControl->setPixmap(PixFalseIcon);
        return false;
    }
    else
    {
        ui->label_montantControl->setPixmap(PixTrueIcon);
        return true;
    }
}



void Caisse::on_pushButton_sauvegarderCaisse_clicked()
{

    if(!this->ajout){

             domcaisse.setLibelle(ui->plainTextEdit_description->toPlainText());
             domcaisse.setDate(ui->dateEdit_date->date());
             domcaisse.setMontant(ui->lineEdit_montant->text().toFloat());
             domcaisse.setType(ui->comboBox_type->currentText());


             if (this->Blocked){
                 QMessageBox::critical(this,
                                       tr("CAISSE PRESSING"),
                                       tr("L'interface est bloquée, Veuillez la débloquée !") );
             }
             else{

                  VerifDate();
                  VerifMontant();
                  VerifType();

                  if( VerifDate() && VerifMontant() && VerifType()){

                      if (domcaisse.update(this->IDtoDisplay)){
                                     QMessageBox::information(this,
                                                              tr("CAISSE PRESSING"),
                                                              tr("Caisse modifiée avec succès!"));
                      }
                      else{
                          QMessageBox::critical(this,
                                                tr("CAISSE PRESSING"),
                                                tr("caisse n'a pas été modifiée, Une erreur s'est produite lors de l'insertion des données dans la base !"));
                      }

                  }
                      else{
                          QMessageBox::critical(this,
                                                tr("CAISSE PRESSING"),
                                                tr("La caisse n'a pas été modifiée, Veuillez verifier les champs  saisis !"));
                  }
              }
          }

    else
    {
        domcaisse.setLibelle(ui->plainTextEdit_description->toPlainText());
        domcaisse.setDate(ui->dateEdit_date->date());
        domcaisse.setMontant(ui->lineEdit_montant->text().toFloat());
        domcaisse.setType(ui->comboBox_type->currentText());

        VerifDate();
        VerifMontant();
        VerifType();

        if( VerifDate() && VerifMontant() && VerifType())
        {
            if(domcaisse.found(domcaisse.getType(),domcaisse.getLibelle())<1){
                if (domcaisse.ajout()){
                     QMessageBox::information(this,
                                             tr("CAISSE PRESSING"),
                                             tr("La caisse a été ajoutée avec succès!"));
                             }
            }

            else {
                QMessageBox::critical(this,
                                     tr("CAISSE PRESSING"),
                                     tr("La caisse n'a pas été ajoutée, car elle existe déjà dans la base de données !") );
             }

        }
        else{
            QMessageBox::critical(this,
                                  tr("CAISSE PRESSING"),
                                  tr("La caisse n'a pas été ajoutée, Veuillez verifier les champs saisis !") );
        }
    }
}







void Caisse::on_pushButton_supprimerCaisse_clicked()
{
    QMessageBox::StandardButton reply;
           reply = QMessageBox::question(this, "Supprimer Caisse", "Etes-vous sûr de vouloir supprimer cette caisse ?",
                                         QMessageBox::Yes|QMessageBox::No);
           if (reply == QMessageBox::Yes) {

               if (domcaisse.supprime(IDtoDisplay)){
                   QMessageBox::information(
                               this,
                               tr("CAISSE PRESSING"),
                               tr("Cette caisse a été supprimée avec succès !") );
                               this->hide();


               }
           }

}

void Caisse::on_pushButton_bloquedCaisse_clicked()
{

    if(this->Blocked){
        ui->pushButton_bloquedCaisse->setText("Bloquer");
    }
    else {
        ui->pushButton_bloquedCaisse->setText("Débloquer");
    }
    this->Blocked=!Blocked;
}
