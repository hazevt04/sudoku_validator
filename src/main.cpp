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

constexpr int RegionSize = 9;

constexpr unsigned int CSum = ( NRows * ( NRows + 1 ) )/2;

bool check_rows_and_cols( const unsigned int vals[][NColumns], const bool& debug = false ) {
   int rchecksum = CSum;
   int cchecksum = CSum;
   for( int rindex = 0; rindex < NColumns; ++rindex ) {
      cchecksum = CSum;
      rchecksum = CSum;
      for( int cindex = 0; cindex < NRows; ++cindex ) {
         dout << __func__ << "(): Row check: vals[" << rindex << "][" << cindex << "] = " << vals[rindex][cindex] << "\n"; 
         dout << __func__ << "(): Column check: vals[" << cindex << "][" << rindex << "] = " << vals[cindex][rindex] << "\n"; 
         if ( (vals[rindex][cindex] == 0) || (vals[cindex][rindex] == 0) ) {
            if ( debug ) {
               if ( vals[rindex][cindex] == 0 ) {
                  std::cout << __func__ << "(): Validation failed due to zero value in row check\n";
               } else {
                  std::cout << __func__ << "(): Validation failed due to zero value in column check\n";
               }
            }
            return false;
         }
         rchecksum -= (int)vals[rindex][cindex];
         cchecksum -= (int)vals[cindex][rindex];
         dout << __func__ << "(): row checksum is " << rchecksum << "\n";
         dout << __func__ << "(): col checksum is " << cchecksum << "\n";
      }
      dout << "\n";
   }
   return ((rchecksum == 0) && (cchecksum == 0));
}


bool check_region( const unsigned int region[][NColumns],
      const int& start_row, const int& start_col, 
      const int& row_size, const int& col_size, 
      const bool& debug = false ) {

   int max_col = start_col + row_size;
   int max_row = start_row + col_size;
   int checksum = CSum;
   for( int rindex = start_row; rindex < max_row; ++rindex ) {
      for( int cindex = start_col; cindex < max_col; ++cindex ) {

         if (region[rindex][cindex] == 0) return false;
         dout << __func__ << "(): [" << rindex << "][" << cindex << "]: "
            << region[rindex][cindex] << "\n";
         checksum -= (int)region[rindex][cindex];
         dout << __func__ << "():\tchecksum became " << checksum << "\n";

      }
   }
   dout << "\n";

   return ( checksum == 0 );
}


