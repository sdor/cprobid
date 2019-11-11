/*
Program       : cprobid
Author        : Sergey Doronin <sdoronin@notes.cc.sunysb.edu>

Copyright (C) 2007 Sergey Doronin

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Sergey Doronin
Stony Brook University
Nicolls Rd.
Stony Brook, NY  11790  USA
sdoronin@notes.cc.sunysb.edu

*/

#ifndef PROTEIN_DATABASE_H_
#define PROTEIN_DATABASE_H_
#include <string>
using namespace std;

class protein_database
{
	string name;
	int database_type;
public:

	enum {
		FASTA_FILE,
		SQL_TABLE,
		UNKNOWN_DATABASE_TYPE
	};

	protein_database();
	virtual ~protein_database();
	void set_name(string name){this->name=name;}
	string get_name() const {return this->name;}
	void set_database_type(int database_type){this->database_type=database_type;}
	int get_database_type() const {return this->database_type;}

	protein_database& operator = (const protein_database& database){
		this->set_name(database.get_name());
		this->set_database_type(database.get_database_type());
		return *this;
	}
};

#endif /*PROTEIN_DATABASE_H_*/
