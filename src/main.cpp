// C++ File for main

#include <iostream>

#ifndef dout
#  define dout debug && std::cout
#endif

constexpr int NRows = 9;
constexpr int NColumns = 9;
constexpr int NItems = NRows * NColumns;

constexpr int NBlockRows = 3;
constexpr int NBlockColumns = 3;

constexpr unsigned int CSum = ( NRows * ( NRows + 1 ) )/2;

bool check_rows_and_cols( const unsigned int vals[][NColumns], const bool& debug = false ) {
   int rchecksum = CSum;
   int cchecksum = CSum;
   for( int rindex = 0; rindex < NColumns; ++rindex ) {
      cchecksum = CSum;
      rchecksum = CSum;
      for( int cindex = 0; cindex < NRows; ++cindex ) {
         if ( (vals[rindex][cindex] == 0) || (vals[cindex][rindex] == 0) ) {
            return false;
         }
         rchecksum -= (int)vals[rindex][cindex];
         cchecksum -= (int)vals[cindex][rindex];
         dout << __func__ << "(): Row check: vals[" << rindex << "][" << cindex << "] = " << vals[rindex][cindex] << "\n"; 
         dout << __func__ << "(): Column check: vals[" << cindex << "][" << rindex << "] = " << vals[rindex][cindex] << "\n"; 
         dout << __func__ << "(): row checksum is " << rchecksum << "\n";
         dout << __func__ << "(): col checksum is " << cchecksum << "\n";
      }
      dout << "\n";
   }
   return ((rchecksum == 0) && (cchecksum == 0));
}


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

bool check_row_and_col_blocks( const unsigned int board[][NColumns], const bool& debug = false ) {
   for( int brow_num = 0; brow_num < NBlockRows; ++brow_num ) {
      for( int bcol_num = 0; bcol_num < NBlockColumns; ++bcol_num ) {
         if ( !check_region( CSum, board, 3, 3, brow_num * NBlockColumns, bcol_num * NBlockRows, debug ) ) {
            std::cout << __func__ << "(): Invalid solution due to block row " << brow_num 
               << ", block column " << bcol_num << "\n"; 
            return false;
         }
      } // for( int bcol_num = 0; bcol_num < NBlockRows; ++bcol_num ) {
   } // for( int brow_num = 0; brow_num < NBlockColumns; ++brow_num ) {

   return true;
}


bool validSolution( unsigned int board[9][9] ) {

   if ( !check_rows_and_cols( board ) ) {
      return false;
   }
   
   if ( !check_row_and_col_blocks( board ) ) {
      return false;
   }
      
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
   
   unsigned int invalid_vals[NRows][NColumns] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, 
      {6, 7, 2, 1, 9, 0, 3, 4, 8},
      {1, 0, 0, 3, 4, 2, 5, 6, 0},
      {8, 5, 9, 7, 6, 1, 0, 2, 0},
      {4, 2, 6, 8, 5, 3, 7, 9, 1},
      {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 0, 1, 5, 3, 7, 2, 1, 4},
      {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 0, 0, 4, 8, 1, 1, 7, 9}
   };

   if ( validSolution( invalid_vals ) ) {
      std::cout << "Sodoku solution 'invalid_vals' is valid\n"; 
      std::cout << "This is NOT expected\n"; 
   } else {
      std::cout << "Sodoku solution 'invalid_vals' is NOT valid\n"; 
      std::cout << "This is expected\n"; 
   }

   return EXIT_SUCCESS;

}

