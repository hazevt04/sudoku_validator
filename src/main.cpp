// C++ File for main

#include "my_utils.hpp"

constexpr int NRows = 9;
constexpr int NColumns = 9;
constexpr int NItems = NRows * NColumns;

constexpr int NBlockRows = 3;
constexpr int NBlockColumns = 3;

constexpr unsigned int CSum = ( NRows * ( NRows + 1 ) )/2;

bool check_region( int check_sum, const unsigned int region[][NColumns],
      const int& row_size, const int& col_size, 
      const int& start_row, const int& start_col, const bool& debug = false ) {

   int max_col = start_col + row_size;
   int max_row = start_row + col_size;
   for( int rindex = start_row; rindex < max_row; ++rindex ) {
      for( int cindex = start_col; cindex < max_col; ++cindex ) {

         if (region[rindex][cindex] == 0) return false;
         dout << __func__ << "(): [" << rindex << "][" << cindex << "]: "
            << region[rindex][cindex] << "\n";
         check_sum -= (int)region[rindex][cindex];
         dout << __func__ << "():\tcheck_sum became " << check_sum << "\n";

      }
   }
   dout << "\n";

   return ( check_sum == 0 );
}


bool validSolution( unsigned int board[9][9] ) {

   for( int row_num = 0; row_num < NRows; ++row_num ) {
      if ( !check_region( CSum, board, 9, 1, row_num, 0 ) ) {
         std::cout << __func__ << "(): Invalid solution due to row " << row_num << "\n"; 
         return false;
      }
   } 
   
   for( int col_num = 0; col_num < NColumns; ++col_num ) {
      if ( !check_region( CSum, board, 1, 9, 0, col_num ) ) {
         std::cout << __func__ << "(): Invalid solution due to column " << col_num << "\n"; 
         return false;
      }
   } 
   
   for( int brow_num = 0; brow_num < NBlockRows; ++brow_num ) {
      for( int bcol_num = 0; bcol_num < NBlockColumns; ++bcol_num ) {
         if ( !check_region( CSum, board, 3, 3, brow_num * NBlockColumns, bcol_num * NBlockRows ) ) {
            std::cout << __func__ << "(): Invalid solution due to block row " << brow_num 
               << ", block column " << bcol_num << "\n"; 
            return false;
         }
      } // for( int bcol_num = 0; bcol_num < NBlockRows; ++bcol_num ) {
   } // for( int brow_num = 0; brow_num < NBlockColumns; ++brow_num ) {
   return true;
}

int main( int argc, char** argv ) {

   unsigned int valid_vals[NRows][NColumns] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2},
      {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7},
      {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1},
      {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4},
      {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9}    
   };
 
   if ( validSolution( valid_vals ) ) {
      std::cout << "Sodoku solution 'valid_vals' is valid\n"; 
   } else {
      std::cout << "Sodoku solution 'valid_vals' is NOT valid\n"; 
   }

   return EXIT_SUCCESS;

}

