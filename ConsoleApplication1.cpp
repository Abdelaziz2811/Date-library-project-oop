#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

int main() {

	clsDate Date1;
	cout << "System Date through default constructor : [1] "; Date1.Print();

	clsDate Date2("12/3/2033");
	cout << "string Date (dd/mm/yyyy) through Parameterized constructor : [2] "; Date2.Print();

	clsDate Date3(25, 1, 2025);
	cout << "Date through Parameterized constructor that receives Dd and Mm and Yyyy as short : [3] "; Date3.Print();

	clsDate Date4(250, 2022);
	cout << "Date by order day through Parameterized constructor : [4] "; Date4.Print();

	/*Date1.PrintMonthCalender();

	Date2.PrintMonthCalender();

	Date3.PrintMonthCalender();

	Date4.PrintMonthCalender();*/

	cout << "---------------\n";

	cout << "Days from beginig of the year is : for date [4] : " << Date4.NumberOfDaysFromBeginningOfTheYear() << endl;

	cout << "---------------\n";

	cout << "For Date [1] : ";
	Date1.DateAfterAddDays(10);

	cout << "---------------\n";
	
	if (Date1.IsDate1BeforeDate2(Date2)){

		cout << "Yes Date ";
		Date1.Print();
		cout << "is before Date ";
		Date2.Print();
	}
	else {

		cout << "No Date ";
		Date1.Print(); 
		cout << "is Not before Date "; 
		Date2.Print();
	}

	cout << "---------------\n";

	if (Date1.IsDate1EqualDate2(Date3)) {

		cout << "Yes Date ";
		Date1.Print();
		cout << "and ";
		Date3.Print();
		cout << "Are equal\n";
	}
	else {

		cout << "No Date ";
		Date1.Print();
		cout << "and ";
		Date3.Print();
		cout << "Are Not equal\n";
	}

	cout << "---------------\n";

	if (Date1.IsLastDayInMonth()) {

		cout << "Yes, Day " << Date1.GetDay() << " wich is '" << Date1.DayName() << "' is the last Day in Month" << endl;
	}
	else {

		cout << "No, Day " << Date1.GetDay() << " wich is '" << Date1.DayName() << "' is Not the last Day in Month" << endl;
	}

	cout << "---------------\n";

	if (Date1.IsLastMonthInYear()) {

		cout << "Yes, Month " << Date1.GetMonth() << " wich is '" << Date1.MonthName() << "' is the last Month in Year" << endl;
	}
	else {

		cout << "No, Month " << Date1.GetMonth() << " wich is '" << Date1.MonthName() << "' is Not the last Month in Year" << endl;
	}

	cout << "---------------\n";

	cout << "For Date [1] : ";
	Date1.IncreaseDateByOneDay();

	cout << "---------------\n";

	cout << "Diff Days between Date : "; Date1.Print();
	cout << "and Date "; Date4.Print(); 

	//Date1 is not before date 4, so it will print 0. 
	cout << "is : " << Date1.GetDiffrenceDays(Date4, true) << endl;//true for including the end day.

	cout << "---------------\n";

	cout << "Diff Days between Date : "; Date4.Print();
	cout << "and Date "; Date1.Print();

	//Date 4 is before date 1, so it will print diff days. 
	cout << "is : " << Date4.GetDiffrenceDays(Date1, true) << endl;//true for including the end day.

	cout << "---------------\n";

	clsDate SDate = clsDate::GetSystemDate();
	cout << "System Date : " << SDate.GetDay() << "/" << SDate.GetMonth() << "/" << SDate.GetYear() << endl;

	cout << "---------------\n";

	cout << "Diff Days between Date : "; Date1.Print();
	cout << "and Date "; Date4.Print();

	//We used swap technique with multiply Diff Days on -1, so resul will be negative even if Date1 is not before date 4.
	cout << "is : " << Date1.GetDiffrenceInDays(Date4, true) << endl;//true for including the end day.

	cout << "---------------\n";

	Date1.IncreaseDateByXDays(10);

	cout << "---------------\n";

	Date1.IncreaseDateByOneWeek();

	cout << "---------------\n";

	Date1.IncreaseDateByXWeeks(2);

	cout << "---------------\n";

	Date1.IncreaseDateByOneMonth();

	cout << "---------------\n";

	Date1.IncreaseDateByXMonth(2);

	cout << "---------------\n";

	Date1.IncreaseDateByOneYear();

	cout << "---------------\n";

	Date1.IncreaseDateByXYears(5);

	cout << "---------------\n";

	Date1.IncreaseDateByOneDecade();

	cout << "---------------\n";

	Date1.IncreaseByXDecade(5);

	cout << "---------------\n";

	Date1.IncreaseByXDecadeFaster(5);

	cout << "---------------\n";

	Date1.IncreaseByOneCentury();

	cout << "---------------\n";

	Date1.IncreaseByOneMillennium();

	cout << "---------------\n";

	Date1.DecreaseDateByOneDay();

	cout << "---------------\n";

	Date1.DecreaseDateByXDays(10);

	cout << "---------------\n";

	Date1.DecreaseDateByOneWeek();

	cout << "---------------\n";

	Date1.DecreaseDateByXWeeks(2);

	cout << "---------------\n";

	Date1.DecreaseDateByOneMonth();

	cout << "---------------\n";

	Date1.DecreaseDateByXMonth(4);

	cout << "---------------\n";

	Date1.DecreaseDateByOneYear();

	cout << "---------------\n";

	Date1.DecreaseDateByXYear(2);

	cout << "---------------\n";

	Date1.DecreaseDateByOneYear(4);

	cout << "---------------\n";

	Date1.DecreaseDateByOneDecade();

	cout << "---------------\n";

	Date1.DecreaseByXDecade(5);

	cout << "---------------\n";

	Date1.DecreaseByXDecadeFaster(5);

	cout << "---------------\n";

	Date1.DecreaseByOneCentury();

	cout << "---------------\n";

	Date1.DecreaseByOneMillennium();

	cout << "---------------\n";

	cout << "Day " << Date1.GetDay() << " wich is '" << Date1.DayName() 
		<< "' and its order in week is : " << Date1.DayOfWeekOrder() << endl;

	cout << "---------------\n";

	if (Date1.IsEndOfWeek())
		cout << "It is End of Week" << endl;
	else 
		cout << "It is Not End of Week" << endl;

	cout << "---------------\n";

	if (Date1.IsWeekEnd())
		cout << "It is WeekEnd" << endl;
	else
		cout << "It is Not WeekEnd" << endl;

	cout << "---------------\n";

	cout << "---------------\n";

	if (Date1.IsBusinessDay())
		cout << "It is a Business Day" << endl;
	else
		cout << "It is Not a Business Day" << endl;

	cout << "---------------\n";

	cout << "Days until End Of Week : " << Date1.DaysUntilEndOfWeek() << endl;

	cout << "---------------\n";

	cout << "Days until End Of Month : " << Date1.DaysUntilEndOfMonth() << endl;

	cout << "---------------\n";

	cout << "Days until End Of Year : " << Date1.DaysUntilEndOfYear() << endl;

	cout << "---------------\n";

	//only business days counts as vacation days.
	cout << "Vacation days between two dates -> (Date1 To Date3) : " << Date1.CalculateVacationDays(Date3) << endl;

	cout << "---------------\n";

	//only business days Discount from vacation duration.
	Date1.ReturnDate(8);

	cout << "---------------\n";

	if (Date1.IsValidDate())
		cout << "Date : " << Date1.GetDay() << "/" << Date1.GetMonth() << "/" << Date1.GetYear() << " is a Valid Date\n";
	else 
		cout << "Date : " << Date1.GetDay() << "/" << Date1.GetMonth() << "/" << Date1.GetYear() << " is Not a Valid Date\n";

	cout << "---------------\n";

	cout << "Date Format [dd.mm.yyyy] : " << Date1.SetDateFormat("dd.mm.yyyy") << endl;
	cout << "Date Format [dd-mm-yyyy] : " << Date1.SetDateFormat("dd-mm-yyyy") << endl;
	cout << "Date Format [dd/:-)/mm/:-)/yyyy] : " << Date1.SetDateFormat("dd/:-)/mm/:-)/yyyy") << endl;

	cout << "---------------\n";

	return 0;
}

