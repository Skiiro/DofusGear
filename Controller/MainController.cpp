#include "MainController.h"
#include "Model/DataBase.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    DataBase* lDatabase = DataBase::getInstance();
    lDatabase->createDatabase();
}
