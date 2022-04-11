#include "commande.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QComboBox>
#include <QTableView>
#include <QTimer>
#include <QDateTime>

Commande::Commande()
{
 ID_CMD=0;PRIX=0;DATE_COM=" ";QT_COMMANDES=0;ID_CL=0;FK_LIVRAISON=0;FK_PRODUIT=0;
};

 Commande::Commande(int ID_CMD,float PRIX,QString DATE_COM,int QT_COMMANDES,int ID_CL,int FK_LIVRAISON,int FK_PRODUIT)
 {
     this ->ID_CMD=ID_CMD;
     this->PRIX=PRIX;
     this->DATE_COM=DATE_COM;
     this->QT_COMMANDES=QT_COMMANDES;
     this->ID_CL=ID_CL;
     this->FK_LIVRAISON=FK_LIVRAISON;
     this->FK_PRODUIT=FK_PRODUIT;
 }


bool Commande::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(ID_CMD);
    QString fes = QString::number(PRIX);
    QString bes = QString::number(QT_COMMANDES);
    QString fk_string = QString::number(ID_CL);

    query.prepare("INSERT INTO COMMANDES (ID_COMMANDE,QT_COMMANDES, DATE_COM, PRIX) "
                          "VALUES (:ID_CMD,:QT_COMMANDES, :DATE_COM,:PRIX)");
    query.bindValue(":ID_CMD",res);
    query.bindValue(":PRIX",fes);
    query.bindValue(":DATE_COM",DATE_COM);
    query.bindValue(":QT_COMMANDES",bes);
    query.bindValue(":ID_CL",fk_string);
    QSqlQuery qry;
        QDateTime dateTime=QDateTime::currentDateTime();
        QString date=dateTime.toString();
        qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('Insertion Commandes',:dateTime)");
        qry.bindValue(":dateTime",dateTime);


        qry.exec();


        if(!query.exec()){
            qDebug()<<"not added";
        }

        return true;
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->showMessage("Gestion des commandes "," Commande added ",QSystemTrayIcon::Information,15000);
}



// recherche


void Commande::rechercher_ID_CMD(QTableView *table, int x)
   {
      QSqlQueryModel *model=new QSqlQueryModel();
      QSqlQuery *query =new QSqlQuery;
      query->prepare("select * from commandes where regexp_like(ID_COMMANDE,:ID_COMMANDE);");
      query->bindValue(":ID_COMMANDE",x);
      if(x==0)
      {
          query->prepare("select * from commandes;");
      }
      query->exec();
      model->setQuery(*query);
      table->setModel(model);
      table->show();
   }
void Commande::rechercherr_QT_COMMANDES(QTableView *table, int x)
   {
      QSqlQueryModel *model=new QSqlQueryModel();
      QSqlQuery *query =new QSqlQuery;
      query->prepare("select * from commandes where regexp_like(QT_COMMANDES,:QT_COMMANDES);");
      query->bindValue(":QT_COMMANDES",x);
      if(x==0)
      {
          query->prepare("select * from commandes;");
      }
      query->exec();
      model->setQuery(*query);
      table->setModel(model);
      table->show();
   }
void Commande::rechrcherr_PRIX(QTableView *table, int x)
   {
      QSqlQueryModel *model=new QSqlQueryModel();
      QSqlQuery *query =new QSqlQuery;
      query->prepare("select * from commandes where regexp_like(PRIX,:PRIX);");
      query->bindValue(":PRIX",x);
      if(x==0)
      {
          query->prepare("select * from commandes;");
      }
      query->exec();
      model->setQuery(*query);
      table->setModel(model);
      table->show();
   }

QSqlQueryModel * Commande::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("select * from commandes");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CMD"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRIX"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_COM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("QT_COMMANDES"));



    return model;


}
// tri ID_CMD
  QSqlQueryModel * Commande::sort_ID_CMD(){
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from commandes order by ID_COMMANDE ");
        return model;
}

// tri function
QSqlQueryModel * Commande::sort_function_cmd(){
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from commandes order by function_cmd  ");
        return model;
}

// clear table
void cleartable(QTableView * table );
void Commande::cleartable(QTableView * table){
     QSqlQueryModel *model=new QSqlQueryModel();
     model->clear();
     table->setModel(model);
}
QSqlQueryModel* Commande::combobox_fk()
{QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select CIN from CLIENTS");
    return model;
}
// tri QT_COMMMANDES
  QSqlQueryModel * Commande::sort_QT_COMMANDES(){
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from commandes order by QT_COMMANDES ");
        return model;
}

// tri function
QSqlQueryModel * Commande::sort_function_cm(){
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from commandes order by function_cmd  ");
        return model;
}

// clear table
void cleartablee(QTableView * table );
void Commande::cleartablee(QTableView * table){
     QSqlQueryModel *model=new QSqlQueryModel();
     model->clear();
     table->setModel(model);
}
bool Commande::supprimer(int ID_CMD)
{
   QSqlQuery query;
   QString res=QString::number(ID_CMD);

   query.prepare("Delete from commandes where ID_COMMANDE= :ID_CMD");
   query.bindValue(":ID_CMD",res);
   QSqlQuery qry;
       QDateTime dateTime=QDateTime::currentDateTime();

       QString date=dateTime.toString();

       qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('supression Commandes',:dateTime)");
       qry.bindValue(":dateTime",dateTime);


       qry.exec();
   return query.exec();
}

bool Commande::modifier()
{
        QSqlQuery  query;
        QString id_string=QString::number(ID_CMD);
        QString prix_string=QString::number(PRIX);
        QString qt_string=QString::number(QT_COMMANDES);
        query.prepare("UPDATE COMMANDES SET  PRIX=:prix,DATE_COM=:DATE_COM,QT_COMMANDES=:QT_COMMANDES WHERE ID_COMMANDE=:ID_COMMANDE");
        query.bindValue(":ID_COMMANDE", id_string);
        query.bindValue(":prix", prix_string);
        query.bindValue(":DATE_COM", DATE_COM);
        query.bindValue(":QT_COMMANDES", qt_string);
        QSqlQuery qry;
            QDateTime dateTime=QDateTime::currentDateTime();
            QString date=dateTime.toString();
            qry.prepare("insert into HISTORIQUE (ACTIVITE_H,DATE_H) values ('modification Commandes',:dateTime)");
            qry.bindValue(":dateTime",dateTime);
            qry.exec();

        return query.exec();
        /*QSqlQueryModel* Commande::combobox_fk();*/

}
QSqlQueryModel * Commande::afficher_historique()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Activite"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date et Heure"));
    return model;
}
