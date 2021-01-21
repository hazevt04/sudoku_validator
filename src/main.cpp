// C++ File for main

//#include <iostream>
//#include <algorithm>
#include "my_utils.hpp"

void sort_nine( unsigned int* sorted, const unsigned int* vals, const bool& debug = false ) {
   try {
      if (!vals) {
         throw std::runtime_error( "vals is nullptr." );
      }
      if (!sorted) {
         throw std::runtime_error( "sorted is nullptr." );
      }

      if ( debug ) {
         print_vals<unsigned int>( vals, 9, "Vals ", ", ", "\n" );
      }

      std::copy( vals, vals + 9, sorted );
      std::sort( sorted, sorted + 9 );
      
      if ( debug ) {
         print_vals<unsigned int>( sorted, 9, "Sorted ", ", ", "\n" );
      }

   } catch ( std::exception& ex ) {
      throw std::runtime_error( std::string{__func__} + "(): " + ex.what() );
   }
}


void flatten_by_nine( unsigned int* flattened_vals, const unsigned int** vals, 
      const int& num_rows, const bool& debug = false ) {

   try {
      if (!vals) {
         throw std::runtime_error( "vals is nullptr." );
      }
      if (!flattened_vals) {
         throw std::runtime_error( "flattened_vals is nullptr." );
      }

      if ( debug ) {
         for( int row_index = 0; row_index < num_rows; ++row_index ) {
            print_vals<unsigned int>( &(vals[row_index][0]), 9, "Vals ", ", ", "\n" );
         } 
      }
      
      for( int row_index = 0; row_index < num_rows; ++row_index ) {
         //std::copy( vals[row_index], vals[row_index] + 9, &(flattened_vals[row_index * 9]) );
         for( int col_index = 0; col_index < 9; ++col_index ) {
            flattened_vals[row_index * 9 + col_index] = vals[row_index][col_index];
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
      
      unsigned int vals[4][9] = {
         { 9, 4, 7, 2, 3, 6, 5, 8, 1 },
         { 2, 8, 4, 7, 1, 5, 6, 3, 9 },
         { 1, 5, 6, 3, 9, 2, 8, 4, 7 }, 
         { 5, 1, 7, 6, 3, 2, 9, 8, 4 }
      };
      unsigned int sorted[4][9];
      unsigned int flattened_vals[36];
      bool debug = true;
      
      flatten_by_nine( &(flattened_vals[0]), &(*vals[0]), debug );
      sort_nine( &(sorted[0][0]), &(vals[0][0]), debug );
      sort_nine( &(sorted[1][0]), &(vals[1][0]), debug );

      return EXIT_SUCCESS;

   } catch ( std::exception& ex ) {
      std::cout << "ERROR: " << ex.what() << "\n";
      return EXIT_FAILURE;
   }
}

