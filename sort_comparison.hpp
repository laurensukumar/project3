///////////////////////////////////////////////////////////////////////////////
// sort_comparison.hpp
//
// Four sorting algorithms:
//
// - the builtin C/C++ sort
// - in-place selection sort
// - merge sort on linked lists
// - merge sort on vectors
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

// standard library headers
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

// user libraries
#include "json.hpp"

// aliases for a vector or list of strings
using StringVector = std::vector<std::string>;
using StringList = std::list<std::string>;

// Load strings from the JSON file at json_path. The JSON file must
// contain precisely one array object, where each element of the array
// is a string. Returns nullptr on I/O error or parse error.
std::unique_ptr<StringVector> load_json_string_array(const std::string& json_path) {

  // Null object to return in the event of error.
  std::unique_ptr<StringVector> io_failure(nullptr);

  // First, try to load a JSON file, whatever it might contain, into
  // root.
  nlohmann::json root;
  {
    // Open file.
    std::ifstream f(json_path);
    if (!f) {
      // file not found
      return io_failure;
    }

    // Parse JSON.
    f >> root;
    if (!f) {
      // JSON parse error
      f.close();
      return io_failure;
    }

    f.close();
    // We're done with the file, so don't need to worry about closing
    // it from now on.
  }

  // Check that the json object is actually an array of strings.
  if (!(root.is_array() &&
	std::all_of(root.begin(),
		    root.end(),
		    [&](const nlohmann::json& element) {
		      return element.is_string();
		    }))) {
    // We got a JSON object, but not the right type of JSON object.
    return io_failure;
  }

  // Now copy the strings out of root and into a StringVector.
  std::unique_ptr<StringVector> result(new StringVector());
  for (auto&& element : root) {
    result->push_back(element);
  }
  return result;
}

// Sort unsorted in-place, using std::sort or qsort.
void builtin_sort(StringVector& unsorted) {
  // TODO: implement this function, then delete this comment
}

// Sort unsorted in-place, using selection sort.
void selection_sort(StringVector& unsorted) {
  // TODO: implement this function, then delete this comment
}

// Sort an unsorted vector using merge sort. Returns a vector
// containing the same elements as unsorted, but in nondecreasing
// order.
std::unique_ptr<StringVector> merge_sort_vector(const StringVector& unsorted) {
  // TODO: implement this function, then delete this comment

  // this return statement will need to be rewritten
  return std::unique_ptr<StringVector>(new StringVector());
}

// Sort an unsorted linked list using merge sort. Returns a linked
// list containing the same elements as unsorted, but in nondecreasing
// order.
std::unique_ptr<StringList> merge_sort_list(const StringList& unsorted) {
  // TODO: implement this function, then delete this comment

  // this return statement will need to be rewritten
  return std::unique_ptr<StringList>(new StringList());
}
