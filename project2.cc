///////////////////////////////////////////////////////////////////////////////
// project2.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "project2.hh"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//-----------------------------------------------------------------------------
// Randomize the order of all items in the list
//-----------------------------------------------------------------------------
void randomize_list(string_vector & strings) {

	int randomNumber;
	srand(time(NULL));
	for(int i = 0; i < strings.size() - 1; i++)
	{
		randomNumber = rand() % strings.size();
		swap(strings[randomNumber], strings[i]);
	}
  	return;
}

//-----------------------------------------------------------------------------
void merge(string_vector & strings, size_t start, size_t mid, size_t end) {
 
	// Create temporary vectors for both sides
	vector<string> left, right;
 
	for (int i = start; i <= mid; i++) 
	{
		left.push_back(strings[i]);
	}

	for (int i = mid + 1; i <= end; i++) 
	{
		right.push_back(strings[i]);
	}

	int s = start;
	// While there is still something in at least one vector
	while (left.size() > 0 || right.size() > 0) 
	{
		// While both vectors still have something		
		if (left.size() > 0 && right.size() > 0)
		{
			if (left.front().compare(right.front()) < 0) 
			{
				strings[s] = (string)left.front();
				left.erase(left.begin());
			} 
			else
			{
				strings[s] = (string)right.front();
				right.erase(right.begin());
			}
			s++;
		}
		// if one vector is empty, finish the non-empty vector  
		else if (left.size() > 0) 
		{
			for (int i = 0; i < left.size(); i++)
			{
				strings[s] = left[i];
				s++;
			}		
			break;
		}  
		else if (right.size() > 0) 
		{
			for (int i = 0; i < right.size(); i++)
			{
				strings[s] = right[i];	
				s++;
			}
			break;
		}
	}
	return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings, size_t start, size_t end) {

	if (start < end) 
    	{ 
        	int middle = (start + end) / 2; 
        	mergesort(strings, start, middle); 
        	mergesort(strings, (middle + 1), end); 
        	merge(strings, start, middle, end); 
    	} 
  	return;

}

//-----------------------------------------------------------------------------
// Implementation of the Hoare Partition.
// This partition uses the first element of the list as a partition
// and divides the list into less than and greater than the pivot value
// It returns the index of the final position of the pivot value.
//-----------------------------------------------------------------------------
int hoare_partition(string_vector & strings, int start, int end) {

	string pivot = strings[start];
    	int i = start - 1;
    	int j = end + 1;
    	while(true)
	{
        	do
		{
            		j--;
        	}
		while(strings[j].compare(pivot) > 0);

        	do
		{
            		i++;
       		}
		while(strings[i].compare(pivot) < 0);

            	swap(strings[j], strings[i]);

        	if(i >= j)
		{
			// undo last swap
            		swap(strings[j], strings[i]);

			// swap the pivot
			swap(strings[start], strings[j]);	
			
			return j;
		}
	}
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This is a recursive method which splits the list into two
// parts, recursively calls itself on the two parts and then merges 
// the two parts together using the merge() method.
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings, int start, int end) {

	if (start < end)
	{
		int partition = hoare_partition(strings, start, end);
		quicksort(strings, start, partition);
		quicksort(strings, (partition + 1), end);
	}
  	return;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ALREADY IMPLEMENTED 
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
//-----------------------------------------------------------------------------
bool load_words(string_vector& words, const std::string& path) 
{
  //std::cout << "Loading words from [" << path << "]" << std::endl;
  words.clear();
  std::ifstream ifs(path.c_str());
  if (!ifs.is_open() || !ifs.good()) {
    //cout << "Failed to open [" << path << "]" << std::endl;
    return false;
  }
  int countWordsLoaded = 0;
  while (!ifs.eof()) {
    std::string lineBuffer;
    std::getline(ifs, lineBuffer);
    if (ifs.eof()) {
      break;
    }
    words.push_back(lineBuffer);
    countWordsLoaded++;
  }
  //std::cout << "Loaded " << countWordsLoaded << " words from [" << path << "]" << std::endl;;
  return true;
}

//-----------------------------------------------------------------------------
// Sort the given list using the merge sort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void mergesort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  mergesort(strings, 0, strings.size() - 1);
  return;
}

//-----------------------------------------------------------------------------
// Sort the given list using the quicksort algorithm.
// This method is simply a helper to make the initial 
// call the recursive mergesort() method below that requires
// first and last indexes for sorting range
//-----------------------------------------------------------------------------
void quicksort(string_vector & strings) {
  if (strings.size() == 0) {
    return;
  }
  quicksort(strings, 0, strings.size() - 1);
  return;
}

