#include<iostream>
#include <ctime>
#include <string>
#include "errorqueue.h"
#include "messgaequeue.h"
#include "Replyqueue.h"
#include "Requestqueue.h"
#pragma warning(disable:4996)

/*
 *COSC 2430 
 * Arya HajiTaheri
 */
using std::string;
using std::cout;

string randomString(int);
void DatePlusDays(struct tm* date, double days);
void developmessage(int&, string, tm*);

int main(int argc, char *argv[])
{
	const int ndays = 30; // number of days in month
	int totalMessage = 1; //initial number of messages
	char buffer[60]; 
	tm *date;
	time_t current_time;

	time(&current_time);//get current date and tme
	date = localtime(&current_time); // get localtime


	int k = 1;
	while (k <= ndays) //while less than 1 month
	{
		cout << "NO.\tName\t\t\t\tType\t\tValue\t\tDate\t\tTime\n\n";

		DatePlusDays(date, 1); // increment date by 1 day
		strftime(buffer, sizeof(buffer), "%d-%m-%Y", date); // get date as string
		developmessage(totalMessage, buffer, date); // run server

		k++;
	}
	return 0;
}
// generate a random string that is valid as defined by the paremeters 
string randomString(int len)
{
	int pos, i = 0;

	string newstr = "", tmp = "";
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_-.0123456789";
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		tmp = str.substr(pos, 1);
		if (i == 0 && tmp == "." || i == len - 1 && tmp == ".") {
			--i;
			continue;
		}
		newstr += tmp;
		i++;
	}
	return newstr;
}
//utility function that adds/subtracts to current time.
void DatePlusDays(struct tm* date, double days)
{
	const time_t ONE_DAY = 24 * 60 * 60;

	time_t date_seconds = mktime(date) + (days * ONE_DAY);

	*date = *localtime(&date_seconds); ;
}
/*Server function
 *4 queues
 *all messages are equally likely to be generated
 *upto 1000 messages a month or 32-41 messages a day are premited 
 */
void developmessage(int &totalmessage, string datestr, tm* date) {
	srand(time(NULL));
	request_queue<string> requestQ; // 0
	reply_queue<string> replyQ;  // 1
	message_queue<string> messageQ; // 2
	error_queue<string> errorQ; // 3
	const int MESSAGE_LEN = 25, MAXMESSAGE = 1000; // message length
	double timeincrement = 0.0005; 
	int  maxmessage =41 , minmessage = 32,
		messageperDay = minmessage + (rand() % (maxmessage - minmessage + 1)),
		random_Qtype = 0, k = 0;
	char buffer[40];
	string message = "";
	while (totalmessage <= MAXMESSAGE && k <= messageperDay)
	{
		message = randomString(MESSAGE_LEN);
		random_Qtype = rand() % 4;
		switch (random_Qtype) {
		case 0:
			requestQ.enqueue(message); // add to queue
			DatePlusDays(date, timeincrement); // increment time
			strftime(buffer, sizeof(buffer), "%I:%M : %S", date); 
			cout << totalmessage << "\t" << message << "\tstring\t\t" << "Request\t\t" << datestr << "\t" << buffer << "\n"; break; //print message
		case 1:
			replyQ.enqueue(message);  // add to queue
			DatePlusDays(date, timeincrement); // increment time
			strftime(buffer, sizeof(buffer), "%I:%M : %S", date);
			cout << totalmessage << "\t" << message << "\tstring\t\t" << "reply\t\t" << datestr << "\t" << buffer << "\n"; break;//print message
			replyQ.dequeue(); 
		case 2:
			messageQ.enqueue(message);  // add to queue
			DatePlusDays(date, timeincrement); // increment time
			strftime(buffer, sizeof(buffer), "%I:%M : %S", date);
			cout << totalmessage << "\t" << message << "\tstring\t\t" << "message\t\t" << datestr << "\t" << buffer << "\n"; break;//print message
		case 3:
			errorQ.enqueue(message); // add to queue
			DatePlusDays(date, timeincrement);// increment time
			strftime(buffer, sizeof(buffer), "%I:%M : %S", date);
			cout << totalmessage << "\t" << message << "\tstring\t\t" << "error\t\t" << datestr << "\t" << buffer << "\n"; break;//print message
			if (errorQ.size() >= 5) { //dequeue if more than 5 messages are stored
				while (!errorQ.isEmpty()) {
					errorQ.dequeue();
				}
			}

		default:
			std::cerr << "Error";
			break;
		};
		k++;
		totalmessage++;
	}
	if (totalmessage >= MAXMESSAGE) {
		cout << "\nMaximum size of 1000 messages per month reached. Please try again next month.\n";
	}
	DatePlusDays(date, -timeincrement *k);
	cout << "\n";
}