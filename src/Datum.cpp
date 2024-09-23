#include <iostream>
#include <string>
#include "Datum.h"

// Initialisera statisk medlem
// (första elementet används inte i denna lösning!)
const std::array< unsigned int, 13 > Datum::ANT_DAGAR_PER_MAANAD = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

// Konstruktor
Datum::Datum() : year(2000), month(1), day(1){
}

// Konstruktor
Datum::Datum( int year, int month, int day  )
{
  set_date( year, month, day);
}

void Datum::set_date( int yy, int mm, int dd )
{
  // Glöm inte att kontrollera inmatade värden, annars "exception"
  year = yy;
  month = mm;
  day = dd;
}

// Denna medlemsfunktion är tänkt att lägga till 1 dag till befintligt datum.
// Om sista dagen i månaden, så byt månad.
//     Om skottår, så ta hänsyn till att februari(månad 2) har 29 dagar.
// Om sista dagen på året, så byt år.
void Datum::step_one_day()
{
  // Dagen är inte sista dagen i månaden!
  if ( !end_of_month( day ) )
    ++day;
  else
    if ( month < 12 )
    {
      ++month;
      day = 1;
    }
    else
    {
      ++year;
      month = 1;
      day = 1;
    }
}

// Returnera true om yy(year) är skottår!
bool Datum::is_skott_aar( int yy )
{
  if ( yy % 400 == 0 ||
      ( yy % 100 != 0 && yy % 4 == 0 ) )
    return true;
  else
    return false;
}

// Är det sista dagen (dd) i månaden?
bool Datum::end_of_month( int dd ) const
{
  if ( month == 2 && is_skott_aar( year ) )
    return dd == 29;
  else
    return dd == ANT_DAGAR_PER_MAANAD[ month ];
}

int Datum::getYear() const{
  return year;
}

int Datum::getMonth() const{
  return month;
}

int Datum::getDay() const{
  return day;
}

// operator<<
std::ostream &operator<<( std::ostream &output, const Datum &d )
{
  // OBS. Glöm inte att modifiera vad som skrivs ut!
  //output << d.year << '-' << d.month << '-' << d.day;
  output << d.day << ' ' << d.months[d.month - 1] << ' ' << d.year;
  return output;
}

// operator+=
const Datum& Datum::operator+=(int i){
  if(end_of_month(day)){
    month += 1;
    day = 1;
  }
  //Borde inte else tas bort? 
  //Nu får nästa månad alltid dag = 1 även om antal dagar ökar mer än så.
  else{
    day += i;
  }
  return *this;
}

// operator+
const Datum Datum::operator+(int i) const{
  Datum tmp(*this);
  tmp.day += i;
  return tmp;
}

// operator++ Prefix
const Datum& Datum::operator++(){
  *this += 1;
  return *this;
}

// operator++ Postfix
const Datum Datum::operator++(int){
  Datum tmp(*this);
  *this += 1;
  return tmp;
}

// operator<
bool operator<(const Datum& left, const Datum& right){
  if(left.getYear() < right.getYear()){
    return true;
  }
  else if(left.getYear() == right.getYear()){
    // Jämför månad om vänster och höger har samma år.
    if(left.getMonth() < right.getMonth()){
      return true;
    }
    else if(left.getMonth() == right.getMonth()){
      // Jämför dag om vänster och höger har samma år och månad.
      if(left.getDay() < right.getDay()){
        return true;
      }
    }
  }
  return false;
}
