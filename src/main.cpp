// C++ File for main

//#include <iostream>
//#include <algorithm>
#include "my_utils.hpp"

constexpr int NRows = 4;
constexpr int NColumns = 9;
constexpr int NItems = NRows * NColumns;

void sort_subset( unsigned int* sorted, const unsigned int* vals, const int& num_to_sort, const bool& debug = false ) {
   try {
      if (!vals) {
         throw std::runtime_error( "vals is nullptr." );
      }
      if (!sorted) {
         throw std::runtime_error( "sorted is nullptr." );
      }

      if ( debug ) {
         print_vals<unsigned int>( vals, num_to_sort, "Vals ", ", ", "\n" );
      }

      std::copy( vals, vals + num_to_sort, sorted );
      std::sort( sorted, sorted + num_to_sort );
      
      if ( debug ) {
         print_vals<unsigned int>( sorted, num_to_sort, "Sorted ", ", ", "\n" );
      }

   } catch ( std::exception& ex ) {
      throw std::runtime_error( std::string{__func__} + "(): " + ex.what() );
   }
}


void flatten_by_nrows( unsigned int* flattened_vals, const unsigned int vals[][9], 
      const int& num_rows, const bool& debug = false ) {

   try {
      if (!flattened_vals) {
         throw std::runtime_error( "flattened_vals is nullptr." );
      }

      if ( debug ) {
         for( int row_index = 0; row_index < num_rows; ++row_index ) {
            print_vals<unsigned int>( &(vals[row_index][0]), NColumns, "Vals ", ", ", "\n" );
         } 
      }
      
      for( int row_index = 0; row_index < NRows; ++row_index ) {
         //std::copy( vals[row_index], vals[row_index] + NColumns, &(flattened_vals[row_index * 9]) );
         for( int col_index = 0; col_index < NColumns; ++col_index ) {
            flattened_vals[row_index * NColumns + col_index] = vals[row_index][col_index];
         } 
      }

      if ( debug ) {
         print_vals<unsigned int>( &(flattened_vals[0]), num_rows * 9, "Flattened Vals ", ", ", "\n" );
      }

   } catch ( std::exception& ex ) {
      throw std::runtime_error( std::string{__func__} + "(): " + ex.what() );
   }

}


int main( int argc, char** argv ) {
   try {
      
      unsigned int vals[NRows][NColumns] = {
         { 9, 4, 7, 2, 3, 6, 5, 8, 1 },
         { 2, 8, 4, 7, 1, 5, 6, 3, 9 },
         { 1, 5, 6, 3, 9, 2, 8, 4, 7 }, 
         { 5, 1, 7, 6, 3, 2, 9, 8, 4 }
      };
      unsigned int flattened_vals[NItems];
      unsigned int sorted_flattened_vals[NItems];
      bool debug = true;

      flatten_by_nrows( &(flattened_vals[0]), vals, NRows, debug );
      
      for( int row_index = 0; row_index < NRows; ++row_index ) {
         sort_subset( &(sorted_flattened_vals[row_index * NColumns]), &(flattened_vals[row_index * NColumns]), NColumns, debug );
      } 

      return EXIT_SUCCESS;

   } catch ( std::exception& ex ) {
      std::cout << "ERROR: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}

