/*
Author: Benjamin Schulte
Student ID: 3051946
Date Created: 2/19/23
Last Updated: 2/20/23
Code Artifact: Lab Extra Credit 1 EECS348
Purpose: Match departments to their preferred programmers
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  /* prgmArr is an array of all of the programmers' preferences, depArr is an array of all of the programmers' preferences,
  and pcPos will be used later to keep track of how many programmers are in prgmChosen array (see line 32) */
  ifstream inp("matching-data.txt");
  unsigned prgmArr[5][5], depArr[5][5], pcPos = 0;

  if (inp.is_open()) // Check for propererly opened file
  {
    for (unsigned i = 0; i < 10; ++i)
    {
      for (unsigned j = 0; j < 5; ++j)
      {
        if (i < 5) // First 5 lines of file are the Departments' preferences
        {
          inp >> depArr[i][j];
        }
        else
        {
          inp >> prgmArr[i-5][j]; // Last 5 lines of file are the Progammers' preferences 
        }
      } 
    }
  }
  inp.close();

  unsigned prgmChosen[4] = { 0 }; // Keeps track of progammers that have already been picked by a department

  for (unsigned i = 0; i < 5; i ++) // Iterates through columns of depArr (each department)
  {
    while (depArr[0][i] != 0) // If depArr[0][i] == 0, department #i has found a progammer
    {
      /*copy[] keeps track of any departments that have the same programmer preference as department #i
        val is department #i's current preference
        pos is # of elements in copy
        prgmPos is department chosen if it goes down to programmer's choice
        inPrgmChosen is if programmer is has already been chosen (in prgmChosen)
        found is if a prgmPos has been found*/
      unsigned copy[5] = { 0 }, val = depArr[0][i], pos = 0, prgmPos;
      bool inPrgmChosen = false, found = false;
      for (unsigned m = 0; m < 4; m ++)
      {
        if (val == prgmChosen[m])
        {
          inPrgmChosen = true;
        }
      }
      if (inPrgmChosen) // Only need to check if department #i's current preference is unpicked
      {
        for (unsigned x = 0; x < 4; x ++) // Shifting preferences up to get the new preference
        {
          swap(depArr[x + 1][i], depArr[x][i]);
        }
        depArr[4][i] = 0;
        continue;
      }
      else
      {
        for (unsigned j = i + 1; j < 5; j ++) // Checking every other department to see if they have the same preference
        {
          if (depArr[0][j] == depArr[0][i])
          {
            copy[pos] = j;
            ++ pos; // Increase number of elements in copy
            for (unsigned x = 0; x < 4; x ++) // Shifting preferences for all department that a copy is found
            {
              swap(depArr[x + 1][j], depArr[x][j]);
            }
            depArr[4][j] = 0;
          }
        }
        if (pos > 0) // Pos > 0 if there was a copy found
        {
          for (unsigned j = 0; j < 5; j ++)
          {
            if (found) // Check programmer to find department at highest preference and skip rest of departments if one is found
            {
              continue;
            }
            else
            {
              for (unsigned k = 0; k < 5; k ++) // Iterate through copy[]
              {
                // If programmer preference is the current department's preference or any of the departments in copy
                if ((prgmArr[j][val - 1] == (i + 1)) || (prgmArr[j][val - 1] == (copy[k] + 1)))
                {
                  prgmPos = j;
                  found = true;
                }
              }
            }
          }
        }
        else // If there are no other departments to compare against, we can just give current department the programmer they want
        {
          prgmPos = i;  
        }        
      }
      cout << "Developer #" << prgmArr[prgmPos][val - 1] << " will get Programmer #" << val << endl;
      depArr[0][(prgmArr[val - 1][prgmPos]) - 1] = 0; // When a department found a match
      prgmChosen[pcPos] = val; // Add programmer used to prgmChosen[]
      ++ pcPos; // Increase # of programmers chosen

      for (unsigned x = 0; x < 4; x ++) // Shifting preferences for current department
      {
        swap(depArr[x + 1][i], depArr[x][i]);
      }
      depArr[4][i] = 0;
    }
  }
}