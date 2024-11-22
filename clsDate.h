//abdelaziz bahoumi

//this is the clsdate class that contains all methods related to date.
#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short Day;
	short Month;
	short Year;

public:
	clsDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;
	}
	clsDate(string sDate) {/* use this order 'mm / dd / yyyy' in intialization on main function to avoid bugs */

		vector <string> vDate = clsString::SplitString(sDate, "/");

		Day = stoi(vDate[0]);
		Month = stoi(vDate[1]);
		Year = stoi(vDate[2]);
	}
	clsDate(short Day,short Month,short Year) {

		this->Day = Day;
		this->Month = Month;
		this->Year = Year;
	}
	clsDate(short DayOrder, short Year) {

		clsDate Date = GetDateFromDayOrderInYear(Year, DayOrder);

		//this will construct a date order in year.
		this->Day = Date.Day;
		this->Month = Date.Month;
		this->Year = Date.Year;
	}

	void SetDay(short Day) {

		this->Day = Day;
	}
	short GetDay() {

		return Day;
	}

	void SetMonth(short Month) {

		this->Month = Month;
	}
	short GetMonth() {

		return Month;
	}

	void SetYear(short Year) {

		this->Year = Year;
	}
	short GetYear() {

		return Year;
	}

	void Print() {
		
		cout << DateToString() << endl;
	}

	static string DateToString(clsDate Date) {

		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString() {

		return DateToString(*this);
	}

	static bool IsLeapYear(int Year) {

		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}

	bool IsLeapYear() {

		return IsLeapYear(Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month) {

		short NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return ((Month == 2) ? ((IsLeapYear(Year)) ? 29 : 28) : NumberOfDays[Month - 1]);
	}

	static clsDate GetDateFromDayOrderInYear(short Year, short DaysOrderInYear) {

		clsDate Date;

		Date.Year = Year;
		Date.Month = 1;

		short MonthDays;
		short RemainingDays = DaysOrderInYear;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Year, Date.Month);

			if (RemainingDays > MonthDays) {

				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else {

				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}

	static clsDate GetSystemDate() {

		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;

		return Date;
	}

	static short DayOrder(short Year, short Month, short Day) {

		short a, y, m;

		a = ((14 - Month) / 12);
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOrder() {

		return DayOrder(Year, Month, Day);
	}

	static string DayName(short DayOrder) {

		string DayName[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return DayName[DayOrder];
	}
	string DayName() {

		return DayName(DayOrder());
	}

	static string MonthName(short MonthNumber) {

		string MonthName[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return MonthName[MonthNumber - 1];
	}
	string MonthName() {

		return MonthName(Month);
	}

	static void PrintMonthCalender(short Year, short Month) {

		short Current = DayOrder(Year, Month, 1);

		short NumberOfDays = NumberOfDaysInMonth(Year, Month);

		printf("\n  _______________%s_______________", MonthName(Month).c_str());
		cout << "\n\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		short i;

		for (i = 0; i < Current; i++)
			printf("     ");

		for (short j = 1; j <= NumberOfDays; j++) {

			printf("%5d", j);

			if (++i == 7) {

				i = 0;
				cout << "\n";
			}
		}
		cout << "\n  _________________________________\n\n";
	}
	void PrintMonthCalender() {

		PrintMonthCalender(Year, Month);
	}

	static void PrintYaerCalender(short Year) {

		cout << "\n\t __________________\n";
		cout << "\n\t Year " << Year << " Calender";
		cout << "\n\t __________________\n";


		for (short i = 1; i <= 12; i++) {

			PrintMonthCalender(Year, i);
		}
	}
	void PrintYaerCalender() {

		PrintYaerCalender(Year);
	}

	static short NumberOfDaysFromBeginningOfTheYear(short Year, short Month, short Day) {

		short TotalDays = 0;

		for (short i = 1; i < Month; i++) {

			TotalDays += NumberOfDaysInMonth(Year, i);
		}

		TotalDays += Day;

		return TotalDays;
	}
	short NumberOfDaysFromBeginningOfTheYear() {

		return NumberOfDaysFromBeginningOfTheYear(Year, Month, Day);
	}

	clsDate DateAfterAddDays(short AddingDays, clsDate Date) {

		short RemainingDays = AddingDays + NumberOfDaysFromBeginningOfTheYear(Date.Year, Date.Month, Date.Day);
		short MonthDays = 0;

		Date.Month = 1;

		while (true) {

			MonthDays = NumberOfDaysInMonth(Date.Year, Date.Month);

			if (RemainingDays > MonthDays) {

				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12) {

					Date.Month = 1;
					Date.Year++;
				}
			}
			else {

				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	void DateAfterAddDays(short AddingDays) {

		clsDate Date = DateAfterAddDays(AddingDays, *this);

		cout << "Date after adding " << AddingDays << " Day(s) is : ";
		cout << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2) {

		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2) {

		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2) {

		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}
	bool IsDate1EqualDate2(clsDate Date2) {

		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date) {

		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}
	bool IsLastDayInMonth() {

		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month) {

		return (Month == 12);
	}
	bool IsLastMonthInYear() {

		return IsLastMonthInYear(Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date) {

		if (IsLastDayInMonth(Date)) {

			Date.Day = 1;
			if (IsLastMonthInYear(Date.Month)) {

				Date.Month = 1;
				Date.Year++;
			}
			else {

				Date.Month++;
			}
		}
		else {

			Date.Day++;
		}
		return Date;
	}
	void IncreaseDateByOneDay() {

		clsDate Date = IncreaseDateByOneDay(*this);
		cout << "Date after adding one day : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
	}

	static short GetDiffrenceDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false) {

		short DiffDays = 0;

		if (IsDate1BeforeDate2(Date1, Date2)) {

			while (!IsDate1EqualDate2(Date1, Date2)) {

				Date1 = IncreaseDateByOneDay(Date1);
				DiffDays++;
			}
			return IncludingEndDay ? ++DiffDays : DiffDays;
		}
		else {

			cout << "\nDate 1 is not before date 2!!" << endl;
			return 0;
		}
	}
	short GetDiffrenceDays(clsDate Date2, bool IncludingEndDay = false) {

		return GetDiffrenceDays(*this, Date2, IncludingEndDay);
	}

	void SwapDates(clsDate& Date1, clsDate& Date2) {

		clsDate TempDate;

		TempDate.Year = Date1.Year;
		TempDate.Month = Date1.Month;
		TempDate.Day = Date1.Day;

		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;

		Date2.Year = TempDate.Year;
		Date2.Month = TempDate.Month;
		Date2.Day = TempDate.Day;
	}

	short GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludingEndDay = false) {

		short DiffDays = 0;
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2)) {

			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (!IsDate1EqualDate2(Date1, Date2)) {

			Date1 = IncreaseDateByOneDay(Date1);
			DiffDays++;
		}

		return IncludingEndDay ? ++DiffDays * SwapFlagValue : DiffDays * SwapFlagValue;
	}

	short GetDiffrenceInDays(clsDate Date2, bool IncludingEndDay = false) {

		return GetDiffrenceInDays(*this, Date2, IncludingEndDay);
	}

	static clsDate IncreaseDateByXDays(short Days, clsDate Date) {

		for (short i = 1; i <= Days; i++) {

			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(short Days) {

		clsDate Date = IncreaseDateByXDays(Days, *this);
		cout << "Date after adding " << Days << " day(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseDateByOneWeek(clsDate Date) {

		for (short i = 1; i <= 7; i++) {

			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek() {

		clsDate Date = IncreaseDateByOneWeek(*this);
		cout << "Date after adding one Week : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date) {

		for (short i = 1; i <= Weeks; i++) {

			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks) {
	
		clsDate Date = IncreaseDateByXWeeks(Weeks, *this);
		cout << "Date after adding " << Weeks << " Week(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date) {

		if (Date.Month == 12) {

			Date.Month = 1;
			Date.Year++;
		}
		else {

			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInCurrentMonth) {

			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	void IncreaseDateByOneMonth() {

		clsDate Date = IncreaseDateByOneMonth(*this);
		cout << "Date after adding one Month : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate IncreaseDateByXMonth(short Months, clsDate Date) {

		for (short i = 1; i <= Months; i++) {

			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonth(short Months) {

		clsDate Date = IncreaseDateByXMonth(Months, *this);
		cout << "Date after adding " << Months << " Months(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {

		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear() {

		clsDate Date = IncreaseDateByOneYear(*this);
		cout << "Date after adding one Year : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate Date) {

        Date.Year += Years;
        return Date;
    }
	void IncreaseDateByXYears(short Years) {

		clsDate Date = IncreaseDateByXYears(Years, *this);
		cout << "Date after adding " << Years << " Years(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date) {

		Date.Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade() {

		clsDate Date = IncreaseDateByOneDecade(*this);
		cout << "Date after adding one Decade : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseByXDecade(short Decade, clsDate Date) {

		for (short i = 1; i <= Decade; i++) {

			Date = IncreaseDateByOneDecade(Date);
		}

		//you can use this also it is the same.

		/*
		for (short i = 1; i <= Decade * 10; i++) {

			Date = IncreaseDateByOneYear(Date);
		}
		*/
		return Date;
	}
	void IncreaseByXDecade(short Decade) {

		clsDate Date = IncreaseByXDecade(Decade, *this);
		cout << "Date after adding " << Decade << " Decade(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseByXDecadeFaster(short Decade, clsDate Date) {

		Date.Year += Decade * 10;
		return Date;
	}
	void IncreaseByXDecadeFaster(short Decade) {

		clsDate Date = IncreaseByXDecadeFaster(Decade, *this);
		cout << "Date after adding " << Decade << " Decade(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseByOneCentury(clsDate Date) {

		Date.Year += 100;
		return Date;
	}
	void IncreaseByOneCentury() {

		clsDate Date = IncreaseByOneCentury(*this);
		cout << "Date after adding one Century : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate IncreaseByOneMillennium(clsDate Date) {

		Date.Year += 1000;
		return Date;
	}
	void IncreaseByOneMillennium() {

		clsDate Date = IncreaseByOneMillennium(*this);
		cout << "Date after adding one Millennium : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByOneDay(clsDate Date) {

		if (Date.Day == 1) {

			if (Date.Month == 1) {

				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else {

				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month--);
			}
		}
		else {

			Date.Day--;
		}
		return Date;
	}
	void DecreaseDateByOneDay() {

		clsDate Date = DecreaseDateByOneDay(*this);
		cout << "Date after Decreasing one day : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate Date) {

		for (short i = 1; i <= Days; i++) {

			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(short Days) {

		clsDate Date = DecreaseDateByXDays(Days, *this);
		cout << "Date after Decreasing " << Days << " day(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date) {

		for (short i = 1; i <= 7; i++) {

			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {

		clsDate Date = DecreaseDateByOneWeek(*this);
		cout << "Date after Decreasing one Week : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date) {

		for (short i = 1; i <= Weeks; i++) {

			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks) {

		clsDate Date = DecreaseDateByXWeeks(Weeks, *this);
		cout << "Date after Decreasing " << Weeks << " Week(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date) {

		if (Date.Month == 1) {

			Date.Month = 12;
			Date.Year--;
		}
		else {

			Date.Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInCurrentMonth) {

			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	void DecreaseDateByOneMonth() {

		clsDate Date = DecreaseDateByOneMonth(*this);
		cout << "Date after Decreasing one Month : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate DecreaseDateByXMonth(short Months, clsDate Date) {

		for (short i = 1; i <= Months; i++) {

			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonth(short Months) {

		clsDate Date = DecreaseDateByXMonth(Months, *this);
		cout << "Date after Decreasing " << Months << " Months(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;

	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {

		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear() {

		clsDate Date = DecreaseDateByOneYear(*this);
		cout << "Date after Decreasing one Year : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByXYear(short Years, clsDate Date) {

		for (short i = 1; i <= Years; i++) {

			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}
	void DecreaseDateByXYear(short Years) {

		clsDate Date = DecreaseDateByXYear(Years, *this);
		cout << "Date after Decreasing " << Years << " Years(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByXYearsFaster(short Years, clsDate Date) {

		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByOneYear(short Years) {

		clsDate Date = DecreaseDateByXYearsFaster(Years, *this);
		cout << "Date after Decreasing " << Years << " Year(s) 'Faster way' : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date) {

		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade() {

		clsDate Date = DecreaseDateByOneDecade(*this);
		cout << "Date after Decreasing one Decade : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseByXDecade(short Decade, clsDate Date) {

		for (short i = 1; i <= Decade; i++) {

			Date = DecreaseDateByOneDecade(Date);
		}

		//another way.
		/*
		for (short i = 1; i <= Decade * 10; i++) {

			Date = SubstractingDateByOneYear(Date);
		}
		*/
		return Date;
	}
	void DecreaseByXDecade(short Decade) {

		clsDate Date = DecreaseByXDecade(Decade, *this);
		cout << "Date after Decreasing " << Decade << " Decade(s) : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseByXDecadeFaster(short Decade, clsDate Date) {

		Date.Year -= Decade * 10;
		return Date;
	}
	void DecreaseByXDecadeFaster(short Decade) {

		clsDate Date = DecreaseByXDecadeFaster(Decade, *this);
		cout << "Date after Decreasing " << Decade << " Decade(s) 'Faster way' : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseByOneCentury(clsDate Date) {

		Date.Year -= 100;
		return Date;
	}
	void DecreaseByOneCentury() {

		clsDate Date = DecreaseByOneCentury(*this);
		cout << "Date after Decreasing one Century : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static clsDate DecreaseByOneMillennium(clsDate Date) {

		Date.Year -= 1000;
		return Date;
	}
	void DecreaseByOneMillennium() {

		clsDate Date = DecreaseByOneMillennium(*this);
		cout << "Date after Decreasing one Millennium : " << Date.Day << "/ " << Date.Month << "/ " << Date.Year << endl;
	}

	static short DayOfWeekOrder(short Year, short Month, short Day) {

		short a, y, m;

		a = ((14 - Month) / 12);
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date) {

		return DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
	}
	short DayOfWeekOrder() {

		return DayOfWeekOrder(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {

		return DayOfWeekOrder(Date) == 6;
	}
	bool IsEndOfWeek() {

		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {

		//WeekEnds are Fri and Sat.
		short DayIndex = DayOfWeekOrder(Date);
		return (DayIndex == 5 || DayIndex == 6);
	}
	bool IsWeekEnd() {

		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date) {

		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay() {

		return IsBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date) {

		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilEndOfWeek() {

		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate Date) {

		clsDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDiffrenceDays(Date, EndOfMonthDate, true);
	}
	short DaysUntilEndOfMonth() {

		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate Date) {

		clsDate EndOfYearDate;

		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDiffrenceDays(Date, EndOfYearDate, true);
	}
	short DaysUntilEndOfYear() {

		return DaysUntilEndOfYear(*this);
	}

	static short CalculateMyAgeInDays(clsDate DateOfBirth) {

		return GetDiffrenceDays(DateOfBirth, GetSystemDate());
	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {

		short BusinessDays = 0;

		while (!IsDate1EqualDate2(DateFrom, DateTo)) {

			if (IsBusinessDay(DateFrom))
				BusinessDays++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return BusinessDays;
	}
	short CalculateBusinessDays(clsDate DateTo) {

		return CalculateBusinessDays(*this, DateTo);
	}

	//only business days counts as vacation days.
	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {

		short VacationDays = 0;

		while (!IsDate1EqualDate2(DateFrom, DateTo)) {

			if (IsBusinessDay(DateFrom))
				VacationDays++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return VacationDays;
	}
	short CalculateVacationDays(clsDate DateTo) {

		return CalculateVacationDays(*this, DateTo);
	}

	//only business days Discount from vacation duration.
	static clsDate ReturnDate(clsDate DateFrom, short VacationDaysNumber) {

		while (VacationDaysNumber > 0) {

			if (IsBusinessDay(DateFrom))
				VacationDaysNumber--;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		//if return date is a weekend we need to skip it.
		while (IsWeekEnd(DateFrom)) {

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}
	void ReturnDate(short VacationDaysNumber) {

		clsDate Date = ReturnDate(*this, VacationDaysNumber);
		cout << "Return Date : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
	}
	
	static bool IsValidDate(clsDate Date) {

		if (Date.Month > 12 || Date.Month < 1)
			return false;

		if (Date.Day > 31 || Date.Day < 1)
			return false;

		if (Date.Month == 2) {

			if (IsLeapYear(Date.Year)) {

				if (Date.Day > 29)
					return false;
			}
			else {

				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}
	bool IsValidDate() {

		return IsValidDate(*this);
	}

	static string ReplaceWordInString(string Str, string WordToReplace, string ReplaceTo) {

		short pos;

		while ((pos = Str.find(WordToReplace)) != Str.npos) {

			Str.replace(pos, WordToReplace.length(), ReplaceTo);
		}
		return Str;
	}
	static string SetDateFormat(clsDate Date, string DateFormat = "dd/mm/yyyy") {

		string NewDateFormat = "";

		NewDateFormat = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		NewDateFormat = ReplaceWordInString(NewDateFormat, "mm", to_string(Date.Month));
		NewDateFormat = ReplaceWordInString(NewDateFormat, "yyyy", to_string(Date.Year));

		return NewDateFormat;
	}
	string SetDateFormat(string DateFormat = "dd/mm/yyyy") {

		return SetDateFormat(*this, DateFormat);
	}

	static enum enCompareDates { Before = -1, Equal = 0, After = 1 };

	static enCompareDates CompareDates(clsDate Date, clsDate Date2) {

		if (IsDate1BeforeDate2(Date, Date2))
			return enCompareDates::Before;

		if (IsDate1EqualDate2(Date, Date2))
			return enCompareDates::Equal;

		return enCompareDates::After;
	}
	enCompareDates CompareDates(clsDate Date2) {

		return CompareDates(*this, Date2);
	}
};

