#include "inverseKinematics.h"

#define ABS(a) (a)>0?(a):-1*(a)
#define moddiff(a,b) ((a > b) ? (a-b) : (b-a))

int angle[] = {0,1,3,5,6,8,10,12,14,15,17,19,21,23,24,26,28,30,32,34,36,38,40,42,44,46,48,50,53,55,57,60,62,64,67,70,72,75,78,80,83,86,90,93,96,99,103,107,111,115,119,123,127,132,137,142,148,153,160,166,173,180,188,196,205,214,224,235,247,260,274,290,307,327,348,373,401,433,470,514,567,631,711,814,951,1143,1430,1908,2863,5728};

int nrst_num(int lo,int hi,int key) 
{
  int mid = 0;
  int mid_parent = 0;

  while (lo < hi)
  {
      mid_parent = mid;
      mid = (lo + hi) / 2; 

      if (key == angle[mid])
      {
        return mid;
      }
      else if (key < angle[mid])
      {
        hi = mid - 1;
      }
      else if (key > angle[mid])
      {
        lo = mid + 1;
      }   
  }

  int ldiff = moddiff(key,angle[lo]);
  int mdiff = moddiff(key,angle[mid]);
  int hdiff = moddiff(key,angle[hi]);
  int mid_parent_diff = moddiff(key,angle[mid_parent]);

  /* select the index from the lowest diff */
  if ((mid_parent_diff <= mdiff) && (mid_parent_diff <= ldiff) && (mid_parent_diff <= hdiff))
  {
      return mid_parent;
  }
  else if ((mdiff <= mid_parent_diff) && (mdiff <= ldiff) && (mdiff <= hdiff))
  {
      return mid;
  }
  else if ((ldiff <= mdiff) && (ldiff <= hdiff) && (ldiff <= mid_parent_diff))
  {
      return lo;
  }
  return hi; 
}


int getAngle(int value)
{
   return nrst_num(0,90,value)+1;
}
