// C++ File for main

//#include <iostream>
//#include <algorithm>
#include "my_utils.hpp"

constexpr int NRows = 9;
constexpr int NColumns = 9;
constexpr int NItems = NRows * NColumns;

constexpr int NBlockRows = 3;
constexpr int NBlockColumns = 3;

constexpr int CSum = ( NRows * ( NRows + 1 ) )/2;

void sort_subset( unsigned int* sorted, const unsigned int* vals, const int& start_index,
      const int& num_to_sort, const bool& debug = false ) {
   try {
      if (!vals) {
         throw std::runtime_error( "vals is nullptr." );
      }
      if (!sorted) {
         throw std::runtime_error( "sorted is nullptr." );
      }
      
      std::copy( vals + start_index, vals + start_index + num_to_sort, sorted );

      if ( debug ) {
         print_vals<unsigned int>( sorted, num_to_sort, "Before sorting ", ", ", "" );
         std::cout << "\n"; 
      }

      std::sort( sorted, sorted + num_to_sort );
      
      if ( debug ) {
         print_vals<unsigned int>( sorted, num_to_sort, "Sorted ", ", ", "" );
         std::cout << "\n"; 
      }

   } catch ( std::exception& ex ) {
      throw std::runtime_error( std::string{__func__} + "(): " + ex.what() );
   }

}


void flatten_by_nrows( unsigned int* flattened_vals, const unsigned int vals[][NColumns], 
      const int& num_rows, const bool& debug = false ) {

   try {
      if (!flattened_vals) {
         throw std::runtime_error( "flattened_vals is nullptr." );
      }

      if ( debug ) {
         for( int row_index = 0; row_index < num_rows; ++row_index ) {
            print_vals<unsigned int>( &(vals[row_index][0]), NColumns, "Vals ", ", ", "" );
         } 
         std::cout << "\n"; 
      }
      
      for( int row_index = 0; row_index < NRows; ++row_index ) {
         //std::copy( vals[row_index], vals[row_index] + NColumns, &(flattened_vals[row_index * 9]) );
         for( int col_index = 0; col_index < NColumns; ++col_index ) {
            flattened_vals[row_index * NColumns + col_index] = vals[row_index][col_index];
         } 
      }

      if ( debug ) {
         print_vals<unsigned int>( &(flattened_vals[0]), num_rows * 9, "Flattened Vals ", ", ", "" );
         std::cout << "\n";
      }

   } catch ( std::exception& ex ) {
      throw std::runtime_error( std::string{__func__} + "(): " + ex.what() );
   }

}

bool check_vals( int check_sum, const int vals[][NColumns],
      const int& row_size, const int& col_size, 
      const int& start_row, const int& start_col, const bool& debug ) {

   int max_col = start_col + row_size;
   int max_row = start_row + col_size;
   for( int rindex = start_row; rindex < max_row; ++rindex ) {
      for( int cindex = start_col; cindex < max_col; ++cindex ) {

         if (vals[rindex][cindex] == 0) return false;
         dout << __func__ << "(): [" << rindex << "][" << cindex << "]: "
            << vals[rindex][cindex] << "\n";
         check_sum -= vals[rindex][cindex];
         dout << __func__ << "():\tcheck_sum became " << check_sum << "\n";

      }
   }
   dout << "\n";

   return ( check_sum == 0 );
}

int main( int argc, char** argv ) {
   try {
      
      int vals[NRows][NColumns] = {
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
      bool debug = true;
      
      for( int row_num = 0; row_num < NColumns; ++row_num ) {
         if ( !check_vals( CSum, vals, 9, 1, row_num, 0, debug ) ) {
            throw std::runtime_error( "Invalid solution due to row " + std::to_string(row_num) );
         }
      } 
      
      for( int col_num = 0; col_num < NRows; ++col_num ) {
         if ( !check_vals( CSum, vals, 1, 9, 0, col_num, debug ) ) {
            throw std::runtime_error( "Invalid solution due to column " + std::to_string(col_num) );
         }
      } 
      
      for( int brow_num = 0; brow_num < NBlockColumns; ++brow_num ) {
         for( int bcol_num = 0; bcol_num < NBlockRows; ++bcol_num ) {
            if ( !check_vals( CSum, vals, 3, 3, brow_num * NBlockColumns, bcol_num * NBlockRows, debug ) ) {
               throw std::runtime_error( "Invalid solution due to block row " + std::to_string(brow_num) 
                  + ", block column " + std::to_string(bcol_num) );
            }
         }
      } 

      std::cout << "Sodoku solution is valid\n"; 
      
      return EXIT_SUCCESS;

   } catch ( std::exception& ex ) {
      std::cout << "ERROR: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}

