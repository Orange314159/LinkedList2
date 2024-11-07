/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */
#include <iostream>
#include <fstream>
#include <cmath> 
#include <fstream>
#include "slist.h"
#include "node.h"
#include "airport.h"



void simpleSortTotal(slist& airportList);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  std::ifstream infile;
  char cNum[20] ;
  // Airport* airportArr[13500];			// Replace array with Linked List
  slist airportList;
  int   airportCount;
  //Airport* a[13500];

  infile.open ("./USAirportCodes.csv", std::ifstream::in);
  char trash[100]; 
  infile.getline(trash, 256, '\n');

  if (infile.is_open()) {
    int c=0;
    Airport a1;
    while (infile.good()) {
      infile.getline(a1.code, 256, ',');
      infile.getline(cNum, 256, ',');
      a1.longitude = atof(cNum);
      infile.getline(cNum, 256, '\n');
      a1.latitude = atof(cNum);
      airportList.add(a1);
      
      if ((c % 1000) == 0) {
        std::cout << a1.code << " long: " << a1.longitude << " lat: " << a1.latitude << std::endl;
      }
      
      c++;

    }
    airportCount = c-1;
    infile.close();

    // std::cout << airportList.size() << "init \n";


    simpleSortTotal(airportList);


    // std::cout << airportList.size() << "end \n";

    
    for (int c=0; c < 10; c++){
      Airport ausAirport;
      ausAirport.latitude =  97.6700f;
      ausAirport.longitude = 30.1944f;
      std::cout << airportList.get(c).code   << " long: " << airportList.get(c).longitude   << " lat: " << airportList.get(c).latitude   <<  std::endl;
      std::cout <<"Distance between " << airportList.get(c).code << " and AUS is " << distanceEarth(airportList.get(c).latitude, airportList.get(c).longitude , ausAirport.latitude, ausAirport.longitude) << std::endl;
    }

    airportCount--;
    Airport ausAirport;
    ausAirport.latitude =  97.6700f;
    ausAirport.longitude = 30.1944f;
    std::cout << airportList.get(airportCount).code   << " long: " << airportList.get(airportCount).longitude   << " lat: " << airportList.get(airportCount).latitude   <<  std::endl;
    std::cout <<"Distance between " << airportList.get(airportCount).code << " and AUS is " << distanceEarth(airportList.get(airportCount).latitude, airportList.get(airportCount).longitude , ausAirport.latitude, ausAirport.longitude) << std::endl;


    for (int c=0; c < 1000; c++){
      Airport ausAirport;
      ausAirport.latitude =  97.6700f;
      ausAirport.longitude = 30.1944f;
      double d = distanceEarth(airportList.get(c).latitude, airportList.get(c).longitude , ausAirport.latitude, ausAirport.longitude);

      if(d < 100.0f){
      std::ofstream outfile("output.txt", std::ios::app);
      outfile << airportList.get(c).code   << " long: " << airportList.get(c).longitude   << " lat: " << airportList.get(c).latitude << std::enl;
      outfile.close();
  }
    }


    
  }
  else {
    std::cout << "Error opening file";
  }   
  airportList.clear(); 
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  double finalDistance  = 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
  
  return finalDistance;
}


/*
	Provide sort routine on linked list
*/

Node* mergeSortedLists(Node* left, Node* right) {
  Airport ausAirport;
  ausAirport.latitude = 97.6700f;
  ausAirport.longitude = 30.1944f;


  Node* dummyHead = new Node(Airport());
  Node* current = dummyHead;

  while (left != nullptr && right != nullptr) {
      double distance1 = distanceEarth(left->data.latitude, left->data.longitude, ausAirport.latitude, ausAirport.longitude);
      double distance2 = distanceEarth(right->data.latitude, right->data.longitude, ausAirport.latitude, ausAirport.longitude);


      if (distance1 < distance2) {
          current->next = left;
          left = left->next;
      } else {
          current->next = right;
          right = right->next;
      }
      current = current->next;
  }

  current->next = left ? left : right;

  return dummyHead->next;
}

void mergeSort(Node*& head) {
  if (head == nullptr || head->next == nullptr) {
      return; // Base case
  }

  Node* slow = head, *fast = head->next;
  while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
  }

  Node* right = slow->next;
  slow->next = nullptr;


  // Recursively sort the two halves
  mergeSort(head);
  mergeSort(right);

  // Merge the sorted halves
  head = mergeSortedLists(head, right);
}

void simpleSortTotal(slist& airportList) {
  mergeSort(airportList.head);
}
