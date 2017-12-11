#include "DataBase.h"
#include "Tools/errorcode.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QSqlError>

DataBase* DataBase::mInstance=nullptr;

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

DataBase* DataBase::getInstance()
{
    if(mInstance == nullptr)
        mInstance = new DataBase();
    return mInstance;
}

void DataBase::killInstance()
{
    if(mInstance != nullptr)
    {
        delete mInstance;
        mInstance = nullptr;
    }
}

int DataBase::createDatabase(QString pName)
{
    int lErrorCode = OK;
    //set a default name to the database
    if(pName == "")
        pName = "Dofus.sqlite3";

    //verify if database is already existing or not
    QFile lFile(QApplication::applicationDirPath() + "/" + pName);
    bool databaseCreated = lFile.exists();

    QSqlDatabase lDatabase = QSqlDatabase::addDatabase("QSQLITE");
    lDatabase.setDatabaseName(QApplication::applicationDirPath() + "/" +  pName);

    if(lDatabase.open())
    {
        if(!databaseCreated)
            lErrorCode = createTables();
    }
    else
    {
        qDebug() << "Impossible to open the database : " << lDatabase.lastError().text();
        lErrorCode = DATABASENOTOPENED;
    }

    return lErrorCode;
}

int DataBase::createTables()
{
    int errorCode = OK;

    //Creation table Pets
    QSqlQuery lQuery;
    lQuery.prepare("CREATE TABLE `Pets`("
                   "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "`frequencyMin` INTEGER NOT NULL,"
                   "`frequencyMax` INTEGER NOT NULL,"
                   "`food` TEXT NOT NULL,"
                   "`name` TEXT NOT NULL);");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create Pets table : " <<  QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEDATABASETABLE;
    }

    //Creation table UserPets
    if(errorCode == OK)
    {
        QSqlQuery lQuery;
        lQuery.prepare("CREATE TABLE `UserPets` ("
                       "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "`idPets` INTEGER NOT NULL,"
                       "`feedDate` NUMERIC NOT NULL,"
                       "FOREIGN KEY(idPets) REFERENCES Pets(id));");
        if(!lQuery.exec())
        {
            qDebug() << "Impossible to create userPets table : " << QSqlDatabase::database().lastError().text();
            errorCode = IMPOSSIBLECREATEDATABASETABLE;
        }
    }

    //Fill the table Pets
    if(errorCode == OK)
        errorCode = fillPetsTable();

    return errorCode;
}

