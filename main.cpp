/*
    Divvy Bike Data Analysis program.
    Authors:Syed Shaban
    Date: 11/2/2021
    Class: CS 141, Fall 2021, UIC
    System:  Ubuntu on Windows
    Menu Option 5 Extra Credit URL: https://www.google.com/maps/d/u/0/edit?mid=1kEBEpX9wK7_L-cxFBnXy6ZYR_u0mVIs6&usp=sharing
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>
#include <iomanip> //setprecision
using namespace std;


// Utility functions getting distant between two map points 
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/  
// converting degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
    long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;

    // Calculate the result
    ans = ans * R;

    return ans;
}

struct Entry{
	string rideID, rideableType, startedAt, endedAt, startStation, endStation, startLat, startLng, endLat, endLng, memberCasual;
};

void graph(vector<Entry> &entries){
	vector <int> weekdays(24);
	vector<int> weekends(24);
        int weekdayNumber = 0;
        int weekendNumber = 0;
        int maxRides = 0;
        int colonIndex;
        int integerHour;
        int symbolAmtWeekday;
	int symbolAmtWeekend;
        for (int i = 0; i <24; i++){//to iterate through each hour
                //counters
                weekendNumber = 0;
                weekdayNumber = 0;
                for (int j = 0; j < entries.size(); j++){//loops through each line
                        colonIndex = entries.at(j).startedAt.find(':');//finds first colon
                        integerHour = stoi(entries.at(j).startedAt.substr(colonIndex-2,2));//converts string into integer for hour

                        if ((entries.at(j).startedAt[2] == '4') && (integerHour == i)){//if it matches the hour and day of week, increment
                                weekends.at(i)++;
                                weekendNumber++;
                        }
                        else if ((entries.at(j).startedAt[2] == '1')&&(integerHour == i)){
                                weekdays.at(i)++;
                                weekdayNumber++;
                        }

                }
        }
        for (int m = 0; m < weekdays.size();m++){//to find max rides
                if (weekdays.at(m) > maxRides)
                        maxRides = weekdays.at(m);
                if (weekends.at(m) > maxRides)
                        maxRides = weekends.at(m);
	}
	for (int k = 0; k < 24; k++){
		symbolAmtWeekday = (weekdays.at(k) * 50)/maxRides;
		symbolAmtWeekend = (weekends.at(k)*50)/maxRides;
		if( k < 10 ) cout << " ";
		cout << k << ": ";
		for (int d = 0; d < symbolAmtWeekday; d++){
			cout << "@";
		}
		cout << endl;
		cout <<  "    ";

		for (int e = 0; e < symbolAmtWeekend; e++){
			cout<< "+";
		}
		cout << endl;
	}

}
void displayEntries(vector<Entry> &entries){
        for (int i = 0; i < entries.size();i++){
                cout << entries[i].rideID << "," <<
                        entries[i].rideableType << "," <<
                        entries[i].startedAt << "," <<
                        entries[i].endedAt << "," <<
                        entries[i].startStation << "," <<
                        entries[i].endStation << "," <<
                        entries[i].startLat << "," <<
                        entries[i].startLng << "," <<
                        entries[i].endLat << "," <<
                        entries[i].endLng << "," <<
                        entries[i].memberCasual << endl;
        }
}

void countPerHour(vector<Entry> entries){
	vector<int> weekdays(24);
	vector <int> weekends(24);
	int weekdayNumber = 0;
	int weekendNumber = 0;
	int maxRides = 0;
	int colonIndex;
	int integerHour;
	string temp = "";
	for (int i = 0; i <24; i++){//to iterate through each hour
		//counters
		weekendNumber = 0;
		weekdayNumber = 0;
		for (int j = 0; j < entries.size(); j++){//loops through each line
			colonIndex = entries.at(j).startedAt.find(':');//finds first colon
			integerHour = stoi(entries.at(j).startedAt.substr(colonIndex-2,2));//converts string into integer for hour
			
			if ((entries.at(j).startedAt[2] == '4') && (integerHour == i)){//if it matches the hour and day of week, increment
				weekends.at(i)++;
				weekendNumber++;
			}
			else if ((entries.at(j).startedAt[2] == '1')&&(integerHour == i)){
				weekdays.at(i)++;
				weekdayNumber++;
			}
		
		}
	}
	for (int m = 0; m < weekdays.size();m++){//to find max rides
		if (weekdays.at(m) > maxRides)
			maxRides = weekdays.at(m);
		if (weekends.at(m) > maxRides)
			maxRides = weekends.at(m);
	}
	cout << "LargestNumberOfRides is: " << maxRides << endl;
	cout << "Rides per hour for weekday and weekend:" <<endl;
	for (int k = 0; k<24; k++){//to output all of the rides per hour
		cout << k << ":\t" << weekdays.at(k) << "\t" << weekends.at(k) << endl;
	}
	cout <<endl;


}
void clean(vector<Entry> &entries){
        int faults = 0;
	for (int i = 0; i < entries.size(); i++){
                if ( (entries[i].rideID == "") ||
                     (entries[i].rideableType == "") ||
                     (entries[i].startedAt == "") ||
                     (entries[i].endedAt == "") ||
                     (entries[i].startStation == "") ||
                     (entries[i].endStation == "") ||
                     (entries[i].startLat == "") ||
                     (entries[i].startLng == "") ||
                     (entries[i].endLat == "") ||
                     (entries[i].endLng == "") ||
                     (entries[i].memberCasual == "")){
                        faults++;
                        }
	}
	//cout << faults << endl;
	while(faults != 0){
		for (int i = 0; i < entries.size(); i++){
			if ( (entries[i].rideID == "") ||
                     	     (entries[i].rideableType == "") ||
                     	     (entries[i].startedAt == "") ||
                     	     (entries[i].endedAt == "") ||
                     	     (entries[i].startStation == "") ||
                     	     (entries[i].endStation == "") ||
                     	     (entries[i].startLat == "") ||
                     	     (entries[i].startLng == "") ||
                     	     (entries[i].endLat == "") ||
                     	     (entries[i].endLng == "") ||
                     	     (entries[i].memberCasual == "") ) {
				entries.erase(entries.begin() + i);
				faults--;
                        	}
        	}
	}

}

void selectDataFile(string nameOfFile, vector<Entry> &entries){
	ifstream fileStream(nameOfFile);
	if(!fileStream.is_open())
		cout << "ERROR: File not open\n";
	Entry currEntry;
	while(fileStream.good()){
		getline(fileStream, currEntry.rideID, ',');
		getline(fileStream, currEntry.rideableType, ',');
		getline(fileStream, currEntry.startedAt, ',');
		getline(fileStream, currEntry.endedAt, ',');
		getline(fileStream, currEntry.startStation, ',');
		getline(fileStream, currEntry.endStation, ',');
		getline(fileStream, currEntry.startLat, ',');
		getline(fileStream, currEntry.startLng, ',');
		getline(fileStream, currEntry.endLat, ',');
		getline(fileStream, currEntry.endLng, ',');
		getline(fileStream, currEntry.memberCasual, '\n');
		entries.push_back(currEntry);

	}
	entries.erase(entries.begin());
}

void firstChoice(vector<Entry> &entries){
	int firstChoiceInput = -1;
	cout << "Select datafile:" << endl
		<<"\t1. Small subset of data with 14 rides to help create your program"<< endl
		<<"\t2. Week day vs weekend rides" << endl
		<<"\t3. All September 2021 data (not tested in Zybooks)" << endl
		<<"Your selection--> ";
	cin >> firstChoiceInput;
	cout << endl;
	entries.clear();
	switch (firstChoiceInput){
		case 1:
			selectDataFile("divvyridesampledata.csv", entries);
			break;
		case 2:
			selectDataFile("weekdayweekend.csv", entries);
	        	break;
		case 3:
			selectDataFile("all_divvy_rides_september.csv", entries);
			break;
		default:
			cout << "Not valid" << endl;
			break;
	}
	if (entries.size() != 0){
		cout << "Total # of trips found in datafile: " << entries.size() << endl;
        	//displayEntries(entries);
        	clean(entries);
        	cout << "Total # of trips in clean data: " << entries.size() << endl << endl;
        	//displayEntries(entries);
	}
}
void displayMenu(){
	cout << "Select a menu option:"<< endl
		<<"\t1. Select datafile, display rides totals and clean data"<< endl
		<<"\t2. Display overall trip information"<< endl
		<<"\t3. Display percentage of members vs. casual riders"<< endl
		<<"\t4. Display weekday vs weekend usage"<< endl
		<<"\t5. Extra Credit: find closest station"<< endl
		<<"\t6. Exit"<< endl
		<< "Your choice --> ";

}

void secondChoice(vector<Entry> &entries){
	long double startLat;
	long double startLng;
	long double endLat;
	long double endLng;
	long double totalMiles = 0;
	Entry longestTrip = entries.at(0);
	
	for (int i = 0; i < entries.size(); i++){
		startLat = stod(entries[i].startLat);
		startLng = stod(entries[i].startLng);
		endLat = stod(entries[i].endLat);
		endLng = stod(entries[i].endLng);
		//cout << "Distance: " << distance(startLat, startLng, endLat, endLng) << " Miles"<<endl;
		totalMiles+= distance(startLat, startLng, endLat, endLng);
	
	}
	//to find longest trip
	long double maxStartLat = stod(longestTrip.startLat);
	long double maxStartLng = stod(longestTrip.startLng);
	long double maxEndLat = stod(longestTrip.endLat);
	long double maxEndLng = stod(longestTrip.endLng);
	for (int j = 1; j < entries.size();j++){
		startLat = stod(entries[j].startLat);
                startLng = stod(entries[j].startLng);
                endLat = stod(entries[j].endLat);
                endLng = stod(entries[j].endLng);	
		if ( distance(startLat, startLng, endLat, endLng) > distance(maxStartLat, maxStartLng, maxEndLat, maxEndLng)){
			maxStartLat = startLat;
			maxStartLng = startLng;
			maxEndLat = endLat;
			maxEndLng = endLng;
			longestTrip = entries[j];
		

		}



	}
	int integerValue = totalMiles+1;
	cout << "Total # of miles traveled: " << integerValue << endl;
	cout << "Average length of trips in miles: " <<setprecision(1) << fixed << 1.0*integerValue/entries.size() << endl;
	cout << "Longest trip information below:" <<endl;
	cout<< "-------------------------------" <<endl;
	cout << "Trip ID: " << longestTrip.rideID <<endl;
	cout << "Trip start location: " << longestTrip.startStation << endl;
	cout << "Trip end location: " << longestTrip.endStation << endl;
	double distancemax = distance(maxStartLat, maxStartLng, maxEndLat, maxEndLng);
	cout << "Trip distance in miles: " << setprecision(1) << fixed << distancemax << endl << endl;

}

void thirdChoice(vector<Entry> &entries){
	int memNum = 0;
	int casNum = 0;
	for (int i = 0; i < entries.size(); i++){
		if (entries[i].memberCasual.compare("member") == 1) 
			memNum++;
		else if (entries[i].memberCasual.compare("casual") == 1) 
			casNum++;
	}
	double memPercent = 0.0;
	double casPercent = 0.0;
	double total = (memNum*1.0) + (casNum*1.0);
	memPercent = (memNum * 100.0);
	memPercent /= total;
	casPercent = (casNum * 100.0);
	casPercent /= total;
	cout << "Casual Rider Percentage: " << setprecision(1) << fixed << casPercent << "%" << endl;
	cout << "Member Rider Percentage: " << setprecision(1) << fixed << memPercent << "%" << endl << endl;
}

void fourthChoice(vector<Entry> &entries){
	
	int fourthChoiceInput = -1;
	cout <<"Select type of display: " << endl;
	cout << "\t1. Counts of rides per hour in the day" << endl;
	cout << "\t2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
	cout << "Your selection--> ";
	cin >> fourthChoiceInput;
	cout << endl;
	switch (fourthChoiceInput){
		case 1:
			countPerHour(entries);
			break;
		case 2:
			graph(entries);
			break;
		default:
			cout << "Not valid" << endl;
			break;
	}
}
void fifthChoice(vector<Entry> &entries){

}
int main()
{
	vector< Entry> entries;
	int input= -1;
	cout << "Analyze Divvy bike ride information using September trip data.\n" <<
		"First select option 1 to read and clean the data." << endl << endl;
	displayMenu();
	cin >> input;
	if (input != 1){
		if(input == 6) {
			exit(0);
		}	
		while(input != 1){
			cout << "\tFirst read in data by selecting menu option 1" << endl << endl;
			displayMenu();
			cin >> input;
			if (input == 1){
				firstChoice(entries);
			}
			if(input == 6) {
                        exit(0);
                }
		}
	}

	else {
		firstChoice(entries);
	}
	while(input != 6){
		displayMenu();
		cin >> input;
		cout << endl;
		switch (input){
			case 1:
				firstChoice(entries);
				break;
			case 2:
				secondChoice(entries);
				break;
			case 3:
				thirdChoice(entries);
				break;
			case 4:
				fourthChoice(entries);
				break;
			case 5: fifthChoice(entries);
				break;
			case 6:

				exit(0);
				break;
			default:
				cout << "Not valid" << endl;
				break;
		}
	}

	return 0;
}
