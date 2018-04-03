///////////////////////////////////////////////////////////////////////////////
// sort_timing.cpp
//
// Example code showing how to run each algorithm while measuring
// elapsed times precisely. You should modify this program to gather
// all of your experimental data.
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "sort_comparison.hpp"
#include "timer.hpp"

using namespace std;

void print_bar() {
  cout << string(79, '-') << endl;
}

int main() {

  const int n = 10*1000;
  const int MAX_SELECTION_SORT_SIZE = 20*1000;

  auto all_words = load_json_string_array("warandpeace.json");
  assert( all_words );
  assert( n <= all_words->size() );
  
  const StringVector word_vector(all_words->begin(), all_words->begin() + n);
  assert( word_vector.size() == n );

  const StringList word_list(word_vector.begin(), word_vector.end());
  assert( word_list.size() == n );

  double elapsed;
  Timer timer;

  print_bar();
  cout << "n=" << n << endl << endl;

  StringVector selection_sort_solution;
  bool do_selection_sort = (n <= MAX_SELECTION_SORT_SIZE);
  if (!do_selection_sort) {
    cout << "(n too large for selection sort)" << endl;
  } else {
    selection_sort_solution = word_vector;
    timer.reset();
    selection_sort(selection_sort_solution);
    elapsed = timer.elapsed();
    cout << "selection sort elapsed time=" << elapsed << " seconds" << endl;
  }

  timer.reset();
  auto merge_sort_list_solution = merge_sort_list(word_list);
  elapsed = timer.elapsed();
  cout << "merge sort list elapsed time=" << elapsed << " seconds" << endl;
  
  timer.reset();
  auto merge_sort_vector_solution = merge_sort_vector(word_vector);
  elapsed = timer.elapsed();
  cout << "merge sort vector elapsed time=" << elapsed << " seconds" << endl;

  StringVector builtin_sort_solution = word_vector;
  timer.reset();
  builtin_sort(builtin_sort_solution);
  elapsed = timer.elapsed();
  cout << "builtin sort elapsed time=" << elapsed << " seconds" << endl;

  if (do_selection_sort) {
    assert(std::equal(builtin_sort_solution.begin(),
		      builtin_sort_solution.end(),
		      selection_sort_solution.begin()));
  }
  
  assert(std::equal(builtin_sort_solution.begin(),
		    builtin_sort_solution.end(),
		    merge_sort_list_solution->begin()));
  
  assert(std::equal(builtin_sort_solution.begin(),
		    builtin_sort_solution.end(),
		    merge_sort_vector_solution->begin()));

  if (n >= 10) {
    print_bar();
    cout << "first 10 words alphabetically:" << endl;
    for (int i = 0; i < 10; ++i) {
      cout << builtin_sort_solution[i] << ' ';
    }
    cout << endl;
  }
  
  print_bar();

  return 0;
}
