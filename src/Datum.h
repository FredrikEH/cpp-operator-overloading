//Fredrik Haupt caha6864

// Labb3, Datum.h – klassdefinition

#ifndef DATUM_H
#define DATUM_H

#include <array>
#include <string>
#include <iostream>

class Datum
{
  friend std::ostream &operator<<( std::ostream &, const Datum & );
  
  unsigned int year;
  unsigned int month;
  unsigned int day;
  
  // Deklaration av statisk privat medlem, "ant_dagar per månad"
  static const std::array< unsigned int, 13 > ANT_DAGAR_PER_MAANAD;
  //void step_one_day(); // Öka datum med en dag

public:
  Datum();
  Datum( int, int, int );
  void set_date( int, int, int ); // set year, month, day
  const char* months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  int getYear() const;
  int getMonth() const;
  int getDay() const;

  //OBS. funktionen "step_one_day()" bör vara PRIVATE
  //Är kommentaren ovan en instruktion eller en upplysning?
  void step_one_day(); // Öka datum med en dag
  static bool is_skott_aar( int ); // Är det skottår?
  bool end_of_month( int ) const; // Är dagen den sista i månaden?
  
  //operatoröverlagringar
  const Datum& operator+=(int i); // operator+=
  const Datum operator+(int i) const; // operator+
  const Datum& operator++(); // operator++ Prefix
  const Datum operator++(int); // operator++ Postfix
};

// operator+ med inline för att hantera addition med siffror innan Datum
inline const Datum operator+(int left, const Datum& right) {
	return right + left;
}

// operatoröverlagring av booleska uttryck
bool operator<(const Datum& left, const Datum& right);

inline bool operator==(const Datum& left, const Datum& right) {
	return !(left < right) && !(right < left);
}

inline bool operator!=(const Datum& left, const Datum& right) {
	return !(left == right);
}

inline bool operator<=(const Datum& left, const Datum& right) {
	return !(right < left);
}

// uppgiften verkade inte kolla efter >=
inline bool operator>=(const Datum& left, const Datum& right) {
	return !(left < right);
}

inline bool operator>(const Datum& left, const Datum& right) {
	return right < left;
}

#endif

