#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class DataBase : public QObject
{
    Q_OBJECT
public:
    /**
     * @fn getInstance
     * @brief Get the instance of this class (see Singleton pattern)
     * @return instance of Database class
     */
    static DataBase* getInstance();
    /**
     * @fn killInstance
     * @brief Kill the current instance
     */
    static void killInstance();

    /**
     * @fn createDatabase
     * @brief Create a sqlite database named pName
     * @param pName: database name
     * @return error code
     */
    int createDatabase(QString pName = "");
signals:

public slots:

private:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    /**
     * @fn createTables
     * @brief Create database tables
     * @param pDatabase: database
     * @return: error code
     */
    int createTables();

    static DataBase* mInstance;

    /**
     * @fn fillPetsTable
     * @brief Fill pets table
     * @return error code
     */
    int fillPetsTable();
};

#endif // DATABASE_H
