#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsPeriod
{
public:
	clsDate StartDate;
	clsDate EndDate;

	clsPeriod(clsDate StartDate, clsDate EndDate) {

		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}

	void SetStartDate(clsDate StartDate) {

		this->StartDate = StartDate;
	}
	clsDate GetStartDate() {

		return StartDate;
	}

	void SetEndDate(clsDate EndDate) {

		this->EndDate = EndDate;
	}
	clsDate GetEndDate() {

		return StartDate;
	}

	void Print() {

		cout << "Period Start : ";
		StartDate.Print();
		cout << "Period End : ";
		EndDate.Print();
	}

	static bool IsOverLapPeriod(clsPeriod Period1, clsPeriod Period2) {

		if (
			clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enCompareDates::Before
			||
			clsDate::CompareDates(Period2.StartDate, Period1.EndDate) == clsDate::enCompareDates::After
			)
			return false;
		else {

			return true;
		}
	}
	bool IsOverLapPeriod(clsPeriod Period2) {

		return IsOverLapPeriod(*this, Period2);
	}

	static short PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false) {

		return clsDate::GetDiffrenceDays(Period.StartDate, Period.EndDate, IncludeEndDay);
	}
	short PeriodLengthInDays(bool IncludeEndDay = false) {

		return PeriodLengthInDays(*this, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsPeriod Period, clsDate Date) {

		return !(clsDate::CompareDates(Date, Period.StartDate) == clsDate::enCompareDates::Before
			||
			clsDate::CompareDates(Date, Period.EndDate) == clsDate::enCompareDates::After);
	}
	bool IsDateWithinPeriod(clsDate Date) {

		return IsDateWithinPeriod(*this, Date);
	}

	static short CountOvelapDays(clsPeriod Period1, clsPeriod Period2) {

		if (!IsOverLapPeriod(Period1, Period2))
			return 0;

		short Period1Length = PeriodLengthInDays(Period1, true);
		short Period2Length = PeriodLengthInDays(Period2, true);
		short OverLapDays = 0;

		if (Period1Length < Period2Length) {

			while (!clsDate::IsDate1EqualDate2(Period1.StartDate, Period1.EndDate)) {

				if (IsDateWithinPeriod(Period2, Period1.StartDate))
					OverLapDays++;

				Period1.StartDate = clsDate::IncreaseDateByOneDay(Period1.StartDate);
			}
		}
		else {

			while (!clsDate::IsDate1EqualDate2(Period2.StartDate, Period2.EndDate)) {

				if (IsDateWithinPeriod(Period1, Period2.StartDate))
					OverLapDays++;

				Period2.StartDate = clsDate::IncreaseDateByOneDay(Period2.StartDate);
			}
		}
		return OverLapDays;
	}
	short CountOvelapDays(clsPeriod Period2) {

		return CountOvelapDays(*this, Period2);
	}

};

