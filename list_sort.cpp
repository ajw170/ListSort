/*
 *  list_sort.cpp
    Andrew J Wood - COP4531 - Algorithms
    9/26/2018

    Implementation of List<T>::Sort() using the bottom up merge sort algorithm.  Note that the
    runtime is O (n log n) while the space overhead is O(1) since this is specifically designed
    for linked lists.

    Note also that since the runspace is constant, there should be no increasing recursive call stack.
    This means that the algorithm will use iteration as opposed to recursion.

    Note that the code is self-documenting.
*/

#include <list.h>

template<typename T>
template<class P>
void fsu::List<T>::Sort(P &comp)
// list sort: in place, stable, Theta(n log n), runspace O(1)
{
  Link * p1; //pointer to element in first set
  Link * p2; //pointer to element in second set
  
  size_t numMerges = 0;
  size_t segSize = 1; //the size of the segments to be merged, starting with size 1
  
  //set current segment to the first link in the list
  p1 = head_->next_; //will be nullptr if there is nothing in the list (edge case)
  p2 = p1; //initially set the p2 pointer to p2
  Link * r; //initially set r to the head node as the initial receiver
  
  //set the head and tail nodes aside to serve as carrier base
  //head_->next_ = tail_; // (head_-> prev is nullptr)
  //tail_->prev_ = head_; // (tail_-> next is nullptr)
  
  tail_->prev_->next_ = nullptr; //detach the tail and re-attach it later.  the last link in the chain will have a
  //next_ value of nullptr.
  tail_->prev_ = nullptr;
  
  size_t totalAdvanceCounter = 0;
  
  do
  { //begin outer loop with seg size = 1.
    r = head_;
    numMerges = 0; //reset merge counter
    
    while (p2 != nullptr) //break when the end of the chain is reached.
    {
      //place the next segment pointer in the correct starting position
      for (size_t k = 0; k < segSize; ++k)
      {
        p2 = p2->next_;
        //++totalAdvanceCounter;
        if (p2 == nullptr) //if p2 winds up hitting nullptr break out
        {
          break;
        }
      } //p1 and p2 are now in place
      
      size_t p1Advance = 0;
      size_t p2Advance = 0;
      
      size_t segAdvanceSize = segSize - 1;
      
      //run the loop so that it will stop when the points stop have reached maximum advance point
      while (p1Advance <= segAdvanceSize && p2Advance <= segAdvanceSize) // ensure bounds are followed
      {
        //check if p2 is null, break if so.
        if (p2 == nullptr)
          break;
        
        if (comp(p1->Tval_,p2->Tval_))
        {
          r->next_ = p1; //set the next link in the chain.
          r->next_->prev_ = r; //set the next node's previous pointer node to the one just added
          r = r->next_; //advance r pointer to next position
          p1 = p1->next_; //advance p1 pointer
          r->next_ = nullptr; //set next_ to nullptr to avoid confusion and for debugging purposes
          ++p1Advance;
          ++totalAdvanceCounter;
        }
        else // (comp(p1->Tval_,p2->Tval_))
        {
          r->next_ = p2;
          r->next_->prev_ = r;
          r = r->next_; //advance r pointer to next position
          p2 = p2->next_; //advance p2.
          r->next_ = nullptr;
          ++p2Advance;
          ++totalAdvanceCounter;
        }
      }
      while (p1Advance <= segAdvanceSize) //finish off left side of chain
      {
        if (p1 == nullptr)
          break;
        r->next_ = p1;
        r->next_->prev_ = r;
        r = r->next_; //advance r pointer to next position
        p1 = p1->next_; //advance p1
        r->next_ = nullptr;
        ++p1Advance;
        ++totalAdvanceCounter;
      }
      while (p2Advance <= segAdvanceSize) //finish off right side of chain
      {
        if (p2 == nullptr)
          break;
        r->next_ = p2;
        r->next_->prev_ = r;
        r = r->next_; //advance r pointer to next position
        p2 = p2->next_; //advance p2
        r->next_ = nullptr;
        ++p2Advance;
        ++totalAdvanceCounter;
      }
      
      ++numMerges;
      p1 = p2; //set p1 to p2, so that p2 can advance.
      
    } //end while
    
    // reset pointers to point to first element
    p1 = head_->next_;
    p2 = p1; //set p2 to p1 (could be nullptr)
    
    //code to multiply the segment size by 2
    
    segSize *= 2;
    
  } while(numMerges > 1); //break if there was only one merge, indicating the end.
  //fix remainders and tie up loose ends (prev_ links and head_ and tail_ nodes)
  
  //tie up loose ends by repairing tail node from remembered "r" link
  r->next_ = tail_;
  r->next_->prev_ = r;


}



