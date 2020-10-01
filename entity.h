#pragma once;

#include <QObject>
#include <QUuid>

class Country: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid Id READ getId WRITE setId)
    Q_PROPERTY(QString CountryName READ getCountryName WRITE setCountryName)
public:
    explicit Country(QUuid Id, QString CountryName):
        m_Id{Id},
        m_CountryName{CountryName}
    {}

    ~Country(){}

    QUuid getId() const
    {
        return m_Id;
    }

    QString getCountryName() const
    {
        return m_CountryName;
    }

public slots:
    void setId(QUuid Id)
    {
        m_Id = Id;
    }

    void setCountryName(QString CountryName)
    {
        m_CountryName = CountryName;
    }

private:
    QUuid m_Id;
    QString m_CountryName;
};

class Company: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUuid Id READ getId WRITE setId)
    Q_PROPERTY(QString CompanyName READ getCompanyName WRITE setCompanyName)
    Q_PROPERTY(Country *CompanyCountry READ getCompanyCountry WRITE setCompanyCountry)
public:
    explicit Company(QUuid Id, QString CompanyName, Country *CompanyCountry):
        m_Id{Id},
        m_CompanyName{CompanyName},
        m_CompanyCountry{CompanyCountry}
    {}
    Company() {
        m_Id = QUuid::createUuid();
        m_CompanyName = "";
        m_CompanyCountry = new Country(QUuid::createUuid(), "");
    }

    ~Company()
    {}

    QUuid getId() const
    {
        return m_Id;
    }

    QString getCompanyName() const
    {
        return m_CompanyName;
    }

    Country *getCompanyCountry() const
    {
        return m_CompanyCountry;
    }

public slots:
    void setId(QUuid Id)
    {
        m_Id = Id;
    }

    void setCompanyName(QString CompanyName)
    {
        m_CompanyName = CompanyName;
    }

    void setCompanyCountry(Country *CompanyCountry)
    {
        m_CompanyCountry = CompanyCountry;
    }

private:
    QUuid m_Id;
    QString m_CompanyName;
    Country *m_CompanyCountry;
};