bool check_regions( const unsigned int board[][NColumns],
      const int& row_size, const int& col_size, 
      const bool& debug = false ) {

   int checksums[RegionSize];
   for( int index = 0; index < RegionSize; ++index ) {
      checksums[index] = CSum; 
   } 

   // Pass 0
   checksum[0] -= board[0][0];
   checksum[1] -= board[0][3];
   checksum[2] -= board[0][6];
   checksum[3] -= board[3][0];
   checksum[4] -= board[3][3];
   checksum[5] -= board[3][6];
   checksum[6] -= board[6][0];
   checksum[7] -= board[6][3];
   checksum[8] -= board[6][6];
   
   // Pass 1, increment column
   checksum[0] -= board[0][1];
   checksum[1] -= board[0][4];
   checksum[2] -= board[0][7];
   checksum[3] -= board[3][1];
   checksum[4] -= board[3][4];
   checksum[5] -= board[3][7];
   checksum[6] -= board[6][1];
   checksum[7] -= board[6][4];
   checksum[8] -= board[6][7];
   
   // Pass 2, increment column
   checksum[0] -= board[0][2];
   checksum[1] -= board[0][5];
   checksum[2] -= board[0][8];
   checksum[3] -= board[3][2];
   checksum[4] -= board[3][5];
   checksum[5] -= board[3][8];
   checksum[6] -= board[6][2];
   checksum[7] -= board[6][5];
   checksum[8] -= board[6][8];
   
   // Pass 3, use Pass 0 column values, but increment row
   checksum[0] -= board[1][0];
   checksum[1] -= board[1][3];
   checksum[2] -= board[1][6];
   checksum[3] -= board[4][0];
   checksum[4] -= board[4][3];
   checksum[5] -= board[4][6];
   checksum[6] -= board[7][0];
   checksum[7] -= board[7][3];
   checksum[8] -= board[7][6];
   
   // Pass 4, increment column
   checksum[0] -= board[1][1];
   checksum[1] -= board[1][4];
   checksum[2] -= board[1][7];
   checksum[3] -= board[4][1];
   checksum[4] -= board[4][4];
   checksum[5] -= board[4][7];
   checksum[6] -= board[7][1];
   checksum[7] -= board[7][4];
   checksum[8] -= board[7][7];
   
   // Pass 5, increment column
   checksum[0] -= board[1][2];
   checksum[1] -= board[1][5];
   checksum[2] -= board[1][8];
   checksum[3] -= board[4][2];
   checksum[4] -= board[4][5];
   checksum[5] -= board[4][8];
   checksum[6] -= board[7][2];
   checksum[7] -= board[7][5];
   checksum[8] -= board[7][8];

   // Pass 6, use Pass 3 column values, but increment row
   checksum[0] -= board[2][0];
   checksum[1] -= board[2][3];
   checksum[2] -= board[2][6];
   checksum[3] -= board[5][0];
   checksum[4] -= board[5][3];
   checksum[5] -= board[5][6];
   checksum[6] -= board[8][0];
   checksum[7] -= board[8][3];
   checksum[8] -= board[8][6];

   // Pass 7, increment column
   checksum[0] -= board[2][1];
   checksum[1] -= board[2][4];
   checksum[2] -= board[2][7];
   checksum[3] -= board[5][1];
   checksum[4] -= board[5][4];
   checksum[5] -= board[5][7];
   checksum[6] -= board[8][1];
   checksum[7] -= board[8][4];
   checksum[8] -= board[8][7];

   // Pass 8, increment column
   checksum[0] -= board[2][2];
   checksum[1] -= board[2][5];
   checksum[2] -= board[2][8];
   checksum[3] -= board[5][2];
   checksum[4] -= board[5][5];
   checksum[5] -= board[5][8];
   checksum[6] -= board[8][2];
   checksum[7] -= board[8][5];
   checksum[8] -= board[8][8];

} 
} 



bool check_row_and_col_blocks( const unsigned int board[][NColumns], const bool& debug = false ) {
   for( int brow_num = 0; brow_num < NBlockRows; ++brow_num ) {
      for( int bcol_num = 0; bcol_num < NBlockColumns; ++bcol_num ) {
         if ( !check_region( board, brow_num * NBlockColumns, bcol_num * NBlockRows, NBlockColumns, NBlockRows, debug ) ) {
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

constexpr int NBoards = 2;

int main( int argc, char** argv ) {

   unsigned int boards[NBoards][NRows][NColumns] = {
      {
         {5, 3, 4, 6, 7, 8, 9, 1, 2},
         {6, 7, 2, 1, 9, 5, 3, 4, 8},
         {1, 9, 8, 3, 4, 2, 5, 6, 7},
         {8, 5, 9, 7, 6, 1, 4, 2, 3},
         {4, 2, 6, 8, 5, 3, 7, 9, 1},
         {7, 1, 3, 9, 2, 4, 8, 5, 6},
         {9, 6, 1, 5, 3, 7, 2, 8, 4},
         {2, 8, 7, 4, 1, 9, 6, 3, 5},
         {3, 4, 5, 2, 8, 6, 1, 7, 9}    
      },
      {
         {5, 3, 4, 6, 7, 8, 9, 1, 2}, 
         {6, 7, 2, 1, 9, 0, 3, 4, 8},
         {1, 0, 0, 3, 4, 2, 5, 6, 0},
         {8, 5, 9, 7, 6, 1, 0, 2, 0},
         {4, 2, 6, 8, 5, 3, 7, 9, 1},
         {7, 1, 3, 9, 2, 4, 8, 5, 6},
         {9, 0, 1, 5, 3, 7, 2, 1, 4},
         {2, 8, 7, 4, 1, 9, 6, 3, 5},
         {3, 0, 0, 4, 8, 1, 1, 7, 9}
      } };
 
   for( int index = 0; index < NBoards; ++index ) {
      if ( validSolution( boards[index] ) ) {
         std::cout << "Sodoku solution for board " << index << " is valid\n"; 
      } else {
         std::cout << "Sodoku solution for board " << index << " is NOT valid\n"; 
      }
   } 

   return EXIT_SUCCESS;

}