/*Sort Without Predicate object; uses default <*/
template<typename T>
void fsu::List<T>::Sort()
{
  Link * p1; //pointer to element in first set
  Link * p2; //pointer to element in second set

  size_t numMerges = 0;
  size_t segSize = 1; //the size of the segments to be merged, starting with size 1

  //set current segment to the first link in the list
  p1 = head_->next_; //will be nullptr if there is nothing in the list (edge case)
  p2 = p1; //initially set the p2 pointer to p2
  Link * r; //initially set r to the head node as the initial receiver

  //set the head and tail nodes aside to serve as carrier base
  //head_->next_ = tail_; // (head_-> prev is nullptr)
  //tail_->prev_ = head_; // (tail_-> next is nullptr)

  tail_->prev_->next_ = nullptr; //detach the tail and re-attach it later.  the last link in the chain will have a
                                  //next_ value of nullptr.
  tail_->prev_ = nullptr;

  size_t totalAdvanceCounter = 0;

  do
  { //begin outer loop with seg size = 1.
    r = head_;
    numMerges = 0; //reset merge counter

    while (p2 != nullptr) //break when the end of the chain is reached.
    {
      //place the next segment pointer in the correct starting position
      for (size_t k = 0; k < segSize; ++k)
      {
        p2 = p2->next_;
        //++totalAdvanceCounter;
        if (p2 == nullptr) //if p2 winds up hitting nullptr break out
        {
            break;
        }
      } //p1 and p2 are now in place

      size_t p1Advance = 0;
      size_t p2Advance = 0;

      size_t segAdvanceSize = segSize - 1;

      //run the loop so that it will stop when the points stop have reached maximum advance point
      while (p1Advance <= segAdvanceSize && p2Advance <= segAdvanceSize) // ensure bounds are followed
      {
          if (p2 == nullptr) //if p2 is null, only adding the p1 side remains.
            break;
          if (p1->Tval_ <= p2->Tval_)
          {
            r->next_ = p1; //set the next link in the chain.
            r->next_->prev_ = r; //set the next node's previous pointer node to the one just added
            r = r->next_; //advance r pointer to next position
            p1 = p1->next_; //advance p1 pointer
            r->next_ = nullptr; //set next_ to nullptr to avoid confusion and for debugging purposes
            ++p1Advance;
            ++totalAdvanceCounter;
          }
          else // (p1->Tval_ > p2->Tval_)
          {
            r->next_ = p2;
            r->next_->prev_ = r;
            r = r->next_; //advance r pointer to next position
            p2 = p2->next_; //advance p2.
            r->next_ = nullptr;
            ++p2Advance;
            ++totalAdvanceCounter;
          }
      }
      while (p1Advance <= segAdvanceSize) //finish off left side of chain
      {
        r->next_ = p1;
        if (p1 == nullptr)
          break;
        r->next_->prev_ = r;
        r = r->next_; //advance r pointer to next position
        p1 = p1->next_; //advance p1
        r->next_ = nullptr;
        ++p1Advance;
        ++totalAdvanceCounter;
      }
      while (p2Advance <= segAdvanceSize) //finish off right side of chain
      {
        r->next_ = p2;
        if (p2 == nullptr)
          break;
        r->next_->prev_ = r;
        r = r->next_; //advance r pointer to next position
        p2 = p2->next_; //advance p2
        r->next_ = nullptr;
        ++p2Advance;
        ++totalAdvanceCounter;
      }

      ++numMerges;
      p1 = p2; //set p1 to p2, so that p2 can advance.

    } //end while

    // reset pointers to point to first element
    p1 = head_->next_;
    p2 = p1; //set p2 to p1 (could be nullptr)

    //code to multiply the segment size by 2

    segSize *= 2;

  } while(numMerges > 1); //break if there was only one merge, indicating the end.
  //fix remainders and tie up loose ends (prev_ links and head_ and tail_ nodes)

  //tie up loose ends by repairing tail node from remembered "r" link
  r->next_ = tail_;
  r->next_->prev_ = r;
  
  
} //end Sort()
