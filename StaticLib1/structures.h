/**
* \file structures.h
* \brief Файл со структурами.
* \date Дата последней модификации - 11.01.2022
*/
#pragma once
namespace sReader
{
	/**
	* \brief Структура информации об услуге
	* \Taxes Структура информации об услуге
	*/
	struct Taxes 
	{
		long long int	number;	///< Поле структуры номер квартиры
		char name[6]; ///< Поле структуры название услуги
		long long int	tariff; ///< Поле структуры услуга
		long long int	code; ///< Поле структуры вариант расчёта ОДН
	};

	/**
	* \brief Структура информации ОДПУ
	* \Record_GHMD Структура информации ОДПУ
	*/
	struct Record_GHMD
	{
		long long int	month; ///< Поле структуры месяц
		long long int	list[6]; ///< Поле структуры список данных
		long long int	count; ///< Поле структуры 
	};
	
	/**
	* \brief Структура информации ИПУ
	* \Record_IMD Структура информации ИПУ
	*/
	struct Record_IMD 
	{
		long long int	month; ///< Поле структуры месяц
		long long int	flat;///< Поле структуры номер квартиры
		long long int	list[6]; ///< Поле структуры список данных
		long long int	count; ///< Количество месяцев отсчёта
	};

	/**
	* \brief Структура информации о квартире
	* \Flat Структура информации о квартире
	*/
	struct Flat 
	{
		long long int	number; ///< Поле структуры номер квартиры
		long long int	S; ///< Поле структуры площадь квартиры
		long long int	count; ///< Поле структуры количество жильцов в квартире
	};

	/**
	* \brief Структура информации о запросе
	* \Query Структура информации о запросе
	*/
	struct Query
	{
		long long int flat; ///< Поле структуры номер квартиры
		char taxes_name[6]; ///< Поле структуры список данных
		long long int month_start; ///< Поле структуры месяц начала отсчёта
		long long int month_end;  ///< Поле структуры месяц конца отсчёта
	};

	/**
	* \brief Структура результата чтения файлов
	* \Result Структура результата чтения файлов
	*/
	struct Result 
	{
		Flat* flats = nullptr; ///< Нулевой указатель flats
		long long int flats_count; ///< Поле структуры количество квартир
		long long int gS; ///< Поле структуры количество квартир
		Taxes taxes[6]; ///< Структура taxes на 6 элементов
		long long int taxes_count; ///< Поле структуры счётчик общей стоимости
		Record_GHMD* ghmd = nullptr; ///< Нулевой указатель ghmd
		long long int ghmd_count; ///< Поле структуры счётчик услуги по ОДПУ
		Record_IMD* imd = nullptr; ///< Нулевой указатель imd
		long long int imd_count; ///< Поле структуры счётчик услуги по ИПУ
		Query query; ///< Структура query
		~Result() ///< Конструктор Result
		{
			if (flats != nullptr) delete[] flats;
			if (ghmd != nullptr) delete[] ghmd;
			if (imd != nullptr) delete[] imd;
		}
	};

	/**
	* \brief Структура записи в отчёте за один месяц
	* \Record_Report Структура записи в отчёте за один месяц
	*/
	struct Record_Report 
	{
		long long int month = 0; ///< Поле структуры месяц
		long long int fsum = 0; ///< Поле структуры общего потребления заданной услуги
		long long int fsum_cost = 0; ///< Поле структуры суммарного потребления заданной услуги
		long long int odn = 0; ///< Поле структуры общего потребления ОДН
		long long int odn_cost = 0; ///< Поле структуры суммарного потребления ОДН заданной услуги
	};

	/**
	* \brief Структура отчёта.
	* \Report Структура отчёта
	*/
	struct Report
	{
		long long int fsum = 0; ///< Поле структуры общего потребления заданной услуги
		long long int fsum_cost = 0; ///< Поле структуры суммарного потребления заданной услуги
		long long int odn = 0; ///< Поле структуры общего потребления ОДН
		long long int odn_cost = 0; ///< Поле структуры суммарного потребления ОДН заданной услуги

		long long int mcount = 0; ///< Поле структуры интервал количества месяцев

		Record_Report* list = nullptr; ///< Нулевой указатель list
		~Report() ///< Конструктор Report
		{
			if (list != nullptr) delete[] list;
		}
	};

	/**
	* \brief Функция для проверки открытия всех вайлов
	* \param Result 
	* \exception Исключений нет.
	* \return Возвращает bool значение - результат открытия всех файлов
	*/
	bool Init(Result&);

	/**
	* \brief Функция для проверки открытия файла home.txt
	* \param Result
	* \exception Исключений нет.
	* \return Возвращает bool значение - результат открытия файла home.txt
	*/
	bool readHome(Result&);

	/**
	* \brief Функция для проверки открытия файла taxes.txt
	* \param Result
	* \exception Исключений нет.
	* \return Возвращает bool значение - результат открытия файла taxes.txt
	*/
	bool readTaxes(Result&);

	/**
	* \brief Функция для проверки открытия файла details.txt
	* \param Result
	* \exception Исключений нет.
	* \return Возвращает bool значение - результат открытия файла details.txt
	*/
	bool readDetails(Result&);
}