int DataBase::fillPetsTable()
{
    int errorCode = OK;
    QSqlQuery lQuery;

    //Dauge
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (3,"
                   "36,"
                   "'Os',"
                   "'Dauge')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Dauge pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Peki
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (3,"
                   "36,"
                   "'Riz, Graine de Pandouille, Racine de Bulbiflore, Racine de Bulbuisson, Racine de Bulbambou, Racine de Bulbig, Fleur de Bulbiflore, Feuille de Bulbuisson, Pousses de Bulbambou, Feuille de Bambouto, Feuille de Bambouto Sacré, Racine Magique de Bambouto, Racine Magique de Bambouto Sacré',"
                   "'Péki')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Péki pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Médugivre
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Perce-Neige',"
                   "'Médugivre')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Médugivre pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Fotome
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Os',"
                   "'Fotome')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Fotome pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Vilain Petit Corbac
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Os',"
                   "'Vilain Petit Corbac')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Vilain Petit Corbac pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Pioute Rose
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Pioute Rose')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Pioute Rose pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Cromeugnon
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Frostiz',"
                   "'Cromeugnon')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Cromeugnon pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Platypus
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (12,"
                   "72,"
                   "'Vertgely, Rougely, Blugely, Multygely',"
                   "'Platypus')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Platypus pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Dragoune Rose
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Fantôme de Familier',"
                   "'Dragoune rose')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Dragoune Rose pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Ecureuil Chenapan
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Ecureuil Chenapan')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Ecureuil Chenapan pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Pioute Rouge
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Pioute Rouge')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Pioute Rouge pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bworky
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Noix de Cajou, Noix de Pécan, Gland, Noisette',"
                   "'Bworky')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bworky pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Crocodaille
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Crocodaille')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Crocodaille pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Tirubim
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Tirubim')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Tirubim pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Chacha Angora
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Chacha Angora')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "chacha Angora pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Pioute Vert
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Pioute Vert')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Pioute Vert pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bilby
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Fleur',"
                   "'Bilby')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bilby pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Walk
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Walk')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Walk pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Ross
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Cawotte',"
                   "'Ross')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Ross pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Atoin
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson(Soin), Viande(Dommage)',"
                   "'Atouin')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Atouin pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Mini Wa
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson(Intelligence), Graine(Agilité), Huile(Chance), Viande(Force)',"
                   "'Mini Wa')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Mini Wa pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bwak de Feu
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (11,"
                   "36,"
                   "'Graine de Sésame(Intelligence), Graine de Tournesol(Intelligence), Graine de Pavot(Intelligence), Graine de Lin(Intelligence), Graine de Chanvre(Intelligence), Fraise(Vitalité), Gland(Vitalité), Noisette(Vitalité), Noix de Cajou(%Résistance Feu), Noix de Pécan(%Résistance Feu)',"
                   "'Bwak de Feu')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bwak de Feu pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Givrefoux
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Anguille Rôtie',"
                   "'Givrefoux')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Givrefoux pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Croum
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Ebonite(%Résistance Eau), Kriptonite(%Résistance Eau), Aluminite(%Résistance Air), Magnésite(%Résistance Terre), Kobalite(%Résistance Terre), Bakélélite(%Résistance Feu), Pyrute(%Résistance Feu), Kouartz(%Résistance Neutre), Rutile(%Résistance Neutre)',"
                   "'Croum')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Croum pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Pioute Bleu
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Pioute Bleu')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Pioute Bleu pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Willy le Relou
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Viande',"
                   "'Willy le Relou')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Willy le Relou pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bébé Pandawa
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Noisette, Riz',"
                   "'Bébé Pandawa')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "bébé Pandawa pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Fëanor
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Fëanor')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Fëanor pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Wabbit
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (24,"
                   "72,"
                   "'Cawotte(Sagesse), Intestin d''Araknosé(Chance), Langue d''Epouvanteur(Chance), Menthe Sauvage(Chance), Trèfle à 5 feuilles(Intelligence), Bave de Rose Démoniaque(Intelligence), Fruit de Palme(Force), Sève d''Abraknyde Retravaillée(Force), Fleur de Blop Coco(Agilité), Fleur de Blop Reinette(Agilité), Fleur de Blop Griotte(Agilité), Fleur de Blop Indigo(Agilité)',"
                   "'Wabbit')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Wabbit pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bwak d'eau
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (11,"
                   "36,"
                   "'Graine de Sésame(Chance), Graine de Tournesol(Chance), Graine de Pavot(Chance), Graine de Lin(Chance), Graine de Chanvre(Chance), Fraise(Vitalité), Gland(Vitalité), Noisette(Vitalité), Noix de Cajou(%Résistance Eau), Noix de Pécan(%Résistance Eau)',"
                   "'Bwak d''Eau')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bwak d'eau pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Ecumouth
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Bois de Tremble',"
                   "'Ecumouth')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Ecumouth pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Pioute Jaune
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Graine',"
                   "'Pioute Jaune')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Pioute Jaune pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bwak d'air
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (11,"
                   "36,"
                   "'Graine de Sésame(Agilité), Graine de Tournesol(Agilité), Graine de Pavot(Agilité), Graine de Lin(Agilité), Graine de Chanvre(Agilité), Fraise(Vitalité), Gland(Vitalité), Noisette(Vitalité), Noix de Cajou(%Résistance Air), Noix de Pécan(%Résistance Air)',"
                   "'Bwak d''Air')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bwak d'air pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Petit chacha Blanc
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "36,"
                   "'Viande',"
                   "'Petit Chacha Blanc')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Petit Chacha Blanc pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Minimino
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Plumes de Tofus, Bec de Tofus, Oeuf de Tofu, Dent de Tofu Mutant, Aile de Tofu Maléfique',"
                   "'Minimino')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Minimino pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Bwak de Terre
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (11,"
                   "36,"
                   "'Graine de Sésame(Force), Graine de Tournesol(Force), Graine de Pavot(Force), Graine de Lin(Force), Graine de Chanvre(Force), Fraise(Vitalité), Gland(Vitalité), Noisette(Vitalité), Noix de Cajou(%Résistance Terre), Noix de Pécan(%Résistance Terre)',"
                   "'Bwak de Terre')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Bwak de Terre pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Petit Chienchien noir
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (11,"
                   "36,"
                   "'Poisson',"
                   "'Petit Chienchien Noir')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Petit Chienchien Noir pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Koalak Sanguin
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Bandelette du Guerrier Koalak, Fémur de Koalak Farouche, Boomerang du Koalak Sanguin, Boomerang du Dok Alako, Boomerang du Maître Koalak, Boomerang du Warko Marron, Étoffe du Fauchalak',"
                   "'Koalak Sanguin')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Koalak Sanguin pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Nomoon
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (24,"
                   "72,"
                   "'Fleur de Gloutovore, Feuille de Fourbasse, Plume de Domoizelle, Tranche de Nodkoko',"
                   "'Nomoon')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Nomoon pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Chacha Tigré
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Poisson',"
                   "'Chacha tigré')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Chacha Tigré pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //Chacha
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "18,"
                   "'Plumes de Tofu(Agilité), Oeuf de Tofu(Agilité), Aile de Tofu Maléfique(Agilité), Oreilles du Tiwabbit(Force), Oreille du Grand Pa Wabbit(Force), Gelée à la Fraise(%Résistance Neutre), Gelée à la Menthe(%Résistance Neutre), Gelée Bleutée(%Résistance Neutre), Plume du Kwak de Glace(Intelligence), Plume du Kwak de Flamme(Intelligence), Plume du Kwak de Vent(Intelligence), Greuvette(Intelligence), Plume du Kwak de Terre(Intelligence), Greuvette vidée(Intelligence), Goujon(Intelligence), Goujon vidé(Intelligence), Sang de Dragon Cochon(Vitalité), Sang de Vampire(Vitalité), Souris Verte(Chance), Truite(Chance), Truite Vidée(Chance)',"
                   "'Chacha')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Chacha pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    //léopardo
    lQuery.prepare("INSERT INTO `Pets`(`frequencyMin`,"
                   "`frequencyMax`,"
                   "`food`,"
                   "`name`) "
                   "VALUES (5,"
                   "72,"
                   "'Viande',"
                   "'Léopardo')");
    if(!lQuery.exec())
    {
        qDebug() << "Impossible to create " << "Leopardo pet : " << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEROWPETSTABLE;
    }

    return errorCode;
}


