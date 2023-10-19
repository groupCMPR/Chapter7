#include "Queen.h"

//default constructor
Queen::Queen() {
	size = 0;
}

//---------------------------------------------------------------------
//							MUTATORS
//---------------------------------------------------------------------
//Precondition: int newSize
//Postcondition: set size of board (sizexsize)
void Queen::set_Size(const int& newSize) {
	size = newSize;
}

//Precondition: int column
//Postcondition: set first line of stack board
void Queen::set_Line(const int& column) {
	for (int i = 0; i < size; ++i) {
		if (i == (column))
			board.push('Q');
		else
			board.push('_');
	}

}

//Precondition: board is not empty (use set_Line), size is not 2 or 3
//Postcondition: fill board_Numberxboard_Number with n queens solution 
void Queen::set_Board() {

	bool column_check = false; //end of column, used to check if column is empty

	for (int iter = size; iter < (size * size); ++iter) {
		//if end of column, will see if there is a Q later
		if ((iter + 1) % size == 0) {
			column_check = true;
		}

		//used to test queens in same territory, success is true if there are no queens there
		int pos_check = iter - size;
		bool success = true, dia_left_bound = true, dia_right_bound = true;
		
		board.push('_'); //placeholder to allow boundary check 

		//territory check
		for (int i = 1; pos_check > -1; ++i) {

			//vertical  (from current position)
			if (board._Get_container().at(pos_check) == 'Q') {
				success = false;
				break;
			}

			//diagonal right (from current position), stops when it is at most right direction
			if (dia_right_bound) {
				if ((pos_check + i) % size == 0 || (iter + 1) % size == 0)
					dia_right_bound = false;
				else if (board._Get_container().at(pos_check + i) == 'Q') {
					success = false;
					break;
				}
			}

			//diagonal left (from current position), , stops when it is at most left direction
			if (dia_left_bound) {
				if ((pos_check - i) % size == (size - 1) || iter % size == 0 || (pos_check - i) < 0)
					dia_left_bound = false;
				else if (board._Get_container().at(pos_check - i) == 'Q') {
					success = false;
					break;
				}
			}
			pos_check -= size;
		}

		if (success) {
			board.pop();
			board.push('Q');

			//pushes in _ for remainder of line
			for (int i = iter; iter < i + (size - (i % size)) - 1; ++iter)
				board.push('_');

			column_check = false;
		}
		else if (column_check) {

			//pops until Q, or if there is a Q in the last column, erases inot next Q
			for (--iter; iter > -1; --iter) {
				board.pop();
				if (board._Get_container().at(iter) == 'Q') {
					if ((iter + 1) % size != 0)
						break;
				}
			}

			//if popped the top row, refills line
			if (iter < size) {
				//pops '_' if there was a Q in the last column of top rown
				// else pops 'Q' 
				board.pop();

				//moves Q over to next spot
				if (iter != -1) {
					board.pop();
					board.push('_');
				}
				board.push('Q');

				//refills top line
				for (++iter; iter < size - 1; ++iter) {
					board.push('_');
				}
			}
			else {
				board.pop();
				board.push('_');
			}

			column_check = false; 

		}
	}
}


//---------------------------------------------------------------------
//							ACCESSORS
//---------------------------------------------------------------------

//Precondition: class Queen, outstream
//Postcondition: displays all elements in stack of Queen
ostream& operator<< (ostream& out, const Queen& obj) {
	out << "\n\t" << obj.size << "-Queens";
	int i = 1;
	//displays menu
	//top of board:
	out << "\n\t" << char(201) << string((obj.size * 2 - 1), char(205)) << char(187) << "\n\t";

	//middle of board:
	for (auto iter = obj.board._Get_container().begin(); iter != obj.board._Get_container().end(); ++iter, ++i) {

		if (i == 1 || i % obj.size == 1)
			cout << char(186);

		out << *iter;

		if (i % obj.size == 0)
			out << char(186) << "\n\t";
		else
			out << char(179);

	}

	//end of board:
	out << char(200) << string((obj.size * 2 - 1), char(205)) << char(188);

	return out;
}

