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
        qDebug() << lDatabase.lastError().text();
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
        qDebug() << QSqlDatabase::database().lastError().text();
        errorCode = IMPOSSIBLECREATEDATABASETABLE;
    }

    //Creation table UserPets
    if(errorCode == OK)
    {
        QSqlQuery lQuery2;
        lQuery2.prepare("CREATE TABLE `UserPets` ("
                       "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "`idPets` INTEGER NOT NULL,"
                       "`feedDate` NUMERIC NOT NULL,"
                       "FOREIGN KEY(idPets) REFERENCES Pets(id));");
        if(!lQuery2.exec())
        {
            qDebug() << QSqlDatabase::database().lastError().text();
            errorCode = IMPOSSIBLECREATEDATABASETABLE;
        }
    }

    return errorCode;
}


