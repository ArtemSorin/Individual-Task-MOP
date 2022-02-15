#pragma once
#include "structures.h";
/**
* \file readfiles.h
* \brief Функции статической библиотеки
* \date Дата последней модификации - 11.01.2022
*/
namespace sReader
{
	bool Init(Result&);
	bool readHome(Result&);
	bool readTaxes(Result&);
	bool readDetails(Result&);
}