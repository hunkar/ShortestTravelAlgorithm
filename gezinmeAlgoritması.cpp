//Hünkar PURTUL
//23.10.2014

#include <iostream>
using namespace std;

bool groupOk(bool*, int); //This function is check all classrooms and if all classrooms are ok return true

int main()
{
    int **relMat;                      //Our relation matrix
    int size;                          //Number of classrooms(We take it from user)
    bool *isInGroup;                   //This will hold classrooms are ok or not
    
//We taking number of classrooms from user
    cout << "Please enter classrooms size: ";
    cin >> size;
    
    isInGroup = new bool[size];         //Our bool array that have classrooms' state
    
//We creating our realtion matrix(It like int "relMat[size][size];" )
    relMat = new int*[size];            
    for(int count = 0; count < size; count++)
    {   
        relMat[count] = new int[size];
        isInGroup[count] = false;
    }

       
// All member of matrix set zero     Ardın
    for(int count = 0; count < size; count++)
       for(int count2 = 0; count2 < size; count2++)
               relMat[count][count2] = 0;


//We taking value of ways
//When I taking value, I dont use 0(zero). But of course I use in processing. Because I want to be friendly to user :)
    for(int count1 = 0; count1 < size; count1++)
        for(int count2 = 0; count2 < count1; count2++)
        {
            cout << "Distance between " << count1+1 << "th and " << count2+1 << "th: ";
            cin >> relMat[count1][count2];
            relMat[count2][count1] = relMat[count1][count2];  //For example I take 1 to 2 and it equals 2 to 1. So I dont take again that.       
            
            if(relMat[count1][count2] < 0 ) 
            {                          
               cout << "You can't enter negative number !!!" << endl;
               --count2;
            }
        }
       
//This values for finding minimum way.
//I made minWaySize=1000000; Because minWayStart's beginning value have to bigger than all ways' size
//minWayStart and minWayStop values hold minimum ways' start and finish classrooms
    int minWaySize = 1000000, minWayStart = 0, minWayStop = 0; 
    
    for(int count1 = 0; count1 < size; count1++)
         for(int count2 = 0; count2 < count1; count2++)    
         {
            //If value of way have to smaller than minWaySize and be different from 0(zero)
               if(relMat[count1][count2] < minWaySize && relMat[count1][count2] != 0)
               {
                  minWaySize = relMat[count1][count2];
                  minWayStart = count1;
                  minWayStop = count2;                           
               }
                 
         }
    
//We print first way   
    cout << minWayStart+1 << " to " << minWayStop+1 << "  distance: " << minWaySize;
//We charnge this way to the 0(zero) because we went this way
    relMat[minWayStart][minWayStop] = relMat[minWayStop][minWayStart] = 0;
//We charnge these classroms' state on isInGroup array
    isInGroup[minWayStart] = true;
    isInGroup[minWayStop] = true;
    
    
    
//If all classrooms states are true, our "while" loop is finish
    while(!groupOk(isInGroup, size))
    {
           minWaySize = 1000000;   //minWaySize setting biggest value
           for(int count1 = 0; count1 < size; count1++)
           {
                   if(!isInGroup[count1]) continue;   //I search only way which in groups
                   else
                   {
                         for(int count2 = 0; count2 < size; count2++)    
                         {
                           //If It smaller than minWaySize and different from 0(zero), it's new minimum way
                              if(relMat[count1][count2] < minWaySize && relMat[count1][count2] != 0)
                              {
                                
                                 minWaySize = relMat[count1][count2];
                                 minWayStart = count1;
                                 minWayStop = count2;                           
                              }
                 
                          }
                   }
                   
      
           }                  
//If minimum ways' begin and finish classrooms in a group, we dont go this way. And we set 0(zero) this way in Relation Matrix
                      if(isInGroup[minWayStart] && isInGroup[minWayStop]) 
                      {
                          relMat[minWayStart][minWayStop] = relMat[minWayStop][minWayStart] = 0; 
                             continue;
                      } 
//We print way. And we change start and finish classrooms' states to true.
                       cout << endl << minWayStart+1 << " to " << minWayStop+1 << "  distance: " << minWaySize << endl;
                       relMat[minWayStart][minWayStop] = relMat[minWayStop][minWayStart] = 0;
                       isInGroup[minWayStart] = true;
                       isInGroup[minWayStop] = true;  

    }
       
    
    system("pause");
    return 0;    
}


//Checking all classrooms and if true all of them return true
bool groupOk(bool *group, int size)
{
     for(int count = 0; count < size; count++)
     {
             if(group[count]) continue;
             else return false;     
     }
     return true;
}