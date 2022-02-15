/**
* \file StaticLib1.cpp
* \brief Главный файл библетеки, который нужно подключать к приложению.
* \date Дата последней модификации - 11.01.2022
*/
#include "pch.h"
#include "framework.h"
#include "readfiles.h"
#include <fstream>
#include <cassert> 
#define FILE_HOME "home.txt"
#define FILE_TAXES "taxes.txt"
#define FILE_DETAILS "details.txt"

/**
* \Init Функция чтения общая
*/
bool sReader::Init(sReader::Result& r) 
{
	using namespace sReader;
	assert(readHome(r) && readTaxes(r) && readDetails(r));
	return readHome(r) && readTaxes(r) && readDetails(r);
}

/**
* \readHome Функция чтения для файла home.txt
*/
bool sReader::readHome(sReader::Result& r)
{
	FILE* f;

	//----------------------------------------------------
	// Проверка на открытие файла home.txt
	//----------------------------------------------------
	if (fopen_s(&f, FILE_HOME, "r") != 0) 
	{
		return false; 
	}

	//----------------------------------------------------
	// Чтение количества квартир и общей площади здания
	//----------------------------------------------------
	fscanf_s(f, "%lld %lld\n", &r.flats_count, &r.gS); 

	//----------------------------------------------------
	// Выделение памяти под квартиры
	//----------------------------------------------------
	r.flats = new Flat[r.flats_count];

	//----------------------------------------------------
	// Чтение информации о квартирах
	//----------------------------------------------------
	for (long long int i = 0; i < r.flats_count; i++) 
	{
		r.flats[i].number = i + 1;
		fscanf_s(f, "%lld %lld\n", &r.flats[i].S, &r.flats[i].count);
	}

	fclose(f);
	return true;
}

/**
* \readTaxes Функция чтения для файла taxes.txt
*/
bool sReader::readTaxes(sReader::Result& r)
{
	FILE* f;

	//----------------------------------------------------
	// Проверка на открытие файла taxes.txt
	//----------------------------------------------------
	if (fopen_s(&f, FILE_TAXES, "r") != 0)
	{
		return false;
	}

	//----------------------------------------------------
	// Чтение количества услуг
	//----------------------------------------------------
	fscanf_s(f, "%lld\n", &r.taxes_count);

	//----------------------------------------------------
	// Чтение информации об услугах
	//----------------------------------------------------
	for (long long int i = 0; i < r.taxes_count; i++)
	{
		r.taxes[i].number = i;

		fscanf_s(f, "%5s %lld %lld\n", r.taxes[i].name, 6, &r.taxes[i].tariff, &r.taxes[i].code);
	}

	fclose(f);

	return true;
}

/**
* \readDetails Функция чтения для файла details.txt
*/
bool sReader::readDetails(sReader::Result& r)
{
	FILE* f;

	//----------------------------------------------------
	// Проверка на открытие файла details.txt
	//----------------------------------------------------
	if (fopen_s(&f, FILE_DETAILS, "r") != 0)
	{
		return false;
	}

	//----------------------------------------------------
	// Чтение количества показаний ОДПУ
	//----------------------------------------------------
	fscanf_s(f, "%lld\n", &r.ghmd_count);

	//----------------------------------------------------
	// Выделение памяти для чтение показаний ОДПУ
	//----------------------------------------------------
	r.ghmd = new Record_GHMD[r.ghmd_count];
	long long int tmonth;
	long long int tyear;

	//----------------------------------------------------
	// Чтение показаний ОДПУ
	//----------------------------------------------------
	for (long long int i = 0; i < r.ghmd_count; i++)
	{
		fscanf_s(f, "%lld.%lld ", &tmonth, &tyear);

		r.ghmd[i].month = (tyear - 2021) * 12 + (tmonth - 8);
		r.ghmd[i].count = r.taxes_count;

		for (long long int j = 0; j < r.taxes_count; j++)
		{
			fscanf_s(f, "%lld", &r.ghmd[i].list[j]);
		}
	}

	//----------------------------------------------------
	// Чтение количества показаний ИПУ
	//----------------------------------------------------
	fscanf_s(f, "%lld\n", &r.imd_count);

	//----------------------------------------------------
	// Выделение памяти для чтение показаний ИПУ
	//----------------------------------------------------
	r.imd = new Record_IMD[r.imd_count];

	//----------------------------------------------------
	// Чтение показаний ИПУ
	//----------------------------------------------------
	for (long long int i = 0; i < r.imd_count; i++) 
	{
		fscanf_s(f, "%lld.%lld %lld", &tmonth, &tyear, &r.imd[i].flat);

		r.imd[i].month = (tyear - 2021) * 12 + (tmonth - 8);
		r.imd[i].count = r.taxes_count;

		for (long long int j = 0; j < r.taxes_count; j++)
		{
			fscanf_s(f, "%lld", &r.imd[i].list[j]);
		}
	}

	fclose(f);

	return true;
}