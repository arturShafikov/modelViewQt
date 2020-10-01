#pragma once;
#include "entity.h"

class DataModel
{

public:
    DataModel(){

    }

    void InitModel(){

        Country *NewCountry;

        NewCountry = new Country(QUuid::createUuid(), "Country 0");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "Company 0", NewCountry ));

        NewCountry = new Country(QUuid::createUuid(), "Country 1");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "Company 1", NewCountry ));

        NewCountry = new Country(QUuid::createUuid(), "Country 2");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "Company 2", NewCountry ));

        NewCountry = new Country(QUuid::createUuid(), "Country 3");
        m_CountryList.append(NewCountry);
        m_CompanyList.append(new Company( QUuid::createUuid(), "Company 3", NewCountry ));
    }

    ~DataModel(){
        qDeleteAll(m_CompanyList.begin(),m_CompanyList.end());
        qDeleteAll(m_CountryList.begin(),m_CountryList.end());

    }

    const QList<Company*> &getCompanyList() const{
        return m_CompanyList;
    }

    const QList<Country*> &getCountryList() const{
        return m_CountryList;
    }


    QList<Company*> &getCompanyList(){
        return m_CompanyList;
    }

    QList<Country*> &getCountryList(){
        return m_CountryList;
    }

private:
    QList<Company*> m_CompanyList;
    QList<Country*> m_CountryList;
};

